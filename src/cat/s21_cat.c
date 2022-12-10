// Copyright 2022 Handehig
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

typedef struct {
    int b, e, v, n, s, t;
} flags;

int parser(int argc, char *argv[], flags *flagers);
int reader(char *argv[], flags *flagers);

int main(int argc, char* argv[]) {
    flags flagers = {};
    int exit = 0;
    exit = parser(argc, argv, &flagers);
     while (optind < argc) {
        exit = reader(argv, &flagers);
        optind++;
    }
    return exit;
}

    int parser(int argc, char *argv[], flags *flagers) {
        int ex = 0;
        int count;
        int index = 0;
        static struct option long_opt[] = {
                {"number-nonblank", 0, 0, 'b'},
                {"number", 0, 0, 'n'},
                {"squeeze-blank", 0, 0, 's'},
                {0, 0, 0, 0},
        };
        while ((count = getopt_long(argc, argv,
                                    "bEnsTvet", long_opt, &index)) != -1) {
            switch (count) {
                case 'b':
                    flagers->b = 1;
                    break;
                case 'n':
                    flagers->n = 1;
                    break;
                case 's':
                    flagers->s = 1;
                    break;
                case 'e':
                    flagers->e = flagers->v = 1;
                    break;
                case 't':
                    flagers->t = flagers->v = 1;
                    break;
                case 'v':
                    flagers->v = 1;
                    break;
              case 'E':
                    flagers->e = 1;
                    break;
               case 'T':
                    flagers->t = 1;
                    break;
                default: fprintf(stderr, "usage: cat [-benstuv] [fp ...]");
                    ex = 1;
                break;
            }
        }
        return ex;
    }

int reader(char *argv[], flags *flagers) {
    FILE *fp;
    int x = 0;

    fp = fopen(argv[optind], "r");

    if (fp != NULL) {
        int count = 1;
        int empty = 0;
        int fut = '\n';
        int now;

        while ((now = fgetc(fp)) != EOF) {
            if (flagers->b && flagers->n) {
                flagers->n = 0;
            }
            if (flagers->s && now == '\n' && fut == '\n') {
                empty++;
                if (empty > 1) {
                    continue;
                }
            } else {
                empty = 0;
            }
            if (flagers->n && fut == '\n') {
                printf("%6d\t", count++);
            }
            if (flagers->b && now != '\n' && fut == '\n') {
                printf("%6d\t", count++);
            }
            if (flagers->t && now == '\t') {
                printf("^");
                now = 'I';
            }
            if (flagers->e && now == '\n') {
                printf("$");
            }
            if (flagers->v) {
                if ((now >= 0 && now < 9)
                || (now > 10 && now < 32) || now == 127) {
                    if (now == 127) {
                        printf("^?");
                        fut = now;
                        continue;
                    } else {
                        printf("^");
                        now += 64;
                    }
                }
            }
            printf("%c", now);
            fut = now;
        }
        fclose(fp);
    } else {
        x = -1;
    }
    return x;
}
