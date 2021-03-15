#ifndef QUIZ_CLI_QUESTION_H
#define QUIZ_CLI_QUESTION_H

#include "answer.h"
#include <iostream>

struct Question {
    char subject[128];
    unsigned short number_of_answers;
    Answer answers[4];
};

void question_to_string(Question que, char s[]);

#endif //QUIZ_CLI_QUESTION_H
