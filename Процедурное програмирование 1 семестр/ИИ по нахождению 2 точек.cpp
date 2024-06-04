#include <iostream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// Функция для вычисления значения целевой функции
int targetFunction(int x, int y) {
    return x * x + y * y - x * y + x + y;
}

// Структура, представляющая особь в популяции
struct Individual {
    int x;
    int y;
    int fitness;

    // Конструктор для инициализации особи с заданными значениями x и y
    Individual(int x, int y) {
        this->x = x;
        this->y = y;
        this->fitness = targetFunction(x, y); // Оценка приспособленности (значение целевой функции)
    }
};

// Инициализация начальной популяции случайными особями
vector<Individual> initializePopulation(int populationSize, int minX, int maxX, int minY, int maxY) {
    vector<Individual> population;

    for (int i = 0; i < populationSize; i++) {
        // Генерация случайных значений x и y в заданных границах
        int x = rand() % (maxX - minX + 1) + minX;
        int y = rand() % (maxY - minY + 1) + minY;

        // Создание и добавление особи в популяцию
        population.push_back(Individual(x, y));
    }

    return population;
}

// Выбор пары родителей из популяции случайным образом
pair<Individual, Individual> selection(vector<Individual>& population) {
    int parent1 = rand() % population.size();
    int parent2 = rand() % population.size();

    return make_pair(population[parent1], population[parent2]);
}

// Скрещивание двух родителей с возможной мутацией
Individual crossover(const Individual& parent1, const Individual& parent2, int minX, int maxX, int minY, int maxY, double mutationRate) {
    int x = (parent1.x + parent2.x) / 2;
    int y = (parent1.y + parent2.y) / 2;

    // Мутация: с вероятностью mutationRate, добавляем случайное смещение
    if (rand() % 100 < mutationRate) {
        x += rand() % (maxX - minX + 1) + minX;
        y += rand() % (maxY - minY + 1) + minY;
    }

    // Создание и возвращение потомка
    return Individual(x, y);
}

// Эволюция популяции: создание новой популяции на основе существующей
void evolvePopulation(vector<Individual>& population, int minX, int maxX, int minY, int maxY, double mutationRate) {
    vector<Individual> newPopulation;

    // Для каждой особи в текущей популяции
    for (int i = 0; i < population.size(); i++) {
        // Выбор пары родителей
        pair<Individual, Individual> parents = selection(population);

        // Создание потомка и добавление его в новую популяцию
        Individual child = crossover(parents.first, parents.second, minX, maxX, minY, maxY, mutationRate);
        newPopulation.push_back(child);
    }

    // Замена старой популяции новой
    population = newPopulation;
}

// Поиск экстремума в заданных границах с использованием генетического алгоритма
Individual findExtremum(int populationSize, int generations, int minX, int maxX, int minY, int maxY, double mutationRate) {
    srand(time(0)); // Инициализация генератора случайных чисел на основе времени

    // Инициализация начальной популяции
    vector<Individual> population = initializePopulation(populationSize, minX, maxX, minY, maxY);

    // Итерации генетического алгоритма
    for (int i = 0; i < generations; i++) {
        evolvePopulation(population, minX, maxX, minY, maxY, mutationRate); // Эволюция популяции
    }

    // Поиск лучшей особи в популяции
    Individual bestIndividual = population[0];
    for (int i = 1; i < population.size(); i++) {
        if (population[i].fitness > bestIndividual.fitness) {
            bestIndividual = population[i];
        }
    }

    return bestIndividual;
}

// Точка входа в программу
int main() {
    setlocale(LC_ALL, "RU");
    int populationSize = 5; // Размер популяции
    int generations = 5; // Количество поколений
    int minX = -5; // Нижняя граница для x
    int maxX = 5; // Верхняя граница для x
    int minY = -5; // Нижняя граница для y
    int maxY = 5; // Верхняя граница для y
    double mutationRate = 5.0; // Вероятность мутации в процентах

        // Поиск экстремума с использованием генетического алгоритма
        Individual bestIndividual = findExtremum(populationSize, generations, minX, maxX, minY, maxY, mutationRate);

    // Вывод результата
    cout << "Точки экстремума: x = " << bestIndividual.x << ", y = " << bestIndividual.y;

    return 0; // Успешное завершение программы
}