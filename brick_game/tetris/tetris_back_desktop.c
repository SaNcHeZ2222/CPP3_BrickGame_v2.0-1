#include "tetris_back_desktop.h"

static GameInfo_t infoGame;

static figureInfo infoCurrentFigure;

static flagInfo flagInfoGame;

int getRandNum() {
  srand(time(0));
  int res = rand() % 8;
  if (res >= 7) res = 6;
  return res;
}

int checkAddNewFigure() {
  int out = 1;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][0] + 2;
    int y =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][1] +
        infoCurrentFigure.shiftHorizon;
    if (infoGame.field[x][y] != 0) out = 0;
  }
  return out;
}

void addFigure(int number) {
  infoCurrentFigure.number = number;
  infoCurrentFigure.rotation = 0;
  infoCurrentFigure.shiftVertical = 0;
  infoCurrentFigure.shiftHorizon = 4;
  flagInfoGame.flagGo = checkAddNewFigure();
  if (flagInfoGame.flagGo != 0 && flagInfoGame.flagGo != -1) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      int x =
          figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][0];
      int y =
          figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][1] +
          infoCurrentFigure.shiftHorizon;
      infoGame.field[x][y] = number + 1;
    }
  }
}

void deleteCurrentFigure() {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][0] +
        infoCurrentFigure.shiftVertical;
    int y =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][1] +
        infoCurrentFigure.shiftHorizon;
    infoGame.field[x][y] = 0;
  }
}

int checkСollisionVertical() {
  int out = 1;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][0] +
        infoCurrentFigure.shiftVertical + 1;
    int y =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][1] +
        infoCurrentFigure.shiftHorizon;

    if (!(x < 20 && x >= 0 && y < 10 && y >= 0 && infoGame.field[x][y] == 0)) {
      out = 0;
      break;
    }
  }
  infoCurrentFigure.shiftVertical += out;
  return out;
}

void checkСollisionRotation() {
  int out = 1;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = figures[infoCurrentFigure.number]
                   [(infoCurrentFigure.rotation + 1) % 4][i][0] +
            infoCurrentFigure.shiftVertical;
    int y = figures[infoCurrentFigure.number]
                   [(infoCurrentFigure.rotation + 1) % 4][i][1] +
            infoCurrentFigure.shiftHorizon;

    if (!(x < 20 && x >= 0 && y < 10 && y >= 0 && infoGame.field[x][y] == 0)) {
      out = 0;
    }
  }
  infoCurrentFigure.rotation = (infoCurrentFigure.rotation + out) % 4;
}

void checkСollisionHorizon(UserAction_t action) {
  int currentShift;
  if (action == Right)
    currentShift = 1;
  else
    currentShift = -1;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][0] +
        infoCurrentFigure.shiftVertical;
    int y =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][1] +
        infoCurrentFigure.shiftHorizon + currentShift;

    if (!(x < 20 && x >= 0 && y < 10 && y >= 0 && infoGame.field[x][y] == 0)) {
      currentShift = 0;
    }
  }
  infoCurrentFigure.shiftHorizon += currentShift;
}

void shiftCurrent(UserAction_t action) {
  deleteCurrentFigure();

  int checkСollision = 1;
  if (action == Down || action == Action)
    checkСollision = checkСollisionVertical();
  else if (action == Left || action == Right)
    checkСollisionHorizon(action);
  else if (action == Up)
    checkСollisionRotation();
  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][0] +
        infoCurrentFigure.shiftVertical;
    int y =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][1] +
        infoCurrentFigure.shiftHorizon;
    infoGame.field[x][y] = infoCurrentFigure.number + 1;
  }
  if (checkСollision == 0) flagInfoGame.flagAddNewFigure = 1;
}

UserAction_t translateKeyToAction(int key) {
  UserAction_t action;
  if (key == 'q' || key == 'Q')
    action = Terminate;
  else if (key == ' ')
    action = Start;
  else if (key == 'p' || key == 'P')
    action = Pause;
  else if (key == 'a' || key == 'A' || key == KEY_LEFT)
    action = Left;
  else if (key == 'd' || key == 'D' || key == KEY_RIGHT)
    action = Right;
  else if (key == 'w' || key == 'W' || key == KEY_UP)
    action = Up;
  else if (key == 's' || key == 'S' || key == KEY_DOWN)
    action = Down;
  else
    action = Action;
  return action;
}

void removeFullLine(int indexLine) {
  for (int i = indexLine - 1; i >= 0; i--) {
    for (int j = 0; j < N; j++) {
      infoGame.field[i + 1][j] = infoGame.field[i][j];
    }
  }
}

GameInfo_t updateCurrentState() { return infoGame; }

void updateHighScore() {
  FILE *file = fopen("highScore.txt", "r");
  if (file != NULL) {
    int number = 0;
    fscanf(file, "%d", &number);
    fclose(file);
    if (infoGame.score > number) {
      file = fopen("highScore.txt", "w");
      if (file != NULL) {
        fprintf(file, "%d", infoGame.score);
        fclose(file);
      }
    }
  }
}

void updateGameInfoHighScoreTetris(int score) { infoGame.high_score = score; }

void checkLine() {
  int sumDel = 0;
  for (int i = 0; i < M; i++) {
    int flag = 1;
    for (int j = 0; j < N; j++) {
      if (infoGame.field[i][j] == 0) flag = 0;
    }
    if (flag) {
      removeFullLine(i);
      sumDel = sumDel * 2 + 100;
    }
  }
  infoGame.score += sumDel;
  updateHighScore();
  infoGame.level = 1 + infoGame.score / 600;

  if (infoGame.level > 10) infoGame.level = 10;

  infoGame.speed = 150 * infoGame.level;
}

void userInput(UserAction_t action) {
  if (action == Terminate) {
    flagInfoGame.flagGo = -1;
  }

  else if (action == Start) {
    flagInfoGame.flagGame = 1;
    flagInfoGame.statusGame = 1;
    infoGame.pause = 0;
  } else if (action == Pause) {
    flagInfoGame.flagGame = 0;
    flagInfoGame.statusGame = 2;
    infoGame.pause = 1;

  } else if (action != Action && flagInfoGame.flagGame == 1 &&
             flagInfoGame.statusGame == 1)
    shiftCurrent(action);

  if (flagInfoGame.flagAddNewFigure == 1 && flagInfoGame.flagGame == 1) {
    int numberNewFigure = infoGame.next;
    checkLine();
    addFigure(numberNewFigure);
    infoGame.next = getRandNum();
    flagInfoGame.flagAddNewFigure = 0;
  }
}

void clearTable() {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      infoGame.field[i][j] = 0;
    }
  }
}

void updateInfoGameScore(int score) { infoGame.score = score; }

void updateInfoGameHighScore(int score) { infoGame.high_score = score; }

void updateInfoGameLevel(int level) { infoGame.level = level; }

void updateInfoGameSpeed(int speed) { infoGame.speed = speed; }

void updateInfoGameCurrent(int current) { infoGame.current = current; }

void updateInfoGameNext(int next) { infoGame.next = next; }

GameInfo_t getInfoGame() { return infoGame; }

void updateFlagInfoGo(int newFlagGo) { flagInfoGame.flagGo = newFlagGo; }

void updateFlagInfoStatus(int newFlagStatus) {
  flagInfoGame.statusGame = newFlagStatus;
}

void updateFlagInfoGame(int newFlagGame) {
  flagInfoGame.flagGame = newFlagGame;
}

void updateFlagNewFigure(int newFlagNewFigure) {
  flagInfoGame.flagAddNewFigure = newFlagNewFigure;
}

void updateGameInfoPauseTetris(int newPause) { infoGame.pause = newPause; }

flagInfo getFlagInfo() { return flagInfoGame; }
