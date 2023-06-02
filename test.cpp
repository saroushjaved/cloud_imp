#include <iostream>
//#include "SneakySnake.h"
#include "string.h"
#include <string>
#include <fstream>
#include <climits>
#include <sys/types.h>
#include <chrono>
#include<stdlib.h>
#include<cstdlib>
#include <omp.h>

using namespace std;
using namespace std::chrono;
/*
int lines = 30000;
const int N = 100;
const int no_threads = 4;
int Accepted[no_threads];
int rejected[no_threads];
*/


int main() {

	/*
	fstream readfile;
	readfile.open("./dataset/100_bp_4.txt", ios::in);
	if (!readfile) {
		std::cout << "Please select a correct file." << endl;

	}
	else {
		std::cout << "File has opened successfully." <<endl;
		std::cout << "There are a total of " << lines << " reads in the file." << endl;
		std::cout << "Total number of threads being utilized: " << no_threads << endl;

	}

	string read;

	auto startTime = high_resolution_clock::now();
	*/

#pragma omp parallel//removes unnesscary accesses to memory
	{


		int ID = omp_get_thread_num();
		cout << "Thread No: " << ID << endl;
		/*
		int accepted_sum = 0; //local variables defined to avoid calling memeory again and again
		int rejected_sum = 0;
		int size_read = N;
		string line;
		char ReadSeq[N + 1];
		char RefSeq[N + 1];

		//#pragma omp parallel for schedule(static)

		for (int i = 0; i < 3000000; i++) {
			getline(readfile, line);
			strncpy_s(ReadSeq, line.c_str(), size_read);
			strncpy_s(RefSeq, line.c_str() + size_read + 1, size_read);
			int r = SneakySnake(size_read, RefSeq, ReadSeq, 60, 0, 0, 0);
			if (r == 1) {
				accepted_sum++;
			}
			else if (r == 0) {
				rejected_sum++;
			}
		}
		Accepted[ID] = accepted_sum;
		rejected[ID] = rejected_sum;
		*/
	}

	/*
	auto stopTime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stopTime - startTime);


	int sum_accepted = 0;
	int sum_rejected = 0;

	for (int i = 0; i < no_threads; i++) {
		sum_accepted += Accepted[i];
		sum_rejected += rejected[i];
	}


	std::cout << "Total Accepted Reads: " << sum_accepted << endl;
	std::cout << "Total Rejected Reads: " << sum_rejected << endl;
	std::cout <<"Total Execution time for Sneaky Snake Algorithm Sec(ms):  "<<duration.count()/1000<<endl;
	*/
}

