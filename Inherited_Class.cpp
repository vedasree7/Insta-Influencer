#include "GraphAlgorithm.cpp"
#include <iostream>

using namespace std;

// Detects if the graph has a cycle
class isCycle : public GraphAlgorithm
{
public:
    isCycle(vector<set<int>> &adjList);
    inline void query() override {cout << (hasCycle ? "YES" : "NO") << endl;}
};

isCycle::isCycle(vector<set<int>> &adjList) : GraphAlgorithm(adjList)
{
    runDFSForAll();
}

// Computes the number and max size of strongly connected components
class indepComponent : public GraphAlgorithm
{
public:
    indepComponent(vector<set<int>> &adjList);
    void query() override { cout << componentCount << " " << maxComponentSize << endl; }

private:
    int componentCount, maxComponentSize;
};

indepComponent::indepComponent(vector<set<int>> &adjList) : GraphAlgorithm(adjList)
{
    runDFSForAll();
    findSCCs();

    componentCount = sccList.size() - 1;
    maxComponentSize = 0;
    for (int i = 1; i <= componentCount; i++) {
        if ((int)sccList[i].size() > maxComponentSize)
            maxComponentSize = sccList[i].size();
    }
}

// Computes and prints a valid topological order if possible
class validOrder : public GraphAlgorithm
{
public:
    validOrder(vector<set<int>> &adjList);
    void query() override;
};

validOrder::validOrder(vector<set<int>> &adjList) : GraphAlgorithm(adjList)
{
    runDFSForAll();
    computeTopologicalOrder();
}

void validOrder::query()
{
    if (hasCycle) {
        cout << "NO" << endl;
        return;
    }
    for (int node : validTopOrder)
        cout << node << " ";
    cout << endl;
}

// Computes the maximum hype score achievable over a valid path
class maxHype : public GraphAlgorithm
{
public:
    maxHype(vector<set<int>> &adjList, vector<int> &hype);
    void query() override {cout << maxHypeValue << endl;}

private:
    void computeMaxHype();
    long long maxHypeValue;
};

maxHype::maxHype(vector<set<int>> &adjList, vector<int> &hype) : GraphAlgorithm(adjList)
{
    hypeScores = hype;
    runDFSForAll();
    findSCCs();
    computeMaxHype();
}

void maxHype::computeMaxHype()
{
    int n = sccList.size();
    sccHypeScores.resize(n, 0);

    // Compute hype scores and build SCC ID mapping
    for (int i = 1; i < n; i++) {
        int totalHype = 0;
        for (int node : sccList[i]) {
            sccIdMap[node] = i;
            totalHype += hypeScores[node];
        }
        sccHypeScores[i] = totalHype;
    }

    sccDependencies.resize(n);

    // Build the condensed SCC graph
    for (int u = 1; u < dependencies.size(); u++) {
        for (int v : dependencies[u]) {
            int sccU = sccIdMap[u];
            int sccV = sccIdMap[v];
            if (sccU != sccV) {
                sccDependencies[sccU].insert(sccV);
            }
        }
    }

    // Create an isCycle object to reuse topological sort logic on SCC DAG
    GraphAlgorithm *sccGraph = new isCycle(sccDependencies);
    sccGraph->computeTopologicalOrder();

    vector<long long> dp(n, 0);
    maxHypeValue = 0;

    // DP on topologically sorted SCC DAG to compute max hype
    for (int u : sccGraph->validTopOrder) {
        dp[u] += sccHypeScores[u];
        maxHypeValue = max(maxHypeValue, dp[u]);
        for (int v : sccDependencies[u]) {
            if (dp[v] < dp[u]) {
                dp[v] = dp[u];
            }
        }
    }
}
