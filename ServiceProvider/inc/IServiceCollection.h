#pragma once

#include "IServiceProvider.h"

class IServiceCollection : public virtual IService {
public:
	virtual auto Build() -> Service<IServiceProvider> = 0;
};
