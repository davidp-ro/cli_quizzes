#ifndef QUIZ_CLI_QUIZ_H
#define QUIZ_CLI_QUIZ_H

#include "question.h"

enum QuizType {
    Geo = 1,
    Math = 2,
    Rom = 3,
    Bio = 4,
};

struct Quiz {
    char name[128];
    QuizType type;
    unsigned short number_of_questions;
    Question questions[64];
};

#endif  //QUIZ_CLI_QUIZ_H
