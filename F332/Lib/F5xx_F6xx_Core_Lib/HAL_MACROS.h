#ifndef HAL_MACROS_H
#define HAL_MACROS_H

/*
 *  This macro is for use by other macros to form a fully valid C statement.
 */
#define st(x)      do { x } while (__LINE__ == -1)

#endif /* HAL_MACROS_H */
