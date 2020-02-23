#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int MCM(vector<int> &chain) {
    int chain_length = chain.size() - 1;
    vector<vector<int>> LUT = vector<vector<int>>(chain_length, vector<int>(chain_length, 0));
    for (int delta = 1; delta < chain_length; delta++) {
        for (int i = 0; i < chain_length - delta; i++) {    //Rows
            int j = delta + i;                              //Columns
            for (int k = i; k < j; k++) {
                int m = LUT[i][k] + LUT[k + 1][j] + chain[i] * chain[k + 1] * chain[j + 1];
                if (LUT[i][j] == 0 || m < LUT[i][j]) {
                    LUT[i][j] = m;
                    LUT[j][i] = k;
                }
            }
        }
    }
    return LUT[0][chain_length - 1];
}

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    int N;
    while (input >> N) {
        char trash;
        int r, c;
        vector<int> chain;
        for (int i = 0; i < N; i++) {
            input >> trash >> r >> trash >> c >> trash;
            if (i == 0) {
                chain.push_back(r);
                chain.push_back(c);
            } else chain.push_back(c);
        }
        output << MCM(chain) << endl;
    }
}