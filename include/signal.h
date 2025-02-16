#ifndef SIGNAL_H
#define SIGNAL_H

#include "globalContext.h"
#include <sodium.h>
class signal {
public:
  signal();
  ~signal();

  // Identity key pair (Ed25519): used for long-term identification and signing.
  // Public key: 32 bytes, Private key: 64 bytes.
  unsigned char identityPublicKey[crypto_sign_PUBLICKEYBYTES];
  unsigned char identityPrivateKey[crypto_sign_SECRETKEYBYTES];

  // Signed pre key pair (Curve25519): medium-term key pair.
  // Both public and private keys are 32 bytes.
  unsigned char signedPrePublicKey[crypto_box_PUBLICKEYBYTES];
  unsigned char signedPrePrivateKey[crypto_box_SECRETKEYBYTES];

  // Signature (Ed25519) over the signed pre key's public component (64 bytes).
  unsigned char signedPreKeySignature[crypto_sign_BYTES];

  // Structure to hold a one‑time pre key pair (Curve25519).
  struct OneTimePreKey {
    unsigned char publicKey[crypto_box_PUBLICKEYBYTES];  // 32 bytes
    unsigned char privateKey[crypto_box_SECRETKEYBYTES]; // 32 bytes
  };

  // Structure to hold an ephemeral key pair (Curve25519).
  struct EphemeralKey {
    unsigned char publicKey[crypto_box_PUBLICKEYBYTES];  // 32 bytes
    unsigned char privateKey[crypto_box_SECRETKEYBYTES]; // 32 bytes
  };
};

#endif // !SIGNAL_H
