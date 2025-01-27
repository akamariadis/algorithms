#include <iostream>
#include <unordered_map>
#include <cstring>
using namespace std;

int M = 1000003;

unsigned int hash_num(unsigned long long n) {
    return n % M;
}

int base = 256;

unsigned int hash_word(char *str) {
    int s = strlen(str);
    unsigned int out = 0;
    for(int i = 0; i < s; ++i) {
        out = ((out*base) % M + str[i]) % M;
    }
    return out;
}

int a[2], b[2];

vector<pair<string, string>> table[2][M], table[M];
void initialize() {
    srand(time(NULL));
    a[0] = rand() % 1000;
    a[1] = rand() % 1000;
    b[0] = rand() % 1000;
    b[1] = rand() % 1000;
}

unsigned int hash_word(string str, int ind) {
    int s = str.size();
    unsigned int out = 0, tmp;
    for(int i = 0; i < s; ++i) {
        tmp = (a[ind] * str[i] + b[ind]) % base;
        out = ((out*base) % M + tmp) % M;
    }
}

void insert(string key, string value) {
    unsigned int pos[2];
    pos[0] = hash_word(key, 0);
    pos[1] = hash_word(key, 1);
    for(int k = 0; k < 2; ++k) {
        for(int i = 0; i < table[k][pos[k]].size(); ++i) {
            if(table[k][pos[k]][i].first == key) {
                table[k][pos[k]][i].second = value;
                return;
            }
        }
    }
    int k = 0;
    if(table[1][pos[1]].size() < table[0][pos[0]].size()) {
        k = 1;
    }
    table[k][pos[k]].insert(make_pair(key, value));
}

string lookup(string key) {
    string out;
    unsigned int pos[2];
    pos[0] = hash_word(key, 0);
    pos[1] = hash_word(key, 1);
    for(int k = 0; k < 2; ++k) {
        for(int i = 0; i < table[k][pos[k]].size(); ++i) {
            if(table[k][pos[k]][i].first == key) {
                out = table[k][pos[k]][i].second;
            }
        }
    }
    return out;
}

pair<string, string> table[M];

unsigned int hash_word(string str) {
    int s = str.size();
    unsigned int out = 0;
    for(int i=0; i<s; ++i) {
        out = ((out * base) % M + str[i]) % M;
    }
}

void insert(string key, string value) {
    unsigned int pos = hash_word(key);
    while(!table[pos][i].first.empty() && table[pos][i].first != key) {
        pos = (pos + 1) % M;
    }
    table[pos] = make_pair(key, value);
}

string lookup(string key) {
    string out;
    unsigned int pos = hash_word(key);
    while(!table[pos][i].first.empty() && table[pos][i].first != key) {
        pos = (pos + 1) % M;
    }
    return table[pos].second;
}

unordered_map<string, string> table;

void initialize(int n) {
    table.rehash(n);
}

void insert(string key, string value) {
    table[key] = value;
}

void lookup(string key) {
    if(table.find(key) != table.end()) {
        return table[key];
    }
    return "";
}
