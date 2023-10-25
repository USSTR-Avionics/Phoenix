#include "StateMachine.h"

StateMachine::StateMachine(State* State) : m_CurrentState(State){}

void StateMachine::Run(SensorData& SD)
{
	m_CurrentState = m_CurrentState->Run(SD);
	// Land return nullptr
    if(m_CurrentState == nullptr){ exit(1); }
}
