// Unity Build file
// Build this and only this file.
// The whole project becomes a Single Compilation Unit (SCU).
// This simplifies the compilation process and results in better optimization.
// Note:
//  The order of #include statements is important.
//  No other file may be built, or there will be multiple definition errors during linking.

#include <stddef.h>
#include <stdio.h>
#include <cstdlib>

#include <SDL.h>

#include "Libs/Naming.h"
#include "Libs/Math/SimpleMath.h"
#include "Libs/Generic/Array.cpp"
#include "Libs/Generic/Bits.cpp"
#include <vector>

#include "Error.c"

#include "ValueRanges.h"

#include "Core/Canonical.h"
#include "Core/InputDevice.cpp"
#include "Core/Mixer.cpp"
#include "MixerLib/MixerLib.cpp"
#include "Core/Curve.cpp"
#include "Core/Output.cpp"

#include "Core/Memory.cpp"

#include "../../serial/src/serial/serial.h"

#include "main.cpp"
