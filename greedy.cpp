#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

void Dijkstra(int vertex, vector<vector<int>>& AdjList)
{
    vector<bool> visited(vertex, false);
    vector<int> dist(vertex, INT_MAX);

    dist[0] = 0;

    for(int i=0;i<vertex;i++)
    {
        // select minimum weight node which is unvisited
        int node = -1;
        int value = INT_MAX;

        for(int i=0;i<vertex;i++)
        {
            if(visited[i] == false && value > dist[i])
            {
                node = i;
                value = dist[i];
            }
        }

        visited[node] = true;

        for(int i=0;i<AdjList[node].size();i++)
        {
            if(AdjList[node][i] > 0)
            {
                int neighbour = i;
                int weight = AdjList[node][i];

                if(visited[neighbour] == false && ((dist[node] + weight) < dist[neighbour]))
                {
                    dist[neighbour] = dist[node] + weight;
                }
            }
        }
    }

    // print the distances
}

void PrimsAlgorithm(int vertex, vector<vector<int>>& AdjList)
{
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> pq;
    vector<bool> isMST(vertex, false);
    vector<int> parent(vertex, -1);

    int cost = 0;

    pq.push(make_pair(0, make_pair(0, -1)));

    while(pq.size() > 0)
    {
        int weight = pq.top().first;
        int node = pq.top().second.first;
        int par = pq.top().second.second;

        pq.pop();

        if(isMST[node])
            continue;
        
        isMST[node] = true;
        cost = cost + weight;
        parent[node] = par;

        for(int i=0;i<vertex;i++)
        {
            if(AdjList[node][i] == 0)
                continue;
            
            if(isMST[i])
                continue;

            pq.push(make_pair(AdjList[node][i], make_pair(i, node)));
        }
    }

    int curr = vertex-1;
    cout<<curr+1;
    while(parent[curr] != -1)
    {
        cout<<"->"<<parent[curr]+1;
        curr = parent[curr];
    }
    cout<<endl;

    cout<<"Cost of MST:- "<<cost<<endl;
}

int findParent(int u, vector<int>& parent)
{
    if(u == parent[u])
        return u;

    // path compression and finding ultimate parent
    return parent[u] = findParent(parent[u], parent);
}

void UnionByRank(int u, int v, vector<int>& parent, vector<int>& rank)
{
    // find ultimate parent of u and v

    int pu = findParent(u, parent);
    int pv = findParent(v, parent);

    // find ranks of u and v

    // merge smaller set with larger set
    if(rank[pu] > rank[pv])
        parent[pv] = pu;
    else if(rank[pu] < rank[pv])
        parent[pu] = pv;
    else
    {
        parent[pv] = pu;
        rank[pu]++;
    }
}

void KrsukalAlgorithm(int vertex, vector<vector<int>>& AdjList)
{
    vector<int> parent(vertex);
    vector<int> rank(vertex, 0);

    for(int i=0;i<vertex;i++)
        parent[i] = i;
    
    // priority queue for finding min weighted edge

    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;

    // push all weighted edges in queue
    for(int i=0;i<vertex;i++)
    {
        for(int j=0;j<vertex;j++)
        {
            pq.push(make_pair(AdjList[i][j], make_pair(i, j)));
        }
    }

    int cost = 0;
    int edges = 0; // when edges == vertex - 1 then stop as we have to find tree

    while(pq.size() > 0)
    {
        int weight = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;

        pq.pop();

        // check if vertex u and v are in same set
        if(findParent(u, parent) == findParent(v,parent))
            continue;
        
        cost = cost + weight;
        UnionByRank(u, v, parent, rank);
        edges++;

        if(edges == vertex-1)
            break;
    }

    cout<<"Cost:- "<<cost<<endl;
}

int main()
{
    while(true)
    {
        int ch;

        cout<<"----------------------Greedy Algorithm----------------------"<<endl;
        cout<<"1. Dijkstra Algorithm"<<endl;
        cout<<"2. Prim's Algorithm"<<endl;
        cout<<"3. Kruskal's Algorithm"<<endl;
        cout<<"-1. Exit"<<endl;
        cout<<"------------------------------------------------------------"<<endl;

        cout<<"Enter your choice:- "<<endl;
        cin>>ch;

        if(ch == -1)
            break;
        
        if(ch == 1)
        {
            cout<<"Enter the number of vertices: "<<endl;
            int vertex;
            cin>>vertex;

            // Creating AdjList
            vector<vector<int>> AdjList(vertex, vector<int>(vertex, 0));

            cout<<"Enter the number of edges: "<<endl;
            int edges;
            cin>>edges;

            while(edges--)
            {
                int u,v,weight;
                cout<<"Enter the node1, node2 and weight:- "<<endl;
                cin>>u>>v>>weight;

                AdjList[u-1][v-1] = weight;
                AdjList[v-1][u-1] = weight;
            }

            Dijkstra(vertex, AdjList);
        }
        else if(ch == 2)
        {
            cout<<"Enter the number of vertices: "<<endl;
            int vertex;
            cin>>vertex;

            // Creating AdjList
            vector<vector<int>> AdjList(vertex, vector<int>(vertex, 0));

            cout<<"Enter the number of edges: "<<endl;
            int edges;
            cin>>edges;

            while(edges--)
            {
                int u,v,weight;
                cout<<"Enter the node1, node2 and weight:- "<<endl;
                cin>>u>>v>>weight;

                AdjList[u-1][v-1] = weight;
                AdjList[v-1][u-1] = weight;
            }

            PrimsAlgorithm(vertex, AdjList);
        }
        else
        {
            cout<<"Enter the number of vertices: "<<endl;
            int vertex;
            cin>>vertex;

            // Creating AdjList
            vector<vector<int>> AdjList(vertex, vector<int>(vertex, 0));

            cout<<"Enter the number of edges: "<<endl;
            int edges;
            cin>>edges;

            while(edges--)
            {
                int u,v,weight;
                cout<<"Enter the node1, node2 and weight:- "<<endl;
                cin>>u>>v>>weight;

                AdjList[u-1][v-1] = weight;
                AdjList[v-1][u-1] = weight;
            }

            KrsukalAlgorithm(vertex, AdjList);
        }
    }
    return 0;
}