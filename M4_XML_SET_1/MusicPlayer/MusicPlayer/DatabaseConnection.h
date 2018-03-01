#pragma once

#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <string>
#include "Property.h"
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

using namespace std;

class DatabaseConnection
{
public:
	static SQLHANDLE get_connection_handler();
	static void Instantiate();
private:
	DatabaseConnection();
	~DatabaseConnection();
	static bool Instance();
	static void createConnection();
};

