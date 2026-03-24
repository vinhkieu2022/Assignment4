#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node* next;
}
void display(struct node* head) {
    struct node* temp = head;
    if (head == NULL) {
        printf("danh sach trong");
    } else {
        while (temp != NULL) {
            printf ("%d ->", temp->data);
            temp = temp -> next;
        }
        printf("NULL\n");
    }
}

void addback(struct node* head, int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
  if (head == NULL) {
    return newnode;
  } else {
    struct node* temp = head;
    while (temp->next != NULL) {
    temp = temp->next;
  }
   temp->next = newnode;
   return head;
}
}