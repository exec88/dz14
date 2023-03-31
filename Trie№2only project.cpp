/* <iostream>
#include <vector>
#include <string>
#include "Trie.h"
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool is_word_end;
};


//Поскольку в английском алфавите всего 26 букв, то каждый узел дерева будет иметь массив указателей на 26 дочерних узлов, каждый из которых соответствует одной букве алфавита.boolean - поле is_word_end будет указывать, заканчивается ли слово в узле дерева.

//Далее нужно создать класс Trie(Trie.h), который будет представлять собой саму структуру данных "дерево":





//Здесь мы объявляем указатель на корневой узел дерева, а также методы : конструктор, деструктор для освобождения памяти, insert для добавления новых слов в дерево, search для поиска слова в дереве и autocomplete для автодополнения.

//Реализация метода insert :


void Trie::insert(string word) {
    TrieNode* node = root;
    for (char c : word) {
        int index = c - 'a';
        if (node->children[index] == NULL) {
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->is_word_end = true;
}


//Метод для поиска слова в дереве :


bool Trie::search(string word) {
    TrieNode* node = root;
    for (char c : word) {
        int index = c - 'a';
        if (node->children[index] == NULL) {
            return false;
        }
        node = node->children[index];
    }
    return node != NULL && node->is_word_end;
}


//Метод для автодополнения :

void Trie::traverse(vector<string>& result, TrieNode* node, string prefix) {
    if (node->is_word_end) {
        result.push_back(prefix);
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            traverse(result, node->children[i], prefix + (char)('a' + i));
        }
    }
}

vector<string> Trie::autocomplete(string prefix) {
    vector<string> result;
    TrieNode* node = root;
    for (char c : prefix) {
        int index = c - 'a';
        if (node->children[index] == NULL) {
            return result;
        }
        node = node->children[index];
    }
    traverse(result, node, prefix);
    return result;
}




//Метод traverse перебирает все узлы дерева, начиная с заданного узла, и добавляет все слова, которые состоят из этой части префикса в вектор результатов.

//Осталось только реализовать конструктор и деструктор :


Trie::Trie() {
    root = new TrieNode();

    free(root);
}

void Trie::free(TrieNode* node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        free(node->children[i]);
    }
    delete node;
}


//Для тестирования нашей реализации Trie, мы можем использовать следующий код :

int main()
{
    Trie dict;
    dict.insert("hello");
    dict.insert("world");
    dict.insert("hell");
    dict.insert("hi");
    cout << dict.search("hello") << endl; // выведет 1
    cout << dict.search("worlds") << endl; // выведет 0
    vector<string> suggestions = dict.autocomplete("hel");
    for (string s : suggestions) {
        cout << s << endl;
    }
}
//"hello", "hell"*/
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* Определяем структуру узла трие
struct TrieNode {
    char ch;
    bool is_end;
    vector<TrieNode*> children;

    TrieNode(char c) {
        ch = c;
        is_end = false;
        children = vector<TrieNode*>(26, NULL); // Для латиницы
    }
};

// Добавление слова в трие
void addWord(TrieNode* root, string& word) {
    TrieNode* currNode = root;
    for (char c : word) {
        int index = c - 'a'; // Для латиницы
        if (currNode->children[index] == NULL)
            currNode->children[index] = new TrieNode(c);
        currNode = currNode->children[index];
    }
    currNode->is_end = true;
}

// Поиск слов, начинающихся с данной части
void findWords(TrieNode* node, const string& prefix, vector<string>& results) {
    if (node == NULL) return;

    if (node->is_end) results.push_back(prefix);

    for (int i = 0; i < node->children.size(); ++i) {
        // Если есть символы префикса, следуем по соответствующему пути
        if (prefix.empty() || node->children[i] == NULL || node->children[i]->ch == prefix[0])
            findWords(node->children[i], prefix.substr(1), results);
    }
}

int main() {
    vector<string> words = { "apple", "banana", "pear", "peach", "pineapple" };
    string prefix = "pe";

    TrieNode* root = new TrieNode(' ');
    for (string& word : words)
        addWord(root, word);

    vector<string> results;
    findWords(root, prefix, results);
    for (string& word : results)
        cout << word << endl;

    return 0;
}*/

class TrieNode {
public:
    char data;
    unordered_map<char, TrieNode*> children;
    bool end_of_word;
    TrieNode* parent;

    TrieNode(char data) {
        this->data = data;
        end_of_word = false;
        parent = nullptr;
    }
};


//Далее, мы можем создать класс Trie(также известный как "Префиксное дерево"), который будет содержать корень дерева и методы для вставки слов, поиска слов и автодополнения.

//Вот вариант кода для класса Trie :

class Trie {
public:
    TrieNode* root;
    unordered_map<string, int> word_frequency;

    Trie() {
        root = new TrieNode('\0');
    }

    void insert(string word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode(c);
                current->children[c]->parent = current;
            }
            current = current->children[c];
        }
        current->end_of_word = true;
        word_frequency[word]++;
    }

    bool search(string word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->end_of_word;
    }

    vector<string> autoComplete(string prefix) {
        TrieNode* current = root;
        vector<string> words;

        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return words;
            }
            current = current->children[c];
        }

        traverse(current, prefix, words);

        
        sort(words.begin(), words.end(), [&](const string a, const string b) {
            return word_frequency[a] > word_frequency[b];
            });

        return words;
    }

private:
    void traverse(TrieNode* current, string prefix, vector<string>& words) {
        if (current->end_of_word) {
            words.push_back(prefix);
        }

        for (auto it = current->children.begin(); it != current->children.end(); ++it) {
            traverse(it->second, prefix + it->first, words);
        }
    }
};


//Метод `insert()` вставляет слово в дерево, метод `search()` проверяет, существует ли слово в дереве, а метод `autoComplete()` находит все слова, начинающиеся с заданного префикса.

//Наконец, мы можем создать бесконечный цикл для ввода слов пользователем и вывода списка автодополнений.


int main()

{
    setlocale(LC_ALL, "");
    Trie* dictionary = new Trie();

    // Здесь можно вставить начальный словарь слов
    dictionary->insert ("apple");
    dictionary->insert ("apocal");
    dictionary->insert ("application");
    dictionary->insert ("appstore");
    dictionary->insert("banana");
    dictionary->insert("cat");
    dictionary->insert("dog");

    cout << "Введите слово (или q для выхода):" << endl;
    string input;
    while (cin >> input && input != "q") {
        vector<string> suggestions = dictionary->autoComplete(input);

        for (string word : suggestions) {
            cout << word << endl;
        }

        cout << "Введите слово (или q для выхода):" << endl;
    }

    if (input == "q") {
        cout << "Завершение работы программы." << endl;
        
    }

      return 0;
}