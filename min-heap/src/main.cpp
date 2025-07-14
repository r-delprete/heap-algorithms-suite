#include "./include/min_heap.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ifstream input2("input2.txt");
  ofstream output("output.txt");

  MinHeap heap(input);
  MinHeap heap2(input2);

  heap.print(cout, "Heap with easiest input");
  heap.print(output, "Heap with easiest input");
  heap2.print(cout, "\nHeap with hardest input");
  heap2.print(output, "\nHeap with hardest input");

  auto min = heap.extract_min();

  cout << endl << "Minimum value (easiest input) => ";
  min ? cout << *min : cout << "NULL";
  cout << endl;

  int old_key = 20, new_key = 1;
  heap2.decrease_key(old_key, new_key);
  cout << "Decreased key " << old_key << " to " << new_key << endl;
  heap2.print(cout, "After decrease key");

  auto sorted = heap.heapsort();
  cout << "\nSorted heap" << endl;
  for (auto& item : sorted) cout << *item << "\t";
  cout << endl;

  input.close();
  input2.close();
  output.close();

  return 0;
}