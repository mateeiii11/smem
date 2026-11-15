#include <stdio.h>
#include "smem.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
int main(void)
{
    char *a = smalloc(40);
    char *b = smalloc(40);
    char *c = smalloc(40);
    assert(a && b && c);

    memset(a, 'A', 40);
    memset(b, 'B', 40);
    memset(c, 'C', 40);

    see_list();

    sfree(b);
    sfree(a);
    sfree(c);

    char *big = smalloc(100);
    assert(big == a);
    memset(big, 'X', 100);
    sfree(big);

    int *nums = scalloc(8, sizeof(int));
    assert(nums != NULL);
    for (int i = 0; i < 8; i++) {
        assert(nums[i] == 0);
        nums[i] = i * 10;
    }

    nums = srealloc(nums, 32 * sizeof(int));

    assert(nums != NULL);
    for (int i = 0; i < 8; i++) {
        assert(nums[i] == i * 10);
    }
    sfree(nums);
    printf("nice\n");
    return 0;
}
