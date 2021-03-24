/**
 * Citirea si scrierea datelor din/in fisierele din folderul quiz-uri
 * 
 * Documentatie pentru functii in header
 */

#include "reader_writter.h"

// Tine cont de cate quiz-uri au fost citite
int number_of_quizzes = 0;

int read(Quiz quizzes[][MAX_NUMBER_OF_QUIZZES]) {
    int status = read_individual(quizzes, Math, "quiz_uri/matematica.data");
    if (status == -1) {
        return -1;
    }

    status = read_individual(quizzes, Rom, "quiz_uri/romana.data");
    if (status == -1) {
        return -1;
    }

    status = read_individual(quizzes, Geo, "quiz_uri/geografie.data");
    if (status == -1) {
        return -1;
    }

    status = read_individual(quizzes, Bio, "quiz_uri/biologie.data");
    if (status == -1) {
        return -1;
    }

    return number_of_quizzes;
}

int write(Quiz quizzes[][MAX_NUMBER_OF_QUIZZES]) {
    write_individual(quizzes, Math, "quiz_uri/matematica.data");

    write_individual(quizzes, Rom, "quiz_uri/romana.data");

    write_individual(quizzes, Geo, "quiz_uri/geografie.data");

    write_individual(quizzes, Bio, "quiz_uri/biologie.data");

    return 0;
}

/* ===============================[ Helpers ]================================ */

int read_individual(Quiz quizzes[][MAX_NUMBER_OF_QUIZZES], QuizType type, const char filename[]) {
    std::ifstream fin(filename);

    char buffer[128];
    bool started_quiz = false;
    int index = 0;

    // Daca ceva nu ii ok cu fisierul / e gol, renuntam
    if (!fin.good()) {
        return -1;
    }

    while (!fin.eof()) {
        fin.getline(buffer, 127);

        // Ignoram linii goale
        if (strlen(buffer) == 0) {
            continue;
        }

        if (strcmp(buffer, "BEGIN_QUIZ") == 0 && !started_quiz) {
            started_quiz = true;
        } else if (strcmp(buffer, "END_QUIZ") == 0 && started_quiz) {
            started_quiz = false;
            ++number_of_quizzes;
            ++index;
        } else {
            if (DEBUG_MODULE) {
                std::cout << "START OF NEW QUIZ\n";
            }
            Quiz new_quiz;
            new_quiz.type = type;
            strcpy(new_quiz.name, buffer);
            fin.getline(buffer, 127);  // Next line
            new_quiz.number_of_questions = atoi(buffer);

            for (unsigned short question_index = 0;
                 question_index < new_quiz.number_of_questions;
                 ++question_index) {
                // Read questions
                fin.getline(buffer, 127);  // Next line
                new_quiz.questions[question_index] = parseRawQuestion(buffer);
            }

            // Adaugam quiz-ul citit
            quizzes[type][index] = new_quiz;
        }
    }

    fin.close();
    return 0;
}

void write_individual(Quiz quizzes[][MAX_NUMBER_OF_QUIZZES], QuizType type, const char filename[]) {
    std::ofstream fout(filename);

    for (int quiz_index = 0; quiz_index < MAX_NUMBER_OF_QUIZZES; ++quiz_index) {
        // Daca numele e gol => nu mai avem quiz-uri de acest tip
        if (strlen(quizzes[type][quiz_index].name) == 0) {
            break;
        }
        // Parcurgem quiz-urile
        fout << "BEGIN_QUIZ\n";
        fout << quizzes[type][quiz_index].name << "\n";  // Nume
        fout << quizzes[type][quiz_index].number_of_questions
             << "\n";  // Nr intrebari
        for (unsigned short question_index = 0;
             question_index < quizzes[type][quiz_index].number_of_questions;
             ++question_index) {
            // Parcurgem intrebarile dintr-un quiz
            fout << quizzes[type][quiz_index].questions[question_index].subject
                 << ", ";  // Subiectul intrebarii
            fout << quizzes[type][quiz_index]
                        .questions[question_index]
                        .number_of_answers
                 << ", ";  // Nr raspunsuri
            for (unsigned short answer_index = 0;
                 answer_index < quizzes[type][quiz_index]
                                    .questions[question_index]
                                    .number_of_answers;
                 ++answer_index) {
                // Parcurgem raspunsurile dintr-o intrebare
                // Daca raspunsul e cel corect punem ! in fata
                if (quizzes[type][quiz_index]
                        .questions[question_index]
                        .answers[answer_index]
                        .is_correct) {
                    fout << "!"
                         << quizzes[type][quiz_index]
                                .questions[question_index]
                                .answers[answer_index]
                                .name;
                } else {
                    fout << quizzes[type][quiz_index]
                                .questions[question_index]
                                .answers[answer_index]
                                .name;
                }
                // Daca nu e ultimul raspuns punem , la final, altfel \n
                if (quizzes[type][quiz_index]
                            .questions[question_index]
                            .number_of_answers -
                        answer_index >
                    1) {
                    fout << ", ";
                } else {
                    fout << "\n";
                }
            }
        }
        fout << "END_QUIZ\n\n";
    }

    fout.close();
}

Answer parseRawAnswer(char pointer_to_answer[]) {
    Answer new_answer;

    new_answer.is_correct = (pointer_to_answer[0] == '!');
    if (new_answer.is_correct) {
        strcpy(new_answer.name, pointer_to_answer + 1);
    } else {
        strcpy(new_answer.name, pointer_to_answer);
    }

    if (DEBUG_MODULE) {
        char str[100];
        answer_to_string(new_answer, str);
        std::cout << "parsed: " << str << "\n";
    }

    return new_answer;
}

Question parseRawQuestion(char question_line[]) {
    Question new_question;

    unsigned short step = 1;
    unsigned short answer_index = 0;
    char* ptr = strtok(question_line, ",");

    while (ptr != nullptr) {
        // Curatare de spatii
        unsigned short space_index = 0;
        while (ptr[space_index] == ' ') {
            ++space_index;
        }
        strcpy(ptr, ptr + space_index);

        switch (step) {
            case 1:  // Nume
                strcpy(new_question.subject, ptr);
                ++step;
                break;
            case 2:  // Cate intrebari
                new_question.number_of_answers = atoi(ptr);
                ++step;
                break;
            case 3:  // Variante
                new_question.answers[answer_index] = parseRawAnswer(ptr);
                ++answer_index;
                if (answer_index == new_question.number_of_answers) {
                    step = 99;
                }
                break;
        }
        ptr = strtok(NULL, ",");
    }

    if (DEBUG_MODULE) {
        char str[256];
        question_to_string(new_question, str);
        std::cout << "parsed: " << str << "\n";
    }

    return new_question;
}
