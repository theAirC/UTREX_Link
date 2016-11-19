// Classes used to make, export/import and use configuration files.
// This will enable external configuration editing, using javascript web-apps for example.

class Config
{
private:
    const char *const filename;
    JSON json;

public:

    Config(const char *filename) : filename(filename) {}

    int load()
    {
		SDL_RWops *SDL_FileHandle = SDL_RWFromFile(filename, "r");            // open for readng
		if (!SDL_FileHandle) SDL_FileHandle = SDL_RWFromFile(filename, "w+"); // create and open for readng
        if (!SDL_FileHandle) return -1;

        // our FileSize is in chars, SDL returns the size in bytes
        size_t FileSize = upperdiv(SDL_RWsize(SDL_FileHandle), sizeof(char)); // usually sizeof(char) == 1, so no division is done
        if (FileSize < 0) return -1;
        
		char *FileContent = new char[FileSize + 1]; // 1 more to add termination
        size_t actualSize = SDL_RWread(SDL_FileHandle, &FileContent[0], sizeof(char), FileSize); // actualSize is in chars
		FileContent[actualSize] = '\0';
		SDL_RWclose(SDL_FileHandle);

        json = JSON::parse(FileContent);
        delete[] FileContent;

        // Validate and fix json if needed

        for (size_t i = 0; i < json["InputControls"].size(); i++) {
            auto &I = json["InputControls"][i]; // contains the count of each type of input controls (Deltas, Ranges, States, Buttons)

            InputDevices.push_back(new InputDevice(I[0], I[1], I[2], I[3]));
        }

        for (size_t i = 0; i < json["MixerNames"].size(); i++) {
            std::string MixerName = json["MixerNames"][i];

			MixerLib::MixerMaker MM = MixerLib::FindMixer(MixerName);
            if (MM == nullptr) {
                json["MixerNames"].erase(i);
                json["MapMixer"].erase(i);
				i--; // Very important !! because we just erased one entry
            }
            else Mixers.push_back(MM());
        }
        
        for (size_t i = 0; i < json["OutputCurves"].size(); i++) {
            for (size_t j = 0; j < json["OutputCurves"][i].size(); j++) {
				JSON curve = json["OutputCurves"][i][j];
				std::string name = curve[0];
				u64 scale = curve[1];
				u64 params = curve[2];
                
                Output *o = new Output(Curve(("Curves/" + name + ".bin").data()));
				o->myCurve.applyScale(scale);
				o->myCurve.processParams(params);
                Outputs.push_back(o);

                size_t attachedMixerIndex = json["MapOutput"][i][j];
                if (attachedMixerIndex >= 0 && attachedMixerIndex < Mixers.size()) o->myMixer = Mixers[attachedMixerIndex];
            }
        }

        return 0;
    }

    void updateInput(size_t deviceIndex, InputDevice *device)
    {
        // Note that testing a size_t == ~0 is valid, but a size_t < 0 is problematic if size_t is unsigned.
        if (deviceIndex != ~0) {
            delete InputDevices[deviceIndex];
            InputDevices[deviceIndex] = device;

            auto &temp = json["InputControls"][deviceIndex];
            temp[0] = device->Deltas.Length;
            temp[1] = device->Ranges.Length;
            temp[2] = device->States.Length;
            temp[3] = device->Buttons.Length;
        }
        else {
            InputDevices.push_back(device);
            
            std::vector<size_t> newEntry({ device->Deltas.Length, device->Ranges.Length, device->States.Length, device->Buttons.Length });
            json["InputControls"].push_back(newEntry);
        }
    }
    void updateInput(SDL_JoystickGUID deviceGUID, InputDevice *device)
    {
        Array<byte> guid(sizeof(SDL_JoystickGUID::data), deviceGUID.data);

        // find deviceGUID index in json[InputGUIDs]
        for (size_t i = 0; i < json["InputGUIDs"].size(); i++) {
            std::vector<byte> v = json["InputGUIDs"][i];
            Array<byte> tempGuid(sizeof(SDL_JoystickGUID::data), v.data());
			if (guid == tempGuid) {
				updateInput(i, device);
				return;
			}
        }

		// Not found, so add it.
		std::vector<byte> v(guid.Raw, guid.Raw + guid.Length);
		json["InputGUIDs"].push_back(v);
        updateInput(~0, device);
    }

    void mapInputs()
    {
        JSON &jMM = json["MapMixer"];
        // for each Mixer
        for (size_t i = 0; i < jMM.size(); i++) {
            // for each control type

            // for each control
            for (size_t k = 0; k < jMM[i][0].size(); k++) {
                // we have 2 coordinates
                std::vector<size_t> coord = jMM[i][0][k];

                // the first one shows the InputDevice
                InputDevice *ID = InputDevices[coord[0]];

                // the second shows the index of the corresponding control
                Mixers[i]->Deltas[k] = &(ID->Deltas[coord[1]]);
            }
            for (size_t k = 0; k < jMM[i][1].size(); k++) {
                std::vector<size_t> coord = jMM[i][1][k];
                InputDevice *ID = InputDevices[coord[0]];
                Mixers[i]->Ranges[k] = &(ID->Ranges[coord[1]]);
            }
            for (size_t k = 0; k < jMM[i][2].size(); k++) {
                std::vector<size_t> coord = jMM[i][2][k];
                InputDevice *ID = InputDevices[coord[0]];
                Mixers[i]->States[k] = &(ID->States[coord[1]]);
            }
            for (size_t k = 0; k < jMM[i][3].size(); k++) {
                std::vector<size_t> coord = jMM[i][3][k];
                InputDevice *ID = InputDevices[coord[0]];
				Mixers[i]->Buttons[k] = &(ID->Buttons[coord[1]]);
                //Mixers[i]->Buttons[k] = ID->Buttons.GetPointer(coord[1]);
            }
        }
    }

	int save()
	{
		SDL_RWops *SDL_FileHandle = SDL_RWFromFile(filename, "w"); // create and open for writing
		if (!SDL_FileHandle) return -1;

		std::string content = json.dump(4);
		size_t length = content.length();
		int result = SDL_RWwrite(SDL_FileHandle, content.data(), sizeof(char), length) - length;
		SDL_RWclose(SDL_FileHandle);

		return result;
	}
};
