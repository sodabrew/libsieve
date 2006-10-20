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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#ifndef __STDC__
#  error "exception.h needs ISO C compiler to work properly"
#endif

#include <setjmp.h>

/*
  some useful macros
*/

#define _makeConcat_(a,b) a ## b
#define _concat_(a,b) _makeConcat_(a,b)

#define _makeString_(a) # a
#define _string_(a) _makeString_(a)

/*
  choose context savings
*/

#ifdef sigsetjmp
#  define _save_context_buffer_(context)         sigsetjmp(context, 1)
#  define _restore_context_buffer_(context, val) siglongjmp(context, val)
#else
#  define _save_context_buffer_(context)         setjmp(context)
#  define _restore_context_buffer_(context, val) longjmp(context, val)
#endif

/*
  some hidden types used to handle exceptions
*/

/* type of stack of protected pointer */
struct _protectedPtr_ {
  struct _protectedPtr_ *next;
  void *ptr;
  void (*func)(void*);
};

/* type of stack of exception */
struct _exceptionContext_ {
  struct _exceptionContext_ *next;
  struct _protectedPtr_ *stack;
  jmp_buf context;
};

extern struct _exceptionContext_ *const _returnExceptionContext_;
extern struct _exceptionContext_ *_currentExceptionContext_;

/* exception keywords */
#define try								 \
  do {									 \
    struct _exceptionContext_ *const _returnExceptionContext0_ =	 \
                                              _returnExceptionContext_;	 \
    struct _exceptionContext_ *const volatile _returnExceptionContext_ = \
                 _returnExceptionContext0_ ? _returnExceptionContext0_:	 \
                                             _currentExceptionContext_;	 \
    struct _exceptionContext_ _localExceptionContext_ =			 \
                                         { _currentExceptionContext_ };	 \
    _currentExceptionContext_ = &_localExceptionContext_;		 \
    (void)_returnExceptionContext_;					 \
    do {								 \
      int const exception =						 \
              _save_context_buffer_(_currentExceptionContext_->context); \
      if (!exception) {

#define catch(except)							\
      } else if ((int)(except) == exception) {				\
        _currentExceptionContext_ = _currentExceptionContext_->next;

#define catch_any							\
      } else {								\
        _currentExceptionContext_ = _currentExceptionContext_->next;

#define endtry								\
      }									\
    } while(0);								\
    if (_currentExceptionContext_ == &_localExceptionContext_) {	\
      _currentExceptionContext_ = _currentExceptionContext_->next;	\
    }									\
  } while(0)

#define rethrow throw(exception)
#define break_try break
#define return_try(...)						\
  do {								\
    _currentExceptionContext_ = _returnExceptionContext_;	\
    return __VA_ARGS__;						\
  } while(0)

#ifdef DEBUG_THROW
#define throw(except)						\
  _exceptionThrowDebug_(__FILE__, __LINE__, __func__,		\
                        _string_(except), (int)(except))
#else
#define throw(except) _exceptionThrow_((int)(except))
#endif /* DEBUG_THROW */

/*
  pointer protection
*/

#define protectPtr(ptr, func)						    \
  struct _protectedPtr_ _concat_(_protected_, ptr) =			    \
  _protectPtr_(&_concat_(_protected_, ptr), (ptr), (void(*)(void *))(func))

static inline struct _protectedPtr_
_protectPtr_(struct _protectedPtr_ *_ptr, void* ptr, void (*func)(void*)) 
{ 
  if (_currentExceptionContext_) { 
    _ptr->next = _currentExceptionContext_->stack;
    _ptr->ptr  = ptr;
    _ptr->func = func;
    _currentExceptionContext_->stack = _ptr;
  }
  return *_ptr;
}

static inline void
unprotectPtr(void *ptr)
{
  if (_currentExceptionContext_ &&
      _currentExceptionContext_->stack &&
      _currentExceptionContext_->stack->ptr == ptr)
    _currentExceptionContext_->stack = _currentExceptionContext_->stack->next;
}

/*
  extern declarations
*/

extern void _exceptionThrow_(int except);
extern void _exceptionThrowDebug_(char const*, int, char const*, char const*,
				  int except);
#endif
