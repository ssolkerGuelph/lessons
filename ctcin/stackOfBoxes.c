#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct BOX {
    int height;
} Box;

void printStack(Box stack[], int len);

void orderDescending(Box stack[], int len);

void split(Box stack[], int l, int r);

void merge(Box stack[], int l, int m, int r);

int main() {

    int numBoxes = 0;
    int ran = 0;
    srand(time(NULL));

    printf("Enter number of boxes: ");
    scanf("%d", &numBoxes);

    Box stack[numBoxes];

    for (int i = 0; i < numBoxes; i++) {
        ran = (rand()%numBoxes) + 1;
        stack[i].height = ran;
    }

    printf("\nInitial\n");
    printStack(stack,numBoxes);

    orderDescending(stack,numBoxes-1);

    printf("\nDescending\n");
    printStack(stack,numBoxes);

    return 0;

}

void printStack(Box stack[],int n) {
    for (int i = 0; i < n; i++) {
        printf("Box %d: h = %d\n", i+1, stack[i].height);
    }
}


void orderDescending(Box stack[], int len) {
    split(stack, 0, len);
}

void split(Box stack[], int l, int r) {

    if (l < r) {
        //same as (l+r)/2
        //avoid overflow
        int mid = l+(r-l)/2;
        //int mid = (l+r)/2;
        split(stack, l, mid);
        split(stack, mid+1, r);
        merge(stack, l, mid, r);
    }
}

void merge(Box stack[], int l, int m, int r) {

    //2 sub arrays, l-m and (m+1)-r
    int i,j,k;
    //length of 2 sub arrays
    int a1 = m - l + 1;
    int a2 = r - m;

    Box left[a1], right[a2];
    
    for ( i = 0; i < a1; i++) {
        left[i].height = stack[l+i].height;
    }
    for ( j = 0; j < a2; j++) {
        right[j].height = stack[m+1+j].height;
    }

    //merge temp to stack
    i = 0;
    j = 0;
    k = l;

    //merged
    while ( i < a1 && j < a2) {
        if (left[i].height >= right[j].height) {
            stack[k].height = left[i].height;
            i++;
        } else {
            stack[k].height = right[j].height;
            j++;
        }
        k++;
    }
    
    //remaining
    while (i < a1) {
        stack[k].height = left[i].height;
        i++;
        k++;
    }
    while (j < a2) {
        stack[k].height = right[j].height;
        j++;
        k++;
    }

}
