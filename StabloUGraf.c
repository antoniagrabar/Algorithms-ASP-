#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
} Node;

void add_node(Node **root, int key) {
  Node *new_node, *trenutni, *prethodni=NULL;

  new_node = malloc(sizeof(Node));
  new_node->key = key;
  new_node->left = new_node->right = NULL;

  trenutni = *root;
  while (trenutni!=NULL) {
    prethodni = trenutni;
    if (new_node->key < trenutni->key) {
      trenutni = trenutni->left;
    } else {
      trenutni = trenutni->right;
    }
  }

  new_node->parent = prethodni;
  if (prethodni==NULL) {
    *root = new_node;
  } else if (new_node->key < prethodni->key) {
    prethodni->left = new_node;
  } else {
    prethodni->right = new_node;
  }
}

int print_tree(Node *tree, int is_left, int offset, int depth, char s[HEIGHT][WIDTH]) {
  int i, left, right, width=5;
  char b[width+1];

  if (!tree)
    return (0);
  sprintf(b,"(%03d)",tree->key);
  left = print_tree(tree->left,1,offset,depth+1,s);
  right = print_tree(tree->right,0,offset+left+width,depth+1,s);
  for (i=0; i<width; i++) {
    s[depth][offset+left+i] = b[i];
  }
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
  return (left+width+right);
}

void stablo_u_graf(Node *node, int **g) {
    if(node == NULL) return;

    if(node->parent)
        g[node->key][node->parent->key] = 1;
    if(node->left)
        g[node->key][node->left->key] = 1;
    if(node->right)
        g[node->key][node->right->key] = 1;

    stablo_u_graf(node->left, g);
    stablo_u_graf(node->right, g);

}

void print_graph(int **g, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%d ", g[i][j]);
    printf("\n");
  }
}

int main() {
  int i, n , val;
  char print_format[6], empty_line[WIDTH], s[HEIGHT][WIDTH];
  Node *root = NULL;
  int **g;

  scanf("%d", &n);

  g = malloc(sizeof(int*) * n);

  for (i = 0; i < n; i++) {
    g[i] = calloc(n, sizeof(int));
  }

  for (i = 0; i < n; i++) {
    do {
      scanf("%d", &val);
    } while (val < 0 || val >= n);

    add_node(&root, val);
  }

  sprintf(print_format, "%%%ds", WIDTH-1);
  for (i=0; i<HEIGHT; i++)
    sprintf(s[i], print_format, " ");

  print_tree(root,0,0,0,s);

  sprintf(empty_line, print_format, " ");
  for (i=0; i<HEIGHT; i++) {
    if (strcmp(s[i],empty_line)) {
      printf("%s\n", s[i]);
    }
  }

  stablo_u_graf(root, g);
  printf("\n");

  print_graph(g, n);

  for (i = 0; i < n; i++) {
    free(g[i]);
  }
  free(g);

  return (0);
}
