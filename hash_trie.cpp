#include <iostream>
#include <vector>
#include <taskflow/taskflow.hpp>

using namespace tf;

// Define a struct to store the Hash Trie data
struct HashTrie {
  std::vector<int> data; // some data for example
};

// Define a function to split the Hash Trie data
void splitHashTrie(HashTrie& ht, int num_splits) {
  // Determine the size of each split
  int split_size = ht.data.size() / num_splits;

  // Split the Hash Trie data into multiple parts
  for(int i = 0; i < num_splits; i++) {
    int start = i * split_size;
    int end = (i == num_splits - 1) ? ht.data.size() : (i + 1) * split_size;
    std::vector<int> split_data(ht.data.begin() + start, ht.data.begin() + end);
    // Do some processing on the split_data here
    // ...
  }
}

int main() {
  // Define the Hash Trie data
  HashTrie ht;
  ht.data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Initialize the Taskflow object
  Taskflow tf;

  // Define the task that splits the Hash Trie data into 2 parts
  auto split_task = tf.emplace([&](HashTrie& ht) { splitHashTrie(ht, 2); }, ht);

  // Run the Taskflow in parallel mode
  Executor executor;
  executor.run(tf).wait();

  // Print the split results for testing
  std::cout << "Split result 1: ";
  for(int i = 0; i < ht.data.size() / 2; i++) {
    std::cout << ht.data[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "Split result 2: ";
  for(int i = ht.data.size() / 2; i < ht.data.size(); i++) {
    std::cout << ht.data[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
