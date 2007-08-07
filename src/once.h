/***************************************************************************
 *
 * once.h - one time initialization helpers
 *
 * $Id$
 *
 ***************************************************************************
 *
 * Licensed to the Apache Software  Foundation (ASF) under one or more
 * contributor  license agreements.  See  the NOTICE  file distributed
 * with  this  work  for  additional information  regarding  copyright
 * ownership.   The ASF  licenses this  file to  you under  the Apache
 * License, Version  2.0 (the  License); you may  not use  this file
 * except in  compliance with the License.   You may obtain  a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the  License is distributed on an  "AS IS" BASIS,
 * WITHOUT  WARRANTIES OR CONDITIONS  OF ANY  KIND, either  express or
 * implied.   See  the License  for  the  specific language  governing
 * permissions and limitations under the License.
 *
 * Copyright 2007 Rogue Wave Software, Inc.
 * 
 **************************************************************************/

#include <rw/_defs.h>


#ifdef _RWSTD_REENTRANT
#  ifdef _RWSTD_OS_SUNOS

#    include <pthread.h>
#    include <thread.h>

#    define _RWSTD_THREAD_ONCE(once, func)   pthread_once (once, func)
#    define _RWSTD_THREAD_YIELD()            thr_yield ()

typedef pthread_once_t __rw_once_t;

#  elif defined (_RWSTD_POSIX_THREADS)

#    include <pthread.h>

typedef pthread_once_t __rw_once_t;

#    define _RWSTD_THREAD_ONCE(once, func)   pthread_once (once, func)

#    ifndef _RWSTD_NO_SCHED_YIELD
#      define _RWSTD_THREAD_YIELD()   sched_yield ()
#    endif   // _RWSTD_NO_SCHED_YIELD
#  elif defined (_RWSTD_DCE_THREADS)

#    if defined (_RWSTD_NO_DCE_PTHREAD_H)
#      include <pthread.h>
#    else
#      include <dce/pthread.h>
#    endif

typedef pthread_once_t __rw_once_t;

#    define _RWSTD_THREAD_ONCE(once, func)   pthread_once (once, func)
#    define _RWSTD_THREAD_YIELD()            pthread_yield ()

#  elif defined (_WIN32)

#    include <windows.h>

struct __rw_once_t { int _C_init; };

#    define _RWSTD_THREAD_YIELD()   Sleep (0)
#  endif   // _RWSTD_*_THREADS


#  ifdef PTHREAD_ONCE_INIT
#    define _RWSTD_ONCE_INIT   PTHREAD_ONCE_INIT
#  endif   // PTHREAD_ONCE_INIT

#else   // if !defined (_RWSTD_REENTRANT)

struct __rw_once_t { int _C_init; };

   // defined to a non-zero value to help detect uninitialized
   // __rw_once_t objects
#  define _RWSTD_ONCE_INIT   { -1 }

   // not defined
#  undef  _RWSTD_THREAD_ONCE
#endif   // _RWSTD_REENTRANT


#ifndef _RWSTD_THREAD_YIELD
#  define _RWSTD_THREAD_YIELD()   (void)0
#endif   // _RWSTD_THREAD_YIELD


_RWSTD_NAMESPACE (__rw) {

extern "C" {

_RWSTD_EXPORT int
__rw_once (__rw_once_t*, void (*)());

}   // extern "C"


}   // namespace __rw
