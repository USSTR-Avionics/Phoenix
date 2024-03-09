#pragma once
#include <variant>
#include <cstdint>
class SensorData;

typedef std::variant<
	class Unarmed,
	class GroundIdle,
    class InFlight,
	class MainChute
    > StateMemPool;

enum FlightState : uint8_t
{
    eUnarmed,
    eGroundIdle,
    eInFlight,
    eMainChute
};