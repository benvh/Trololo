#include "SqliteDatabase.h"

#include <iostream>

SqliteDatabase::SqliteDatabase(std::string db, bool connect)
{
	this->dbName = db;
	this->connected = false;
	
	if(connect) this->connect();
}

SqliteDatabase::~SqliteDatabase(void)
{
	if(this->isConnected())
		this->disconnect();
}

bool SqliteDatabase::isConnected(void)
{
	return this->connected;
}

int SqliteDatabase::connect(void)
{
	sqlite3_open(this->dbName.c_str(), &(this->db));
	this->connected = true; //needs a check
	
	return 0;	//Return some error/succes stuff
}

int SqliteDatabase::disconnect(void)
{
	sqlite3_close(this->db);
	
	return 0;	//Return some error/succes stuff
}

QueryResult* SqliteDatabase::simpleQuery(std::string query)
{
	if(this->isConnected())
	{
		sqlite3_stmt *stmt;
		if(sqlite3_prepare(this->db, query.c_str(), -1, &stmt, NULL) == SQLITE_OK)
		{
			std::vector<std::string> colnames;
			std::vector<Column* > cols;

			for(int i = 0; i < sqlite3_column_count(stmt); i++)
			{
				colnames.push_back(sqlite3_column_name(stmt, i));
				cols.push_back(new Column);

			}

			int rows = 0;

			while(sqlite3_step(stmt) == SQLITE_ROW)
			{
				for(int i = 0; i < sqlite3_column_count(stmt); i++)
				{
					switch(sqlite3_column_type(stmt, i))
					{
						case SQLITE_INTEGER:
							cols.at(i)->pushValue(sqlite3_column_int(stmt, i));
							break;

						case SQLITE_FLOAT:
							cols.at(i)->pushValue(sqlite3_column_double(stmt, i));
							break;

						case SQLITE_TEXT:
							cols.at(i)->pushValue((std::string) ((const char*)sqlite3_column_text(stmt, i)) );
							break;

						case SQLITE_BLOB:
							//Implement here
							break;

						case SQLITE_NULL:
							cols.at(i)->pushValue(boost::any()); 
							break;					
					}
				}
				rows++;
			}

			std::map<std::string, Column*> colmap;

			for(int i = 0; i < cols.size(); i++)
				colmap.insert(std::pair<std::string, Column*>(colnames.at(i), cols.at(i)));

			return new QueryResult(colmap, rows);	
		}		
	}

	return NULL;
}
