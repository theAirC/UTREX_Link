#pragma once

typedef s32 Delta_t;  // Relative values, like mouse movement or trackball change.
typedef u16 Range_t;  // Absolute values, like throttles sticks, knobs and joysticks.
typedef u8  State_t;  // Distinct state values, like multi-position switches and D-pads.
typedef u8  Button_t; // Simple buttons, 1 or 0
// typedef bits Buttons_t

const Delta_t  Delta_Center = 0;
const Range_t  Range_Center = 32 * 1024 - 1;
const State_t  State_Center = 0;
const Button_t Button_Center = 0;
//Buttons_t Buttons_Center(1);

// The following Mixer values are used internally,
// the information is spread across the full 16-bit range.
const u16 Mixer_Center = 32 * 1024 - 1; // Mixer center/half value
const u16 Mixer_Min    = 0;             // Mixer Minimum value
const u16 Mixer_Max    = 64 * 1024 - 1; // Mixer Maximum value
