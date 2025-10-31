cmake_minimum_required (VERSION 3.10)


if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(-O2 -Wall -Wextra -pedantic -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
add_compile_options(/O2 /W4 /WX)
endif()

if (CMAKE_HOST_WIN32)
	set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/yaml-cpp.lib) # For Windows
elseif(CMAKE_HOST_LINUX)
	set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/yaml-cpp.a) # For Linux
endif()

project ("maker")

include_directories(./include)
link_directories(lib)

add_executable (maker  maker.cpp "include/main.h" "include/print.h" "include/get.h" "include/execute.h" 
"include/get.cpp" "include/print.cpp" "include/execute.cpp")

target_compile_definitions(maker PUBLIC YAML_CPP_STATIC_DEFINE)

target_link_libraries(maker ${LIB_PATH})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET maker PROPERTY CXX_STANDARD 20)
endif()
