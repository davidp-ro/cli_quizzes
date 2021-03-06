/**
 * Se ocupa de operatiile legate de quiz-uri 
 * 
 * Documentatie pentru functii in header
 */

#include "quiz_service.h"

void put_current_question_to_file(std::ofstream &file, Quiz quiz, unsigned short question_index) {
    file << "Intrebarea " << question_index + 1 << " din " << quiz.number_of_questions
         << " - " << quiz.questions[question_index].subject << "\n";

    for (unsigned short answer_index = 0;
         answer_index < quiz.questions[question_index].number_of_answers;
         ++answer_index) {
        file << "\t" << answer_index + 1 << ") " << quiz.questions[question_index].answers[answer_index].name << "\n";
    }
}

void get_filename(char s[], char date_time[], User user, Quiz quiz) {
    strcpy(s, "");
    strcat(s, "rezultat_");
    strcat(s, user.name);
    strcat(s, "_");
    strcat(s, quiz.name);
    strcat(s, "_");
    strcat(s, date_time);
    strcat(s, ".txt");
}

void make_valid_path(char path[]) {
    for (int i = 0; path[i]; ++i) {
        if (path[i] == '\\')
            path[i] = '/';
        else if (path[i] == ' ')
            path[i] = '_';
        else if (path[i] == ':' && i > 2)
            path[i] = '-';
    }
}

int take_quiz(Quiz quiz, User user) {
    unsigned short raspunsuri_corecte = 0;

    char save_path[1024] = "";
    strcpy(save_path, getenv("USERPROFILE"));

    if (strlen(save_path) != 0) {
        strcat(save_path, "\\Desktop\\");
    }
    char td[MAX_SAFE_INPUT];
    ui::get_time_and_date(td);

    // Fisier salvare
    char filename[MAX_SAFE_INPUT] = "";
    get_filename(filename, td, user, quiz);
    strcat(save_path, filename);
    make_valid_path(save_path);
    std::ofstream s_file(save_path);

    s_file << "REZULTAT - Nume: " << user.name << " | Cod Verificare: " << user.verification_code << "\n";
    s_file << "Inceput la " << td << "\n\n";

    s_file << "Quiz - Nume: " << quiz.name << " | Categorie: " << ui::categorii_quiz[quiz.type] << "\n";

    s_file << "\n"
           << ui::separator << "\n\n";

    for (unsigned short question_index = 0;
         question_index < quiz.number_of_questions;
         ++question_index) {
        ui::show_quiz_question(quiz, user, question_index, false);
        put_current_question_to_file(s_file, quiz, question_index);

        if (DBG_SHOW_FILEPATH) {
            std::cout << "\nFilepath: " << save_path << "\n";
        }

        char option_s[MAX_SAFE_INPUT];
        if (!ui::input(option_s)) {
            s_file << "--NETERMINAT--";
            s_file.close();
            return -1;
        }

        s_file << "\nRaspuns ales: " << option_s << " | E raspunsul corect? ";

        if (quiz.questions[question_index].answers[atoi(option_s) - 1].is_correct) {
            s_file << "Da\n";
            ++raspunsuri_corecte;
        } else {
            s_file << "Nu\n";
        }

        s_file << "\n"
               << ui::separator << "\n\n";
    }

    ui::get_time_and_date(td);
    char scor[32];
    itoa((raspunsuri_corecte * 100 / quiz.number_of_questions), scor, 10);
    strcat(scor, "%");

    s_file << "\nSUMAR:\n"
           << "Finalizat la " << td << "\n"
           << raspunsuri_corecte << " raspunsuri corecte din " << quiz.number_of_questions << " raspunsuri totale"
           << " | Scor: " << scor << "\n";

    s_file.close();
    write_statistic(user.name, quiz.name, td, scor);
    return 0;
}

int view_quiz(Quiz quiz, User user) {
    for (unsigned short question_index = 0;
         question_index < quiz.number_of_questions;
         ++question_index) {
        ui::show_quiz_question(quiz, user, question_index, true);

        char option_s[MAX_SAFE_INPUT];
        if (!ui::input(option_s)) {
            return -1;
        }
    }

    return 0;
}

int create_quiz(Quiz quizzes[][MAX_NUMBER_OF_QUIZZES], int category) {
    Quiz newQuiz;
    newQuiz.type = (QuizType)category;
    char buf[MAX_SAFE_INPUT];

    ui::reset();
    ui::put_header();
    std::cout << ui::footer << "\n";

    std::cout << "\nNumele quiz-ului: ";
    if (!ui::input(buf)) {
        return -1;
    }
    strcpy(newQuiz.name, buf);
    std::cout << "\nCate intrebari are quiz-ul: ";
    if (!ui::input(buf)) {
        return -1;
    }
    newQuiz.number_of_questions = atoi(buf);

    for (unsigned short question_index = 0;
         question_index < newQuiz.number_of_questions;
         ++question_index) {
        Question newQuestion;
        if (ui::create_question(newQuestion, question_index) != 0) {
            return -1;
        }
        newQuiz.questions[question_index] = newQuestion;
    }

    // Salvare
    for (int quiz_index = 0; quiz_index < MAX_NUMBER_OF_QUIZZES; ++quiz_index) {
        if (strlen(quizzes[category][quiz_index].name) == 0) {
            quizzes[category][quiz_index] = newQuiz;
            write(quizzes);
            return 0;
        }
    }

    return -1;
}
