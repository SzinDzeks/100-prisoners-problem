// Prisoners2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>     /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)y, (SHORT)x };
    SetConsoleCursorPosition(hOut, coord);
}

int getRandomNumber(int x, int y) {
    return rand() % y + x;
}
int main()
{
    srand(time(NULL));
    long maxRuns, freq, runsWon = 0;

    system("cls");
    cout << "Input number of simulations to run: ";
    cin >> maxRuns;

    system("cls");
    cout << "Input frequency of data update: ";
    cin >> freq;

    system("cls");
    setCursorPosition(0, 0);
    cout << "100 Prisoners Problem Simulation";
    setCursorPosition(2, 0);
    cout << "Simulation number: b.d.";
    setCursorPosition(3, 0);
    cout << "Simulations won: b.d.";
    setCursorPosition(4, 0);
    cout << "Wins percentage: b.d.";
    setCursorPosition(6, 0);
    cout << "Execution time per 10k sims: b.d.";
    setCursorPosition(7, 0);
    cout << "Execution time per 100k sims: b.d.";

    auto timeTenK = high_resolution_clock::now();
    auto timeHunK = high_resolution_clock::now();

    for (long currentRuns = 0; currentRuns < maxRuns; currentRuns++) {
        if (currentRuns % freq == 0) {
            setCursorPosition(2, 19);
            cout << 1 + currentRuns << "    ";
            setCursorPosition(3, 17);
            cout << runsWon << "     ";
            setCursorPosition(4, 17);
            if (currentRuns != 0) {
                double percentWon = (1.0 * runsWon) / (1.0 * currentRuns) * 100;
                cout << percentWon << "%    ";
            }
        }
        if (currentRuns % 10000 == 0) {
            auto now = high_resolution_clock::now();
            auto durTen = duration_cast<milliseconds> (now - timeTenK);
            setCursorPosition(6, 29);
            cout << durTen.count() << "ms";
            timeTenK = now;
            if (currentRuns % 100000 == 0) {
                auto durHun = duration_cast<milliseconds>(now - timeHunK);
                setCursorPosition(7, 30);
                cout << durHun.count() << "ms";
                setCursorPosition(8, 0);
                timeHunK = now;
            }
            
        }

        int boxes[100];
        for (int j = 0; j < 100; j++) {
            boxes[j] = j;
        }
        random_shuffle(begin(boxes), end(boxes));

        //Wiezniowie grają
        bool allLose = false;
        for (int i = 0; i < 100; i++) {
            int nextBox = i;
            bool failed = true;

            for (int j = 0; j < 50; j++) {
                if (boxes[nextBox] == i) {
                    failed = false;
                    break;
                } 
                else {
                    nextBox = boxes[nextBox];
                }

            }
            
            if (failed) {
                allLose = true;
                break;
            }
        }
        if (!allLose) {
            runsWon++;
        }
    }
}




// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
