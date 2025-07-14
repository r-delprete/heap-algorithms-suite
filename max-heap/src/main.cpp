#include "./include/max_heap.hpp"

using namespace std;

int main(int argc, char** argv) {
  ifstream input("input.txt");
  ifstream input2("input2.txt");
  ofstream output("output.txt");

  MaxHeap mh(input2);

  mh.print();
  mh.print(output, "Max heap");

  int old_key = 10;
  int new_key = 45;
  cout << endl;
  cout << "Increased key " << old_key << " to " << new_key << endl;
  mh.increase_key(old_key, new_key);
  mh.print();

  auto max = mh.extract_max();
  cout << "\nMax heap value => ";
  (max ? cout << *max : cout << "NULL");
  cout << endl;

  auto sorted = mh.heapsort();
  cout << "\nAfter heap sort" << endl;
  for (auto& item : sorted) cout << *item << "\t";
  cout << endl;

  input.close();
  input2.close();
  output.close();

  return 0;
}