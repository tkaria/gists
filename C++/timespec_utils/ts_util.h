/* $Id: ts_util.h,v 1.11 2009/09/09 22:38:13 alex Exp $ */
/*******************************************************************************

    ts_util.h

    "timespec" Manipulation Definitions.

*******************************************************************************/

#ifndef  TS_UTIL_H		/* Has the file been INCLUDE'd already? */
#define  TS_UTIL_H  yes

#ifdef __cplusplus		/* If this is a C++ compiler, use C linkage */
extern  "C"  {
#endif


#include  <time.h>		/* System time definitions. */
//#include  "pragmatics.h"		/* Compiler, OS, logging definitions. */
//#include  "tv_util.h"			/* "timeval" manipulation functions. */
#if defined(VXWORKS)
#include  <timers.h>		/* POSIX timer definitions. */
#elif defined(__hpux)
#include  <sys/timers.h>		/* POSIX timer definitions. */
#elif defined(_POSIX_SOURCE)
#include  <sys/time.h>		/* System time definitions. */
//#elif defined(HAVE_TIMESPEC) && !HAVE_TIMESPEC
    //struct  timespec {
        //time_t  tv_sec ;		/* Seconds. */
        //long  tv_nsec ;			/* Nanoseconds. */
    //} ;
#endif



/*******************************************************************************
    Public functions.
*******************************************************************************/

extern  timespec tsAdd((timespec time1,
                                   timespec time2)) ;

extern  int  tsCompare((timespec time1,
                           timespec time2)) ;

extern  timespec  tsCreate((long seconds,
                                       long nanoseconds)) ;

extern  timespec  tsCreateF((double fSeconds)) ;

extern  double  tsFloat((timespec time)) ;

extern  const  char  *tsShow((timespec binaryTime,
                                 bool inLocal,
                                 const char *format)) ;

extern  timespec  tsSubtract((timespec time1,
                                         timespec time2)) ;

extern  timespec  tsTOD (
#    if PROTOTYPES && !defined(__cplusplus)
        void
#    endif
    ) ;


#ifdef __cplusplus		/* If this is a C++ compiler, use C linkage */
}
#endif

#endif				/* If this file was not INCLUDE'd previously. */
