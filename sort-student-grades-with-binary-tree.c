#include <stdio.h>
#include <stdlib.h>

struct grades_tree{ //Grades Tree
    int id;
    int grade;
    struct grades_tree *left;
    struct grades_tree *right;
};

typedef struct grades_tree grades_tree;

grades_tree *create(grades_tree *tree, int id, int grade){ //Create and inıtialize to Grades Tree
    if (tree==NULL){
        grades_tree *ptr = malloc(sizeof(grades_tree));
        ptr->id = id;
        ptr->grade = grade;
        ptr->left = ptr->right = NULL;
        tree = ptr;
    }
    else{
        if (grade<tree->grade){
            tree->left = create(tree->left,id,grade);
        }
        else{
            tree->right = create(tree->right,id,grade);
        }
    }

    return tree;
};

void print_ascending(grades_tree *tree){ //Print Grades Tree by ascending
    if (tree!=NULL){
        print_ascending(tree->left);
        printf("%d ", tree->id);
        printf("%d\n", tree->grade);
        print_ascending(tree->right);
    }
};

int height(grades_tree *tree){ //Calculate height of tree
    if (tree == NULL){
        return 0;
    }
    else{
        int lheight = height(tree->left);
        int rheight = height(tree->right);
 
        if (lheight > rheight){
            return (lheight + 1);
        }
        else{
            return (rheight + 1);
    }
    }
};

void print_level(grades_tree *tree, grades_tree *top_node, int right, int level){ //Print spesific level of Grades Tree
    if (tree == NULL){
        return;
    }

    if (level == 1){
        printf("%d ", tree->id);
        printf("%d ", tree->grade);
        
        if (top_node!=NULL){ //Print Direction
            if (right==1){
                printf("(%d R) ", top_node->grade);
            }
            else{
                printf("(%d L) ", top_node->grade);
            }
        }    
    }
    else if (level > 1){
        print_level(tree->left, tree, 0, level - 1);
        print_level(tree->right, tree, 1, level - 1);
    }
};

void print_level_order(grades_tree *tree){ //Print all levels of Grades Tree
    int h = height(tree);

    for (int i=1; i <= h; i++){
        print_level(tree, NULL, -1, i);
        printf("\n");
    }
};

int main(){
    int id, grade;
    grades_tree *t = NULL;
    while (1){ //Scan id and grades and create the Grades Tree
        scanf("%d", &id);
        if (id==-1){
            break;
        }
        scanf("%d", &grade);
        t = create(t, id, grade);
    }

    print_ascending(t);
    printf("\n");
    print_level_order(t);
}