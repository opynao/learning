

class TimeServer 
{
public:
	std::string GetCurrentTime();
private:
	string last_fetched_time = "00:00:00";
};

std::string TimeServer::GetCurrentTime()
{
	std::string temporaryTime {last_fetched_time};
	try
	{
		last_fetched_time = AskTimeServer();
		return last_fetched time;
	}
	catch(std::system_error&)
	{
		return temporaryTime;
	}
}
