    #include <bits/stdc++.h>
    #include <vector>

    std::ifstream inputFile("feribot.in");
    std::ofstream outputFile("feribot.out");

    // Functia check verifica daca putem imparti elementele din arr
    // in k submultimi folosind o metoda Greedy
    bool check(const std::vector<long long>& arr, long long k, long long mid) {
        long long currK = 1;
        long long currSum = 0;

        // Iteram prin arr si verificam daca putem imparti
        // elementele in maxim k submultimi
        for (long long elem : arr) {
            // Daca un element este mai mare decat mid,
            // nu putem face o astfel de impartire
            if (elem > mid)
                return false;
            if (currSum + elem > mid) {
                currK++;
                currSum = 0;
            }
            currSum += elem;
        }

        // Daca numarul de submultimi este mai mic sau egal cu k, returnam true
        if (currK <= k)
            return true;
        // Altfel, returnam false
        return false;
    }

    int main() {
        // Verificam daca fisierul de intrare a fost deschis
        if (!inputFile.is_open()) {
            std::cerr << "Error opening \"feribot.in\"!" << std::endl;
            return 1;
        }

        // Citim datele de intrare
        long long n, k;
        inputFile >> n >> k;
        std::vector<long long> arr;

        for (long long i = 0; i < n; ++i) {
            long long elem;
            inputFile >> elem;
            arr.push_back(elem);
        }

        // Setam stanga (minSum) si dreapta (maxSum) pentru cautarea binara
        long long minSum = arr.front();
        long long maxSum = minSum;

        for (long long elem : arr) {
            if (minSum > elem)
                minSum = elem;
            maxSum += elem;
        }

        // Incepem cautarea binara
        long long lastMid = -1;
        while (minSum <= maxSum) {
            long long mid = (minSum + maxSum) / 2;
            if (check(arr, k, mid)) {
                // Daca putem imparti elementele in maxim k submultimi,
                // cautam o solutie mai buna
                lastMid = mid;
                maxSum = mid - 1;
            } else {
                // Daca nu putem, cautam o solutie mai mare
                minSum = mid + 1;
            }
        }

        // Verificam daca fisierul de iesire a fost deschis
        if (!outputFile.is_open()) {
            std::cerr << "Error opening \"feribot.out\"!" << std::endl;
            return 1;
        }

        outputFile << lastMid;

        // Inchidem fisierele
        inputFile.close();
        outputFile.close();
        return 0;
    }
