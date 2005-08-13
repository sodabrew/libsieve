<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'example.' );
 $smarty->assign( 'leftcontent', array(
        array( '',
        <<<ENDOFPRE

<h1>Sieve 2 API: Structures</h1>

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_context</font> <font class="type">sieve2_context_t</font>; <br> &nbsp; &nbsp; <font class="qual">typedef</font> <font class="type">int</font> <font class="func">(*sieve2_callback_func)</font> ( <br> &nbsp; &nbsp; <font class="qual">sieve2_context_t</font> * <font class="arg">sieve2_context</font>, <br> &nbsp; &nbsp; <font class="qual">void</font> * <font class="arg">user_data</font> <br> ); <br> <br> <font class="qual">typedef</font> <font class="qual">struct</font> { <br> &nbsp; &nbsp; <font class="type">sieve2_values_t</font> <font class="arg">value</font>; <br> &nbsp; &nbsp; <font class="type">sieve2_callback_func</font> <font class="arg">func</font>; <br> } <font class="type">sieve2_callback_t</font>;</div>
<p> There is only one opaque type for you to worry about: sieve2_context_t.
Everything that happens in an instance of the interpreter is contained
inside of the context opaque structure.

<p> There are three user-accessible data types: sieve2_values_t,
sieve2_callback_func and sieve2_callback_t. These data types allow
you to specify your callbacks, prototype your callback functions, and
register your callbacks to their call codes, respectively.

<div class="code"> <font class="qual">typedef</font> <font class="type">enum</font> { <br> &nbsp; &nbsp; <font class="arg">SIEVE2_VALUE_FIRST</font> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_REDIRECT</font> <i>address</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_REJECT</font> <i>message</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_DISCARD</font> <i>none</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_FILEINTO</font> <i>mailbox</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_KEEP</font> <i>none</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_NOTIFY</font> <i>bunch of these...</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_DENOTIFY</font> <i>bunch of these...</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_VACATION</font> <i>bunch of these...</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_SETFLAG</font> <i>imapflags</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_ADDFLAG</font> <i>imapflags</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_REMOVEFLAG</font> <i>imapflags</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_MARK</font> <i>none</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ACTION_UNMARK</font> <i>none</i> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ERRCALL_RUNTIME</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: message. set: none.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_ERRCALL_PARSE</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: message lineno. set: none.</i> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_SCRIPT_GETSCRIPT</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: name path. set: script.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_SCRIPT_GETSIZE</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: name path. set: size.</i> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETHEADER</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: header. set: body.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETALLHEADERS</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: none. set: allheaders.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETENVELOPE</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: env. set: from to.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETSIZE</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: none. set: size.</i> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_MESSAGE_GETBODY</font> <br> &nbsp; &nbsp; &nbsp; &nbsp; <i>get: none. set: body.</i> <br> <br> &nbsp; &nbsp; <font class="arg">SIEVE2_VALUE_LAST</font> <br> } <font class="type">sieve2_values_t</font>;</div>
<p> Each of these call codes can be registered to a callback function.
When the callback function is called, it finds out the details of
what is being asked of it using the functions sieve2_getvalue...()
and responds with sieve2_setvalue...(). The value key names for
each callback are listed in italics inlined into the enum above.

 <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_vacation_context</font> {
<br> &nbsp; &nbsp; <font class="type">int</font> <font class="arg">min_response</font>; /* 0 -> defaults to 3 */
<br> &nbsp; &nbsp; <font class="type">int</font> <font class="arg">max_response</font>; /* 0 -> defaults to 90 */
<br> &nbsp; &nbsp;
<br> &nbsp; &nbsp; /* In Sieve 2, send_response is right here */
<br> &nbsp; &nbsp; <font class="qual">struct</font> {
<br> &nbsp; &nbsp; &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">addr</font>;
<br> &nbsp; &nbsp; &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">fromaddr</font>;
<br> &nbsp; &nbsp; &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">subj</font>;
<br> &nbsp; &nbsp; &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">msg</font>;
<br> &nbsp; &nbsp; &nbsp; &nbsp; <font class="type">int</font> <font class="arg">mime</font>;
<br> &nbsp; &nbsp; } <font class="arg">send</font>;
<br>
<br> &nbsp; &nbsp; /* In Sieve 2, check_response is right here */
<br> &nbsp; &nbsp; <font class="qual">struct</font> {
<br> &nbsp; &nbsp; &nbsp; &nbsp; <font class="qual">unsigned</font> <font class="type">char</font> *<font class="arg">hash</font>;
<br> &nbsp; &nbsp; &nbsp; &nbsp; <font class="type">int</font> <font class="arg">len</font>;
<br> &nbsp; &nbsp; &nbsp; &nbsp; <font class="type">int</font> <font class="arg">days</font>;
<br> &nbsp; &nbsp; } <font class="arg">check</font>;
<br> } <font class="type">sieve2_vacation_context_t</font>;
        )

The vacation structure is used to reply to a message to let the sender
know that the recipient is out of town for a while. The client application
needs to check to see if the particular sender has already been sent a
vacation reply within the time frame indicated by vacation.check.days.
If yes, give up. If not, the members of vacation.send should be used to
build up a message. The members of vacation.send are pretty self-explanatory,
except for the mime number. I have no idea what that is.

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_imapflags_context</font> { <br> &nbsp; &nbsp; <font class="type">char</font> **<font class="arg">flag</font>; /* NULL -> defaults to \flagged */ <br> &nbsp; &nbsp; <font class="type">int</font> <font class="arg">nflags</font>; <br> } <font class="type">sieve2_imapflags_context_t</font>;</div>






The imapflags structure holds a list of imap flag strings. Each carries
the format \Flag and comforms to recent revisions of the IMAP standard.
Probably the easiest thing to do is loop through the flags, compare them
to the known flags that your application supports, and mark those that
match up.

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_redirect_context</font> { <br> &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">addr</font>; <br> } <font class="type">sieve2_redirect_context_t</font>;</div>





The redirect structure indicates where the message should be sent to next.

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_reject_context</font> { <br> &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">msg</font>; <br> } <font class="type">sieve2_reject_context_t</font>;</div>





The reject structure gives a message to return to the message sender,
generally indicating why the message was rejected. The message itself
may or may not be included as an attachment; it is generally recommended
to send just the headers, if not only the subject line.

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_fileinto_context</font> { <br> &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">mailbox</font>; <br> &nbsp; &nbsp; <font class="type">sieve2_imapflags_context_t</font> *<font class="arg">imapflags</font>; <br> } <font class="type">sieve2_fileinto_context_t</font>;</div>






The fileinto structure indicates the mailbox into which the message should
be filed. In general, the mailbox should be created if it does not already
exist, but this behavior is up to the client application, possibly user
preferences or system policy, or whatever else.

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_keep_context</font> { <br> &nbsp; &nbsp; <font class="type">sieve2_imapflags_context_t</font> *<font class="arg">imapflags</font>; <br> } <font class="type">sieve2_keep_context_t</font>;</div>





The keep structure itself indicates that the message should be kept. It
further contains an imapflags structure that indicates the flags that
that should be set on the kept message. See the imapflags section above.

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_notify_context</font> { <br> &nbsp; &nbsp; <font class="type">int</font> <font class="arg">isactive</font>; <br> &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">id</font>; <br> &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">method</font>; <br> &nbsp; &nbsp; <font class="type">char</font> **<font class="arg">options</font>; <br> &nbsp; &nbsp; <font class="qual">const</font> <font class="type">char</font> *<font class="arg">priority</font>; <br> &nbsp; &nbsp; <font class="type">char</font> *<font class="arg">message</font>; <br> &nbsp; &nbsp; <font class="qual">struct</font> <font class="type">sieve2_notify_context</font> *<font class="arg">next</font>; <br> } <font class="type">sieve2_notify_context_t</font>;</div>
The notify structure is in fact a linked list of notify structures. It is
up to the client application to traverse the list. The next member will
be NULL when the end has been reached; just a typical linked list. The
notification extension is fairly involved, so rather than trying to explain
it all here, do please read the latest draft of the extension.

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_error_parse_context</font> { <br> &nbsp; &nbsp; <font class="type">int</font> <font class="arg">lineno</font>; <br> &nbsp; &nbsp; <font class="qual">const</font> <font class="type">char</font> *<font class="arg">msg</font>; <br> } <font class="type">sieve2_error_parse_context_t</font>;</div>






The parse error structure contains a descriptive error message indicating
what went wrong while parsing the script, headers and email addresses
therein. If the parse error was in the script or the headers, the line
number member will be non-zero.

At this time, no translation facility is in place, so the message
will be in English.

<div class="code"> <font class="qual">typedef</font> <font class="qual">struct</font> <font class="type">sieve2_error_execute_context</font> { <br> &nbsp; &nbsp; <font class="qual">const</font> <font class="type">char</font> *<font class="arg">msg</font>; <br> } <font class="type">sieve2_error_execute_context_t</font>;</div>





The execution error structure contains a descriptive error message
indicating what went wrong during execution of the script. At this time,
no translation facility is in place, so the message will be in English.

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
