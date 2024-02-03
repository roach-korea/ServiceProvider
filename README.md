# ServiceProvider
C++ Dependency Injection Model

This C++ Service Provider seamlessly integrates into your C++ projects, bringing the convenience of dependency injection to your development toolkit. It's intentionally designed to mirror the familiar C# Service Provider interface, ensuring a smooth transition for developers.

## IService
All interfaces intended for injection must inherit from the `IService` class, establishing a common ground for dependency management.

```c++
class IHelloworld : public virtual IService {
public:
  virtual void SayHi() = 0;
}
```

## Implements
C++ doesn't offer built-in inheritance confirmation, so implement classes must explicitly declare their inheritance using the `Implements` macro.

```c++
class ConsoleHelloworld : public IHelloworld {
  Implements(IHelloworld)

public:
  virtual void SayHi() override;
}
```

## Register Dependency
Register your dependencies with the `ServiceCollection` object, creating a blueprint for the provider.

``` c++
auto* collection = new ServiceCollection;

collection->AddTransient<ConsoleHelloworld>();
```

Build the ServiceProvider from the ServiceCollection.

``` c++
auto* provider = collection->Build();
```

provider retreives service or services.

``` c++
auto service = provider->GetService<IHelloworld>();
auto services = provider->GetServiceList<IHelloworld>();
```

## Instance Life Cycle
### Transient
Instances are created a new for each request, ensuring independence and isolation.

```c++
const auto helloworld1 = provider->GetService<IHelloworld>();
const auto helloworld2 = provider->GetService<IHelloworld>();

std::cout << helloworld1.get() << std::endl;
std::cout << helloworld2.get() << std::endl;
// helloworld1, helloworld2 are different instance.
```

### Scoped
Instances persist within a defined scope, promoting efficiency and consistency within a specific context.

```c++
{
  const auto helloworld1 = provider->GetService<IHelloworld>();
  const auto helloworld2 = provider->GetService<IHelloworld>();

  std::cout << helloworld1.get() << std::endl;
  std::cout << helloworld2.get() << std::endl;
}

{
  const auto helloworld3 = provider->GetService<IHelloworld>();

  std::cout << helloworld3.get() << std::endl;
}

// helloworld1, helloworld2 are same instance, but helloworld3 is different.
```

### Singleton
A single instance is created for the application's lifetime, guaranteeing global accessibility and shared state.

```c++
const auto helloworld = provider->GetService<IHelloworld>();

std::cout << helloworld.get() << std::endl;
// helloworld is always same instance from now on.
```

## Inject by Constructor
If implement class accepts IServiceProvider on constructor, this will be injected!

```c++
class MessageBoxHelloworld : public IHelloworld {
  Implements(IHelloworld)

public:
  MessageBoxHelloworld(IServiceProvider* provider);
}
```
