#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int max(int a, int b) { return a > b ? a : b; }

int LCS(int &N, int &M, string &s1, string &s2) {
    vector<vector<int>> lookUp = vector<vector<int>>(N + 1, vector<int>(M + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (s1[i - 1] == s2[j - 1])
                lookUp[i][j] = lookUp[i - 1][j - 1] + 1;
            else
                lookUp[i][j] = max(lookUp[i - 1][j], lookUp[i][j - 1]);
        }
    }
    return lookUp[N][M];
}

int matrixLCS(int &N, int &M, string &s1, string &s2) {
    int **m = new int *[N + 1];
    for (int i = 0; i < N + 1; i++) {
        m[i] = new int[M];
    }
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < M + 1; j++) {
            m[i][j] = 0;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (s1[i - 1] == s2[j - 1])
                m[i][j] = m[i - 1][j - 1] + 1;
            else
                m[i][j] = max(m[i - 1][j], m[i][j - 1]);
        }
    }
    return m[N][M];
}

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    int N, M;

    while (input >> N >> M) {
        string a, b, lcs;
        input >> a >> b;
        output << LCS(N, M, a, b) << endl;
        cout << matrixLCS(N, M, a, b) << endl;
    }
}