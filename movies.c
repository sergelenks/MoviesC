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

struct movie* createMovie(char* title, int year, char* languages, double rating) {
    struct movie* movie = malloc(sizeof(struct movie));
    
    movie->title = malloc(strlen(title) + 1);
    strcpy(movie->title, title);
    
    movie->languages = malloc(strlen(languages) + 1);
    strcpy(movie->languages, languages);
    
    movie->year = year;
    movie->rating = rating;
    movie->next = NULL;
    return movie;
}

struct movie* processInputFile(char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("File cannot be opened, filepath is:  %s\n", filePath);
        return NULL;
    }

    struct movie* head = NULL;
    char* token;
    char* line = NULL;
    size_t length = 0;
    int count = 0;
    ssize_t check;

    getline(&line, &length, file);

    while ((check = getline(&line, &length, file)) != -1) {
        token = strtok(line, ",");
        char* title = malloc(strlen(token) + 1);
        strcpy(title, token);

        token = strtok(NULL, ",");
        int year = atoi(token);

        token = strtok(NULL, ",");
        char* languages = malloc(strlen(token) + 1);
        strcpy(languages, token);

        token = strtok(NULL, "\n");
        double rating = strtod(token, NULL);

        struct movie* newMovie = createMovie(title, year, languages, rating);
        newMovie->next = head;
        head = newMovie;
        count++;

        free(title);
        free(languages);
    }

    printf("Processed file %s and parsed data for %d movies\n", filePath, count);
    free(line);
    fclose(file);
    return head;
}

int main (int argc, char *argv[]){
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        return EXIT_FAILURE;
    }

    struct movie* list = processInputFile(argv[1]);
    if (list == NULL) { return 1; }


    return EXIT_SUCCESS;
}