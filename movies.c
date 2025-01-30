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
    strcpy(nmovie->languages, languages);
    
    movie->year = year;
    movie->rating = rating;
    movie->next = NULL;
    return movie;
}

int main (int argc, char **argv){
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}