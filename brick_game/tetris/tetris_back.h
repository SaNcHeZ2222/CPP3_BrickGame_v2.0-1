#ifndef TETRIS_BACK
#define TETRIS_BACK

#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>



#define N 20
#define M 20

#define NUM_FIGURES 7
#define NUM_ROTS 4
#define FIGURE_SIZE 8
#define NUM_COORDS 2


typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef struct {
    int field[M][N];
    int current;
    int next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause; 
} GameInfo_t;

typedef struct 
{
    int number;
    int rotation;
    int shiftHorizon;
    int shiftVertical;
} figureInfo;




int getRandNum();

int updateFlagGo();

int updateFlagGame();

GameInfo_t updateCurrentState();

int updateStatusGame();

void deleteCurrentFigure();

int checkСollisionVertical();

void checkСollisionRotation();

void checkСollisionHorizon(UserAction_t action);

void shiftCurrent(UserAction_t action);

UserAction_t translateKeyToAction(int key);

void removeFullLine(int indexLine);

void updateHighScore();

void checkLine();

void userInput(UserAction_t action);

void initColor();

void clearTable();

void updateInfoGameScore(int score);

void updateInfoGameLevel(int level);

void updateInfoGameSpeed(int speed);

void updateInfoGameCurrent(int current);

void updateInfoFlagGame(int flagGameNew);

void updateInfoStatusGame(int statusGameNew);

void updateInfoflagGo(int flagGoNew);

void updateInfoGameNext(int next);

GameInfo_t getInfoGame();

#endif