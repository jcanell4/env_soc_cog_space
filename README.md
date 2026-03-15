# env_soc_cog_space

**Environmental Social Cognitive Space** – Projecte C++ multiplataforma (Linux, Windows, macOS).

## Requisits

- [CMake](https://cmake.org/) ≥ 3.14
- Compilador C++17 (GCC, Clang, MSVC)

## Compilació local

```bash
# Configurar i compilar
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Executar (Linux/macOS)
./build/env_soc_cog_space

# Windows: build\Release\env_soc_cog_space.exe
```

## CI/CD (GitHub Actions)

El workflow [`.github/workflows/build.yml`](.github/workflows/build.yml) compila el projecte a:

- **Linux** (ubuntu-latest)
- **Windows** (windows-latest)
- **macOS** (macos-latest)

S’executa en cada `push` i `pull_request` a les branques `main` i `master`. Els executables es publiquen com a *artifacts* de l’acció.

## Crear el repositori a GitHub

1. Crea un repositori nou a [github.com/new](https://github.com/new):
   - Nom: `env_soc_cog_space`
   - Propietari: **jcanell4**
   - Públic, sense inicialitzar amb README (ja en tens un al projecte)

2. Enllaça el projecte local i puja el codi:

```bash
cd /home/josep/Dropbox/projecteRicard/colletive_intelligence/implementation/language_c/env_soc_cog_space
git init
git add .
git commit -m "Initial commit: env_soc_cog_space C++ project with cross-platform build"
git branch -M main
git remote add origin https://github.com/jcanell4/env_soc_cog_space.git
git push -u origin main
```

3. A **Actions** del repositori veuràs el workflow “Build (Linux, Windows, macOS)”. Després de cada push es generaran els executables per a les tres plataformes.

## Estructura

```
env_soc_cog_space/
├── CMakeLists.txt
├── README.md
├── .github/workflows/
│   └── build.yml      # CI: Linux, Windows, macOS
├── include/           # Capçaleres
├── src/
│   └── main.cpp
└── .gitignore
```

## Llicència

A definir.
