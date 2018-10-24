#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>

#include "geostar.hpp"

#include "boost/filesystem.hpp"
#include "H5Cpp.h"

using namespace std;

int main(int argc, char* argv[]) {
   string filename="a2.h5";
   GeoStar::File *file = new GeoStar::File(filename,"new");
   string name = "/filename1";

   SQLite::Database  db = file->create_sqldatabase(name);

   db.exec("CREATE TABLE BRANCH("  \
         "CENTERX             STRING      NOT NULL," \
         "CENTERY             STRING      NOT NULL," \
         "CENTERZ             STRING      NOT NULL," \
         "RADIUS              STRING      NOT NULL," \
         "LENGTH              STRING      NOT NULL," \
         "THETA               STRING      NOT NULL," \
         "PHI                 STRING      NOT NULL)");

   cout<<"db->getErrorMsg()="<<db.getErrorMsg()<<endl;

   db.exec("CREATE TABLE STEMEND("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "LENGTH              STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL)");

   cout<<"db->getErrorMsg()="<<db.getErrorMsg()<<endl;

   db.exec("CREATE TABLE NEEDLE("  \
         "STARTX              STRING     NOT NULL," \
         "STARTY              STRING     NOT NULL," \
         "STARTZ              STRING     NOT NULL," \
         "ENDX                STRING     NOT NULL," \
         "ENDY                STRING     NOT NULL," \
         "ENDZ                STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "LENGTH              STRING     NOT NULL)");

   cout<<"db->getErrorMsg()="<<db.getErrorMsg()<<endl;

   db.exec("CREATE TABLE LEAFA("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "THICKNESS           STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL)");

   cout<<"db->getErrorMsg()="<<db.getErrorMsg()<<endl;

   db.exec("CREATE TABLE LEAFB("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "THICKNESS           STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL)");

   cout<<"db->getErrorMsg()="<<db.getErrorMsg()<<endl;

   db.exec("CREATE TABLE LEAFSECTION("  \
         "CENTERX              STRING     NOT NULL," \
         "CENTERY              STRING     NOT NULL," \
         "CENTERZ              STRING     NOT NULL," \
         "LENGTH               STRING     NOT NULL," \
         "WIDTH                STRING     NOT NULL," \
         "THICKNESS            STRING     NOT NULL," \
         "THETA                STRING     NOT NULL," \
         "PHI                  STRING     NOT NULL)");

   cout<<"db->getErrorMsg()="<<db.getErrorMsg()<<endl;

   int nb=0;
   ifstream ifs("lep15.cmp");
   string read;
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

               nb = db.exec("INSERT INTO BRANCH (CENTERX, CENTERY, CENTERZ,\
               RADIUS, LENGTH, THETA, PHI) VALUES (" + centerx +", "+
               centery +", "+ centerz+", "+ radius +
               ", "+ length +", "+ theta + ", "+ phi+")");

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

               db.exec("INSERT INTO STEMEND (CENTERX, CENTERY, CENTERZ,\
               RADIUS, LENGTH, THETA, PHI) VALUES (" + centerx +", "+
               centery +", "+ centerz+", "+ radius +
               ", "+ length +", "+ theta + ", "+ phi+")");
               
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

               db.exec("INSERT INTO LEAFA (CENTERX, CENTERY, CENTERZ,\
               RADIUS, THICKNESS, THETA, PHI) VALUES (" + centerx +", "+
               centery +", "+ centerz+", "+ radius +
               ", "+ thickness +", "+ theta + ", "+ phi+")");

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

               db.exec("INSERT INTO LEAFB (CENTERX, CENTERY, CENTERZ,\
               RADIUS, THICKNESS, THETA, PHI) VALUES (" + centerx +", "+
               centery +", "+ centerz+", "+ radius +
               ", "+ thickness +", "+ theta + ", "+ phi+")");

               break;
            }
            else{
               break;
            }
         } 
      }
   }

   ifs.close();

   return 0;
}