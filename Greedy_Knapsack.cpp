#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void xDsort(int *a, int N) {
	int min;
	for (int i=0; i<N; i++) {
		min=i;
		for (int j=i+1; j<N; j++) {
			if (a[j] < a[min])
				min = j;
		}
		swap(a[i],a[min]);
	}
}

int main() {
	fstream input, output;
	input.open("input.txt", fstream::in);
	output.open("output.txt",fstream::out);
	
	int N, P;
	
	while(input >> N >> P) {
		vector<int> a;
		for (int i=0; i<N; i++) {
			int tmp;
			input >> tmp;
			a.push_back(tmp);
		}
		sort(a.begin(), a.end());
		int sum = 0;
		for(int i=N-1;i>=N-P;i--){
			sum += a[i];
		}
		output << sum << endl;
	}
	input.close();
	output.close();
}
