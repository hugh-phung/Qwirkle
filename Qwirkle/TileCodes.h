#include <iostream>

#ifndef ASSIGN1_TILECODES_H
#define ASSIGN1_TILECODES_H

//Represnts an invalid number used in the game
#define INVALID_NUM -1

// Tilebag
#define TILE_SET 1
#define MAX_COLOURS 6
#define MAX_SHAPES 6
#define MAX_TILES (MAX_COLOURS * MAX_SHAPES)

// Colours
#define RED    'R'
#define ORANGE 'O'
#define YELLOW 'Y'
#define GREEN  'G'
#define BLUE   'B'
#define PURPLE 'P'

// Shapes
#define CIRCLE    1
#define STAR_4    2
#define DIAMOND   3
#define SQUARE    4
#define STAR_6    5
#define CLOVER    6

// Colour codes
#define RED_COLOUR "\u001b[31m"
#define ORANGE_COLOUR "\u001b[38;5;202m"
#define YELLOW_COLOUR "\u001b[33m"
#define GREEN_COLOUR "\u001b[32m"
#define BLUE_COLOUR "\u001b[34m"
#define PURPLE_COLOUR "\u001b[38;5;92m"
#define RESET_COLOUR "\u001b[0m"

const char colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};

const int shapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

#endif // ASSIGN1_TILECODES_H

