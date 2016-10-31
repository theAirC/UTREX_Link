
struct Serial
{
	static const u32 Baudrate = 38400;
    static const byte bytesPerLine = 8;
	static const byte Preamble[2]; // 'Start' byte
    
    std::vector<Output*> myOutputs;
    serial::Serial mySerial;
    Stack<byte, 256> Buffer; // a large buffer used to send data to the serial port

    Serial(const std::string &PortName)
        : mySerial(PortName, Baudrate)
    {
		mySerial.setDTR(1);
	}

	void SendOutputs()
	{
		mySerial.write(Preamble, sizeof(Preamble));

		// First, reset the buffer.
		Buffer.Count = 0;

		// Then generate/read the outputs one-by-one and write to the buffer.
		for (size_t i = 0; i < Outputs.size(); i++) {
			u16 v = Outputs[i]->Get();
			byte temp;

			temp = v >> 8; // MSB first
			Buffer.Add(temp);
			if (temp == 0xBF) Buffer.Add(~0); // escape byte

			temp = v & 0xFF;
			Buffer.Add(temp);
			if (temp == 0xBF) Buffer.Add(~0); // escape byte
		}

		// We may need to add padding, if the data in the buffer is not a multiple of bytesPerLine.
		Buffer.Count = upperdiv(Buffer.Count, bytesPerLine) * bytesPerLine;

        // Finally, send the buffer.
        mySerial.write(Buffer.Data, Buffer.Count);
    }
};

const byte Serial::Preamble[] = { 0xBF, 0x00 };
