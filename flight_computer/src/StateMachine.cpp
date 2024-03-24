#include "StateMachine.h"

StateMachine::StateMachine(RA::Sensor&& Sensor, FRAM&& Fram) : m_Sensor{Sensor}, m_Fram{Fram}
{
	m_MemPool.emplace<Unarmed>();
}

FlightState StateMachine::Run()
{
    // if record data
    if(GetState() == FlightState::eInFlight || GetState() == FlightState::eMainChute)
    {
        m_Sensor.RecordSensorData();

        m_Fram.StoreData(m_Sensor.SetFlightState(GetState()));
    }
	return std::visit
			(
                [&](auto&& CurrentState)
                {
                    return CurrentState.Run(m_Sensor.GetData(), m_MemPool);
                },
                m_MemPool
			);
}

FlightState StateMachine::GetState() const
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