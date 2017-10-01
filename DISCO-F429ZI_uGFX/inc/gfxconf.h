/******************************************************************************/
/* This file has been generated by the uGFX-Studio                            */
/*                                                                            */
/* http://ugfx.org                                                            */
/******************************************************************************/

#ifndef _GFXCONF_H
#define _GFXCONF_H

///////////////////////////////////////////////////////////////////////////
// GOS - One of these must be defined, preferably in your Makefile       //
///////////////////////////////////////////////////////////////////////////
//#define GFX_USE_OS_CHIBIOS                           FALSE
//#define GFX_USE_OS_FREERTOS                          FALSE
//#define GFX_FREERTOS_USE_TRACE                   FALSE
//#define GFX_USE_OS_WIN32                             FALSE
//#define GFX_USE_OS_LINUX                             FALSE
//#define GFX_USE_OS_OSX                               FALSE
//#define GFX_USE_OS_ECOS                              FALSE
//#define GFX_USE_OS_RAWRTOS                           FALSE
//#define GFX_USE_OS_ARDUINO                           FALSE
//#define GFX_USE_OS_KEIL                              FALSE
//#define GFX_USE_OS_CMSIS                             FALSE
#define GFX_USE_OS_RAW32      	                       TRUE
//#define GFX_USE_OS_NIOS                              FALSE
//#define GFX_USE_OS_QT                                FALSE
//#define INTERRUPTS_OFF()                         optional_code
//#define INTERRUPTS_ON()                          optional_code

// Options that (should where relevant) apply to all operating systems
//#define GFX_NO_INLINE                            FALSE
//#define GFX_COMPILER                             GFX_COMPILER_UNKNOWN
//#define GFX_SHOW_COMPILER                        FALSE
//#define GFX_CPU                                  GFX_CPU_UNKNOWN
#define GFX_CPU                 	                   GFX_CPU_CORTEX_M4_FPU
#define GFX_OS_PRE_INIT_FUNCTION 					   Raw32OSInit
//#define GFX_CPU_NO_ALIGNMENT_FAULTS              FALSE
//#define GFX_CPU_ENDIAN                           GFX_CPU_ENDIAN_UNKNOWN
//#define GFX_OS_HEAP_SIZE                         0
//#define GFX_OS_NO_INIT                           FALSE
//#define GFX_OS_INIT_NO_WARNING                   FALSE
//#define GFX_OS_PRE_INIT_FUNCTION                 myHardwareInitRoutine
//#define GFX_OS_EXTRA_INIT_FUNCTION               myOSInitRoutine
//#define GFX_OS_EXTRA_DEINIT_FUNCTION             myOSDeInitRoutine
//#define GFX_OS_CALL_UGFXMAIN                     FALSE
//#define GFX_OS_UGFXMAIN_STACKSIZE                0
//#define GFX_EMULATE_MALLOC                       FALSE

/********************************************************/
/* GDISP stuff                                          */
/********************************************************/
#define GFX_USE_GDISP TRUE

#define GDISP_NEED_CONTROL TRUE
#define GDISP_NEED_VALIDATION TRUE
#define GDISP_NEED_CLIP TRUE
#define GDISP_NEED_ARC FALSE
#define GDISP_NEED_CONVEX_POLYGON FALSE
#define GDISP_NEED_IMAGE FALSE
#define GDISP_NEED_STARTUP_LOGO FALSE
#define GDISP_NEED_CIRCLE TRUE
#define GDISP_NEED_MULTITHREAD TRUE
#define GDISP_DEFAULT_ORIENTATION GDISP_ROTATE_0
#define GDISP_STARTUP_COLOR HTML2COLOR(0xFFFFFF)


/********************************************************/
/* Font stuff                                           */
/********************************************************/
#define GDISP_NEED_TEXT TRUE
#define GDISP_NEED_ANTIALIAS FALSE
#define GDISP_NEED_TEXT_KERNING FALSE
#define GDISP_NEED_UTF8 FALSE
#define GDISP_INCLUDE_USER_FONTS FALSE
#define GDISP_INCLUDE_FONT_DEJAVUSANS16 TRUE

/********************************************************/
/* GWIN stuff                                           */
/********************************************************/
#define GFX_USE_GWIN TRUE

#define GWIN_NEED_WINDOWMANAGER TRUE
#define GWIN_REDRAW_IMMEDIATE TRUE
#define GWIN_REDRAW_SINGLEOP TRUE

#define GWIN_NEED_WIDGET TRUE
#define GWIN_NEED_CHECKBOX TRUE
#define GWIN_NEED_BUTTON TRUE
#define GWIN_BUTTON_LAZY_RELEASE FALSE
#define GWIN_NEED_RADIO TRUE
#define GWIN_NEED_SLIDER TRUE
#define GWIN_FLAT_STYLING FALSE

#define GWIN_NEED_CONTAINERS TRUE
#define GWIN_NEED_CONTAINER TRUE
#define GWIN_NEED_FRAME FALSE
#define GWIN_NEED_TABSET FALSE

//#define GWIN_NEED_CONSOLE       TRUE
//#define GWIN_CONSOLE_USE_FLOAT  TRUE


/********************************************************/
/* GTIMER stuff                                         */
/********************************************************/
#define GFX_USE_GTIMER TRUE

#define GTIMER_THREAD_PRIORITY NORMAL_PRIORITY
#define GTIMER_THREAD_WORKAREA_SIZE 2048


/********************************************************/
/* GINPUT stuff                                         */
/********************************************************/
#define GFX_USE_GINPUT TRUE

#define GINPUT_NEED_MOUSE TRUE
#define GINPUT_TOUCH_USER_CALIBRATION_LOAD FALSE
#define GINPUT_NEED_KEYBOARD FALSE
//#define GINPUT_TOUCH_NOCALIBRATE TRUE


/********************************************************/
/* GEVENT stuff                                         */
/********************************************************/
#define GFX_USE_GEVENT TRUE

#define GEVENT_ASSERT_NO_RESOURCE FALSE
#define GEVENT_MAXIMUM_SIZE 32
#define GEVENT_MAX_SOURCE_LISTENERS 32


/********************************************************/
/* GEVENT stuff                                         */
/********************************************************/
#define GFX_USE_GQUEUE TRUE

#define GQUEUE_NEED_ASYNC TRUE


/********************************************************/
/* GFILE stuff                                          */
/********************************************************/
#define GFX_USE_GFILE FALSE

#define GFILE_NEED_NATIVEFS FALSE
#define GFILE_NEED_ROMFS TRUE



#endif /* _GFXCONF_H */
