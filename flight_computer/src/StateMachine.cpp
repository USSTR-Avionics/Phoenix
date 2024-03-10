#include "StateMachine.h"

StateMachine::StateMachine() : m_CurrentState(static_cast<State*>(&m_MemPool.emplace<Unarmed>())){}

bool StateMachine::Ready()
{
	return m_CurrentState != nullptr;
}

void StateMachine::Run(const SensorData& SD)
{
	m_CurrentState = m_CurrentState->Run(SD, m_MemPool);
}