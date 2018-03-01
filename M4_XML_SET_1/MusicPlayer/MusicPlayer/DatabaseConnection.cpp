#include "DatabaseConnection.h"

static DatabaseConnection* Connection;
static SQLHANDLE SqlHandle;
static SQLHANDLE SqlConnHandle;
static SQLHANDLE SqlEnvHandle;
static SQLWCHAR RetConString[SQL_RETURN_CODE_LEN];
DatabaseConnection::DatabaseConnection()
{
}


DatabaseConnection::~DatabaseConnection()
{
	if (Connection)
	{
		delete Connection;
		SQLDisconnect(SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
		SQLFreeHandle(SQL_HANDLE_ENV, SqlEnvHandle);
	}
	Connection = NULL;
}

void DatabaseConnection::Instantiate()
{
	if (Connection == NULL)
	{
		Connection = new DatabaseConnection();
		SqlConnHandle = NULL;
		SqlHandle = NULL;
		createConnection();
	}
}

void DatabaseConnection::createConnection()
{
	if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SqlEnvHandle))
	{
		if (SQL_SUCCESS == SQLSetEnvAttr(SqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		{
			if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_DBC, SqlEnvHandle, &SqlConnHandle))
			{
				SQLDriverConnect(SqlConnHandle,
					NULL,
					CONNECTION_DRIVER,
					SQL_NTS,
					RetConString,
					1024,
					NULL,
					SQL_DRIVER_NOPROMPT);
				SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
			}
		}
	}
}

bool DatabaseConnection::Instance()
{
	return (Connection == NULL) ? false : true;
}

/*This method will return the connection handler for establishing a connection with the database with in the application*/
SQLHANDLE DatabaseConnection::get_connection_handler()
{
	return (Instance()) ? SqlConnHandle : NULL;
}

