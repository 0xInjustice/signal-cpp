# signal-cpp

`signal-cpp` is an experimental C++ library that implements core components of the Signal Protocol using `libsodium`. It provides key generation routines, the X3DH key agreement protocol, and the Double Ratchet algorithm to enable secure, end-to-end encrypted messaging with forward secrecy and post-compromise security.

## Features

- **X3DH Key Agreement:** Establish a shared session key via multiple Diffie–Hellman exchanges.
- **Double Ratchet Algorithm:** Continuously update message keys to ensure forward secrecy.
- **Libsodium Integration:** Leverages `libsodium` for robust, high-performance cryptographic primitives.

## Components

The library is structured into several components, each responsible for a specific part of the Signal Protocol implementation:

- **`signal.h`**: The main class that orchestrates the key generation, X3DH handshake, and the Double Ratchet session.
- **`generateKeyPair.h`**: Handles the generation of all necessary keys:
  - **Identity Keys (Ed25519):** Long-term keys for signing.
  - **Signed Pre-Keys (Curve25519):** Medium-term keys signed by the identity key.
  - **One-Time Pre-Keys (Curve25519):** A list of keys for single use.
- **`x3dh.h`**: Implements the **Extended Triple Diffie-Hellman (X3DH)** key agreement protocol.
- **`doubleratchet.h`**: Implements the **Double Ratchet** algorithm, which manages session keys for ongoing secure communication.
- **`encryption.h`**: Provides wrappers for symmetric encryption (`XChaCha20-Poly1305`) using `libsodium`.
- **`printHex.h` & `stringtohex.h`**: Utility functions for handling hexadecimal representations of keys and other data.

## Prerequisites

### Libsodium

The project depends on [libsodium](https://libsodium.gitbook.io/doc/). Make sure you have it installed on your system.

#### On Linux (Debian/Ubuntu)

1.  **Update your package index:**
    ```bash
    sudo apt update
    ```
2.  **Install the libsodium development package:**
    ```bash
    sudo apt install libsodium-dev
    ```

#### On Windows

For Windows, you can use `vcpkg` to install `libsodium`:

1.  **Clone and bootstrap vcpkg:**
    ```bash
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.bat
    ```
2.  **Install libsodium:**
    ```bash
    ./vcpkg install libsodium
    ```
3.  **Integrate with your build system:**
    ```bash
    ./vcpkg integrate install
    ```

## Building `signal-cpp`

To compile and run the provided code, follow these steps:

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/injustice-x/signal-cpp.git
    cd signal-cpp
    ```
2.  **Create a build directory and navigate into it:**
    ```bash
    mkdir build
    cd build
    ```
3.  **Generate the build system with CMake:**
    ```bash
    cmake ..
    ```
4.  **Build the project:**
    ```bash
    make
    ```
5.  **Run the executable:**
    ```bash
    ./signal
    ```

## Usage

The sample code in `signal.cpp` demonstrates how to use the library:

1.  **Initialization:**
    Both Alice and Bob generate all necessary keys (identity, signed pre-keys, one-time pre-keys, and ephemeral keys).

2.  **X3DH Key Agreement:**
    - Alice computes her session key using her identity and ephemeral keys along with Bob’s public key material.
    - Bob computes his session key using his responder function.
    - The session keys are verified to ensure that both parties have derived the same key.

3.  **Double Ratchet Initialization:**
    The session key seeds the double ratchet state. Each party initializes its sending and receiving chain keys using its own DH key pair and the remote party’s public key.

4.  **Simulated Secure Conversation:**
    The program simulates a conversation by encrypting and decrypting messages between Alice and Bob using the ratchet state. Message encryption involves generating a ciphertext and nonce, while decryption recovers the original plaintext.

For a detailed look at the code and to use these features in your own projects, refer to the source files (`signal.h`, `signal.cpp`, etc.).

## Project Structure

```
/
├── CMakeLists.txt
├── README.md
├── signal.cpp
└── includes/
    ├── doubleratchet.h
    ├── encryption.h
    ├── generateKeyPair.h
    ├── printHex.h
    ├── signal.h
    ├── stringtohex.h
    └── x3dh.h
```

---

Happy coding and secure messaging!
