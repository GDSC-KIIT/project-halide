#include <halidestdlib.h>

int hldstd::stringLength(char* str)
{
    int len=0;
    while(str[len++]);
    return len-1;
}

int hldstd::stringCompare(char* s1, char* s2)
{
    bool eq=false;
    if(stringLength(s1) != stringLength(s2))
        eq = false;
    for (int i = 0; s1[i] != '\0'; i++)
    {
        if(s1[i] != s2[i]) {
            eq= true;
            break;
        }
        else {
            eq = true;
        }
    }
    
    return (eq) ? 1 : 0;
}