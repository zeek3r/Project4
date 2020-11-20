#pragma once
#include <chrono>
class Time {
private:
public:
	static std::chrono::high_resolution_clock clock;
	static float deltaTime() {
		static auto time = clock.now();
		float dt = std::chrono::duration<float, std::milli>(clock.now() - time).count();
		time = clock.now();
		return dt;
	}
};