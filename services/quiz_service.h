/**
 * Se ocupa de operatiile legate de quiz-uri 
 */

#ifndef QUIZ_CLI_TAKE_QUIZ_H
#define QUIZ_CLI_TAKE_QUIZ_H

#include <fstream>
#include "../ui/tui.h"
#include "../data/reader_writter.h"
#include "statistics_service.h"

// Daca e true va afisa path-ul pana la fiserul de salvare
const bool DBG_SHOW_FILEPATH = false;

/**
 * @brief "Intra" in modul de test.
 * 
 *  Afiseaza optiunile, utilizatorul alege, iar optiunile cat si rezultatul e 
 * salvat (daca USERPROFILE e prezent -> pe desktop, altfel in folderul curent)
 * 
 * @param quiz Quiz-ul selectat
 * @param user Utilizatorul
 * @return status code: -1: exit | 0: success
 */
int take_quiz(Quiz quiz, User user);

/**
 * @brief Vizualizeaza un quiz
 * 
 * @param quiz Quiz-ul selectat
 * @param user Utilizatorul
 * @return status code: -1: exit | 0: success
 */
int view_quiz(Quiz quiz, User user);

/**
 * @brief Creeaza un quiz.
 * 
 *  Adauga in memorie, si salveaza toate quiz-urile
 * 
 * @param quizzes array-ul in care sunt stocate quiz-urile
 * @param category categoria aleasa pentru creeatie
 * @return status code: -1: exit | 0: success
 */
int create_quiz(Quiz quizzes[][MAX_NUMBER_OF_QUIZZES], int category);

#endif