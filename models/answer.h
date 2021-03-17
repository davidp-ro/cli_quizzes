#ifndef QUIZ_CLI_ANSWER_H
#define QUIZ_CLI_ANSWER_H

#include <cstring>
#include <stdlib.h>

/**
 * @brief Reprezinta un raspuns
 * 
 * La citire un raspuns va fi marcat ca fiind cel corect printr-un ! la inceputul cuvantului
 * 
 * Exemplu:
 *  <Subiect intrebare>, 4, <raspuns1>, !<raspuns2>, <raspuns3>, <raspuns4>
 *  Aici raspunsul corect va fi cel de-al doilea
 */
struct Answer {
    char name[64];
    bool is_correct;
};

/**
 * @brief Reprezentarea unui Answer sub un string
 * 
 * @param ans instanta de Answer
 * @param s string-ul in care e pusa reprezentarea
 */
void answer_to_string(Answer ans, char s[]);

#endif //QUIZ_CLI_ANSWER_H
