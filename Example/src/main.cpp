#include "ServiceCollection.h"

#include "Implement.h"

int main(int argc, char** argv) {
	const auto col = std::make_shared<ServiceCollection>();

	col->AddScoped<ScopedTest>()
			->AddTransient<TransientTest>()
			->AddSingleton<SingletonTest>();

	const auto provider = col->Build();

	{
		const auto transient1 = provider->GetService<ITransientTest>();
		const auto transient2 = provider->GetService<ITransientTest>();
		transient1->SayHello();
		transient2->SayHello();
	}

	{
		const auto scoped1 = provider->GetService<IScopedTest>();
		const auto scoped2 = provider->GetService<IScopedTest>();
		scoped1->SayHello();
		scoped2->SayHello();
	}

	{
		const auto scoped3 = provider->GetService<IScopedTest>();
		const auto scoped4 = provider->GetService<IScopedTest>();
		scoped3->SayHello();
		scoped4->SayHello();
	}

	{
		const auto singleton = provider->GetService<ISingletonTest>();
		singleton->SayHello();
	}

	{
		const auto singleton = provider->GetService<ISingletonTest>();
		singleton->SayHello();
	}
}
