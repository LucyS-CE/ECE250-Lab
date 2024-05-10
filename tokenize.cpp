#include <iostream>
#include <string>
#include <vector>   // for mapping tokens to words
#include <forward_list> // for resize
#include <cctype>       // for checking the non-alphabetic characters 
#include <fstream>  // for read txt
#include <ctime>   // for count time cost for load function
#include <chrono>   // for count time cost for load function

#include "tokenize.h"

// const int MAX_INT = 2147483647;
// implement classes' member functions here...

// 1. parameters[] ?int????????
// 2. ??function???????????????????
// 3. ????word??load txt?????load factor?????0.8????rehash
// 4. rehash?function???deallocate???hash
// 5. ???????function for mapping token to word

Dictionary :: ~Dictionary()
{
    delete[] table;
    if(parameters != nullptr)
    {
        delete[] parameters;
    }
    array.clear();
}

// create size(range 1~256): Create a hash table with a size of size. 
void Dictionary :: command_create(const int & size)
{
    if(size >=1 && size <=256)
    {
        table_size = size;
    }
    else
    {
        table_size = 256;
    }
    table = new HashNode * [size];
    key_value_pairs = 0;
    memset(table, 0, size * sizeof(HashNode *));
    cout << "success create" << endl;
} 

// insert word: insert the word into the dictionary only if it does not already exist and is entirely alphabetic.
void Dictionary :: command_insert(const string & word)
{
    if(insert(word))   // word is insert successfully
    {
        cout << "success insert" << endl;
        rehash();
    }
    else
    {
        cout << "failure insert" << endl;
    }
}

// load filename: insert all words in the filenameWords in filename are separated by white spaces. This operation is successful only if at least one word is inserted into the dictionary
void Dictionary :: command_load(const string & filename)
{
    ifstream file(filename);
    if(!file.is_open())
    {
        cout << "error opening file" << endl;
        return;
    }

    // start the timer
    // clock_t start = clock();
    auto start = chrono::high_resolution_clock::now();

    string word;
    bool insertion_success = false; // flag to track if any insertion succeeds, start at false
    while (file >> word)     // reach char by char
    {
        if(word.empty())
        {
            continue;   // skip empty line
        }
        if(insert(word))
        {
            insertion_success = true;   
        }
    }
    rehash();
    if(!insertion_success)
    {
        cout << "failure load" << endl;
    }
    else
    {
        cout << "success load" << endl;
    }

    // Stop the timer
    // clock_t end = clock();
    auto stop = chrono::high_resolution_clock::now();

    // Calculate the duration
    // double duration = double(end - start) / CLOCKS_PER_SEC;
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
    // cout << "time cost: " << duration << "s" << endl;
    cout << "num of words " << key_value_pairs << endl;

    file.close();
}

// tok word: Return the numeric token associated with word. Return -1 if word does not exist in the dictionary.
int Dictionary :: command_tok(const string & word)
{
    if(check_exist(array, word))    // exist in dictionary
    { 
        return get_token(word);
    }
    else
    {
        return -1;
    }
}

// ret token(range 1~MAX_INT) Retrieve the word associated with token, only if it exists in the dictionary.
string Dictionary :: command_ret(const int & token)
{
    if(token >= 1 && token <= key_value_pairs)    // exist in dictionary
    {
        return array[token];
    }
    else
    {
        return "N/A";
    }
}

// tok_all W1 W2 ...: Tokenize all words, which are separated by white spaces only. For each non-existing word print -1.
void Dictionary :: command_tok_all()
{
    for(int i = 0; i < para_count; i++)
    {
        cout << command_tok(parameters[i]) << " ";
    }
    cout << endl;
}

// ret_all T1 T2 ...(range 1~MAX_INT): Retrieve the words of all tokens, which are separated by white spaces. For each non-existing token print N/A.
void Dictionary :: command_ret_all()
{
    for(int i = 0; i < para_count; i++)
    {
        cout << command_ret(stoi(parameters[i])) << " ";
    }
    cout << endl;
}

// print k(range 0~MAX_INT): Print the keys in the chain at hash table position k (0 ? k < m). No output for invalid k or empty chain
void Dictionary :: command_print(const int & k)
{
    if(k >= 0 && k <= key_value_pairs && key_value_pairs != 0)
    {
        HashNode * current = table[k];
        while(current != nullptr)
        {
            cout << current -> key << " ";
            current = current -> next;
        }
        cout << endl;
    }
}

// exit: exit the program
void Dictionary :: command_exit()
{
    cout << endl;
    exit(0);
}
