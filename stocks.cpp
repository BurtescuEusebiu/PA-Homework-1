#include <bits/stdc++.h>

// Definim structura pentru a stoca informatiile despre actiuni
typedef struct {
    int currVal;
    int minVal;
    int maxVal;
}stock;

std::ifstream inputFile("stocks.in");
std::ofstream outputFile("stocks.out");

int main() {
    // Verificam daca fisierul de intrare a fost deschis
    if (!inputFile.is_open()) {
        std::cerr << "Error opening \"stocks.in\"!" << std::endl;
        return 1;
    }
    // Citim datele de intrare
    int n, b, l, result = 0;
    inputFile >> n >> b >> l;
    std::vector<stock> arr(n);
    // Citim valorile curente, minime si maxime pentru fiecare actiune
    for (int i = 0; i < n; i++) {
        inputFile >> arr[i].currVal >> arr[i].minVal >> arr[i].maxVal;
    }

    // Cream matrixa dp pentru a stoca rezultatele intermediare
    // dp[i][j] va contine valoarea maxima a actiunilor cumparate
    // cu bugetul i si pierdrea j
    // Initializam dp cu -1
    // pentru a indica ca nu am gasit inca o solutie
    std::vector<std::vector<int>> dp(b + 1, std::vector<int>(l + 1, -1));
    // dp[0][0] = 0, adica nu am cumparat nimic
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = b ; j >= arr[i].currVal; --j) {
            for (int k = l ; k >= arr[i].currVal - arr[i].minVal; --k) {
                // Verificam daca putem cumpara actiunea i
                if (dp[j - arr[i].currVal][k - (arr[i].currVal -
                    arr[i].minVal)] != -1) {
                    // Daca putem, actualizam dp[j][k]
                    dp[j][k] = std::max(dp[j][k], dp[j - arr[i].currVal]
                        [k - (arr[i].currVal - arr[i].minVal)]
                    + (arr[i].maxVal - arr[i].currVal));
                }
            }
        }
    }

    // Cautam valoarea maxima in dp
    for (int i = 0; i <= b; ++i) {
        for (int j = 0; j <= l; ++j) {
            if (dp[i][j] != -1)
                result = std::max(result, dp[i][j]);
        }
    }

    outputFile << result << std::endl;
    inputFile.close();
    outputFile.close();
    return 0;
}
