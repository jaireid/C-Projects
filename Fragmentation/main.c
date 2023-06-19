#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int m = 45000;
    int triple = 3 * m;
    int **A = (int **)malloc(triple * (sizeof(int *)));
    int **B = (int **)malloc(m * (sizeof(int *)));
    printf("m = %d\n", m);

    clock_t func_one;
    func_one = clock();
    for (int i = 0; i < triple; i++)
    {
        A[i] = (int *)malloc(1048576);
    }
    func_one = clock() - func_one;
    double time_taken_one = ((double)func_one) / CLOCKS_PER_SEC;
    printf("The allocation of the 3m arrays of size 1 MB each took %f seconds to execute \n", time_taken_one);

    clock_t func_two;
    func_two = clock();
    for (int i = 0; i < triple; i = i + 2)
    {
        free(A[i]);
        // A[i] = NULL;
    }
    func_two = clock() - func_two;
    double time_taken_two = ((double)func_two) / CLOCKS_PER_SEC;
    printf("The deallocation of the even-numbered arrays took %f seconds to execute \n", time_taken_two);

    clock_t func_three;
    func_three = clock();
    for (int i = 0; i < m; i++)
    {
        B[i] = (int *)malloc(1468006);
    }
    func_three = clock() - func_three;
    double time_taken_three = ((double)func_three) / CLOCKS_PER_SEC;
    printf("The allocation of the m arrays of size 1.4 MB each took %f seconds to execute \n", time_taken_three);

    for (int i = 1; i < triple; i += 2)
    {
        // if(A[i] != NULL) {
        free(A[i]);
        // }
    }

    for (int i = 0; i < m; i++)
    {
        // if(B[i] != NULL) {
        free(B[i]);
        // }
    }

    free(A);
    free(B);

    return 0;
}
