#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <ncurses.h>

char** mapGen(int x, int y)
{
    int i, j;

    // create array of length x
    char **map = malloc(sizeof(char *) * y);

    // allocate the y direction
    for (i = 0; i < y; i++)
      map[i] = malloc(sizeof(char) * x);

    // populate the array
    for (i = 0; i < y; i++)
    {
        for (j = 0; j < x; j++)
          map[i][j] = '.';
    }

    return map;
}

void printMap(char **map, int x, int y)
{
    int i, j;

    // print map to screen
    for (i = 0; i < y; i++)
    {
        for (j = 0; j < x; j++)
          printw("%c ", map[i][j]);

        printw("\n");
    }
}

char** destroyMap(char **map, int y)
{
    int i;

    if (map == NULL)
      return NULL;

    // destroy every chunk of dynamic memory
    for (i = 0; i < y; i++)
      free(map[i]);

    // free the pointer layer
    free(map);

    return NULL;
}

player* initPlayer(char **map, int x, int y)
{
    // allocate space for new player struct
    player *hero = malloc(sizeof(player));

    // initialize player attributes
    hero->x = 0;
    hero->y = 0;
    hero->symbol = '@';

    // put the player on the map
    map[x][y] = hero->symbol;

    // return the dynamic player variable
    return hero;
}

player* destroyPlayer(player *character)
{
    if (character == NULL)
      return NULL;

    // deallocate dynmaic player memory
    free(character);

    return NULL;
}

void redraw(player *character, char **map, int x, int y)
{
    int exitFlag = 1, ch;

    // initialize screen using ncurses
    initscr();

    // stops the input characters from being printed to the screen
    noecho();

    // Allow special keys to be read
    keypad(stdscr, TRUE);

    // print map to screen
    printMap(map, x, y);

    while (exitFlag)
    {
        // get user input
        ch = getch();

        // check for appropriate command
        if (ch == KEY_LEFT)
        {
            // erase character from current tile
            map[character->x][character->y] = '.';

            // calculate next position
            character->y -= 1;
            map[character->x][character->y] = character->symbol;

            // update screen
            clear();

            // reprint the map
            printMap(map, x, y);
        }
        else if (ch == KEY_RIGHT)
        {
            // erase character from current tile
            map[character->x][character->y] = '.';

            // calculate next position
            character->y += 1;
            map[character->x][character->y] = character->symbol;

            // update screen
            clear();

            // reprint the map
            printMap(map, x, y);
        }
        else if (ch == KEY_UP)
        {
            // erase character from current tile
            map[character->x][character->y] = '.';

            // calculate next position
            character->x -= 1;
            map[character->x][character->y] = character->symbol;

            // update screen
            clear();

            // reprint the map
            printMap(map, x, y);
        }
        else if (ch == KEY_DOWN)
        {
            // erase character from current tile
            map[character->x][character->y] = '.';

            // calculate next position
            character->x += 1;
            map[character->x][character->y] = character->symbol;

            // update screen
            clear();

            // reprint the map
            printMap(map, x, y);
        }
        else if (ch == KEY_BACKSPACE) // Exit case (pressing backspace)
          exitFlag = 0;
    }

    // clear screen
    clear();

    // exit message
    printw("\nExiting Game\n");

    // close screen
    endwin();

    // Exit the function
    return;
}

int main(int argc, char **argv)
{
    int x, y;

    x = atoi(argv[1]);
    y = atoi(argv[2]);

    printf("your entered (x, y): %d %d\n", x, y);

    char **map = mapGen(x, y);
    player *hero = initPlayer(map, 0, 0);
    redraw(hero, map, x, y); // movement driver
    hero = destroyPlayer(hero);
    map = destroyMap(map, y);

    return 0;
}
