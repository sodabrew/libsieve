<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'about.' );
 $smarty->assign( 'leftcontent', array(
	array( 'a library for parsing, sorting and filtering your mail.',
	'libSieve provides a library to interpret Sieve scripts, and to execute those scripts over a given set of messages. The return codes from the libSieve functions let your program know how to handle the message, and then it\'s up to you to make it so. libSieve makes no attempt to have knowledge of how SMTP, IMAP, or anything else work; just how to parse and deal with a buffer full of emails. The rest is up to you!' ),
	array( 'this is not for end users.',
	'Sorry, but I need to put this disclaimer right up front. The \'lib\' part in \'libSieve\' should be an indicator, but if you\'re still looking for a mail sorting program that\'s ready to run, you\'re in the wrong place! libSieve is simply one component of a potential mail sorting system, and it\'s a component that takes a lot of pain away from a developer who\'d like to write his own mail sorting program but doesn\'t want to reinvent a sorting language or write a parsing grammar.' ),
	array( 'history.',
	'Sieve was developed by Carnegie Mellon University, in Pittsburgh, PA. Since they wanted to write a complete mail server based entirely on Internet RFC standards, they started with SMTP, then POP and IMAP, and so on. One day, someone asked if they could sort their mail automatically. But there were no RFC\'s for mail sorting languages. So they wrote one! And then a library to make it work, and then nestled it tightly into the Cyrus project and nobody else wanted to bother trying to get that library out of there and available for public consumption. And that\'s where libSieve fits in :-)' ),
	) );

 $smarty->assign( 'righttitle', 'news.' );
 $smarty->assign( 'rightcontent', array(
 	array( 'December 2003: 2.2.0pre4',
	'I\'m proud to announce that libSieve 2.2.0pre4 has been released!
Some minor API changes are still expected before the final 2.2.0 release, but we\'re
now making them in much more controlled ways than during the heddy days of full
overhauls just a few months ago.' ),
	array( 'December 2003: DBMail 2.0 alpha 2',
	'Well, I\'m pre-announcing it, but the DBMail 2.0 development
has been progressing nicely, and libSieve support is soon to be added to CVS. After
some work on stabilizing the source base, another pre-release will be made which
may likely include much of the libSieve interface code.' ),
	) );
 $smarty->assign( 'rightlinks', array(
 	array( 'DBMail', 'http://dbmail.org/' ),
	) );


 $smarty->display( 'tweedy.tpl' );

?>
