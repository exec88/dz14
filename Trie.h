#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <stack>
using namespace std;

const int ALPHABET_SIZE = 32;

struct TrieNode
{
    TrieNode()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            children[i] = NULL;
        }
        isEndWord = false;
       
    }
    ~TrieNode()
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (children[i] != NULL) delete children[i];
        }
       
    }
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndWord;
};

class Trie
{
public:
    Trie();
    ~Trie();

    void paste(string& key);
    bool search(string& key);
    bool isTrieEmpty();                     // проверка пуст словарь ли
    void removeKey(string& key);
    void printAll();                 // вывод всех слов
    void getWords(string& halfWord, const int maxLength);
    void printTest();
    void findMinPrefixes();
    bool singleThread();
    int wordCount();

private:
    bool isEmpty(TrieNode*& node);
    void printAllInternal(TrieNode*& node, string& toPrint);
    void getWordInternal(TrieNode*& node, vector<string>& words, string& word, const int maxLength, int& currentLength);
    void printTestInternal(TrieNode*& node, string& toPrint);
    void findMinPrefixes(TrieNode* node, char buf[], int ind, string& res);
    bool isSingleThread(TrieNode* node);
    void SingleThreadInternal(TrieNode* node, bool& multiChildDetector);              
    int wordCount(TrieNode* node);                                          
    void wordCountInternal(TrieNode* node, int& count);                                 
    TrieNode* origin;
};
