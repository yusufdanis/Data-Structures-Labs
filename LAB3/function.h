#define N 5

int fbArr[(N*2)+1];
int gsArr[N+1];
int num;

struct fbNode {
    int id;
    int age;
    struct fbNode *next;
};

struct gsNode {
    int id;
    struct gsNode *next;
};


struct gsNode gs[N];

int *fb_arr() {
    int i=0;

    while (1) {
        scanf("%d", &num);
        fbArr[i] = num;

        if (num==-1){
            return fbArr;
        }
    }
    
}

int *gs_arr() {
    int i=0;

    while (1) {
        scanf("%d", &num);
        
        gsArr[i] = num;

        if (num==-1){
            return gsArr;
        }
    }
}

//Creating FB Linked List
struct fbNode *create_fb(int arr[]) {
    int i=0;
    struct fbNode *fb;
    struct fbNode *ptr;
    struct fbNode *newNode;

    while (arr[i] != -1) {
        newNode = (struct fbNode*)malloc(sizeof(struct fbNode));
        newNode -> id = arr[i];
        newNode -> age = arr[i+1];
        newNode -> next = NULL;
        
        if (fb==NULL){
            fb = newNode;
            newNode -> next = NULL;
        }
        else {
            ptr = fb;
            
            while (ptr -> next != NULL) {
                    ptr = ptr -> next;
            }
                ptr -> next = newNode;
        }
        
        i = i+2;

    }

    return fb;
}

//Creating GS Linked List
struct gsNode *create_gs(int arr[]) {
    int i=0;
    struct gsNode *gs;
    struct gsNode *ptr;
    struct gsNode *newNode;

    while (arr[i] != -1) {
        newNode = (struct gsNode*)malloc(sizeof(struct gsNode));
        newNode -> id = arr[i];
        newNode -> next = NULL;
        
        if (gs==NULL){
            gs = newNode;
            newNode -> next = NULL;
        }
        else {
            ptr = gs;
            
            while (ptr -> next != NULL) {
                    ptr = ptr -> next;
            }
                ptr -> next = newNode;
        }
        
        i++;

    }

    return gs;
}

void print_fb(struct fbNode *head) {
    struct fbNode *curr = head;

    while (curr) {
        printf("%d ", curr->id);
        printf("%d\n", curr->age);

        curr = curr->next;
    }
}

void print_gs(struct gsNode *head) {
    struct gsNode *curr = head;

    while (curr) {
        printf("%d\n", curr->id);

        curr = curr->next;
    }
}