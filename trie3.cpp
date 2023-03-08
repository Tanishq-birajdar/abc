#include <iostream>
#include <vector>
#include <string>
#include <taskflow/taskflow.hpp>

// Define a node in the trie data structure
struct TrieNode {
    bool isEndOfWord;
    std::vector<TrieNode*> children;
    TrieNode(): isEndOfWord(false), children(26, nullptr) {}
};

// Insert a word into the trie data structure
void insertWord(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for(char c : word) {
        int index = c - 'a';
        if(curr->children[index] == nullptr) {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

// Check if a word exists in the trie data structure
bool searchWord(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for(char c : word) {
        int index = c - 'a';
        if(curr->children[index] == nullptr) {
            return false;
        }
        curr = curr->children[index];
    }
    return curr->isEndOfWord;
}

// Remove a word from the trie data structure
bool removeWord(TrieNode* root, const std::string& word) {
    TrieNode* curr = root;
    for(char c : word) {
        int index = c - 'a';
        if(curr->children[index] == nullptr) {
            return false;
        }
        curr = curr->children[index];
    }
    if(curr->isEndOfWord == false) {
        return false;
    }
    curr->isEndOfWord = false;
    return true;
}

// Print all words in the trie data structure
void printWords(TrieNode* root, std::string prefix = "") {
    if(root->isEndOfWord) {
        std::cout << prefix << std::endl;
    }
    for(int i=0; i<26; i++) {
        if(root->children[i] != nullptr) {
            char c = 'a' + i;
            std::string newPrefix = prefix + c;
            printWords(root->children[i], newPrefix);
        }
    }
}

int main() {
    // Initialize the root node of the trie data structure
    TrieNode* root = new TrieNode();

    // Insert some words into the trie data structure
    insertWord(root, "hello");
    insertWord(root, "world");
    insertWord(root, "task");
    insertWord(root, "flow");

    // Create a taskflow object
    tf::Taskflow taskflow;
    taskflow parallel_for

    // Create a parallel for loop to remove some words from the trie data structure
    std::vector<std::string> wordsToRemove = {"world", "flow"};
    tf::Task removeTask = taskflow.parallel_for(wordsToRemove.begin(), wordsToRemove.end(), [&](const std::string& word) {
        removeWord(root, word);
    });

}
