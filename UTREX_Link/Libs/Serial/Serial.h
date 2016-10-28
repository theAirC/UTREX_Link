#pragma once

#include "../Naming.h"
#include <vector>

namespace Serial {

	struct Serial
	{
		const char *const PortName;

		u32           Baudrate = 250000;
		Databits_t    Databits = Databits_8;
		Parity_t      Parity = Parity_None;
		Stopbits_t    Stopbits = Stopbits_1;

		union
		{
			size_t id;
			void *ptr;
		} Port; // OS Implementation dependent

		Serial(const char *const PortName) : PortName(PortName) {}
		~Serial() { Close(); }

		static std::vector<char*> List();

		bool Open();
		void Close();

		size_t Write(const void *buffer, size_t size);
		size_t Read(void *buffer, size_t size);

		void FlushTX();
		void FlushRX();

		void setDTR(bool level);
		void setRTS(bool level);
		bool getDCD();
		bool getDSR();
		bool getRI();
		bool getCTS();
	};

}
