#include "../includes/prekey.h"
#include "../includes/constants.h"
#include "../includes/identity_key.h"

int preKey_generate(tsPreKey *pPreKey, int *iErrorCode)
{
	if(pPreKey !=NULL)
	{
		fprintf(stdout, "pPreKey is not NULL\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	pPreKey = malloc(sizeof(tsPreKey));

	if (pPreKey != NULL) 
	{
		fprintf(stdout, "generate_preKey, malloc failed, pPreKey\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	if(crypto_box_keypair(pPreKey->spk_pub,pPreKey->spk_priv)<0)
	{
		fprintf(stdout, "generate_preKey, crypto_box_keypair, pPreKey\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	return SUCCESS;
}


int preKey_sign(tsSignedPreKey   *pSignedPreKey,
		tsPreKey				 *pPreKey,
		tsIdentityKeyPair		 *pIdentityKeyPair,
		int                 	 *iErrorCode)
{

	if(pSignedPreKey !=NULL)
	{
		fprintf(stdout, "pSignedPreKey is not NULL\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	if(pPreKey==NULL)
	{
		fprintf(stdout, "sign_preKey, pPreKey is NULL\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	pSignedPreKey = malloc(sizeof(tsSignedPreKey));

	if(pSignedPreKey == NULL)
	{
		fprintf(stdout, "sign_preKey, pSignedPreKey, malloc failed\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	if(pIdentityKeyPair==NULL)
	{
		free(pSignedPreKey);
		fprintf(stdout, "sign_preKey, pIdentityKeyPair NULL\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	if(crypto_sign_detached(pSignedPreKey->spk_sig,
				&(pSignedPreKey->sig_len),
				pPreKey->spk_pub,
				sizeof(pPreKey->spk_pub),
				pIdentityKeyPair->ed25519_pk)<0)
	{
		free(pSignedPreKey);
		fprintf(stdout, "sign_preKey, crypto_sign_detached\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	if(crypto_sign_verify_detached(pSignedPreKey->spk_sig,
				pPreKey->spk_pub,
				sizeof(pPreKey->spk_pub),
				pIdentityKeyPair->ed25519_skpk) !=0)
	{
		free(pSignedPreKey);
		fprintf(stdout, "sign_preKey, crypto_sign_verify_detached, invalid signature\n");
		*iErrorCode = FAILURE;
		return FAILURE;
	}

	return SUCCESS;
}
