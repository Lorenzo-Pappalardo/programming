#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int MCM(vector<int> &chain) {
    int chain_length = chain.size() - 1;
    vector<vector<int>> LUT = vector<vector<int>>(chain_length, vector<int>(chain_length, 0));
    for (int j = 1; j < chain_length; j++) {            //Columns
        for (int i = 0; i < chain_length - j; i++) {    //Rows
            int k = i + j;
            for (int l = i; l < k; l++) {
                int m = LUT[i][l] + LUT[l + 1][k] + chain[i] * chain[l + 1] * chain[k + 1];
                if (LUT[i][k] == 0 || m < LUT[i][k]) {
                    LUT[i][k] = m;
                    LUT[k][i] = l;
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