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

void delete_vertex(Graph *g, int u) {

    if(!g || g->nvertices < 1 || u < 0 || u >= g->nvertices) return;

    //u - index vrha kojeg zelimo obrisati
    //polje labels - skup svih vrhova u grafu
    for (int i = u; i < g->nvertices-1; ++i){
        g->labels[i] = g->labels[i+1];
    }

    for (int i = 0; i < g->nvertices-1; ++i){
        for (int j = 0; j < g->nvertices-1; ++j){
            g->adj[i][j] = g->adj[i+(i>=u)][j+(j>=u)];
        }
    }

    g->nvertices--;
}


int main() {
    Graph *g=NULL;
    int u, menu_choice;
    char label, c;

    do {
        DEBUG("1. Obrisi vrh\n");
        DEBUG("2. Unos grafa\n");
        DEBUG("3. Ispisi\n");
        DEBUG("4. Izlaz\n");
        DEBUG("Odabir:\t");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                DEBUG("Unesite oznaku vrha: ");
                scanf(" %c", &label);
                delete_vertex(g, find_vertex_index(g, label));
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
