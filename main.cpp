#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <stack>
#include "Trie.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    Trie tree;
    string a = "Elect";
    string b = "element";
    string c = "embarrassing";
    string d = "emergency";
    string e = "enemy";
    string f = "energy";
    string g = "button";
    string h = "butterfly";
    string i = "bus";
    string j = "busz";
    tree.paste(a); tree.paste(b); tree.paste(c); tree.paste(d); tree.paste(e); tree.paste(f);
    tree.paste(g); tree.paste(h); tree.paste(i); tree.paste(j);
  
    
    int max_numb_letters = 8;    // ����� ���������� ���� ������� ��������� � ��������� �����
    cout << "��������� ���������� �������� ���� �� ������� �� ��������� ������\n";
    cout << "��������� �����:\n\n";
    tree.printAll();
    cout << "\n��� ������ �� ��������� ������� 0\n";
    string input;

    while (1)
    {
        cout << "������� ����� ��� ��� ������: ";
        getline(cin,input);
        if (input == "0") 
            break;
        tree.getWords(input, max_numb_letters);
    }
    cout << "�����!\n";
  
   return 0;
}