#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define row 23
#define col 23
#define max 8
#define sink -1

int grid[row][col];
int h;

void sandFall(int i, int j);

void sandAvalanche(int i, int j);

void initGrid() {
    // printf("initGrid");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == sink) {
                printf("# ");
            } else {
                printf("%d ", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void sandFall(int i, int j) {
    // printf("sandFall");
    if (grid[i][j] > max) {
        sandAvalanche(i, j);
    }
}

void sandAvalanche(int m, int n) {
    // printf("sandAvalanche");
    if (grid[m][n] != sink) {
        grid[m][n] = grid[m][n] + 1;
    }
    if (grid[m][n] != sink && grid[m][n] < max) {
        // break;
        return;
    } else if (grid[m][n] > max) {
        grid[m][n] = 1;
        if (grid[m - 1][n] != sink && m - 1 > sink) {
            grid[m - 1][n] = grid[m - 1][n] + 1;
            sandFall(m - 1, n);
        }

        if (grid[m + 1][n] != sink && n + 1 < col) {
            grid[m + 1][n] = grid[m + 1][n] + 1;
            sandFall(m + 1, n);
        }


        if (grid[m][n - 1] != sink && n - 1 > sink) {
            grid[m][n - 1] = grid[m][n - 1] + 1;
            sandFall(m, n - 1);
        }

        if (grid[m][n + 1] != sink && n + 1 < col) {
            grid[m][n + 1] = grid[m][n + 1] + 1;
            sandFall(m, n + 1);
        }


        if (grid[m - 1][n - 1] != sink && m - 1 > sink && n - 1 > sink) {
            grid[m - 1][n - 1] = grid[m - 1][n - 1] + 1;
            sandFall(m - 1, n - 1);
        }

        if (grid[m - 1][n + 1] != sink && m - 1 > sink && n + 1 < col) {
            grid[m - 1][n + 1] = grid[m - 1][n + 1] + 1;
            sandFall(m - 1, n + 1);

        }

        if (grid[m + 1][n - 1] != sink && m + 1 < col && n - 1 > sink) {
            grid[m + 1][n - 1] = grid[m + 1][n - 1] + 1;
            sandFall(m + 1, n - 1);
        }

        if (grid[m + 1][n + 1] != sink && m + 1 < row && n + 1 < col) {
            grid[m + 1][n + 1] = grid[m + 1][n + 1] + 1;
            sandFall(m + 1, n + 1);
        }
    }
}

int main(int argc, char *argv[]) {
    int i;
    int j;
    int x;
    int y;
    int fps = 100;
    int index = 1;

    if (argc > 1) {
        i = 1;
        index = 1;
        if (strcmp("--fps", argv[i]) == 0) {
            char *fp = argv[i + 1];
            fps = atoi(fp);
            index = index + 2;
        } else {
            index = 1;
        }

        //printf("%d", fps);

        for (i = index; i < argc; i += 3) {
            char *mb = argv[i];
            char *mbmb = argv[i + 1];
            char *mbmbmb = argv[i + 2];
            x = atoi(mb);
            y = atoi(mbmb);
            h = atoi(mbmbmb);
            grid[y][x] = h;
        }
    }

    // printf("%d", x);
    // printf("%d", y);
    // printf("%d", h);
    // 1 = True, 0 = False

    while (1) {
        initGrid();
        sandAvalanche(row / 2, col / 2);
        usleep(1000000 / fps);
    }
}

