#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

typedef struct player
{
    int x;
    int y;
    char symbol;
} player;

void printMap(char **map, int x, int y);

char** mapGen(int x, int y);

char** destroyMap(char **map, int y);

player* initPlayer(char **map, int x, int y);

player* destroyPlayer(player *character);

void redraw(player *character, char **map, int x, int y);

#endif
