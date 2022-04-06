# uint320

![build](https://github.com/mrdcvlsc/uint320/actions/workflows/build.yml/badge.svg)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

**mini-tests:**

![gcc-gnu](https://github.com/mrdcvlsc/uint320/actions/workflows/gcc-gnu.yml/badge.svg)
![clang](https://github.com/mrdcvlsc/uint320/actions/workflows/clang.yml/badge.svg)
![mingw32](https://github.com/mrdcvlsc/uint320/actions/workflows/mingw32.yml/badge.svg)

-----

# Environment Requirements
- x86_64 architecture
- little endian system

If your system does not have these requirements, it might produce wrong results or might not even compile.

-----

# Sample Use

```c++
#include <iostream>
#include "Header-Mode-uint320.hpp"

uint320 fac(size_t n) {
    uint320 factorial(1);
    uint320 iter = factorial;

    for(size_t i=1; i<=n; ++i) {
        factorial = factorial * iter;
        iter.limbs[0]++;
    }

    return factorial;
}

int main() {
    uint320 factorial67 = fac(67);
    factorial67.printHex();
}
```

**output:**
```
0x45f0025cc534351 d9eca1b12a7b1294 a77c082c2962623d fe3152bcbff89f41 0000000000000000
```

-----


# Compilation

There are **TWO WAYS** to use the library, either using the **header only mode**, or building the **static library**.

- ## **Using header only**

    Directly include the **Header-Mode-uint320.hpp** in your source code, and you can directly compile it without building the static library.

    ```c++
    #include "Header-Mode-uint320.hpp"
    ```

    But you always need to enable the optimization flags for this method to work.

    ```shell
    g++ main.cpp main.out -O2
    ```

    ```shell
    clang++ main.cpp main.out -O2
    ```

<br>

- ## **Static Build with GNU-GCC Linux makefiles**

    Build & install static library
    ```shell
    make -f staticlib
    sudo make -f staticlib install
    ```

    Run tests (optional)
    ```
    make -f staticlib build_test
    ```

    Include ```#include <uint320.hpp>``` in your program then compile with **-lchacha20**

    ```
    g++ main.cpp -o main.out -lchacha20
    ```

    To uninstall library
    ```
    sudo make -f staticlib uninstall
    ```

    Clean Up compiled objects
    ```
    make -f staticlib cleanup
    ```

<br>

- ## **Static Build with Clang Linux makefiles**

    Build static library with clang
    ```shell
    make -f staticlib CC=clang++
    sudo make -f staticlib install
    ```

    Run tests with clang (optional)
    ```
    make -f staticlib build_test CC=clang++
    ```

    Include ```#include <uint320.hpp>``` in your program then compile with **-lchacha20**

    ```
    clang++ main.cpp -o main.out -lchacha20
    ```

    To uninstall library
    ```
    sudo make -f staticlib uninstall
    ```

    Clean Up compiled objects
    ```
    make -f staticlib cleanup
    ```

<br>

- ## **Static Build with Mingw64 Windows makefiles**
    
    Build & install static library
    ```shell
    mingw32-make -f staticlib
    mingw32-make -f staticlib install INSTALL_PREFIX=(path/to/mingw64)
    ```

    Run tests (optional)
    ```
    mingw32-make -f staticlib build_test
    ```

    Include ```#include <uint320.hpp>``` in your program then compile with **-lchacha20**

    ```
    g++ main.cpp -o main.out -lchacha20
    ```

    To uninstall library
    ```
    mingw32-make -f staticlib uninstall INSTALL_PREFIX=(path/to/mingw64)
    ```

    Clean Up compiled objects
    ```
    mingw32-make -f staticlib cleanup
    ```

You can also modify the installation path in linux by setting up a new value for the ```INSTALL_PREFIX=``` when executing the make build commands similar to what is shown in the windows build.