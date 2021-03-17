#ifndef QUIZ_CLI_QUIZ_H
#define QUIZ_CLI_QUIZ_H

#include "question.h"

const int MAX_NUMBER_OF_CATEGORIES = 6;
const int MAX_NUMBER_OF_QUIZZES = 12; // Pe categorie
const int NUMBER_OF_TYPES = 3; // Cate sunt MINUS 1

/**
 * @brief Tipurile de quiz disponibile
 */
enum QuizType {
    Math = 0,
    Rom = 1,
    Geo = 2,
    Bio = 3,
};

/**
 * @brief Reprezentarea unui Quiz
 */
struct Quiz {
    char name[128];
    QuizType type;
    unsigned short number_of_questions;
    Question questions[64];
};

#endif  //QUIZ_CLI_QUIZ_H
