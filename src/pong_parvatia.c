#include <stdio.h>

int ball_coord(int ball_x, int ball_y, int l_racket, int r_racket, int start, int var) {
    /* ball_x и ball_y координаты мячика, var - выбор одного из 2 начальный направлений движения шарика
    координаты ракеток по y */
    int ball_dir_x, ball_dir_y;
    if (start == 0) {
        ball_x = 40;
        ball_y = 11;
        if (var == 1) {
            ball_dir_y = 0;
            ball_dir_x = 1;
            printf("ball_x = %d, ball_y = %d, l_racket = %d, r_racket = %d, start = %d, var = %d\n", ball_x, ball_y, l_racket, r_racket, start, var);
        }
        else {
            ball_dir_y = 0;
            ball_dir_x = -1;
        }
    }
    else {
        if ((ball_x < 77) && (ball_x > 2)) {
            
        }
        if (ball_x == 77) {
            if (ball_y == r_racket) {
                ball_dir_x *= -1;
                ball_dir_y *= -1;
            }
            if ((ball_y == r_racket - 1) || (ball_y == r_racket + 1)) {
                ball_dir_x *= -1;
                ball_dir_y *= 1;
            }
            else {
                ball_dir_x *= 1;
                ball_dir_y *= 1;
            }
        }
        if (ball_x == 2) {
            if (ball_y == l_racket) {
                ball_dir_x *= -1;
                ball_dir_y *= -1;
            }
            if ((ball_y == l_racket - 1) || (ball_y == r_racket + 1)) {
                ball_dir_x *= -1;
                ball_dir_y *= 1;
            }
            else {
                ball_dir_x *= 1;
                ball_dir_y *= 1;
            }
        }
    }
    ball_x = ball_x + ball_dir_x;
    ball_y = ball_y + ball_dir_y;
    return ball_x, ball_y, l_racket, r_racket, start, var;
}



int main () {
    printf("ball_x = %d, ball_y = %d, l_racket = %d, r_racket = %d, start = %d, var = %d\n", ball_coord(41, 13, 12, 11, 1, 1));
    return 0;
}