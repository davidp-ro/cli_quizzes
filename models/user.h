/**
 * Reprezentarea unui utilizator
 */

#ifndef QUIZ_CLI_USER_H
#define QUIZ_CLI_USER_H

/**
 * @brief Reprezentarea unui raspuns
 */
struct User {
    char name[256];
    char verification_code[256];
};

#endif
