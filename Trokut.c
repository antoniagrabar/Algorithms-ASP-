#include<stdio.h>
#include<stdlib.h>


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXV 100

#define TRUE  1
#define FALSE 0
typedef int bool;

typedef struct {
    int adj[MAXV][MAXV];
    int nvertices;
    char labels[MAXV];
} Graph;

int find_vertex_index(Graph *g, char label) {
    int u;

    if (!g) return -1;
    for (u=0; u<g->nvertices; u++) {
        if (g->labels[u]==label)
            return u;
    }
    return -1;
}

Graph *initialize_graph() {
    int u, v;
    Graph *g;

    g = (Graph *)malloc(sizeof(Graph));
    if (!g) return NULL;
    g->nvertices = 0;
    for (u=0; u<MAXV; u++) {
        for (v=0; v<MAXV; v++) {
            g->adj[u][v] = 0;
        }
    }
    return g;
}

void print_graph(Graph *g) {
    int u,v;

    for (u=0; u<g->nvertices; u++) {
        printf("%c: ",g->labels[u]);
        for (v=0; v<g->nvertices; v++) {
            if (g->adj[u][v])
                printf(" %c",g->labels[v]);
        }
        printf("\n");
    }
    printf("\n");
}

int add_vertex(Graph *g, char label) {
    int u;

    u = g->nvertices++;
    g->labels[u] = label;
    return u;
}

void insert_edge_vertices(Graph *g) {
    char label;
    int u, v;

    scanf(" %c",&label);
    u = find_vertex_index(g, label);
    if (u==-1) u = add_vertex(g, label);
    scanf(" %c", &label);
    if (label=='/') return;
    v = find_vertex_index(g, label);
    if (v==-1) v = add_vertex(g, label);
    g->adj[u][v] = g->adj[v][u] = 1;
}

void read_graph(Graph *g) {
    int i, nedges;

    DEBUG("Unesite broj bridova: ");
    scanf("%d",&nedges);
    for (i=0; i<nedges; i++) {
        DEBUG("Unesite oznake vrhova brida %d ", i+1);
        insert_edge_vertices(g);
    }
}

bool triangle_exists(Graph *g) {
    if(!g) return FALSE;

    for (int i = 0; i < g->nvertices; ++i){
        for (int j = 0; j < g->nvertices; ++j){
            if(g->adj[i][j]){
                for (int k = 0; k < g->nvertices; ++k){
                    if (g->adj[k][i] && g->adj[k][j]){
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}


int main() {
    Graph *g=NULL;
    int u, menu_choice;
    char label, c;

    do {
        DEBUG("1. Postoji trokut\n");
        DEBUG("2. Unos grafa\n");
        DEBUG("3. Ispisi\n");
        DEBUG("4. Izlaz\n");
        DEBUG("Odabir:\t");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                printf("%c\n", triangle_exists(g) ? 'Y' : 'N');
                break;
            case 2:
                if (g) free (g);
                g = initialize_graph();
                if (!g) DEBUG("Neuspjesna inicijalizacija.");
                read_graph(g);
                break;
            case 3:
                DEBUG("\nIspis grafa:\n");
                print_graph(g);
                break;
            case 4:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=4);
    return 0;
}
