#include "ServiceCollection.h"

auto ServiceCollection::Build() -> Service<IServiceProvider> {
	auto provider = std::make_shared<ServiceProvider>();
	std::map<Service<IServiceBuilder>, Service<IServiceBuilder>> copyMap;

	for (auto it = builderMap.begin(); it != builderMap.end(); ++it) {
		for (const auto& f : it->second) {
			if (!copyMap.count(f))
				copyMap[f] = f->GetLifeCycle() == LifeCycle::Singleton ? f : f->Copy();

			provider->AddBuilder(it->first, copyMap[f]);
		}
	}

	return provider;
}
