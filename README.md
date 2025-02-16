---
# signal-cpp

signal-cpp is an experimental C++ library that implements core components of the Signal Protocol using libsodium. It provides key generation routines, the X3DH key agreement protocol, and the Double Ratchet algorithm to enable secure, end-to-end encrypted messaging with forward secrecy and post-compromise security.
---

## Features

- **X3DH Key Agreement:** Establish a shared session key via multiple Diffie–Hellman exchanges.
- **Double Ratchet Algorithm:** Continuously update message keys to ensure forward secrecy.
- **Libsodium Integration:** Leverages libsodium for robust, high-performance cryptographic primitives.

---

## Prerequisites

### Libsodium

The project depends on [libsodium](https://libsodium.gitbook.io/doc/). Make sure you have it installed on your system.

---

## Installation

### On Linux (Debian/Ubuntu)

1. **Update your package index:**

   ```bash
   sudo apt update
   ```

````

2. **Install the libsodium development package:**

   ```bash
   sudo apt install libsodium-dev
   ```

3. **Compile Your Project:**
   - In your source files, include the header:
     ```cpp
     #include <sodium.h>
     ```
   - When compiling, link against libsodium by adding the `-lsodium` flag. For example:
     ```bash
     g++ your_source.cpp -o your_program -lsodium
     ```

### On Windows

#### Option 1: Pre-built Binaries

1. **Download the pre-built package:**

   - Visit the [libsodium releases page](https://download.libsodium.org/libsodium/releases/) and download the latest pre-built binary for Windows (e.g., `libsodium-1.0.18-msvc.zip`).

2. **Extract and Set Up:**
   - Unzip the package.
   - For Visual Studio, add the extracted include folder to your project's include directories and the corresponding library folder to your linker settings.
   - Ensure that the appropriate DLL is available in your project directory or added to your system's PATH.

#### Option 2: Using vcpkg

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
   - This sets up your projects to automatically find the libsodium headers and libraries.

For more details on Windows build configuration (e.g., using Visual Studio or MinGW), please refer to the [official docs for Windows compilation](citeturn0search0).

---

## Building signal-cpp

To compile and run the provided code, follow these steps:

1. **Clone the repository:**

   ```bash
   git clone https://github.com/injustice-x/signal-cpp.git
   cd signal-cpp
   ```

2. **Create a build directory and navigate into it:**

   ```bash
   mkdir build
   cd build
   ```

3. **Generate the build system with CMake:**

   ```bash
   cmake ..
   ```

4. **Build the project:**

   ```bash
   make
   ```

5. **Run the executable:**

   ```bash
   ./signal
   ```

---

## Usage

The sample code in `signal.cpp` demonstrates how to use the library:

1. **Initialization:**
   Both Alice and Bob generate all necessary keys (identity, signed prekeys, one-time prekeys, and ephemeral keys).

2. **X3DH Key Agreement:**

   - Alice computes her session key using her identity and ephemeral keys along with Bob’s public key material.
   - Bob computes his session key using his responder function.
   - The session keys are verified to ensure that both parties have derived the same key.

3. **Double Ratchet Initialization:**
   The session key seeds the double ratchet state. Each party initializes its sending and receiving chain keys using its own DH key pair and the remote party’s public key.

4. **Simulated Secure Conversation:**
   The program simulates a conversation by encrypting and decrypting messages between Alice and Bob using the ratchet state. Message encryption involves generating a ciphertext and nonce, while decryption recovers the original plaintext.

For a detailed look at the code and to use these features in your own projects, refer to the source files (`signal.h`, `signal.cpp`, etc.).

---

Happy coding and secure messaging!

```

---

```
````
