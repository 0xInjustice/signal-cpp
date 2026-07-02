#include "includes.h"

#ifndef IDENTITY_KEY_H 
#define IDENTITY_KEY_H
typedef struct sIdentityKeyPair {
	unsigned char ed25519_pk[crypto_sign_ed25519_PUBLICKEYBYTES];    // 32
	unsigned char ed25519_skpk[crypto_sign_ed25519_SECRETKEYBYTES];  // 64
	unsigned char x25519_pk[crypto_scalarmult_curve25519_BYTES];     // 32
	unsigned char x25519_sk[crypto_scalarmult_curve25519_BYTES];     // 32
} tsIdentityKeyPair;

int identityKeyPair_generate(tsIdentityKeyPair *pIdentityKeyPair,
		int *iErrorCode);

#endif
