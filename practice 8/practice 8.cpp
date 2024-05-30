#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

typedef bool (*ContainsAllCharsFunc)(const char*, const char*);

int main() {
    setlocale(LC_ALL, "RU");
    string inputStr;
    string inputChars;

    cout << "Введите текст: ";
    getline(cin, inputStr);

    cout << "Введите фразу для поиска: ";
    getline(cin, inputChars);

    HINSTANCE hLib = LoadLibrary(L"StringChecker.dll");
    if (hLib == NULL) {
        cerr << "Библиотека не найдена!" << endl;
        return 1;
    }

    ContainsAllCharsFunc contains_all_chars = (ContainsAllCharsFunc)GetProcAddress(hLib, "contains_all_chars");
    if (contains_all_chars == NULL) {
        cerr << "Не удалось получить адрес функции!" << endl;
        FreeLibrary(hLib);
        return 1;
    }

    bool result = contains_all_chars(inputStr.c_str(), inputChars.c_str());

    if (result) {
        cout << "Введённая фраза найдена в тексте." << endl;
    }
    else {
        cout << "Фраза не найдена в тексте." << endl;
    }

    FreeLibrary(hLib);

    return 0;
}


