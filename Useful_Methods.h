#pragma once
#include <ctime>
#include <iostream>
#include <stdlib.h>

void generateRandomNumber(int &x, int limit);
bool check_timing(time_t end, time_t &start, int interval);
bool detect_collision(const float x1, const float y1, const int width1, const int height1, 
	const float x2, const float y2, const int width2, const int height2);