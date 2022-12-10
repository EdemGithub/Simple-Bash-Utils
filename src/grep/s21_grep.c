// Copyright 2022 Handehig
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <getopt.h>

struct flags {
    int e, i, v, c, l, n;
};

int parsing(int argc, char *argv[], struct flags *flagers, char *pattern);
void grep(struct flags *flagers, int argc, char **argv, char *temp);

int main(int argc, char *argv[]) {
    struct flags flagers = {};
    int exit = 0;
    char pattern[1024] = {'\0'};
    exit = parsing(argc, argv, &flagers, pattern);
    if ((argc >= 3) && exit != 1) {
        grep(&flagers, argc, argv, pattern);
    }
    return exit;
}

int parsing(int argc, char *argv[], struct flags *flagers, char *pattern) {
    int i = 0, result = 0;
    char temp[2056] = {'\0'};
    while ((i = getopt_long(argc, argv, "e:ivcln", 0, 0)) != -1) {
        switch (i) {
            case 'e':
                strcpy(temp, pattern);
                flagers->e = 1;
                sprintf(pattern, "%s%s%s", temp,
                        *pattern == '\0' ? "\0" : "|", optarg);
                break;
            case 'i':
                flagers->i = 1;
                break;
            case 'v':
                flagers->v = 1;
                break;
            case 'c':
                flagers->c = 1;
                break;
            case 'l':
                flagers->l = 1;
                break;
            case 'n':
                flagers->n = 1;
                break;
            default:
                fprintf(stderr, "usage: grep");
                result = 1;
                break;
        }
    }
    return result;
}

void grep(struct flags *flagers, int argc, char **argv, char *temp) {
    char mass[1024] = {0};
    char *filename[1024] = {'\0'};

    if (flagers != NULL && !flagers->e) {
        sprintf(mass, "%s", argv[optind++]);
    }
    if (flagers != NULL && flagers->e) {
        sprintf(mass, "%s", temp);
    }

    for (int i = optind, countFile = 0; i < argc; i++, countFile++) {
        filename[countFile] = &argv[i][0];
    }
    for (int i = 0; filename[i]; i++) {
    }
    int yo = 0;
    for (int i = optind; i < argc; i++) {
        regex_t reg;
        FILE *fp;
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
        } else {
            regcomp(&reg, mass, (flagers != NULL && flagers->i == 1) ?
                                REG_ICASE | REG_EXTENDED : REG_EXTENDED);
            char text[1024] = {0};
            regmatch_t pmatch[1];
            int matches = 0, fut = 1;
            while (fgets(text, 1024, fp) != NULL) {
                int status = regexec(&reg, text, 1, pmatch, 0);
                int match = 0;
                if (!status && flagers->v == 0) match = 1;
                if (status == REG_NOMATCH && flagers->v) match = 1;
                if (match && !flagers->l && !flagers->c
                    && !flagers->n && !flagers) {
                    printf("%d:", fut);
                }
                if (match && !flagers->l && !flagers->c) {
                    if (filename[1] != NULL) {
                        printf("%s:", filename[yo]);
                        if (flagers->n) printf("%d:", fut);
                    }
                    if (flagers->n && !flagers->v) printf("%d:", fut);
                    printf("%s", text);
                }
                matches += match;
                fut++;
                if (strchr(text, '\n') == NULL &&
                    !feof(fp)) printf("\n");
            }

            if (flagers->l && flagers->c) {
                if (filename[1] != NULL) {
                    printf("%s:", filename[yo]);
                    if (matches > 0) {
                        printf("%d", 1);
                    } else {
                        printf("%d", matches);
                    }
                    printf("\n");
                }
            }
            if (flagers->l && matches > 0) printf("%s\n", argv[i]);
            if (flagers->c && !flagers->l) {
                if (filename[1] != NULL) printf("%s:", filename[yo]);
                printf("%d\n", matches);
            }
            regfree(&reg);
            fclose(fp);
        }
        yo++;
    }
}

