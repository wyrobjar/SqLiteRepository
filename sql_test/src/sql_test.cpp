/*
 * sql_test.cpp
 *
 *  Created on: 10 paü 2013
 *      Author: wyrobjar
 */
#include <iostream>
#include <sqlite3.h>
#include <iomanip>
#include <ctime>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

static char * timer(char *buffer)
{
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strftime (buffer,17,"%Y-%m-%d %H:%M",timeinfo);
	return buffer;

}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   cout << " argc " << argc << " " << (int*)NotUsed << " " << *(int*)NotUsed << endl;
   *(int*)NotUsed = 8;
   for(i=0; i<argc; i++){
      cout << azColName[i] << " " << argv[i] << endl;
   }
   return 0;
}

class Database
{
	sqlite3 *database;
public:
	int test;
	vector <vector <string>> vec;
	Database(const char * db_name);
	~Database();
	bool open(const char * db_name);
	bool query(const char * sql_statement);
	bool create_db();
	bool insert_rec(string name, int hala, string address, int value);
	bool insert();
	bool show();
	void close();
};

Database::Database(const char *db_name)
{
	database = NULL;
	test = 99;
	open(db_name);
}

Database::~Database()
{

}

bool Database::open(const char * db_name)
{
	 if(SQLITE_OK == sqlite3_open(db_name, &database))
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }
}

bool Database::query(const char * sql_statement)
{
	char *zErrMsg = 0;
	if(SQLITE_OK == sqlite3_exec(database, sql_statement, callback, &test, &zErrMsg))
	{
		return true;
	}
	else
	{
		cerr << "SQL statement error: "<< zErrMsg << endl;
		sqlite3_free(zErrMsg);
		return false;
	}
}

bool Database::create_db()
{
	char *sql = "CREATE TABLE COMPANY("  \
	         "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
	         "NAME           TEXT    NOT NULL," \
	         "HALA            INT     NOT NULL," \
	         "ADDRESS        CHAR(50)," \
	         "SALARY         REAL," \
	         "DATE 			 TEXT    NOT NULL);";
	return query(sql);
}

bool Database::insert()
{
	char * sql = "INSERT INTO COMPANY (NAME,HALA,ADDRESS,SALARY,DATE) "  \
			 "VALUES ('Paul', 32, 'California', 20000.00, '2013-10-01 12:10' ); " \
			 "INSERT INTO COMPANY (ID,NAME,HALA,ADDRESS,SALARY,DATE) "  \
			 "VALUES ('Allen', 25, 'Texas', 15000.00, '2013-10-02 12:10' ); "     \
			 "INSERT INTO COMPANY (ID,NAME,HALA,ADDRESS,SALARY,DATE)" \
			 "VALUES ('Teddy', 23, 'Norway', 20000.00, '2013-10-03 12:10' );" \
			 "INSERT INTO COMPANY (ID,NAME,HALA,ADDRESS,SALARY,DATE)" \
			 "VALUES ('Mark', 25, 'Rich-Mond ', 65000.00, '2013-10-04 12:10' );";
	return query(sql);
}

bool Database::insert_rec(string name, int hala, string address, int value)
{
	string temp_sql = "INSERT INTO COMPANY (NAME,HALA,ADDRESS,SALARY,DATE) VALUES ('";
	//string str_id = static_cast<ostringstream*>( &(ostringstream() << id) )->str();
	//temp_sql += str_id+", '";
	temp_sql += name+"', ";
	string str_hala = static_cast<ostringstream*>( &(ostringstream() << hala) )->str();
	temp_sql += str_hala+", '";
	temp_sql += address+"', ";
	string str_salary = static_cast<ostringstream*>( &(ostringstream() << value) )->str();
	temp_sql += str_salary+", '";
	char *data = new char[17];
	string temp = timer(data);
	temp_sql += temp+"' );";
	//cout << temp_sql << endl;
	delete []data;
	const char * sql = temp_sql.c_str();
	return query(sql);
}

bool Database::show()
{
	char * sql = "SELECT * from COMPANY";
	return query(sql);
}

void Database::close()
{
	sqlite3_close(database);
}


int main()

{
	bool rc;
	Database Test("Database8.sqlite");
	//rc = Test.create_db();
	//cout << "Create DB return : " << rc << endl;
	/*
	rc = Test.insert_rec("Ania", 10, "NEW YORK", 15);
	cout << "Insert DB return : " << rc << endl;
	rc = Test.insert_rec("Igor", 10, "NEW YORK", 12);
	cout << "Insert DB return : " << rc << endl;
	rc = Test.insert_rec("Ola", 10, "NEW YORK", 13);
	cout << "Insert DB return : " << rc << endl;
	rc = Test.insert_rec("Marian", 10, "NEW YORK", 16);
	cout << "Insert DB return : " << rc << endl;
	*/
	rc = Test.show();
	cout << "test = " << Test.test << endl;
	cout << "Show DB return : " << rc << endl;
	Test.close();

	return 0;
}


