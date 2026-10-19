#include <stdio.h>
#include "smem.h"
#include <stdlib.h>
#include <string.h>
int main(void)
{
    int i;
    char *p = smalloc(11);
    for(i = 0; i < 10; i++)
        p[i] = i + '0';
    p[++i] = '\0';
    printf("%s\n", p);
    sfree(p);

    char *a = smalloc(7);
    for(i = 0; i < 10; i++)
        a[i] = i + '0';
    a[++i] = '\0';
    printf("%s\n", a);
    sfree(a);

    char *x = smalloc(3);
    for(i = 0; i < 10; i++)
        x[i] = i + '0';
    x[++i] = '\0';
    printf("%s\n", x);
    sfree(x);

    char *c = smalloc(2);
    char *b = smalloc(7);
    char *h = smalloc(100);
    sfree(c); sfree(b); sfree(h);
    /**
    int *a = scalloc(4, sizeof(int) * 4);
    for(int i = 0; i < 4; i++)
        printf("%d ", a[i]);
    sfree(a);
    printf("\n");

    int *arr = smalloc(5 * sizeof(int));
    for(int i = 0; i < 4; i++)
        arr[i] = i;
    for(int i = 0; i < 4; i++)
        printf("%d ", a[i]);       
    printf("\n");

    arr = srealloc(arr, 10 * sizeof(int));
    for(int i = 0; i < 10; i++)
        arr[i] = i;
    for(int i = 0; i < 10; i++)
        printf("%d ", a[i]);       
    printf("\n");
    sfree(arr);
    */
    return 0;
}
