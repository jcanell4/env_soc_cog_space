/**
 * env_soc_cog_space - Environmental Social Cognitive Space
 * Cross-platform C++ entry point.
 */

#include <iostream>
#include <string>

#if defined(ENV_SOC_COG_SPACE_PLATFORM_LINUX)
const char* platform_name = "Linux";
#elif defined(ENV_SOC_COG_SPACE_PLATFORM_MACOS)
const char* platform_name = "macOS";
#elif defined(ENV_SOC_COG_SPACE_PLATFORM_WINDOWS)
const char* platform_name = "Windows";
#else
const char* platform_name = "Unknown";
#endif

int main(int argc, char* argv[]) {
    std::cout << "env_soc_cog_space v0.1.0 - Environmental Social Cognitive Space\n";
    std::cout << "Platform: " << platform_name << "\n";
    return 0;
}
