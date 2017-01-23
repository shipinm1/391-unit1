#include <stdio.h>
#include <sqlite3.h>

int main (int argc, char *argv[])
{
	sqlite3 *db;
	sqlite3_stmt *stmt;

	int rc;
	rc = sqlite3_open('mydb.sql', &db);
	if (rc )
	{
		fprintf(stderr, 'Can't open database: %s\n', sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}
