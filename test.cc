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
		if(!res->isNULL("value1")) cout << res->getString("value1") << " ";
		if(!res->isNULL("value2")) cout << res->getInt("value2");
		cout << endl;
		res->next();
	}
	
	return 0;
}
