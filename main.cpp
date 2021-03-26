/**
 * @author David Pescariu
 * @brief Proiect Struct-uri
 * @date Mar 2021
 * 
 * @copyright The Unlicense - Public Domain
 * 
 * Format fisier quiz
 * ---------------------
 *  Fiecare quiz incepe cu BEGIN_QUIZ
 *  Pe urmatoarea linie va fi numarul de intrebari (n)
 *  Pe urmatoarele n linii vor fi intrebarile efective cu urmatorul format (unde rasp. corect e marcat cu !):
 *      Subiect intrebare, nr_raspunsuri, raspuns1, !raspuns2, raspuns3, raspuns4
 *  Fiecare quiz se termina cu END_QUIZ
 * 
 * Compilare / Compile
 * ---------------------
 *  V Compilator  V Linkuim source-file-urile                                                                                                                                                      Toate Warning-urile V   V Output
 *  g++ main.cpp -I data/ data/reader_writter.cpp -I models/ models/answer.cpp -I models/ models/question.cpp -I ui/ ui/tui.cpp -I services/ services/quiz_service.cpp -I services/ services/statistics_service.cpp -Wall -o quizzes.exe
 */

#include "data/reader_writter.h"
#include "services/quiz_service.h"
#include "services/statistics_service.h"
#include "ui/tui.h"

/**
 * @brief Verifica daca cateogria e valida
 * 
 * @param category categoria de verificat
 * @return true / false 
 */
inline bool is_valid_category(int category);

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
                // Modul de test pentru quiz
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
                // Doar vizualizarea quiz-urilor
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
                // Adaugare quiz
                category = ui::select_quiz_category("Selectati categoria in care doriti sa adaugati quiz-ul");
                if (is_valid_category(category)) {
                    create_quiz(quizzes, category);
                }
                break;
            case 4:
                // Stergere quiz
                category = ui::select_quiz_category("Stergeti un quiz");
                if (is_valid_category(category)) {
                    char select_title[] = "Selectati un quiz din categoria ";
                    strcat(select_title, ui::categorii_quiz[category]);

                    selection = ui::select_quiz(select_title, quizzes, category);

                    for (unsigned short quiz_index = selection;
                         quiz_index < (MAX_NUMBER_OF_QUIZZES - 1);
                         ++quiz_index) {
                        quizzes[category][quiz_index] = quizzes[category][quiz_index + 1];
                    }

                    write(quizzes);
                }
                break;
            case 5:
                // Leaderboard local
                ui::reset();
                std::cout << "Se incarca...\n";

                PreviousResult results[MAX_PREVIOUS_RESULTS];
                unsigned short number_of_results;

                if (read_statistics(results, number_of_results) == -1) {
                    ui::reset();
                    std::cout << "Whoops! Ceva nu a mers bine! (Nu s-a putut citi statistics_service.data)\n";
                    return EXIT_FAILURE;
                };

                if (number_of_results == 0) {
                    ui::reset();
                    std::cout << "Nu sunt disponibile rapoarte anterioare\n";
                    Sleep(1500);
                    break;
                }

                if (ui::show_reports(results, number_of_results) == 99) {
                    delete_statistics();
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

inline bool is_valid_category(int category) {
    return (category >= 0 && category < NUMBER_OF_TYPES);
}
