#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "trie.h"

// implement classes' member functions here...

// destructor
Trie :: ~Trie()
{
    command_clear();
    delete root;
}


// load: read from curpos txt to create a trie, asked chatgpt for info of reading txt
void Trie :: command_load(const string & filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cout << "error opening file" << endl;
        return;
    }
    string word;
    while (file >> word)
    {
        TrieNode * current = root;
        for(char character : word)      // "character : word" - "character" is used to represent each character in the word string as the loop iterates
        {
            int index = character - 'A';
            if(current -> alphabet[index] == nullptr)     // if the alphabet node is not exist, we create one
            {
                current -> alphabet[index] = new TrieNode();
            }
            current = current -> alphabet[index];       // move on
        }
        if(current -> end_of_word)  // duplicate word
        {
            // cout << "failure add" << endl;
        }
        else
        {
            current -> end_of_word = true;      // after the loop reached the end of word
            // cout << "success add" << endl;
            word_count++;
        }
    }
    file.close();
    cout << "success" << endl;
}


// i: insert word to trie if there is not exist one
void Trie :: command_i(const string & word)
{
    TrieNode * current = root;
    for(char character : word)      // "character : word" - "character" is used to represent each character in the word string as the loop iterates
    {
        int index = character - 'A';
        if(current -> alphabet[index] == nullptr)     // if the alphabet node is not exist, we create one
        {
            current -> alphabet[index] = new TrieNode();
        }
        current = current -> alphabet[index];       // move on
    }
    if(current -> end_of_word)  // duplicate word
    {
        cout << "failure" << endl;
    }
    else
    {
        current -> end_of_word = true;      // after the loop reached the end of word
        cout << "success" << endl;
        word_count++;
    }
}


// c: count the number of words have same prefix
int Trie :: command_c(const string & prefix)
{
    TrieNode * current = root;
    // traverse Trie to the end of prefix
    for(char character : prefix)      // "character : prefix" - "character" is used to represent each character in the word string as the loop iterates
    {
        int index = character - 'A';
        if(current -> alphabet[index] == nullptr) 
        {
            cout << "not found" << endl;
            return 0;
        }
        current = current -> alphabet[index];
    }
    int count = count_word(current);
    cout << "count is " << count << endl;
    return count;
}
// recursive help function for counting words along one specific node
int Trie :: count_word(TrieNode * node)
{
    int count = 0;
    if(node -> end_of_word) // reach the end of word
    {
        count++;
    }
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(node -> alphabet[i] != nullptr)
        {
            count += count_word(node -> alphabet[i]);   // recursively call the function
        }
    }
    return count;
}


// e: erase the word given from Trie if it exists
void Trie :: command_e(const string & word)
{
    TrieNode * current = root;
    size_t position = 0;
    if(word_count == 0 || word.empty()) // if the Trie is empty or if the word has no character, then we will fail to erase
    {
        cout << "failure" << endl;
        return;
    }
    // traverse Trie to the end of word
    for(char character : word)      // "character : word" - "character" is used to represent each character in the word string as the loop iterates
    {
        int index = character - 'A';
        if(current -> alphabet[index] == nullptr) 
        {
            cout << "failure" << endl;
            return;
        }
        current = current -> alphabet[index];
        // cout << "children count: " << children_count(current) << endl;
        if(((current -> end_of_word == true) || (children_count(current) > 1)) && (position != (word.size()-1)))   // record the word_end node before or the last node with two or more child
        {
            // cout << "children count: " << children_count(current) << ", ";
            index_record = word[word.find(character, position) + 1] - 'A';    // 
            word_end_before_or_has_child = current;                 // 
            // cout << "recorded node: " << index_record  << endl;
        }
        // cout << "index record: " << index_record << endl;
        position++;
    }
    // change the mark for end_word sign
    if(current -> end_of_word)  // reach the end of word
    {
        current -> end_of_word = false;     // word need to delete, so it will not be the end of word
    }
    else    // have the word but it is part of another word
    {
        cout << "failure" << endl;
        return;
    }
    // check node if the end_word node is also the node with no children(leaf node)
    // cout << "try to delete" << endl;
    if(children_count(current) == 0)
    {
        delete_word(word_end_before_or_has_child -> alphabet[index_record]);    // delete the node after the marked node
        word_end_before_or_has_child -> alphabet[index_record] = nullptr;       // set the marked node's specific pointer to nullptr
    }
    cout << "success" << endl;
    word_count--;
    // cout << word_end_before_or_has_child -> alphabet[index_record];
}
// helper recursive function for deletion
void Trie :: delete_word(TrieNode * node)
{
    if(node == nullptr || node == root) return;
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        delete_word(node -> alphabet[i]);
    }
    delete node;
}
// helper function to count if node have children
int Trie :: children_count(TrieNode * node)
{
    int count = 0;
    for(int i = 0; i < ALPHABET_SIZE; i++)  // go over to see if it has children
    {
        if(node -> alphabet[i] != nullptr)
        {   
            count++;
        }
    }
    return count;
}


// p: print all words in the Trie
void Trie :: command_p()
{
    if(root == nullptr || word_count == 0) return;

    print_word(root, "");
    cout << endl;
}
// recursive function, in_order traversal, asked chatgpt for the prefix for tracking the characters of a word
void Trie :: print_word(TrieNode * node, string prefix)
{
    if(node == nullptr) return;

    if(node -> end_of_word) // if reached the end of word(prefix become word), print the word in prefix
    {
        cout << prefix << " ";
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(node -> alphabet[i] != nullptr)
        {
            print_word(node -> alphabet[i], prefix + char('A' + i));    // here we keep adding corresponding characters to prefix
        }
    }
}


// spellcheck: check if word in the Trie, return "correct" if exits, else suggest words that have the max common prefix
void Trie :: command_spellcheck(const string & word)
{
    TrieNode * current = root;
    string same_prefix = "";
    // traverse Trie to the end of prefix
    if(current -> alphabet[word.front() - 'A'] == nullptr) // if there is no suggestions(first letter not found), turn a new line
    {
        cout << endl;
        return;
    } 
    for(char character : word)      // "character : word" - "character" is used to represent each character in the word string as the loop iterates
    {
        int index = character - 'A';
        if(current -> alphabet[index] == nullptr || children_count(current) == 0)   // if the given word have characters that not in the corresponding position or the word exceed the max length of the containing words
        {
            // cout << "prefix found: " << same_prefix << endl;
            print_word(current, same_prefix);
            cout << endl;
            return;
        }
        current = current -> alphabet[index];
        same_prefix += char('A'+ index);
        // cout << "prefix time: " << same_prefix << endl;
    }
    if(current -> end_of_word != true) // after go over the given word, then it is part of another word
    {
        // cout << "prefix2 found: " << same_prefix << endl;
        print_word(current, same_prefix);
        cout << endl;
        return;
    }
    // cout << "prefix3 found: " << same_prefix << endl;
    cout << "correct" << endl;
}


// empty: check if the Trie is empty, "empty 1" for empty, otherwise "empty 0"
void Trie :: command_empty()
{
    if(word_count == 0) // trie is empty
    {
        cout << "empty 1" << endl;
    }
    else
    {
        cout << "empty 0" << endl;
    }
}


// clear: delete all words from Trie
void Trie :: command_clear()
{
    if(word_count == 0) return;
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        deleteNode(root -> alphabet[i]);
        root -> alphabet[i] = nullptr;
    }  
    word_end_before_or_has_child = nullptr;
    word_count = 0;
}
// helper recursive function for clear
void Trie :: deleteNode(TrieNode * node)
{
    if(node == nullptr) return;
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        deleteNode(node -> alphabet[i]);
    }
    delete node;
}


// size: print the number of words in the Trie
void Trie :: command_size()
{
    cout << "number of words is " << word_count << endl;
}


// exit: end the program
void Trie :: command_exit()
{
    command_clear();
    exit(0);
}
