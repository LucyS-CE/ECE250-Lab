#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;
// define your classes here...
class Trie
{
    private:
        struct TrieNode
        {
            TrieNode * alphabet[ALPHABET_SIZE];    // for 1~26 indicate 26 different characters, 1 means A, 2 means B ...
            bool end_of_word;   // indicate if it reach the end of the word

            TrieNode()     // constructor
            {
                for(int i = 0; i < 26; i++)
                {
                    alphabet[i] = nullptr;
                }
                end_of_word = false;
            }
        };
        TrieNode * root;

    public:
        Trie()  // constructor
        {
            root = new TrieNode();
        }
        ~Trie();    // destructor

        // load N/A: load the corpus into the Trie
        void command_load(const string & file);

        // i word: insert word into Trie if the word is not in it
        void command_i(const string & word);

        // c prefix: output numbers of words in the Trie that have the given prefix
        int command_c(const string & prefix);

        // e word: erase word from the Trie if it exists
        void command_e(const string & word);

        // p N/A: print all words in the Trie in the alphabetical order on a single line, no output if the Trie is empty
        void command_p();

        // spellcheck word: if the word is in the Trie print "correct"; if not suggest words that have the max common prefix; no output if no suggestion found (... more details see the project file)
        void command_spellcheck(const string & word);

        // empty N/A: check if the Trie is empty, "empty 1" for empty, otherwise "empty 0"
        void command_empty();

        // clear N/A: delete all words from Trie
        void command_clear();

        // size N/A: print the number of words in the Trie
        void command_size();

        // exit N/A: end the program
        void command_exit();        

        void deleteNode(TrieNode * node);
        int count_word(TrieNode * node);
        int children_count(TrieNode * node);
        void delete_word(TrieNode * node);
        void print_word(TrieNode * node, string prefix = "");

        TrieNode * word_end_before_or_has_child = nullptr;
        int word_count = 0;
        int index_record = 0;
};
#endif
