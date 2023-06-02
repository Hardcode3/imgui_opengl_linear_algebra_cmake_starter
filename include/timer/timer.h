#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void begin();
	void stop();

	std::chrono::high_resolution_clock::time_point getCurrentTime() const;
	std::chrono::duration<double> getExecutionTime() const;
	std::chrono::duration<double> getTimeSinceCreation() const;
	void printExecutionTime() const;
	void printTimeSinceCreation() const;

private:
	std::chrono::high_resolution_clock::time_point begin_time_;
	std::chrono::high_resolution_clock::time_point end_time_;
	std::chrono::high_resolution_clock::time_point creation_time_;
	std::chrono::duration<double> execution_time_;
};

#endif