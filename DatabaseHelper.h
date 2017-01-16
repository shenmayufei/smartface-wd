#pragma once

#include <string>

#include "mysql_connection.h"
#include "cppconn\driver.h"
#include "cppconn\connection.h"
#include "cppconn\statement.h"
#include "cppconn\resultset.h"

#include "cppconn\exception.h"


#define DB_VERSION 12

#define STRINGIZE2(s) #s
#define STRINGISZE(s) STRINGIZE2(s)

#define DB_URL "localhost:3306"
#define DB_USER "root"
#define DB_PASSWORD "quangtri@74"
#define DB_NAME "testsds"

#define TABLE_USER "user"
#define TABLE_INFO "info"
#define TABLE_LIST "list_check"

#define COLUMN_USER_ID "ID"
#define COLUMN_USER_NAME "NAME"
#define COLUMN_USER_NUMBER "NUMBER"
#define COLUMN_USER_IMAGE_1 "IMAGE_1"
#define COLUMN_USER_IMAGE_2 "IMAGE_2"
#define COLUMN_USER_IMAGE_3 "IMAGE_3"
#define COLUMN_USER_FET_1 "FET_1"
#define COLUMN_USER_FET_2 "FET_2"
#define COLUMN_USER_FET_3 "FET_3"


#define COLUMN_INFO_ID "ID"
#define COLUMN_INFO_VERSION "VERSION"

#define COLUMN_LIST_ID "ID"
#define COLUMN_LIST_USER_ID "USER_ID"
#define COLUMN_LIST_TYPE "LIST_TYPE"
#define COLUMN_LIST_IMAGE "LIST_IMAGE"
#define COLUMN_LIST_DATE "LIST_DATE"
#define COLUMN_LIST_TIME "LIST_TIME"

#define CREATE_TABLE_USER "CREATE TABLE user(ID INTEGER PRIMARY KEY auto_increment,NAME VARCHAR(256)"\
						", NUMBER VARCHAR(10)"\
						", IMAGE_1 VARCHAR(256), IMAGE_2 VARCHAR(256), IMAGE_3 VARCHAR(256)"\
						", FET_1 VARCHAR(256), FET_2 VARCHAR(256), FET_3 VARCHAR(256))"
#define DELETE_TABLE_USER "DROP TABLE IF EXISTS testsds.user"

#define CREATE_TABLE_INFO "CREATE TABLE info(ID INTEGER PRIMARY KEY auto_increment,VERSION INTEGER NOT NULL)"
#define DELETE_TABLE_INFO "DROP TABLE IF EXISTS testsds.info"

#define CREATE_TABLE_LIST "CREATE TABLE list_check(ID INTEGER PRIMARY KEY auto_increment, USER_ID INTEGER NOT NULL"\
							", LIST_TYPE INTEGER, LIST_DATE VARCHAR(32), LIST_TIME VARCHAR(32)"\
							",LIST_IMAGE VARCHAR(256)"\
							", FOREIGN KEY (USER_ID) REFERENCES testsds.user(ID)" \
							")"
#define DELETE_TABLE_LIST "DROP TABLE IF EXISTS testsds.list_check"
class DatabaseHelper
{
public:
	
	~DatabaseHelper();

	static DatabaseHelper& getInstance();
	virtual bool exeSQL(sql::SQLString);
	virtual sql::ResultSet * exeSQLQuery(sql::SQLString);
	virtual int exeSQLUpdate(sql::SQLString);
private:
	sql::Connection * mConn;

	DatabaseHelper();


	virtual void onCreate();
	virtual void onUpgrade(int oldVersion, int newVersion);
	virtual void onDowngrade(int oldVersion, int newVersion);


	virtual int queryVersion();
	virtual int insertVersion();

	virtual bool openConnection();
	virtual bool closeConnection();
};

