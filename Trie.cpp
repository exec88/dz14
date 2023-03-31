#include "Trie.h"
using namespace std;
Trie::Trie()
{
    origin = new TrieNode;
}

Trie::~Trie()
{
    delete origin;
}

void Trie::paste(string& key)
{
    TrieNode* triePtr = origin;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32;
        if (triePtr->children[index] == NULL) triePtr->children[index] = new TrieNode;
        triePtr = triePtr->children[index];
    }
    triePtr->isEndWord = true;
}

bool Trie::search(string& key)
{
    TrieNode* triePtr = origin;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32;
        if (triePtr->children[index] == NULL) return false;
        triePtr = triePtr->children[index];
    }
    return ((triePtr != NULL) && (triePtr->isEndWord == true));
}

bool Trie::isTrieEmpty()
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (origin->children[i] != NULL) 
            
            return false;
    }
    return true;
}

bool Trie::isEmpty(TrieNode*& node)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL) 
            
            return false;
    }
    return true;
}

void Trie::removeKey(string& key)                  // �������� ����� �� �������
{
    if (origin == NULL) // ������ �������
        return;                            
    stack<TrieNode*> toDelete;
    toDelete.push(origin);
    TrieNode* triePtr = origin;
    for (size_t i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32;
        if (triePtr->children[index] == NULL)              // ������ ����� ���
            return;              
        
        toDelete.push(triePtr->children[index]);
        triePtr = triePtr->children[index];                             // �������� � ���������� �������
    }
    if (triePtr->isEndWord == true) triePtr->isEndWord = false;
    if (isEmpty(triePtr) == false) return;
    int k = key.length() - 1;
    triePtr = toDelete.top(); toDelete.pop();
    while (k >= 0)
    {
        // ��������� �������� ������ ������ ������-���� ����� ���� ��� ��
        if (triePtr->isEndWord == true) delete triePtr;              // �������
        else 
            break;                                                    // ���� ������ �� ������� ����� ����������� �������
        triePtr = toDelete.top();                                    // ������� ���������� �� ��������
        toDelete.pop();
        int delSymbolIndex = key[k] - 'a';
        if ((delSymbolIndex >= -32) && (delSymbolIndex <= -7)) delSymbolIndex += 32;
        triePtr->children[delSymbolIndex] = NULL;
        if (triePtr == origin) 
            break;

        if (triePtr->isEndWord == true) break;
        k--;
    }
}

void Trie::printTestInternal(TrieNode*& node, string& toPrint)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            toPrint.push_back((char)(i + 'a'));
            if (node->children[i]->isEndWord == true)
            {
                cout << toPrint << " ";
                
                if (!toPrint.empty()) toPrint.erase(toPrint.end() - 1);
                return;
            }
            printTestInternal(node->children[i], toPrint);
            if (!toPrint.empty()) toPrint.erase(toPrint.end() - 1);
        }
    }
}

void Trie::printTest()
{
    string toPrint;
    printTestInternal(origin, toPrint);
    cout << "\n";
}

void Trie::printAllInternal(TrieNode*& node, string& toPrint)
{
    if (isEmpty(node) == true)
    {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            toPrint.push_back((char)(i + 'a'));
            if (node->children[i]->isEndWord == true)
            {
                cout << toPrint << " ";
            }
            printAllInternal(node->children[i], toPrint);
            if (!toPrint.empty()) toPrint.erase(toPrint.end() - 1);
        }
    }
}

void Trie::printAll()
{
    string str;
    printAllInternal(origin, str);
    cout << "\n";
}

void Trie::getWordInternal(TrieNode*& node, vector<string>& words, string& word, const int maxLength, int& currentLength)
{
    if (isEmpty(node) == true)        // ���� ����� �� ����� ������������
    {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)               // ��� �������� ����� ��������� ��������� �����
    {
        if (node->children[i] != NULL)                    // ���� ����� ����� ��� ��� �� �������� � ��������� �����
        {
            currentLength++;                                // ����������� ����� ����� �� �������
            word.push_back((char)(i + 'a'));              // ��������� ����� ��������� �����
            if (currentLength > maxLength)
            {
                if (!word.empty())                       // ��������� �� ����� �� �����
                {
                    word.erase(word.end() - 1);           // ����� �� ����� �� ������� ��������� ����������� ������
                }
                currentLength--;                             // ��������� ����� �����
                return;
            }
            if (node->children[i]->isEndWord == true)
            {
                words.push_back(word);
            }
            getWordInternal(node->children[i], words, word, maxLength, currentLength);
            if (!word.empty())
            {
                word.erase(word.end() - 1);
                currentLength--;
            }
        } 
    }
}

void Trie::getWords(string& halfWord, const int maxLength)
{
    TrieNode* triePtr = origin;
    vector<string> words;
    for (size_t i = 0; i < halfWord.size(); i++)
    {
        int index = halfWord[i] - 'a';
        if ((index >= -32) && (index <= -7)) index += 32; 
        if (triePtr->children[index] == NULL)               // ������ ����� �� � ������� �� ����������
            return;        

        triePtr = triePtr->children[index];                        // ��������� �� �����
    }
    TrieNode* hwEnd = triePtr;                         // ���������� ��������� ����� ���������� �����
        
    int currentLength = 0;
    string word;
    getWordInternal(triePtr, words, word, maxLength, currentLength);
           
    if (hwEnd->isEndWord == true) cout << halfWord << "\n";      // ���� ����� ����� �������� ����������� ��������� ��� � ������ ������������
    for (size_t i = 0; i < words.size(); i++)
    {
        cout << halfWord + words[i] << "\n";
    }
}

void Trie::findMinPrefixes()
{
    char buf[ALPHABET_SIZE];
    string res;
    int ind = 0;
    TrieNode* node = origin;
    findMinPrefixes(node, buf, ind, res);
    cout << "\n" << res << "\n";
}

void Trie::findMinPrefixes(TrieNode* node, char buf[], int ind, string& res)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != NULL)
        {
            buf[ind] = (char)(i + 'a');
            buf[ind + 1] = '\0';
            ind++;
                        
            if ((isSingleThread(node->children[i]) == true) && (wordCount(node->children[i]) == 1)) // �����
            {
                res += buf;
                res += " ";
                ind--;
            }
            else
            {
                findMinPrefixes(node->children[i], buf, ind, res);
                ind--;
            }
            
        }
    }
}

void Trie::SingleThreadInternal(TrieNode* node, bool& multiChildDetector)
{
    if (multiChildDetector == true) 
        return;

    int ctr = 0;
    int who;
    for (int i = 0; i < ALPHABET_SIZE; i++)              // ���������� ������� ����������� � �������
    {
        if (node->children[i] != nullptr)
        {
            who = i;
            ctr++;
        }
    }
    if (ctr >= 2)
    {
        multiChildDetector = true;
        return;
    }
    if (ctr == 0) return;                 // ���� ����������� ��� �� ������ return

   SingleThreadInternal(node->children[who], multiChildDetector);
}

bool Trie::isSingleThread(TrieNode* node)
{
    bool multiChildDetector = false;
    SingleThreadInternal(node, multiChildDetector);
    return !multiChildDetector;
}

bool Trie::singleThread()
{
    return !isSingleThread(origin);
}

int Trie::wordCount()
{
    return wordCount(origin);
}

int Trie::wordCount(TrieNode* node)
{
    int count = 0;
    if (node->isEndWord == true) count++;
    wordCountInternal(node, count);
    return count;
}

void Trie::wordCountInternal(TrieNode* node, int& count)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            if (node->children[i]->isEndWord == true)
            {
                count++;
            }
            wordCountInternal(node->children[i], count);
        }
    }
}