#include "StateMachine.h"

StateMachine::StateMachine() : m_CurrentState(dynamic_cast<State*>(&m_MemPool.emplace<Unarmed>())){}

bool StateMachine::Ready()
{
	return m_CurrentState != nullptr;
}

void StateMachine::Run(SensorData& SD)
{
	m_CurrentState = m_CurrentState->Run(SD, m_MemPool);
	m_eCurrentState = m_CurrentState->GetState();
}