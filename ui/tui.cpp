/**
 * Se ocupa de tot ce e legat de ui - afisari / clear / input-uri
 * 
 * Documentatie pentru functii in header 
 */

#include "tui.h"

int ui::input(char s[]) {
    std::cout << "> ";
    std::cin.getline(s, MAX_SAFE_INPUT - 1);

    if (strchr(s, 'q') || strchr(s, 'q') || strstr(s, "quit") || strstr(s, "exit")) {
        return 0;
    }

    return 1;
}

/* ===============================[ Screens ]================================ */

int ui::select_quiz_category(const char* title) {
    ui::reset();
    ui::put_header();
    std::cout << title << "\n";
    std::cout << "\n"
              << ui::separator << "\n";
    std::cout << "\nAlegeti o categorie (introducand numarul corespunzator):\n"
              << "\t1) " << ui::categorii_quiz[Math] << "\n"
              << "\t2) " << ui::categorii_quiz[Rom] << "\n"
              << "\t3) " << ui::categorii_quiz[Geo] << "\n"
              << "\t4) " << ui::categorii_quiz[Bio] << "\n";
    ui::put_footer();

    char option[MAX_SAFE_INPUT];
    if (!ui::input(option)) {
        return -1;
    }

    switch (atoi(option)) {
        case 1:
            return Math;
        case 2:
            return Rom;
        case 3:
            return Geo;
        case 4:
            return Bio;
        default:
            ui::reset();
            std::cout << "Atentie! Optiune invalida...\n";
            Sleep(1000);
            return -2;
    }
}

int ui::select_quiz(const char* title, Quiz quizzes[][MAX_NUMBER_OF_QUIZZES], int type) {
    ui::reset();
    ui::put_header();
    std::cout << title << "\n";
    std::cout << "\n"
              << ui::separator << "\n";
    std::cout << "\nAlegeti un quiz (introducand numarul corespunzator):\n";
    unsigned short index = 0;
    for (; index < MAX_NUMBER_OF_QUIZZES; ++index) {
        if (strlen(quizzes[type][index].name) != 0) {
            std::cout << "\t" << index + 1 << ") "
                      << quizzes[type][index].name
                      << " - " << quizzes[type][index].number_of_questions
                      << " intrebari\n";
        } else
            break;
    }
    ui::put_footer();

    char option_s[MAX_SAFE_INPUT];
    if (!ui::input(option_s)) {
        return -1;
    }

    int option = atoi(option_s);
    if (option < 1 || option > index) {
        ui::reset();
        std::cout << "Atentie! Optiune invalida...\n";
        Sleep(1000);
        return -2;
    }
    return option - 1;
}

void ui::show_quiz_question(Quiz quiz, User user, unsigned short question_index, bool view_mode) {
    ui::reset();
    ui::put_header();

    std::cout << ui::categorii_quiz[quiz.type] << " : " << quiz.name << " | Intrebarea " << question_index + 1 << " din " << quiz.number_of_questions << "\n";
    std::cout << ui::separator << "\n";
    std::cout << "Nume: " << user.name << " | Cod test: " << user.verification_code << "\n";

    std::cout << ui::separator << "\n\n";

    std::cout << quiz.questions[question_index].subject << "\n";

    for (unsigned short answer_index = 0;
         answer_index < quiz.questions[question_index].number_of_answers;
         ++answer_index) {
        std::cout << "\t" << answer_index + 1 << ") " << quiz.questions[question_index].answers[answer_index].name << "\n";
    }

    std::cout << "\n" << ui::separator << "\n";

    if (view_mode) {
        std::cout << "\nApasati enter pentru a merge mai departe\n";
    } else {
        std::cout << "\nAlegeti un raspuns (introducand numarul corespunzator):\n";
    }

    ui::put_footer();
}

void ui::main_menu(User user) {
    char timedate[80];
    ui::get_time_and_date(timedate);
    
    char padding[80] = "";
    for (unsigned short i = 0; i < (80 - (strlen(user.name) + 6) - strlen(timedate)); ++i) {
        strcat(padding, " ");
    }

    ui::reset();
    ui::put_header();
    std::cout << "\nBuna, " << user.name << padding << timedate << "\n";

    std::cout << "\n" << ui::separator << "\n";

    std::cout << "\nAlegeti o optiune (introducand numarul corespunzator):\n"
              << "\t1) Incepeti un nou quiz\n\n"
              << "\t2) Vedeti quiz-urile disponibile\n"
              << "\t3) Creeati un nou quiz\n"
              << "\t4) Stergeti un quiz\n\n"
              << "\t5) Rezultate anterioare\n";
    ui::put_footer();
}

void ui::welcome() {
    ui::put_header();
    std::cout << "\n"
              << ui::bun_venit[0]
              << ui::bun_venit[1]
              << ui::bun_venit[2]
              << ui::bun_venit[3]
              << ui::bun_venit[4]
              << ui::bun_venit[5];

    std::cout << "\n"
              << ui::separator << "\n";

    std::cout << "Daca ai primit un cod de la profesor acum e momentul sa il introduceti.\n"
              << "Daca nu doar apasati enter.\n";

    ui::put_footer();
}

int ui::create_question(Question &q, unsigned short question_number) {
    char buf[MAX_SAFE_INPUT];
    
    std::cout << "\n" << ui::separator << "\n";

    std::cout << "\nSubiectul intrebarii " << question_number + 1 << ": ";
    if (!ui::input(buf)) {
        return -1;
    }
    strcpy(q.subject, buf);
    std::cout << "\nCate raspunsuri are intrebarea: ";
    if (!ui::input(buf)) {
        return -1;
    }
    q.number_of_answers = atoi(buf);

    for (unsigned short answer_index = 0;
         answer_index < q.number_of_answers;
         ++answer_index) {
        Answer newAnswer;
        if (ui::create_answer(newAnswer, answer_index) != 0) {
            return -1;
        }
        q.answers[answer_index] = newAnswer;
    }

    return 0;
}

int ui::create_answer(Answer &a, unsigned short answer_number) {
    char buf[MAX_SAFE_INPUT];

    std::cout << "\nNumele raspunsului " << answer_number + 1 << ": ";
    if (!ui::input(buf)) {
        return -1;
    }
    strcpy(a.name, buf);

    std::cout << "\nE corect? (da/nu): ";
    if (!ui::input(buf)) {
        return -1;
    }
    if (strstr(buf, "da") || strstr(buf, "DA")) {
        a.is_correct = true;
    } else {
        a.is_correct = false;
    }

    return 0;
}

/* ===============================[ Helpers ]================================ */

void ui::get_time_and_date(char s[]) {
    time_t now = time(0);
    tm *time = localtime(&now);
    char buf[36];
    
    strcpy(s, "");
    
    // Time:
    // Ora
    itoa(time->tm_hour, buf, 10);
    if (time->tm_hour < 10) {
        strcat(s, "0");
    }
    strcat(s, buf);
    strcat(s, ":");
    // Minut
    itoa(time->tm_min, buf, 10);
    if (time->tm_min < 10) {
        strcat(s, "0");
    }
    strcat(s, buf);

    strcat(s, " ");

    // Date:
    // Ziua (cu 0 in fata daca e sub 10)
    itoa(time->tm_mday, buf, 10);
    if (time->tm_mday < 10) {
        strcat(s, "0");
    }
    strcat(s, buf);
    strcat(s, ".");
    // Luna (cu 0 in fata daca e sub 10)
    itoa(1 + time->tm_mon, buf, 10);
    if (1 + time->tm_mon < 10) {
        strcat(s, "0");
    }
    strcat(s, buf);
    strcat(s, ".");
    // Anul
    itoa(1900 + time->tm_year, buf, 10);
    strcat(s, buf);
}

void ui::put_header() {
    std::cout << "\n"
              << ui::header << "\n";
}

void ui::put_footer() {
    std::cout << "\n"
              << ui::footer << "\n";
}

void ui::reset() {
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
            hStdOut,
            (TCHAR)' ',
            cellCount,
            homeCoords,
            &count)) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
            hStdOut,
            csbi.wAttributes,
            cellCount,
            homeCoords,
            &count)) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
