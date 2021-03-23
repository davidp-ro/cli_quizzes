#ifndef QUIZ_CLI_TAKE_QUIZ_H
#define QUIZ_CLI_TAKE_QUIZ_H

#include <fstream>
#include "../ui/tui.h"

const bool DBG_SHOW_FILEPATH = true;

int take_quiz(Quiz quiz, User user);

#endif