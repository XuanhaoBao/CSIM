#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#if defined(CSIM_IN_WIN32) || defined(CSIM_IN_CYGWIN)
#define DLIB_SUFFIX ".dll"
#elif defined(CSIM_IN_UNIX)
#define DLIB_SUFFIX ".so"
#else
#error Unsupported OS!
#endif

#if defined(CSIM_IN_CYGWIN)
#define DLIB_PREFIX "cyg"
#elif defined(CSIM_IN_WIN32)
#define DLIB_PREFIX ""
#else
#define DLIB_PREFIX "lib"
#endif

static const double epsilon = 1e-3;
static const char *csimLibrary = DLIB_PREFIX "csim" DLIB_SUFFIX;
static const char *resistorLibrary = DLIB_PREFIX "csimModelResistor" DLIB_SUFFIX;
static const char *VDCLibrary = DLIB_PREFIX "csimModelVDC" DLIB_SUFFIX;

#endif // CONSTANTS_H_
