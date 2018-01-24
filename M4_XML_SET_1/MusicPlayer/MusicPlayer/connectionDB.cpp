#include "connectionDB.h"


connectionDB::connectionDB()
{
	sqlConnHandle = NULL;
}


connectionDB::~connectionDB()
{
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

SQLHANDLE connectionDB::createConnection(){
	SQLHANDLE sqlHandle = NULL;
	if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
	{

		if (SQL_SUCCESS == SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		{
			if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
			{
				SQLDriverConnect(sqlConnHandle,
					NULL,
					(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=IN11W-TRAINEE6\\SQLEXPRESS,49297;DATABASE=MusicPlayer;Trusted=true;",
					SQL_NTS,
					retconstring,
					1024,
					NULL,
					SQL_DRIVER_NOPROMPT);
				SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlHandle);
				return sqlHandle;
			}
		}
	}
	return sqlHandle;
}
