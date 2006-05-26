<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'about.' );
 $smarty->assign( 'leftcontent', array(
	array( 'A library for parsing, sorting and filtering your mail.',
	'libSieve provides a library to interpret Sieve scripts, and to execute those scripts over a given set of messages. The return codes from the libSieve functions let your program know how to handle the message, and then it\'s up to you to make it so. libSieve makes no attempt to have knowledge of how SMTP, IMAP, or anything else work; just how to parse and deal with a buffer full of emails. The rest is up to you!' ),
	array( 'This is not for end users!',
	'Up front disclaimer: the \'lib\' part in \'libSieve\' should be an indicator, but if you\'re still looking for a mail sorting program that\'s ready to run, you\'re in the wrong place! libSieve is simply one component of a potential mail sorting system, and it\'s a component that takes a lot of pain away from a developer who\'d like to write his own mail sorting program but doesn\'t want to reinvent a sorting language or write a parsing grammar.' ),
	array( 'History.',
	'Sieve was developed by Carnegie Mellon University, in Pittsburgh, PA. Since they wanted to write a complete mail server based entirely on Internet RFC standards, they started with SMTP, then POP and IMAP, and so on. One day, someone asked if they could sort their mail automatically. But there were no RFC\'s for mail sorting languages. So they wrote one! And then a library to make it work, and then nestled it tightly into the Cyrus project and nobody else wanted to bother trying to get that library out of there and available for public consumption. And that\'s where libSieve fits in :-)' ),
	array( 'Downstream.',
	'<a href="http://dbmail.org/">DBMail</a> is a mail system based on database storage. DBMail provides IMAP and POP3 access to email, and integrates well with popular SMTP servers. During message delivery, libSieve can be used to sort and filter each user\'s email according to their own Sieve scripts.' ),
	) );


 $smarty->assign( 'righttitle', 'news.' );
 $smarty->assign( 'rightcontent', array(
 	array( 'Version numbers are staggered with odd minor numbers denoting experimental / development versions. API calls will be frozen along versions 2.x where x is an even number.' ),
 	array( 'February 2006: libSieve 2.1.10',
	'Fixed sieve2_listextensions.
	' ),
 	array( 'February 2006: libSieve 2.1.9',
	'Fixed subaddress tests, and the vacation and getenvelope callbacks. Added a few more debugging messages.
	' ),
 	array( 'February 2006: libSieve 2.1.8',
	'Fixed a memory allocation bug that was preventing the library from being reused after sieve2_free was called.
	' ),
 	array( 'August 2005: libSieve 2.1.7',
	'I\'ve rewritten the API, and I really like it this time. Take a look at the documentation pages and see what you think!
	' ),
 	array( 'November 2004: libSieve 2.1.5',
	'In a move to confuse and astound, I am re-releasing libSieve 2.2.0_pre3 as 2.1.5. I dragged my feet for almost a year trying to figure out how I was going to fix the API in one fell swoop, release 2.2.0 final, and save the world. All that is gone now. 
	' ),
	) );

 $smarty->assign( 'rightlinks', '' );

 $smarty->display( 'tweedy.tpl' );

?>
