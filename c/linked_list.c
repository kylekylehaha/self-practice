#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* next;
    int value;
} Node;

typedef struct list{
    Node* head;
} List;

Node* create_node (int value){
    Node* node = malloc(sizeof(Node));
    node -> value = value;
    node -> next = NULL;
    return node;
}

void dump (List* list){
    if (!list || !list->head)
        return;

    printf ("%d", list->head->value);
    Node *temp = list->head->next;
    while(temp){
        printf(" , %d", temp->value);
        temp = temp->next;
    }
    printf("\n");
    return;
}

//Assume target is in linked_list
void remove_list_node_v1(List* list, Node* target){//   用ptr是因為會改變head值，故必須傳ptr進來
    Node* prev = NULL;
    Node* current = list->head;

    while(current!=target){
        prev = current;
        current = current->next;
    }
    if(!prev){
        list->head = target->next;
    }
    else{
        prev->next = target->next;
    }
    return;
}

//直接改變該記憶體位置所存的node，故需要ptr to ptr
void remove_list_node_v2(List* list, Node* target){
    Node** indirect = &list->head;
    
    while(*indirect != target){
        indirect = &(*indirect)->next;
    }
    *indirect = target->next;
}

int main(){
    int i;
    List list;
    Node* node = list.head = create_node(1);
    dump(&list);
    for (i=2;i<=5;i++){
        node->next = create_node(i);
        node = node->next;
        dump(&list);
    }

    Node* a = list.head;    
    Node* c = list.head->next->next;
    remove_list_node_v2(&list, a);
    dump(&list);
    remove_list_node_v2(&list, c);
    dump(&list);
}