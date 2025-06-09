#include <check.h>

#include "tetris_back.h"

#define START_SHIFT_RIGHT 6

void setStartSetting() {
  updateInfoGameScore(0);

  updateInfoGameLevel(1);

  updateInfoGameSpeed(200);

  updateInfoGameNext(getRandNum());

  updateInfoGameCurrent(getRandNum());
}

START_TEST(test_1) {
  int arr[FIGURE_SIZE][2] = {{1, 0}, {1, 1}, {1, 2}, {1, 3},
                             {1, 4}, {1, 5}, {1, 6}, {1, 7}};

  GameInfo_t game_info_test = {0};
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) game_info_test.field[i][j] = 0;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = arr[i][0];
    int y = arr[i][1] + START_SHIFT_RIGHT;
    game_info_test.field[x][y] = 0;
  }

  setStartSetting();
  GameInfo_t output = updateCurrentState();
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      ck_assert_int_eq(game_info_test.field[i][j], output.field[i][j]);
}
END_TEST

START_TEST(test_2) {
  int arr[FIGURE_SIZE][2] = {{1, 0}, {1, 1}, {1, 2}, {1, 3},
                             {1, 4}, {1, 5}, {1, 6}, {1, 7}};

  GameInfo_t game_info_test = {0};
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j) game_info_test.field[i][j] = 0;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = arr[i][0] + 1;
    int y = arr[i][1] + START_SHIFT_RIGHT;
    game_info_test.field[x][y] = 2;
  }

  setStartSetting();
  shiftCurrent(Down);
  GameInfo_t output = updateCurrentState();

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j)
      ck_assert_int_eq(game_info_test.field[i][j], output.field[i][j]);
}
END_TEST

START_TEST(test_3) {
  int arr[FIGURE_SIZE][2] = {{1, 0}, {1, 1}, {1, 2}, {1, 3},
                             {1, 4}, {1, 5}, {1, 6}, {1, 7}};

  GameInfo_t game_info_test = {0};
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j) game_info_test.field[i][j] = 0;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = arr[i][0];
    int y = arr[i][1] + START_SHIFT_RIGHT + 2;
    game_info_test.field[x][y] = 2;
  }

  setStartSetting();
  UserAction_t action = translateKeyToAction(' ');
  userInput(action);
  action = translateKeyToAction('d');
  userInput(action);
  shiftCurrent(action);
  GameInfo_t output = updateCurrentState();

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j)
      ck_assert_int_eq(game_info_test.field[i][j], output.field[i][j]);
}
END_TEST

START_TEST(test_4) {
  int arr[FIGURE_SIZE][2] = {{1, 0}, {1, 1}, {1, 2}, {1, 3},
                             {1, 4}, {1, 5}, {1, 6}, {1, 7}};

  GameInfo_t game_info_test = {0};
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j) game_info_test.field[i][j] = 0;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = arr[i][0];
    int y = arr[i][1] + START_SHIFT_RIGHT - 2;
    game_info_test.field[x][y] = 2;
  }

  setStartSetting();
  UserAction_t action = translateKeyToAction(' ');
  userInput(action);
  action = translateKeyToAction('a');
  userInput(action);
  shiftCurrent(action);
  GameInfo_t output = updateCurrentState();

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j)
      ck_assert_int_eq(game_info_test.field[i][j], output.field[i][j]);
}
END_TEST

START_TEST(test_5) {
  int arr[FIGURE_SIZE][2] = {{1, 0}, {1, 1}, {1, 2}, {1, 3},
                             {1, 4}, {1, 5}, {1, 6}, {1, 7}};

  GameInfo_t game_info_test = {0};
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j) game_info_test.field[i][j] = 0;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = arr[i][0] + 1;
    int y = arr[i][1] + START_SHIFT_RIGHT;
    game_info_test.field[x][y] = 2;
  }

  setStartSetting();
  userInput(Start);
  shiftCurrent(Down);
  GameInfo_t output = updateCurrentState();

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j)
      ck_assert_int_eq(game_info_test.field[i][j], output.field[i][j]);
}
END_TEST

START_TEST(test_6) {
  int arr[FIGURE_SIZE][2] = {{1, 0}, {1, 1}, {1, 2}, {1, 3},
                             {1, 4}, {1, 5}, {1, 6}, {1, 7}};

  GameInfo_t game_info_test = {0};
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j) game_info_test.field[i][j] = 0;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = arr[i][0] + 1;
    int y = arr[i][1] + START_SHIFT_RIGHT;
    game_info_test.field[x][y] = 2;
  }

  setStartSetting();
  UserAction_t action = translateKeyToAction(' ');
  userInput(action);
  action = translateKeyToAction('s');
  userInput(action);
  shiftCurrent(action);
  GameInfo_t output = updateCurrentState();

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j)
      ck_assert_int_eq(game_info_test.field[i][j], output.field[i][j]);
}
END_TEST

START_TEST(test_7) {
  int arr[FIGURE_SIZE][2] = {{1, 0}, {1, 1}, {1, 2}, {1, 3},
                             {1, 4}, {1, 5}, {1, 6}, {1, 7}};

  GameInfo_t game_info_test = {0};
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j) game_info_test.field[i][j] = 0;

  for (int i = 0; i < FIGURE_SIZE; i++) {
    int x = arr[i][0];
    int y = arr[i][1] + START_SHIFT_RIGHT;
    game_info_test.field[x][y] = 2;
  }

  setStartSetting();
  UserAction_t action = translateKeyToAction(' ');
  userInput(action);
  action = translateKeyToAction('w');
  userInput(action);
  shiftCurrent(action);
  checkLine();
  GameInfo_t output = updateCurrentState();

  for (int i = 0; i < N; ++i)
    for (int j = 0; j < COLS; ++j)
      ck_assert_int_eq(game_info_test.field[i][j], output.field[i][j]);
}
END_TEST

Suite *expression_value_suite() {
  Suite *selection;
  TCase *test_core;
  selection = suite_create("expression_value");
  test_core = tcase_create("core");
  tcase_add_test(test_core, test_1);
  tcase_add_test(test_core, test_2);
  tcase_add_test(test_core, test_3);
  tcase_add_test(test_core, test_4);
  tcase_add_test(test_core, test_5);
  tcase_add_test(test_core, test_6);
  tcase_add_test(test_core, test_7);
  suite_add_tcase(selection, test_core);
  return selection;
}

void case_tests(Suite *selection, int *fail) {
  SRunner *runner = srunner_create(selection);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fail = 0;
  case_tests(expression_value_suite(), &fail);
  return fail;
}
