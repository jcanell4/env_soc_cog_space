cmake_minimum_required(VERSION 3.14)
project(env_soc_cog_space VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform-specific settings
if(WIN32)
    add_definitions(-DENV_SOC_COG_SPACE_PLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DENV_SOC_COG_SPACE_PLATFORM_MACOS)
elseif(UNIX)
    add_definitions(-DENV_SOC_COG_SPACE_PLATFORM_LINUX)
endif()

add_executable(env_soc_cog_space
    src/main.cpp
)

target_include_directories(env_soc_cog_space PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Optional: install target
install(TARGETS env_soc_cog_space RUNTIME DESTINATION bin)
