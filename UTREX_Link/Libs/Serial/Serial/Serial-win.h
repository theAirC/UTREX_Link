#pragma once

#include <Windows.h>

namespace Serial {

	typedef enum
	{
		Databits_4 = 4,
		Databits_5 = 5,
		Databits_6 = 6,
		Databits_7 = 7,
		Databits_8 = 8,
	} Databits_t;

	typedef enum
	{
		Parity_None = NOPARITY,
		Parity_Odd = ODDPARITY,
		Parity_Even = EVENPARITY,
		Parity_Mark = MARKPARITY,
		Parity_Space = SPACEPARITY,
	} Parity_t;

	typedef enum
	{
		Stopbits_1 = ONESTOPBIT,
		Stopbits_1_5 = ONE5STOPBITS,
		Stopbits_2 = TWOSTOPBITS,
	} Stopbits_t;

}
