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

#include "../../Libs/Libs/Naming.h"
#include "../../Libs/Libs/Math/SimpleMath.h"
#include "../../Libs/Libs/Generic/Array.cpp"
//#include "../../Libs/Libs/Generic/Bits.cpp"
#include "../../Libs/Libs/Generic/Stack.cpp"
#include <vector>

#include "Error.c"

#include "Core/Types.h"
#include "Core/InputDevice.cpp"
#include "Core/Mixer.cpp"
#include "MixerLib/MixerLib.cpp"
#include "Core/Curve.cpp"
#include "Core/Output.cpp"

#include "Core/Memory.cpp"

#include "../../serial/src/serial/serial.h"
#include "Serial.cpp"

#include "../../json/src/json.hpp"
using JSON = nlohmann::json;

#include "Config.cpp"

#include "main.cpp"
