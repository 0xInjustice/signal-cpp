#include "../includes/signal_protocol.h"

int init_signal_protocol(int *iErrorCode) {
	if (sodium_init() < 0) {
		*iErrorCode = SODIUM_FAILURE;
		return FAILURE;
	}
	*iErrorCode = SODIUM_SUCCESS;
	return SUCCESS;
}
