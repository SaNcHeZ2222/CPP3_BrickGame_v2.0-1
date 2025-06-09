#include "tetris_back.h"

static int statusGame = -1;

static int flagGo = 1;

static int flagAddNewFigure = 1;

static int flagGame = 0;

static GameInfo_t infoGame;

static figureInfo infoCurrentFigure;

static const int figures[NUM_FIGURES][NUM_ROTS][FIGURE_SIZE][NUM_COORDS] = {
    {{{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}},
     {{0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 2}, {2, 3}, {3, 2}, {3, 3}},
     {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7}},
     {{0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 2}, {2, 3}, {3, 2}, {3, 3}}},
    {{{0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
     {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {2, 2}, {2, 3}},
     {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 4}, {2, 5}},
     {{0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}}},
    {{{0, 4}, {0, 5}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
     {{0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 2}, {2, 3}, {2, 4}, {2, 5}},
     {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 0}, {2, 1}},
     {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 2}, {2, 3}}},
    {{{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
     {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
     {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
     {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 2}, {1, 3}, {1, 4}, {1, 5}}},
    {{{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 2}, {2, 3}},
     {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 0}, {1, 1}, {1, 2}, {1, 3}},
     {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 2}, {2, 3}}},
    {{{0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
     {{0, 2}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 2}, {2, 3}},
     {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 2}, {2, 3}},
     {{0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 2}, {2, 3}}},
    {{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
     {{0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}},
     {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {1, 5}},
     {{0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}}}};

static GameInfo_t infoGame;

int getRandNum() {
  srand(time(0));
  int res = rand() % 8;
  if (res >= 7) res = 6;
  return res;
}

int checkAddNewFigure() {
  int out = 1;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][0];
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
  flagGo = checkAddNewFigure();
  if (flagGo != 0 && flagGo != -1) {
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

    if (!(x < 20 && x >= 0 && y < 20 && y >= 0 && infoGame.field[x][y] == 0)) {
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

    if (!(x < 20 && x >= 0 && y < 20 && y >= 0 && infoGame.field[x][y] == 0)) {
      out = 0;
    }
  }
  infoCurrentFigure.rotation = (infoCurrentFigure.rotation + out) % 4;
}

void checkСollisionHorizon(UserAction_t action) {
  int currentShift;
  if (action == Right)
    currentShift = 2;
  else
    currentShift = -2;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][0] +
        infoCurrentFigure.shiftVertical;
    int y =
        figures[infoCurrentFigure.number][infoCurrentFigure.rotation][i][1] +
        infoCurrentFigure.shiftHorizon + currentShift;

    if (!(x < 20 && x >= 0 && y < 20 && y >= 0 && infoGame.field[x][y] == 0)) {
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
  if (checkСollision == 0) flagAddNewFigure = 1;
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
    for (int j = 0; j < M; j++) {
      infoGame.field[i + 1][j] = infoGame.field[i][j];
    }
  }
}

GameInfo_t updateCurrentState() { return infoGame; }

int updateStatusGame() { return statusGame; }

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

void checkLine() {
  int sumDel = 0;
  for (int i = 0; i < N; i++) {
    int flag = 1;
    for (int j = 0; j < M; j++) {
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
}

void userInput(UserAction_t action) {
  if (action == Terminate)
    flagGo = -1;
  else if (action == Start && flagGame == 0) {
    flagGame = 1;
    statusGame = 1;
  } else if (action == Pause) {
    flagGame = 0;
    statusGame = 2;
  } else if (action != Action && flagGame == 1 && statusGame == 1)
    shiftCurrent(action);

  if (flagAddNewFigure == 1 && flagGame == 1) {
    int numberNewFigure = infoGame.next;
    checkLine();
    addFigure(numberNewFigure);
    infoGame.next = getRandNum();
    flagAddNewFigure = 0;
  }
}

void initColor() {
  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_GREEN, COLOR_GREEN);
  init_pair(4, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(5, COLOR_BLUE, COLOR_BLUE);
  init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(7, COLOR_CYAN, COLOR_CYAN);
  init_pair(8, COLOR_WHITE, COLOR_WHITE);
}

void clearTable() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      infoGame.field[i][j] = 0;
    }
  }
}

int updateFlagGo() { return flagGo; }

int updateFlagGame() { return flagGame; }

void updateInfoGameScore(int score) { infoGame.score = score; }

void updateInfoGameLevel(int level) { infoGame.level = level; }

void updateInfoGameSpeed(int speed) { infoGame.speed = speed; }

void updateInfoGameCurrent(int current) { infoGame.current = current; }

void updateInfoFlagGame(int flagGameNew) { flagGame = flagGameNew; }

void updateInfoStatusGame(int statusGameNew) { statusGame = statusGameNew; }

void updateInfoflagGo(int flagGoNew) { flagGo = flagGoNew; }

void updateInfoGameNext(int next) { infoGame.next = next; }

GameInfo_t getInfoGame() { return infoGame; }
