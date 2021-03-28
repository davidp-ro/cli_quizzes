/**
 * Se ocupa de operatiile legate de statistici
 * 
 * Documentatie pentru functii in header
 */

#include "statistics_service.h"

int read_statistics(PreviousResult results[MAX_PREVIOUS_RESULTS], unsigned short &n) {
    std::ifstream fin("quiz_uri/statistics.data");
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
                    strtok(ptr, "%"); // In ptr va ramane doar valoarea ca numar
                    results[i].i_score = atoi(ptr);
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
    fout.open("quiz_uri/statistics.data", std::fstream::app); // Append

    fout << username << "," << quiz_name << "," << time_date << "," << score << "\n";
    
    fout.close();
}

void delete_statistics() {
    std::ofstream fout("quiz_uri/statistics.data");
    fout.close();
}

void swap(PreviousResult &r1, PreviousResult &r2) {
    PreviousResult temp = r1;
    r1 = r2;
    r2 = temp;
}

void sort_results_by_score(PreviousResult results[], unsigned short n) {
    for (unsigned short i = 0; i < n - 1; ++i) {
        for (unsigned short index = 0; index < n - i - 1; ++index) {
            if (results[index].i_score < results[index + 1].i_score) {
                swap(results[index], results[index + 1]);
            }
        }
    }
}
