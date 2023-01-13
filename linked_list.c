#include<stdio.h>

struct Node{
    int data;
    struct Node* next;
};
struct Node* head;
// In c++
// struct Node{
//     int data;
//     Node* next;
// }

void insert_at_begin(int x){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));  // We typecast here bcoz malloc returns void pointer n we need a pointer to node
    (*temp).data=x;
    temp->next=NULL;
    if(head != NULL)
        temp->next = head;
    head=temp; 

    // In c++
    // Node* A;
    // A=NULL;
    // Node* temp = new Node();
    // temp->data=2;
    // temp->next=NULL;
    // A=temp;
}

void insert_at_nth(int data,int n){
    struct Node* temp1 = (struct Node*)malloc(sizeof(struct Node));
    temp1->data = data;
    temp1->next = NULL;
    if(n==1){  // This also takes care if we had an empty list bcoz then head would be null
        temp1->next = head;
        head=temp1;
        return;
    }
    struct Node* temp2 = head;
    for(int i=0 ; i<n ; i++){  // Traversing till the (n-1)th block
        temp2=temp2->next;
    }
    temp1->next=temp2->next;  // Setting the next part of node to be inserted as the address of the nth node
    temp2->next=temp1;
}

void delete_at_nth(int n){
    struct Node* temp1 = head;
    if(n==1){
        head = temp1->next;
        free(temp1);
    }
    else{
        for(int i=1 ; i<=n-2 ; i++)
            temp1=temp1->next;  // Now temp1 points to (n-1)th node
        struct Node* temp2 = temp1->next;  // temp2 is nth node
        temp1->next = temp2->next;  // Now (n-1)th node is pointing to (n+1)th node
        free(temp2);
    }
}

void reverse_iterative(){
    struct Node *current,*prev,*next;
    current = head;
    prev = NULL;
    while(current != NULL){
        next = current->next;  // Saving the address of next node before the link of current node is reset
        current->next=prev;
        prev=current;
        current=next;
    }
}

void print_recursive(struct Node* p){
    if(p==NULL) return;
    printf("%d ",p->data);  // For printing in reverse order just swap line 78 and 79
    print_recursive(p->next);
}

void reverse_recursive(struct Node* p){
    if(p->next == NULL){
        head=p;
        return;
    }
    reverse_recursive(p->next);
    struct Node* q=p->next;
    q->next=p;
    p->next=NULL;
}

void print_list(){
    struct Node* temp=head;
    printf("List is: ");
    while(temp != NULL){
        printf(" %d",temp->data);
        temp=temp->next;
    }
    // Note- We never use the head node(A) to traverse but a different variable. Here if the node we are currently are 
    // does not point to NULL,i.e,it is not the last node we move to the next address by using the address stored in next.
    printf("\n");
}

int main(){
    head=NULL;
    printf("How many numbers? \n");
    int n,i,x;
    scanf("%d",&n);
    for (int i=0 ; i<n ; i++){
        printf("Enter number \n");
        scanf("%d",&x);
        insert_at_begin(x);
        print_list();
    }

    // insert_at_nth(2,1); // list: 2
    // insert_at_nth(3,2); // list: 2,3
    // insert_at_nth(4,1); // list: 4,2,3
    // insert_at_nth(5,2); // list: 4,5,2,3
    return 0;
}
