#include <stdio.h>
#include "smem.h"


int main(void)
{
    int i;
    char *p = smalloc(sizeof(char) * 20);
    for(i = 0; i < 19; i++)
        p[i] = i;
    p[++i] = '\0';
    printf("%s", p);
    sfree(p);
    return 0;
}
