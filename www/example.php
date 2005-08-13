<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'example.' );
 $smarty->assign( 'leftcontent', array(
 	array( '',
	<<<ENDOFPRE
<pre>
int main(int argc, char *argv[])
{
    sieve2_message_t *m;
    sieve2_support_t *p;
    sieve2_script_t *s;
    sieve2_thread_t *t;
    sieve2_action_t *a;
    char *script = NULL, *message = NULL;
    int c, usage_error = 0;
    int res;
    struct stat m_stat;
    char *m_buf;
    char *s_buf;

    while ((c = getopt(argc, argv, "v:c")) != EOF)
	switch (c) {
	case 'v':
	    script = optarg;
	    break;
	case 'c':
	    test_comparator();
	    /* test_comparator exits for us */
	    break;
	default:
	    usage_error = 1;
	    break;
	}

    if (!script) {
	if ((argc - optind) < 2)
	    usage_error = 1;
	else {
	    message = argv[optind];
	    script = argv[optind+1];
	}
    }

    if (usage_error) {
	fprintf(stderr, "usage:\n");
	fprintf(stderr, "%s message script\n", argv[0]);
	fprintf(stderr, "%s -v script\n", argv[0]);
	exit(1);
    }

    res = read_script_file(script, &s_buf);
    if (res != SIEVE2_OK) {
	printf("read_script_file() returns %d\n", res);
	exit(1);
    }

    res = sieve2_thread_alloc(&t);
    if (res != SIEVE2_OK) {
	printf("sieve2_thread_alloc() returns %d\n", res);
	exit(1);
    }

    res = sieve2_action_alloc(&a);
    if (res != SIEVE2_OK) {
	printf("sieve2_action_alloc() returns %d\n", res);
	exit(1);
    }

    res = sieve2_support_alloc(&p);
    if (res != SIEVE2_OK) {
	printf("sieve2_support_alloc() returns %d\n", res);
	exit(1);
    }

    res = sieve2_support_register(p, SIEVE2_ACTION_FILEINTO);
    res = sieve2_support_register(p, SIEVE2_ACTION_REDIRECT);
    res = sieve2_support_register(p, SIEVE2_ACTION_REJECT);
    res = sieve2_support_register(p, SIEVE2_ACTION_NOTIFY);

    res = sieve2_script_alloc(&s);
    if (res != SIEVE2_OK) {
	printf("sieve2_script_alloc() returns %d\n", res);
	exit(1);
    }

    res = sieve2_script_register(s, s_buf, SIEVE2_SCRIPT_CHAR_ARRAY);
    if (res != SIEVE2_OK) {
	printf("sieve2_script_parse() returns %d: %s\n", res, sieve2_errstr(res));
	exit(1);
    }

    if (message) {
	res = stat(message, &m_stat);
	if (res != 0) {
	    perror("fstat");
	}

        res = read_message_file(message, &m_buf);
        if (res != SIEVE2_OK) {
            printf("read_message_file() returns %d\n", res);
            exit(1);
        }
 
	res = sieve2_message_alloc(&m);
	if (res != SIEVE2_OK) {
	    printf("sieve2_message_alloc() returns %d\n", res);
	    exit(1);
	}

	res = sieve2_message_register(m, &m_stat.st_size, SIEVE2_MESSAGE_SIZE);
	res = sieve2_message_register(m, m_buf, SIEVE2_MESSAGE_HEADER);

	res = sieve2_execute(t, s, p, m, a);
	if (res != SIEVE2_OK) {
	    printf("sieve2_execute_script() returns %d\n", res);
	    exit(1);
	}
	
	res = unroll_action(a);
	if (res != SIEVE2_OK && res != SIEVE2_DONE ) {
	    printf("unroll_action() returns %d\n", res);
	    exit(1);
	}

	res = sieve2_message_free(m);
	if (res != SIEVE2_OK) {
	    printf("sieve2_message_free() returns %d\n", res);
	    exit(1);
	}

        /* These are built here, freed here */
        free(m_buf);
    }

    /* These are built here, freed here */
    free(s_buf);

    res = sieve2_support_free(p);
    if (res != SIEVE2_OK) {
	printf("sieve2_support_free() returns %d\n", res);
	exit(1);
    }

    res = sieve2_action_free(a);
    if (res != SIEVE2_OK) {
	printf("sieve2_action_free() returns %d\n", res);
	exit(1);
    }

    res = sieve2_script_free(s);
    if (res != SIEVE2_OK) {
	printf("sieve2_script_free() returns %d\n", res);
	exit(1);
    }

    res = sieve2_thread_free(t);
    if (res != SIEVE2_OK) {
	printf("sieve2_thread_free() returns %d\n", res);
	exit(1);
    }

    return 0;
}

int unroll_action(sieve2_action_t *a)
{
    int res = SIEVE2_OK;
    int code;
    void *action_context;

    while( res == SIEVE2_OK ) {
        res = sieve2_action_next(&a, &code, &action_context);
        if( res == SIEVE2_DONE ) {
            printf( "We've reached the end.\n" );
            break;
        } else if ( res != SIEVE2_OK ) {
            printf( "Error in action list.\n" );
            break;
        }
        printf( "Action code is: %d\n", code );
	switch( code ) {
            case SIEVE2_ACTION_REDIRECT:
                {
                sieve2_redirect_context_t *context
                        = (sieve2_redirect_context_t *)action_context;
                printf( "Action is REDIRECT: " );
                printf( "Destination is %s\n", context->addr);
                break;
                }
            case SIEVE2_ACTION_REJECT:
                {
                sieve2_reject_context_t *context
                        = (sieve2_reject_context_t *)action_context;
                printf( "Action is REJECT: " );
                printf( "Message is %s\n", context->msg);
                break;
                }
            case SIEVE2_ACTION_DISCARD:
                printf( "Action is DISCARD\n" );
                break;
            case SIEVE2_ACTION_FILEINTO:
                {
                sieve2_fileinto_context_t *context
                        = (sieve2_fileinto_context_t *)action_context;
                printf( "Action is FILEINTO: " );
                printf( "Destination is %s\n", context->mailbox);
                break;
                }
            case SIEVE2_ACTION_NOTIFY:
                {
                sieve2_notify_context_t *context
                        = (sieve2_notify_context_t *)action_context;
                printf( "Action is NOTIFY: " );
                printf( "Destination is %s\n", "FIXME: TODO");
                break;
                }
            case SIEVE2_ACTION_KEEP:
                printf( "Action is KEEP\n" );
                break;
            default:
                printf( "Unrecognized action code: %d\n", code );
                break;
	}
    }

    return res;
}
</pre>
ENDOFPRE
 	) ) );

 $smarty->assign( 'righttitle', 'notes.' );
 $smarty->assign( 'rightcontent', array(
 	array( 'This is example code for an implementation using the libSieve 2 API.' )
	) );
 $smarty->assign( 'rightlinks', array(
 	array( 'API Functions', 'functions.php' ),
 	array( 'API Structures', 'structures.php' ),
 	array( 'Example App', 'example.php' ),
	) );

 $smarty->display( 'tweedy.tpl' );

?>
