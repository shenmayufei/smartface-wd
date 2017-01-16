#include "stdafx.h"
#include "DatabaseHelper.h"


DatabaseHelper& DatabaseHelper::getInstance()
{
	static DatabaseHelper instance;
	return instance;
}
DatabaseHelper::DatabaseHelper()
{
	if (openConnection())
	{
		// check version
		int currentVerion = queryVersion();

		// new
		if (currentVerion == -1)
		{
			onCreate();
		}
		else if (currentVerion < DB_VERSION)
		{
			// upgrade
			
			onUpgrade(currentVerion, DB_VERSION);
		}
		else if (currentVerion > DB_VERSION)
		{
			// downgrade
			onDowngrade(currentVerion, DB_VERSION);
		}
			

	}
}


DatabaseHelper::~DatabaseHelper()
{
	closeConnection();
}

bool DatabaseHelper::openConnection()
{
	try
	{

		sql::Driver * driver = get_driver_instance();
	
		mConn = driver->connect(DB_URL, DB_USER, DB_PASSWORD);
		mConn->setSchema(DB_NAME);
		return true;
	}
	catch (sql::SQLException &e)
	{
		TRACE(e.what());
	}
	return false;
}
bool DatabaseHelper::closeConnection()
{
	try
	{
		if (mConn && !mConn->isClosed())
		{
			mConn->close();
		}
		return true;
	}
	catch (sql::SQLException &e)
	{
		TRACE(e.what());
	}
	return false;
}

void DatabaseHelper::onCreate()
{
	exeSQL(CREATE_TABLE_USER);
	exeSQL(CREATE_TABLE_INFO);
	exeSQL(CREATE_TABLE_LIST);
	insertVersion();

}
void DatabaseHelper::onUpgrade(int oldVersion, int newVersion)
{
	exeSQL(DELETE_TABLE_LIST);
	exeSQL(DELETE_TABLE_INFO);
	exeSQL(DELETE_TABLE_USER);
	
	onCreate();
}
void DatabaseHelper::onDowngrade(int oldVersion, int newVersion)
{
	exeSQL(DELETE_TABLE_LIST);
	exeSQL(DELETE_TABLE_INFO);
	exeSQL(DELETE_TABLE_USER);
	
	onCreate();
}

bool DatabaseHelper::exeSQL(sql::SQLString sql)
{
	try
	{
		std::auto_ptr<sql::Statement> stmt(mConn->createStatement());
		return stmt->execute(sql);
	}
	catch (sql::SQLException &e)
	{
		TRACE(e.what());
	}
	return false;
}
sql::ResultSet * DatabaseHelper::exeSQLQuery(sql::SQLString sql)
{
	sql::ResultSet * rs = NULL;
	try
	{
		std::auto_ptr<sql::Statement> stmt(mConn->createStatement());
		rs = stmt->executeQuery(sql);
	}
	catch (sql::SQLException &e)
	{
		TRACE(e.what());
	}
	return rs;
}
int DatabaseHelper::exeSQLUpdate(sql::SQLString sql)
{
	int rs = -1;
	try
	{
		std::auto_ptr<sql::Statement> stmt(mConn->createStatement());
		rs = stmt->executeUpdate(sql);
	}
	catch (sql::SQLException &e)
	{
		TRACE(e.what());
		TRACE(sql.c_str());
	}
	return rs;
}
int DatabaseHelper::queryVersion()
{
	sql::SQLString sql;
	sql.append("SELECT * FROM ")
		.append(DB_NAME).append(".")
		.append(TABLE_INFO);
	sql::ResultSet * rs = exeSQLQuery(sql);
	while (rs && rs->next())
	{
		return rs->getInt(COLUMN_INFO_VERSION);
	}
	return -1;
}
int DatabaseHelper::insertVersion()
{
	sql::SQLString sql;
	sql.append("INSERT INTO ")
		.append(DB_NAME).append(".")
		.append(TABLE_INFO).append("(").append(COLUMN_INFO_VERSION).append(")")
		.append(" values(")
		.append(STRINGISZE(DB_VERSION))
		.append(")");
	
	return exeSQLUpdate(sql);
}