cmake_minimum_required(VERSION 3.5)

project (ServiceProviderProject LANGUAGES CXX VERSION 0.1)

option (BUILD_EXAMPLES "Build the examples" ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(ServiceProvider)
add_subdirectory(ServiceProviderImpl)

if (BUILD_EXAMPLES)
	add_subdirectory(Example)
endif()