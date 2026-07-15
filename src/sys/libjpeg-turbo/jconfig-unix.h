/* Version ID for the JPEG library.
 * Might be useful for tests like "#if JPEG_LIB_VERSION >= 60".
 */
#define JPEG_LIB_VERSION  62

/* libjpeg-turbo version */
#define LIBJPEG_TURBO_VERSION  3.1.1

/* libjpeg-turbo version in integer form */
#define LIBJPEG_TURBO_VERSION_NUMBER  30101

/* Support arithmetic encoding when using 8-bit samples */
#define C_ARITH_CODING_SUPPORTED 1

/* Support arithmetic decoding when using 8-bit samples */
#define D_ARITH_CODING_SUPPORTED 1

/* Support in-memory source/destination managers */
#define MEM_SRCDST_SUPPORTED  1

/* Use accelerated SIMD routines when using 8-bit samples */
#define WITH_SIMD 1

/* This version of libjpeg-turbo supports run-time selection of data precision,
 * so BITS_IN_JSAMPLE is no longer used to specify the data precision at build
 * time.  However, some downstream software expects the macro to be defined.
 * Since 12-bit data precision is an opt-in feature that requires explicitly
 * calling 12-bit-specific libjpeg API functions and using 12-bit-specific data
 * types, the unmodified portion of the libjpeg API still behaves as if it were
 * built for 8-bit precision, and JSAMPLE is still literally an 8-bit data
 * type.  Thus, it is correct to define BITS_IN_JSAMPLE to 8 here.
 */
#ifndef BITS_IN_JSAMPLE
#define BITS_IN_JSAMPLE  8
#endif

/* Unix/Linux-specific configurations */
/* Define if your (broken) compiler shifts signed values as if they were
   unsigned. */
#undef RIGHT_SHIFT_IS_UNSIGNED 