#ifndef QUIZ_CLI_QUIZ_H
#define QUIZ_CLI_QUIZ_H

#include "question.h"

enum QuizType {
    Math = 0,
    Rom = 1,
    Geo = 2,
    Bio = 3,
};

struct Quiz {
    char name[128];
    QuizType type;
    unsigned short number_of_questions;
    Question questions[64];
};

#endif  //QUIZ_CLI_QUIZ_H
