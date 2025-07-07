#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class MinHeap {
  std::vector<int> data;
  int size;

  void clear_stream(std::istringstream& stream) {
    stream.clear();
    stream.str("");
  }

  void format_line(std::string& line) {
    if (line.front() == '<') line = line.substr(1);
    if (line.back() == '>') line.pop_back();
    for (auto& c : line) {
      if (c == ',') c = ' ';
    }
  }

  void build_heap() {
    for (int i = size / 2; i >= 0; i--) heapify(i, size);
  }

  void heapify(int index, int size) {
    int min = index, left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && data[min] > data[left]) min = left;
    if (right < size && data[min] > data[right]) min = right;

    if (min != index) {
      std::swap(data[min], data[index]);
      heapify(min, size);
    }
  }

  void shift_up(int index) {
    while (index > 0 && data[(index - 1) / 2] > data[index]) {
      std::swap(data[(index - 1) / 2], data[index]);
      index = (index - 1) / 2;
    }
  }

public:
  MinHeap(std::ifstream& input) { load(input); }

  ~MinHeap() { data.clear(); }

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
    size = data.size();
    clear_stream(iss);

    build_heap();
  }

  int extract_min() {
    if (data.empty()) {
      std::cerr << "[extract_min ERROR] Heap is empty" << std::endl;
      return -1;
    }

    int min = data[0];
    std::swap(data[0], data[size - 1]);
    size--;
    data.pop_back();
    heapify(0, size);

    return min;
  }

  void heap_sort() {
    build_heap();

    for (int i = size - 1; i >= 0; i--) {
      std::swap(data[0], data[i]);
      size--;
      heapify(0, i);
    }
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

  void decrease_key(int old_key, int new_key) {
    if (new_key > old_key) {
      std::cerr << "[increase_key ERROR] New key " << new_key << " is greater than old key " << old_key << std::endl;
      return;
    }

    int index = index_of(old_key);
    if (!index != -1) {
      data[index] = new_key;
      shift_up(index);

      std::cout << "[increase_key INFO] Increased old key " << old_key << " to new key " << new_key << std::endl;
    }
  }

  void print(std::string message = "Min heap", std::ostream& out = std::cout) {
    out << message << std::endl;
    for (auto& value : data) out << value << "\t";
    out << std::endl;
  }
};

#endif