#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

typedef int bool;
#define FALSE 0 \
#define TRUE 1  \

// structure for storing ip addresses
struct address_t {
    int octet[4];
    char alias[11];
    struct address_t *leftChild, *rightChild;
};

typedef struct address_t node;

// prototypes of the functions
bool greater_alias(char *s1, char *s2);

int alias_cmp(char *s1, char *s2, int l1, int l2);

void insert(node **tree, int val[], char alias[]);

node *find_by_alias(node **head, char *alias);

bool check_alias(node **head, char *alias, int *flag);

bool checkIP(node **head, int ip[], int *flag);

int update_adress(node **head);

void update(node **head, int ip[], char *alias);

void find_by_loc(node **head);

void findusingloc(node **head, int loc[], int *flag);

void inOrder(node *tree, int *count);

void print(struct address_t *root);

void write_data(node *tree, char filename[]);

//fucntion to check which alias is greater and is used in building the bst
bool greater_alias(char *s1, char *s2) {
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    for (int i = 0;
         i < l1;
         i++) {
        if (s1[i] > s2[i]) return 1;
        if (s1[i] < s2[i]) return 0;
    }
    return 0;
}

//compare two aliases and tell if they are equal or not
int alias_cmp(char *s1, char *s2, int l1, int l2) {
    if (l1 != l2) {
        return 0;
    }
    for (int i = 0;
         i < l1;
         i++) {
        char a = toupper(s1[i]);
        char b = toupper(s2[i]);
        if (a != b) {
            return 0;
        }
    }
    return 1;
}

bool checkIP(node **head, int loc[], int *flag)
//check if ip exists in bst and change the flag accordingly
{
    if (*head) {
        checkIP((&(*head)->leftChild), loc, &(*flag));
        if ((*head)->octet[0] == loc[0] && (*(head))->octet[1] == loc[1] && (*(head))->octet[2] == loc[2] &&
            (*(head))->octet[3] == loc[3]) {
            *flag = 1;
            return 1;
        }
        checkIP((&(*head)->rightChild), loc, &(*flag));
    }
    return 0;
}

bool check_alias(node **head, char *alias, bool *flag)
//check if alias exists in bst and change the flag accordingly
{
    if (*head) {
        check_alias(&((*head)->leftChild), alias, &(*flag));
        int l1 = strlen((*(head))->alias);
        int l2 = strlen(alias);
        if (alias_cmp((*(head))->alias, alias, l1, l2) == 1) {
            *flag = 1;
            return 1;
        }
        check_alias(&((*head)->rightChild), alias, &(*flag));
    }
    return 0;
}

void insert(node **tree, int val[], char alias[])
//insert node in bst
{
    node *temp = NULL;
    if ((*tree) == NULL) {
        temp = (node *) malloc(sizeof(node));
        temp->leftChild = temp->rightChild = NULL;
        for (int i = 0;
             i < 4;
             i++)
            temp->octet[i] = val[i];
        strcpy(temp->alias, alias);
        *tree = temp;
        return;
    }
    if (greater_alias((*tree)->alias, alias)) {
        insert(&(*tree)->leftChild, val, alias);
    } else {
        insert(&(*tree)->rightChild, val, alias);
    }
}

int insertAddress(node **root)
//helper function for insert
{
    char alias[11];
    char ip[25];
    char dot;
    int IP[4];
    struct address_t *add = NULL;
    bool flag = 0;

    // take user input for ip address
    printf("Enter address for %s: ", alias);
    scanf("%s", ip);

    // converts the string to int
    sscanf(ip, "%d%c%d%c%d%c%d", &IP[0], &dot, &IP[1], &dot, &IP[2], &dot, &IP[3]);
    struct address_t *t;

    // check if ip address  already exist
    flag = 0;
    checkIP(&(*(root)), IP, &flag);
    if (flag == 1) {
        // if ip address is already present we cannot use it again
        printf("ip Address already exists\n");
        return -1;
    }
    // check if ip address octets are vaild
    if (IP[0] < 0 || IP[0] > 255) {
        printf("octet must be in range [0-255]\n");
        return -1;
    }
    if (IP[0] < 0 || IP[0] > 255) {
        printf("octet must be in range [0-255]\n");
        return -1;
    }
    if (IP[0] < 0 || IP[0] > 255) {
        printf("octet must be in range [0-255]\n");
        return -1;
    }
    if (IP[0] < 0 || IP[0] > 255) {
        printf("octet must be in range [0-255]\n");
        return -1;
    }
    printf("Enter alias >> ");
    scanf("%s", alias);
    flag = 0;
    check_alias(root, alias, &flag);
    if (flag == 1) {
        // as alias does  exist . return the function
        printf("%s already exists\n", alias);
        return -1;
    }
    // testing good
    printf("%d.%d.%d.%d %s\n", IP[0], IP[1], IP[2], IP[3], alias);

    insert(&(*root), IP, alias);
    return 0;
}

node *find_by_alias(node **head, char *alias)
//find node by alias and print data of that node
{
    if (*head) {
        find_by_alias((&(*head)->leftChild), alias);
        int l1 = strlen((*(head))->alias);
        int l2 = strlen(alias);
        if (alias_cmp((*(head))->alias, alias, l1, l2) == 1) {
            printf("%s %d.%d.%d.%d\n", (*head)->alias, (*head)->octet[0], (*head)->octet[1], (*head)->octet[2],
                   (*head)->octet[3]);
            return ((*head));
        }
        find_by_alias((&(*head)->rightChild), alias);
    }
    return NULL;
}

int update_adress(node **head)
//update the node address after finding it using alias
{
    char alias[11];
    printf("Enter alias >> ");
    scanf("%s", alias);
    char ip[25];
    char dot;
    int IP[4];
    bool flag = 0;
    check_alias(&(*(head)), alias, &flag);
    if (flag != 1) {
        // as alias does  exist . return the function
        printf("%s does not exists\n", alias);
        return -1;
    }
    for (int i = 0;
         i < 4;
         i++) {
        // loop untill four valid inputs are recieved
        while (1) {
            printf("Enter location # %d\n", i + 1);
            scanf("%d", &IP[i]);

            // if valid input is received stop loop
            if (IP[i] >= 0 && IP[i] <= 255) {
                break;
            }
                // if not valid input
            else {
                printf("error: %d is an illegal entry - please reenter\n", IP[i]);
            }
        }
    }
    // check if ip address  already exist
    flag = 0;
    checkIP(&(*(head)), IP, &flag);
    if (flag == 1) {
        // if ip address is already present we cannot use it again
        printf("ip Address already exists\n");
        return -1;
    }
    //call helper function to update the address
    update(&(*head), IP, alias);
    return 0;
}

void update(node **head, int ip[], char *alias)
//helper function for update
{
    if (*head) {
        update((&(*head)->leftChild), ip, alias);
        int l1 = strlen((*(head))->alias);
        int l2 = strlen(alias);
        if (alias_cmp((*(head))->alias, alias, l1, l2) == 1) {
            //updating values
            for (int i = 0;
                 i < 4;
                 i++)
                ((*head))->octet[i] = ip[i];
        }
        update((&(*head)->rightChild), ip, alias);
    }
}

void find_by_loc(node **head)
//find the alias and IP using location
{
    int a;
    int b;
    int loc[2];

    // getting the loc octets
    for (int i = 0;
         i < 2;
         i++) {
        // loop untill valid inputs are reviewed
        while (1) {
            printf("enter locataion # %d\n", i + 1);
            scanf("%d", &loc[i]);
            if (loc[i] >= 0 && loc[i] <= 255) {
                break;
            } else {
                printf("error: %d is an illegal entry - please reenter\n", loc[i]);
            }
        }
    }
    int flag = 0;
    findusingloc(head, loc, &flag);
    if (!flag) printf("no matching location  exists\n");
}

void findusingloc(node **head, int loc[],
                  int *flag)
//helper function for find_by_loc
{
    if (*head) {
        findusingloc(&((*head)->leftChild), loc, flag);
        if ((*head)->octet[0] == loc[0] && (*head)->octet[1] == loc[1]) {
            *flag = 1;

// testingfor
            printf("%s %d.%d.%d.%d\n", (*head)->alias, (*head)->octet[0], (*head)->octet[1], (*head)->octet[2],
                   (*head)->octet[3]);

            printf("%s\n", (*head)->alias);
        }
        findusingloc((&(*head)->rightChild), loc, flag);
    }
}

void inOrder(node *tree, int *count)
//printing bst in order
{
    if (tree == NULL) return;
    inOrder(tree->leftChild, count);
    printf("%s %d.%d.%d.%d \n", tree->alias, tree->octet[0], tree->octet[1], tree->octet[2], tree->octet[3]);
    *count = *count + 1;
    inOrder(tree->rightChild, count);
}

//void print(struct address_t *root)
////wrapper function for inorder
//{
//    int *co;
//     inOrder(root,); }
// Helper function to find minimum value node in the subtree rooted at `curr`
struct address_t *minValueNode(struct address_t *node) {
    struct address_t *current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->leftChild != NULL)
        current = current->leftChild;
    return current;
}

struct address_t *Delete(struct address_t *head, char *alias, int con) {
    // base case
    if (head == NULL) {
        printf("%s not found\n", alias);
        return head;
    }
    // If the aliases to be deleted is smaller than the head alias, then it lies in left subtree
    if (greater_alias(head->alias, alias) == 1)
        //find greater alias/key
    {
        head->leftChild = Delete(head->leftChild, alias, 1);
    }
        // If the alias to be deleted is greater than the head's alias, then it lies in right subtree
    else if (greater_alias(alias, head->alias) == 1) {
        head->rightChild = Delete(head->rightChild, alias, 1);
    } else {
        if (con) {
            char conf;
            int a = head->octet[0];
            int b = head->octet[1];
            int c = head->octet[2];
            int d = head->octet[3];

            // priting confirmation
            printf("delete %s %d.%d.%d.%d ?(y/n)\n", alias, a, b, c, d);
            scanf(" %c", &conf);

            // if user select no.. we cannot delete
            if (conf == 'n') {
                // printf("not deleted\n");

                return head;
            }
        }
        // if node has only one child or no child
        if (head->leftChild == NULL) {
            printf("left deleted\n");
            struct address_t *temp = head->rightChild;
            free(head);
            return temp;
        } else if (head->rightChild == NULL) {
            printf("right deleted\n");
            struct address_t *temp = head->leftChild;
            free(head);
            return temp;
        }
        // if node has two children then get the inorder susccessor
        // minimum in the right subtree
        struct address_t *temp = minValueNode(head->rightChild);

        // Copy the successor's content to this node
        strcpy(head->alias, temp->alias);

        // Delete the inorder successor
        head->rightChild = Delete(head->rightChild, temp->alias, 0);
    }
    return head;
}

// read the file and store in the Binary tree
int read_file(node **tree, char *file_path) {
    char ip[15];
    int IP[4];
    char alias[32];
    int a, b, c, d;
    char dot;

    // opening the file in read mode
    FILE *fptr = fopen(file_path, "r");
    if (fptr == NULL) {
        printf("error: file cannot be opened\n");
        return -1;
    }
    while (!feof(fptr)) {
        // reading formatted file
        fscanf(fptr, "%d%c%d%c%d%c%d %s", &a, &dot, &b, &dot, &c, &dot, &d, alias);

        // if data is read
        if (strlen(alias) != 0) {
            IP[0] = a;
            IP[1] = b;
            IP[2] = c;
            IP[3] = d;

            // passing the last argument 0 to indicate no user input
            insert(&(*tree), IP, alias);
        }
        // clearing the buffers
        strcpy(ip, "");
        strcpy(alias, "");
    }
    // closing the file
    fclose(fptr);
    return 0;
}

void save_list(node *head) {
    char filename[100] = {"output.txt"};

    // TWO LINES BELOW testing
    printf("Enter file name >> ");

    scanf("%s", filename);
    FILE *fptr = fopen(filename, "w");

    //if file cannot be opened
    if (fptr == NULL) {
        printf("cannot open output file\n");
        return;
    }
    //if list is emtpy
    if (head == NULL) {
        printf("tree is empty\n");
        return;
    }
    fclose(fptr);

    // printing to file
    write_data(head, filename);

    /// closing the file
    return;
}

void write_data(node *tree, char filename[]) {
    if (tree == NULL) return;
    write_data(tree->leftChild, filename);

    //Appending the each node one at a time in file
    FILE *fptr;

    /*  Open all file in append mode. */
    fptr = fopen(filename, "a");
    fprintf(fptr, "%s %d.%d.%d.%d \n", tree->alias, tree->octet[0], tree->octet[1], tree->octet[2], tree->octet[3]);
    fclose(fptr);
    write_data(((tree))->rightChild, filename);
}


int main() {
    struct address_t *root;
    root = NULL;
    int choice;
    read_file(&root, "/home/hilla/Desktop/C_PLAIN/linked_dsa_NO2/CS531_Inet.txt");
    while (1) {
        printf("\n=============================================\n");
        printf("1)Add address\n");
        printf("2)Look up address\n");
        printf("3)Update address\n");
        printf("4)Delete address\n");
        printf("5)Display Tree\n");
        printf("6)Display aliases for location\n");
        printf("7)Save to file\n");
        printf("8)Quit\n");
        printf("\n=============================================\n");
        printf("Enter Option >> ");
        scanf("%d", &choice);

        // using a switch for selecting options
        switch (choice) {
            // if user select one
            case 1: {
                insertAddress(&root);
                break;
            }
            case 2: {
                char alias[11];
                printf("Enter alias >> ");
                scanf("%s", alias);
                bool flag = 0;
                check_alias(&root, alias, &flag);
                if (flag == 1) find_by_alias(&root, alias);
                else printf("%s does not exists\n", alias);
                break;
            }
            case 3: {
                update_adress(&root);
                break;
            }
            case 4: {
                char alias[11];
                printf("Enter Alias to delete:  ");
                scanf("%s", alias);
                Delete(root, alias, 1);
                break;
            }
            case 5: {
                int count = 0;
                inOrder(root, &count);
                printf("total node count: %d\n", count);
                break;
            }
            case 6: {
                find_by_loc(&root);
                break;
            }
            case 7: {
                //save_list(&root);

                char filename[100];
                printf("Enter file name >> ");
                scanf("%s", filename);
                fclose(fopen(filename, "w"));

                //It will erase all data in file and create a new one if the file does not exist
                write_data(root, filename);
                break;
            }
            case 8: {
                printf("Good bye!\n");
                return 0;
                break;
            }
            default: {
                //if value is not in range
                printf("error: invalid selection \n");
                break;
            }
        }
    }
    return 0;
}