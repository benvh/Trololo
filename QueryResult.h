#ifndef __QUERYRESULT_H__
#define __QUERYRESULT_H__

#include <vector>
#include <map>
#include <string>

#include <boost/any.hpp>


class Column
{
	private:
		std::vector<boost::any> data;

	public:

		boost::any getValue(int rowid);
		void pushValue(boost::any value);

};

class QueryResult
{
	private:

		std::map<std::string, Column*> cols;
		
		int rows;
		int currentRow;
		
	public:
		QueryResult(std::map< std::string, Column* > cols, int rows);
		~QueryResult(void);

		bool hasNext(void);
		void next(void);
		
		boost::any getValue(std::string colname);
		
		int getInt(std::string colname);
		double getDouble(std::string colname);
		std::string getString(std::string colname);

		bool isInt(std::string colname);
		bool isDouble(std::string colname);
		bool isString(std::string colname);
		bool isNULL(std::string colname);
};

#endif /* __QUERYRESULT_H__ */

