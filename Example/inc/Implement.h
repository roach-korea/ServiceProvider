#pragma once

#include "Interface.h"

class TransientTest final : public ITransientTest {
	Implements(ITransientTest)

public:
	auto SayHello() -> void override;
};

class ScopedTest final : public IScopedTest {
	Implements(IScopedTest)

public:
	auto SayHello() -> void override;
};

class SingletonTest final : public ISingletonTest {
	Implements(ISingletonTest)

public:
	auto SayHello() -> void override;
};