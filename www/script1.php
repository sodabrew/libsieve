<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'script.one.' );
 $smarty->assign( 'leftcontent', array(
	array( '',
	<<<ENDOFPRE
<pre>
    if header :contains ["From"]  ["coyote"] {
        redirect "acm@frobnitzm.edu";
    } elsif header :contains "Subject" "$$$" {
        redirect "postmaster@frobnitzm.edu";
    } else {
        redirect "field@frobnitzm.edu";
    }
</pre>
ENDOFPRE
 	) ) );

 $smarty->assign( 'righttitle', 'scripts.' );
 $smarty->assign( 'rightlinks', array(
 	array( 'Script 1', 'script1.php' ),
 	array( 'Script 2', 'script2.php' ),
 	array( 'Script 3', 'script3.php' ),
	) );

 $smarty->display( 'tweedy.tpl' );

?>
