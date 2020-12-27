#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

typedef struct node_struct{
    int key;
    struct node_struct *parent;
    struct node_struct *left;
    struct node_struct *right;
}Node;

Node *add_node(Node *node, Node *parent, int key) {
    if (!node) {
        node = (Node*) malloc(sizeof(Node));
        node->key = key;
        node->parent = parent;
        node->left = node->right = NULL;
        return node;
    }

    if (key < node->key) {
        node->left = add_node(node->left,node,key);
    } else {
        node->right = add_node(node->right,node,key);
    }
    return node;
}

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

#define PARENT(i)      ((i-1) / 2)
#define LEFT(i)        (2*(i) + 1)
#define RIGHT(i)       (2*(i) + 2)
#define HEAP_ROOT      0
#define LINE_WIDTH     70
#define SIZE(x)        (sizeof(x) / sizeof(x[0]))

typedef struct heap_struct{
    size_t size;   // broj elemenata u gomili
    size_t length; // broj elemenata u polju
    int *array;
}Heap;

int print_heap(Heap *heap) {
    int print_pos[heap->size];
    int i, j, k, pos, current_pos=1, level=0;

    print_pos[HEAP_ROOT] = 0;
    for(i=0,j=1; i<heap->size; i++,j++) {
        pos = print_pos[PARENT(i)] + (i%2?-1:1)*(LINE_WIDTH/(pow(2,level+1))+1);
        for (k=0; k<pos-current_pos; k++) printf("%c",i==0||i%2?' ':'-');
        printf("%d",heap->array[i]);
        print_pos[i] = current_pos = pos+1;
        if (j==pow(2,level)) {
            printf("\n");
            level++;
            current_pos = 1;
            j = 0;
        }
    }
    printf("\n");
    return 0;
}

int total_nodes(Node *n){
    if(!n) return 0;
    return total_nodes(n->left) + total_nodes(n->right) + 1;
}

void reverse_in_order(Node *n, Heap *heap){
    if(!n) return;

    reverse_in_order(n->right, heap);
    heap->array[heap->size++] = n->key;
    reverse_in_order(n->left, heap);
}

Heap *create_heap(Node *root){
    int tree_size;
    Heap *heap;

    tree_size = total_nodes(root);
    heap = (Heap*)malloc(sizeof(Heap));
    heap->array = malloc(tree_size*sizeof(int));
    heap->length = tree_size;
    heap->size = 0;
    reverse_in_order(root, heap);
    return heap;
}

int main() {
    int i, menu_choice, val;
    char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    Node *new_node, *root = NULL;
    Heap *heap=NULL;

    setbuf(stdout, NULL);
    do {
        //DEBUG("\n1 opis funkcije (ime_funkcije)");
        DEBUG("\n2.Unos elemenata u stablo (1-999)\n3.Ispis stabla\n4.Ispis gomile\n5.Izlaz\n");
        scanf("%d", &menu_choice);

        switch(menu_choice) {
            case 1:
                heap = create_heap(root);
                break;
            case 2:
                DEBUG("Unos zakljucite bilo kojim nebrojcanim znakom: ");
                while (scanf("%d", &val)==1) {
                    if (val<1 || val>999) continue;
                    new_node = add_node(root,NULL,val);
                    if (new_node) root = new_node;
                }
                while((c=getchar())!='\n' && c!=EOF);
                break;
            case 3:
                sprintf(print_format, "%%%ds", WIDTH-1);
                for (i=0; i<HEIGHT; i++)
                    sprintf(s[i], print_format, " ");

                print_tree(root,0,0,0,s);

                sprintf(empty_line, print_format, " ");
                for (i=0; i<HEIGHT; i++) {
                    if (strcmp(s[i],empty_line))
                        printf("%s\n", s[i]);
                }
                break;
            case 4:
                if (heap) print_heap(heap);
                break;
            case 5:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=5);
    return 0;
}
