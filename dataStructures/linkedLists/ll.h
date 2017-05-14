#ifndef __ll_h__
#define __ll_h__

typedef struct Node {

    int key;
    char * name;
    struct Node * next;

} node;

/**
*
*/

//init the head
node * createNode(int key, char * name);

//print the node
void printNode(node * out);

//add to back
void addToBack(node ** head, int key, char * name);

void removeFront(node ** head);

void cleanList(node ** head);

//mergesort
int sortByKey(node ** head);

void mergeSort(node ** head);

node * merge(node * back, node * front);

void splitFB(node * head, node ** front, node ** back);

node * mergeSortName(node * front, node * back);

/**
*parser
*/

node * readIn(node * head);

void resetString(char empty[]);



#endif
