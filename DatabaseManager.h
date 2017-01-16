#pragma once
#include "User.h"
#include "List.h"
#include <vector>

#include "DatabaseHelper.h"
#include "cppconn\sqlstring.h"
#include <sstream>

class DatabaseManager
{
public:
	DatabaseManager();
	~DatabaseManager();
	virtual int insert(User user);
	virtual std::vector<User> query(int id = -1);
	virtual std::vector<User> query(std::string name, std::string number);
	virtual std::vector<User> query(std::string number);
	virtual void remove(int id = -1);
	virtual int update(User user);

	// list
	virtual std::vector<List> queryList(int id = -1);
	virtual std::vector<List> queryList(std::string date);
	virtual int insertList(List list);

};