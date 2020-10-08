/*
 * int.c
 *
 * Performs integer boundary check
 */

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

#include "int.h"

#ifndef lint
static const char rcsid[] = "$Id$";
#endif /* lint */

/* addition functions */

#define check_overflow(a, b, p, max) 	\
{  										\
	if(b > max - a)                 	\
		return INT_OVERFLOW;    		\
	if(p != (void*)0)               	\
		*p = a+b;               		\
	return INT_OK;                  	\
}

int_rt add_ui(ui_t a, ui_t b, ui_t *p)
        check_overflow(a, b, p, UINT_MAX)

int_rt add_si(si_t a, si_t b, si_t *p)
        check_overflow(a, b, p, INT_MAX)

int_rt add_us(us_t a, us_t b, us_t *p)
        check_overflow(a, b, p, USHRT_MAX)

int_rt add_ss(ss_t a, ss_t b, ss_t *p)
        check_overflow(a, b, p, SHRT_MAX)

int_rt add_ul(ul_t a, ul_t b, ul_t *p)
        check_overflow(a, b, p, ULONG_MAX)

int_rt add_sl(sl_t a, sl_t b, sl_t *p)
        check_overflow(a, b, p, LONG_MAX)

#if ( __STDC_VERSION__ >= 199901L )
int_rt add_ull(ull_t a, ull_t b, ull_t *p)
        check_overflow(a, b, p, ULLONG_MAX)

int_rt add_sll(sll_t a, sll_t b, sll_t *p)
        check_overflow(a, b, p, LLONG_MAX)
#endif


/* subtraction functions */

#define check_underflow(a, b, p, min) 	\
{ 										\
	if(a > min + b)                 	\
		return INT_UNDERFLOW;   		\
	if(p != (void*)0)               	\
		*p = a-b;               		\
	return INT_OK;                  	\
}

int_rt sub_ui(ui_t a, ui_t b, ui_t *p)
        check_underflow(a, b, p, 0)

int_rt sub_si(si_t a, si_t b, si_t *p)
        check_underflow(a, b, p, INT_MIN)

int_rt sub_us(us_t a, us_t b, us_t *p)
        check_underflow(a, b, p, 0)

int_rt sub_ss(ss_t a, ss_t b, ss_t *p)
        check_underflow(a, b, p, SHRT_MIN)

int_rt sub_ul(ul_t a, ul_t b, ul_t *p)
        check_underflow(a, b, p, 0)

int_rt sub_sl(sl_t a, sl_t b, sl_t *p)
        check_underflow(a, b, p, LONG_MIN)

#if ( __STDC_VERSION__ >= 199901L )
int_rt sub_ull(ull_t a, ull_t b, ull_t *p)
        check_underflow(a, b, p, 0)

int_rt sub_sll(sll_t a, sll_t b, sll_t *p)
        check_underflow(a, b, p, LLONG_MIN)
#endif


/* multiplication functions */

#define check_mul_unsigned(a, b, p, max) 	\
{											\
	ubig_t r = (ubig_t)a*b;                 \
	if(r > (ubig_t)max)                     \
		return INT_OVERFLOW;            	\
	if(p != (void*)0)                       \
		*p = a*b;                       	\
	return INT_OK;                          \
}

#define check_mul_signed(a, b, p, min, max) \
{   										\
	sbig_t r = (sbig_t)a*b;                 \
	if(r < (sbig_t)min)                     \
		return INT_UNDERFLOW;           	\
	if(r > (sbig_t)max)                     \
		return INT_OVERFLOW;            	\
	if(p != (void*)0)                       \
		*p = a*b;                       	\
	return INT_OK;                          \
}

int_rt mul_ui(ui_t a, ui_t b, ui_t *p) 
        check_mul_unsigned(a, b, p, UINT_MAX)

int_rt mul_si(si_t a, si_t b, si_t *p) 
        check_mul_signed(a, b, p, INT_MIN, INT_MAX)

int_rt mul_us(us_t a, us_t b, us_t *p) 
        check_mul_unsigned(a, b, p, USHRT_MAX)

int_rt mul_ss(ss_t a, ss_t b, ss_t *p)
        check_mul_signed(a, b, p, SHRT_MIN, SHRT_MAX)

int_rt mul_ul(ul_t a, ul_t b, ul_t *p) 
        check_mul_unsigned(a, b, p, ULONG_MAX)

int_rt mul_sl(sl_t a, sl_t b, sl_t *p) 
        check_mul_signed(a, b, p, LONG_MIN, LONG_MAX)

#if ( __STDC_VERSION__ >= 199901L )
int_rt mul_ull(ull_t a, ull_t b, ull_t *p) 
{
	double r = (double) a * b;

	if(r > ULLONG_MAX)
		return INT_OVERFLOW;
	if(p != (void*)0)
		*p = a*b;
	return INT_OK;
}
int_rt mul_sll(sll_t a, sll_t b, sll_t *p) 
{
	double r = (double) a * b;

if(r < (double)LLONG_MIN)
	return INT_OVERFLOW;
	if(r > (double)LLONG_MAX)
		return INT_OVERFLOW;
	if(p == (void*)0)
		*p = a*b;
	return INT_OK;
}
#endif
