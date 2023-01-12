#include <iostream>
#include <chrono>
#include <thread>
#include "AdjacencyMatrix.h"
#include "Timer.h"
#include "Genetic.h"

using namespace std;

void AlgorithmMenu(AdjacencyMatrix mat);
void mutationShow();

int populationSize = 5000;
float crossRate = 0.8, mutationRate = 0.01;
double exeTime = 5;
bool mutationType = true;

//Głowne menu programu
int main(int, char**) {

    AdjacencyMatrix mat = *(new AdjacencyMatrix());
    srand(time(NULL));
    bool koniec = false;
    char wybor;

    system("cls");

    while (!koniec) {

        system("cls");
        cout << " ============MENU============ " << endl;
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "1.  Wczytaj dane z pliku" << endl;
        cout << "2.  Automatyczne generowanie grafu" << endl;
        cout << "x.  Zamkniecie programu " << endl;
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "Wybor: ";
        cin >> wybor;

        switch (wybor) {
        case '1': {
            cout << "Podaj nazwe pliku do wczytania danych: ";
            string name;
            cin >> name;
            if (!mat.readMatrix(name)) {
                cout << endl << "Blad odczytu pliku" << endl;
            }
            else {
                cout << endl << "Pomyslnie wczytano plik" << endl;
                system("cls");
                AlgorithmMenu(mat);
            }

            break;
        }
        case '2': {
            cout << "Podaj liczbe wierzcholkow: ";
            int N;
            cin >> N;
            mat.generateMatrix(N);
            cout << endl << "Pomyslnie wygenerowano graf" << endl;
            system("cls");
            AlgorithmMenu(mat);
            break;
        }
        case 'x':;	koniec = true; break;
        default: {
            cout << endl << "POMYLKA!" << endl;
            break;
        }
        }
    }
}

//Menu wyboru algorytmu i ustawiania roznych zmiennych 
void AlgorithmMenu(AdjacencyMatrix mat) {
    Timer test = *(new Timer());
    bool koniec = false;
    char wybor;

    while (!koniec) {
        cout << " ============MENU============ " << endl;
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "Ustawiony czas wykonywania algorytmow: " << exeTime << " Sekund" << endl;
        cout << "Ustawiona wielkosc populacji: " << populationSize << endl;
        cout << "Ustawiony wspolczynnik krzyzowania: " << crossRate << endl;
        cout << "Ustawiony wspolczynnik mutacji: " << mutationRate << endl;
        cout << "Ustawiony typ mutacji: "; mutationShow();
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "1.  Algorytn Genetyczny (GA)" << endl;
        cout << "2.  Wyswietl graf" << endl;
        cout << "3.  Ustaw czas wykonywania" << endl;
        cout << "4.  Ustaw wielkosc populacji" << endl;
        cout << "5.  Ustaw wspolczynnik krzyzowania" << endl;
        cout << "6.  Ustaw wspolczynnik mutacji" << endl;
        cout << "7.  Zmien typ mutacji" << endl;
        cout << "x.  Powrot" << endl;
        cout << "-----------------------------" << endl;
        cout << "-----------------------------" << endl;
        cout << "Wybor: ";
        cin >> wybor;


        switch (wybor) {
        case '1': {
            system("cls");
            Genetic gn = *(new Genetic());
            cout << "ALGORYTM GENETYCZNY" << endl << endl;
            test.start();
            cout << "=====> " << gn.TSP(mutationType, populationSize, crossRate, mutationRate, exeTime, mat.getMatrix(), mat.getSize()) << " <=====" << endl;
            test.stop();
            cout << endl;
            cout << test.timeCount()/1000000  << " Seconds";
            cout << endl << endl;
            break;
        }
        case '2': {
            system("cls");
            mat.show();
            cout << endl << endl;
            break;
        }
         case '3': {
            system("cls");
            cout << "Podaj czas wykonywania algorytmu w sekundach: ";
            double n;
            cin >> n;
            exeTime = n;
            system("cls");
            break;
        }
        case '4': {
            system("cls");
            cout << "Podaj wielkosc populacji: ";
            int n;
            cin >> n;
            populationSize = n;
            break;
        }
         case '5': {
            system("cls");
            cout << "Podaj wspolczynnik krzyzowania: ";
            float n;
            cin >> n;
            crossRate = n;
            break;
        }
        case '6': {
            system("cls");
            cout << "Podaj wspolczynnik mutacji: ";
            float n;
            cin >> n;
            mutationRate = n;
            break;
        }
        case '7': {
            system("cls");
            char wybor2;
            cout << "Wybierz typ sasiedztwa: " << endl;
            cout << "1.  SWAP" << endl;
            cout << "2.  INVERT" << endl;
            cout << "Wybor: ";
            cin >> wybor2;
            
            if(wybor2 == '1'){
                system("cls");
                cout << "Wybrano typ sasiedztwa: SWAP";
                mutationType = true;
            } else if(wybor2 == '2'){
                system("cls");
                cout << "Wybrano typ sasiedztwa: INVERT";
                mutationType = false;
            } else {
                system("cls");
                cout << "POMYLKA!";
            }
            cout << endl << endl;
            break;
        }
        case 'x':;	koniec = true; break;
        default: {
            cout << endl << "POMYLKA!" << endl;
            break;
        }
        }
    }
}

//Wyswietlanie typu mutacji 
void mutationShow(){
    if(mutationType){
        cout << "SWAP" << endl; 
    }
    else{
        cout << "INVERT" << endl; 
    }
}
