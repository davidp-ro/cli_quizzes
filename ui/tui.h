#ifndef QUIZ_CLI_TUI_H
#define QUIZ_CLI_TUI_H

#include <iostream>
#include <windows.h>
#include <ctime>
#include "../models/quiz.h"
#include "../models/user.h"

const int MAX_SAFE_INPUT = 256;

namespace ui {

/* ===============================[ Constante ]============================== */

const char header[] = "==========================[ QuizCLI - David Pescariu ]==========================";
const char separator[] = "--------------------------------------------------------------------------------";
const char footer[] = "=============[Pentru a iesi sau merge inapoi, introduceti q oricand]============";

const char bun_venit[][75] = {
    "______                               _ _     _ \n",
    "| ___ \\                             (_) |   | |\n",
    "| |_/ /_   _ _ __   __   _____ _ __  _| |_  | |\n",
    "| ___ \\ | | | '_ \\  \\ \\ / / _ \\ '_ \\| | __| | |\n",
    "| |_/ / |_| | | | |  \\ V /  __/ | | | | |_  |_|\n",
    "\\____/ \\__,_|_| |_|   \\_/ \\___|_| |_|_|\\__| (_)\n"
};

const char categorii_quiz[][30] = {"Matematica", "Romana", "Geografie", "Biologie"};

/* ================================[ Functii ]=============================== */

/**
 * @brief Wrapper pentru citire
 * 
 * @param s string-ul unde va fi stocat ce e citit
 * @return 0 - User-ul vrea sa iasa | 1 - Input normal
 */
int input(char s[]);

/* ===============================[ Screens ]================================ */

/**
 * @brief Afiseaza (+input) meniul pentru selectarea categoriei
 * 
 * @param title titlul afisat pe ecran
 * @return int - optiunea selectata sau -1 pentru iesire
 */
int select_quiz_category(const char * title);

/**
 * @brief Afiseaza (+input) meniul pentru selectarea quiz-ului
 * 
 * @param title titlul afisat pe ecran
 * @param quizzes array-ul in care sunt stocate quiz-urile
 * @param type categoria quiz-ului
 * @return int - -1: iesire | -2: optiune invalida | index-ul quiz-ului selectat
 */
int select_quiz(const char * title, Quiz quizzes[][MAX_NUMBER_OF_QUIZZES], int type);

/**
 * @brief Afiseaza intrebarea curenta dintr-un quiz
 * 
 * @param quiz Quiz-ul selectat
 * @param user Utilizatorul
 * @param question_index index-ul intrebarii curente
 * @param view_mode true: Modul de vizualizare | false: Modul de testare
 */
void show_quiz_question(Quiz quiz, User user, unsigned short question_index, bool view_mode);

int create_question(Question &q, unsigned short question_number);

int create_answer(Answer &a, unsigned short answer_number);

/**
 * @brief Afiseaza meniul 
 */
void main_menu(User user);

/**
 * @brief Afiseaza mesajul de inceput
 */
void welcome();

/* ===============================[ Helpers ]================================ */

/**
 * @brief Reprezentarea date time ca string (padded)
 * 
 * @param s hh:mm dd:MM:yyyy
 */
void get_time_and_date(char s[]);

/**
 * @brief Afiseaza header-ul 
 */
void put_header();

/**
 * @brief Afiseaza footer-ul 
 */
void put_footer();

/**
 * @brief Face clear la ecran fara system("cls") (Windows only!)
 * 
 * Articol: https://www.cplusplus.com/articles/4z18T05o/
 */
void reset();

}  // namespace ui

#endif