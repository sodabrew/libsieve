/* testcomp.c -- test and exercises for the comparator functions.
 * $Id$
 *
 * usage: "testcomp"
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


/* THESE ARE INTERNAL HEADERS,
 * DO NOT TRY TO USE THEM IN
 * YOUR OWN APPLICATION CODE.
 * */
#include "comparator.h"
#include "tree.h"
#include "sieve.h"


struct testcase {
	const char *comp; 
	int mode;
	const char *pat;
	const char *text;
	int result;
};

struct testcase tc[] = {
	{ "i;octet", IS, "", "", 1 },
	{ "i;octet", IS, "a", "", 0 },
	{ "i;octet", IS, "", "a", 0 },
	{ "i;octet", IS, "a", "a", 1 },
	{ "i;octet", IS, "a", "A", 0 },

	{ "i;ascii-casemap", IS, "", "", 1 },
	{ "i;ascii-casemap", IS, "a", "", 0 },
	{ "i;ascii-casemap", IS, "", "a", 0 },
	{ "i;ascii-casemap", IS, "a", "a", 1 },
	{ "i;ascii-casemap", IS, "a", "A", 1 },

	{ "i;octet", CONTAINS, "", "", 1 },
	{ "i;octet", CONTAINS, "", "a", 1 },
	{ "i;octet", CONTAINS, "a", "", 0 },
	{ "i;octet", CONTAINS, "a", "a", 1 },
	{ "i;octet", CONTAINS, "a", "ab", 1 },
	{ "i;octet", CONTAINS, "a", "ba", 1 },
	{ "i;octet", CONTAINS, "a", "aba", 1 },
	{ "i;octet", CONTAINS, "a", "bab", 1 },
	{ "i;octet", CONTAINS, "a", "bb", 0 },
	{ "i;octet", CONTAINS, "a", "bbb", 0 },

	{ "i;octet", MATCHES, "", "", 1 },
	{ "i;octet", MATCHES, "", "a", 0 },
	{ "i;octet", MATCHES, "a", "", 0 },
	{ "i;octet", MATCHES, "a", "a", 1 },
	{ "i;octet", MATCHES, "a", "ab", 0 },
	{ "i;octet", MATCHES, "a", "ba", 0 },
	{ "i;octet", MATCHES, "a", "aba", 0 },
	{ "i;octet", MATCHES, "a", "bab", 0 },
	{ "i;octet", MATCHES, "a", "bb", 0 },
	{ "i;octet", MATCHES, "a", "bbb", 0 },

	{ "i;octet", MATCHES, "*", "", 1 },
	{ "i;octet", MATCHES, "*", "a", 1 },
	{ "i;octet", MATCHES, "*a*", "", 0 },
	{ "i;octet", MATCHES, "*a*", "a", 1 },
	{ "i;octet", MATCHES, "*a*", "ab", 1 },
	{ "i;octet", MATCHES, "*a*", "ba", 1 },
	{ "i;octet", MATCHES, "*a*", "aba", 1 },
	{ "i;octet", MATCHES, "*a*", "bab", 1 },
	{ "i;octet", MATCHES, "*a*", "bb", 0 },
	{ "i;octet", MATCHES, "*a*", "bbb", 0 },

	{ "i;octet", MATCHES, "*a", "", 0 },
	{ "i;octet", MATCHES, "*a", "a", 1 },
	{ "i;octet", MATCHES, "*a", "ab", 0 },
	{ "i;octet", MATCHES, "*a", "ba", 1 },
	{ "i;octet", MATCHES, "*a", "aba", 1 },
	{ "i;octet", MATCHES, "*a", "bab", 0 },
	{ "i;octet", MATCHES, "*a", "bb", 0 },
	{ "i;octet", MATCHES, "*a", "bbb", 0 },

	{ "i;octet", MATCHES, "a*", "", 0 },
	{ "i;octet", MATCHES, "a*", "a", 1 },
	{ "i;octet", MATCHES, "a*", "ab", 1 },
	{ "i;octet", MATCHES, "a*", "ba", 0 },
	{ "i;octet", MATCHES, "a*", "aba", 1 },
	{ "i;octet", MATCHES, "a*", "bab", 0 },
	{ "i;octet", MATCHES, "a*", "bb", 0 },
	{ "i;octet", MATCHES, "a*", "bbb", 0 },

	{ "i;octet", MATCHES, "a*b", "", 0 },
	{ "i;octet", MATCHES, "a*b", "a", 0 },
	{ "i;octet", MATCHES, "a*b", "ab", 1 },
	{ "i;octet", MATCHES, "a*b", "ba", 0 },
	{ "i;octet", MATCHES, "a*b", "aba", 0 },
	{ "i;octet", MATCHES, "a*b", "bab", 0 },
	{ "i;octet", MATCHES, "a*b", "bb", 0 },
	{ "i;octet", MATCHES, "a*b", "bbb", 0 },
	{ "i;octet", MATCHES, "a*b", "abbb", 1 },
	{ "i;octet", MATCHES, "a*b", "acb", 1 },
	{ "i;octet", MATCHES, "a*b", "acbc", 0 },

	{ "i;octet", MATCHES, "a?b", "", 0 },
	{ "i;octet", MATCHES, "a?b", "a", 0 },
	{ "i;octet", MATCHES, "a?b", "ab", 0 },
	{ "i;octet", MATCHES, "a?b", "ba", 0 },
	{ "i;octet", MATCHES, "a?b", "aba", 0 },
	{ "i;octet", MATCHES, "a?b", "bab", 0 },
	{ "i;octet", MATCHES, "a?b", "bb", 0 },
	{ "i;octet", MATCHES, "a?b", "bbb", 0 },
	{ "i;octet", MATCHES, "a?b", "abbb", 0 },
	{ "i;octet", MATCHES, "a?b", "acb", 1 },
	{ "i;octet", MATCHES, "a?b", "acbc", 0 },

	{ "i;octet", MATCHES, "a*?b", "", 0 },
	{ "i;octet", MATCHES, "a*?b", "a", 0 },
	{ "i;octet", MATCHES, "a*?b", "ab", 0 },
	{ "i;octet", MATCHES, "a*?b", "ba", 0 },
	{ "i;octet", MATCHES, "a*?b", "aba", 0 },
	{ "i;octet", MATCHES, "a*?b", "bab", 0 },
	{ "i;octet", MATCHES, "a*?b", "bb", 0 },
	{ "i;octet", MATCHES, "a*?b", "bbb", 0 },
	{ "i;octet", MATCHES, "a*?b", "abbb", 1 },
	{ "i;octet", MATCHES, "a*?b", "acb", 1 },
	{ "i;octet", MATCHES, "a*?b", "acbc", 0 },

	{ "i;octet", MATCHES, "a?*b", "", 0 },
	{ "i;octet", MATCHES, "a?*b", "a", 0 },
	{ "i;octet", MATCHES, "a?*b", "ab", 0 },
	{ "i;octet", MATCHES, "a?*b", "ba", 0 },
	{ "i;octet", MATCHES, "a?*b", "aba", 0 },
	{ "i;octet", MATCHES, "a?*b", "bab", 0 },
	{ "i;octet", MATCHES, "a?*b", "bb", 0 },
	{ "i;octet", MATCHES, "a?*b", "bbb", 0 },
	{ "i;octet", MATCHES, "a?*b", "abbb", 1 },
	{ "i;octet", MATCHES, "a?*b", "acb", 1 },
	{ "i;octet", MATCHES, "a?*b", "acbc", 0 },

	{ "i;octet", MATCHES, "a*?*b", "", 0 },
	{ "i;octet", MATCHES, "a*?*b", "a", 0 },
	{ "i;octet", MATCHES, "a*?*b", "ab", 0 },
	{ "i;octet", MATCHES, "a*?*b", "ba", 0 },
	{ "i;octet", MATCHES, "a*?*b", "aba", 0 },
	{ "i;octet", MATCHES, "a*?*b", "bab", 0 },
	{ "i;octet", MATCHES, "a*?*b", "bb", 0 },
	{ "i;octet", MATCHES, "a*?*b", "bbb", 0 },
	{ "i;octet", MATCHES, "a*?*b", "abbb", 1 },
	{ "i;octet", MATCHES, "a*?*b", "acb", 1 },
	{ "i;octet", MATCHES, "a*?*b?", "acbc", 1 },

	{ "i;ascii-casemap", MATCHES, "a*b", "", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "a", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "ab", 1 },
	{ "i;ascii-casemap", MATCHES, "a*b", "ba", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "aba", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "bab", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "bb", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "bbb", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "abbb", 1 },
	{ "i;ascii-casemap", MATCHES, "a*b", "acb", 1 },
	{ "i;ascii-casemap", MATCHES, "a*b", "acbc", 0 },

	{ "i;ascii-casemap", MATCHES, "a*b", "", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "A", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "Ab", 1 },
	{ "i;ascii-casemap", MATCHES, "a*b", "BA", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "ABA", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "BAb", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "BB", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "BBB", 0 },
	{ "i;ascii-casemap", MATCHES, "a*b", "aBBB", 1 },
	{ "i;ascii-casemap", MATCHES, "a*b", "ACB", 1 },
	{ "i;ascii-casemap", MATCHES, "a*b", "ACBC", 0 },

	{ NULL, 0, NULL, NULL, 0 } };

static int test_comparator(void)
{
	struct testcase *t;
	int didfail = 0;

	for (t = tc; t->comp != NULL; t++) {
		comparator_t *c =
			libsieve_comparator_lookup(t->comp, t->mode);
		int res;
		char *mode;

		if (t->mode == IS) mode = "IS";
		else if (t->mode == CONTAINS) mode = "CONTAINS";
		else if (t->mode == MATCHES) mode = "MATCHES";
		else if (t->mode == REGEX) mode = "REGEX";
		else mode = "<unknown mode>";
		
		if (!c) {
			printf("FAIL: can't find a comparator %s/%s\n", 
				t->comp, mode);
			didfail++;
			continue;
		}

		res = c(t->pat, t->text);
		if (res != t->result) {
			printf("FAIL: %s/%s(%s, %s) = %d, not %d\n", 
				t->comp, mode,
				t->pat, t->text, res, t->result);
			didfail++;
		}
	}

	return didfail;
}

int main(int argc, char *argv[])
{
	int res;

	res = test_comparator();
	if (res > 0) {
		printf("Failed %d tests.\n", res);
		exit(1);
	} else {
		printf("Passed all tests.\n");
		exit(0);
	}

}

