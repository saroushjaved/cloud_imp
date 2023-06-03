#include <iostream>
#include "SneakySnake.h"
#include "string.h"
#include <string>
#include <fstream>
#include <climits>
#include <sys/types.h>
#include <chrono>
#include <cstdlib>
#include <omp.h>

using namespace std;
using namespace std::chrono;

int lines = 30000;
const int N = 100;
const int no_threads =20;
int Accepted[no_threads];
int rejected[no_threads];


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

    int size_read = N;
    string line;

#pragma omp parallel for shared(readfile) reduction(+:accepted_sum, rejected_sum)
    for (int i = 0; i < 30000; i++) {
        char ReadSeq[N + 1];
        char RefSeq[N + 1];
        int r;


#pragma omp critical
        {
int ID = omp_get_thread_num();
              cout << "Thread No: " << ID << " Iteration Number: " <<i<< endl;
            getline(readfile, line);
        }

        strncpy(ReadSeq, line.c_str(), size_read);
        strncpy(RefSeq, line.c_str() + size_read + 1, size_read);
        r = SneakySnake(size_read, RefSeq, ReadSeq, 5, 0, 0, 0);

        if (r == 1) {
            accepted_sum += 1;
        }
        else {
            rejected_sum += 1;
        }
    }

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    std::cout << "Total Accepted Reads: " << accepted_sum << endl;
    std::cout << "Total Rejected Reads: " << rejected_sum << endl;
    std::cout << "Total Execution time for Sneaky Snake Algorithm (ms): " << duration.count() / 1000 << endl;

    return 0;
}

