#ifndef XPSEUDO_ASM_H
#define XPSEUDO_ASM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xreg_cortexa9.h"
#ifdef __GNUC__
 #include "xpseudo_asm_gcc.h"
#elif defined (__ICCARM__)
 #include "xpseudo_asm_iccarm.h"
#else
 #include "xpseudo_asm_rvct.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
