#include "States.h"

#include <Global.h>

FlightState Unarmed::Run(FlightStateMemPool& MemPool)
{
    //swichs states if recieved arming signal
    //TODO: be able to recieve arming signal
    if(Arm)
    {
        // transition to new state, will break SM if you create random obj
	   return MemPool.emplace<GroundIdle>().GetState();
    }

	// Get radio message
	auto Message{RA::Global::IO::Radio.UDP_Receive()};

	if(Message.MessageType == RA::RadioMessage::Type::string)
	{
		// Get message
		auto& S = std::get<std::string>(Message.Message);

		if(S == "Arm") { Arm = true; }
		else
		{ RA::Global::IO::Radio.ParseCmd(S); }
	}

	return GetState();
}

FlightState inline Unarmed::GetState() const
{
	return eUnarmed;
}