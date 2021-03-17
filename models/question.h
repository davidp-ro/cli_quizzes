#ifndef QUIZ_CLI_QUESTION_H
#define QUIZ_CLI_QUESTION_H

#include "answer.h"
#include <iostream>

/**
 * @brief Reprezentarea unei intrebari
 */
struct Question {
    char subject[128];
    unsigned short number_of_answers;
    Answer answers[4];
};

/**
 * @brief Reprezentarea unui struct Question sub un string
 * 
 * @param ans instanta de Question
 * @param s string-ul in care e pusa reprezentarea
 */
void question_to_string(Question que, char s[]);

#endif //QUIZ_CLI_QUESTION_H
