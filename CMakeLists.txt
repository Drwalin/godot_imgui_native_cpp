cmake_minimum_required(VERSION 3.19)
project(godot_imgui_native)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(godot-cpp)

include_directories(imgui)
include_directories(include)
include_directories(godot-cpp/include)
include_directories(godot-cpp/gen/include)

# Library compilation

aux_source_directory(./include/godot_imgui_native godot_imgui_native_include)
aux_source_directory(./src/ godot_imgui_native_src)
aux_source_directory(./imgui/ imgui)
add_library(godot_imgui_native SHARED
	${godot_imgui_native_include}
	${godot_imgui_native_src}
	${imgui}
)
target_link_libraries(godot_imgui_native PUBLIC godot::cpp)

add_custom_command(TARGET godot_imgui_native POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:godot_imgui_native>
	${PROJECT_SOURCE_DIR}/example/bin/libgodot_imgui_native.so
	COMMENT "dummy"
)
