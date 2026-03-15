cmake_minimum_required(VERSION 3.14)
project(col_com_env VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform-specific settings
if(WIN32)
    add_definitions(-DCOL_COM_ENV_PLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DCOL_COM_ENV_PLATFORM_MACOS)
elseif(UNIX)
    add_definitions(-DCOL_COM_ENV_PLATFORM_LINUX)
endif()

add_executable(col_com_env
    src/main.cpp
)

target_include_directories(col_com_env PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optional: install target
install(TARGETS col_com_env RUNTIME DESTINATION bin)
