#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

// Base class for graph algorithms (for queries)
class GraphAlgorithm
{
public:
    GraphAlgorithm() {}
    GraphAlgorithm(vector<set<int>> &adjList) { dependencies = adjList; }

    virtual void query() = 0; // Pure virtual for derived classes

    void runDFSForAll();             // Run DFS to detect cycles and fill topOrder
    void DFS(int node);              // DFS for cycle detection and topOrder
    void DFSCollect(set<int> &sccSet, int node); // DFS for SCC collection on transpose
    void findSCCs();                 // Finds strongly connected components
    void computeTopologicalOrder();  // Lex min topological sort using Kahn's algorithm

public:
    vector<set<int>> dependencies;   // Adjacency list
    vector<char> color;              // 'w' = white, 'g' = gray, 'b' = black
    bool hasCycle = false;           // True if a cycle is detected
    vector<int> topOrder;            // Reverse post-order for topological sort
    vector<set<int>> sccList;        // List of SCCs
    unordered_map<int, int> sccIdMap;// Maps node to its SCC id
    vector<set<int>> transpose;      // Transposed graph
    vector<set<int>> sccDependencies;// Condensed SCC graph
    vector<int> hypeScores;          // Hype scores per event
    vector<int> sccHypeScores;       // Total hype per SCC
    vector<int> validTopOrder;       // Lex min valid topological order
};

void GraphAlgorithm::runDFSForAll()
{
    int n = dependencies.size();
    hasCycle = false;
    color.assign(n, 'w');

    for (int i = 1; i < n; i++) {
        if (color[i] == 'w') {
            DFS(i);
        }
    }
}

void GraphAlgorithm::DFS(int node)
{
    color[node] = 'g';
    for (int neighbor : dependencies[node]) {
        if (color[neighbor] == 'g') {
            hasCycle = true;
        } else if (color[neighbor] == 'w') {
            DFS(neighbor);
        }
    }
    color[node] = 'b';
    topOrder.push_back(node);
}

void GraphAlgorithm::DFSCollect(set<int> &sccSet, int node)
{
    color[node] = 'g';
    for (int neighbor : transpose[node]) {
        if (color[neighbor] == 'g') {
            hasCycle = true;
        } else if (color[neighbor] == 'w') {
            DFSCollect(sccSet, neighbor);
        }
    }
    color[node] = 'b';
    sccSet.insert(node);
}

void GraphAlgorithm::findSCCs()
{
    int n = dependencies.size();
    transpose.assign(n, {});
    for (int u = 1; u < n; u++) {
        for (int v : dependencies[u]) {
            transpose[v].insert(u);
        }
    }

    color.assign(n, 'w');
    sccList.push_back({}); // Placeholder for 1-based indexing alignment

    for (int i = n - 2; i >= 0; i--) {
        int node = topOrder[i];
        if (color[node] == 'w') {
            set<int> currentSCC;
            DFSCollect(currentSCC, node);
            sccList.push_back(currentSCC);
        }
    }
}

void GraphAlgorithm::computeTopologicalOrder()
{
    int n = dependencies.size();
    vector<int> indegree(n, 0);
    for (int u = 1; u < n; u++) {
        for (int v : dependencies[u]) {
            indegree[v]++;
        }
    }

    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int i = 1; i < n; i++) {
        if (indegree[i] == 0) {
            minHeap.push(i);
        }
    }

    while (!minHeap.empty()) {
        int u = minHeap.top();
        minHeap.pop();
        validTopOrder.push_back(u);

        for (int v : dependencies[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                minHeap.push(v);
            }
        }
    }
}
