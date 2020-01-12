#include <fstream>
#include <iostream>

using namespace std;

const int INF = INT32_MAX;

template <class T>
class Graph {
    int dim, nodesNum, edgesNum, root;
    T **nodes;
    int **edges;
    int **weights;

    int getIndex(T key) {
        for (int i = 0; i < nodesNum; i++) {
            if (*nodes[i] == key) return i;
        }
        return -1;
    }

   public:
    Graph(int dim) {
        this->dim = dim;
        nodesNum = edgesNum = 0;
        root = -1;
        nodes = new T *[dim];
        edges = new int *[dim];
        weights = new int *[dim];
        for (int i = 0; i < dim; i++) {
            nodes[i] = nullptr;
            edges[i] = new int[dim];
            weights[i] = new int[dim];
            for (int j = 0; j < dim; j++) {
                edges[i][j] = 0;
                weights[i][j] = INF;
            }
        }
    }

    void addRoot(T const &newNode) {
        root = nodesNum;
        addNode(newNode);
    }

    void addNode(T const &newNode) {
        if (nodesNum < dim) {
            nodes[nodesNum++] = new T(newNode);
        }
    }

    void addEdge(T n1, T n2, int weight) {
        int i = getIndex(n1);
        int j = getIndex(n2);
        if (i != -1 && j != -1) {
            edges[i][j] = 1;
            weights[i][j] = weight;
            edgesNum++;
        }
    }

    int Bellman_Ford(T from, T to) {
        int distance[nodesNum];
        int predecessor[nodesNum];
        int index = getIndex(from);
        for (int i = 0; i < nodesNum; i++) {
            distance[i] = INF;
            predecessor[i] = -1;
        }
        distance[index] = 0;
        predecessor[index] = index;
        for (int c = 0; c < nodesNum - 1; c++) {  //Relaxing all nodes...
            for (int i = 0; i < nodesNum; i++) {
                for (int j = 0; j < nodesNum; j++) {
                    if (distance[i] != INF && edges[i][j] == 1) {
                        int weight = weights[i][j];
                        if (distance[i] + weight < distance[j]) {
                            distance[j] = distance[i] + weight;
                            predecessor[j] = i;
                        }
                    }
                }
            }
        }
        //Checking for negative cycles...
        for (int i = 0; i < nodesNum; i++) {
            for (int j = 0; j < nodesNum; j++) {
                if (distance[i] != INF && edges[i][j] == 1) {
                    int weight = weights[i][j];
                    if (distance[i] + weight < distance[j]) {
                        return -INF;
                    }
                }
            }
        }
        return (distance[getIndex(to)] != INF ? distance[getIndex(to)] : -INF + 1);
    }

    void print(ostream &os, int res) {
        if (res == -INF) os << "undef.";
        else if (res == -INF+1) os << "inf.";
        else os << res;
        os << endl;
    }
};

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    int N, M;
    string type;

    while (input >> N >> M >> type) {
        if (type == "int" || type == "double") {
            Graph<double> *g = new Graph<double>(N);
            for (int i = 0; i < N; i++) {
                double value;
                input >> value;
                g->addNode(value);
            }
            for (int i = 0; i < M; i++) {
                char trash;
                double from, to;
                int weight;
                input >> trash >> from >> to >> weight >> trash;
                g->addEdge(from, to, weight);
            }
            double source, destination;
            input >> source >> destination;
            g->print(output, g->Bellman_Ford(source, destination));
        }
    }
    input.close();
    output.close();
}