#include "StateMachine.h"

StateMachine::StateMachine()
{
	m_MemPool.emplace<Unarmed>();
}

FlightState StateMachine::Run(const SensorData& SD)
{
	return std::visit
	(
		[&](auto&& CurrentState)
	       {
	           return CurrentState.Run(SD, m_MemPool);
	       },
		   m_MemPool
   );
}