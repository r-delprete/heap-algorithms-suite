#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using shared_item = std::shared_ptr<int>;
shared_item create_item(int value) { return std::make_shared<int>(value); }

void format_line(std::string& line) {
  if (line.empty()) return;
  if (line.front() == '<') line = line.substr(1);
  if (line.back() == '>') line.pop_back();
  for (auto& ch : line) {
    if (ch == ',') ch = ' ';
  }
}

void clear_stream(std::istringstream& stream) {
  stream.clear();
  stream.str("");
}

class MinHeap {
  std::vector<shared_item> data;

  void build_heap(std::vector<shared_item>& heap) {
    for (int i = (heap.size() - 1) / 2; i >= 0; i--) heapify(heap, i, heap.size());
  }

  void heapify(std::vector<shared_item>& heap, const int index, const int size) {
    int min = index, left = 2 * index + 1, right = 2 * index + 2;

    if (left < size && *heap[left] < *heap[min]) min = left;
    if (right < size && *heap[right] < *heap[min]) min = right;
    if (min != index) {
      std::swap(heap[min], heap[index]);
      heapify(heap, index, size);
    }
  }

  void shift_up(int index) {
    while (index > 0 && *data[(index - 1) / 2] > *data[index]) {
      std::swap(data[index], data[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

public:
  MinHeap(std::ifstream& input) { load(input); }

  std::size_t size() const { return data.size(); }
  void reset() { data.clear(); }
  void resize(const int size) { data.resize(size); }
  bool empty() const { return data.empty(); }

  void load(std::ifstream& input) {
    reset();
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    std::getline(input, line);
    format_line(line);
    std::istringstream iss(line);
    int value;
    while (iss >> value) insert(create_item(value));
  }

  void insert(const shared_item& item) {
    data.push_back(item);
    shift_up(size() - 1);
  }

  std::vector<shared_item> heapsort() {
    auto tmp = data;
    build_heap(tmp);

    for (int i = tmp.size() - 1; i >= 0; i--) {
      std::swap(tmp[0], tmp[i]);
      heapify(tmp, 0, i);
    }

    return tmp;
  }

  shared_item extract_min() {
    if (empty()) {
      std::cerr << "[extract_min ERROR] Heap is empty" << std::endl;
      return nullptr;
    }

    auto min = data[0];
    std::swap(data[0], data[size() - 1]);
    data.pop_back();
    heapify(data, 0, size());

    return min;
  }

  int index_of(const int key) const {
    if (empty()) {
      std::cerr << "[index_of ERROR] Heap is empty" << std::endl;
      return -1;
    }

    for (int i = 0; i < size(); i++) {
      if (*data[i] == key) return i;
    }

    return -1;
  }

  void decrease_key(const int old_key, const int new_key) {
    if (new_key > old_key) {
      std::cerr << "[decrease_key ERROR] New key " << new_key << " is greater than old key " << old_key << std::endl;
      return;
    }

    const int index = index_of(old_key);
    if (index == -1) {
      std::cerr << "[decrease_key ERROR] Index of " << old_key << " not found" << std::endl;
      return;
    }

    *data[index] = new_key;
    shift_up(index);
  }

  void print(std::ostream& out = std::cout, const std::string message = "Heap") const {
    if (empty()) {
      out << "Heap is empty" << std::endl;
      return;
    }

    out << message << std::endl;
    for (auto& item : data) out << *item << "\t";
    out << std::endl;
  }
};

#endif