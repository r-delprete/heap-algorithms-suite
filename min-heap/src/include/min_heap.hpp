#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using shared_heap_item = std::shared_ptr<int>;
shared_heap_item factory_shared_item(int value) { return std::make_shared<int>(value); }

enum LogType { ERROR, INFO, WARNING };
void log(std::string function_name, std::string message, LogType type = LogType::INFO) {
  std::string log_type = type == LogType::ERROR ? "ERROR" : type == LogType::INFO ? "INFO" : "WARNING";
  std::ostream& out = type == LogType::ERROR ? std::cerr : std::cout;
  out << "[" << function_name << " " << log_type << "] " << message << std::endl;
}

class MinHeap {
  std::vector<shared_heap_item> data;

  void format_line(std::string& line) {
    if (line.empty()) return;
    if (line.front() == '<') line = line.substr(1);
    if (line.back() == '>') line.pop_back();
    for (auto& c : line) {
      if (c == ',') c = 32;
    }
  }

  void build_heap(std::vector<shared_heap_item>& data) {
    for (int i = data.size() / 2 - 1; i >= 0; i--) heapify(data, i, data.size());
  }

  void heapify(std::vector<shared_heap_item>& heap, int index, int size) {
    int min = index, left = 2 * index + 1, right = 2 * index + 2;
    if (left < size && *heap[min] > *heap[left]) min = left;
    if (right < size && *heap[min] > *heap[right]) min = right;
    if (min != index) {
      std::swap(heap[index], heap[min]);
      heapify(heap, min, size);
    }
  }

  void shift_up(int index) {
    while (index > 0 && *data[(index - 1) / 2] > *data[index]) {
      std::swap(data[(index - 1) / 2], data[index]);
      index = (index - 1) / 2;
    }
  }

public:
  MinHeap(std::ifstream& input) { load(input); }

  void reset() { data.clear(); }

  bool empty() { return data.empty(); }

  void load(std::ifstream& input) {
    reset();
    input.clear();
    input.seekg(0, std::ios::beg);

    std::string line;
    std::getline(input, line);
    format_line(line);
    std::istringstream iss(line);
    int value;
    while (iss >> value) insert(factory_shared_item(value));
    iss.clear();
    iss.str("");
    line.clear();
  }

  void insert(shared_heap_item item) {
    data.push_back(item);
    shift_up(data.size() - 1);
  }

  int index_of(int value) const {
    for (int i = 0; i < data.size(); i++) {
      if (*data[i] == value) return i;
    }

    return -1;
  }

  shared_heap_item extract_min() {
    if (empty()) {
      log("extract_min", "Heap is empty", LogType::ERROR);
      return nullptr;
    }

    auto min = data[0];
    std::swap(data[0], data[data.size() - 1]);
    data.pop_back();
    heapify(data, 0, data.size());

    return min;
  }

  std::vector<shared_heap_item> heapsort() {
    int size = data.size();
    auto tmp = data;
    build_heap(tmp);

    for (int i = size - 1; i >= 0; i--) {
      std::swap(tmp[0], tmp[i]);
      heapify(tmp, 0, i);
    }

    return tmp;
  }

  void decrease_key(int old_key, int new_key) {
    std::ostringstream ss;
    if (new_key > old_key) {
      ss << "New key " << new_key << " is greater than old key " << old_key;
      log("decrease_key", ss.str(), LogType::ERROR);
      ss.clear();
      ss.str("");
      return;
    }

    int index = index_of(old_key);
    if (index != -1) {
      *data[index] = new_key;
      shift_up(index);
      ss << "Decreased key " << old_key << " to new key " << new_key;
      log("decrease_key", ss.str());
      ss.clear();
      ss.str("");
    } else {
      ss << "Key index " << old_key << " not found";
      log("decrease_key", ss.str(), LogType::ERROR);
      ss.clear();
      ss.str("");
    }
  }

  void print(std::string message = "Heap", std::ostream& out = std::cout) const {
    out << message << std::endl;
    for (auto& item : data) out << *item << "\t";
    out << std::endl;
  }
};

#endif