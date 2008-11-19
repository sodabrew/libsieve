#ifndef SIEVE_ENCODEDCHAR_H
#define SIEVE_ENCODEDCHAR_H

#include "context2.h"

char *libsieve_encoded_char_hex(struct sieve2_context *context, char *text, size_t len, size_t *outlen);
char *libsieve_encoded_char_uni(struct sieve2_context *context, char *text, size_t len, size_t *outlen);

#endif
