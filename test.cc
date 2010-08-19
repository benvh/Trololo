#include <iostream>
#include <string>
#include "SqliteDatabase.h"

using namespace std;

int
main (int argc, char const* argv[])
{
	SqliteDatabase *db = new SqliteDatabase("test.db");

	QueryResult* res = db->simpleQuery("SELECT * FROM `testing`");
	while(res->hasNext())
	{
		std::cout << res->getString("value1") << ", " << res->getInt("value2") << ", " << res->getDouble("value3") << std::endl;
		res->next();
	}
	
	return 0;
}
