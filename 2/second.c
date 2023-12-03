#include <stdio.h.>
#include <stdlib.h>
#include <string.h>

typedef enum {
    RED,
    GREEN,
    BLUE
} Color;

const char * const color_str[] =
{
    [RED] = "red",
    [GREEN] = "green",
    [BLUE]  = "blue"
};

typedef struct {
    int count;
    Color color;
} balls_shown;

typedef struct {
    int num_of_balls_showings;
    balls_shown *balls;
} sequence;

typedef struct {
    int id;
    int num_of_sequences;
    sequence *sequences;
} game;

game* parse_game(char *line, size_t len) {
    game *result = (game*) malloc(sizeof(game));
    int i = 0;

    result->id = atoi(line + 5);
    while(line[i] != ':') {
        ++i;
    }
    i += 1;
    int first_sequence_start = i;
    result->num_of_sequences = 1;
    for(size_t j = first_sequence_start; j < len; ++j) {
        if(line[j] == ';') {
            ++result->num_of_sequences;
        }
    }

    result->sequences = (sequence*) malloc(result->num_of_sequences * sizeof(sequence));
    for(int j = 0; j < result->num_of_sequences; ++j) {
        result->sequences[j].num_of_balls_showings = 1;
        for(int k = i; k < len && line[k] != ';'; ++k) {
            if(line[k] == ',') {
                ++result->sequences[j].num_of_balls_showings;
            }
        }
        result->sequences[j].balls = (balls_shown*) malloc(result->sequences[j].num_of_balls_showings * sizeof(balls_shown));
        for(int k = 0; k < result->sequences[j].num_of_balls_showings; ++k) {
            while(line[i] > '9' || line[i] < '0') {
                ++i;
            }
            result->sequences[j].balls[k].count = atoi(line + i);
            while(line[i] < 'a' || line[i] > 'z') {
                ++i;
            }
            switch(line[i]) {
                case 'r':
                    result->sequences[j].balls[k].color = RED;
                    break;
                case 'b':
                    result->sequences[j].balls[k].color = BLUE;
                    break;
                case 'g':
                    result->sequences[j].balls[k].color = GREEN;
                    break;
            }
        }
        while(i < len && line[i] != ';') {
            ++i;
        }
        i += 1;
    }

    return result;
}

void free_game(game *game) {
    if(game != NULL) {
        for(int i = 0; i < game->num_of_sequences; ++i) {
            free(game->sequences->balls);
        }
        free(game->sequences);
        free(game);
    }
}

int power_number(game *game) {
    int max_blue = 0;
    int max_red = 0;
    int max_green = 0;
    for(int i = 0; i < game->num_of_sequences; ++i) {
        for(int j = 0; j < game->sequences[i].num_of_balls_showings; ++j) {
            balls_shown balls = game->sequences[i].balls[j];
            if(balls.color == RED && balls.count > max_red) {
                max_red = balls.count;
            } else if(balls.color == BLUE && balls.count > max_blue) {
                max_blue = balls.count;
            } else if(balls.color == GREEN && balls.count > max_green) {
                max_green = balls.count;
            }
        }
    }
    return max_blue * max_red * max_green;
}

int main() {
    FILE *input = fopen("input/input.txt", "r");
    if(input == NULL) {
        perror("Unable to open a file");
        exit(1);
    }
    game c;
    char *line = NULL;
    size_t len = 0;
    size_t nread;
    int sum = 0;
    while((nread = getline(&line, &len, input)) != -1) {
        game *current_game = parse_game(line, nread);
        sum += power_number(current_game);
        free_game(current_game);
    }

    printf("%d", sum);
    free(line);
    fclose(input);
}