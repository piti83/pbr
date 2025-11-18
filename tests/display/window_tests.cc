#include <gtest/gtest.h>

#include <display/window.h>
#include <app.h>

TEST(WindowTests, WindowCreation) {
  pbr::Window window(1200, 800, "test");
  window.Init();
  EXPECT_NE(window.GetWindow(), nullptr);
}

TEST(WindowTests, WindowInvalidParams) {
  pbr::Window test(0, -200, "Test");
  EXPECT_EQ(test.GetWidth(), 800);
  EXPECT_EQ(test.GetHeight(), 600);
  EXPECT_STREQ(test.GetTitle(), "Test");
}

TEST(WindowTests, CustomParams) { 
  pbr::Window test(1200, 400, "Test"); 
  EXPECT_EQ(test.GetWidth(), 1200);
  EXPECT_EQ(test.GetHeight(), 400);
  EXPECT_STREQ(test.GetTitle(), "Test");
}

TEST(WindowTests, WindowInit) { 
  pbr::Window test(1200, 400, "Test"); 
  EXPECT_NO_THROW(test.Init());
}