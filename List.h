#pragma once
#include <string>
#define START 1
#define END 2
#define LEAVE 3
typedef struct List
{
	int id;
	int user_id;
	int type;
	std::string image;
	std::string date;
	std::string time;
} List;