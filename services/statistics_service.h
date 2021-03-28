/**
 * Se ocupa de operatiile legate de statistici
 */

#ifndef QUIZ_CLI_STATISTICS_SERVICE_H
#define QUIZ_CLI_STATISTICS_SERVICE_H

#include <fstream>
#include <cstring>
#include "../models/result.h"

// Numarul maxim de rezultate (folosit la definirea results[])
const unsigned short MAX_PREVIOUS_RESULTS = 256;

/**
 * @brief Citeste rezultatele anterioare (din quiz_uri/statistics.data)
 * 
 * @param results aici vor fi salvate
 * @param n referinta - aici se va memora numarul de rezultate anterioare
 * @return status code: -1: fail | 0: success
 */
int read_statistics(PreviousResult results[], unsigned short &n);

/**
 * @brief Adauga un nou rezultat in fisier (face append)
 * 
 * @param username User.name
 * @param quiz_name Quiz.name
 * @param time_date Ora si Data curenta
 * @param score scorul (xx%) 
 */
void write_statistic(char username[], char quiz_name[], char time_date[], char score[]);

/**
 * @brief Sterge statisticile anterioare din fisier 
 */
void delete_statistics();

#endif