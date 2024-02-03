project(ServiceProvider)

set(HEADERS
	inc/IService.h
	inc/IServiceBuilder.h
	inc/IServiceCollection.h
	inc/IServiceProvider.h
)

set(SOURCES
	src/IService.cpp
	src/IServiceBuilder.cpp
	src/IServiceCollection.cpp
	src/IServiceProvider.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

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