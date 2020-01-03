#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

const int min(int a, int b) { return a < b ? a : b; }

int editDistance(int &n, int &m, string &x, string &y) {
    vector<vector<int>> LUT = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) LUT[i][0] = LUT[i - 1][0] + 1;
    for (int i = 1; i <= m; i++) LUT[0][i] = LUT[0][i - 1] + 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (x[i - 1] == y[j - 1])
                LUT[i][j] = LUT[i - 1][j - 1];
            else {
                int tmp = min(LUT[i - 1][j] + 1, LUT[i][j - 1] + 1);
                LUT[i][j] = min(tmp, LUT[i - 1][j - 1] + 1);
            }
        }
    }
    return LUT[n][m];
}

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    int N, M;
    string X, Y;

    while (input >> N >> M >> X >> Y) {
        output << editDistance(N, M, X, Y) << endl;
    }
}