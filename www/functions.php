<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'example.' );
 $smarty->assign( 'leftcontent', array(
        array( '',
        <<<ENDOFPRE

<h1>Sieve 2 API: Functions</h1>

<div class="code"> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_alloc</font>(<font class="type">sieve2_context_t</font> **<font class="arg">c</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_free</font>(<font class="type">sieve2_context_t</font> **<font class="arg">c</font>);</div>




<p> Allocates and frees the basic context which carries through all of the
functions and callbacks in libSieve. At this time, the core parsers are not
thread-safe; <b>only one instance may be allocated per-process</b>.

<div class="code"> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_callbacks</font>(<font class="type">sieve2_context_t</font> *<font class="arg">c</font>, <font class="type">sieve2_callback_t</font> *<font class="arg">callbacks</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_listextensions</font>(<font class="type">sieve2_context_t</font> *<font class="arg">c</font>);</div>




<p> Registers a table of callbacks. See the structures page for details.
After a table of callbacks is registered, the extensions for which callbacks
have been registered will be listed by sieve2_listextensions.

<div class="code"> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_validate</font>(<font class="type">sieve2_action_t</font> *<font class="arg">c</font>, <font class="type">void</font> *<font class="arg">user_data</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_execute</font>(<font class="type">sieve2_action_t</font> *<font class="arg">c</font>, <font class="type">void</font> *<font class="arg">user_data</font>);</div>




<p> Validate a script and execute a script over a message. Validation will
only call the getscript callback, while execution will call getscript and
either getallheaders or getheader, then call the appropriate action callbacks.
The user_data you provide here will be passed into each of the callbacks.

<p> The way to use this is to set up your own structure which contains
information the script and message you are currently working with. As the
callbacks are called, your functions, which know about your structure, can
figure out what they should be doing.

<div class="code"> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_getvalue_int</font>(<font class="type">sieve2_context_t</font> *<font class="arg">c</font>, <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="arg">name</font>); <br> <font class="qual">extern</font> <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="func">sieve2_getvalue_string</font>(<font class="type">sieve2_context_t</font> *<font class="arg">c</font>, <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="arg">name</font>); <br> <font class="qual">extern</font> <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> * <font class="qual">const</font> <font class="func">sieve2_getvalue_stringlist</font>(<font class="type">sieve2_context_t</font> *<font class="arg">c</font>, <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="arg">name</font>);</div>





<p> The getvalue family of functions allow you to retrieve information
about the callback being called. All of the memory returned by these
functions are managed by libSieve and will be freed by calling sieve2_free.

<p> See the structures page for a listing of value names available to each
callback.

<div class="code"> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_setvalue_int</font>(<font class="type">sieve2_context_t</font> *<font class="arg">c</font>, <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="arg">name</font>, <font class="type">int</font> <font class="arg">value</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_setvalue_string</font>(<font class="type">sieve2_context_t</font> *<font class="arg">c</font>, <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="arg">name</font>, <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="arg">value</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_setvalue_stringlist</font>(<font class="type">sieve2_context_t</font> *<font class="arg">c</font>, <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="arg">name</font>, <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> * <font class="qual">const</font> <font class="arg">value</font>);</div>





<p> The setvalue family of functions allows you to return values into
libSieve from your callbacks. This is your memory, and must be freed after
calling sieve2_free.

<p> See the structures page for a listing of value names available to each
callback.

<div class="code"> <font class="qual">extern</font> <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="func">sieve2_errstr</font>(<font class="qual">const</font> <font class="type">int</font> <font class="arg">code</font>);</div>


<p> Convert an error code to a generic description of the error.
Detailed error reports are found in the sieve2_error array. Do not free the
returned string, it is static.

<div class="code"> <font class="qual">extern</font> <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="func">sieve2_credits</font>(<font class="type">void</font>); <br> <font class="qual">extern</font> <font class="qual">const</font> <font class="type">char</font> * <font class="qual">const</font> <font class="func">sieve2_license</font>(<font class="type">void</font>);</div>



<p> Get a list of Credits about who writes libSieve
and a brief rundown on the License under which
libSieve is distributed. Do not free the returned string, it is static.

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
