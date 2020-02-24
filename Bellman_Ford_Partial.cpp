#include <iostream>
#include <fstream>

using namespace std;

const int INF = INT_MAX;

template<class T>
class Graph {
    int dim, nodesNum, edgesNum;
    T *nodes;
    bool **edges;
    int **weights;

    int getIndex(T key) {
        for (int i = 0; i < nodesNum; i++)
            if (nodes[i] == key) return i;
        return -1;
    }

public:
    Graph(int dim = 420) {
        this->dim = dim;
        nodesNum = edgesNum = 0;
        nodes = new T[dim];
        edges = new bool *[dim];
        weights = new int *[dim];
        for (int i = 0; i < dim; i++) {
            edges[i] = new bool[dim];
            weights[i] = new int[dim];
            for (int j = 0; j < dim; j++) {
                edges[i][j] = false;
                weights[i][j] = INF;
            }
        }
    }

    void insert(T key) {
        if (nodesNum < dim)
            nodes[nodesNum++] = key;
    }

    void addEdge(T key1, T key2, int weight) {
        int i = getIndex(key1);
        int j = getIndex(key2);
        if (i != -1 && j != -1) {
            edges[i][j] = true;
            weights[i][j] = weight;
            edgesNum++;
        }
    }

    int Bellman_Ford(T from, T to, int k) {
        int f = getIndex(from);
        int t = getIndex(to);
        int distances[nodesNum];
        for (int i = 0; i < nodesNum; i++)
            distances[i] = INF;
        distances[f] = 0;
        for (int delta = 0; delta < k; delta++) {            //Relaxing all nodes but stopping after k iterations
            for (int i = 0; i < nodesNum; i++) {
                for (int j = 0; j < edgesNum; j++) {
                    if (distances[i] != INF && edges[i][j]) {
                        if (distances[i] + weights[i][j] < distances[j])
                            distances[j] = distances[i] + weights[i][j];
                    }
                }
            }
        }
        return distances[to];
    }
};

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    int N, M, K;

    while (input >> N >> M >> K) {
        Graph<int> g;
        for (int i = 0; i < N; i++)
            g.insert(i);
        for (int i = 0; i < M; i++) {
            char trash;
            int from, to, weight;
            input >> trash >> from >> to >> weight >> trash;
            g.addEdge(from, to, weight);
        }
        int from;
        int to;
        input >> from >> to;
        int res = g.Bellman_Ford(from, to, K);
        if (res != INF) output << res << endl;
        else output << "inf." << endl;
    }
    input.close();
    output.close();
}