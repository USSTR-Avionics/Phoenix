#include "StateMachine.h"

StateMachine::StateMachine(State* State) : m_CurrentState(State){}

void StateMachine::Run(SensorData& SD)
{
	// Land return nullptr
    if(m_CurrentState->Run(SD) == nullptr){ exit(1); }
}
