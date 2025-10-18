#include <bits/stdc++.h>
using namespace std;

void get_path(int v , vector<int> parent){
    vector<int> path;
    while(v!=-1){
        path.push_back(v);
        v=parent[v];
    }
    reverse(path.begin(),path.end());
    cout << "\t( ";
    for(int i = 0 ; i < (int)path.size(); i++){
        cout << path[i] << " ";
    }
    cout << ")\n";
}

void bellman_ford(vector<vector<pair<int,int>>>& adj, vector<int>& parent, int n , int m, int src){
    vector<int> dist(n+1,1e9);
    dist[src]=0;

    for(int i = 0 ; i < n-1 ; i++){
        for(int u =1 ; u <= n ; u++){
            for(auto[v,w]:adj[u]){
                if(dist[u]!=1e9 && dist[u]+w < dist[v]){
                    dist[v]=dist[u]+w;
                    parent[v]=u;
                }
            }            
        }
    }
    for(int u =1 ; u <= n ; u++){
        for(auto[v,w]:adj[u]){
            if(dist[u]!=1e9 && dist[u]+w < dist[v]){
                cout << "Negative edge cycle detected\n";return;
            }
        } 
    }
    cout << "node\tdist\tpath\n";
    for(int i = 1 ; i<= n ; i++){
        cout << i << "  :   " << dist[i];
        get_path(i,parent);
    }
    
}


int main(){
    int n , m;
    cout << "Enter the no of nodes (1 based graph) :";
    cin >> n;
    cout << "Enter the no of directed edges :";
    cin >> m;
    vector<vector<pair<int,int>>> adj(n+1);
    cout << "Enter " << m << " edges : (source , destination , wt)" << endl;
    for(int i = 0 ; i < m ; i++){
        int u , v , w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
    }
    int src;
    cout << "Enter source node : ";
    cin >> src;
    vector<int> parent(n+1,-1);
    bellman_ford(adj,parent,n,m,src);
}

/*

#################  TEST CASE 1 ###################### 

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/DAA/Design-of-Analysis-Algorithm---DAA (main)
$ ./b
Enter the no of nodes (1 based graph) :5
Enter the no of directed edges :6
Enter 6 edges : (source , destination , wt)
1 2 2
1 3 2
2 5 6
2 4 2
3 4 3
4 5 3
Enter source node : 1
node    dist    path
1  :   0        ( 1 )
2  :   2        ( 1 2 )
3  :   2        ( 1 3 )
4  :   4        ( 1 2 4 )
5  :   7        ( 1 2 4 5 )

#################  TEST CASE 2 ###################### 

Admin@DESKTOP-KMA1ERO MINGW64 /f/ME/3-Year/LABS/DAA/Design-of-Analysis-Algorithm---DAA (main)
$ ./b
Enter the no of nodes (1 based graph) :3
Enter the no of directed edges :3
Enter 3 edges : (source , destination , wt)
1 2 -2
2 3 -4
3 1 4
Enter source node : 1
Negative edge cycle detected

*/
