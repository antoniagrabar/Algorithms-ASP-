#include<stdio.h>
#include<stdlib.h>
#define MAXV 100


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define TRUE  1
#define FALSE 0
typedef int bool;

#define WHITE 0
#define GRAY  1
#define BLACK 2
typedef int color;

typedef struct {
    int adj[MAXV][MAXV];
    int nvertices;
    char labels[MAXV];
    int next[MAXV];
    color colors[MAXV];
} graph;

int find_vertex_index(graph *g, char label) {
    int u;

    for (u=0; u<g->nvertices; u++) {
        if (g->labels[u]==label)
            return u;
    }
    return -1;
}

void initialize_attributes(graph *g) {
    int v;

    for (v=0; v<g->nvertices; v++) {
        g->next[v] = -1;
        g->colors[v] = WHITE;
    }
}

graph *initialize_graph() {
    int u, v;
    graph *g;

    g = (graph *)malloc(sizeof(graph));
    if (!g) return NULL;
    g->nvertices = 0;
    for (u=0; u<MAXV; u++) {
        for (v=0; v<MAXV; v++) {
            g->adj[u][v] = 0;
        }
    }
    initialize_attributes(g);
    return g;
}

void print_graph(graph *g) {
    int u,v;

    for (u=0; u<g->nvertices; u++) {
        printf("%c: ",g->labels[u]);
        for (v=0; v<g->nvertices; v++) {
            if (g->adj[u][v])
                printf(" %c",g->labels[v]);
        }
        printf("\n");
    }
}

int add_vertex(graph *g, char label) {
    int u;

    u = g->nvertices++;
    g->labels[u] = label;
    return u;
}

void insert_edge_vertices(graph *g) {
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

void read_graph(graph *g) {
    int i, nedges;

    DEBUG("Unesite broj bridova: ");
    scanf("%d",&nedges);
    for (i=0; i<nedges; i++) {
        DEBUG("Unesite oznake vrhova brida %d ", i+1);
        insert_edge_vertices(g);
    }
}

void dfs(graph *g, int u) {
    int v;

    g->colors[u] = GRAY;
    for (v=0; v<g->nvertices; v++) {
        if (g->adj[u][v]) {
            if (g->colors[v]==WHITE) {
                dfs(g,v);
            }
        }
    }
    g->colors[u] = BLACK;
}

int num_neighbors(graph *g, int u){
    int sum = 0;
    for(int v = 0; v < g->nvertices; v++){
        if(g->adj[u][v]) sum++;
    }
    return sum;
}

bool eulerov_put(graph *g) {
    int odd, u;

    //Pronađi prvi vrh koji ima susjeda
    for (u = 0; u < g->nvertices; u++){
        if(num_neighbors(g,u)) break;
    }

    // Ako nema bridova u grafu postoji trivijalan Eulerov put duljine 0
    if(u == g->nvertices) return TRUE;

    dfs(g,u);

    //Provjeri jesu li svi neposjeceni vrhovi izolirani
    for (u = 0; u < g->nvertices; u++){
        if(g->colors[u]!=BLACK){
            if(num_neighbors(g,u)) return FALSE;
        }
    }

    //Prebroji vrhove s neparnim brojem susjeda
    odd = 0;
    for (u = 0; u < g->nvertices; u++){
        if((num_neighbors(g,u))%2) odd++;
    }

    //Ako ih je vise od 2 graf ne sadrzi Eulerov put
    //Broj vrhova s neparnim susjedima ne moze biti 1 za neusmjereni graf

    return (odd > 2) ? FALSE : TRUE;
    
}

int main() {
    graph *g=NULL;
    int menu_choice;
    char c;

    setbuf(stdout, NULL);
    do {
        DEBUG("\n1.Postoji li Eulerov put (eulerov_put)");
        DEBUG("\n2.Unos grafa\n3.Ispis grafa\n4.Izlaz\n");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                initialize_attributes(g);
                printf("%c\n", eulerov_put(g) ? 'Y' : 'N');
                break;
            case 2:
                if (g) free(g);
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
