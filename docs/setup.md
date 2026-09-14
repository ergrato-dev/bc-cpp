# 🛠️ Setup del entorno

Plataforma primaria: **Linux o WSL2** (Ubuntu 24.04 o Debian 12). macOS y Windows/MSVC
funcionan, pero los ejemplos con `perf`, `epoll`, `fork` y `mmap` (semanas 15-17) son
Linux; en macOS se anotan las diferencias y en Windows se recomienda WSL2.

Mínimos según [`politica-versiones.md`](politica-versiones.md): **CMake 3.28, GCC 13 o
Clang 17**.

## 1. Ubuntu 24.04 / Debian 12

```bash
sudo apt update
sudo apt install -y build-essential g++-13 clang-17 clang-format-17 clang-tidy-17 \
                    lldb-17 gdb cmake ninja-build git pkg-config
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100
sudo update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-17 100
sudo update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-17 100
sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-17 100
```

Ubuntu 24.04 trae GCC 13 y CMake 3.28 en sus repositorios. Si `apt` te da algo más
viejo, mira la sección 2.

## 2. Ubuntu 22.04 (GCC 11, CMake 3.22: insuficientes)

GCC 11 no tiene `<format>` ni `<ranges>` completos. Dos salidas:

**a) PPA de toolchain + CMake de Kitware** (recomendado):

```bash
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt update && sudo apt install -y g++-13
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100

# CMake reciente desde el repo oficial de Kitware
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null \
  | gpg --dearmor - | sudo tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null
echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' \
  | sudo tee /etc/apt/sources.list.d/kitware.list >/dev/null
sudo apt update && sudo apt install -y cmake ninja-build
```

**b) Clang 17+ desde apt.llvm.org**:

```bash
wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && sudo ./llvm.sh 17
sudo apt install -y libc++-17-dev libc++abi-17-dev
```

Con Clang en 22.04 sigues necesitando una libstdc++ moderna (`libstdc++-13-dev` del
PPA) o usar `-stdlib=libc++`.

## 3. macOS

```bash
xcode-select --install
brew install cmake ninja llvm gcc@13
```

Apple Clang va por detrás de LLVM en soporte de C++20. Usa el `clang++` de Homebrew
(`/opt/homebrew/opt/llvm/bin/clang++`) exportando `CXX`. No hay ASan/UBSan
diferencias relevantes; **TSan y `perf` no**: `perf` no existe en macOS, usa
`Instruments`. Las semanas 16-17 usan `kqueue` donde Linux usa `epoll`; el texto lo
anota.

## 4. Windows

Usa **WSL2** con Ubuntu 24.04 y sigue la sección 1. MSVC 19.3x soporta C++20 bien,
pero el material de sanitizers, `perf`, POSIX y `epoll` no aplica. Si insistes en MSVC,
los starters compilan con `cmake --preset debug` cambiando el generador a
`"Visual Studio 17 2022"`, y los flags `-Wall -Wextra -Wpedantic -Werror` hay que
mapearlos a `/W4 /WX`; no está soportado oficialmente.

## 5. Verificar la instalación

```bash
g++ --version        # >= 13
clang++ --version    # >= 17
cmake --version      # >= 3.28
ninja --version
gdb --version | head -1
```

Y compila el primer starter del bootcamp:

```bash
cd bootcamp/week-01-toolchain_y_compilacion/2-practicas/ejercicio-01-hola-toolchain/starter
cmake --preset debug && cmake --build --preset debug && ctest --preset debug
```

Si `cmake --preset debug` falla por no encontrar Ninja, instálalo o edita el
`generator` en `CMakePresets.json` a `"Unix Makefiles"`.

## 6. Editor

Cualquiera con soporte de `compile_commands.json` (lo generan todos los presets):

- **VS Code**: extensiones `ms-vscode.cpptools` o `llvm-vs-code-extensions.vscode-clangd`,
  más `ms-vscode.cmake-tools`. El repo trae `.vscode/settings.json` con el color del
  bootcamp y `.vscode/extensions.json` con las recomendaciones.
- **CLion**, **Neovim + clangd**, **Emacs + eglot**: abren el `CMakeLists.txt` y listo.

## 7. Herramientas por semana (se instalan cuando toca)

| Semana | Herramienta | Instalación |
| ------ | ----------- | ----------- |
| 03 | `gdb` con pretty printers | Viene con `gdb` ≥ 12 en Ubuntu 24.04 |
| 13-14 | TSan | Incluido en GCC/Clang; preset `tsan` |
| 15 | `perf`, `valgrind` | `sudo apt install linux-tools-common linux-tools-$(uname -r) valgrind` (en WSL2, `linux-tools-generic`) |
| 15 | Google Benchmark | `FetchContent`, nada que instalar |
| 17 | Asio | `FetchContent`, nada que instalar |
| 18 | libFuzzer | Incluido en Clang: `-fsanitize=fuzzer` |
| 19 | Doxygen | `sudo apt install doxygen graphviz` |

## 8. Compiler Explorer

https://godbolt.org/ no se instala, pero se usa desde la Semana 01 para ver qué
ensamblador genera cada línea. Los trucos de cada semana incluyen enlaces con el código
precargado cuando aporta.
