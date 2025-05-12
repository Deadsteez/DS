#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define INF 99

int G[MAX][MAX], par[MAX], n;
int ne = 1;

int find_par(int i) {
    while (i != par[i])
        i = par[i];
    return i;
}

int union_sets(int i, int j) {
    if (i != j) {
        par[j] = i;
        return 1;
    }
    return 0;
}

void kruskal_matrix() {
    int i, j, a, b, u, v, min, min_wt = 0;
    ne = 1;

    for (i = 0; i < n; i++) 
        par[i] = i;

    printf("\nMST using Adjacency Matrix:\n");

    while (ne < n) {
        min = INF;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (G[i][j] < min) {
                    min = G[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }

        u = find_par(u);
        v = find_par(v);

        if (union_sets(u, v)) {
            printf("Edge %d: %d - %d = %d\n", ne++, a, b, min);
            min_wt += min;
        }

        G[a][b] = G[b][a] = INF;
    }

    printf("Total weight = %d\n", min_wt);
}

int main() {
    int i, j;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (i = 0; i < n; i++) {
        par[i] = i;
        for (j = 0; j < n; j++) {
            scanf("%d", &G[i][j]);
            if (G[i][j] == 0)
                G[i][j] = INF;
        }
    }

    kruskal_matrix();

    return 0;
}
