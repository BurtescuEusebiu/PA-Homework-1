#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <set>

const long long MOD = 1e9 + 7;

std::ifstream inputFile("crypto.in");
std::ofstream outputFile("crypto.out");

int main() {
    // Verificam daca fisierul de intrare a fost deschis
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening \"crypto.in\"!" << std::endl;
        return 1;
    }

    // Citim datele de intrare
    long long n, l;

    inputFile >> n >> l;

    std::string k, s;

    inputFile >> k >> s;

    // Declaram matricea dp
    // dp[i][j] = numarul de moduri de a forma un prefix de lungime j
    // din primele i caractere ale lui k
    std::vector<std::vector<long long>> dp(n+1, std::vector<long long>(l+1, 0));
    dp[0][0] = 1;

    // Set pentru a retine literele unice din s
    std::set<char> letters;
    for (long long i = 0; i < s.size(); i++) {
        letters.insert(s[i]);
    }

    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j <= l; j++) {
            // Daca dp[i][j] este 0, continuam
            if (dp[i][j] == 0) continue;

            // Daca k[i] este un caracter cunoscut
            if (k[i] != '?') {
                // Adaugam la dp[i+1][j] numarul curent de moduri
                dp[i+1][j] = (dp[i+1][j] + dp[i][j])%MOD;

                // Daca k[i] este un caracter din s, adaugam la dp[i+1][j+1]
                // numarul curent de moduri
                if (k[i] == s[j]) {
                    dp[i+1][j+1] = (dp[i+1][j+1] + dp[i][j])%MOD;
                }
            } else {
                // Daca k[i] este '?'
                for (char c : letters) {
                    // Adaugam la dp[i+1][j] numarul curent de moduri
                    // pentru fiecare litera posibila
                    dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % MOD;

                    // Daca c este un caracter din s, adaugam la dp[i+1][j+1]
                    // numarul curent de moduri
                    if (j < l && c == s[j]) {
                        dp[i+1][j+1] = (dp[i+1][j+1] + dp[i][j]) % MOD;
                    }
                }
            }
        }
    }


    // Verificam daca fisierul de iesire a fost deschis
    if (!outputFile.is_open()) {
        std::cerr <<"Error opening \"crypto.out\"!"<< std::endl;
        return 1;
    }

    outputFile << dp[n][l] << std::endl;
    return 0;
}
