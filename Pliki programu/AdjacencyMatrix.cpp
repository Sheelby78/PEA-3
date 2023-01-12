#include "AdjacencyMatrix.h"
#include <fstream>

//konstruktor
AdjacencyMatrix::AdjacencyMatrix(){
    size = 0;
}

//destruktor
AdjacencyMatrix::~AdjacencyMatrix(){
    for (int i = 0; i < size; i++){
        delete[] Matrix[i];
    }
    delete[] Matrix;
    size = 0;
}

//wczytywanie danych z pliku tesktowego
bool AdjacencyMatrix::readMatrix(string name){

    string name3 = ".txt";
	ifstream read(name + name3);

	if (!read.good()){
		return false;
	}

	read >> size;
    Matrix = new int *[size];

	for (int i = 0; i < size; i++){
		Matrix[i] = new int[size];
	}

	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
            read >> Matrix[i][j];
        }
	}
    
    read.close();
    return true;
}

//zwracanie wielkosci macierzy
int AdjacencyMatrix::getSize(){

    return size;
}

//zwracanie macierzy
int** AdjacencyMatrix::getMatrix(){

    return Matrix;
}

//wyswietlanie zawartosci macierzy
void AdjacencyMatrix::show(){
    cout<<endl;
    for(int i=0;i<size;i++){
        cout<<"{";
        for(int j=0;j<size;j++){
            if(j==size-1){
                cout<<Matrix[i][j];
                continue;
            }
            cout<<Matrix[i][j]<<", ";
        }
        cout<<"}"<<endl;
    }
}

//automatyczne generowanie macierzy
void AdjacencyMatrix::generateMatrix(int mainSize){

    size = mainSize;
    Matrix = new int *[size];

	for (int i = 0; i < size; i++){
		Matrix[i] = new int[size];

        for(int j=0; j<size; j++){
            if(j==i){
                Matrix[i][j]=0;
                continue;
            }
            Matrix[i][j] = 1 + (rand() % (100));
        }
    }
}
