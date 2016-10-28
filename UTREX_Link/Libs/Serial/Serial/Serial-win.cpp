#include "Serial-win.h"
#include "..\Serial.h"

namespace Serial {

	using namespace std;

	inline void _prefix_port_if_needed(wstring &input)
	{
		wstring windows_com_port_prefix = L"\\\\.\\";
		if (input.compare(windows_com_port_prefix) != 0) input += windows_com_port_prefix;
	}

	bool Serial::Open()
	{
		// See: https://github.com/wjwwood/serial/issues/84
		wstring port_with_prefix((wchar_t *)PortName);
		_prefix_port_if_needed(port_with_prefix);
		LPCWSTR lp_port = port_with_prefix.c_str();
		Port.ptr = CreateFileW(lp_port,
			GENERIC_READ | GENERIC_WRITE,
			0,
			0,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0);

		if (Port.ptr == INVALID_HANDLE_VALUE) return false;

		DCB dcbSerialParams = { 0 };

		dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

		dcbSerialParams.BaudRate = Baudrate;
		dcbSerialParams.ByteSize = Databits;
		dcbSerialParams.StopBits = Stopbits;
		dcbSerialParams.Parity = Parity;

		// activate settings
		if (SetCommState(Port.ptr, &dcbSerialParams)) return true;
		else {
			CloseHandle(Port.ptr);
			return false;
		}
	}
	void Serial::Close()
	{
		CloseHandle(Port.ptr);
		Port.ptr = INVALID_HANDLE_VALUE;
	}

	size_t Serial::Write(const void *buffer, size_t size)
	{
		DWORD bytes_written;

		if (!WriteFile(Port.ptr, buffer, (DWORD)size, &bytes_written, NULL)) return 0;

		return (size_t)(bytes_written);
	}
	size_t Serial::Read(void *buffer, size_t size)
	{
		DWORD bytes_read;

		if (!ReadFile(Port.ptr, buffer, (DWORD)size, &bytes_read, NULL)) return 0;

		return (size_t)(bytes_read);
	}

	void Serial::FlushTX()
	{
		FlushFileBuffers(Port.ptr);
	}
	void Serial::FlushRX()
	{
		FlushFileBuffers(Port.ptr);
	}

	void Serial::setDTR(bool level)
	{
		if (level) {
			EscapeCommFunction(Port.ptr, SETDTR);
		}
		else {
			EscapeCommFunction(Port.ptr, CLRDTR);
		}
	}
	void Serial::setRTS(bool level)
	{
		if (level) {
			EscapeCommFunction(Port.ptr, SETRTS);
		}
		else {
			EscapeCommFunction(Port.ptr, CLRRTS);
		}
	}
	bool Serial::getDCD()
	{
		DWORD dwModemStatus;

		GetCommModemStatus(Port.ptr, &dwModemStatus);

		return (MS_RLSD_ON & dwModemStatus) != 0;
	}
	bool Serial::getDSR()
	{
		DWORD dwModemStatus;

		GetCommModemStatus(Port.ptr, &dwModemStatus);

		return (MS_DSR_ON & dwModemStatus) != 0;
	}
	bool Serial::getRI()
	{
		DWORD dwModemStatus;

		GetCommModemStatus(Port.ptr, &dwModemStatus);

		return (MS_RING_ON & dwModemStatus) != 0;
	}
	bool Serial::getCTS()
	{
		DWORD dwModemStatus;

		GetCommModemStatus(Port.ptr, &dwModemStatus);

		return (MS_CTS_ON & dwModemStatus) != 0;
	}

}
