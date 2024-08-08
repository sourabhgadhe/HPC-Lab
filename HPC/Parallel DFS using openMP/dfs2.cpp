#include <bits/stdc++.h>
using namespace std;

int nodes;
int adj_mat_s[20][20];
int adj_mat_p[20][20];
int visited_s[20]; // for seq DFS
int visited_p[20]; // for parallel DFS


void s_DFS(int i) // function for DFS traversal
{

    cout<<" "<<i;
    visited_s[i] = 1; // marking current node as visited
    for (int j = 0; j < nodes; j++)
    {
        if (adj_mat_s[i][j] == 1 && !visited_s[j])
        {
            s_DFS(j); // recurrsive call for unvisited nodes
        }
    }
}


void p_DFS(int i) // function for DFS traversal
{
    visited_p[i] = 1; // marking current node as visited
    #pragma omp parallel for
    for (int j = 0; j < nodes; j++)
    {
        if (adj_mat_p[i][j] == 1 && !visited_p[j])
        {
            p_DFS(j); // recurrsive call for unvisited nodes
        }
    }
}



int main()
{
    cout << "Enter the number of nodes: "; // taking user input for nodes
    cin >> nodes;


    for (int i = 0; i < (nodes); i++)
    {
        for (int j = 0; j < nodes; j++)
        {
            char edge;
            cout << "\nIs there any route from " << i << " to " << j << " (Enter: y/n) : ";
            cin >> edge;

            if (edge == 'y')
            {
                adj_mat_s[i][j] = 1;
                adj_mat_p[i][j] = 1;
            }
            else if (edge == 'n')
            {
                adj_mat_s[i][j] = 0;
                adj_mat_p[i][j] = 0;
            }
        }
    }


    
    auto start = chrono::high_resolution_clock::now();
    s_DFS(0);
    auto stop = chrono::high_resolution_clock::now();
    auto result = stop - start;
    auto duration = chrono::duration_cast<chrono::nanoseconds>(result);
    cout<<"\nTime taken by sequential DFS: "<<to_string(duration.count())<<" nanoseconds";


    auto start2 = chrono::high_resolution_clock::now();
    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            p_DFS(0);
        }
    }
    auto stop2 = chrono::high_resolution_clock::now();
    auto result2 = stop2 - start2;
    auto duration2 = chrono::duration_cast<chrono::nanoseconds>(result2);
    cout<<"\nTime taken by parallel DFS: "<<to_string(duration2.count())<<" nanoseconds";

    return 0;
}
