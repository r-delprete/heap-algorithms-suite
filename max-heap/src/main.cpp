#include "./include/max_heap.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ifstream input2("input2.txt");
  ofstream output("output.txt");

  MaxHeap mh(input2);

  mh.print();
  mh.print("Max heap", output);

  int old_value = 10;
  int new_value = 45;
  cout << endl;
  mh.increase_key(old_value, new_value);
  mh.print();
  int max = mh.extract_max();
  cout << "\nMax heap value => ";
  (max != -1 ? cout << max : cout << "NULL");
  cout << endl;
  mh.heap_sort();
  mh.print("\nAfter heap sort");

  input.close();
  input2.close();
  output.close();

  return 0;
}