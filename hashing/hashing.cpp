#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

const int M = 1000003; 
const int base = 256;  

unsigned int hash_num(unsigned long long n) {
    return n % M;
}

unsigned int hash_word(const char *str) {
    int s = strlen(str);
    unsigned int out = 0;
    for (int i = 0; i < s; ++i) {
        out = ((out * base) % M + str[i]) % M;
    }
    return out;
}

int a[2], b[2];

vector<pair<string, string>> table[2][M];

void initialize() {
    srand(time(NULL));
    a[0] = rand() % 1000;
    a[1] = rand() % 1000;
    b[0] = rand() % 1000;
    b[1] = rand() % 1000;
}

unsigned int hash_word(const string& str, int ind) {
    int s = str.size();
    unsigned int out = 0, tmp;
    for (int i = 0; i < s; ++i) {
        tmp = (a[ind] * str[i] + b[ind]) % base;
        out = ((out * base) % M + tmp) % M;
    }
    return out;
}

void insert_cuckoo(const string& key, const string& value) {
    unsigned int pos[2] = { hash_word(key, 0), hash_word(key, 1) };

    for (int k = 0; k < 2; ++k) {
        for (auto& pair : table[k][pos[k]]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
    }

    int k = (table[1][pos[1]].size() < table[0][pos[0]].size()) ? 1 : 0;
    table[k][pos[k]].push_back(make_pair(key, value));
}

string lookup_cuckoo(const string& key) {
    unsigned int pos[2] = { hash_word(key, 0), hash_word(key, 1) };

    for (int k = 0; k < 2; ++k) {
        for (const auto& pair : table[k][pos[k]]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
    }
    return "";
}

pair<string, string> linear_table[M];

unsigned int hash_word(const string& str) {
    int s = str.size();
    unsigned int out = 0;
    for (int i = 0; i < s; ++i) {
        out = ((out * base) % M + str[i]) % M;
    }
    return out;
}

void insert_linear(const string& key, const string& value) {
    unsigned int pos = hash_word(key);
    while (!linear_table[pos].first.empty() && linear_table[pos].first != key) {
        pos = (pos + 1) % M;
    }
    linear_table[pos] = make_pair(key, value);
}

string lookup_linear(const string& key) {
    unsigned int pos = hash_word(key);
    while (!linear_table[pos].first.empty() && linear_table[pos].first != key) {
        if (linear_table[pos].first == key) {
            return linear_table[pos].second;
        }
        pos = (pos + 1) % M;
    }
    return "";
}

unordered_map<string, string> hash_table;

void initialize_map(int n) {
    hash_table.rehash(n);
}

void insert_map(const string& key, const string& value) {
    hash_table[key] = value;
}

string lookup_map(const string& key) {
    auto it = hash_table.find(key);
    if (it != hash_table.end()) {
        return it->second;
    }
    return "";
}

int main() {
    initialize();
    insert_cuckoo("name", "Alice");
    cout << "Cuckoo Lookup: " << lookup_cuckoo("name") << endl;
    insert_linear("name", "Bob");
    cout << "Linear Lookup: " << lookup_linear("name") << endl;
    insert_map("name", "Charlie");
    cout << "Unordered Map Lookup: " << lookup_map("name") << endl;
    return 0;
}
