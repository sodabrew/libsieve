<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'example.' );
 $smarty->assign( 'leftcontent', array(
        array( '',
        <<<ENDOFPRE

<h1>Sieve 2 API: Structures</h1>

<div class="code"> <font class="qual">typedef</font> <font class="type">struct</font> <font class="type">sieve2_context</font> <font class="type">sieve2_context_t</font>; <br> &nbsp; &nbsp; <font class="qual">typedef</font> <font class="type">int</font> <font class="func">(*sieve2_callback_func)</font> ( <br> &nbsp; &nbsp; <font class="qual">sieve2_context_t</font> * <font class="arg">sieve2_context</font>, <br> &nbsp; &nbsp; <font class="qual">void</font> * <font class="arg">user_data</font> <br> ); <br> <br> <font class="qual">typedef</font> <font class="type">struct</font> { <br> &nbsp; &nbsp; <font class="type">sieve2_values_t</font> <font class="arg">value</font>; <br> &nbsp; &nbsp; <font class="type">sieve2_callback_func</font> <font class="arg">func</font>; <br> } <font class="type">sieve2_callback_t</font>;</div>
<p> There is only one opaque type for you to worry about: sieve2_context_t.
Everything that happens in an instance of the interpreter is contained
inside of the context opaque structure.

<p> There are three user-accessible data types: sieve2_values_t,
sieve2_callback_func and sieve2_callback_t. These data types allow
you to specify your callbacks, prototype your callback functions, and
register your callbacks to their call codes, respectively.

<div class="code"> <font class="qual">typedef</font> <font class="type">enum</font> { <br> &nbsp; &nbsp; <font class="arg">SIEVE2_VALUE_FIRST</font> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_REDIRECT</font> <i>address (string)</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_REJECT</font> <i>message (string)</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_DISCARD</font> <i>none</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_FILEINTO</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: mailbox (string) imapflags (stringlist). set: none.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_KEEP</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: imapflags (stringlist). set: none.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_NOTIFY</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: active (int) id (string) method (string) options (stringlist) priority (string) message (string). set: none.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_DENOTIFY</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: active (int) id (string) method (string) options (stringlist) priority (string) message (string). set: none.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_VACATION</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: toaddress (string) fromaddress (string) subject (string) message (string) mime (int). hash (string) days (int). min (int) max (int).</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_SETFLAG</font> <i>imapflags (stringlist)</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_ADDFLAG</font> <i>get: imapflags (stringlist). set: none.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_REMOVEFLAG</font> <i>get: imapflags (stringlist). set: none.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_MARK</font> <i>none</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_UNMARK</font> <i>none</i> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ERRCALL_RUNTIME</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: message. set: none.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ERRCALL_PARSE</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: message (string) lineno (int). set: none.</i> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_SCRIPT_GETSCRIPT</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: name (string) path (string). set: script (string).</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_SCRIPT_GETSIZE</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: name (string) path (string). set: size (int).</i> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETHEADER</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: header (string). set: body (string).</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETALLHEADERS</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: none. set: allheaders (string).</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETENVELOPE</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: env (string). set: from (string) to (string).</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETSIZE</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: none. set: size (int).</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETBODY</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: none. set: body (string).</i> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_VALUE_LAST</font> <br> } <font class="type">sieve2_values_t</font>;</div>
<p> Each of these call codes can be registered to a callback function.
When the callback function is called, it finds out the details of
what is being asked of it using the functions sieve2_getvalue...()
and responds with sieve2_setvalue...(). The value key names for
each callback are listed in italics inlined into the enum above.

ENDOFPRE
        ) ) );

 $smarty->assign( 'righttitle', 'notes.' );
 $smarty->assign( 'rightcontent', array(
        array(
        <<<ENDOFPRE
The Sieve 2 API is an extensible API designed to ride through revisions
in the underlying implementation and through updates to the Sieve RFC
and various extensions, as they move from drafts towards full RFC&#39;s.

The API has three main parts: the incomplete opaque internal types, the
complete and user accessible external structures and the function calls.
ENDOFPRE
        ) ) );
 $smarty->assign( 'rightlinks', array(
        array( 'API Functions', 'functions.php' ),
        array( 'API Structures', 'structures.php' ),
        array( 'Example App', 'example.php' ),
        ) );

 $smarty->display( 'tweedy.tpl' );

?>
