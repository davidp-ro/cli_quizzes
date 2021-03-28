/**
 * Reprezentarea unui utilizator
 */

#ifndef QUIZ_CLI_RESULT_H
#define QUIZ_CLI_RESULT_H

/**
 * @brief Reprezentarea unui rezultat anterior
 */
struct PreviousResult {
    char username[256];
    char quiz_name[256];
    char time_date[256];
    char score[16];
    int i_score = -1;
};

#endif
