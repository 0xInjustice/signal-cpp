#ifndef PREKEY_H
#define PREKEY_H

#include "includes.h"

typedef struct sPreKey
{
	unsigned char spk_pub[crypto_box_PUBLICKEYBYTES];   // 32
	unsigned char spk_priv[crypto_box_SECRETKEYBYTES];  // 32
} tsPreKey;

typedef struct sSignedPreKey
{
	unsigned char spk_sig[crypto_sign_BYTES]; //64 B
	unsigned long long sig_len;
} tsSignedPreKey;

typedef struct sIdentityKeyPair tsIdentityKeyPair ;

int preKey_generate(tsPreKey *pPreKey, int *iErrorCode);
int preKey_sign(tsSignedPreKey *pSignedPreKey,
		tsPreKey *pPreKey,
		tsIdentityKeyPair *pIdentityKeyPair,
		int *iErrorCode);

#endif
