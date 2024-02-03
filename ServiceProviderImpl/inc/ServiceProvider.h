#pragma once

#include <map>
#include <vector>

#include "IServiceProvider.h"

class ServiceProvider final : public IServiceProvider {
	Implements(IServiceProvider)

public:
	auto AddBuilder(ServiceId id, const std::shared_ptr<IServiceBuilder>& builder) -> void;

protected:
	auto GetBuilder(ServiceId id) -> IServiceBuilder* override;
	auto GetBuilderList(ServiceId id) -> std::vector<IServiceBuilder*> override;

private:
	std::map<ServiceId, std::vector<std::shared_ptr<IServiceBuilder>>> builderMap;
};