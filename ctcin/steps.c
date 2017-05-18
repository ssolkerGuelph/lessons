#include<stdio.h>

int countSteps(int n, int mem[]);

int main() {

    int n = 0;
    //1 step 2 step or 3 steps to nth
    printf("Enter step count: ");
    scanf("%d",&n);

    int mem[n+1];
    for (int i = 0; i < n+1; i++) {
        mem[i] = -1;
    }
    int total = countSteps(n,mem);

    printf("Total steps = %d\n", total);

    return 0;
}

int countSteps(int n, int mem[]) {
    
    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (mem[n] > -1) {
        printf("%d\n",n);
        return mem[n];
    } else {
        mem[n] = countSteps(n-1,mem) + countSteps(n-2,mem) + countSteps(n-3,mem);
        return mem[n];
    }
}   
