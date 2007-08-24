/* sieve-encodedchar.c -- RFC 3028-bis Encoded Char Decoder
 * Aaron Stone
 * $Id: sieve-lex.l 80 2006-07-24 14:24:53Z sodabrew $
 */
/* * * *
 * Copyright 2007 by Aaron Stone
 *
 * Licensed under the GNU Lesser General Public License (LGPL)
 * version 2.1, and other versions at the author's discretion.
 * * * */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* sv_interface */
#include "callbacks2.h"

/* sv_util */
#include "util.h"

#define THIS_MODULE "sv_parser"
#define THIS_CONTEXT libsieve_parse_context
extern struct sieve2_context *libsieve_parse_context;

typedef int (* char_conv_fp)(unsigned int, char *);

static int char_uni(unsigned int ch, char *text)
{
	if (ch < 0x80) {
		text[0] = (char)ch;
		return 1;
	} else if (ch < 0x800) {
		text[0] = (char)( 0xC0 |  (ch >>  6)         ); // One more follows
		text[1] = (char)( 0x80 |  (ch        & 0x3F) ); // Lower 6 bits
		return 2;
	} else if (ch < 0x10000) {
		text[0] = (char)( 0xE0 |  (ch >> 12)         ); // Two more follow
		text[1] = (char)( 0x80 | ((ch >>  6) & 0x3F) ); // Lower 6 bits
		text[2] = (char)( 0x80 |  (ch        & 0x3F) );
		return 3;
	} else if (ch < 0x110000) {
		text[0] = (char)( 0xF0 |  (ch >> 18)         ); // Three more follow
		text[1] = (char)( 0x80 | ((ch >> 12) & 0x3F) ); // Lower 6 bits
		text[2] = (char)( 0x80 | ((ch >>  6) & 0x3F) );
		text[3] = (char)( 0x80 |  (ch        & 0x3F) );
		return 4;
	}
	return 0;
}

static int char_hex(unsigned int ch, char *text)
{
	if (ch < 256) {
		text[0] = (char)ch;
		return 1;
	}
	return 0;
}


static char *libsieve_encoded_char(char *text, size_t len, size_t *outlen,
	char_conv_fp char_conv)
{
        size_t i = 0, j = 0;
	unsigned int curval = 0;
	// Worst-case UTF-8 encoding is each character needs 4 bytes
        char *decoded = libsieve_malloc(sizeof(char) * (len * 2 + 1));

        // Advance i up to the : in '${hex:01 23 45 ...}
        while (i < len && text[i] != ':') { i++; }
        i++;

        // Decode the hex singles/pairs
        while (j < len && i < len) {
		if ((isspace(text[i]) || text[i] == '}')) {
			if ((j += char_conv(curval, decoded + j)) == 0) {
				TRACE_DEBUG("Value [%u] is not a character code", curval);
			}
			curval = 0;
		} else if (!isspace(text[i])) {
			char dig = text[i];

			     if (dig >= '0' && dig <= '9') {
				 dig -= '0';
			} else if (dig >= 'A' && dig <= 'F') {
				 dig -= 'A';
				 dig += 10;
			} else if (dig >= 'a' && dig <= 'f') {
				 dig -= 'a';
				 dig += 10;
			} else {
				TRACE_DEBUG("Char [%c] is not hex", dig);
				break;
			}

			curval = curval << 4;
			curval = curval + dig;
		} else {
			TRACE_DEBUG("Found char [%c] repeated whitespace", text[i]);
		}
		
		i++;
	}

        decoded[j] = '\0';

        TRACE_DEBUG("Converting [%s] to [%s] length [%zu]", text, decoded, j);

	if (outlen)
		*outlen = j;
        return decoded;
}

char *libsieve_encoded_char_hex(char *text, size_t len, size_t *outlen)
{
	return libsieve_encoded_char(text, len, outlen, char_hex);
}

char *libsieve_encoded_char_uni(char *text, size_t len, size_t *outlen)
{
	return libsieve_encoded_char(text, len, outlen, char_uni);
}

