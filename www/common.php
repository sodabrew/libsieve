<?php
 $smarty->template_dir ='../Smarty/templates/';
 $smarty->compile_dir = '../Smarty/templates_c/';
 $smarty->config_dir =  '../Smarty/configs/';
 $smarty->cache_dir =   '../Smarty/cache/';

 $smarty->assign( 'title', 'libSieve: a library for parsing, sorting and filtering your mail' );
 $smarty->assign( 'lefthead', 'lib' );
 $smarty->assign( 'righthead', 'Sieve' );

 // This should be useful as a counter
 $smarty->assign( 'i', 0 );

 $smarty->assign( 'thispage', substr($HTTP_SERVER_VARS['PHP_SELF'], 1) );

 $smarty->assign( 'toplinks', array(
 	array( 'home', 'index.php' ), 
	array( 'api docs', 'functions.php' ), 
 	array( 'scripts', 'script1.php' ), 
 	array( 'license', 'license.php' ), 
	array( 'download', 'http://sf.net/project/showfiles.php?group_id=66233' ), 
	array( 'sourceforge', 'http://sf.net/projects/libsieve' ), 
	) );

 $smarty->assign( 'righttitle', 'stuff.' );
 $smarty->assign( 'rightlinks', array(
 	array( 'example code', 'example.php', 'Interfacing with your own code.' ),
 	array( 'example scripts', 'script1.php', 'Some sample user scripts.' ),
 	array( 'license', 'license.php', 'Yes, there are license terms...' ),
	) );

 $smarty->assign( 'links', array(
 	array( 'Sieve Homepage', 'http://sieve.info/' ),
 	array( 'Cyrus Project', 'http://asg.web.cmu.edu/cyrus/' ),
	array( 'GNU Mailutils', 'http://www.gnu.org/software/mailutils/' ),
	array( 'Network World Chaos article', 'http://www.nwfusion.com/news/2002/0715chaos.html' ),
	array( 'Network World Gearhead article', 'http://www.nwfusion.com/columnists/2002/0729gearhead.html' ),
	) );

?>
