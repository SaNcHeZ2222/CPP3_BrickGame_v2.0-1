#ifndef TETRIS_BACK
#define TETRIS_BACK

#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10
#define M 20

#define NUM_FIGURES 7
#define NUM_ROTS 4
#define FIGURE_SIZE 4
#define NUM_COORDS 2


const int figures[NUM_FIGURES][NUM_ROTS][FIGURE_SIZE][NUM_COORDS] = {
    {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 1}, {1, 1}, {2, 1}, {3, 1}}},

    {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 0}}},

    {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
     {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},

    {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
     {{0, 1}, {0, 2}, {1, 1}, {1, 2}}},

    {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
     {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},

    {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 1}}},

    {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 0}},
     {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
     {{0, 1}, {1, 0}, {1, 1}, {2, 0}}}};

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

typedef struct 
{
    int statusGame;
    int flagGo;
    int flagAddNewFigure;
    int flagGame;
} flagInfo;



// static int statusGame = 0;

// static int flagGo = 1;

// static int flagAddNewFigure = 1;

// static int flagGame = 0;



// void setStartSetting() {
//   updateInfoGameScore(0);

//   updateInfoGameLevel(1);

//   updateInfoGameSpeed(200);

//   updateInfoGameNext(getRandNum());

//   updateInfoGameCurrent(getRandNum());
// }

// void updateFlagFoZero() {
//   updateInfoFlagGame(0);

//   updateInfoStatusGame(3);

//   updateInfoflagGo(1);
//   clearTable();
//   updateInfoGameScore(0);

//   updateInfoGameLevel(1);

//   updateInfoGameSpeed(200);
// }

void addFigure(int number);

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

void updateInfoGameHighScore(int score);

void updateInfoGameLevel(int level);

void updateInfoGameSpeed(int speed);

void updateInfoGameCurrent(int current);

void updateInfoFlagGame(int flagGameNew);

void updateInfoStatusGame(int statusGameNew);

void updateInfoflagGo(int flagGoNew);

void updateInfoGameNext(int next);

GameInfo_t getInfoGame();


void updateFlagInfoGo(int newFlagGo);

void updateFlagInfoStatus(int newFlagStatus);

void updateFlagInfoGame(int newFlagGame);

void updateFlagNewFigure(int newFlagNewFigure);

flagInfo getFlagInfo();

void updateGameInfoHighScoreTetris(int score);

void updateGameInfoPauseTetris(int newPause);

#endif