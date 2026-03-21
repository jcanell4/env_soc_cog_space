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
├── include/           # Public API headers (documented below)
├── src/
│   └── main.cpp
└── .gitignore
```

## API overview

Public types live under `include/`. Headers use **Doxygen-style** comments (`@file`, `@class`, `@brief`, `@param`, `@return`) so you can generate HTML/LaTeX reference with [Doxygen](https://www.doxygen.nl/):

```bash
doxygen -g Doxyfile   # once: edit INPUT = include src, RECURSIVE = YES, etc.
doxygen Doxyfile
```

### Class summary

| Type | Header | Role |
|------|--------|------|
| **LivingBeing** | `LivingBeing.h` | Abstract species: name, energy per biomass, death & growth demand contracts. |
| **Autotroph** | `Autotroph.h` | Abstract producer: tolerances, resilience, environment sensitivity vs niche conditions. |
| **AutotrophByRates** | `AutotrophByRates.h` | Concrete autotroph with max growth rate, base death rate, tolerances; JSON constructor. |
| **Cohort** | `Cohort.h` | Population of one species: living/dead biomass, `update_biomass`, `calculate_growth_demand`. |
| **Niche** | `Niche.h` | Contains cohorts, nutrients, conditions; `step()` runs nutrient recycling and cohort updates. |
| **Constants** | `Constants.h` | `NUTRIENTS_POS` — channel code for nutrient-limited growth tuples. |

### Growth-demand tuple convention

`LivingBeing::calculate_growth_biomass` / `Cohort::calculate_growth_demand` return `std::vector<std::tuple<int,double>>`:

- **`NUTRIENTS_POS`** (`Constants.h`) — first int: demand competes for niche **nutrients** (autotroph path in `Niche::update_cohorts`).
- **Negative `code`** — decomposer: donor cohort index = `-(code + 1)`.
- **Non-negative `code`** (and not `NUTRIENTS_POS`) — heterotroph: prey cohort index = `code`.

### Simulation flow (niche)

1. **`Niche::update_nutrients`** — per cohort, move `return_rate × death_biomass` into `nutrients` and out of dead pool; then **`update_ecological_health`** with the nutrient delta.
2. **`Niche::update_cohorts`** — random starting index, for each cohort resolve growth demand tuples and update nutrients / biomass transfers.

## Licence

This project is licensed under the [MIT License](LICENSE).
