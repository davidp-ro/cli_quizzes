#include "quiz_service.h"

int take_quiz(Quiz quiz, User user) {
    for (unsigned short question_index = 0;
         question_index < quiz.number_of_questions;
         ++question_index) {
        ui::show_quiz_question(quiz, user, question_index);

        char option_s[MAX_SAFE_INPUT];
        if (!ui::input(option_s)) {
            return -1;
        }
    }

    return 0;
}

// hdr
// titlu | intrebarea x/n | cod = x
// spacer
// intrebare
// raspunsuri 1/rand
// input