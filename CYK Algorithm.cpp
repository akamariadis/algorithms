#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>

using namespace std;

typedef unordered_map<string, productionset> Grammar;
typedef set<string> productionset;

bool cykAlgorithm(const Grammar& grammar, const string& startSymbol, const string& input) {
    int n = input.size();
    if (n == 0) return false;
    vector<vector<set<string>>> dp(n, vector<set<string>>(n));
    for (int i = 0; i < n; i++) {
        string symbol(1, input[i]);
        for (const auto& rule : grammar) {
            if (rule.second.count(symbol)) {
                dp[i][i].insert(rule.first);
            }
        }
    }
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            for (int k = i; k < j; k++) {
                for (const auto& rule : grammar) {
                    for (const string& production : rule.second) {
                        if (production.size() == 2) {
                            string B(1, production[0]);
                            string C(1, production[1]);
                            if (dp[i][k].count(B) && dp[k + 1][j].count(C)) dp[i][j].insert(rule.first);   
                        }
                    }
                }
            }
        }
    }
    return dp[0][n - 1].count(startSymbol) > 0;
}

int main() {
    Grammar grammar = {
        {"S", {"AB", "BC"}},
        {"A", {"BA", "a"}},
        {"B", {"CC", "b"}},
        {"C", {"AB", "a"}}
    };
    string startSymbol = "S";
    string input;
    cin >> input;
    if (cykAlgorithm(grammar, startSymbol, input)) {
        cout << "Η αλυσίδα \"" << input << "\" μπορεί να παραχθεί από τη γραμματική." << endl;
    } else {
        cout << "Η αλυσίδα \"" << input << "\" δεν μπορεί να παραχθεί από τη γραμματική." << endl;
    }
    return 0;
}
