// FILE.SORT.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>

bool createFileWithRandomNumbers(const std::string& fileF, const int numbersCount, const int maxNumberValue) {
    std::ofstream F(fileF);
    if (!F.is_open()) {
        return false;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, maxNumberValue);

    for (int k = 0; k < numbersCount; k++) {
        int number = dis(gen);
        F << number << ' ';
    }
    F.close();
    return true;
}

bool Razbienie(const std::string& fileF, const std::string& fileFa, const std::string& fileFb, int p) {
    std::ifstream F(fileF);
    if (!F.is_open()) {
        return false;
    }

    std::ofstream Fa(fileFa);
    std::ofstream Fb(fileFb);

    int num;
    while (F >> num) {
        Fa << num << ' ';
        for (int i = 1; i < p && F >> num; ++i) {
            Fa << num << ' ';
        }

        if (F >> num) {
            Fb << num << ' ';
            for (int i = 1; i < p && F >> num; ++i) {
                Fb << num << ' ';
            }
        }
    }

    F.close();
    Fa.close();
    Fb.close();

    
}


bool Merge(const std::string& fileFa, const std::string& fileFb, const std::string& fileFc) {
    std::ifstream Fa(fileFa);
    std::ifstream Fb(fileFb);

    if (!Fa.is_open() || !Fb.is_open()) {
        return false;
    }

    int num;
    std::vector<int> mergedNumbers;

    while (Fa >> num) {
        mergedNumbers.push_back(num);
    }

    while (Fb >> num) {
        mergedNumbers.push_back(num);
    }

    std::sort(mergedNumbers.begin(), mergedNumbers.end());

    std::ofstream Fc(fileFc);

    for (int i = 0; i < mergedNumbers.size(); ++i) {
        Fc << mergedNumbers[i] << ' ';
    }

    Fa.close();
    Fb.close();
    Fc.close();

    return true;
}


int main() {
    std::string fileF = "F.txt";
    std::string fileFa = "Fa.txt";
    std::string fileFb = "Fb.txt";
    std::string fileFc = "Fc.txt";

    int p = 1;

    if (createFileWithRandomNumbers(fileF, 10, 100)) {
        if (Razbienie(fileF, fileFa, fileFb, p)) {
            while (true) {
                Merge(fileFa, fileFb, fileFc);
                p *= 2;
                if (!Razbienie(fileFc, fileFa, fileFb, p)) {
                    break;
                }
            }

            std::cout << "Files created, merged and sorted successfully." << std::endl;
            return 0;
        }
    }
}
