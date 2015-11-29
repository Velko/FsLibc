#ifndef FSLC_STDIO_H
#define FSLC_STDIO_H

#ifndef ALT_FSLC_NAMES

#define FSLC_FILE       FILE
#define fslc_stdout     stdout
#define fslc_putchar    putchar
#define fslc_fputc      fputc
#define fslc_fputs      fputs
#define fslc_puts       puts

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

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#endif /* FSLC_STDIO_H */
