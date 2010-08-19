#include "QueryResult.h"

using boost::any_cast;

boost::any Column::getValue(int rowid)
{
	if(rowid < this->data.size())
		return this->data.at(rowid);

	return boost::any();
}

void Column::pushValue(boost::any value)
{
	this->data.push_back(value);
}



QueryResult::QueryResult(std::map< std::string, Column* > cols, int rows)
{
	this->cols = cols;
	this->rows = rows;
	this->currentRow = 0;
}

QueryResult::~QueryResult(void)
{
	std::map< std::string, Column* >::const_iterator it;
	for(it = this->cols.begin(); it != cols.end(); it++)
	{
		delete(it->second);
	}
}

bool QueryResult::hasNext(void)
{
	return this->currentRow < this->rows;	
}

void QueryResult::next(void)
{
	if(this->hasNext())
		this->currentRow++;
}

boost::any QueryResult::getValue(std::string colname)
{
	return this->cols.find(colname)->second->getValue(this->currentRow);
}


bool QueryResult::isInt(std::string colname)
{
	return this->getValue(colname).type() == typeid(int);
}

bool QueryResult::isDouble(std::string colname)
{
	return this->getValue(colname).type() == typeid(double);
}

bool QueryResult::isString(std::string colname)
{
	//Implement here
	return true;
}

bool QueryResult::isNULL(std::string colname)
{
	return this->getValue(colname).empty();
}




int QueryResult::getInt(std::string colname)
{
	return any_cast<int>(this->getValue(colname));	
}

double QueryResult::getDouble(std::string colname)
{
	return any_cast<double>(this->getValue(colname));
}

std::string QueryResult::getString(std::string colname)
{
	return any_cast<std::string>(this->getValue(colname));
}
