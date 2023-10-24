#include "StateMachine.h"

StateMachine::StateMachine(State* State) : m_CurrentState(State){};

void StateMachine::Run(SensorData& SD)
{
	// break if you point to random obj
    if(m_CurrentState->Run(SD))
    {
        m_CurrentState = m_CurrentState->Transition();
    }
}
