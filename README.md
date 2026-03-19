# env_soc_cog_space

**Environmental Social Cognitive Space** – Cross-platform C++ project (Linux, Windows, macOS).

## Requirements

- [CMake](https://cmake.org/) ≥ 3.14
- C++17 compiler (GCC, Clang, MSVC)

## Local build

```bash
# Configure and build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Run (Linux/macOS)
./build/env_soc_cog_space

# Windows: build\Release\env_soc_cog_space.exe
```

## CI/CD (GitHub Actions)

The workflow [`.github/workflows/build.yml`](.github/workflows/build.yml) builds the project on:

- **Linux** (ubuntu-latest)
- **Windows** (windows-latest)
- **macOS** (macos-latest)

It runs on every `push` and `pull_request` to the `main` and `master` branches. Executables are published as workflow *artifacts*.

## Creating the repository on GitHub

1. Create a new repository at [github.com/new](https://github.com/new):
   - Name: `env_soc_cog_space`
   - Owner: **jcanell4**
   - Public, do not initialize with a README (you already have one in the project)

2. Link the local project and push the code:

```bash
cd /home/josep/Dropbox/projecteRicard/colletive_intelligence/implementation/language_c/env_soc_cog_space
git init
git add .
git commit -m "Initial commit: env_soc_cog_space C++ project with cross-platform build"
git branch -M main
git remote add origin https://github.com/jcanell4/env_soc_cog_space.git
git push -u origin main
```

3. Under **Actions** in the repository you will see the "Build (Linux, Windows, macOS)" workflow. After each push, executables for all three platforms will be generated.

## Structure

```
env_soc_cog_space/
├── CMakeLists.txt
├── LICENSE            # MIT License
├── README.md
├── .github/workflows/
│   └── build.yml      # CI: Linux, Windows, macOS
├── include/           # Headers
├── src/
│   └── main.cpp
└── .gitignore
```

## Licence

This project is licensed under the [MIT License](LICENSE).
