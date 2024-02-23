#include <iostream>
#include <queue>
#include <fstream>
#include <utility>


using namespace std;

const int MAX = 1e4 + 5;            
vector<pair<int, int> > adj[MAX];   // Adjacency list to store the graph, where each node is represented by an index
bool visited[MAX];                  // Visited array to keep track of nodes that have been processed
int dist[MAX];                      // Distance array to store the minimum distance of each node from the start node
int parent[MAX];                    //Parent array to store the previous node of each node

int dijkstra(string startString, string endString)
{
    memset(visited, false, sizeof(visited));    // Initialize the visited array to false for all nodes
    memset(dist, 0x3f, sizeof(dist));           // Initialize the distance array to a large value for all nodes
    memset(parent, -1, sizeof(parent));         //Initialize the parent array to -1 for all nodes

    int start, end{};

    //Convert input starting point to an integer
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

    //Convert input destination point to an integer
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

    // Create a priority queue to store the nodes to be processed
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({ 0, start });  // Push the start node into the priority queue with distance 0
    dist[start] = 0;

    // Loop until the priority queue is empty
    while (!pq.empty())
    {
        int u = pq.top().second;    // Get the node with the smallest distance from the start node
        pq.pop();

        if (u == end)               // Check if the node is the end node
            break;

        if (visited[u])             // Skip the node if it has already been processed
            continue;

        visited[u] = true;          // Mark the node as processed

        // Loop through all the neighbors of the node
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;            // Get the neighboring node
            int weight = adj[u][i].second;      // Get the weight of the edge between the nodes

            // Update the distance of the neighboring node if it is shorter than the current distance
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

// Convert the integer into the name of the place
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

// Print the shortest path
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

// Calculate the time taken for the journey
float calcTime(string mode, int distance) {
    float speed{};
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
    /*n = no. of nodes
    m = no. of edges
    a = node 1 representing starting place
    b = node 2 representing destination place
    w = distance between two places */

    fin >> n >> m;      // Read in the number of nodes and edges in the graph
    // Read in the edges of the graph and add them to the adjacency list
    for (int i = 0; i < m; i++)
    {
        fin >> a >> b >> w;
        adj[a].push_back({ b, w });
        adj[b].push_back({ a, w });
    }
}

int main()
{
    cout << "************************* Welcome to the Map Navigator! *************************" << endl<<endl;
    cout << "AVAILABLE PLACES: Airport  Park  Restaurant  Bank  School  University  Church"<< endl;  
    cout<<"\t\t  Hospital  Super-market  Shopping-mall  Harbour" << endl<<endl;
    cout << "MODE OF TRANSPORT: Car  Motor-bike  Foot" << endl;
    cout << "********************************************************************************" << endl << endl;
    readMap("Map.txt");
    
    string startString, endString;
    
    cout << "Starting Point : ";
    cin >> startString;

    cout << "Destination Point : ";
    cin >> endString;
    
    string mode;
    
    cout << "Mode of Transport : ";
    cin >> mode;
    
    int end = dijkstra(startString, endString);     // Call the Dijkstra's algorithm function to find the shortest path
    cout << endl<<"Total Distance of the Journey: " << dist[end] <<" km" << endl;
    cout << "Path: ";
    printPath(end);     // Call the printPath function to print the shortest path
    cout << endl;
    cout << "Time for the journey : " << calcTime(mode, dist[end])<< " mins"<<endl<<endl;
    cout << "********************** Thank you and have a safe ride! **********************" << endl<<endl;
    return 0;
}
