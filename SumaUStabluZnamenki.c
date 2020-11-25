#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

// najmanja i najveca dopustena vrijednost u stablu
#define MIN_VAL 0
#define MAX_VAL 9

#define MAX_TREE_STRING 100
#define MAX_NODES 100

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;

int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width = 5;

    if (!tree) return 0;
    sprintf(b,"(%03d)",tree->key);
    left = print_tree(tree->left,1,offset,depth+1,s);
    right = print_tree(tree->right,0,offset+left+width,depth+1,s);
    for (i=0; i<width; i++)
        s[depth][offset+left+i] = b[i];
    if (depth) {
        if (is_left) {
            for (i=0; i<width+right; i++)
                s[depth-1][offset+left+width/2+i] = '-';
        } else {
            for (i=0; i<left+width; i++)
                s[depth-1][offset-width/2+i] = '-';
        }
        s[depth-1][offset+left+width/2] = '.';
    }
    return left+width+right;
}

Node *add_child(Node *parent, int key, int is_left) {
    Node *new;

    new = (Node *)malloc(sizeof(Node));
    if (!new) return NULL;
    new->left = new->right = NULL;
    new->key = key;
    if (parent) {
        if (is_left==1) parent->left = new;
        else parent->right = new;
    }
    return new;
}

Node *create_tree(char *tree_string) {
    int tail, head, i=0, j=0, n, ns, size=strlen(tree_string);
    unsigned int key=0;
    Node *queue[MAX_NODES], *parent;

    tail = head = -1;
    queue[0] = parent = NULL;
    while(i<size) {
        ns = sscanf(&(tree_string[i]), " %u;%n", &key, &n);
        if (ns==1 && key>=MIN_VAL && key<=MAX_VAL && (parent || j==0))
            queue[++tail] = add_child(parent, key, j%2);
        if (j%2==0) {
            if (head>=tail) break;
            parent = queue[++head];
        }
        i += ns==1 ? n : 1;
        j++;
    }
    return queue[0];
}

int suma(Node *node, int val) {
    if(!node) return 0;

    val = val*10 + node->key;

    if(!node->left && !node->right) return val;

    return suma(node->left, val) + suma(node->right, val);
}

int main () {
    Node *root=NULL;
    int i, menu_choice;
    char c, tree_string[MAX_TREE_STRING];
    char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];

    setbuf(stdout, NULL);
    do {
        menu_choice = 0;
        DEBUG("\n1 Suma (suma)");
        DEBUG("\n2 Kreiraj stablo \n3 Ispis \n4 Izlaz\n");
        scanf("%d", &menu_choice);
        switch (menu_choice) {
            case 1:
                printf("%d\n", suma(root, 0));
                break;
            case 2:
                DEBUG("Unesite stablo kao niz znamenki odvojenih sa znakom ;\n");
                scanf(" %s", tree_string);
                root = create_tree(tree_string);
                break;
            case 3:
                sprintf(print_format, "%%%ds", WIDTH-1);
                for (i=0; i<HEIGHT; i++)
                    sprintf(s[i], print_format, " ");

                print_tree(root, 0, 0, 0, s);

                sprintf(empty_line, print_format, " ");
                for (i=0; i<HEIGHT; i++) {
                    if (strcmp(s[i],empty_line))
                        printf("%s\n", s[i]);
                }
                break;
            case 4:
                break;
            default:
                while((c = getchar()) != '\n' && c != EOF);
        }
    } while(menu_choice!=4);
    return 0;
}
