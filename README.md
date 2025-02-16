#### **signal-cpp**

---

an attempt to create library for signal protocol using libsodium

---

## On Linux (using apt)

For Debian-based distributions (such as Ubuntu), the easiest way to install libsodium is by installing the development package. This package includes the header files and the library you need to compile and link your C++ code.

1. **Update your package index:**

   ```bash
   sudo apt update
   ```

2. **Install the libsodium development package:**

   ```bash
   sudo apt install libsodium-dev
   ```

3. **Using in your C++ project:**
   - Include the header in your source files:
     ```cpp
     #include <sodium.h>
     ```
   - When compiling, link against the library by adding the `-lsodium` flag. For example:
     ```bash
     g++ your_source.cpp -o your_program -lsodium
     ```

---

## On Windows

### Option 1: Pre-built Binaries

1. **Download the pre-built package:**

   - Go to the [libsodium releases page](https://download.libsodium.org/libsodium/releases/).
   - Download the latest pre-built binary for Windows (for example, a file like `libsodium-1.0.18-msvc.zip`).

2. **Extract and set up:**
   - Unzip the package.
   - Choose the appropriate build (e.g., for Visual Studio, locate the corresponding `.lib` and header files).
   - In your Visual Studio project, add the extracted include folder to your project’s include directories and the library folder to your linker settings.
   - Make sure that the corresponding DLL (for dynamic linking) is either in your project directory or in a folder on your system’s PATH (you can copy it to `C:\Windows\System32` if needed).

### Option 2: Using vcpkg

vcpkg is a popular package manager for Windows (and even cross-platform) that automates the download, build, and integration of libraries.

1. **Clone and bootstrap vcpkg:**

   ```bash
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```

2. **Install libsodium:**

   ```bash
   .\vcpkg install libsodium
   ```

3. **Integrate with your build system:**
   - For Visual Studio, run:
     ```bash
     .\vcpkg integrate install
     ```
   - This automatically sets up your projects so that they can find the installed libsodium headers and libraries.

For further details on building with Visual Studio or MinGW, you can refer to the [official docs for Windows compilation](citeturn0search0).

---

##### clone this repository

```bash
git clone https://github.com/injustice-x/signal-cpp.git
cd signal-cpp
mkdir build
cd build
cmake ..
make
./signal
```
