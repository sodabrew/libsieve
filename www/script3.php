<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'script.three.' );
 $smarty->assign( 'leftcontent', array(
	array( '',
	<<<ENDOFPRE
<pre>
##############################################
# Submitted by Tony Maro
# http://www.maro.net/tony
# Use and abuse this script as you will
# I'm not responsible for what it does...
#
# Save this script in your home directory.
# Install this script with the following command,
# replacing "thisfile" and "yourname" with the appropriate
# information:
#
# installsieve -i thisfile -m PLAIN -u yourname localhost
#
#
require "fileinto";
require "reject";
#
# Circle MUD mailing list list
# All mail from the list has "[CIRCLE]" in the subject
# Place all these in the "Circle List" folder
# I could filter on the mail list senders e-mail as it's always
# the same, but this way I even catch personal replies that come
# directly from a user to me
if header :contains "Subject" "[CIRCLE]" {
        fileinto "INBOX.Circle List";
}
#
# "shockwave" e-mail virus - just reject it
#
if header :contains "Subject" "A great Shockwave flash movie" {
        reject "Possible virus?  Check your system!";
}
#
# Get a lot of junk from dial-up uu.net accounts
# Make sure you create a Junk folder under your INBOX
# I like this one because it catches them even if they
# relay their crap through some international open
# mail relay
#
if header :contains "Received" ".da.uu.net" {
        fileinto "INBOX.Junk";
}
#
# If the mail is listed as TO someone at bigfoot.com
# Then just reject it because it's spam (my experience anyway)
#
if header :contains "To" "@bigfoot.com" {
        reject "Yeah, right.  Bugoff, hosier!";
}
#
# If the mail is not directed to me put in the junk folder
# be sure to replace yourname@youraddress.com with the
# appropriate information
# Took me a while to figure out how to do NOT statements... :-}
#
if anyof ( not address :all :contains ["To", "Cc", "Bcc"] "yourname@youraddress.com" ) {
        fileinto "INBOX.Junk";
}
#
# Everything that makes it to here ends up in the INBOX
########################################################
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
