#pragma once

#include "IServiceCollection.h"

#include "ServiceBuilder.h"
#include "ServiceProvider.h"

class ServiceCollection final : public IServiceCollection {
	Implements(IServiceCollection)

public:
	auto Build() -> Service<IServiceProvider> override;

	template <typename T,
			std::enable_if_t<std::is_base_of_v<IService, T>, bool>  = true,
			std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>  = true>
	auto AddSingleton() -> ServiceCollection*;

	template <typename T,
			std::enable_if_t<std::is_base_of_v<IService, T>, bool>  = true,
			std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>  = true>
	auto AddScoped() -> ServiceCollection*;

	template <typename T,
			std::enable_if_t<std::is_base_of_v<IService, T>, bool>  = true,
			std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>  = true>
	auto AddTransient() -> ServiceCollection*;

	template <typename T,
			std::enable_if_t<std::is_base_of_v<IService, T>, bool>  = true,
			std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>  = true>
	auto AddSingleton(T* instance) -> ServiceCollection*;

	template <typename T,
			std::enable_if_t<std::is_base_of_v<IService, T>, bool>  = true,
			std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>  = true>
	auto AddScoped(T* instance) -> ServiceCollection*;

	template <typename T, typename K>
	auto ContainsService() const -> bool;

protected:
	template <typename T>
	auto AddBuilder(const std::shared_ptr<ServiceBuilder<T>>& builder) -> void;

private:
	std::map<ServiceId, std::vector<std::shared_ptr<IServiceBuilder>>> builderMap;
};

template <typename T,
		std::enable_if_t<std::is_base_of_v<IService, T>, bool>,
		std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>>
auto ServiceCollection::AddSingleton() -> ServiceCollection* {
	AddBuilder(std::make_shared<ServiceBuilder<T>>(LifeCycle::Singleton));
	return this;
}

template <typename T,
		std::enable_if_t<std::is_base_of_v<IService, T>, bool>,
		std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>>
auto ServiceCollection::AddScoped() -> ServiceCollection* {
	AddBuilder(std::make_shared<ServiceBuilder<T>>(LifeCycle::Scoped));
	return this;
}

template <typename T,
		std::enable_if_t<std::is_base_of_v<IService, T>, bool>,
		std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>>
auto ServiceCollection::AddTransient() -> ServiceCollection* {
	AddBuilder(std::make_shared<ServiceBuilder<T>>(LifeCycle::Transient));
	return this;
}

template <typename T, std::enable_if_t<std::is_base_of_v<IService, T>, bool>, std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>>
auto ServiceCollection::AddSingleton(T* instance) -> ServiceCollection* {
	AddBuilder(std::make_shared<ServiceBuilder<T>>(instance, LifeCycle::Singleton));
	return this;
}

template <typename T, std::enable_if_t<std::is_base_of_v<IService, T>, bool>, std::enable_if_t<IsTuple<typename T::ServiceParent>::value, bool>>
auto ServiceCollection::AddScoped(T* instance) -> ServiceCollection* {
	AddBuilder(std::make_shared<ServiceBuilder<T>>(instance, LifeCycle::Scoped));
	return this;
}

template <typename Impl, typename Base>
auto ServiceCollection::ContainsService() const -> bool {
	const auto implId = typeid(Impl).hash_code();
	const auto baseId = typeid(Base).hash_code();
	const auto pos = builderMap.find(baseId);

	if (pos == builderMap.end())
		return false;

	for (const auto& f : pos->second) {
		if (f->GetServiceId() == implId)
			return true;
	}

	return false;
}

template <typename T>
auto ServiceCollection::AddBuilder(const std::shared_ptr<ServiceBuilder<T>>& builder) -> void {
	if (!ContainsService<T, T>())
		builderMap[typeid(T).hash_code()].push_back(builder);

	ConstexprFor<std::tuple_size_v<typename T::ServiceParent>>([&] (auto index) {
		if (!ContainsService<T, std::tuple_element_t<index, typename T::ServiceParent>>())
			builderMap[typeid(std::tuple_element_t<index, typename T::ServiceParent>).hash_code()].push_back(builder);
	});
}
