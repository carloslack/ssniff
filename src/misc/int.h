/*
 * int.h
 */

#ifndef _INT_H
#define _INT_H

typedef enum 
{
    INT_OK,
    INT_OVERFLOW,
    INT_UNDERFLOW,
    INT_NULLPTR
} int_rt;

typedef unsigned int    ui_t;
typedef signed   int    si_t;

typedef unsigned short  us_t;
typedef signed   short  ss_t;

typedef unsigned long   ul_t;
typedef signed   long   sl_t;

#if ( __STDC_VERSION__ >= 199901L )
typedef unsigned long long ull_t;
typedef signed   long long sll_t;

typedef ull_t ubig_t;
typedef sll_t sbig_t;
#else /* ANSI C */
typedef double ubig_t;
typedef double sbig_t;
#endif

/* addition */
int_rt add_ui(ui_t, ui_t, ui_t*);
int_rt add_si(si_t, si_t, si_t*);
int_rt add_us(us_t, us_t, us_t*);
int_rt add_ss(ss_t, ss_t, ss_t*);
int_rt add_ul(ul_t, ul_t, ul_t*);
int_rt add_sl(sl_t, sl_t, sl_t*);

/* subtraction */
int_rt sub_ui(ui_t, ui_t, ui_t*);
int_rt sub_si(si_t, si_t, si_t*);
int_rt sub_us(us_t, us_t, us_t*);
int_rt sub_ss(ss_t, ss_t, ss_t*);
int_rt sub_ul(ul_t, ul_t, ul_t*);
int_rt sub_sl(sl_t, sl_t, sl_t*);

/* multiplication */
int_rt mul_ui(ui_t, ui_t, ui_t*);
int_rt mul_si(si_t, si_t, si_t*);
int_rt mul_us(us_t, us_t, us_t*);
int_rt mul_ss(ss_t, ss_t, ss_t*);
int_rt mul_ul(ul_t, ul_t, ul_t*);
int_rt mul_sl(sl_t, sl_t, sl_t*);

/* C99 functions */
#if ( __STDC_VERSION__ >= 199901L )
int_rt add_ull(ull_t, ull_t, ull_t*);
int_rt add_sll(sll_t, sll_t, sll_t*);

int_rt sub_ull(ull_t, ull_t, ull_t*);
int_rt sub_sll(sll_t, sll_t, sll_t*);

int_rt mul_ull(ull_t, ull_t, ull_t*);
int_rt mul_sll(sll_t, sll_t, sll_t*);
#endif

#else
#endif
