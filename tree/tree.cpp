#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   // create table for branch
   /* Create SQL statement */
   sql = "CREATE TABLE BRANCH("  \
         "CENTERX             STRING      NOT NULL," \
         "CENTERY             STRING      NOT NULL," \
         "CENTERZ             STRING      NOT NULL," \
         "RADIUS              STRING      NOT NULL," \
         "LENGTH              STRING      NOT NULL," \
         "THETA               STRING      NOT NULL," \
         "PHI                 STRING      NOT NULL);";


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }


   // create table for stemend
   /* Create SQL statement */
   sql = "CREATE TABLE STEMEND("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "LENGTH              STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL);";


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }


   // create table for needle
   /* Create SQL statement */
   sql = "CREATE TABLE NEEDLE("  \
         "STARTX              STRING     NOT NULL," \
         "STARTY              STRING     NOT NULL," \
         "STARTZ              STRING     NOT NULL," \
         "ENDX                STRING     NOT NULL," \
         "ENDY                STRING     NOT NULL," \
         "ENDZ                STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "LENGTH              STRING     NOT NULL);";


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

   // create table for leafA
   /* Create SQL statement */
   sql = "CREATE TABLE LEAFA("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "THICKNESS           STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL);";


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }


   // create table for leafB
   /* Create SQL statement */
   sql = "CREATE TABLE LEAFB("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "THICKNESS           STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL);";


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }


   // create table for needle
   /* Create SQL statement */
   sql = "CREATE TABLE LEAFSECTION("  \
         "CENTERX              STRING     NOT NULL," \
         "CENTERY              STRING     NOT NULL," \
         "CENTERZ              STRING     NOT NULL," \
         "LENGTH               STRING     NOT NULL," \
         "WIDTH                STRING     NOT NULL," \
         "THICKNESS            STRING     NOT NULL," \
         "THETA                STRING     NOT NULL," \
         "PHI                  STRING     NOT NULL);";


   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

   ifstream ifs("lep15.cmp");
   string read;
   string command;
   char *command2;
   string centerx;
   string centery;
   string centerz;
   string radius;
   string length;
   string theta;
   string phi;
   string thickness;
   if (ifs.is_open()){
      while (getline(ifs, read)){
         istringstream line(read);
         string data;
         while (line >> data){
            if (data == "branch"){
               line >> centerx;
               line >> centery;
               line >> centerz;
               line >> radius;
               line >> length;
               line >> theta;
               line >> phi;

               command = "INSERT INTO BRANCH (CENTERX, CENTERY, CENTERZ,\
               RADIUS, LENGTH, THETA, PHI) VALUES (" + centerx +", "+
               centery +", "+ centerz+", "+ radius +
               ", "+ length +", "+ theta + ", "+ phi+");";
               
               char *command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               break;
            }
            else if (data == "stemend"){
               line >> centerx;
               line >> centery;
               line >> centerz;
               line >> radius;
               line >> length;
               line >> theta;
               line >> phi;

               command = "INSERT INTO STEMEND (CENTERX, CENTERY, CENTERZ,\
               RADIUS, LENGTH, THETA, PHI) VALUES (" + centerx +", "+
               centery +", "+ centerz+", "+ radius +
               ", "+ length +", "+ theta + ", "+ phi+");";
               
               char *command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();
               
               break;
            }
            else if (data == "leafA"){
               line >> centerx;
               line >> centery;
               line >> centerz;
               line >> radius;
               line >> thickness;
               line >> theta;
               line >> phi;

               command = "INSERT INTO LEAFA (CENTERX, CENTERY, CENTERZ,\
               RADIUS, THICKNESS, THETA, PHI) VALUES (" + centerx +", "+
               centery +", "+ centerz+", "+ radius +
               ", "+ thickness +", "+ theta + ", "+ phi+");";
               
               char *command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               break;
               
            }
            else if (data == "leafB"){
               line >> centerx;
               line >> centery;
               line >> centerz;
               line >> radius;
               line >> thickness;
               line >> theta;
               line >> phi;
               
               command = "INSERT INTO LEAFB (CENTERX, CENTERY, CENTERZ,\
               RADIUS, THICKNESS, THETA, PHI) VALUES (" + centerx +", "+
               centery +", "+ centerz+", "+ radius +
               ", "+ thickness +", "+ theta + ", "+ phi+");";
               
               char *command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               break;
            }
            else{
               break;
            }
         } 
      }
   }

   ifs.close();


   sqlite3_close(db);
   return 0;
}