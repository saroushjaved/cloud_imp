#include <iostream>
#include "SneakySnake.h"
#include <fstream>
#include <string>
#include <chrono>
#include <cstring>
#include <omp.h>

const int N = 100;
const int no_threads = 8;

int main() {
    int lines = 30000;

    std::ifstream readfile("./dataset/100_bp_1.txt");
    if (!readfile) {
        std::cout << "Please select a correct file." << std::endl;
        return 1;
    }

    std::cout << "File has opened successfully." << std::endl;
    std::cout << "There are a total of " << lines << " reads in the file." << std::endl;
    std::cout << "Total number of threads being utilized: " << no_threads << std::endl;

    int accepted_sum[no_threads] = {0};
    int rejected_sum[no_threads] = {0};

    auto startTime = std::chrono::high_resolution_clock::now();

    #pragma omp parallel num_threads(no_threads)
    {
        int thread_id = omp_get_thread_num();

        // Each thread processes a portion of the lines
        for (int i = 0; i < lines; i++) {
            std::ifstream thread_readfile("./dataset/100_bp_1.txt");
            std::string line;

            // Skip lines until reaching the start index for the current thread
            for (int j = 0; j < i; j++)
                std::getline(thread_readfile, line);

            std::getline(thread_readfile, line);
            char ReadSeq[N + 1];
            char RefSeq[N + 1];
            std::strncpy(ReadSeq, line.c_str(), N);
            ReadSeq[N] = '\0';
            std::strncpy(RefSeq, line.c_str() + N + 1, N);
            RefSeq[N] = '\0';
            int r = SneakySnake(N, RefSeq, ReadSeq, 10, 0, 0, 0);
            if (r == 1) {
                #pragma omp atomic
                accepted_sum[thread_id]++;
            } else {
                #pragma omp atomic
                rejected_sum[thread_id]++;
            }

            thread_readfile.close();
        }
    }

    int total_sum_acc = 0;
    int total_sum_rej = 0;
    for (int i = 0; i < no_threads; i++) {
        total_sum_acc += accepted_sum[i];
        total_sum_rej += rejected_sum[i];
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);

    std::cout << "Total Accepted Reads: " << total_sum_acc << std::endl;
    std::cout << "Total Rejected Reads: " << total_sum_rej << std::endl;
    std::cout << "Total Execution time for Sneaky Snake Algorithm (ms): " << duration.count() << std::endl;

    return 0;
}

