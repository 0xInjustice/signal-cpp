#include "../includes/signal_protocol.h"
#include <stdio.h>

int main() {
	int iErrorCode;
	if (init_signal_protocol(&iErrorCode) == SODIUM_FAILURE) {
		fprintf(stdout, "main, init_signal_protocol");
		return FAILURE;
	}
	printf("%d\n%d\n%d\n%d\n", crypto_sign_ed25519_PUBLICKEYBYTES,
	       crypto_sign_ed25519_SECRETKEYBYTES,
	       crypto_scalarmult_curve25519_BYTES,
	       crypto_scalarmult_curve25519_BYTES);

	printf("SUCCESS\n");
	return SUCCESS;
}
