#include <iostream>
#include <string>
#include "QueryResult.h"

using namespace std;

int
main (int argc, char const* argv[])
{
	Column* a = new Column;
	a->pushValue((string)"aabc");
	a->pushValue((string)"lol");

	Column* b = new Column;
	b->pushValue(1);
	b->pushValue();

	map<string, Column*> cols;
	cols.insert(pair<string, Column*>((string)"blap", a));
	cols.insert(pair<string, Column*>((string)"blop", b));

	QueryResult* q = new QueryResult(cols, 2);

	while(q->hasNext())
	{
		cout << q->getString("blap") << " " << q->getInt("blop") << endl;
		q->next();
	}
	
	
	return 0;
}
