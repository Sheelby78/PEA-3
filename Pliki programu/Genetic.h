#include <vector>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

class Genetic
{
private:

    struct element {
        int pathSize;
        vector<int> path;
    };

    int stop;
    int **matrix;
    int size;
    int populationSize;
    float crossRate, mutationRate;
    double t;

public:

    int path_distance(const vector<int>& path, int** Matrix);
    void CrossoverOX(vector<int> &parent1, vector<int> &parent2, vector<element> &population, int** Matrix);
    bool isInPath(int element, int begin, int end, vector<int> &path);
    int TSP(bool mutationType, int popSize, float crossRat, float mutationRat, double max_iterations, int** Matrix, int mainSize);
    void mutationSWAP(vector<element> &population, int** Matrix);
    void mutationINVERT(vector<element> &population, int** Matrix);
};