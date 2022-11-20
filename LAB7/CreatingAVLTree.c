#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *left;
    struct node *right;
    int height;
};

typedef struct node node;

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(node *N){
    if (N == NULL){
        return 0;
    }

    return (1 + max(height(N->left), height(N->right)));
}

node *right_rotate(node *N){
    node *new = N->left;
    node *temp = new->right;
 
    new->right = N;
    N->left = temp;
 
    N->height = height(N);
    new->height = height(new);
 
    return new;
}

node *left_rotate(node *N){
    node *new = N->right;
    node *temp = new->left;
 
    new->left = N;
    N->right = temp;
 
    N->height = height(N);
    new->height = height(new);
 
    return new;
}

int get_balance(node *N){
    if (N == NULL){
        return 0;
    }

    return height(N->left) - height(N->right);
}

node *insert(node* N, int data){
    if (N == NULL){
        node *new = malloc(sizeof(node));
        new->data = data;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;

        return new;
    }
 
    if (data < N->data){
        N->left  = insert(N->left, data);
    }
    else if (data > N->data){
        N->right = insert(N->right, data);
    }
    else{
        return N;
    }
    
    N->height = height(N);
 
    int balance = get_balance(N);
 
    if (balance > 1 && data < N->left->data){ // LL Case
        return right_rotate(N);
    }
    else if (balance < -1 && data > N->right->data){ // RR Case
        return left_rotate(N);
    }
    else if (balance > 1 && data > N->left->data){ // LR Case
        N->left =  left_rotate(N->left);

        return right_rotate(N);
    }
    else if (balance < -1 && data < N->right->data){   // RL Case
        N->right = right_rotate(N->right);

        return left_rotate(N);
    }
 
    return N;
}

void print_ascending(node *tree){ //Print Tree by ascending
    if (tree!=NULL){
        print_ascending(tree->left);
        printf("%d\n", tree->data);
        print_ascending(tree->right);
    }
};

void print_level(node *tree, node *top_node, int right, int level){ //Print spesific level of Tree
    if (tree == NULL){
        return;
    }

    if (level == 1){
        printf("%d ", tree->data);
        
        if (top_node != NULL){ //Print Direction and Balance
            if (right == 1){
                printf("(%d R) (%d B) ", top_node->data, get_balance(tree));
            }
            else{
                printf("(%d L) (%d B) ", top_node->data, get_balance(tree));
            }
        }    
    }
    else if (level > 1){
        print_level(tree->left, tree, 0, level - 1);
        print_level(tree->right, tree, 1, level - 1);
    }
};

void print_level_order(node *tree){ //Print all levels of Tree
    int h = height(tree);

    for (int i=1; i <= h; i++){
        print_level(tree, NULL, -1, i);
        printf("\n");
    }
};

int main(){
    int data;
    node *avlTree = NULL;
    
    while (1){ //Scan datas and create the AVL Tree
        scanf("%d", &data);
        if (data == -1){
            break;
        }
        avlTree = insert(avlTree, data);
    }

    print_ascending(avlTree);
    printf("\n");
    print_level_order(avlTree);
}