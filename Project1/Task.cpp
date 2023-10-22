#include "Task.h"
#include<string>
#include<vector>
#include<filesystem>
#include<fstream>
#include<algorithm>


void saveTaskToFile(const std::vector<Task>& task, const std::string& fileName)
{
	std::ofstream ostream(fileName);
	ostream << task.size();

	for (const Task& task : task) {
		std::string description = task.description;
		std::replace(description.begin(), description.end(), ' ', '_');

		ostream << '\n' << description << ' ' << task.done;

	}
}

std::vector<Task> loadTaskFromFile(const std::string& fileName)
{
	if (!std::filesystem::exists(fileName)) {
		return std::vector<Task>();
	}
	std::vector<Task> task;
	std::ifstream istream(fileName);

	int n;
	istream >> n;

	for (int i = 0; i < n; i++) {
		std::string description;
		bool done;

		istream >> description >> done;
		std::replace(description.begin(), description.end(), '_', ' ');
		task.push_back(Task{ description, done });
	}

	return task;
}