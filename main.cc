#include <iostream>
#include <random>
#include <vector>

#include "sorted_list.hh"

#define DATA_SIZE 100

int main() {
    ReverseSortedList list;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, DATA_SIZE);

    std::vector<std::uint32_t> timestamps;
    for (int i = 0; i < DATA_SIZE; i++) {
        timestamps.push_back(i);
    }
    std::vector<std::uint32_t> sorted_timestamps(timestamps);
    std::reverse(sorted_timestamps.begin(), sorted_timestamps.end());

    std::shuffle(timestamps.begin(), timestamps.end(), gen);
    for (auto ts : timestamps) {
        list.insert(new Node(ts));
    }

    std::vector<std::uint32_t> result;
    auto cur = list.get_head();
    while (cur != nullptr) {
        result.push_back(cur->ts);
        cur = cur->next;
    }

    // compare result with sorted_timestamps
    for (int i = 0; i < DATA_SIZE; i++) {
        if (result[i] != sorted_timestamps[i]) {
            std::cout << "ERROR: result[" << i << "] = " << result[i]
                      << ", sorted_timestamps[" << i
                      << "] = " << sorted_timestamps[i] << std::endl;
            return 1;
        }
    }
    std::cout << "PASS: insertion test" << std::endl;

    std::shuffle(timestamps.begin(), timestamps.end(), gen);
    for (int i = 0; i < DATA_SIZE / 2; i++) {
        list.remove(timestamps[i]);
        sorted_timestamps.erase(
            std::remove(sorted_timestamps.begin(), sorted_timestamps.end(),
                        timestamps[i]),
            sorted_timestamps.end());
    }

    result.clear();
    cur = list.get_head();
    while (cur != nullptr) {
        result.push_back(cur->ts);
        cur = cur->next;
    }

    // compare result with sorted_timestamps
    for (int i = 0; i < DATA_SIZE / 2; i++) {
        if (result[i] != sorted_timestamps[i]) {
            std::cout << "Error: result[" << i << "] = " << result[i]
                      << ", sorted_timestamps[" << i
                      << "] = " << sorted_timestamps[i] << std::endl;
            return 1;
        }
    }
    std::cout << "PASS: removal test" << std::endl;

    return 0;
}