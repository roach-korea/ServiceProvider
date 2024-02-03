project(Examples)

set(HEADERS
	inc/Interface.h
	inc/Implement.h
)

set(SOURCES
	src/Interface.cpp
	src/Implement.cpp
	src/main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		ServiceProviderImpl
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