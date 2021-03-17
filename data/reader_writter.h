/**
 * Citirea si scrierea datelor in fisier (data/quizzes.data) 
 */

#ifndef QUIZ_CLI_READER_WRITTER_H
#define QUIZ_CLI_READER_WRITTER_H

#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "../models/quiz.h"
#include "../models/question.h"
#include "../models/answer.h"

// Print-uri pentru debugging
const bool DEBUG_MODULE = false;

/**
 * @brief Citeste quiz-urile din folderul quiz-uri
 * 
 * @param quizzes array-ul in care vor fi stocate quiz-urile
 * @return status code: -1 - Ceva nu a mers | <pozitiv> - Numarul de quiz-uri
 */
int read(Quiz quizzes[][12]);

/**
 * @brief Scrie quiz-urile in folderul quiz-uri
 * 
 * @param quizzes array-ul in care sunt stocate quiz-urile
 * @param number_of_quizzes care quiz-uri sunt
 * @return status code: 0 - Success | -1 - Ceva nu a mers 
 */
int write(Quiz quizzes[][12], int number_of_quizzes);

/* ===============================[ Helpers ]================================ */

/**
 * @brief Citeste dintr-un fisier quiz-uri
 * 
 * @param quizzes array-ul in care sunt stocate quiz-urile
 * @param type tip-ul quiz-ului
 * @param filename fisierul din care citim quiz-urile / categorie
 * @return status code: 0 - Success | -1 - Ceva nu a mers 
 */
int read_individual(Quiz quizzes[][12], QuizType type, const char filename[]);

/**
 * @brief Scrie intr-un fisier quiz-uri
 * 
 * @param quizzes array-ul in care sunt stocate quiz-urile
 * @param type tip-ul quiz-ului
 * @param filename fisierul in care scriem quiz-urile / categorie
 */
void write_individual(Quiz quizzes[][12], QuizType type, const char filename[]);

/**
 * @brief Creeaza un struct Answer dintr-un string 
 * 
 * @note Daca un cuvant incepe cu ! este marcat ca fiind corect
 * 
 * @param pointer_to_answer string-ul separat cu strtok (si curatat!)
 * @return Answer - struct-ul construit
 */
Answer parseRawAnswer(char pointer_to_answer[]);

/**
 * @brief Creeaza un struct Question dintr-un string 
 * 
 * @param question_line string-ul rezultat din fin.getline()
 * @return Question - struct-ul construit
 */
Question parseRawQuestion(char question_line[]);

#endif //QUIZ_CLI_READER_WRITTER_H
