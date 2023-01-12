#include <ctime>
#include "Genetic.h"
#include "Timer.h"
#include <vector>

//funkcja liczaca dlugosc sciezki rozwiazania
int Genetic::path_distance(const vector<int>& path, int** Matrix){

  int dist = 0;
  for (int i = 0; i < path.size() - 1; i++) {
    dist += Matrix[path[i]][path[i+1]];
  }
  dist += Matrix[path[size-1]][path[0]];
  return dist;
}

// Krzyżowanie typu Order Crossover
void Genetic::CrossoverOX(vector<int> &parent1, vector<int> &parent2, vector<element> &population, int** Matrix) {
  
    vector<int> child1(size), child2(size);
    int begin, end;

    do {
        begin = rand() % size;
        end = rand() % size;
    } while (end <= begin );

    for (int i = begin; i <= end; i++) {
        child1[i] = parent1[i];
        child2[i] = parent2[i];
    }

    if (end + 1 == size){
        end = 0;
    }
    int temp = end + 1;
    int temp2 = end + 1;
    int tempp = end + 1;
    int tempp2 = end + 1;

    for (int i = 0; i < size; i++){
        //pierwszy potomek
        if (!isInPath(parent2[temp2], begin, end, child1)){
            child1[temp] = parent2[temp2];
        if (temp == child1.size() - 1){
                temp = 0;
        }else {
            temp++;
        }
        if (temp2 == parent2.size() - 1){
            temp2 = 0;
        }else {
            temp2++;
        }
        }else {
            if (temp2 == parent2.size() - 1){
                temp2 = 0;
            }
            else{
                temp2++;
            }
        }

        //drugi potomek
        if (!isInPath(parent1[tempp2], begin, end, child2)){
            child2[tempp] = parent1[tempp2];
        if (tempp == child2.size() - 1){
                tempp = 0;
        }else {
            tempp++;
        }
        if (tempp2 == parent1.size() - 1){
            tempp2 = 0;
        }else {
            tempp2++;
        }
        }else {
            if (tempp2 == parent1.size() - 1){
                tempp2 = 0;
            }
            else{
                tempp2++;
            }
        }
    }
    
    parent1.clear();
    parent2.clear();
    parent1 = child1;
    parent2 = child2;
}

//Sprawdzanie czy element jest w danej siezce
bool Genetic::isInPath(int element, int begin, int end, vector<int> &path) {
    for (int i = begin; i <= end; i++) {
        if (element == path[i])
            return true;
    }
    return false;
}

//Glowna funkcja algorytmu 
int Genetic::TSP(bool mutationType, int popSize, float crossRat, float mutationRat, double max_iterations, int** Matrix, int mainSize) {

    Timer test = *(new Timer());
    t = 0.0;

    size = mainSize;
    stop = max_iterations;
    populationSize = popSize;
    crossRate = crossRat;
    mutationRate = mutationRat;

    vector<element> population, newPopulation;
    vector<int> permutation;
    int tournamentSize = 5;
    int index;
    int result = INT32_MAX;

    //Tworzenie poczatkowej populacji
    for (int i = 0; i < size; i++) {
        permutation.push_back(i);
    }

    for (int i = 0; i < populationSize; i++) {
        random_shuffle(permutation.begin(), permutation.end());
        element e; 
        e.path = permutation;
        e.pathSize = path_distance(permutation, Matrix);
        population.push_back(e);
    }

    test.start();

    // Glowna petla programu
    while ((t/1000000) < stop) {
        newPopulation.clear();

       // Selekcja poprzez turniej
        for (int j = 0; j < populationSize; j++) {
            int v = INT32_MAX;
            int temp = 0;
            // Wybór najlepszego osobnika z turnieju
            for (int i = 0; i < tournamentSize; i++) {
                index = rand() % populationSize;
                
                if (population[index].pathSize < v) {
                    v = population[index].pathSize;
                    temp = index;
                }

            }
            newPopulation.push_back(population[temp]);
        }
        population = newPopulation;

        // Krzyżowanie
        for (int j = 0; j < (int) (crossRate * (float) populationSize); j += 2) {
            int parent1, parent2;
            do {
                parent1 = rand() % populationSize;
                parent2 = rand() % populationSize;
            } while (parent1==parent2);

            CrossoverOX(population[parent1].path, population[parent2].path, population, Matrix);
            population[parent1].pathSize = path_distance(population[parent1].path, Matrix);
            population[parent2].pathSize = path_distance(population[parent2].path, Matrix);
        }

        // Mutacje osobników
        if(mutationType){
            mutationSWAP(population, Matrix);
        } else{
            mutationINVERT(population, Matrix);
        }
        
        sort(population.begin(), population.end(),[](element s1, element s2) {return s1.pathSize < s2.pathSize;});
        if(population[0].pathSize < result){
            result = population[0].pathSize;
        }
        test.stop();
		t = test.timeCount();
    }
    return result;
}

//Mutacja typu SWAP
void Genetic::mutationSWAP(vector<element> &population, int** Matrix){
    int point1, point2; 
    for (int j = 0; j < (int) (mutationRate * (float) populationSize); j++) {
        int x = rand() % populationSize;
        do {
            point1 = rand() % size;
            point2 = rand() % size;
        } while (point1==point2);

        swap(population[x].path[point1], population[x].path[point2]);
        population[x].pathSize = path_distance(population[x].path, Matrix);
    }
}

//Mutacja typu INVERT
void Genetic::mutationINVERT(vector<element> &population, int** Matrix){
    int point1, point2; 
    for (int j = 0; j < (int) (mutationRate * (float) populationSize); j++) {
        int x = rand() % populationSize;
        do {
            point1 = rand() % size;
            point2 = rand() % size;
        } while (point1>=point2);

        int z = point2;
        for(int i = point1; i < z; i++){
            swap(population[x].path[i], population[x].path[z]);
            z--;
        }
        population[x].pathSize = path_distance(population[x].path, Matrix);
    }
}