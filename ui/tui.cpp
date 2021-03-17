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

int ui::select_quiz_category() {
    ui::reset();
    ui::put_header();
    std::cout << "\nAlegeti o categorie (introducand numarul corespunzator):\n"
              << "\t1) Matematica\n"
              << "\t2) Romana\n"
              << "\t3) Geografie\n"
              << "\t4) Biologie\n";
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

void ui::main_menu() {
    ui::reset();
    ui::put_header();
    std::cout << "\nAlegeti o optiune (introducand numarul corespunzator):\n"
              << "\t1) Incepeti un nou quiz\n\n"
              << "\t2) Vedeti quiz-urile disponibile\n"
              << "\t3) Creeati un nou quiz\n"
              << "\t4) Stergeti un quiz\n";
    ui::put_footer();
}

void ui::welcome() {
    std::cout << "\n"
              << ui::bun_venit[0]
              << ui::bun_venit[1]
              << ui::bun_venit[2]
              << ui::bun_venit[3]
              << ui::bun_venit[4]
              << ui::bun_venit[5];

    std::cout << "\n"
              << ui::separator << "\n";

    std::cout << "Aveti un cod de verificare de la profesor? Daca da introduce-ti-l.\n"
              << "Daca nu doar apasati enter.\n";
}

/* ===============================[ Helpers ]================================ */

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
