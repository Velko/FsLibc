#include "fslc_string.h"

char* fslc_strcat(char* destination, const char* source) {
    char* dest = destination;

    // Move the pointer to the end of the destination string
    while (*dest) {
        dest++;
    }

    // Copy the source string to the end of the destination string
    while (*source) {
        *dest = *source;
        dest++;
        source++;
    }

    // Null-terminate the concatenated string
    *dest = '\0';

    return destination;
}

