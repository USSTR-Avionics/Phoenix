#include "StateMachine.h"

StateMachine::StateMachine(WDT_timings_t WD_Config) : m_CurrentState(dynamic_cast<State*>(&m_MemPool.emplace<Unarmed>()))
{
	WD_Config.callback = WD_CallBack;
	m_WatchDog.begin(WD_Config);
}

bool StateMachine::Ready()
{
	return m_CurrentState != nullptr;
}

void StateMachine::Run(SensorData& SD)
{
	m_WatchDog.feed();
	m_CurrentState = m_CurrentState->Run(SD, m_MemPool);
}

void StateMachine::WD_CallBack()
{
	// continue on or enter recovery mode?
}
