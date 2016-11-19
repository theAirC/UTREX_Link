// This file #includes multiple other files with Mixer classes inside them.
// You can write your own Mixer in another file and #include it here.
// Don't forget to add your Mixer to the MixerList (down below) as well.

#include "DirectMixers.cpp"
#include "CommonMixers.cpp"

#include "CustomMixers.cpp" // Add your own mixers to this file

namespace MixerLib {

	// MixerMaker: a pointer to a function that generates a new mixer of some type
	typedef Mixer *(*MixerMaker)();
	// MakeMixer: a template function that generates a new mixer of the given type
	template <class MixerType> Mixer *MakeMixer() { return new MixerType; }

	// MixerEntry: a struct that holds both the factory (generator function) of a mixer type and its name
	struct MixerEntry
	{
		MixerMaker generator;
		std::string name;
	};

	// a useful macro that simplifies mixer type registration in the MixerList
	#define _MixerEntry(x) { MakeMixer<x>, #x }

	// Register your Mixer here, like the examples.
	const MixerEntry MixerList[] = {

		// Direct Mixers
		_MixerEntry(DirectDelta),
		_MixerEntry(DirectRange),
		_MixerEntry(DPadStateY),
		_MixerEntry(DPadStateX),
		_MixerEntry(DirectButton),

		// Common Mixers
		_MixerEntry(ThrottleAndBrake),
		_MixerEntry(Average),
		_MixerEntry(Difference),
		_MixerEntry(RangeIfButton),

		// Custom Mixers
		//_MixerEntry(my_awesome_mixer_s_name),

	};

	MixerMaker FindMixer(const std::string MixerName)
	{
		for (size_t i = 0; i < asize(MixerList); i++) {
			if (MixerList[i].name == MixerName) {
				return MixerList[i].generator;
			}
		}
		return nullptr;
	}

}
