#include "translator.h"
#include "gtest/gtest.h"

class TranslatorTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
  }
  Translator translator;
};

TEST_F( TranslatorTest, Simple )
{
  translator.Add(std::string("okno"), std::string("window"));
  translator.Add(std::string("stol"), std::string("table"));

  EXPECT_EQ(translator.TranslateForward("okno"), "window");
  EXPECT_EQ(translator.TranslateBackward("table"), "stol");
  EXPECT_EQ(translator.TranslateBackward("stol"), "");
}

TEST_F( TranslatorTest, TranslateReturnsLastOccurence )
{
  translator.Add(std::string("okno"), std::string("window"));
  translator.Add(std::string("stol"), std::string("table"));
  translator.Add(std::string("experience"), std::string("opit"));
  translator.Add(std::string("experience"), std::string("znanie"));
  translator.Add(std::string("experience"), std::string("sluchai"));

  EXPECT_EQ(translator.TranslateForward("experience"), "sluchai");
  EXPECT_EQ(translator.TranslateForward("feel"), "");
}

