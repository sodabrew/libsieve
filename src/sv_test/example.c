/* test.c -- test and example for sieve version 2 api
 * Aaron Stone
 * $Id$
 *
 * usage: "test message script"
 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                       *
 * As an exception to the LGPL license which applies to the libSieve     *
 * library as a whole, this file is released under the "MIT License"     *
 * so as to promote use of this work as a generic template for both      *
 * free and proprietary software which make use of the libSieve library. *
 *                                                                       *
 * Copyright (c) 2005 Aaron Stone                                        *
 *                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining *
 * a copy of this software and associated documentation files (the       *
 * "Software"), to deal in the Software without restriction, including   *
 * without limitation the rights to use, copy, modify, merge, publish,   *
 * distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject    *
 * to the following conditions:                                          *
 *                                                                       *
 * The above copyright notice and this permission notice shall be        *
 * included in all copies or substantial portions of the Software.       *
 *                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                *
 *                                                                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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

#include "sieve2.h"
#include "sieve2_error.h"

struct my_context {
	int m_size;
	char *m_buf;
	char *s_buf;
	char *scriptfile;
	int error_runtime;
	int error_parse;
	int actiontaken;
};

static int read_file(char *filename, char **ret_buf,
	int (* terminator)(char *buf, int pos) );
static int end_of_nothing(char *buf, int pos);
static int end_of_header(char *buf, int pos);

int my_notify(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;
	const char * const * options;
	int i;

	printf( "Action is NOTIFY: \n" );
	printf( "  ID \"%s\" is %s\n",
		sieve2_getvalue_string(s, "id"),
		sieve2_getvalue_string(s, "active"));
	printf( "    Method is %s\n",
		sieve2_getvalue_string(s, "method"));
	printf( "    Priority is %s\n",
		sieve2_getvalue_string(s, "priority"));
	printf( "    Message is %s\n",
		sieve2_getvalue_string(s, "message"));

	options = sieve2_getvalue_stringlist(s, "options");
	if (!options)
		return SIEVE2_ERROR_BADARGS;
	for (i = 0; options[i] != NULL; i++) {
		printf( "    Options are %s\n", options[i] );
	}

	m->actiontaken = 1;
	return SIEVE2_OK;
}

int my_vacation(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;
	int yn;

	/* Ask for the message hash, the days parameters, etc. */
	printf("Have I already responded to '%s' in the past %d days?\n",
		sieve2_getvalue_string(s, "hash"),
		sieve2_getvalue_int(s, "days") );

	yn = getchar();

	/* Check in our 'database' to see if there's a match. */
	if (yn == 'y' || yn == 'Y') {
		printf( "Ok, not sending a vacation response.\n" );
	}

	/* If so, do nothing. If not, send a vacation and log it. */
	printf("echo '%s' | mail -s '%s' '%s' for message '%s'\n",
		sieve2_getvalue_string(s, "message"),
		sieve2_getvalue_string(s, "subject"),
		sieve2_getvalue_string(s, "address"),
		sieve2_getvalue_string(s, "name") );

	m->actiontaken = 1;
	return SIEVE2_OK;
}

int my_redirect(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	printf( "Action is REDIRECT: \n" );
	printf( "  Destination is [%s]\n",
		sieve2_getvalue_string(s, "address"));

	m->actiontaken = 1;
	return SIEVE2_OK;
}

int my_reject(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	printf( "Action is REJECT: \n" );
	printf( "  Message is [%s]\n",
		sieve2_getvalue_string(s, "message"));

	m->actiontaken = 1;
	return SIEVE2_OK;
}

int my_discard(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	printf( "Action is DISCARD\n" );

	m->actiontaken = 1;
	return SIEVE2_OK;
}

int my_fileinto(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;
	const char * const * flags;
	int i;

	printf( "Action is FILEINTO: \n" );
	printf( "  Destination is %s\n",
		sieve2_getvalue_string(s, "mailbox"));
	flags = sieve2_getvalue_stringlist(s, "imapflags");
	if (flags) {
		printf( "  Flags are:");
		for (i = 0; flags[i]; i++)
			printf( " %s", flags[i]);
		printf( ".\n");
	} else {
			printf( "  No flags specified.\n");
	}

	m->actiontaken = 1;
	return SIEVE2_OK;
}

int my_keep(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	printf( "Action is KEEP\n" );

	m->actiontaken = 1;
	return SIEVE2_OK;
}

int my_errparse(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	printf( "Error is PARSE: " );
	printf( "  Line is %d\n",
		sieve2_getvalue_int(s, "lineno"));
	printf( "  Message is %s\n",
		sieve2_getvalue_string(s, "message"));

	m->error_parse = 1;
	return SIEVE2_OK;
}

int my_errexec(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	printf( "Error is EXEC: " );
	printf( "  Message is %s\n",
		sieve2_getvalue_string(s, "message"));

	m->error_runtime = 1;
	return SIEVE2_OK;
}

int my_getscript(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;
	const char * path, * name;
	int res;

	/* Path could be :general, :personal, or empty. */
	path = sieve2_getvalue_string(s, "path");

	/* If no file is named, we're looking for the main file. */
	name = sieve2_getvalue_string(s, "name");

	if (path == NULL || name == NULL)
		return SIEVE2_ERROR_BADARGS;

	if (strlen(path) && strlen(name)) {
		printf("Include requested from '%s' named '%s'\n",
			path, name);
	} else
	if (!strlen(path) && !strlen(name)) {
		/* If we're being called again, free what was here before. */
		if (m->s_buf) free(m->s_buf);

		/* Read the script file given as an argument. */
		res = read_file(m->scriptfile, &m->s_buf, end_of_nothing);
		if (res != SIEVE2_OK) {
			printf("my_getscript: read_file() returns %d\n", res);
			return SIEVE2_ERROR_FAIL;
		}
		sieve2_setvalue_string(s, "script", m->s_buf);
	} else {
		return SIEVE2_ERROR_BADARGS;
	}

	return SIEVE2_OK;
}

int my_getheaders(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	sieve2_setvalue_string(s, "allheaders", m->m_buf);

	return SIEVE2_OK;
}

int my_getheader(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	printf( "Requested header [%s], returning NULL\n",
			sieve2_getvalue_string(s, "header") );

	char ** null = { NULL, NULL };
	sieve2_setvalue_stringlist(s, "body", null );

	return SIEVE2_OK;
}

/* Feed back null values as a crash test. */
int my_getenvelope(sieve2_context_t *s, void *my)
{
	sieve2_setvalue_string(s, "to", "foo@bar");
	sieve2_setvalue_string(s, "from", "" );

	return SIEVE2_OK;
//	return SIEVE2_ERROR_UNSUPPORTED;
}

int my_getbody(sieve2_context_t *s, void *my)
{
	return SIEVE2_ERROR_UNSUPPORTED;
}

int my_getsize(sieve2_context_t *s, void *my)
{
	struct my_context *m = (struct my_context *)my;

	sieve2_setvalue_int(s, "size", m->m_size);

	return SIEVE2_OK;
}

/* END OF EXAMPLE SIEVE CALLBACKS */

/* little function to check for end of a RFC 822 header. */
static int end_of_header(char *buf, int pos)
{
	return ( (pos < 2 ? 0 :
			(buf[pos-1] == '\n' && buf[pos-2] == '\n'))
		|| (pos < 4 ? 0 :
			(buf[pos-1] == '\n' && buf[pos-2] == '\r'
			&& buf[pos-3] == '\n' && buf[pos-4] == '\r'))
	);
}

/* little function to do not muc of anything. */
static int end_of_nothing(char *buf, int pos)
{
	return 0;
}

static int read_file(char *filename, char **ret_buf,
	int (* terminator)(char *buf, int pos) )
{
#define GROW_AMOUNT 200
	size_t f_len=0;
	size_t f_pos=0;
	char *tmp_buf;
	char *f_buf = NULL; // This one needs to initialize NULL!
	FILE *f;

	if (!filename) {
		*ret_buf = f_buf;
		return SIEVE2_ERROR_FAIL;
	}

   	f = fopen(filename, "r");
		if (!f) {
		printf("Could not open file '%s'\n", filename);
		return 1;
		}

	while(!feof(f) && !terminator(f_buf, f_pos)) {
		if( f_pos + 1 >= f_len ) {
			tmp_buf = realloc(f_buf,
				sizeof(char) * (f_len+=GROW_AMOUNT));
		if( tmp_buf != NULL )
			f_buf = tmp_buf;
		else
			return 1;
		}
		f_buf[f_pos] = fgetc(f);
		f_pos++;
	}

	if(f_pos)
		f_buf[f_pos] = '\0';

	fclose(f);

	*ret_buf = f_buf;
	return SIEVE2_OK;
}

/* END OF EXAMPLE FILE PROCESSING FUNCTIONS */

/* CALLBACK REGISTRATION TABLE */

sieve2_callback_t my_callbacks[] = {
{ SIEVE2_ERRCALL_RUNTIME,       my_errexec     },
{ SIEVE2_ERRCALL_PARSE,         my_errparse    },
{ SIEVE2_ACTION_FILEINTO,       my_fileinto    },
{ SIEVE2_ACTION_REDIRECT,       my_redirect    },
{ SIEVE2_ACTION_REJECT,         my_reject      },
{ SIEVE2_ACTION_NOTIFY,         my_notify      },
{ SIEVE2_ACTION_VACATION,       my_vacation    },
{ SIEVE2_ACTION_KEEP,           my_keep        },
{ SIEVE2_SCRIPT_GETSCRIPT,      my_getscript   },
/* We don't support one header at a time in this example. */
{ SIEVE2_MESSAGE_GETHEADER,     NULL            },
/* libSieve can parse headers itself, so we'll use that. */
{ SIEVE2_MESSAGE_GETALLHEADERS, my_getheaders  },
//{ SIEVE2_MESSAGE_GETHEADER,     my_getheader   },
{ SIEVE2_MESSAGE_GETENVELOPE,   my_getenvelope },
{ SIEVE2_MESSAGE_GETBODY,       my_getbody     },
{ SIEVE2_MESSAGE_GETSIZE,       my_getsize     },
{ 0 } };

static int beenhere = 0;

int main(int argc, char *argv[])
{
	int usage_error = 0;
	int res, exitcode = 0;
	struct my_context *my_context;
	sieve2_context_t *sieve2_context;
	char *message = NULL, *script = NULL;

	if (argc < 2) {
		usage_error = 1;
	} else {
		if (strcmp(argv[1], "-l") == 0) {
			printf("%s", sieve2_license());
			exitcode = 0;
			goto endnofree;
		} else if (strcmp(argv[1], "-c") == 0) {
			printf("%s", sieve2_credits());
			exitcode = 0;
			goto endnofree;
		} else if (argc == 2) {
			script = argv[1];
		} else if (argc == 3) {
			script = argv[1];
			message = argv[2];
		} else {
			usage_error = 1;
		}
	}

	if (usage_error) {
		printf("Usage:\n");
		printf("%s script\n", argv[0]);
		printf("%s script message\n", argv[0]);
		exitcode = 1;
		goto endnofree;
	}

	/* This is the locally-defined structure that will be
	 * passed as the user context into the sieve calls.
	 * It will be passed by libSieve into each callback.*/
	my_context = malloc(sizeof(struct my_context));
	if (!my_context) {
		exitcode = 1;
		goto endnofree;
	}
	memset(my_context, 0, sizeof(struct my_context));

	if (script) {
		my_context->scriptfile = script;
	}

	if (message) {
		res = read_file(message, &my_context->m_buf, end_of_header);
		if (res != SIEVE2_OK) {
			printf("Message: read_file() returns %d\n", res);
			exitcode = 1;
			goto endnofree;
		}
	}

	res = sieve2_alloc(&sieve2_context);
	if (res != SIEVE2_OK) {
		printf("Error %d when calling sieve2_alloc: %s\n",
			res, sieve2_errstr(res));
		exitcode = 1;
		goto freesieve;
	}

	res = sieve2_callbacks(sieve2_context, my_callbacks);
	if (res != SIEVE2_OK) {
		printf("Error %d when calling sieve2_callbacks: %s\n",
			res, sieve2_errstr(res));
		exitcode = 1;
		goto freesieve;
	}

	printf("Validating script...\n");
	res = sieve2_validate(sieve2_context, my_context);
	if (res != SIEVE2_OK) {
		printf("Error %d when calling sieve2_validate: %s\n",
			res, sieve2_errstr(res));
		exitcode = 1;
	}

	if (message) {
		printf("Executing script...\n");
		res = sieve2_execute(sieve2_context, my_context);
		if (res != SIEVE2_OK) {
			printf("Error %d when calling sieve2_execute: %s\n",
				res, sieve2_errstr(res));
			exitcode = 1;
		}
		if (!my_context->actiontaken) {
			printf("  no actions taken; keeping message.\n");
			my_keep(NULL, my_context);
		}
	}

	/* At this point the callbacks are called from within libSieve. */

	exitcode |= my_context->error_parse;
	exitcode |= my_context->error_runtime;

freesieve:
	res = sieve2_free(&sieve2_context);
	if (res != SIEVE2_OK) {
		printf("Error %d when calling sieve2_free: %s\n",
			res, sieve2_errstr(res));
		exitcode = 1;
	}

	if (my_context->m_buf) free(my_context->m_buf);
	if (my_context->s_buf) free(my_context->s_buf);

	if (my_context) free(my_context);

endnofree:
	if (beenhere)
		return exitcode;
	beenhere = 1;
	return 0;
}

/* END OF THE EXAMPLE */

