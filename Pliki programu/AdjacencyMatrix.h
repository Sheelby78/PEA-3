#include <iostream>

using namespace std;

class AdjacencyMatrix{
    private:
        int **Matrix;
        int size;

    public:
        AdjacencyMatrix();
        ~AdjacencyMatrix();
        int** getMatrix();
        int getSize();
        bool readMatrix(string name);
        void show();
        void generateMatrix(int mainSize);
};