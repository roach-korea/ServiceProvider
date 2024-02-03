#pragma once

#include <typeinfo>

#include "IServiceBuilder.h"

class IServiceProvider : public virtual IService {
public:
	template <typename T>
	auto GetService() -> Service<T>;

	template <typename T>
	auto GetServiceList() -> ServiceList<T>;

protected:
	virtual auto GetBuilder(ServiceId id) -> IServiceBuilder* = 0;
	virtual auto GetBuilderList(ServiceId id) -> std::vector<IServiceBuilder*> = 0;
};

template <typename T>
auto IServiceProvider::GetService() -> Service<T> {
	if (auto* builder = GetBuilder(typeid(T).hash_code())) {
		if (auto service = std::dynamic_pointer_cast<T>(builder->ToService()))
			return service;
	}

	return nullptr;
}

template <typename T>
auto IServiceProvider::GetServiceList() -> ServiceList<T> {
	ServiceList<T> list;

	for (auto* builder : GetBuilderList(typeid(T).hash_code())) {
		if (auto service = std::dynamic_pointer_cast<T>(builder->ToService()))
			list.push_back(service);
	}

	return list;
}
