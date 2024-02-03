#pragma once

#include "IServiceBuilder.h"
#include "IServiceProvider.h"

#include "ServiceMetatemplate.h"

template <typename T>
class ServiceBuilder final : public IServiceBuilder {
	Implements(IServiceBuilder)

public:
	explicit ServiceBuilder(LifeCycle cycle);
	explicit ServiceBuilder(IService* instance, LifeCycle cycle);

	auto SetProvider(IServiceProvider* provider) -> void override;
	auto Copy() -> Service<IServiceBuilder> override;

	auto GetServiceId() const -> ServiceId override;
	auto GetLifeCycle() const -> LifeCycle override;
	auto ToService() -> Service<IService> override;

protected:
	auto CreateInstance() -> T*;

private:
	IService* instance = nullptr;

	IServiceProvider* provider = nullptr;
	LifeCycle cycle;
	int ref = 0;
};

template <typename T>
ServiceBuilder<T>::ServiceBuilder(LifeCycle cycle) : cycle(cycle) {}

template <typename T>
ServiceBuilder<T>::ServiceBuilder(IService* instance, LifeCycle cycle) : instance(instance), cycle(cycle) {}

template <typename T>
auto ServiceBuilder<T>::SetProvider(IServiceProvider* provider) -> void {
	this->provider = provider;
}

template <typename T>
auto ServiceBuilder<T>::Copy() -> Service<IServiceBuilder> {
	return std::make_shared<ServiceBuilder>(instance, cycle);
}

template <typename T>
auto ServiceBuilder<T>::GetServiceId() const -> ServiceId {
	return typeid(T).hash_code();
}

template <typename T>
auto ServiceBuilder<T>::GetLifeCycle() const -> LifeCycle {
	return cycle;
}

template <typename T>
auto ServiceBuilder<T>::ToService() -> Service<IService> {
	switch (cycle) {
		case LifeCycle::Transient:
			return std::shared_ptr<T>(CreateInstance());
		default:
			if (!instance)
				instance = CreateInstance();

			switch (cycle) {
				case LifeCycle::Singleton:
					return std::shared_ptr<T>(dynamic_cast<T*>(instance), SingletonDeleter());
				case LifeCycle::Scoped:
					return std::shared_ptr<T>(dynamic_cast<T*>(instance), ScopedDeleter(instance, ref));
				default:
					return {};
			}
	}
}

template <typename T>
auto ServiceBuilder<T>::CreateInstance() -> T* {
	if constexpr (IsRequirementDefined<T>()) {
		static_assert(IsNewConstructible<T, typename T::ServiceRequirement>(), "No proper constructor found while \'Requires\' had been requested!");

		auto args = typename T::ServiceRequirement();

		ConstexprFor < std::tuple_size_v<typename T::ServiceRequirementType> > ([this, &args] (auto index) {
			std::get<index>(args) = provider->GetService<std::tuple_element_t<index, typename T::ServiceRequirementType>>();
		});

		return NewFromTuple<T, decltype(args)>(std::move(args));
	} else if constexpr (std::is_constructible_v<T, IServiceProvider*>) {
		return new T(provider);
	} else if constexpr (std::is_default_constructible_v<T>)
		return new T;

	return {};
}
