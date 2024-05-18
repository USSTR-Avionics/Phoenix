#include "Radio.h"
#include "Functions.h"

RA::Radio Radio{0, 0};
void setup()
{
	
}

void loop()
{
	auto Message = Radio.UDP_Receive();
	if(Message.MessageType == RA::RadioMessage::Type::UnDefined) { return; }
	else if(Message.MessageType == RA::RadioMessage::Type::SensorChunk)
	{
		Serial.println(RA::to_string(std::get<SensorChunk>(Message.Message)).c_str());
	}
	else
	{
		Serial.println(std::get<std::string>(Message.Message).c_str());
	}
	
}
