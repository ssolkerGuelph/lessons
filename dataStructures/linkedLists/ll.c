#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ll.h"

int main(int argc, char * argv[]) {

    node * head = NULL;
    head = createNode(0,"head");                

    if (head == NULL) {
        printf("Head creation failed\n");
        exit(1);
    }

    head = readIn(head);
    printf("In:\n");
    printNode(head);

    printf("\nSort by key\n");
    sortByKey(&head);
    printNode(head);

    //printf("Sort by name\n");
    //printNode(head);

    cleanList(&head);

    printf("\n");
    
    return 0;

}

void resetString(char empty[]) {

    for(int i = 0; i < 50; i++) {
        empty[i] = '\0';
    }

}

node * readIn(node * head) {

    FILE * fptr;
    char c;
    int key;
    int count = 0;

    char name[50];
    char temp[50];

    resetString(temp); 

    fptr = fopen("file","r");
    while( (c=getc(fptr)) != EOF ) {
        if (c == ',') {
            count = 0;
            key = atoi(temp);
            resetString(temp);
        } else if (c == '\n') {
            count = 0;
            strcpy(name,temp);
            resetString(temp);
            addToBack(&head,key,name);
        } else {  
            temp[count] = c;
            count++;
            //printf("%c",c); 
        }
    }  
    printf("\n");
    fclose(fptr);

    return head;

}

node * createNode(int key, char * name) {

    node * head = NULL;
    head = malloc(sizeof(node));
    head->name = malloc(sizeof(char));

    if (head == NULL) {
        printf("Malloc fail\n");
        return NULL;
    }

    head->key = key;
    strcpy(head->name, name);
    head->next = NULL;

    return head;
}

void printNode(node * out) {

    if (out != NULL) {
        printf("The key is %d and the name is %s\n", out->key, out->name);
        printf("The next node is:\n");
        printNode(out->next);
    } else {
        printf("Empty\n");
    }
}

void addToBack(node ** head, int key, char * name) {

    node * temp = * head;

    while(temp->next != NULL) {
        temp = temp->next;
    }
    node * added = createNode(key,name);
    temp->next = added;
}

void removeFront(node ** head) {

    //when using * make sure precedence is correct (*head)
    if (*head != NULL) {
        node * temp = *head;
        *head = (*head)->next;
        free(temp->name);
        free(temp);
    } else {
        printf("Empty, cannot remove front\n");
    }   

}

void cleanList(node ** head) {

    node * cur = *head;
    node * next;

    while (cur != NULL) {
        next = cur->next;
        free(cur->name);
        free(cur);
        cur = next;
    }

    *head = NULL;

}

int sortByKey(node ** head) {

    node * temp = *head;

    mergeSort(&temp);

    return 0;
}

void mergeSort(node** headRef) {

  node* head = *headRef;
  node* front;
  node* back;
 
  /*length 0/1*/
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
 
  /* Split head into 'a' and 'b' sublists */
  splitFB(head, &front, &back); 
 
  /* Recursively sort the sublists */
  mergeSort(&front);
  mergeSort(&back);
 
  /* answer = merge the two sorted lists together */
  *headRef = merge(front, back);
}
 
node * merge(node* front,node* back) {

    node * result = NULL;
 
    /* Base cases */
    if (front == NULL) {
        return back;
    } else if (back == NULL) {
        return front;
    }

    /* Pick either a or b, and recur */
    if (front->key <= back->key) {
        result = front;
        result->next = merge(front->next, back);
    } else {
        result = back;
        result->next = merge(front, back->next);
    }

    return result;
}

node * mergeSortName(node * front, node * back) {

    node * result = NULL;

    if (front == NULL) {
        return back;
    } else if (back == NULL) {
        return front;
    }
    
    //condition
    if (strcmp(front->name,back->name) > 0) {
        result = front;
        result->next = mergeSortName(front->next,back);
    } else {
        result = back;
        result->next = mergeSortName(front,back->next);
    }
    
    return result; 

}
 
void splitFB(node* source, node** frontRef, node** backRef) {

    node* fast = NULL;
    node* slow = NULL;

    if (source==NULL || source->next==NULL) {
    /* length < 2 cases */
        *frontRef = source;
        *backRef = NULL;
    } else {
        slow = source;
        fast = source->next;
    }
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
      fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
