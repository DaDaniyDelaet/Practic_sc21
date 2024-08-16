#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define STR 25
#define ROW 80

// Функция ввода матрцицы
void input_matrix(int matrx[][ROW]);

// Функция вывода матрицы
void out_matrix(int matrx[][ROW]);

// Функция возвращающая stop и переводящяя матрицу на новое поколение
int new_matrx(int matrx[][ROW], int matrx_tmpl[][ROW]);

// Функция определения след поколения для клетки

int chek_life(int matrx[][ROW], int x, int y);

// Функция для подсчета живых соседей
int sum_neigh(int matrx[][ROW], int x, int y);

// Функция проверяющая статичность матрицы
int check_new(int matrx[][ROW], int matrx_tmpl[][ROW]);

// Функция смены скорости
int change_speed(char control_button, int time_mili_sec);

// main
int main() {
    int matrx[STR][ROW];
    int matrx_tmpl[STR][ROW];
    int time_mili_sec = 500;
    int stop = 0;

    input_matrix(matrx);
    if (freopen("/dev/tty", "r", stdin)) initscr();  // Инициализация ncurses
    nodelay(stdscr, true);

    while (stop != 1) {
        char control_button = getch();

        if (control_button == 'q') break;

        time_mili_sec = change_speed(control_button, time_mili_sec);

        usleep(time_mili_sec * 1000);
        clear();

        stop = new_matrx(matrx, matrx_tmpl);
        out_matrix(matrx);
    }

    endwin();
    return 0;
}

void input_matrix(int matr[STR][ROW]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < ROW; j++) {
            scanf("%d", &matr[i][j]);
        }
    }
}

void out_matrix(int matrx[STR][ROW]) {
    for (int i = 0; i < STR; i++) {
        for (int j = 0; j < ROW; j++) {
            if (matrx[i][j] == 1)
                printw("0");
            else
                printw("-");
        }
        printw("\n");
    }
}

int new_matrx(int matrx[][ROW], int matrx_tmpl[][ROW]) {
    for (int i = 0; i < STR; ++i) {
        for (int j = 0; j < ROW; j++) {
            matrx_tmpl[i][j] = chek_life(matrx, i, j);
        }
    }
    int tmp = check_new(matrx, matrx_tmpl);
    for (int i = 0; i < STR; ++i) {
        for (int j = 0; j < ROW; j++) {
            matrx[i][j] = matrx_tmpl[i][j];
            matrx_tmpl[i][j] = 0;
        }
    }
    return tmp;
}

int chek_life(int matrx[STR][ROW], int x, int y) {
    int sum = sum_neigh(matrx, x, y);
    if (matrx[x][y] == 0) {
        if (sum == 3) return 1;
    } else {
        if ((sum == 3) || (sum == 2)) return 1;
    }
    return 0;
}

int sum_neigh(int matrx[STR][ROW], int x, int y) {
    int sum = 0;
    int str = STR;
    int row = ROW;
    // [1][2][3]
    // [8][*][4]
    // [7][6][5]
    // 1:
    sum += matrx[(str + x - 1) % str][(row + y - 1) % row];
    // 2:
    sum += matrx[x][(row + y - 1) % row];
    // 3:
    sum += matrx[(str + x + 1) % str][(row + y - 1) % row];
    // 4:
    sum += matrx[(str + x + 1) % str][y];
    // 5:
    sum += matrx[(str + x + 1) % str][(row + y + 1) % row];
    // 6:
    sum += matrx[x][(row + y + 1) % row];
    // 7:
    sum += matrx[(str + x - 1) % str][(row + y + 1) % row];
    // 8:
    sum += matrx[(str + x - 1) % str][y];
    return sum;
}

int check_new(int matrx[STR][ROW], int matrx_tmpl[STR][ROW]) {
    int tmp = 0;
    for (int i = 0; i < STR; ++i) {
        for (int j = 0; j < ROW; j++) {
            if (matrx[i][j] == matrx_tmpl[i][j]) tmp += 1;
        }
    }
    if (tmp == (STR) * (ROW)) {
        return 1;
    } else {
        return 0;
    }
}

int change_speed(char control_button, int time_mili_sec) {
    if ((control_button == 's') && (time_mili_sec > 100))
        time_mili_sec = time_mili_sec - 100;
    else if (control_button == '2')
        time_mili_sec = 50;
    else if (control_button == 'w')
        time_mili_sec = time_mili_sec + 100;
    return time_mili_sec;
}
