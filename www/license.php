<?php

 include( '../Smarty/libs/Smarty.class.php' );
 $smarty = new Smarty;
 include( 'common.php' );

 $smarty->assign( 'lefttitle', 'license.' );
 $smarty->assign( 'leftcontent', array(
 	array( '',
	<<<ENDOFPRE
<p>All new libSieve code, and the distribution as a whole, is covered
by the GNU (Lesser|Library) General Public License.

<p>This is the nifty MIT style license on the legacy Sieve portions.
<pre>
/***********************************************************
        Copyright 1998 by Carnegie Mellon University

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of Carnegie Mellon
University not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO
THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE FOR
ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
******************************************************************/
</pre>

ENDOFPRE
 	) ) );

 $smarty->assign( 'righttitle', 'notes.' );
 $smarty->assign( 'rightcontent', array(
 	array( '',
	<<<ENDOFPRE
<p>Older pieces of Sieve are under a basic no-fault, no-warranty license from CMU.
All new libSieve code is placed under the LGPL. Because the original license does
not prohibit this form of combination, the LGPL becomes effective upon the entirety
of the libSieve distribution.

<p>Licensing terms can be retrieved by calling sieve_license(). Similarly, and
although not required, credits can also be retrieved. Call sieve_credits() for
those.
ENDOFPRE
	) ) );
 $smarty->assign( 'rightlinks', array(
	array( 'GNU Lesser GPL', 'http://www.fsf.org/licensing/licenses/lgpl.html' )
	) );


 $smarty->display( 'tweedy.tpl' );

?>
