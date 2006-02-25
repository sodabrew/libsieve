<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'example.' );
 $smarty->assign( 'leftcontent', array(
 	array( '', '<pre>' . read_file( 'example.c' ) . '</pre>' )
	) );

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
