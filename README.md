# ServiceProvider
C++ Dependency Injection Model

This C++ Service Provider project is designed to be as compatible as possible with the C# Service Provider interface, making it easy to use.

## IService
C++ doesn't have the grand superclass, so every interfaces to be injected should inherit **IService** class.

```c++
class IHelloworld : public virtual IService {
public:
  virtual void SayHi() = 0;
}
```

## Implements
C++ doesn't provider function to confirm inheritance, so every implement class should declare **Implements({InterfaceClass})**.

```c++
class ConsoleHelloworld : public IHelloworld {
  Implements(IHelloworld)

public:
  virtual void SayHi() override;
}
```

## Register Dependency
You can register dependencies with ServiceCollection.

``` c++
auto* collection = new ServiceCollection;

collection->AddTransient<ConsoleHelloworld>();
```

and then, build provider from collection.

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
Instance will be created on every request.

```c++
const auto helloworld1 = provider->GetService<IHelloworld>();
const auto helloworld2 = provider->GetService<IHelloworld>();

std::cout << helloworld1.get() << std::endl;
std::cout << helloworld2.get() << std::endl;
// helloworld1, helloworld2 are different instance.
```

### Scoped
Instance will be created if requested instance in advanced is not deleted.

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
Instance will be created on first request.

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
