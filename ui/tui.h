#ifndef QUIZ_CLI_TUI_H
#define QUIZ_CLI_TUI_H

#include <iostream>
#include <windows.h>
#include "../models/quiz.h"

const int MAX_SAFE_INPUT = 256;

namespace ui {

/* ===============================[ Constante ]============================== */

const char header[] = "==========================[ QuizCLI - David Pescariu ]==========================";
const char separator[] = "--------------------------------------------------------------------------------";
const char footer[] = "=====================[Pentru a iesi, introduceti q oricand]=====================";

const char bun_venit[][75] = {
    {"______                               _ _     _ \n"},
    {"| ___ \\                             (_) |   | |\n"},
    {"| |_/ /_   _ _ __   __   _____ _ __  _| |_  | |\n"},
    {"| ___ \\ | | | '_ \\  \\ \\ / / _ \\ '_ \\| | __| | |\n"},
    {"| |_/ / |_| | | | |  \\ V /  __/ | | | | |_  |_|\n"},
    {"\\____/ \\__,_|_| |_|   \\_/ \\___|_| |_|_|\\__| (_)\n"}
};

/* ================================[ Functii ]=============================== */

/**
 * @brief Wrapper pentru citire
 * 
 * @param s string-ul unde va fi stocat ce e citit
 * @return 0 - User-ul vrea sa iasa | 1 - Input normal
 */
int input(char s[]);

/* ===============================[ Screens ]================================ */

int select_quiz_category();

/**
 * @brief Afiseaza meniul 
 */
void main_menu();

/**
 * @brief Afiseaza mesajul de inceput
 */
void welcome();

/* ===============================[ Helpers ]================================ */

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