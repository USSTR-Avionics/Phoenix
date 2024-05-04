#include "StateMachine_t.h"

StateMachine_t::StateMachine_t()
{
	m_MemPool.emplace<Unarmed>();
}

FlightState StateMachine_t::Run()
{
	return std::visit
			(
                [&](auto&& CurrentState)
                {
                    return CurrentState.Run(m_MemPool);
                },
                m_MemPool
			);
}

FlightState StateMachine_t::GetState() const
{
	return std::visit
			(
                [&](const auto& CurrentState)
                {
                    return CurrentState.GetState();
                },
                m_MemPool
			);
}