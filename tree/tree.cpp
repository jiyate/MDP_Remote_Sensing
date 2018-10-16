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
         "CENTERX             DOUBLE     NOT NULL," \
         "CENTERY             DOUBLE     NOT NULL," \
         "CENTERZ             DOUBLE     NOT NULL," \
         "RADIUS              DOUBLE     NOT NULL," \
         "LENGTH              DOUBLE     NOT NULL," \
         "THETA               DOUBLE     NOT NULL," \
         "PHI                 DOUBLE     NOT NULL);";


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
         "CENTERX             DOUBLE     NOT NULL," \
         "CENTERY             DOUBLE     NOT NULL," \
         "CENTERZ             DOUBLE     NOT NULL," \
         "RADIUS              DOUBLE     NOT NULL," \
         "LENGTH              DOUBLE     NOT NULL," \
         "THETA               DOUBLE     NOT NULL," \
         "PHI                 DOUBLE     NOT NULL);";


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
         "STARTX              DOUBLE     NOT NULL," \
         "STARTY              DOUBLE     NOT NULL," \
         "STARTZ              DOUBLE     NOT NULL," \
         "ENDX                DOUBLE     NOT NULL," \
         "ENDY                DOUBLE     NOT NULL," \
         "ENDZ                DOUBLE     NOT NULL," \
         "RADIUS              DOUBLE     NOT NULL," \
         "LENGTH              DOUBLE     NOT NULL);";


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
         "CENTERX             DOUBLE     NOT NULL," \
         "CENTERY             DOUBLE     NOT NULL," \
         "CENTERZ             DOUBLE     NOT NULL," \
         "RADIUS              DOUBLE     NOT NULL," \
         "THICKNESS           DOUBLE     NOT NULL," \
         "THETA               DOUBLE     NOT NULL," \
         "PHI                 DOUBLE     NOT NULL);";


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
         "CENTERX             DOUBLE     NOT NULL," \
         "CENTERY             DOUBLE     NOT NULL," \
         "CENTERZ             DOUBLE     NOT NULL," \
         "RADIUS              DOUBLE     NOT NULL," \
         "THICKNESS           DOUBLE     NOT NULL," \
         "THETA               DOUBLE     NOT NULL," \
         "PHI                 DOUBLE     NOT NULL);";


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
         "CENTERX              DOUBLE     NOT NULL," \
         "CENTERY              DOUBLE     NOT NULL," \
         "CENTERZ              DOUBLE     NOT NULL," \
         "LENGTH               DOUBLE     NOT NULL," \
         "WIDTH                DOUBLE     NOT NULL," \
         "THICKNESS            DOUBLE     NOT NULL," \
         "THETA                DOUBLE     NOT NULL," \
         "PHI                  DOUBLE     NOT NULL);";


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
   double centerx;
   double centery;
   double centerz;
   double radius;
   double length;
   double theta;
   double phi;
   double thickness;
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
               // concatenate and insert into table branch
               // USE ONE LINE INSTEAD
               //command = "INSERT INTO " + "BRANCH" +" CENTERX " + centerx;
               command += "INSERT INTO ";
               command += "BRANCH";
               command += " CENTERX ";
               command += centerx;
               char *command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               // command = "INSERT INTO " + "BRANCH" +" CENTERY " + centery;
               command += "INSERT INTO ";
               command += "BRANCH";
               command += " CENTERY ";
               command += centery;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               // command = "INSERT INTO " + "BRANCH" +" CENTERZ " + centerz;
               command += "INSERT INTO ";
               command += "BRANCH";
               command += " CENTERZ ";
               command += centerz;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "BRANCH" +" RADIUS " + radius;
               command += "INSERT INTO ";
               command += "BRANCH";
               command += " RADIUS ";
               command += radius;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "BRANCH" +" LENGTH " + length;
               command += "INSERT INTO ";
               command += "BRANCH";
               command += " LENGTH ";
               command += length;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "BRANCH" +" THETA " + theta;
               command += "INSERT INTO ";
               command += "BRANCH";
               command += " THETA ";
               command += theta;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "BRANCH" +" PHI " + phi;
               command += "INSERT INTO ";
               command += "BRANCH";
               command += " PHI ";
               command += phi;
               command2 = new char[command.length() + 1];
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
               // concatenate and insert into table stemend
               //command = "INSERT INTO " + "STEMEND" +" CENTERX " + centerx;
               command += "INSERT INTO ";
               command += "STEMEND";
               command += " CENTERX ";
               command += centerx;
               char *command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "STEMEND" +" CENTERY " + centery;
               command += "INSERT INTO ";
               command += "STEMEND";
               command += " CENTERY ";
               command += centery;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "STEMEND" +" CENTERZ " + centerz;
               command += "INSERT INTO ";
               command += "STEMEND";
               command += " CENTERZ ";
               command += centerz;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "STEMEND" +" RADIUS " + radius;
               command += "INSERT INTO ";
               command += "STEMEND";
               command += " RADIUS ";
               command += radius;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "STEMEND" +" LENGTH " + length;
               command += "INSERT INTO ";
               command += "STEMEND";
               command += " LENGTH ";
               command += length;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "STEMEND" +" THETA " + theta;
               command += "INSERT INTO ";
               command += "STEMEND";
               command += " THETA ";
               command += theta;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "STEMEND" +" PHI " + phi;
               command += "INSERT INTO ";
               command += "STEMEND";
               command += " PHI ";
               command += phi;
               command2 = new char[command.length() + 1];
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
               // concatenate and insert into table leafA
               //command = "INSERT INTO " + "LEAFA" +" CENTERX " + centerx;
               command += "INSERT INTO ";
               command += "LEAFA";
               command += " CENTERX ";
               command += centerx;
               char *command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFA" +" CENTERY " + centery;
               command += "INSERT INTO ";
               command += "LEAFA";
               command += " CENTERY ";
               command += centery;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFA" +" CENTERZ " + centerz;
               command += "INSERT INTO ";
               command += "LEAFA";
               command += " CENTERZ ";
               command += centerz;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFA" +" RADIUS " + radius;
               command += "INSERT INTO ";
               command += "LEAFA";
               command += " RADIUS ";
               command += radius;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFA" +" THICKNESS " + thickness;
               command += "INSERT INTO ";
               command += "LEAFA";
               command += " THICKNESS ";
               command += thickness;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFA" +" THETA " + theta;
               command += "INSERT INTO ";
               command += "LEAFA";
               command += " THETA ";
               command += theta;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFA" +" PHI " + phi;
               command += "INSERT INTO ";
               command += "LEAFA";
               command += " PHI ";
               command += phi;
               command2 = new char[command.length() + 1];
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
               // concatenate and insert into table leafB
               //command = "INSERT INTO " + "LEAFB" +" CENTERX " + centerx;
               command += "INSERT INTO ";
               command += "LEAFB";
               command += " CENTERX ";
               command += centerx;
               char *command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFB" +" CENTERY " + centery;
               command += "INSERT INTO ";
               command += "LEAFB";
               command += " CENTERY ";
               command += centery;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFB" +" CENTERZ " + centerz;
               command += "INSERT INTO ";
               command += "LEAFB";
               command += " CENTERZ ";
               command += centerz;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFB" +" RADIUS " + radius;
               command += "INSERT INTO ";
               command += "LEAFB";
               command += " RADIUS ";
               command += radius;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFB" +" THICKNESS " + thickness;
               command += "INSERT INTO ";
               command += "LEAFB";
               command += " THICKNESS ";
               command += thickness;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFB" +" THETA " + theta;
               command += "INSERT INTO ";
               command += "LEAFB";
               command += " THETA ";
               command += theta;
               command2 = new char[command.length() + 1];
               strcpy(command2, command.c_str());
               rc = sqlite3_exec(db, command2, callback, 0, &zErrMsg);
               delete [] command2;
               command.clear();

               //command = "INSERT INTO " + "LEAFB" +" PHI " + phi;
               command += "INSERT INTO ";
               command += "LEAFB";
               command += " PHI ";
               command += phi;
               command2 = new char[command.length() + 1];
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