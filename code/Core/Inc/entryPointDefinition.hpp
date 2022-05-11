/*
 * POWERHACKER HEADER FILE
 * Use only for entry point definition as this is processed by the C compiler (not C++)
 */

#ifndef __POWERHACKER
#define __POWERHACKER

#ifdef __cplusplus
extern "C"
{
#endif

#define SOFTWARE_VERSION "1.0-alpha";

// Function prototypes
void entryPointLoop();
void entryPointSetup();
void captureUserInput();

#ifdef __cplusplus
}
#endif
#endif
