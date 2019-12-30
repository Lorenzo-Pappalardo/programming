#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int MCM(int &N, int &r, int &c) {
    vector<vector<int>> LUT = vector<vector<int>>(N, vector<int>(N, 0));
    for (int i = 1; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            int k = i + j;
            for (int l = j; l < k; l++) {
                int m = LUT[j][l] + LUT[l + 1][k];//Robe...
            }
        }
    }
}

int main() {
    fstream input, output;
    input.open("input.txt", fstream::in);
    output.open("output.txt", fstream::out);

    int N;
    while (input >> N) {
        char trash;
        int r, c;
        for (int i = 0; i < N; i++) {
            input >> trash >> r >> trash >> c >> trash;
            //cout << r << 'x' << c << " | ";   //Checking...
        }
    }
}