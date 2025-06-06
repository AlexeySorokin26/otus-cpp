#pragma once

#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> split(const std::string& str, char d);

std::vector<std::vector<std::string>> getFirstPartOfSplitedVector(const std::string& fileName);

void print(const std::vector<std::vector<std::string>>& data);

void reverseLexSort(std::vector<std::vector<std::string>>& data);