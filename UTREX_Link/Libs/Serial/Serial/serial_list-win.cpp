#include <tchar.h>

namespace Serial {

	std::vector<char*> Serial::List()
	{
		std::vector<char*> me;

		HKEY key;
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS) return me;

		DWORD ValueNameLenMAX, ValueDataSizeMAX;
		if (RegQueryInfoKey(key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &ValueNameLenMAX, &ValueDataSizeMAX, NULL, NULL) != ERROR_SUCCESS) return me;

		TCHAR *ValueName = new TCHAR[ValueNameLenMAX + 1];
		TCHAR *ValueData = new TCHAR[ValueDataSizeMAX + 1];

		DWORD index = 0;
		DWORD ValueNameLen, ValueDataSize;
		while (1) {

			ValueNameLen = ValueNameLenMAX;
			ValueDataSize = ValueDataSizeMAX;
			if (RegEnumValue(key, index, ValueName, &ValueNameLen, NULL, NULL, (LPBYTE)ValueData, &ValueDataSize) != ERROR_SUCCESS) break;

			ValueData[ValueDataSize / sizeof(TCHAR)] = '\0';

			char *item = new char[ValueDataSize + 1];

			memcpy(item, ValueData, ValueDataSize + 1);

			me.push_back(item);

			index++;
		}

		delete[] ValueData;
		delete[] ValueName;
		RegCloseKey(key);

		return me;
	}

}
