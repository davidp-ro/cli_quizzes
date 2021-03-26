#ifndef QUIZ_CLI_STATISTICS_SERVICE_H
#define QUIZ_CLI_STATISTICS_SERVICE_H

#include <fstream>
#include <cstring>
#include "../models/result.h"

const unsigned short MAX_PREVIOUS_RESULTS = 256;

int read_statistics(PreviousResult results[], unsigned short &n);

void write_statistic(char username[], char quiz_name[], char time_date[], char score[]);

void delete_statistics();

#endif