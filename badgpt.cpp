#include <bits/stdc++.h>
#include <vector>
const long long MOD = 1e9 + 7;

std::ifstream inputFile("badgpt.in");
std::ofstream outputFile("badgpt.out");

// Functie pentru a inmultii doua matrice 2x2
void matrixMul(std::vector<std::vector<long long>>& m1,
     std::vector<std::vector<long long>>& m2) {
    long long a = (1LL * m1[0][0] * m2[0][0] % MOD +
         1LL * m1[0][1] * m2[1][0] % MOD) % MOD;
    long long b = (1LL * m1[0][0] * m2[0][1] % MOD +
         1LL * m1[0][1] * m2[1][1] % MOD) % MOD;
    long long c = (1LL * m1[1][0] * m2[0][0] % MOD +
         1LL * m1[1][1] * m2[1][0] % MOD) % MOD;
    long long d = (1LL * m1[1][0] * m2[0][1] % MOD +
         1LL * m1[1][1] * m2[1][1] % MOD) % MOD;

    m1[0][0] = a;
    m1[0][1] = b;
    m1[1][0] = c;
    m1[1][1] = d;
}

// Functie pentru a ridica matricea la puterea n
void matrixPow(std::vector<std::vector<long long>>& m, long long n) {
    // Matricea de identitate
    std::vector<std::vector<long long>> result = {{1, 0}, {0, 1}};

    // Inmultim matricea de baza cu ea insasi
    // de n ori, folosind exponentierea rapida
    while (n > 0) {
        if (n % 2 == 1)
            matrixMul(result, m);
        matrixMul(m, m);
        n /= 2;
    }

    m = result;
}

// Functie pentru a calcula n-lea numar Fibonacci
// folosind matricea de transformare
long long fibo(long long n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    std::vector<std::vector<long long>> m = {{1, 1}, {1, 0}};
    matrixPow(m, n - 1);
    return m[0][0];
}

int main() {
    // Verificam daca fisierul de intrare a fost deschis
    if (!inputFile.is_open()) {
        std::cerr << "Error opening \"badgpt.in\"!" << std::endl;
        return 1;
    }
    // Citim datele de intrare
    std::string s;
    inputFile >> s;

    // Iteram prin sirul de caractere
    long long res = 1;
    for (long long i = 0; i < s.size();) {
        // Salvam caracterul curent
        char currentChar = s[i];
        i++;

        if (currentChar == 'n' || currentChar == 'u') {
            // Calculam numarul de aparitii
            // ale caracterului curent
            long long size = 0;
            while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                size = size * 10 + (s[i] - '0');
                i++;
            }

            // Daca caracterul curent este 'n' sau 'u',
            // inmultim rezultatul cu numarul de aparitii
            // al caracterului curent

            res = (res * fibo(size + 1)) % MOD;
        } else {
            while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                // Daca caracterul curent nu este 'n' sau 'u',
                // cautam urmatorul caracter care nu este cifra
                i++;
            }
        }
    }

    // Verificam daca fisierul de iesire a fost deschis
    if (!outputFile.is_open()) {
        std::cerr << "Error opening \"badgpt.out\"!" << std::endl;
        return 1;
    }

    // Afisam rezultatul
    outputFile << res << std::endl;
}
