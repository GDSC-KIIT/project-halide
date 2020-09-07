#include <halidestdlib.h>

int hldstd::stringLength(char* str)
{
    int len=0;
    while(str[len++]);
    return len-1;
}

int hldstd::stringCompare(char* s1, char* s2)
{
    int result = 1;
    int size = stringLength(s1);
    if(size != stringLength(s2)) result =0;
    else 
    {
        int i = 0;
        for(i;i<=size;i++)
        {
            if(s1[i] != s2[i]) result = 0;
        }
    }
    return result;
}