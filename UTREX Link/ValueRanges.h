#pragma once

// The following Mixer values are used internally,
// the information is spread across the full 16-bit range.
const u16 Mixer_Center = 32 * 1024; // Mixer center/half value
const u16 Mixer_Min    = 0;             // Mixer Minimum value
const u16 Mixer_Max    = 64 * 1024 - 1; // Mixer Maximum value


// The following RC values are used in the last stage of the outputs.
// We need to hold 4ms pulse information in the 16-bit range.
// So, 0 means 0ms and 64*1024 means 4ms
const u16 RC_Center = 24 * 1024; // Center pulse lasts 1.5ms
const u16 RC_Min    = 16 * 1024; // Minimum pulse lasts 1ms
const u16 RC_Max    = 32 * 1024; // Maximum pulse lasts 2ms

const u16 RC_EMin   =  8 * 1024; // Minimum Extended pulse lasts 0.5ms
const u16 RC_EMax   = 40 * 1024; // Maximum Extended pulse lasts 2.5ms
