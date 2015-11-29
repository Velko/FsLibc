#ifndef STDIOFIXTURE_H
#define STDIOFIXTURE_H

#define ALT_FSLC_NAMES /* use alternative FSLC names - do not clash with Host Libc */
#include "fslc_stdio.h"

#include <vector>
#include <iostream>

struct StdIOFixture
{
    FSLC_FILE stream;
    
    enum struct CalledFunc { None, PreOp, PutC, PostOp };
        
    struct FuncCallItem {
        enum CalledFunc opera;
        int param1;
        bool operator == (const FuncCallItem &other) const
        {
            return opera == other.opera 
                && param1 == other.param1;
        }
    };

    std::vector<FuncCallItem> FuncCallLog;
    
    int eof_counter;
    
    StdIOFixture();
    
    static int fixture_putc(int c, FSLC_FILE *stream);
    static void fixture_preop(FSLC_FILE *stream);
    static void fixture_postop(FSLC_FILE *stream);
};

std::ostream &operator<< (std::ostream &stream, const StdIOFixture::FuncCallItem &citem);


#endif // STDIOFIXTURE_H
