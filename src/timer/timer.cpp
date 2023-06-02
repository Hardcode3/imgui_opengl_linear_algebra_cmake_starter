#include <timer.h>


void Timer::begin()
{
	begin_time_ = std::chrono::high_resolution_clock::now();
	creation_time_ = begin_time_;
}

void Timer::stop()
{
	end_time_ = std::chrono::high_resolution_clock::now();
	execution_time_ = end_time_ - begin_time_;
}

std::chrono::duration<double> Timer::getExecutionTime() const
{
	return execution_time_;
}

std::chrono::duration<double> Timer::getTimeSinceCreation() const
{
	return std::chrono::high_resolution_clock::now() - creation_time_;
}

std::chrono::high_resolution_clock::time_point Timer::getCurrentTime() const
{
	return std::chrono::high_resolution_clock::now();
}

void Timer::printExecutionTime() const
{
	std::cout << "Execution time -> " << execution_time_.count() << " s\n";
}

void Timer::printTimeSinceCreation() const
{
	std::cout << "Warning, NOT WORKING \n";
	std::cout << "Time since timer creation -> " << getTimeSinceCreation().count() << " s\n";
}