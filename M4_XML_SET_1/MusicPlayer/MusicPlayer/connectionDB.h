#pragma once

#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <string>
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

using namespace std;

class connectionDB
{
public:
	connectionDB();
	~connectionDB();
	SQLHANDLE createConnection();

private:
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

};

