#include "snakegame_back.h"

static int gameType;

static GameInfoSnake gameInfo;

static FlagInfoSnake flagInfo;

void updateGameInfoScore(int newScore) { gameInfo.score = newScore; }

void updateGameInfoHighScore(int newHighScore) {
  gameInfo.high_score = newHighScore;
}

void updateGameInfoSpeed(int newSpeed) { gameInfo.speed = newSpeed; }

void updateGameInfoLevel(int newLevel) { gameInfo.level = newLevel; }

void updateGameInfoPause(int newPause) { gameInfo.pause = newPause; }

void updateGameInfoSnakeSize(int newSize) { gameInfo.snakeSize = newSize; }

GameInfoSnake getGameInfoSnake() { return gameInfo; }

void updateGameInfoSnakeX(int newValue, int index) {
  gameInfo.snakeX[index] = newValue;
}

void addSnakeSegment() {
  gameInfo.snakeSize++;
  gameInfo.snakeX[gameInfo.snakeSize - 1] =
      gameInfo.snakeX[gameInfo.snakeSize - 2];
  gameInfo.snakeY[gameInfo.snakeSize - 1] =
      gameInfo.snakeY[gameInfo.snakeSize - 2];
}

void updateScoreSnake() {
  gameInfo.score++;
  if (gameInfo.score > gameInfo.level * 10) {
    gameInfo.level++;
    if (gameInfo.level >= 10) gameInfo.level = 10;
    gameInfo.speed += 50;
  }
}

void checkCollisionBack() {
  // Check if the snake has collided with the wall
  if (gameInfo.snakeX[0] < 0 || gameInfo.snakeX[0] >= 10 ||
      gameInfo.snakeY[0] < 0 || gameInfo.snakeY[0] >= 20) {
    flagInfo.flagGame = 0;
    flagInfo.statusGame = -2;
    flagInfo.flagGo = 1;
  }
  // Check if the snake has collided with itself
  for (int i = 1; i < gameInfo.snakeSize; i++) {
    if (gameInfo.snakeX[0] == gameInfo.snakeX[i] &&
        gameInfo.snakeY[0] == gameInfo.snakeY[i]) {
      flagInfo.flagGame = 0;
      flagInfo.statusGame = -2;
      flagInfo.flagGo = 1;
    }
  }
  // Check if the snake has eaten food
  if (gameInfo.snakeX[0] == gameInfo.foodX &&
      gameInfo.snakeY[0] == gameInfo.foodY) {
    addSnakeSegment();
    gameInfo.foodX = rand() % 10;
    gameInfo.foodY = rand() % 20;
    updateScoreSnake();
  }

  if (gameInfo.snakeSize == winDigit) {
    flagInfo.flagGame = 2;
    flagInfo.statusGame = -3;
  }
}

void checkCollisionBackConsole() {
  // Check if the snake has collided with the wall
  if (gameInfo.snakeX[0] < 0 || gameInfo.snakeX[0] >= 20 ||
      gameInfo.snakeY[0] < 0 || gameInfo.snakeY[0] >= 20) {
    flagInfo.flagGame = 0;
    flagInfo.statusGame = -2;
    flagInfo.flagGo = 1;
  }
  // Check if the snake has collided with itself
  for (int i = 1; i < gameInfo.snakeSize; i++) {
    if (gameInfo.snakeX[0] == gameInfo.snakeX[i] &&
        gameInfo.snakeY[0] == gameInfo.snakeY[i]) {
      flagInfo.flagGame = 0;
      flagInfo.statusGame = -2;
      flagInfo.flagGo = 1;
    }
  }
  // Check if the snake has eaten food
  if (gameInfo.snakeX[0] == gameInfo.foodX &&
      gameInfo.snakeY[0] == gameInfo.foodY) {
    addSnakeSegment();
    gameInfo.foodX = rand() % 20;
    gameInfo.foodY = rand() % 20;
    updateScoreSnake();
  }

  if (gameInfo.snakeSize == winDigit) {
    flagInfo.flagGame = 0;
    flagInfo.statusGame = -3;
  }
}

int getGameType() { return gameType; }
void updateGameType(int newType) { gameType = newType; }

FlagInfoSnake getFlagInfoSnake() { return flagInfo; }

void userInputSnake(UserActionSnake action) {
  if (action == StartSnake) {
    if (gameType == 1)
      flagInfo.statusGame = 0;
    else {
      flagInfo.statusGame = 1;
      flagInfo.flagGo = 1;
    }

    flagInfo.flagGo = 0;

  } else if (action == PauseSnake) {
    flagInfo.statusGame = 0;
    flagInfo.flagGo = 5;
  } else if (action == TerminateSnake) {
    flagInfo.flagGame = 0;
    flagInfo.flagGo = -1;
  }
}

void moveSnakeBack(UserActionSnake direction) {
  for (int i = gameInfo.snakeSize - 1; i > 0; i--) {
    gameInfo.snakeX[i] = gameInfo.snakeX[i - 1];
    gameInfo.snakeY[i] = gameInfo.snakeY[i - 1];
  }

  if (direction == UpSnake) {
    gameInfo.snakeY[0]--;
  } else if (direction == DownSnake) {
    gameInfo.snakeY[0]++;
  } else if (direction == LeftSnake) {
    gameInfo.snakeX[0]--;
  } else if (direction == RightSnake) {
    gameInfo.snakeX[0]++;
  }
}

UserActionSnake translateKeyToActionSnake(int key) {
  UserActionSnake action;
  if (key == 'q' || key == 'Q')
    action = TerminateSnake;
  else if (key == ' ')
    action = StartSnake;
  else if (key == 'p' || key == 'P')
    action = PauseSnake;
  else if (key == 'a' || key == 'A')
    action = LeftSnake;
  else if (key == 'd' || key == 'D')
    action = RightSnake;
  else if (key == 'w' || key == 'W')
    action = UpSnake;
  else if (key == 's' || key == 'S')
    action = DownSnake;
  else
    action = ActionSnake;
  return action;
}

void updateFlagInfoGameSnake(int newFlag) { flagInfo.flagGame = newFlag; }

void clearTableSnake() {
  for (int i = 0; i < 200; i++) {
    gameInfo.snakeX[i] = 0;
    gameInfo.snakeY[i] = 0;
  }
}

void clearTableSnakeCli() {
  for (int i = 0; i < 400; i++) {
    gameInfo.snakeX[i] = 0;
    gameInfo.snakeY[i] = 0;
  }
}

void startSettingSnake() {
  // statusGame = 1 Play
  // statusGame = 0 Pause
  // statusGame = 2 GameOver

  // flagGame = 0 GameOver
  // flagGame = 1 Play
  // flagGame = 2 Win

  FILE *file = fopen("gui/cli/highscoreSnake.txt", "r");
  if (file != NULL) {
    int number = 0;
    fscanf(file, "%d", &number);
    fclose(file);

    gameInfo.high_score = number;
  }

  updateGameInfoSnakeSize(4);
  updateGameInfoScore(0);
  updateGameInfoLevel(1);
  updateGameInfoSpeed(150);

  flagInfo.statusGame = 1;

  flagInfo.flagGame = 1;

  clearTableSnakeCli();

  gameInfo.snakeX[0] = 5;
  gameInfo.snakeY[0] = 5;

  gameInfo.snakeX[1] = 6;
  gameInfo.snakeY[1] = 5;

  gameInfo.snakeX[2] = 7;
  gameInfo.snakeY[2] = 5;

  gameInfo.snakeX[3] = 8;
  gameInfo.snakeY[3] = 5;

  gameInfo.foodX = rand() % 3;
  gameInfo.foodY = rand() % 20;
}

void updateFlagInfoStatusGameSnake(int newFlag) {
  flagInfo.statusGame = newFlag;
}

UserActionSnake getDirection() { return gameInfo.direction; }

void updateDirection(UserActionSnake newDir) { gameInfo.direction = newDir; }

void setScoreSnake(int newScore) { gameInfo.score = newScore; }

void setLevelSnake(int newLevel) { gameInfo.level = newLevel; }

void setSpeedSnake(int newSpeed) { gameInfo.speed = newSpeed; }

void setHighScoreSnake(int newHighScore) { gameInfo.high_score = newHighScore; }

void updateHighScoreSnake() {
  if (gameInfo.score > gameInfo.high_score)
    gameInfo.high_score = gameInfo.score;
  updateHighScoreSnakeFile();
}

void updateHighScoreSnakeFile() {
  FILE *file = fopen("gui/cli/highscoreSnake.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d", gameInfo.high_score);
    fclose(file);
  }
}
