/**
 * Functii ajutatoare pentru struct-ul Answer
 * 
 * Documentatie pentru functii in header
 */

#include "question.h"

void question_to_string(Question que, char s[]) {
  strcpy(s, "");
  strcat(s, "Question:{subject: ");
  strcat(s, que.subject);
  strcat(s, ", number_of_answers: ");
  char num_ans_string[10];
  itoa(que.number_of_answers, num_ans_string, 10);
  strcat(s, num_ans_string);
  strcat(s, ", answers: Answer[]}");
}