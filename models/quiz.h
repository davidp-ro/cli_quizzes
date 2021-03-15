#ifndef QUIZ_CLI_QUIZ_H
#define QUIZ_CLI_QUIZ_H

#include "question.h"

struct Quiz {
    char name[128];
    unsigned short number_of_questions;
    Question questions[64];
};

#endif //QUIZ_CLI_QUIZ_H
