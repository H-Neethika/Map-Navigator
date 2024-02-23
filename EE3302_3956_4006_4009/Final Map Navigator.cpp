#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <string>
#include <fstream>
#include <map>

using namespace std;

const int MAX = 1e4 + 5;
vector<pair<int, int> > adj[MAX];
bool visited[MAX];
int dist[MAX];
int parent[MAX];

int dijkstra(string startString, string endString)
{
    memset(visited, false, sizeof(visited));
    memset(dist, 0x3f, sizeof(dist));
    memset(parent, -1, sizeof(parent));

    int start, end;

    if (startString == "Airport") {
        start = 0;
    }
    else if (startString == "Park") {
        start = 1;
    }
    else if (startString == "Restaurant") {
        start = 2;
    }
    else if (startString == "Bank") {
        start = 3;
    }
    else if (startString == "School") {
        start = 4;
    }
    else if (startString == "University") {
        start = 5;
    }
    else if (startString == "Church") {
        start = 6;
    }
    else if (startString == "Hospital") {
        start = 7;
    }
    else if (startString == "Super-market") {
        start = 8;
    }
    else if (startString == "Shopping-mall") {
        start = 9;
    }
    else if (startString == "Harbour") {
        start = 10;
    }
    else {
        cout << "Place is not found" << endl;
    }

    if (endString == "Airport") {
        end = 0;
    }
    else if (endString == "Park") {
        end = 1;
    }
    else if (endString == "Restaurant") {
        end = 2;
    }
    else if (endString == "Bank") {
        end = 3;
    }
    else if (endString == "School") {
        end = 4;
    }
    else if (endString == "University") {
        end = 5;
    }
    else if (endString == "Church") {
        end = 6;
    }
    else if (endString == "Hospital") {
        end = 7;
    }
    else if (endString == "Super-market") {
        end = 8;
    }
    else if (endString == "Shopping-mall") {
        end = 9;
    }
    else if (endString == "Harbour") {
        end = 10;
    }
    else {
        cout << "Place is not found" << endl;
    }

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({ 0, start });
    dist[start] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (u == end)
            break;

        if (visited[u])
            continue;

        visited[u] = true;
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }
    return end;
}
void place(int end) {
    switch (end) {
    case 0: 
        cout << "Airport";
        break;
    case 1:
        cout << "Park";
        break;
    case 2:
        cout << "Restaurant";
        break;
    case 3:
        cout << "Bank";
        break;
    case 4:
        cout << "School";
        break;
    case 5:
        cout << "University";
        break;
    case 6:
        cout << "Church";
        break;
    case 7:
        cout << "Hospital";
        break;
    case 8:
        cout << "Super-market";
        break;
    case 9:
        cout << "Shopping-mall";
        break;
    case 10:
        cout << "Harbour";
        break;
    }
}
void printPath(int end)
{
    if (parent[end] == -1)
    {
        place(end);
        return;
    }
    printPath(parent[end]);
    cout <<" -> ";
    place(end);
}
float transport(string mode, int distance) {
    float speed;
    if (mode == "Car") {
        speed = 60;
    }
    else if (mode == "Motor-bike") {
        speed = 50;
    }
    else if (mode == "Foot") {
        speed = 4;
    }
    else {
        cout << "Invalid mode of transport" << endl;
    }
    float time = distance / speed*60;
    return time;
}

void readMap(string path) {
    ifstream fin(path);
    int n, m, a, b;
    float w;

    fin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        fin >> a >> b >> w;
        adj[a].push_back({ b, w });
        adj[b].push_back({ a, w });
    }
}

int main()
{
    cout << "********************** Welcome to the Map Navigator! **********************" << endl<<endl;
    cout << "AVAILABLE PLACES: Airport  Park  Restaurant  Bank  School  University  Church"<< endl;  
    cout<<"\t\t  Hospital  Super-market  Shopping-mall  Harbour" << endl<<endl;
    cout << "MODES OF TRANSPORT: Car  Motor-bike  Foot" << endl;
    cout << "***************************************************************************" << endl << endl;
    readMap("Map.txt");
    
    string startString, endString;
    
    cout << "Starting Point : ";
    cin >> startString;

    cout << "Destination Point : ";
    cin >> endString;
    
    string mode;
    
    cout << "Mode of Transport : ";
    cin >> mode;
    
    int end = dijkstra(startString, endString);
    cout << endl<<"Total Distance of the Journey: " << dist[end] <<" km" << endl;
    cout << "Path: ";
    printPath(end);
    cout << endl;
    cout << "Time for the journey : " << transport(mode, dist[end])<< " mins"<<endl<<endl;
    cout << "********************** Thank you and have a safe ride! **********************" << endl<<endl;
    return 0;
}
