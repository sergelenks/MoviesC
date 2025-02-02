#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie* createMovie(char* title, int year, char* languages, double rating);
struct movie* processInputFile(char* filePath);
void bySpecifiedYear(struct movie* list);
void byHighestRating(struct movie* list);
void byLanguage(struct movie* list);

struct movie {
    char* title;
    int year;
    char* languages;
    double rating;
    struct movie* next;
};


int main (int argc, char *argv[]){
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        return EXIT_FAILURE;
    }

    struct movie* movies = processInputFile(argv[1]);
    if (movies == NULL) { return 1; }

    int choice;
    do {
        printf("\n1. Show movies released in the specified year\n");
        printf("2. Show highest rated movie for each year\n");
        printf("3. Show the title and year of release of all movies in a specific language\n");
        printf("4. Exit from the program\n");
        printf("\nEnter a choice from 1 to 4: ");
        
        scanf("%d", &choice);
        while (getchar() != '\n');  

        switch (choice) {
            case 1:
                bySpecifiedYear(movies);
                break;
            case 2:
                byHighestRating(movies);
                break;
            case 3:
                byLanguage(movies);
                break;
            case 4:
                printf("Exiting program, bye for now\n");
                break;
            default:
                printf("You entered an incorrect choice. Try again.\n");
        }
    } while (choice != 4);

    struct movie* current = movies;
    while (current != NULL) {
        struct movie* temp = current;
        current = current->next;
        free(temp->title);
        free(temp->languages);
        free(temp);
    }

    return EXIT_SUCCESS;
}

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

void bySpecifiedYear(struct movie* list) {
    if (list == NULL) {
        printf("Data unavailable\n");
        return;
    }

    int year;
    printf("Enter the year for which you want to see movies: ");
    scanf("%d", &year);
    while (getchar() != '\n');  

    struct movie* current = list;
    int count = 0;
    
    while (current != NULL) {
        if (current->year == year) {
            printf("%d. %s\n", ++count, current->title);
        }
        current = current->next;
    }
    
    if (count == 0) {
        printf("No data about movies released in the year %d\n", year);
    }
}

void byHighestRating(struct movie* list) {
    if (list == NULL) {
        printf("Data unavailable\n");
        return;
    }

    struct movie* current = list;
    int lastYear = -1; 
    
    while (current != NULL) {
        if (current->year != lastYear) {
            float rating = current->rating;
            char* title = current->title;
            
            struct movie* temp = current->next;
            while (temp != NULL) {
                if (temp->year == current->year && temp->rating > rating) {
                    rating = temp->rating;
                    title = temp->title;
                }
                temp = temp->next;
            }
            
            printf("%d %.1f %s\n", current->year, rating, title);
            lastYear = current->year;
        }
        current = current->next;
    }
}

void byLanguage(struct movie* list) {
    if (list == NULL) {
        printf("Data unavailable\n");
        return;
    }

    char language[50];
    printf("Enter the language for which you want to see movies: ");
    scanf("%s", language);
    while (getchar() != '\n');

    struct movie* current = list;
    int count = 0;

    while (current != NULL) {
        if (strstr(current->languages, language) != NULL) {
            printf("%d %s\n", current->year, current->title);
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("No data about movies released in %s\n", language);
    }
}
