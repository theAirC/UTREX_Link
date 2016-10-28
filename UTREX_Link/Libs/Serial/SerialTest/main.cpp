#include <iostream>

#include "../Serial.cpp"

#define ifdie(cond) if(cond) { cout << "[X] " << #cond << endl; exit(-1); }

using namespace std;

int main()
{
	cout << "Testing Serial - Connect TX with RX" << endl;

	auto a = Serial::Serial::List();

	if (a.size() > 0) {
		cout << a[0] << endl;

		Serial::Serial ms(a[0]);

		ms.Baudrate = 250000;
		ms.Databits = Serial::Databits_8;
		ms.Parity = Serial::Parity_None;
		ms.Stopbits = Serial::Stopbits_1;

		ifdie(!ms.Open());

		ms.setDTR(1);

		char msg[] = "Hello World";

		cout << "Bytes Written: " << ms.Write(msg, sizeof(msg)) << endl;
		cout << "Bytes Read: " << ms.Read(msg, sizeof(msg)) << endl;
		cout << msg << endl;
	}
	else {
		cout << "No COM Ports found !" << endl;
	}
}
