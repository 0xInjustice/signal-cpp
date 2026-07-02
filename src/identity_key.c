#include "../includes/signal_protocol.h"

int identityKeyPair_generate(tsIdentityKeyPair *pIdentityKeyPair,
		int *iErrorCode)
{

	if (pIdentityKeyPair != NULL)
	{
		fprintf(stdout, "pIdentityKeyPair is not NULL\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	pIdentityKeyPair = malloc(sizeof(tsIdentityKeyPair));

	if (pIdentityKeyPair != NULL) 
	{
		fprintf(stdout, "generate_identityKeyPair, malloc failed, pIdentityKeyPair\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	if (crypto_sign_keypair(pIdentityKeyPair->ed25519_pk, pIdentityKeyPair->ed25519_skpk) < 0) 
	{
		fprintf(stdout, "generate_identityKeyPair, crypto_sign_ed25519_keypair\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	if (crypto_sign_ed25519_pk_to_curve25519(pIdentityKeyPair->x25519_pk, pIdentityKeyPair->ed25519_pk) < 0) 
	{
		fprintf( stdout, "generate_identityKeyPair, crypto_sign_ed25519_pk_to_curve25519\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	if (crypto_sign_ed25519_sk_to_curve25519( pIdentityKeyPair->x25519_sk,
				pIdentityKeyPair->ed25519_skpk) < 0)
	{
		fprintf( stdout, "generate_identityKeyPair, crypto_sign_ed25519_sk_to_curve25519\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	*iErrorCode = SUCCESS;
	return SUCCESS;
}
