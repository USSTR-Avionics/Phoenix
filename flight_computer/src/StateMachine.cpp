#include "StateMachine.h"

StateMachine::StateMachine() { m_MemPool.emplace<Unarmed>(); }

FlightState StateMachine::Run()
{
    return std::visit([&](auto&& CurrentState) { return CurrentState.Run(m_MemPool); }, m_MemPool);
}

FlightState StateMachine::GetState() const
{
    return std::visit([&](const auto& CurrentState) { return CurrentState.GetState(); }, m_MemPool);
}
