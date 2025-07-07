#include "Inherited_Class.cpp"
using namespace std;
int main()
{
    int N, M; // N = number of events and M = number of dependencies
    cin >> N >> M;
    vector<int> hypescores(N + 1); // vector for hypescores for all events respectively
    for (int i = 1; i <= N; i++)
        cin >> hypescores[i];

    vector<set<int>> dependencies; // map for dependencies
    dependencies.resize(N + 1, {});
    
    for (int i = 0; i < M; i++)
    { // Storing dependencies in map
        int u, v;
        cin >> u >> v;
        dependencies[u].insert(v);
    }
    
    // Q = number of queries , type = query type
    int Q, type;
    cin >> Q;
    
    GraphAlgorithm *q1 = new isCycle(dependencies);
    GraphAlgorithm *q2 = new indepComponent(dependencies);
    GraphAlgorithm *q3 = new validOrder(dependencies);
    GraphAlgorithm *q4 = new maxHype(dependencies, hypescores);
    
    while (Q--)
    { // will pass dependencies later
        cin >> type;
        if (type == 1)
        {
            q1->query();
        }
        else if (type == 2)
        {
            q2->query();
        }
        else if (type == 3)
        {
            q3->query();
        }
        else if (type == 4)
        {
            q4->query();
        }
    }
}