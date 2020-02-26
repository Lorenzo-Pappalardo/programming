#include <iostream>
#include <fstream>
using namespace std;

class Activity {
	int start, finish;
public:
	Activity(int start, int finish) {
		this->start = start;
		this->finish = finish;
	}
	
	int getStart() { return start; }
	int getFinish() { return finish; }
};

void print(ostream &os, Activity **a, int N) {
	for (int i=0; i<N; i++) {
		os << a[i]->getFinish() << ' ';
	}
	os << endl;
}

void bubbleSort(Activity **a, int N) {
	for (int i=0; i<N; i++) {
		for (int j=i+1; j<N; j++) {
			if (a[i]->getFinish() > a[j]->getFinish()) {
				Activity *tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int select(Activity **a, int N) {
	bubbleSort(a, N);
	int count = 1;
	int k = 0;
	for (int i=1; i<N; i++) {
		if (a[i]->getStart() >= a[k]->getFinish()) {
			k = i;
			count++;
		}
	}
	return count;
}

int main() {
	fstream input, output;
	input.open("input.txt", fstream::in);
	output.open("output.txt", fstream::out);
	
	int N;
	
	while(input >> N) {
		Activity **a = new Activity*[N];
		for (int i=0; i<N; i++) {
			char trash;
			int s, f;
			input >> trash >> s >> f >> trash;
			a[i] = new Activity(s, f);
		}
		output << select(a, N) << endl;
	}
	
	input.close();
	output.close();
}
