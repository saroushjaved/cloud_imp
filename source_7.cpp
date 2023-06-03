#include <iostream>
#include "SneakySnake.h"
#include "string.h"
#include <string>
#include <fstream>
#include <climits>
#include <sys/types.h>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <omp.h>

using namespace std;
using namespace std::chrono;

const int N = 100;
const int no_threads = 20;

int main() {
    fstream readfile;
    readfile.open("./dataset/100_bp_1.txt", ios::in);
    if (!readfile) {
        std::cout << "Please select a correct file." << endl;
    } else {
        std::cout << "File has opened successfully." << endl;
    }

    string read;
    vector<string> lines;
    while (getline(readfile, read)) {
        lines.push_back(read);
    }

    int total_sum_acc = 0;
    int total_sum_rej = 0;
    auto startTime = high_resolution_clock::now();

    int accepted_sum = 0;
    int rejected_sum = 0;

    omp_set_num_threads(no_threads);

#pragma omp parallel reduction(+:accepted_sum, rejected_sum)
    {
        int size_read = N;
        int local_accepted_sum = 0;
        int local_rejected_sum = 0;

        int thread_id = omp_get_thread_num();
        int lines_per_thread = lines.size() / no_threads;
        int start_line = thread_id * lines_per_thread;
        int end_line = start_line + lines_per_thread;

        if (thread_id == no_threads - 1) {
            end_line = lines.size(); // Last thread handles remaining lines
        }

        for (int i = start_line; i < end_line; i++) {
            const string& line = lines[i];
            char ReadSeq[N + 1];
            char RefSeq[N + 1];
            strncpy(ReadSeq, line.c_str(), size_read);
            strncpy(RefSeq, line.c_str() + size_read + 1, size_read);
            int r = SneakySnake(size_read, RefSeq, ReadSeq, 10, 0, 0, 0);

            if (r == 1) {
                local_accepted_sum += 1;
            } else {
                local_rejected_sum += 1;
            }
        }

        accepted_sum += local_accepted_sum;
        rejected_sum += local_rejected_sum;
    }

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    std::cout << "Total Accepted Reads: " << accepted_sum << endl;
    std::cout << "Total Rejected Reads: " << rejected_sum << endl;
    std::cout << "Total Execution time for Sneaky Snake Algorithm (ms): " << duration.count() / 1000 << endl;
}

