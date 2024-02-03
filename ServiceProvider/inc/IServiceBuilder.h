#pragma once

#include <memory>

#include "IService.h"

class IServiceProvider;
using ServiceId = decltype(typeid(void).hash_code());

enum class LifeCycle {
	Singleton,
	Scoped,
	Transient
};

class IServiceBuilder : public virtual IService {
public:
	virtual auto SetProvider(IServiceProvider* provider) -> void = 0;
	virtual auto Copy() -> Service<IServiceBuilder> = 0;

	virtual auto GetLifeCycle() const -> LifeCycle = 0;
	virtual auto GetServiceId() const -> ServiceId = 0;
	virtual auto ToService() -> Service<IService> = 0;
};
