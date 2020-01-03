#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int MCM(vector<int> &chain) {
    int chain_length = chain.size() - 1;
    vector<vector<int>> LUT = vector<vector<int>>(chain_length, vector<int>(chain_length, 0));
    for (int i = 1; i < chain_length; i++) {
        for (int j = 0; j < chain_length - i; j++) {
            int k = i + j;
            for (int l = j; l < k; l++) {
                int m = LUT[j][l] + LUT[l + 1][k] + chain[j] * chain[l + 1] * chain[k + 1];
                if (LUT[j][k] == 0 || m < LUT[j][k]) {
                    LUT[j][k] = m;
                    LUT[k][j] = l;
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
            //cout << r << 'x' << c << " | ";   //Checking...
            if (i == 0) {
                chain.push_back(r);
                chain.push_back(c);
            } else chain.push_back(c);
        }
        /*for (int i = 0; i < chain.size(); i++) {
            cout << chain[i] << ' ';
        }
        cout << endl; Checking...*/
        output << MCM(chain) << endl;
    }
}