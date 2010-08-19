#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <sqlite3.h>
#include "QueryResult.h"

class SqliteDatabase
{
	private:
		sqlite3* db;
		
	public:
		SqliteDatabase(const char* db);
		~SqliteDatabase(void);

		QueryResult* simpleQuery(const char* qeury);

		
};

#endif /* __DATABASE_H__ */

