#pragma once

#include "IService.h"

class ITransientTest : public virtual IService {
public:
	virtual auto SayHello() -> void = 0;
};

class IScopedTest : public virtual IService {
public:
	virtual auto SayHello() -> void = 0;
};

class ISingletonTest : public virtual IService {
public:
	virtual auto SayHello() -> void = 0;
};