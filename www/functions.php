<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'example.' );
 $smarty->assign( 'leftcontent', array(
        array( '',
        <<<ENDOFPRE

<h1>Sieve 2 API: Functions</h1>

<div class="code"> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_support_alloc</font>(<font class="type">sieve2_support_t</font> **<font class="arg">p</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_support_free</font>(<font class="type">sieve2_support_t</font> *<font class="arg">p</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_support_register</font>(<font class="type">sieve2_support_t</font> *<font class="arg">p</font>, <font class="type">void</font> *<font class="arg">thing</font>, <font class="type">int</font> <font class="arg">type</font>);</div>





The support functions are used to build up a structure which indicates
what actions and extensions are supported by the client application.
An application could potentially create several "personalities" with
different support structures, perhaps to allow an administrator to limit
certain actions, such as vacation and notification, to certain users.
In general, however, only one support structure is needed and it can
be safely shared among multiple threads of the client program.

<div class="code"> #define SIEVE2_MESSAGE_SIZE <br> #define SIEVE2_MESSAGE_HEADER <br> #define SIEVE2_MESSAGE_ENVELOPE <br> <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_message_alloc</font>(<font class="type">sieve2_message_t</font> **<font class="arg">m</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_message_free</font>(<font class="type">sieve2_message_t</font> *<font class="arg">m</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_message_register</font>(<font class="type">sieve2_message_t</font> *<font class="arg">m</font>, <font class="type">void</font> *<font class="arg">thing</font>, <font class="type">int</font> <font class="arg">type</font>);</div>
<p> The message functions are used to build up a structure holding key information
about the message. The most important thing happening is parsing the message
header into its constituent fields. Other message details currently supported
are the size of the entire message (not just the size of the headers) and the
envelope recipient (which is may be different than the To: header field).

<p> There are plans to accept a pre-parsed table of headers. This will be particularly
useful for client applications which store their headers as parsed structures.
The format for this data structure is still being discussed, and in particular,
finding a relatively neutral format which is not dependant upon any third party
applications and yet is easily transformed to and from those third party structures.

<div class="code"> #define SIEVE2_ACTION_REDIRECT <br> #define SIEVE2_ACTION_REJECT <br> #define SIEVE2_ACTION_DISCARD <br> #define SIEVE2_ACTION_FILEINTO <br> #define SIEVE2_ACTION_KEEP <br> #define SIEVE2_ACTION_NOTIFY <br> <br> #define SIEVE2_ACTION_NULL <br> #define SIEVE2_ACTION_NONE <br> #define SIEVE2_ACTION_VACATION <br> #define SIEVE2_ACTION_SETFLAG <br> #define SIEVE2_ACTION_ADDFLAG <br> #define SIEVE2_ACTION_REMOVEFLAG <br> #define SIEVE2_ACTION_MARK <br> #define SIEVE2_ACTION_UNMARK <br> #define SIEVE2_ACTION_DENOTIFY <br> <br> #define SIEVE2_ACTION_ALL <br> <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_action_alloc</font>(<font class="type">sieve2_action_t</font> **<font class="arg">a</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_action_free</font>(<font class="type">sieve2_action_t</font> *<font class="arg">a</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_action_next</font>(<font class="type">sieve2_action_t</font> **<font class="arg">a</font>, <font class="type">int</font> *<font class="arg">code</font>, <font class="type">void</font> **<font class="arg">context</font>);</div>
<p> The action functions are used to retrieve the results of sieve2_execute(). There
is no external registration function (there is a sort of internal one, though) but
rather a the sieve2_action_next() function which helps to step through the list of
resulting actions. The action code is placed into the variable pointed to by the
code argument and a pointed to the corresponding context structure is placed into the
variable pointed to by context. Only structures which the client application has
registered support for will be returned; in the event that this restriction
is violated, the client should not attempt to "guess" the format of the returned
structure. The returned structures should not be freed by the client; they are all
freed by sieve2_action_free().

<div class="code"><br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_error_alloc</font>(<font class="type">sieve2_error_t</font> **<font class="arg">e</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_error_free</font>(<font class="type">sieve2_error_t</font> *<font class="arg">e</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_error_next</font>(<font class="type">sieve2_error_t</font> **<font class="arg">e</font>, <font class="type">int</font> *<font class="arg">code</font>, <font class="type">void</font> **<font class="arg">context</font>);</div>





<p> The error functions are used to retrieve error codes resulting from mistakes
in a script found either during validation with sieve2_validate or execution
with sieve2_execute.


<div class="code"> #define SIEVE2_SCRIPT_SIZE <br> #define SIEVE2_SCRIPT_CALLBACK <br> #define SIEVE2_SCRIPT_CHAR_ARRAY <br> #define SIEVE2_SCRIPT_FILE_POINTER <br> #define SIEVE2_SCRIPT_INCLUDE_CALLBACK <br> <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_script_alloc</font>(<font class="type">sieve2_script_t</font> **<font class="arg">s</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_script_free</font>(<font class="type">sieve2_script_t</font> *<font class="arg">s</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_script_register</font>(<font class="type">sieve2_script_t</font> *<font class="arg">s</font>, <font class="type">void</font> *<font class="arg">thing</font>, <font class="type">int</font> <font class="arg">type</font>);</div>
<div class="code"> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_interp_alloc</font>(<font class="type">sieve2_interp_t</font> **<font class="arg">t</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_interp_free</font>(<font class="type">sieve2_interp_t</font> *<font class="arg">t</font>); <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_interp_register</font>(<font class="type">sieve2_interp_t</font> *<font class="arg">t</font>, <font class="type">void</font> *<font class="arg">thing</font>, <font class="type">int</font> <font class="arg">type</font>);</div>





Allocate an interp struct to hold parser/scanner state.
Once flex provides reentrantcy, all builds will use it.

<div class="code"> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_validate</font>( <br> &nbsp; &nbsp; <font class="type">sieve2_interp_t</font> *<font class="arg">t</font>, <font class="type">sieve2_script_t</font> *<font class="arg">s</font>, <br> &nbsp; &nbsp; <font class="type">sieve2_support_t</font> *<font class="arg">p</font>, <font class="type">sieve2_error_t</font> *<font class="arg">e</font>); <br> <br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_execute</font>( <br> &nbsp; &nbsp; <font class="type">sieve2_interp_t</font> *<font class="arg">t</font>, <font class="type">sieve2_script_t</font> *<font class="arg">s</font>, <br> &nbsp; &nbsp; <font class="type">sieve2_support_t</font> *<font class="arg">p</font>, <font class="type">sieve2_error_t</font> *<font class="arg">e</font>, <br> &nbsp; &nbsp; <font class="type">sieve2_message_t</font> *<font class="arg">m</font>, <font class="type">sieve2_action_t</font> *<font class="arg">a</font>);</div>
Validate a script for syntax and feature support.
Execute a script on a message, producing an action list.

<div class="code"><br> <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_extensions_listconst</font>(<font class="type">char</font> **<font class="arg">extensions</font>); <font class="qual">extern</font> <font class="type">int</font> <font class="func">sieve2_extensions_listsupport</font>(<font class="type">sieve2_support_t</font> *<font class="arg">p</font>, <font class="type">char</font> **<font class="arg">extensions</font>);</div>




Get a space separated list of supported extensions.
If a sieve2_support struct is passed, only those extensions will appear.
If NULL is passed in the support argument, all extensions that the
interpreter knows about will appear. The caller must call free(extensions).

<div class="code"> <font class="qual">extern</font> <font class="qual">const</font> <font class="type">char</font> *<font class="func">sieve2_errstr</font>(<font class="qual">const</font> <font class="type">int</font> <font class="arg">code</font>);</div>


Convert an error code to a generic description of the error.
Detailed error reports are found in the sieve2_error array.

<div class="code"> <font class="qual">extern</font> <font class="qual">const</font> <font class="type">char</font> *<font class="func">sieve2_credits</font>(<font class="type">void</font>); <br> <font class="qual">extern</font> <font class="qual">const</font> <font class="type">char</font> *<font class="func">sieve2_license</font>(<font class="type">void</font>);</div>



Get a list of Credits about who writes libSieve
and a brief rundown on the License under which
libSieve is distributed.

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
        array( 'Usage Example 1', 'example1.php' ),
        array( 'Usage Example 2', 'example2.php' ),
        ) );

 $smarty->display( 'tweedy.tpl' );

?>
