#include <app.h>
#include <display/window_stats.h>
#include <gtest/gtest.h>

#include <GLFW/glfw3.h>

TEST(AppTests, AppDefaultConstruct) {
  pbr::App app;
  app.Init();
  pbr::WindowStats stats = app.GetWindowStats();
  EXPECT_EQ(stats.width, 800);
  EXPECT_EQ(stats.height, 600);
}

TEST(AppTests, AppParamConstruct) {
  pbr::App app(1200, 300, "test");
  app.Init();
  pbr::WindowStats stats = app.GetWindowStats();
  EXPECT_STREQ(stats.title, "test");
  EXPECT_EQ(stats.width, 1200);
  EXPECT_EQ(stats.height, 300);
}

TEST(AppTests, AppIncorrectParamConstruct) {
  pbr::App app(-400, 0, "test");
  app.Init();
  pbr::WindowStats stats = app.GetWindowStats();
  EXPECT_STREQ(stats.title, "test");
  EXPECT_EQ(stats.width, 800);
  EXPECT_EQ(stats.height, 600);
}