#include<bits/stdc++.h>
using namespace std;


#ifndef DEBUG
#define DEBUG(...) printf(__VA_ARGS__)
#endif

#define MAXV 100
#define WHITE 0
#define GRAY  1
#define BLACK 2
typedef int color;

typedef struct {
    int adj[MAXV][MAXV];
    int nvertices;
    char labels[MAXV];
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

void process_vertex(graph *g, int u) {
    printf("Obradjujem vrh %c\n", g->labels[u]);
}

void process_edge(graph *g, int u, int v) {
    printf("Obradjujem brid (%c,%c)\n", g->labels[u], g->labels[v]);
}

void bfs(graph *g, int u) {
    queue<int> q;
    q.push(u);

    g->colors[u] = GRAY;

    while ((!q.empty())){
        u = q.front();
        q.pop();

        process_vertex(g,u);

        for (int v = 0; v < g->nvertices; v++){
            //provjera ako je v susjed od u
            if(g->adj[u][v]){
                //ako cvor nije bio posjecen, posjeti ga
                if(g->colors[v] == WHITE){
                    q.push(v);
                    g->colors[v] = GRAY;
                    process_edge(g,u,v);
                }
            }
        }
        
    }
    
}

void dfs_rec(graph *g, int u) {
    g->colors[u] = GRAY;
    for (int v = 0; v < g->nvertices; v++){
        if(g->adj[u][v]){
            if(g->colors[v] == WHITE){
                process_edge(g,u,v);
                dfs_rec(g,v);
            }
        }
    }

    g->colors[u] = BLACK;
    process_vertex(g,u);
    
}

void dfs(graph *g, int u) {
    stack <int> s;
    s.push(u);
    g->colors[u] = GRAY;

    while(!s.empty()){
        int u = s.top();

        bool found = false;
        for(int v = 0; v < g->nvertices; v++){
            if(g->adj[u][v]){
                if(g->colors[v] == WHITE){
                    s.push(v);
                    g->colors[v] = GRAY;
                    process_edge(g,u,v);
                    found = true;
                    break;
                }
            }
        }

        if(!found){
            s.pop();
            g->colors[u] = BLACK;
            process_vertex(g,u);
        }
    }
}

void initialize_attributes(graph *g) {
    int v;

    for (v=0; v<g->nvertices; v++) {
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

int main() {
    graph *g=NULL;
    int u,menu_choice;
    char label,c;

    do {
        DEBUG("\n1.Unos grafa\n");
        DEBUG("2.Ispisi\n");
        DEBUG("3.BFS\n");
        DEBUG("4.DFS\n");
        DEBUG("5.DFS rekurzivno\n");
        DEBUG("6.Izlaz\n");
        DEBUG("Odabir:\t");
        scanf("%d", &menu_choice);
        switch(menu_choice) {
            case 1:
                if (g) free (g);
                g = initialize_graph();
                if (!g) DEBUG("Neuspjesna inicijalizacija.");
                read_graph(g);
                break;
            case 2:
                DEBUG("\nIspis grafa:\n");
                print_graph(g);
                break;
            case 3:
                DEBUG("\nUnesite oznaku vrha:\n");
                scanf(" %c", &label);
                u = find_vertex_index(g, label);
                if (u==-1) break;
                initialize_attributes(g);
                DEBUG("\nPretrazivanje prvo u sirinu:\n");
                bfs(g, u);
                break;
            case 4:
                DEBUG("\nUnesite oznaku vrha:\n");
                scanf(" %c",&label);
                u = find_vertex_index(g, label);
                if (u==-1) break;
                initialize_attributes(g);
                DEBUG("\nPretrazivanje prvo u dubinu:\n");
                dfs(g, u);
                break;
            case 5:
                DEBUG("\nUnesite oznaku vrha:\n");
                scanf(" %c",&label);
                u = find_vertex_index(g, label);
                if (u==-1) break;
                initialize_attributes(g);
                DEBUG("\nRekurzivno pretrazivanje prvo u dubinu:\n");
                dfs_rec(g, u);
                break;
            case 6:
                break;
            default:
                while((c=getchar())!='\n' && c!=EOF);
        }
    } while(menu_choice!=6);
    return 0;
}
