#ifndef __STRING_BAD_H__
#define __STRING_BAD_H__

#include <iostream>

class StringBad
{
    private:
        char *str;
        int len;
        static int num_strings;
    public:
        StringBad(const char *s);
        StringBad();
        ~StringBad();
        friend std::ostream &operator<<(std::ostream &os, const StringBad &st);
};

#endif
