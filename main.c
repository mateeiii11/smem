#include <stdio.h>
#include "smem.h"
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char *a = smalloc(120);
    char *p = scalloc(1, 20);
    srealloc(a, 140); 
    sfree(a); sfree(p);
    return 0;
}
