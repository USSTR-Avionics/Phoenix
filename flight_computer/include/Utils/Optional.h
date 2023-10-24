//
// Created by TDKua on 2023/10/22.
//

#ifndef FLIGHT_COMPUTER_OPTIONAL_H
#define FLIGHT_COMPUTER_OPTIONAL_H

#include <string>

template<typename T>
class Optional
{
public:
	constexpr Optional() = default;
	constexpr Optional(const T& V) : Value(V), Flag(true){};

	[[nodiscard]] bool HasValue() const { return Flag; }
	[[nodiscard]] T Get() const { return Value; }

	void operator=(const T& V)
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

	[[nodiscard]] bool HasValue() const { return Value != nullptr; }
	[[nodiscard]] const T* Get() const { return Value; }

	void operator = (const T& V) { Value = &V; }

	T& operator*() { return *Value; }
	T* operator->() { return Value; }

private:
	T* Value{nullptr};
};
#endif //FLIGHT_COMPUTER_OPTIONAL_H
