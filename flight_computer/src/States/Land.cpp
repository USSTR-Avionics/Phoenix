//
// Created by TDKua on 2023/10/22.
//
#include "StateMachine.h"

State* Land::Run(SensorData& SD, StateMemPool& MemPool)
{
	// always return self, no transition
	return dynamic_cast<State*>(&std::get<Land>(MemPool)); // equivalent : return this;
}