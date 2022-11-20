#include <stdio.h>
#include <stdlib.h>

struct node{
    int d;
    int c; // 0: Black, 1: Red
    struct node* p;
    struct node* l;
    struct node* r;
};

typedef struct node node;

node *root = NULL;

node *insert(node* root, node *temp){
    if (root == NULL){
        return temp;
    }

    if (temp->d < root->d){
        root->l = insert(root->l, temp);
        root->l->p = root;
    }
    else{
        root->r = insert(root->r, temp);
        root->r->p = root;
    }

    return root;
}

void right_rotate(node *temp){
    node *left = temp->l;
    temp->l = left->r;

    if (temp->l){
        temp->l->p = temp;
    }

    left->p = temp->p;

    if (!temp->p){
        root = left;
    }
    else if (temp == temp->p->l){
        temp->p->l = left;
    }
    else{
        temp->p->r = left;
    }

    left->r = temp;
    temp->p = left;
}

void left_rotate(node *temp){
    node *right = temp->r;
    temp->r = right->l;

    if (temp->r){
        temp->r->p = temp;
    }

    right->p = temp->p;

    if (!temp->p){
        root = right;
    }
    else if (temp == temp->p->l){
        temp->p->l = right;
    }
    else{
        temp->p->r = right;
    }

    right->l = temp;
    temp->p = right;
}

void fix_up(node *root, node *ptr){
    node *parent = NULL;
    node *grandParent = NULL;
 
    while ((ptr != root) && (ptr->c != 0) && (ptr->p->c == 1)){
        parent = ptr->p;
        grandParent = ptr->p->p;
 
        if (parent == grandParent->l){  // CaseA: Parent is left child of Grand Parent
            node *uncle = grandParent->r;

            if (uncle != NULL && uncle->c == 1){    // Case1: The uncle of ptr is red
                grandParent->c = 1;
                parent->c = 0;
                uncle->c = 0;
                ptr = grandParent;
            }
            else{
                if (ptr == parent->r){  // Case2: Ptr is right child of its parent
                    left_rotate(parent);
                    ptr = parent;
                    parent = ptr->p;
                }

                right_rotate(grandParent);  //Case3: Ptr is left child of its parent
                int color = parent->c;
                parent->c = grandParent->c;
                grandParent->c = color;
                ptr = parent;
            }
        }
        else{   // CaseB: Parent is right child of Grand Parent
            node *uncle = grandParent->l;

            if ((uncle != NULL) && (uncle->c == 1)){    // Case1: The uncle of ptr is also red
                grandParent->c = 1;
                parent->c = 0;
                uncle->c = 0;
                ptr = grandParent;
            }
            else{   // Case2: Ptr is left child of its parent
                if (ptr == parent->l){
                    right_rotate(parent);
                    ptr = parent;
                    parent = ptr->p;
                }

                left_rotate(grandParent);   // Case3: Ptr is right child of its parent
                int color = parent->c;
                parent->c = grandParent->c;
                grandParent->c = color;
                ptr = parent;
            }
        }
    }

    root->c = 0;
}

void print_ascending(node *tree){ //Print Tree by ascending
    if (tree!=NULL){
        print_ascending(tree->l);
        printf("%d\n", tree->d);
        print_ascending(tree->r);
    }
};

int max(int a, int b){
    return (a > b) ? a : b;
}

int height(node *N){
    if (N == NULL){
        return 0;
    }

    return (1 + max(height(N->l), height(N->r)));
}

void print_level(node *tree, node *top_node, int right, int level){ //Print spesific level of Tree
    if (tree == NULL){
        return;
    }

    if (level == 1){
        printf("%d ", tree->d);
        
        if (top_node != NULL){ //Print Direction
            if (right == 1){
                printf("(%d R) ", top_node->d);
            }
            else{
                printf("(%d L) ", top_node->d);
            }
        }    
    }
    else if (level > 1){
        print_level(tree->l, tree, 0, level - 1);
        print_level(tree->r, tree, 1, level - 1);
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
    node *redBlackTree = NULL;
    
    while (1){ //Scan datas and create the Red Black Tree
        scanf("%d", &data);
        if (data == -1){
            break;
        }
        node *temp = malloc(sizeof(node));
        temp->d = data;
        temp->l = NULL;
        temp->r = NULL;
        temp->p = NULL;
        temp->c = 1;

        redBlackTree = insert(redBlackTree, temp);
        fix_up(redBlackTree, temp);
    }

    print_ascending(redBlackTree);
    printf("\n");
    print_level_order(redBlackTree);
}