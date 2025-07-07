#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class MaxHeap {
  std::vector<int> data;
  int size;

  void build_heap() {
    for (int i = size / 2; i >= 0; i--) heapify(i, size);
  }

  void heapify(int index, int size) {
    int max = index, left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && data[max] < data[left]) max = left;
    if (right < size && data[max] < data[right]) max = right;

    if (max != index) {
      std::swap(data[max], data[index]);
      heapify(max, size);
    }
  }

  void format_line(std::string& line) {
    if (line.front() == '<') line = line.substr(1);
    if (line.back() == '>') line.pop_back();
    for (auto& c : line) {
      if (c == ',') c = ' ';
    }
  }

  void clear_stream(std::istringstream& stream) {
    stream.clear();
    stream.str("");
  }

  void shift_up(int index) {
    while (index > 0 && data[(index - 1) / 2] < data[index]) {
      std::swap(data[index], data[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

public:
  MaxHeap(std::ifstream& input) { load(input); }

  ~MaxHeap() { data.clear(); }

  void load(std::ifstream& input) {
    data.clear();
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    std::getline(input, line);
    format_line(line);
    std::istringstream iss(line);
    int value;
    while (iss >> value) data.push_back(value);
    clear_stream(iss);
    size = data.size();

    build_heap();
  }

  int extract_max() {
    if (data.empty()) {
      std::cerr << "[extract_max ERROR] Heap is empty" << std::endl;
      return -1;
    }

    int max = data[0];
    std::swap(data[0], data[size - 1]);
    size--;
    data.pop_back();
    heapify(0, size);

    return max;
  }

  int index_of(int key) {
    if (data.empty()) {
      std::cerr << "[index_of ERROR] Heap is empty" << std::endl;
      return -1;
    }

    for (int i = 0; i < data.size(); i++) {
      if (data[i] == key) {
        std::cout << "[index_of INFO] Key " << key << " found at position " << i << std::endl;
        return i;
      }
    }

    std::cerr << "[index_of ERROR] Key " << key << " not found" << std::endl;
    return -1;
  }

  void increase_key(int old_key, int new_key) {
    if (new_key < old_key) {
      std::cerr << "[increase_key ERROR] New key " << new_key << " is less than old key " << old_key << std::endl;
      return;
    }

    int index = index_of(old_key);
    if (index != -1) {
      data[index] = new_key;
      shift_up(index);

      std::cout << "[increase_key INFO] Increased old key " << old_key << " to new key " << new_key << std::endl;
    }
  }

  void heap_sort() {
    build_heap();
    for (int i = size - 1; i >= 0; i--) {
      std::swap(data[0], data[i]);
      size--;
      heapify(0, i);
    }
  }

  void print(std::string message = "Max heap", std::ostream& out = std::cout) {
    out << message << std::endl;
    for (auto& value : data) out << value << "\t";
    out << std::endl;
  }
};

#endif