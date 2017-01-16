#include "stdafx.h"
#include "DatabaseManager.h"


DatabaseManager::DatabaseManager()
{
	// init
	DatabaseHelper::getInstance();
}


DatabaseManager::~DatabaseManager()
{
}

int DatabaseManager::insert(User user)
{
	sql::SQLString sql;
	sql.append("INSERT INTO ")
		.append(DB_NAME).append(".").append(TABLE_USER)
		.append("(").append(COLUMN_USER_NAME)
		.append(",").append(COLUMN_USER_NUMBER).append(")")
		.append(" values('")
		.append(user.name.c_str()).append("','")
		.append(user.number.c_str())
		.append("')");
	int rs = DatabaseHelper::getInstance().exeSQLUpdate(sql);
	return rs;

}
std::vector<User> DatabaseManager::query(int id)
{
	std::vector<User> v;
	sql::SQLString sql;
	sql.append("SELECT * FROM ")
		.append(DB_NAME).append(".").append(TABLE_USER);
	if (id > -1)
	{
		sql.append(" WHERE ").append(COLUMN_USER_ID).append("=").append(std::to_string(id));
	}
	sql::ResultSet * rs = DatabaseHelper::getInstance().exeSQLQuery(sql);
	if (rs)
	{
		while (rs->next())
		{
			User user;
			user.id = rs->getInt(COLUMN_USER_ID);
			user.name = rs->getString(COLUMN_USER_NAME);
			user.number = rs->getString(COLUMN_USER_NUMBER);
			user.fet_1 = rs->getString(COLUMN_USER_FET_1);
			user.fet_2 = rs->getString(COLUMN_USER_FET_2);
			user.fet_3 = rs->getString(COLUMN_USER_FET_3);

			user.image_1 = rs->getString(COLUMN_USER_IMAGE_1);
			user.image_2 = rs->getString(COLUMN_USER_IMAGE_2);
			user.image_3 = rs->getString(COLUMN_USER_IMAGE_3);
			v.push_back(user);
		}
	}

	return v;
}
std::vector<User> DatabaseManager::query(std::string name, std::string number)
{
	std::vector<User> v;
	sql::SQLString sql;
	sql.append("SELECT * FROM ")
		.append(DB_NAME).append(".").append(TABLE_USER)
		.append(" WHERE ")
		.append(COLUMN_USER_NAME).append("='").append(name).append("'").append(" AND ")
		.append(COLUMN_USER_NUMBER).append("='").append(number).append("'");
	sql::ResultSet * rs = DatabaseHelper::getInstance().exeSQLQuery(sql);
	if (rs)
	{
		while (rs->next())
		{
			User user;
			user.id = rs->getInt(COLUMN_USER_ID);
			user.name = rs->getString(COLUMN_USER_NAME);
			user.number = rs->getString(COLUMN_USER_NUMBER);

			user.fet_1 = rs->getString(COLUMN_USER_FET_1);
			user.fet_2 = rs->getString(COLUMN_USER_FET_2);
			user.fet_3 = rs->getString(COLUMN_USER_FET_3);
			user.image_1 = rs->getString(COLUMN_USER_IMAGE_1);
			user.image_2 = rs->getString(COLUMN_USER_IMAGE_2);
			user.image_3 = rs->getString(COLUMN_USER_IMAGE_3);
			
			v.push_back(user);
		}
	}

	return v;
}
std::vector<User> DatabaseManager::query(std::string number)
{
	std::vector<User> v;
	sql::SQLString sql;
	sql.append("SELECT * FROM ")
		.append(DB_NAME).append(".").append(TABLE_USER)
		.append(" WHERE ")
		.append(COLUMN_USER_NUMBER).append("='").append(number).append("'");
	sql::ResultSet * rs = DatabaseHelper::getInstance().exeSQLQuery(sql);
	if (rs)
	{
		while (rs->next())
		{
			User user;
			user.id = rs->getInt(COLUMN_USER_ID);
			user.name = rs->getString(COLUMN_USER_NAME);
			user.number = rs->getString(COLUMN_USER_NUMBER);

			user.fet_1 = rs->getString(COLUMN_USER_FET_1);
			user.fet_2 = rs->getString(COLUMN_USER_FET_2);
			user.fet_3 = rs->getString(COLUMN_USER_FET_3);
			user.image_1 = rs->getString(COLUMN_USER_IMAGE_1);
			user.image_2 = rs->getString(COLUMN_USER_IMAGE_2);
			user.image_3 = rs->getString(COLUMN_USER_IMAGE_3);

			v.push_back(user);
		}
	}

	return v;
}
void DatabaseManager::remove(int id)
{

}
int DatabaseManager::update(User user)
{
	sql::SQLString sql;
	sql.append("UPDATE ").append(DB_NAME).append(".").append(TABLE_USER).append(" SET ")
		.append(COLUMN_USER_NAME).append("='").append(user.name).append("',")
		.append(COLUMN_USER_IMAGE_1).append("='").append(user.image_1).append("',")
		.append(COLUMN_USER_IMAGE_2).append("='").append(user.image_2).append("',")
		.append(COLUMN_USER_IMAGE_3).append("='").append(user.image_3).append("',")
		.append(COLUMN_USER_FET_1).append("='").append(user.fet_1).append("',")
		.append(COLUMN_USER_FET_2).append("='").append(user.fet_2).append("',")
		.append(COLUMN_USER_FET_3).append("='").append(user.fet_2).append("'")
		.append(" WHERE ").append(COLUMN_USER_ID).append("=").append(std::to_string(user.id));

	return DatabaseHelper::getInstance().exeSQLUpdate(sql);
}
std::vector<List> DatabaseManager::queryList(int id)
{
	std::vector<List> v;
	sql::SQLString sql;
	sql.append("SELECT * FROM ")
		.append(DB_NAME).append(".").append(TABLE_LIST);
	if (id > -1)
	{
		sql.append(" WHERE ").append(COLUMN_LIST_ID).append("=").append(std::to_string(id));
	}
	sql::ResultSet * rs = DatabaseHelper::getInstance().exeSQLQuery(sql);
	if (rs)
	{
		while (rs->next())
		{
			List list;
			list.id = rs->getInt(COLUMN_LIST_ID);
			list.user_id = rs->getInt(COLUMN_LIST_USER_ID);
			list.type = rs->getInt(COLUMN_LIST_TYPE);
			list.image = rs->getString(COLUMN_LIST_IMAGE);
			list.date = rs->getString(COLUMN_LIST_DATE);
			list.time = rs->getString(COLUMN_LIST_TIME);

			v.push_back(list);
		}
	}

	return v;
}
std::vector<List> DatabaseManager::queryList(std::string date)
{
	std::vector<List> v;
	sql::SQLString sql;
	sql.append("SELECT * FROM ")
		.append(DB_NAME).append(".").append(TABLE_LIST)
		.append(" WHERE ").append(COLUMN_LIST_DATE).append("='").append(date).append("'");
	sql::ResultSet * rs = DatabaseHelper::getInstance().exeSQLQuery(sql);
	if (rs)
	{
		while (rs->next())
		{
			List list;
			list.id = rs->getInt(COLUMN_LIST_ID);
			list.user_id = rs->getInt(COLUMN_LIST_USER_ID);
			list.type = rs->getInt(COLUMN_LIST_TYPE);
			list.image = rs->getString(COLUMN_LIST_IMAGE);
			list.date = rs->getString(COLUMN_LIST_DATE);
			list.time = rs->getString(COLUMN_LIST_TIME);

			v.push_back(list);
		}
	}

	return v;
}
int DatabaseManager::insertList(List list)
{
	sql::SQLString sql;
	sql.append("INSERT INTO ")
		.append(DB_NAME).append(".").append(TABLE_LIST)
		.append("(").append(COLUMN_LIST_USER_ID)
		.append(",").append(COLUMN_LIST_TYPE)
		.append(",").append(COLUMN_LIST_DATE)
		.append(",").append(COLUMN_LIST_TIME)
		.append(",").append(COLUMN_LIST_IMAGE)	
		.append(")")
		.append(" values(")
		.append(std::to_string(list.user_id)).append(",")
		.append(std::to_string(list.type)).append(",'")
		.append(list.date).append("','")
		.append(list.time).append("','")
		.append(list.image)
		.append("')");
	int rs = DatabaseHelper::getInstance().exeSQLUpdate(sql);
	return rs;
}