#include <stdio.h>
#include <sqlite3.h>

int main (int argc, char *argv[])
{
	sqlite3 *db;
	sqlite3_stmt *stmt;

	int rc;
	rc = sqlite3_open("openflights.db", &db);
	if (rc )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}
	char *sql_stmt = "select count(a.Airline_ID) from airlines a where a.ICAO = \'\\N' or a.IATA = \'\\N' or a.Callsign = \'\\N' or a.Country = \'\\N' and a.Airline_ID in (select distinct r.Airline_ID from routes r, routes r1 where r.Source_airport_ID = r1.Destination_airport_ID and r.Destination_airport_ID = r1.Source_airport_ID);";
	
	rc = sqlite3_prepare_v2(db, sql_stmt, -1, &stmt, 0);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Preparation failed: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
	{
		int col;
		for (col = 0; col<sqlite3_column_count(stmt)-1; col++)
		{
			printf("%s|", sqlite3_column_text(stmt, col));
		}
		printf("%s", sqlite3_column_text(stmt, col));
		printf("\n");
	}
	sqlite3_finalize(stmt);
}

