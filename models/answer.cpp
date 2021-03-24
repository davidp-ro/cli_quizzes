/**
 * Functii ajutatoare pentru struct-ul Answer
 * 
 * Documentatie pentru functii in header
 */

#include "answer.h"

void answer_to_string(Answer ans, char s[]) {
  strcpy(s, "");
  strcat(s, "Answer:{name: ");
  strcat(s, ans.name);
  strcat(s, ", is_correct: ");
  strcat(s, ans.is_correct ? "true" : "false");
  strcat(s, "}");
}