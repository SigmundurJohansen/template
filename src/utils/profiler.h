#pragma once
#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

class profiler
{
  public:
	static void record_timing(const std::string &name);
	static void report();

  private:
	static std::vector<std::string> timings;
	static std::mutex mutex_;
};

class timer
{
  public:
	timer(const std::string &name);
	~timer();

	timer(const timer &) = delete;
	timer &operator=(const timer &) = delete;

  private:
	std::string m_name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};

template <typename Func>
auto benchmark(Func test_func, int iterations)
{
	const auto start = std::chrono::system_clock::now();
	while (iterations-- > 0)
		test_func();
	const auto stop = std::chrono::system_clock::now();
	const auto secs = std::chrono::duration<double>(stop - start);
	return secs.count();
}