#ifndef SNAKEGAME_BACK_H
#define SNAKEGAME_BACK_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
// #include <ncurses.h>


#define winDigit 20






#define N_SNAKE 10
#define M_SNAKE 20


typedef enum {
    StartSnake,
    PauseSnake,
    TerminateSnake,
    LeftSnake,
    RightSnake,
    UpSnake,
    DownSnake,
    ActionSnake
} UserActionSnake;

typedef struct {
    int snakeX[400];
    int snakeY[400];

    int foodX;
    int foodY;
    UserActionSnake direction;

    int snakeSize;
    int current;
    int next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause; 
} GameInfoSnake;


typedef struct {
    int statusGame;
    int flagGo;
    int flagAddNewFigure;
    int flagGame;
} FlagInfoSnake;

#ifdef __cplusplus
extern "C" {
#endif

int getGameType();
void updateGameType(int newType); 

void updateGameInfoScore(int newScore);

void updateGameInfoHighScore(int newHighScore);

void updateGameInfoSpeed(int newSpeed);

void updateGameInfoLevel(int newLevel);

void updateGameInfoPause(int newPause);

void updateGameInfoSnakeSize(int newSize);

GameInfoSnake getGameInfoSnake();

void updateGameInfoSnakeX(int newValue, int index);

void addSnakeSegment();

void updateScoreSnake();

FlagInfoSnake getFlagInfoSnake();

void moveSnakeBack(UserActionSnake direction);

void userInputSnake(UserActionSnake action);

void checkCollisionBack();

void updateFlagInfoGameSnake(int newFlag);

void clearTableSnake();
    

void startSettingSnake();


void updateFlagInfoStatusGameSnake(int newFlag);


UserActionSnake translateKeyToActionSnake(int key);

UserActionSnake getDirection();

void updateDirection(UserActionSnake newDir);

void setScoreSnake(int newScore);


void setLevelSnake(int newLevel);

void setSpeedSnake(int newSpeed);

void setHighScoreSnake(int newHighScore);

void checkCollisionBackConsole();

void updateHighScoreSnake();

void updateHighScoreSnakeFile();


#ifdef __cplusplus
}
#endif

#endif // SNAKEGAME_BACK_H