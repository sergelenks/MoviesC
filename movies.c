#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie {
    char* title;
    int year;
    char* languages;
    double rating;
    struct movie* next;
};
