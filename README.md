# col_com_env

**Collective Communication Environment** – Projecte C++ multiplataforma (Linux, Windows, macOS).

## Requisits

- [CMake](https://cmake.org/) ≥ 3.14
- Compilador C++17 (GCC, Clang, MSVC)

## Compilació local

```bash
# Configurar i compilar
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Executar (Linux/macOS)
./build/col_com_env

# Windows: build\Release\col_com_env.exe
```

## CI/CD (GitHub Actions)

El workflow [`.github/workflows/build.yml`](.github/workflows/build.yml) compila el projecte a:

- **Linux** (ubuntu-latest)
- **Windows** (windows-latest)
- **macOS** (macos-latest)

S’executa en cada `push` i `pull_request` a les branques `main` i `master`. Els executables es publiquen com a *artifacts* de l’acció.

## Crear el repositori a GitHub

1. Crea un repositori nou a [github.com/new](https://github.com/new):
   - Nom: `col_com_env`
   - Propietari: **jcanell4**
   - Públic, sense inicialitzar amb README (ja en tens un al projecte)

2. Enllaça el projecte local i puja el codi:

```bash
cd /home/josep/Dropbox/projecteRicard/colletive_intelligence/implementation/language_c/col_com_env
git init
git add .
git commit -m "Initial commit: col_com_env C++ project with cross-platform build"
git branch -M main
git remote add origin https://github.com/jcanell4/col_com_env.git
git push -u origin main
```

3. A **Actions** del repositori veuràs el workflow “Build (Linux, Windows, macOS)”. Després de cada push es generaran els executables per a les tres plataformes.

## Estructura

```
col_com_env/
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
