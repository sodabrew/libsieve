#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

#ifndef YYSTYPE
typedef union {
    int nval;
    char *sval;
    stringlist_t *sl;
    test_t *test;
    testlist_t *testl;
    commandlist_t *cl;
    struct vtags *vtag;
    struct aetags *aetag;
    struct htags *htag;
    struct ntags *ntag;
    struct dtags *dtag;
} yystype;
# define YYSTYPE yystype
#endif
# define	NUMBER	257
# define	STRING	258
# define	IF	259
# define	ELSIF	260
# define	ELSE	261
# define	REJCT	262
# define	FILEINTO	263
# define	REDIRECT	264
# define	KEEP	265
# define	STOP	266
# define	DISCARD	267
# define	VACATION	268
# define	REQUIRE	269
# define	SETFLAG	270
# define	ADDFLAG	271
# define	REMOVEFLAG	272
# define	MARK	273
# define	UNMARK	274
# define	NOTIFY	275
# define	DENOTIFY	276
# define	ANYOF	277
# define	ALLOF	278
# define	EXISTS	279
# define	SFALSE	280
# define	STRUE	281
# define	HEADER	282
# define	NOT	283
# define	SIZE	284
# define	ADDRESS	285
# define	ENVELOPE	286
# define	COMPARATOR	287
# define	IS	288
# define	CONTAINS	289
# define	MATCHES	290
# define	REGEX	291
# define	OVER	292
# define	UNDER	293
# define	ALL	294
# define	LOCALPART	295
# define	DOMAIN	296
# define	USER	297
# define	DETAIL	298
# define	DAYS	299
# define	ADDRESSES	300
# define	SUBJECT	301
# define	MIME	302
# define	METHOD	303
# define	ID	304
# define	OPTIONS	305
# define	LOW	306
# define	NORMAL	307
# define	HIGH	308
# define	MESSAGE	309


extern YYSTYPE sievelval;

#endif /* not BISON_Y_TAB_H */
