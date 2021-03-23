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
 *  V Compilator  V Linkuim source-file-urile                                                                                                Toate Warning-urile V   V Output
 *  g++ main.cpp -I data/ data/reader_writter.cpp -I models/ models/answer.cpp -I models/ models/question.cpp -I ui/ ui/tui.cpp -I services/ services/quiz_service.cpp -Wall -o quizzes.exe
 */

#include "data/reader_writter.h"
#include "services/quiz_service.h"
#include "ui/tui.h"

bool is_valid_category(int category);

int main() {
    std::cout << "Initializare...\n";
    Quiz quizzes[MAX_NUMBER_OF_CATEGORIES][MAX_NUMBER_OF_QUIZZES];
    User user;

    if (read(quizzes) == -1) {
        std::cout << "Whoops! Ceva nu a mers bine! (Exista fisierele in folderul quiz_uri?)\n";
        return EXIT_FAILURE;
    }

    /* -- Initializat -- */

    ui::reset();
    ui::welcome();

    if (!ui::input(user.verification_code)) {
        return EXIT_SUCCESS;
    }

    if (strlen(user.verification_code) == 0) {
        strcpy(user.verification_code, "<FARA>");
    };

    std::cout << ui::separator 
              << "\nIntroduceti numele dumneavoastra\n";
    if (!ui::input(user.name)) {
        return EXIT_SUCCESS;
    }

    /* -- Meniu -- */

    while (true) {
        ui::main_menu(user);

        char option[MAX_SAFE_INPUT];
        if (!ui::input(option)) {
            return EXIT_SUCCESS;
        }

        int category = 0;
        int selection = 0;

        switch (atoi(option)) {
            case 1:
                category = ui::select_quiz_category("Inceperea unui nou Quiz");
                if (is_valid_category(category)) {
                    char select_title[] = "Selectati un quiz din categoria ";
                    strcat(select_title, ui::categorii_quiz[category]);

                    selection = ui::select_quiz(select_title, quizzes, category);

                    if (selection == -1) {
                        break;
                    }

                    take_quiz(quizzes[category][selection], user);
                }
                break;
            case 2:
                category = ui::select_quiz_category("Quiz-uri disponibile");
                if (is_valid_category(category)) {
                    char select_title[] = "Selectati un quiz din categoria ";
                    strcat(select_title, ui::categorii_quiz[category]);

                    selection = ui::select_quiz(select_title, quizzes, category);

                    if (selection == -1) {
                        break;
                    }

                    view_quiz(quizzes[category][selection], user);
                }
                break;
            case 3:
                // TODO: Ecran pentru creeatie
                break;
            case 4:
                category = ui::select_quiz_category("Stergeti un quiz");
                if (is_valid_category(category)) {
                    selection = ui::select_quiz("", quizzes, category);
                }
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

bool is_valid_category(int category) {
    return (category >= 0 && category < NUMBER_OF_TYPES);
}
