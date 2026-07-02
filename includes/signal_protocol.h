#ifndef SIGNAL_H
#define SIGNAL_H

/* User created Library*/
#include "constants.h"
#include "identity_key.h"
#include "includes.h"
#include "prekey.h"

int init_signal_protocol(int *iErrorCode);

#endif

// Identity Key Pair (IK) - Long-term Ed25519/Curve25519 key pair
// Signed Prekey (SPK) - Medium-term Curve25519 key pair
// One-Time Prekey (OPK) - Ephemeral Curve25519 key pairs
// Ephemeral Key (EK) - Generated fresh per X3DH session by Alice
// Root Key (RK) - 32-byte symmetric key, output of X3DH, evolves in Double Ratchet
// Chain Key (CK) - 32-byte symmetric key, one per chain (sending/receiving)
// Message Key (MK) - 32-byte symmetric key per message, used for AEAD
// Header Key (HK) - Optional, for header encryption
// Next Header Key (NHK) - For future ratchet steps
