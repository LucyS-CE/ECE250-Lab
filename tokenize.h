#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <iostream>
#include <string>
#include <vector>   // for mapping tokens to words
#include <forward_list> // for rehash, but I did not use it
#include <cstring>  // for strcmp to compare case sensitivity

using namespace std;

// define your classes here...
class Dictionary
{
    private: 
        // (move to public) int key_value_pairs;        // for record number of word stored
        int table_size;        // for calculating hash value in hash function
        double load_factor;         // for load factor (key value pairs)/(table size) = average chain length

        struct HashNode
        {
            string key;    // key word
            int value;      // token, index for vector array
            HashNode * next;
            HashNode(const string& w, int t) : key(w), value(t), next(nullptr) {};
        };

        // for mapping words to token
        HashNode ** table;
        // for mapping tokens to words (can use <vector>)
        vector<string> array;

        // hash function from project file (to calculate the hash value of a word)
        unsigned hash(const string & word, int size) 
        {
            if(word.empty()) 
            {
                cout << "here's empty word" << endl;
            }
            unsigned ans = 0;
            for (auto it = word.begin(); it != word.end(); ++it)
            {
                ans = ans * 29 + *it;
            }
            return ans % size;
        }

        // rehash function resize when load_factor is greater or equal to 0.8
        void rehash() 
        {
            if(load_factor_cal(key_value_pairs, table_size) >= 0.8)
            {
                // int new_size = table_size*2;
                int new_size = table_size;
                while(load_factor_cal(key_value_pairs, new_size) >= 0.8)
                {
                    new_size *= 2;
                }
                HashNode ** new_table = new HashNode * [new_size];  // create a larger array
                memset(new_table, 0, new_size * sizeof(HashNode *));
                // array.clear();  // clear the array so we can apply new token to words
                key_value_pairs = 0;
                //cout << "1" << endl;
                for(int i = 0; i < table_size; i++)
                {
                    HashNode * current = table[i];
                    //cout << "1.1" << endl;
                    while(current != nullptr)
                    {
                        //cout << "1.2" << endl;
                        HashNode * next_node = current -> next;
                        //cout << "1.3" << endl;
                        int hash_index = hash(current -> key, new_size);
                        //cout << "1.4" << endl;
                        //cout << "1.5" << endl;
                        // set_token_word(key_value_pairs, current -> key);  // reset mapping array for token(pair#) to word
                        current -> next = new_table[hash_index]; // now new_table[token] is nullptr
                        new_table[hash_index] = current; 
                        current = next_node;
                        key_value_pairs++;
                        //cout << "1.9" << endl;
                    }
                }
                //cout << "2" << endl;
                delete[] table;
                //cout << "3" << endl;
                table = new_table;
                table_size = new_size;
                // cout << "success rehash" << endl;
            }
        }

        // to calculate the load factor
        double load_factor_cal(int key_value_pairs, int table_size)
        {
            double pairs = key_value_pairs; // change it to double
            return pairs/table_size;
        }

        // create a mapping array for token and word pairs
        void set_token_word(size_t token, const string & word)
        {
            // token = token + 1;
            if(token >= array.size())
            {
                array.resize(token + 1);    // need to check and resize, since the token we use may not be continuous
            }
            array[token] = word;
        }

    public:
        int key_value_pairs;    
        string * parameters;
        int para_count;

        Dictionary() : table_size(0), load_factor(0), table(nullptr), key_value_pairs(0), parameters(nullptr), para_count(0){};
        ~Dictionary();

        // create size(range 1~256): Create a hash table with a size of size. 
        void command_create(const int & size);

        // insert word: insert the word into the dictionary only if it does not already exist and is entirely alphabetic.
        void command_insert(const string & word);

        // load filename: insert all words in the filenameWords in filename are separated by white spaces. This operation is successful only if at least one word is inserted into the dictionary
        void command_load(const string & filename);

        // tok word: Return the numeric token associated with word. Return -1 if word does not exist in the dictionary.
        int command_tok(const string & word);

        // ret token(range 1~MAX_INT) Retrieve the word associated with token, only if it exists in the dictionary.
        string command_ret(const int & token);

        // tok_all W1 W2 ...: Tokenize all words, which are separated by white spaces only. For each non-existing word print -1.
        void command_tok_all();

        // ret_all T1 T2 ...(range 1~MAX_INT): Retrieve the words of all tokens, which are separated by white spaces. For each non-existing token print N/A.
        void command_ret_all();

        // print k(range 0~MAX_INT): Print the keys in the chain at hash table position k (0 ? k < m). No output for invalid k or empty chain
        void command_print(const int & k);

        // exit: exit the program
        void command_exit();

        bool check_alpha(const string & word)
        {
            for(char c : word)
            {
                if(isalpha(c) == false) return false;
                // cout << "word not valid" << endl;
            }
            // cout << "word valid" << endl;
            return true;
        }

        bool check_exist(const vector<string> & words, const string & target_word)
        {
            for(const string & word : words)
            {
                if(strcmp(word.c_str(), target_word.c_str()) == 0)  // asked chat gpt for the header <cstring> and refers to https://cplusplus.com/reference/cstring/ for usage
                {
                    // cout << "word exist" << endl;
                    return true;
                }
            }
            // cout << "word not exist" << endl;
            return false;
        }

        bool insert(const string & word)
        {
            if(!word.empty() && check_alpha(word) && !check_exist(array, word) && word.size() <= 256)   // word not empty, it has no non-alpha characters, it is not exist in dictionary and its length is less than 256
            {
                // cout << "table size insert: " << table_size << endl;
                int hash_index = hash(word, table_size);
                HashNode * newNode = new HashNode(word, key_value_pairs);
                // cout << "word: " << word << ", token: " << key_value_pairs << ", hash_index: " << hash_index << endl;
                newNode -> next = table[hash_index]; // now table[index] is nullptr or another node
                table[hash_index] = newNode;
                key_value_pairs++;
                set_token_word(key_value_pairs, word);  // set mapping array for token(pair#) to word
                // cout << "key value pairs insert: " << key_value_pairs << endl;
                return true;
            }
            else
            {
                return false;
            }
        }

        int get_token(const string & word)
        {
            for(int i = 1; i <= key_value_pairs; i++)
            {
                if(array[i] == word)
                {
                    return i;
                }
            }
            return -1;
        }

        // void print_table()
        // {
        //     cout << "================ table ===================" << endl;
        //     cout << "table size: " << table_size << endl;
        //     cout << "key value pairs: " << key_value_pairs << endl;
        //     for(int i = 0; i < table_size; i++)
        //         {
        //             HashNode * current = table[i];
        //             if(current != nullptr)
        //             {
        //                 cout << "at position " << i << " keys are : ";
        //                 while(current != nullptr)
        //                 {
        //                 cout << "{" << current -> key << "}";
        //                 current = current -> next;
        //                 }
        //                 cout << endl;
        //             }
        //         }
        //     cout << "============== END table =================" << endl;
        // }

        // void print_array()
        // {
        //     cout << "================ array ===================" << endl;
        //     cout << key_value_pairs << endl;
        //     for(int i = 1; i <= key_value_pairs; i++)
        //     {
        //         cout << array[i] << " ";
        //     }
        //     cout << endl;
        //     cout << "============== END array =================" << endl;
        // }
};

#endif