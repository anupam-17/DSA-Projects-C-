#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjacencyList;

public:
    Graph(int V) : vertices(V), adjacencyList(V) {}

    void addEdge(int u, int v, int weight) {
        adjacencyList[u].push_back({v, weight});
        adjacencyList[v].push_back({u, weight});  // Assuming an undirected graph
    }

    void dijkstra(int startVertex) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> distance(vertices, numeric_limits<int>::max());
        vector<int> parent(vertices, -1);

        pq.push({0, startVertex});
        distance[startVertex] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const auto& neighbor : adjacencyList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;  // Update parent to reconstruct the path
                    pq.push({distance[v], v});
                }
            }
        }

        cout << "Minimum distances from vertex " << startVertex << ":\n";
        for (int i = 0; i < vertices; ++i) {
            cout << "To vertex " << i << ": " << distance[i] << "\n";
        }

        cout << "\nShortest paths:\n";
        for (int i = 0; i < vertices; ++i) {
            if (i != startVertex) {
                cout << "From vertex " << startVertex << " to " << i << ": ";
                printPath(startVertex, i, parent);
                cout << "\n";
            }
        }
    }

private:
    void printPath(int startVertex, int endVertex, const vector<int>& parent) {
        stack<int> path;
        int currentVertex = endVertex;

        while (currentVertex != startVertex) {
            path.push(currentVertex);
            currentVertex = parent[currentVertex];
        }

        cout << startVertex << " ";
        while (!path.empty()) {
            cout << "-> " << path.top() << " ";
            path.pop();
        }
    }
};

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    Graph graph(numVertices);

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    cout << "Enter the edges (source destination weight):\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    int startVertex;
    cout << "Enter the starting vertex: ";
    cin >> startVertex;

    graph.dijkstra(startVertex);

    return 0;
}
