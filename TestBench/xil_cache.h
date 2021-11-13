#ifndef XIL_CACHE_H
#define XIL_CACHE_H

#include "xil_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *@cond nocomments
 */

#if defined (__GNUC__)
#define asm_inval_dc_line_mva_poc(param) __asm__ __volatile__("mcr " \
		XREG_CP15_INVAL_DC_LINE_MVA_POC :: "r" (param))

#define asm_clean_inval_dc_line_sw(param) __asm__ __volatile__("mcr " \
		XREG_CP15_CLEAN_INVAL_DC_LINE_SW :: "r" (param))

#define asm_clean_inval_dc_line_mva_poc(param) __asm__ __volatile__("mcr " \
		XREG_CP15_CLEAN_INVAL_DC_LINE_MVA_POC :: "r" (param))

#define asm_inval_ic_line_mva_pou(param) __asm__ __volatile__("mcr " \
		XREG_CP15_INVAL_IC_LINE_MVA_POU :: "r" (param))
#elif defined (__ICCARM__)
#define asm_inval_dc_line_mva_poc(param) __asm volatile("mcr " \
		XREG_CP15_INVAL_DC_LINE_MVA_POC :: "r" (param))

#define asm_clean_inval_dc_line_sw(param) __asm volatile("mcr " \
		XREG_CP15_CLEAN_INVAL_DC_LINE_SW :: "r" (param))

#define asm_clean_inval_dc_line_mva_poc(param) __asm volatile("mcr " \
		XREG_CP15_CLEAN_INVAL_DC_LINE_MVA_POC :: "r" (param))

#define asm_inval_ic_line_mva_pou(param) __asm volatile("mcr " \
		XREG_CP15_INVAL_IC_LINE_MVA_POU :: "r" (param))
#endif

/**
 *@endcond
 */

void Xil_DCacheEnable(void);
void Xil_DCacheDisable(void);
void Xil_DCacheInvalidate(void);
void Xil_DCacheInvalidateRange(INTPTR adr, u32 len);
void Xil_DCacheFlush(void);
void Xil_DCacheFlushRange(INTPTR adr, u32 len);
void Xil_DCacheInvalidateLine(INTPTR adr);
void Xil_DCacheFlushLine(INTPTR adr);
void Xil_DCacheStoreLine(INTPTR adr);

void Xil_ICacheEnable(void);
void Xil_ICacheDisable(void);
void Xil_ICacheInvalidate(void);
void Xil_ICacheInvalidateRange(INTPTR adr, u32 len);
void Xil_ICacheInvalidateLine(INTPTR adr);

#ifdef __cplusplus
}
#endif

#endif
