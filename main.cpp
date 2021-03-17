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
 *  V Compilator  V Linkuim source-file-urile                                                                  Toate Warning-urile V   V Output
 *  g++ main.cpp -I data/ data/reader_writter.cpp -I models/ models/answer.cpp -I models/ models/question.cpp -I ui/ ui/tui.cpp -Wall -o quizzes.exe
 */

#include "data/reader_writter.h"
#include "ui/tui.h"

int main() {
    std::cout << "Initializare...\n";
    Quiz quizzes[MAX_NUMBER_OF_CATEGORIES][MAX_NUMBER_OF_QUIZZES];
    int number_of_quizzes = 0;

    // Citire quiz-uri din fisier
    number_of_quizzes = read(quizzes);

    if (number_of_quizzes == -1) {
        std::cout << "Whoops! Ceva nu a mers bine! (Exista fisierele in folderul quiz_uri?)\n";
        return EXIT_FAILURE;
    }

    /* -- Initializat -- */

    ui::reset();
    ui::put_header();
    ui::welcome();
    ui::put_footer();

    char verification_code[MAX_SAFE_INPUT];
    if (!ui::input(verification_code)) {
        return EXIT_SUCCESS;
    }

    if (strlen(verification_code) == 0) {
        strcpy(verification_code, "<FARA>");
    };

    while (true) {
        ui::main_menu();

        char option[MAX_SAFE_INPUT];
        if (!ui::input(option)) {
            return EXIT_SUCCESS;
        }

        int category = 0;

        switch (atoi(option)) {
            case 1:
                category = ui::select_quiz_category();
                if (category < 0 || category > NUMBER_OF_TYPES) {
                    break;
                }
                // TODO: Alege testul efectiv
                break;
            case 2:
                category = ui::select_quiz_category();
                if (category < 0 || category > NUMBER_OF_TYPES) {
                    break;
                }
                // TODO: Alege testul efectiv
                break;
            case 3:
                category = ui::select_quiz_category();
                if (category < 0 || category > NUMBER_OF_TYPES) {
                    break;
                }
                // TODO: Ecran pentru creeatie
                break;
            case 4:
                category = ui::select_quiz_category();
                if (category < 0 || category > NUMBER_OF_TYPES) {
                    break;
                }
                // TODO: Alege testul efectiv
                break;
            default:
                ui::reset();
                std::cout << "Atentie! Optiune invalida...\n";
                Sleep(1000);
        }

        if (category == -1) {
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}
