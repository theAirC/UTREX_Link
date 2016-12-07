
struct Serial
{
	static const u32 Baudrate = 38400;
	static const byte PreambleTX[2]; // 'Start' byte
	static const byte PreambleRX[2]; // 'Start' byte for the RX line
	static const byte bytesPerLineTX = 8;

	const size_t RX_ByteCount;

	std::vector<Output*> myOutputs;
	serial::Serial mySerial;

	Serial(const std::string &PortName, byte RX_ByteCount)
		: mySerial(PortName, Baudrate), RX_ByteCount(RX_ByteCount)
	{
		RX_Line = new Stack<byte>(RX_ByteCount);
		mySerial.setDTR(1);
	}

	void SendOutputs()
	{
		mySerial.write(PreambleTX, sizeof(PreambleTX));

		Stack<byte> BufferTX(256); // a large buffer to hold the data to send

		//printf("\n");
		// Then generate/read the outputs one-by-one and write to the buffer.
		for (size_t i = 0; i < Outputs.size(); i++) {
			u16 v = Outputs[i]->Get();
			//printf(" %05u", v);
			byte temp;

			temp = v >> 8; // MSB first
			BufferTX.Add(temp);
			if (temp == 0xBF) BufferTX.Add(~0); // escape byte

			temp = v & 0xFF;
			BufferTX.Add(temp);
			if (temp == 0xBF) BufferTX.Add(~0); // escape byte
		}

		// We may need to add padding, if the data in the buffer is not a multiple of bytesPerLineTX.
		BufferTX.Count = upperdiv(BufferTX.Count, bytesPerLineTX) * bytesPerLineTX;

		// Finally, send the buffer.
		mySerial.write(BufferTX.Data.Raw, BufferTX.Count);
	}

	Stack<byte> *RX_Line;
	bool RX_StartReceived = false;

	Stack<byte> *getTelem()
	{
		Stack<byte> *me = nullptr;

		size_t bytes_to_read = mySerial.available();
		Array<byte> buffer(bytes_to_read);
		size_t bytes_read = mySerial.read(buffer.Raw, bytes_to_read);

		for (size_t i = 0; i < bytes_read; i++) {

			if (RX_StartReceived) {
				RX_StartReceived = false;

				if (buffer[i] == PreambleRX[1]) RX_Line->Count = 0; // reset
				else RX_Line->Add(PreambleRX[0]);                   // StartByte is escaped
			}
			else {
				if (buffer[i] == PreambleRX[0]) RX_StartReceived = true; // potential reset
				else RX_Line->Add(buffer[i]);                            // actual byte
			}
			
			if (RX_Line->isFull()) {
				Stack<byte> *temp = (me != nullptr) ? me : new Stack<byte>(RX_ByteCount);
				me = RX_Line;
				RX_Line = temp;
			}
		}
		return me;
	}
};

const byte Serial::PreambleTX[] = { 0xBF, 0x00 };
const byte Serial::PreambleRX[] = { 0xBF, 0x00 };
