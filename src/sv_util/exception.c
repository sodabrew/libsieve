/*
 ******************************
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * License Public Domain Without Warranty
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/oopc/exception.html
 *
 ******************************
 */

#include <stdio.h>
#include <stdlib.h>
#include "exception.h"

/* global stack of exception context */
struct _exceptionContext_ *const _returnExceptionContext_ = NULL;
struct _exceptionContext_ *_currentExceptionContext_ = NULL;

/* delete protected pointers and throw exception */
void
_exceptionThrow_(int exception)
{
  struct _protectedPtr_ *p;

  /* no exception context saved, exit program */
  if (!_currentExceptionContext_) exit(exception); 

  /* free pointers stored on the current exception context pointers stack */
  for (p=_currentExceptionContext_->stack; p; p=p->next) p->func(p->ptr);

  /* jump to previous exception context */
  _restore_context_buffer_(_currentExceptionContext_->context, exception); 
} 

void
_exceptionThrowDebug_(char const* _file_, int _line_, char const* _func_,
		      char const* _exception_, int exception)
{
  fprintf(stderr, "%s(%d)-%s: exception '%s' (id %d) thrown\n",
	  _file_, _line_, _func_, _exception_, exception);
  _exceptionThrow_(exception);
}
