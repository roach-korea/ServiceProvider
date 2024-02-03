project(ServiceProviderImpl)

set(HEADERS
	inc/ServiceCollection.h
	inc/ServiceBuilder.h
	inc/ServiceMetatemplate.h
	inc/ServiceProvider.h
)

set(SOURCES
	src/ServiceCollection.cpp
	src/ServiceBuilder.cpp
	src/ServiceProvider.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		ServiceProvider
)

target_compile_features(${PROJECT_NAME} 
	PUBLIC 
		cxx_std_17
)

target_compile_options(${PROJECT_NAME}
	PUBLIC
		/wd4251
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
		$<INSTALL_INTERFACE:inc>

	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

install(FILES ${HEADERS}
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
	COMPONENT headers
)