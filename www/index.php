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
	'Sieve was developed by Project Cyrus at Carnegie Mellon University. Since they wanted to write a complete mail server based entirely on Internet RFC standards, they started with SMTP, then POP and IMAP, and so on. One day, someone asked if they could sort their mail automatically. But there were no RFC\'s for mail sorting languages. So they wrote one! And then a library to make it work, and then nestled it tightly into the Cyrus mail server and nobody else wanted to bother trying to get that library out of there and available for public consumption. That\'s where libSieve fits in :-)' ),
	array( 'Downstream.',
	'<a href="http://dbmail.org/">DBMail</a> is a mail system based on database storage. DBMail provides IMAP and POP3 access to email, and integrates well with popular SMTP servers. During message delivery, libSieve can be used to sort and filter each user\'s email according to their own Sieve scripts.' ),
	) );


 $smarty->assign( 'righttitle', 'news.' );
 $smarty->assign( 'rightcontent', array(
 	array( 'Latest stable release: ...',
	'Well, we\'re almost there!' ),
 	array( 'Latest unstable release: <a href="http://prdownloads.sourceforge.net/libsieve/libsieve-2.1.10.tar.gz?download">libSieve 2.1.10</a>.',
	'Released February, 2006. Changes: '
		. '<ul><li>Fixed sieve2_listextensions.</li></ul>' ),
	) );

 $smarty->display( 'tweedy.tpl' );

?>
