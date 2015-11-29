#ifndef FSLC_STDIO_H
#define FSLC_STDIO_H

#include <stdarg.h>

#ifndef ALT_FSLC_NAMES

#define FSLC_FILE       FILE
#define fslc_stdout     stdout
#define fslc_putchar    putchar
#define fslc_fputc      fputc
#define fslc_fputs      fputs
#define fslc_puts       puts

#define fslc_vfprintf   vfprintf
#define fslc_vprintf    vprintf
#define fslc_fprintf    fprintf
#define fslc_printf     printf

#endif /* ALT_FSLC_NAMES */

typedef struct _FSLC_FILE FSLC_FILE;

struct _FSLC_FILE
{
    void *user_ptr;
    int (*putc)(int c, FSLC_FILE *stream);
    void (*pre_output)(FSLC_FILE *stream);
    void (*post_output)(FSLC_FILE *stream);
};

extern FSLC_FILE    *fslc_stdout;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    int fslc_putchar(int c);
    int fslc_fputc(int c, FSLC_FILE *stream);
    int fslc_fputs(const char *str, FSLC_FILE *stream);
    int fslc_puts(const char *str);

    int fslc_vfprintf(FSLC_FILE *stream, const char *format, va_list arg);
    int fslc_vprintf(const char *format, va_list arg);
    int fslc_fprintf(FSLC_FILE *stream, const char *format, ...);
    int fslc_printf(const char *format, ...);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#endif /* FSLC_STDIO_H */
