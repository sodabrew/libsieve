/*
 *  Copyright (c) 2006 Aaron Stone <aaron@serendipity.cx>
 *
 *  $Id$ 
 *
 *  Gross compliance tests for libSieve.
 *
 */ 

#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "sieve2.h"

/*
sieve2_callback_t my_callbacks[] = {
{ SIEVE2_ERRCALL_RUNTIME,       my_errexec       },
{ SIEVE2_ERRCALL_PARSE,         my_errparse      },
{ SIEVE2_ACTION_FILEINTO,       my_fileinto      },
{ SIEVE2_ACTION_REDIRECT,       my_redirect      },
{ SIEVE2_ACTION_REJECT,         my_reject        },
{ SIEVE2_ACTION_NOTIFY,         my_notify        },
{ SIEVE2_ACTION_VACATION,       my_vacation      },
{ SIEVE2_ACTION_KEEP,           my_keep          },
{ SIEVE2_SCRIPT_GETSCRIPT,      my_getscript     },
// We don't support one header at a time in this example.
{ SIEVE2_MESSAGE_GETHEADER,     NULL             },
// libSieve can parse headers itself, so we'll use that.
{ SIEVE2_MESSAGE_GETALLHEADERS, my_getheaders    },
{ SIEVE2_MESSAGE_GETSUBADDRESS, my_getsubaddress },
{ SIEVE2_MESSAGE_GETENVELOPE,   my_getenvelope   },
{ SIEVE2_MESSAGE_GETBODY,       my_getbody       },
{ SIEVE2_MESSAGE_GETSIZE,       my_getsize       },
{ 0 } };
*/

struct my_context {
	int m_size;
	char *m_buf;
	char *s_buf;
	char *scriptfile;
	int error_runtime;
	int error_parse;
	int actiontaken;
};

sieve2_context_t *sieve2_context;
struct my_context *my_context;

void setup(void)
{
	/* This is the locally-defined structure that will be
	 * passed as the user context into the sieve calls.
	 * It will be passed by libSieve into each callback.*/
	my_context = malloc(sizeof(struct my_context));
	if (!my_context) {
		exit(1);
	}
	memset(my_context, 0, sizeof(struct my_context));
}

void teardown(void)
{
	free(my_context);
}

START_TEST(test_sv_fileinto)
{
	fail_unless(0==0,"Action fileinto failed.");
	
}
END_TEST

Suite *suite(void)
{
	Suite *s = suite_create("libSieve Gross Functionality");

	TCase *tc_sv = tcase_create("libSieve");
	suite_add_tcase(s, tc_sv);
	tcase_add_checked_fixture(tc_sv, setup, teardown);
	tcase_add_test(tc_sv, test_sv_fileinto);
	return s;
}

int main(void)
{
	int nf;
	Suite *s = suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	nf = srunner_ntests_failed(sr);
	srunner_free(sr);
	return nf;
}

