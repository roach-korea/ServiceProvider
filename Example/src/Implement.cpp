#include "Implement.h"

#include <iostream>

auto TransientTest::SayHello() -> void {
	std::cout << "Hello, I'm Transient " << this << std::endl;
}

auto ScopedTest::SayHello() -> void {
	std::cout << "Hello, I'm Scoped " << this << std::endl;
}

auto SingletonTest::SayHello() -> void {
	std::cout << "Hello, I'm Singleton " << this << std::endl;
}
