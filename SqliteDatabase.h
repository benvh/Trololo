#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <sqlite3.h>
#include <string>
#include "QueryResult.h"

class SqliteDatabase
{
	private:
		sqlite3* db;
		std::string dbName;
		bool connected;
		
	public:
		SqliteDatabase(std::string db, bool connect=true);
		~SqliteDatabase(void);

		int connect(void);
		int disconnect(void);
		bool isConnected(void);
		
		QueryResult* simpleQuery(std::string query);

		
};

#endif /* __DATABASE_H__ */

