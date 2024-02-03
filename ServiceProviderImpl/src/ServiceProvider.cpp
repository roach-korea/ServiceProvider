#include "ServiceProvider.h"

auto ServiceProvider::AddBuilder(ServiceId id, const std::shared_ptr<IServiceBuilder>& builder) -> void {
	builder->SetProvider(this);
	builderMap[id].push_back(builder);
}

auto ServiceProvider::GetBuilder(ServiceId id) -> IServiceBuilder* {
	if (builderMap.count(id) && builderMap[id].size() > 0)
		return builderMap[id].front().get();

	return nullptr;
}

auto ServiceProvider::GetBuilderList(ServiceId id) -> std::vector<IServiceBuilder*> {
	if (builderMap.count(id)) {
		std::vector<IServiceBuilder*> list;

		for (const auto& f : builderMap[id])
			list.push_back(f.get());

		return list;
	}

	return {};
}
