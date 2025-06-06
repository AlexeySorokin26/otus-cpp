#pragma once

#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> split(const std::string& str, char d);

void getSplitedVector(std::vector<std::vector<std::string>>& data);

void print(const std::vector<std::vector<std::string>>& data);