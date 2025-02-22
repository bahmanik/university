#include <climits>
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>

const int NUM_PRISONERS = 100;
const int NUM_ATTEMPTS = 50;
const int TOTAL_TRIALS = 10000000;  //INT_MAX;
const int NUM_THREADS = std::thread::hardware_concurrency();

// Simulates one trial of the 100 prisoners problem.
bool runTrial(std::mt19937 &rng) {
    int boxes[NUM_PRISONERS];

    for (int i = 0; i < NUM_PRISONERS; i++) {
        boxes[i] = i;
    }

    // Shuffle the boxes
    for (int i = NUM_PRISONERS - 1; i > 0; i--) {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(rng);
        int temp = boxes[i];
        boxes[i] = boxes[j];
        boxes[j] = temp;
    }

    for (int prisoner = 0; prisoner < NUM_PRISONERS; prisoner++) {
        int box_to_open = prisoner;
        bool found = false;
        for (int attempt = 0; attempt < NUM_ATTEMPTS; attempt++) {
            if (boxes[box_to_open] == prisoner) {
                found = true;
                break;
            }
            box_to_open = boxes[box_to_open];
        }
        if (!found) return false; // A prisoner failed, so the trial fails.
    }
    return true; // All prisoners succeeded.
}

void worker(int trials, int &local_success, unsigned int seed) {
    int count = 0;
    std::mt19937 rng(seed); // Each thread has its own RNG.
    for (int i = 0; i < trials; i++) {
        if (runTrial(rng)) {
            count++;
        }
    }
    local_success = count;
}

int main() {
    // Divide trials among threads.
    int trials_per_thread = TOTAL_TRIALS / NUM_THREADS;
    std::vector<int> successes(NUM_THREADS, 0);
    std::vector<std::thread> threads;

    // Start timing.
    auto start = std::chrono::high_resolution_clock::now();

    // Launch threads.
    for (int i = 0; i < NUM_THREADS; i++) {
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count() + i;
        threads.push_back(std::thread(worker, trials_per_thread, std::ref(successes[i]), seed));
    }

    // Wait for all threads to finish.
    for (auto &th : threads) {
        th.join();
    }

    // End timing.
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Sum successes from all threads.
    int total_successes = 0;
    for (int s : successes) {
        total_successes += s;
    }

    double success_rate = static_cast<double>(total_successes) / TOTAL_TRIALS * 100.0;
    std::cout << "Number Of Trails: " << TOTAL_TRIALS << "\n";
    std::cout << "Total Successes:  " << total_successes << "\n";
    std::cout << "Success Rate:     " << success_rate << "%\n";
    std::cout << "Execution Time:   " << elapsed.count() << " seconds\n";

    return 0;
}

