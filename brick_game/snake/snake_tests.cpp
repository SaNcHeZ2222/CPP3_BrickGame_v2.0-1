// #include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "snakegame_back.h"

// TEST(Test, TestSnake1) {
//   startSettingSnake();
//   updateGameType(1);
//   userInputSnake(StartSnake);
//   checkCollisionBack();
//   FlagInfoSnake flagInfo = getFlagInfoSnake();
//   ASSERT_TRUE(flagInfo.statusGame == 0);
//   userInputSnake(TerminateSnake);
//   checkCollisionBack();
//   flagInfo = getFlagInfoSnake();
//   ASSERT_TRUE(flagInfo.statusGame == -2);
// }

// TEST(Test, TestSnake2) {
//   startSettingSnake();
//   updateGameType(1);
//   FlagInfoSnake flagInfo = getFlagInfoSnake();
//   ASSERT_TRUE(flagInfo.statusGame == 1);
//   userInputSnake(StartSnake);
//   checkCollisionBack();
//   flagInfo = getFlagInfoSnake();
//   ASSERT_TRUE(flagInfo.statusGame == 0);
//   userInputSnake(PauseSnake);
//   checkCollisionBack();
//   flagInfo = getFlagInfoSnake();
//   ASSERT_TRUE(flagInfo.statusGame == 0);
//   userInputSnake(PauseSnake);
//   checkCollisionBack();
//   flagInfo = getFlagInfoSnake();
//   ASSERT_TRUE(flagInfo.statusGame == 0);
//   userInputSnake(TerminateSnake);
//   checkCollisionBack();
//   flagInfo = getFlagInfoSnake();
//   ASSERT_TRUE(flagInfo.statusGame == -2);
// }

// TEST(Test, TestSnake3) {
//   startSettingSnake();
//   updateGameType(1);
//   userInputSnake(StartSnake);
//   GameInfoSnake gameInfo = getGameInfoSnake();
//   ASSERT_TRUE(gameInfo.is_exit == 0);
// }

// TEST(Test, TestSnake4) {
//   startSettingSnake();
//   updateGameType(1);
//   userInputSnake(LeftSnake);
//   GameInfoSnake gameInfo = getGameInfoSnake();
//   ASSERT_TRUE(gameInfo.game == Snake);
// }

TEST(Test, TestSnake5) {
  startSettingSnake();
  updateGameType(1);
  userInputSnake(StartSnake);
  for (int i = 0; i < 20; ++i) {
    moveSnakeBack(LeftSnake);
    checkCollisionBack();
  }
  FlagInfoSnake flagInfo = getFlagInfoSnake();
  ASSERT_TRUE(flagInfo.statusGame == -2);
}

TEST(Test, TestSnake6) {
  startSettingSnake();
  updateGameType(1);
  userInputSnake(StartSnake);
  for (int i = 0; i < 20; ++i) {
    moveSnakeBack(RightSnake);
    checkCollisionBack();
  }
  FlagInfoSnake flagInfo = getFlagInfoSnake();
  ASSERT_TRUE(flagInfo.statusGame == -2);
}

TEST(Test, TestSnake7) {
  startSettingSnake();
  updateGameType(1);
  userInputSnake(StartSnake);
  for (int i = 0; i < 20; ++i) {
    moveSnakeBack(DownSnake);
    checkCollisionBack();
  }
  FlagInfoSnake flagInfo = getFlagInfoSnake();
  ASSERT_TRUE(flagInfo.statusGame == -2);
}

TEST(Test, TestSnake8) {
  startSettingSnake();
  updateGameType(1);
  userInputSnake(StartSnake);
  for (int i = 0; i < 20; ++i) {
    moveSnakeBack(UpSnake);
    checkCollisionBack();
  }
  FlagInfoSnake flagInfo = getFlagInfoSnake();
  ASSERT_TRUE(flagInfo.statusGame == -2);
}

// TEST(Test, TestSnake9) {
//   startSettingSnake();
//   updateGameType(1);
//   userInputSnake(TerminateSnake);
//   GameInfoSnake gameInfo = getGameInfoSnake();
//   ASSERT_TRUE(gameInfo.is_exit == 1);
// }
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}