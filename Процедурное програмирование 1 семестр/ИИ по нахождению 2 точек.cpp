#include <iostream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// ������� ��� ���������� �������� ������� �������
int targetFunction(int x, int y) {
    return x * x + y * y - x * y + x + y;
}

// ���������, �������������� ����� � ���������
struct Individual {
    int x;
    int y;
    int fitness;

    // ����������� ��� ������������� ����� � ��������� ���������� x � y
    Individual(int x, int y) {
        this->x = x;
        this->y = y;
        this->fitness = targetFunction(x, y); // ������ ����������������� (�������� ������� �������)
    }
};

// ������������� ��������� ��������� ���������� �������
vector<Individual> initializePopulation(int populationSize, int minX, int maxX, int minY, int maxY) {
    vector<Individual> population;

    for (int i = 0; i < populationSize; i++) {
        // ��������� ��������� �������� x � y � �������� ��������
        int x = rand() % (maxX - minX + 1) + minX;
        int y = rand() % (maxY - minY + 1) + minY;

        // �������� � ���������� ����� � ���������
        population.push_back(Individual(x, y));
    }

    return population;
}

// ����� ���� ��������� �� ��������� ��������� �������
pair<Individual, Individual> selection(vector<Individual>& population) {
    int parent1 = rand() % population.size();
    int parent2 = rand() % population.size();

    return make_pair(population[parent1], population[parent2]);
}

// ����������� ���� ��������� � ��������� ��������
Individual crossover(const Individual& parent1, const Individual& parent2, int minX, int maxX, int minY, int maxY, double mutationRate) {
    int x = (parent1.x + parent2.x) / 2;
    int y = (parent1.y + parent2.y) / 2;

    // �������: � ������������ mutationRate, ��������� ��������� ��������
    if (rand() % 100 < mutationRate) {
        x += rand() % (maxX - minX + 1) + minX;
        y += rand() % (maxY - minY + 1) + minY;
    }

    // �������� � ����������� �������
    return Individual(x, y);
}

// �������� ���������: �������� ����� ��������� �� ������ ������������
void evolvePopulation(vector<Individual>& population, int minX, int maxX, int minY, int maxY, double mutationRate) {
    vector<Individual> newPopulation;

    // ��� ������ ����� � ������� ���������
    for (int i = 0; i < population.size(); i++) {
        // ����� ���� ���������
        pair<Individual, Individual> parents = selection(population);

        // �������� ������� � ���������� ��� � ����� ���������
        Individual child = crossover(parents.first, parents.second, minX, maxX, minY, maxY, mutationRate);
        newPopulation.push_back(child);
    }

    // ������ ������ ��������� �����
    population = newPopulation;
}

// ����� ���������� � �������� �������� � �������������� ������������� ���������
Individual findExtremum(int populationSize, int generations, int minX, int maxX, int minY, int maxY, double mutationRate) {
    srand(time(0)); // ������������� ���������� ��������� ����� �� ������ �������

    // ������������� ��������� ���������
    vector<Individual> population = initializePopulation(populationSize, minX, maxX, minY, maxY);

    // �������� ������������� ���������
    for (int i = 0; i < generations; i++) {
        evolvePopulation(population, minX, maxX, minY, maxY, mutationRate); // �������� ���������
    }

    // ����� ������ ����� � ���������
    Individual bestIndividual = population[0];
    for (int i = 1; i < population.size(); i++) {
        if (population[i].fitness > bestIndividual.fitness) {
            bestIndividual = population[i];
        }
    }

    return bestIndividual;
}

// ����� ����� � ���������
int main() {
    setlocale(LC_ALL, "RU");
    int populationSize = 5; // ������ ���������
    int generations = 5; // ���������� ���������
    int minX = -5; // ������ ������� ��� x
    int maxX = 5; // ������� ������� ��� x
    int minY = -5; // ������ ������� ��� y
    int maxY = 5; // ������� ������� ��� y
    double mutationRate = 5.0; // ����������� ������� � ���������

        // ����� ���������� � �������������� ������������� ���������
        Individual bestIndividual = findExtremum(populationSize, generations, minX, maxX, minY, maxY, mutationRate);

    // ����� ����������
    cout << "����� ����������: x = " << bestIndividual.x << ", y = " << bestIndividual.y;

    return 0; // �������� ���������� ���������
}