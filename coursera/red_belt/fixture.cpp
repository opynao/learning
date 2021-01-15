class AddTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
     for(const auto& item : vInput)
      {
          std::istringstream iss (item.second);
          db.Add(Date (item.first), ParseEvent(iss));
      }
  }
  Database db;
  std::vector<std::pair<std::string,std::string>> vInput {{"2017-01-01","New Year"},{"2017-03-08","Holiday"},{"2017-01-01","Holiday"}};
};

