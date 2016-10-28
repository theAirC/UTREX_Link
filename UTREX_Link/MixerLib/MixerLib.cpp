// This file #includes multiple other files with Mixer classes inside them.
// You can write your own Mixer in another file and #include it here.
// Don't forget to add your Mixer to the MixerList (down below) as well.

#include "DirectMixers.cpp"
#include "CommonMixers.cpp"

#include "CustomMixers.cpp" // Add your own mixers to this file

// Register your Mixer here, like the examples.
const MixerMaker MixerList[] = {

// Direct Mixers
    MakeMixer< Mixer_DirectDelta >,
    MakeMixer< Mixer_DirectRange >,
    MakeMixer< Mixer_DPadStateY >,
    MakeMixer< Mixer_DPadStateX >,
    MakeMixer< Mixer_DirectButton >,

// Common Mixers
    MakeMixer< Mixer_ThrottleAndBrake >,
    MakeMixer< Mixer_Average >,
    MakeMixer< Mixer_Difference >,
    MakeMixer< Mixer_RangeIfButton >,

// Custom Mixers

};
