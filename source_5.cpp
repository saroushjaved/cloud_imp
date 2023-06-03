#include <iostream>
#include "SneakySnake.h"
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

int lines = 30000;
const int N = 100;
const int no_threads = 20;

int main() {

	fstream readfile;
	readfile.open("./dataset/100_bp_1.txt", ios::in);
	if (!readfile) {
		std::cout << "Please select a correct file." << endl;
	}
	else {
		std::cout << "File has opened successfully." << endl;
		std::cout << "There are a total of " << lines << " reads in the file." << endl;
		std::cout << "Total number of threads being utilized: " << no_threads << endl;
	}

	string read;

	int total_sum_acc = 0;
	int total_sum_rej = 0;
	auto startTime = high_resolution_clock::now();

	int accepted_sum = 0;
	int rejected_sum = 0;

	omp_set_num_threads(no_threads);

#pragma omp parallel
	{
		int size_read = N;
		string line;
		int local_accepted_sum = 0;
		int local_rejected_sum = 0;

#pragma omp for
		for (int i = 0; i < 30000; i++) {
			char ReadSeq[N + 1];
			char RefSeq[N + 1];
			getline(readfile, line);
			strncpy(ReadSeq, line.c_str(), size_read);
			strncpy(RefSeq, line.c_str() + size_read + 1, size_read);
			int r = SneakySnake(size_read, RefSeq, ReadSeq, 10, 0, 0, 0);

			if (r == 1) {
#pragma omp atomic
				local_accepted_sum += 1;
			}
			else {
#pragma omp atomic
				local_rejected_sum += 1;
			}
		}

#pragma omp atomic
		accepted_sum += local_accepted_sum;

#pragma omp atomic
		rejected_sum += local_rejected_sum;
	}

	auto stopTime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stopTime - startTime);

	std::cout << "Total Accepted Reads: " << accepted_sum << endl;
	std::cout << "Total Rejected Reads: " << rejected_sum << endl;
	std::cout << "Total Execution time for Sneaky Snake Algorithm (ms): " << duration.count() / 1000 << endl;

}

