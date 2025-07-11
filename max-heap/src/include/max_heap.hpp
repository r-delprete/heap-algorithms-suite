#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using shared_heap_item = std::shared_ptr<int>;

class MaxHeap {
  std::vector<shared_heap_item> data;
  int size;

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

  void build_heap() {
    for (int i = size / 2; i >= 0; i--) heapify(i, size);
  }

  void heapify(int index, int size) {
    int largest = index, left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && *(data[left]) > *(data[largest])) largest = left;
    if (right < size && *(data[right]) > *(data[largest])) largest = right;
    if (largest != index) {
      std::swap(data[largest], data[index]);
      heapify(largest, size);
    }
  }

  void shift_up(int index) {
    while (index > 0 && *(data[(index - 1) / 2]) < *(data[index])) {
      std::swap(data[(index - 1) / 2], data[index]);
      index = (index - 1) / 2;
    }
  }

public:
  MaxHeap(std::ifstream& input) { load(input); }

  void reset() {
    data.clear();
    size = 0;
  }

  void load(std::ifstream& input) {
    reset();
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    std::getline(input, line);
    format_line(line);
    std::istringstream iss(line);
    int value;
    while (iss >> value) data.push_back(std::make_shared<int>(value));
    size = data.size();
    line.clear();
    clear_stream(iss);

    build_heap();
  }

  shared_heap_item extract_max() {
    if (data.empty()) {
      std::cerr << "Heap is empty" << std::endl;
      return nullptr;
    }

    auto max = data[0];
    std::swap(data[0], data[size - 1]);
    size--;
    data.pop_back();
    heapify(0, size);

    return max;
  }

  void heap_sort() {
    build_heap();
    int original_size = size;

    for (int i = size - 1; i >= 0; i--) {
      std::swap(data[0], data[i]);
      size--;
      heapify(0, i);
    }

    size = original_size;
  }

  void print(std::ostream& out = std::cout, std::string message = "Heap") {
    out << message << std::endl;
    for (int i = 0; i < size; i++) out << *data[i] << "\t";
    out << std::endl;
  }

  int index_of(int key) {
    for (int i = 0; i < data.size(); i++) {
      if (key == *(data[i])) return i;
    }

    return -1;
  }

  void increase_key(int old_key, int new_key) {
    if (new_key < old_key) {
      std::cerr << "[increase_key ERROR] New key " << new_key << " is less than old key " << old_key << std::endl;
      return;
    }

    int index = index_of(old_key);
    if (index != -1) {
      *data[index] = new_key;
      shift_up(index);

      std::cout << "[increase_key INFO] Increased key " << old_key << " to " << new_key << std::endl;
    }
  }
};

#endif