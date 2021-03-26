/**
 * Se ocupa de operatiile legate de statistici
 * 
 * Documentatie pentru functii in header
 */

#include "statistics_service.h"

int read_statistics(PreviousResult results[MAX_PREVIOUS_RESULTS], unsigned short &n) {
    std::ifstream fin("services/statistics_service.data");
    char buffer[1025];
    unsigned short i = 0;
    n = 0;

    if (!fin.good()) {
        return -1;
    }

    while (fin.good()) {
        fin.getline(buffer, 1024);

        if (strlen(buffer) < 5) {
            continue; // Sari peste linii goale
        }

        char* ptr = strtok(buffer, ",");
        unsigned short step = 1;

        while (ptr != nullptr) {
            switch (step) {
                case 1:
                    strcpy(results[i].username, ptr);
                    ++step;
                    break;
                case 2:
                    strcpy(results[i].quiz_name, ptr);
                    ++step;
                    break;
                case 3:
                    strcpy(results[i].time_date, ptr);
                    ++step;
                    break;
                case 4:
                    strcpy(results[i].score, ptr);
                    ++step;  // Nu mai e folosit
                    ++i;
                    ++n;
                    break;
            }

            ptr = strtok(NULL, ",");
        }
    }

    fin.close();
    return 0;
}

void write_statistic(char username[], char quiz_name[], char time_date[], char score[]) {
    std::fstream fout;
    fout.open("services/statistics_service.data", std::fstream::app); // Append

    fout << username << "," << quiz_name << "," << time_date << "," << score << "\n";
    
    fout.close();
}

void delete_statistics() {
    std::ofstream fout("services/statistics_service.data");
    fout.close();
}