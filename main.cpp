/**
 * @author David Pescariu
 * @brief Proiect Struct-uri
 * @date Mar 2021
 * 
 * @copyright The Unlicense - Public Domain
 * 
 * Format quizzes.data
 *  Fiecare quiz incepe cu BEGIN_QUIZ
 *  Pe urmatoarea linie va fi numarul de intrebari (n)
 *  Pe urmatoarele n linii vor fi intrebarile efective cu urmatorul format (unde rasp. corect e marcat cu !):
 *      Subiect intrebare, nr_raspunsuri, raspuns1, !raspuns2, raspuns3, raspuns4
 *  Fiecare quiz se termina cu END_QUIZ
 * 
 * Compile:
 *  V Compilator  V Linkuim source-file-urile                                                Toate Warning-urile V   V Output
 *  g++ main.cpp -I data/ data/reader_writter.cpp -I models/ models/answer.cpp -I models/ models/question.cpp -Wall -o quizzes.exe
 */

#include "data/reader_writter.h"

int main() {
    std::cout << "==[ START ]==\n";
    Quiz quizzes[32];
    int number_of_quizzes = 0;

    // Citire quiz-uri din fisier
    number_of_quizzes = read(quizzes);

    if (number_of_quizzes == -1) {
        std::cout << "Whoops! Ceva nu a mers bine!\n";
        return EXIT_FAILURE;
    }

    // std::cout << "\n" << quizzes[0].questions[0].answers[0].name;
    // std::cout << "\n" << quizzes[1].questions[0].subject;

    write(quizzes, number_of_quizzes);

    std::cout << "==[ EXIT ]==\n";
    return EXIT_SUCCESS;
}
