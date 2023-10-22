//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_OPTIONAL_H
#define FLIGHT_COMPUTER_OPTIONAL_H

#include <string>

constexpr int32_t NULL_VAL{-128};

template<typename T>
class Optional
{
public:
	constexpr Optional() = default;
	constexpr Optional(const T& V) : Value(V), Flag(true){};

	bool HasValue() const { return Flag; }
	[[nodiscard]] T Get() const { return Flag ? Value : static_cast<T>(NULL_VAL); }

	void operator = (const T& V)
	{
		Value = V;
		Flag = true;
	}

private:
	T Value{};
	bool Flag{false};
};

template<>
std::string Optional<std::string>::Get() const
{
	return Flag ? Value : "";
}

template<typename T>
class Optional<T*>
{
public:
	constexpr Optional() = default;
	constexpr Optional(T* V) : Value(V){};

	bool HasValue() const { return Value != nullptr; }
	[[nodiscard]] const T* Get() const { return Value; }

	void operator = (const T& V) { Value = &V; }

	const T operator*() const{ return *Value; }

private:
	T* Value{nullptr};
};
#endif //FLIGHT_COMPUTER_OPTIONAL_H
