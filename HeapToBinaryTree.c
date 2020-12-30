#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

// sirina i visina 2D polja koje se koristi za funkciju print_tree
#define WIDTH 80
#define HEIGHT 10

typedef struct node_struct {
    int key;
    struct node_struct *parent;
    struct node_struct *left;
    struct node_struct *right;
} Node;

#define PARENT(i)      ((i-1) / 2)
#define LEFT(i)        (2*(i) + 1)
#define RIGHT(i)       (2*(i) + 2)
#define HEAP_ROOT      0
#define LINE_WIDTH     70
#define SIZE(x)        (sizeof(x) / sizeof(x[0]))

typedef struct heap_struct{
    size_t size;
    int *array;
} Heap;


int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
    char b[HEIGHT];
    int i, left, right, width=7;

    if (!tree) return 0;
    sprintf(b,"(%02d:%02d)", tree->key, tree->parent ? tree->parent->key : 0);
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


void print_heap(Heap *heap) {
    int print_pos[heap->size];
    int i, j, k, pos, current_pos=1, level=0;

    if (!heap) return;
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
    return;
}

int is_max_heap(int *array, int len) {
    int i;

    for (i=len-1; i>0; i--) {
        if (array[i]>array[PARENT(i)]) {
            return 0;
        }
    }
    return 1;
}

Node *heap_to_tree(Heap *heap, Node *parent, int j) {
    Node *node;

    if(j >= heap->size) return NULL;

    node = malloc(sizeof(Node));
    node->key = heap->array[j];
    node->parent = parent;
    node->left = heap_to_tree(heap, node, LEFT(j));
    node->right = heap_to_tree(heap, node, RIGHT(j));
    return node;
}

int main() {
    int i, menu_choice, len, val;
    char c, print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
    Node *root=NULL;
    Heap *heap=NULL;

    heap = malloc(sizeof(heap));
    heap->size = 0;
    setbuf(stdout, NULL);
    do {
        DEBUG("1. Gomila iz polja u binarno stablo\n");
        DEBUG("2. Unos elemenata u gomilu (1-99)\n");
        DEBUG("3. Ispis stabla\n");
        DEBUG("4. Ispis gomile\n");
        DEBUG("5. Izlaz\n");
        scanf("%d", &menu_choice);

        switch(menu_choice) {
            case 1:
                root = heap_to_tree(heap, NULL, 0);
                break;
            case 2:
                DEBUG("\nUnesite broj elemenata gomile: ");
                scanf("%d", &len);
                if (heap->array) free(heap->array);
                heap->array = malloc(len*sizeof(int));
                heap->size = len;
                while (len>0) {
                    scanf("%d", &val);
                    if (val<1 || val>99) continue;
                    heap->array[heap->size-len] = val;
                    len--;
                }
                if (!is_max_heap(heap->array, heap->size)) {
                    DEBUG("\nUneseni niz nije max gomila.");
                    free(heap->array);
                }
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
                print_heap(heap);
                break;
            case 5:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=5);
    return 0;
}
