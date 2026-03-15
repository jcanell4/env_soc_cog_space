/**
 * col_com_env - Collective Communication Environment
 * Cross-platform C++ entry point.
 */

#include <iostream>
#include <string>

#if defined(COL_COM_ENV_PLATFORM_LINUX)
const char* platform_name = "Linux";
#elif defined(COL_COM_ENV_PLATFORM_MACOS)
const char* platform_name = "macOS";
#elif defined(COL_COM_ENV_PLATFORM_WINDOWS)
const char* platform_name = "Windows";
#else
const char* platform_name = "Unknown";
#endif

int main(int argc, char* argv[]) {
    std::cout << "col_com_env v0.1.0 - Collective Communication Environment\n";
    std::cout << "Platform: " << platform_name << "\n";
    return 0;
}
