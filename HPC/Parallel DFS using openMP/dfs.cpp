#include <bits/stdc++.h>
using namespace std;

int nodes;
int adj_mat_s[100][100];
int adj_mat_p[100][100];
int visited_s[100]; // for sequential DFS
int visited_p[100]; // for parallel DFS

void s_DFS(int i) {
    visited_s[i] = 1; // marking current node as visited
    cout << " " << i;
    for (int j = 0; j < nodes; j++) {
        if (adj_mat_s[i][j] == 1 && !visited_s[j]) {
            s_DFS(j); // recursive call for unvisited nodes
        }
    }
}

void p_DFS(int i) {
    visited_p[i] = 1; // marking current node as visited
    #pragma omp parallel for
    for (int j = 0; j < nodes; j++) {
        if (adj_mat_p[i][j] == 1 && !visited_p[j]) {
            p_DFS(j); // recursive call for unvisited nodes
        }
    }
}

int main() {
    cout << "Enter the number of nodes: ";
    cin >> nodes;

    float density;
    cout << "Enter the graph density (0 to 1): "; // fraction of possible edges that exist
    cin >> density;


    // Create a random graph with the specified density
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (i != j && ((float)rand() / RAND_MAX) < density) {
                adj_mat_s[i][j] = 1;
                adj_mat_p[i][j] = 1;
            }
        }
    }


    auto start = chrono::high_resolution_clock::now();
    s_DFS(0); // start DFS from node 0
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "\nTime taken by sequential DFS: " << to_string(duration.count()) << " nanoseconds";

    auto start2 = chrono::high_resolution_clock::now();
    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            p_DFS(0); // start DFS from node 0
        }
    }
    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::nanoseconds>(stop2 - start2);
    cout << "\nTime taken by parallel DFS: " << to_string(duration2.count()) << " nanoseconds";

    return 0;
}
