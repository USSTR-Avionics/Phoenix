#include "StateMachine.h"

StateMachine::StateMachine() : m_CurrentState(dynamic_cast<State*>(&MemPool.emplace<Unarmed>())){}

void StateMachine::Run(SensorData& SD)
{
	m_CurrentState = m_CurrentState->Run(SD, MemPool);
}
