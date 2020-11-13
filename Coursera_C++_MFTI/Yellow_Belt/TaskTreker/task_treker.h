
enum class TaskStatus
{
	NEW ,          
	IN_PROGRESS ,  
	TESTING ,     
	DONE         
};

using TasksInfo = std::map<TaskStatus, int>;


