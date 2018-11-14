// geostar lib
#include "geostar.hpp"
#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"
#include "H5Cpp.h"
#include <SQLiteCpp.hpp>
#include <VariadicBind.hpp>
#include <sqlite3.h>
#include <spatialite/gaiageo.h>
#include <spatialite.h>
// std lib
#include <string>
#include <iostream>
#include <fstream>
#include <deque>
#include <sstream>
// user defined header
#include "obj_object.hpp"

void OBJ_object::init() {
    SQLite::Database db = file->open_sqldatabase(db_name);
    db.exec("CREATE TABLE v (x FLOAT, y FLOAT, z FLOAT, w FLOAT, \
		                     ref_num INTEGER NOT NULL, \
			                 PRIMARY KEY(x, y, z), \
							 UNIQUE(ref_num))");
    db.exec("CREATE TABLE vn (i FLOAT, j FLOAT, k FLOAT, \
		                      ref_num INTEGER NOT NULL, \
			                  PRIMARY KEY(i, j, k), \
							  UNIQUE(ref_num))");
    db.exec("CREATE TABLE vp (u FLOAT, v FLOAT, w FLOAT, \
                              PRIMARY KEY(u, v, w))"); 
							  //w default to 1.0
    db.exec("CREATE TABLE vt (u FLOAT, v FLOAT, w FLOAT, \
	                          ref_num INTEGER NOT NULL, \
                              PRIMARY KEY(u, v, w), \
							  UNIQUE(ref_num))");
	db.exec("CREATE TABLE fv (v INTEGER, vt INTEGER, vn INTEGER, \
		                      f_id INTEGER NOT NULL, \
		                      PRIMARY KEY(v, vt, vn), \
							  FOREIGN KEY(f_id) REFERENCES f(f_id))");
    db.exec("CREATE TABLE f (f_id INTEGER, \
                      	     PRIMARY KEY(f_id))");

	//////////////////////Tree components/////////////////////////////
	db.exec("CREATE TABLE BRANCH("  \
         "CENTERX             STRING      NOT NULL," \
         "CENTERY             STRING      NOT NULL," \
         "CENTERZ             STRING      NOT NULL," \
         "RADIUS              STRING      NOT NULL," \
         "LENGTH              STRING      NOT NULL," \
         "THETA               STRING      NOT NULL," \
         "PHI                 STRING      NOT NULL)");

   db.exec("CREATE TABLE STEMEND("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "LENGTH              STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL)");

   db.exec("CREATE TABLE NEEDLE("  \
         "STARTX              STRING     NOT NULL," \
         "STARTY              STRING     NOT NULL," \
         "STARTZ              STRING     NOT NULL," \
         "ENDX                STRING     NOT NULL," \
         "ENDY                STRING     NOT NULL," \
         "ENDZ                STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "LENGTH              STRING     NOT NULL)");
   
   db.exec("CREATE TABLE LEAFA("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "THICKNESS           STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL)");

   db.exec("CREATE TABLE LEAFB("  \
         "CENTERX             STRING     NOT NULL," \
         "CENTERY             STRING     NOT NULL," \
         "CENTERZ             STRING     NOT NULL," \
         "RADIUS              STRING     NOT NULL," \
         "THICKNESS           STRING     NOT NULL," \
         "THETA               STRING     NOT NULL," \
         "PHI                 STRING     NOT NULL)");

   db.exec("CREATE TABLE LEAFSECTION("  \
         "CENTERX              STRING     NOT NULL," \
         "CENTERY              STRING     NOT NULL," \
         "CENTERZ              STRING     NOT NULL," \
         "LENGTH               STRING     NOT NULL," \
         "WIDTH                STRING     NOT NULL," \
         "THICKNESS            STRING     NOT NULL," \
         "THETA                STRING     NOT NULL," \
         "PHI                  STRING     NOT NULL)");


}

OBJ_object::OBJ_object(std::string output_file_name) {
    file = new GeoStar::File(output_file_name, "new");
    db_name = "/obj_sqldb";
    SQLite::Database db = file->create_sqldatabase(db_name);
    init();
}

OBJ_object::~OBJ_object() {
    delete file;
}

void OBJ_object::read_obj_file(std::string filename) {
    std::ifstream obj_file(filename);
    if(obj_file.is_open()) {
        std::string obj_file_line = "";
        // incase of int overflow, use long
        while(std::getline(obj_file, obj_file_line)) {
            if(!obj_file_line.empty()) {
                write_database(parse_line(obj_file_line));
            }
        }
    } else {
        std::cout << "ERROR opening file\n"; 
    }
}

std::deque<std::string> OBJ_object::parse_line(std::string obj_file_line) {
    std::istringstream iss(obj_file_line);
    std::deque<std::string> result(std::istream_iterator<std::string>{iss},
                                          std::istream_iterator<std::string>());

    return result;
}

void OBJ_object::test_read_db(std::string table_name) {
    SQLite::Database db = file->open_sqldatabase(db_name);
    SQLite::Statement query(db, "SELECT * FROM " + table_name);
    if(table_name == "v") {
        while(query.executeStep()) {
            double x = query.getColumn(0);
            double y = query.getColumn(1);
            double z = query.getColumn(2);
            double w = query.getColumn(3);
            std::cout << table_name << " " << x << " " << y << " " << z << " " << w << "\n";
        }
    } else if(table_name == "vn") {
        while(query.executeStep()) {
            double i = query.getColumn(0);
            double j = query.getColumn(1);
            double k = query.getColumn(2);
            std::cout << table_name << " " << i << " " << j << " " << k << "\n";
        }
    } else if(table_name == "vt") {
        while(query.executeStep()) {
            double u = query.getColumn(0);
            double v = query.getColumn(1);
            double w = query.getColumn(2);
            std::cout << table_name << " " << u << " " << v << " " << w << "\n";
        }        
    } else if(table_name == "vp") {
        while(query.executeStep()) {
            double u = query.getColumn(0);
            double v = query.getColumn(1);
            double w = query.getColumn(2);
            std::cout << table_name << " " << u << " " << v << " " << w << "\n";
        }        
	} else if(table_name == "f") {
		std::deque<int> f_ids;
		while(query.executeStep()) {
            int f_id = query.getColumn(0);
		    f_ids.push_back(f_id);
		}
		for(auto f_id : f_ids) {
		    SQLite::Database fvdb = file->open_sqldatabase(db_name);
		    SQLite::Statement fvquery(fvdb, "SELECT v, vt, vn \
			    	                         FROM fv \
				    					     WHERE fv.f_id = " +
											 std::to_string(f_id) +
					    				     " ORDER BY fv.f_id ASC");
		    std::cout << table_name << " ";
		    while(fvquery.executeStep()) {
			    // v, vt, vn here are all ref_nums
			    int v = fvquery.getColumn(0);
			    int vt = fvquery.getColumn(1);
			    int vn = fvquery.getColumn(2);
			    std::cout << v << "/" << vt << "/" << vn << " ";
		    }
			std::cout << "\n";
		}
	}
}

void OBJ_object::read_v(std::deque<std::string> components) {
	static int v_ref_num = 0;
    SQLite::Database db = file->open_sqldatabase(db_name);
    std::string values = "(" + components[1] + ", " + components[2] + ", " + components[3]; 
    if(components.size() == 5) {
        values = values + ", " + components[4];
    } else { //components.size() == 4
        // The default value for w is 1.0
        values = values + ", " + std::to_string(1.0);
    }
    db.exec("INSERT INTO v VALUES" + values + ", " + 
			std::to_string(v_ref_num) + ")");
	v_ref_num ++;
}

void OBJ_object::read_vt(std::deque<std::string> components) {
    static int vt_ref_num = 0;
	SQLite::Database db = file->open_sqldatabase(db_name);
    std::string values = "("; 
    std::string comma = "";
    for(size_t i = 1; i < components.size(); ++ i) {
        values = values + comma + components[i];
        comma = ", ";
    }
    if(components.size() == 4) {
        values = values;
    } else if(components.size() == 3) {
        // The default value for w is 1.0
        values = values + ", " + std::to_string(0.0);
    } else { //components.size() == 2
        values = values + ", " + std::to_string(0.0) + ", " + std::to_string(0.0);
    }
#ifdef DEBUG
    std::cout << values << "\n";
#endif
    db.exec("INSERT INTO vt VALUES" + values + ", " + 
			std::to_string(vt_ref_num) + ")");
	vt_ref_num ++;
}

void OBJ_object::read_vn(std::deque<std::string> components) {
    static int vn_ref_num = 0;
	SQLite::Database db = file->open_sqldatabase(db_name);
    std::string values = "("; 
    std::string comma = "";
    for(size_t i = 1; i < components.size(); ++ i) {
        values = values + comma + components[i];
        comma = ", ";
    }
#ifdef DEBUG
    std::cout << values << "\n";
#endif
    db.exec("INSERT INTO vn VALUES" + values + ", " + 
			 std::to_string(vn_ref_num) + ")");
    vn_ref_num ++;
}

void OBJ_object::read_vp(std::deque<std::string> components) {
    SQLite::Database db = file->open_sqldatabase(db_name);
    std::string values = "("; 
    std::string comma = "";
    for(size_t i = 1; i < components.size(); ++ i) {
        values = values + comma + components[i];
        comma = ", ";
    }
#ifdef DEBUG 
	std::cout << values << "\n";
	std::cout << components.size() << "\n";
#endif
    if(components.size() == 3) {
        values = values + ", 1.0";
    } 
    db.exec("INSERT INTO vp VALUES" + values + ")");
}


void OBJ_object::read_f(std::deque<std::string> components) {
	SQLite::Database db = file->open_sqldatabase(db_name);
	static int f_id = 0;
	db.exec("INSERT INTO f VALUES(" + std::to_string(f_id) + ")");
    for(size_t i = 1; i < components.size(); ++ i) {
        std::deque<std::string> elements;
		std::string values = "INSERT INTO fv VALUES(";
        boost::split(elements, components[i], boost::is_any_of("/"));
        for(auto element : elements) {
            values = values + element + ", ";
        }
		db.exec(values + std::to_string(f_id) + ")");
    }
	f_id ++;
}
/*
void OBJ_object::read_o(std::deque<std::string> components, Group &group) {
    std::string values = "("; 
    values = values + "'" + components[1] + "')";
    sqldb.exec("INSERT INTO o VALUES" + values);
    group.group_type = "o";
    group.valid = true;
}

void OBJ_object::read_s(std::deque<std::string> components, Group &group) {
    std::string values = "("; 
    if(components[1] == "off") {
        values = values + "0)";
        group.valid = false;
    } else {
        values = values + components[1] + ")";
        group.valid = true;
    }
    sqldb.exec("INSERT INTO s VALUES" + values);
    group.group_type = "s";
}

void OBJ_object::read_g(std::deque<std::string> components, Group &group) {
    std::string comma = "";
    if(components.size() > 1) {
        for(auto i : components) {
            sqldb.exec("INSERT INTO g VALUES(" + i + ")");
        }   
    } else {
        sqldb.exec("INSERT INTO g VALUES(default)");
    } 
    group.group_type = "g";
    group.valid = true;
}
void OBJ_object::read_mg(std::deque<std::string> components, Group &group) {
    std::string values = "(";

    if(components[1] == "off") {
        values = values + "0)";
        group.valid = false;
    } else {
        values = values + components[1] + ")";
        group.valid = true;
    }
    group.group_type = "mg";
}
*/

/*
void OBJ_object::read_usemtl(std::string &values,
                        std::deque<std::string> components) {
    if(components.size() > 1) {
        values = values + "'" + components[1] + "')";
    } else {
        values = values + "'white')";
    }
}

void OBJ_object::read_mtllib(std::string &values,
        std::deque<std::string> components) {
    std::string comma = "";
    for(size_t i = 1; i < components.size(); i ++) {
        values = values + comma + "'" + components[i];
        comma = " ";
    }
    values = values + "')";
}

*/
void OBJ_object::write_database(std::deque<std::string> components) {
    // use line numebr as the unique id
    std::string table_name = "";
    std::string values = "(";
    std::string command = components[0];
    Group group;
    // Vertex data line 251
    if(command == "v") { //geometric vertices
        read_v(components);
    } 
    
    else if (command == "vt") { //texture vertices
        read_vt(components);
    } 
    else if (command == "vn") { //vertex normals
        read_vn(components);
    } 
    else if (command == "vp") { //parameter space vertices
        read_vp(components);
    } 
    /*
    else if ("cstype") { // rational or non-rational forms of curve or surface type
        
    } 
    else if("deg") { //degree
        
    }*//*("bmat"): //basis matrix
        break;
    case("step"): //step size
        break;
    // Elements line 624
    case("p"): //point
        break;
    case("l"): //line
        break; */
    else if("f") { //face
        table_name = "f";
        read_f(components);
    }/*
    case("curv"): //curve
        break;
    case("curv2"): //2D curve
        break;
    case("surf"): //surface
        break;
    // Free-form curve/surface body statements    
    case("parm"): //parameter values
        break;
    case("trim"): // outer trimming loop
        break;
    case("hole"): //inner trimming loop
        break;
    case("scrv"): //special curve
        break;
    case("sp"): //special point
        break;
    case("end"): //end statement
        break;
    // Connectivity between free-form surfaces
    case("con"): //connect
        break;
    // Grouping line 1572
    else if(command == "g") { //group name
        read_g(components, group);
    } else if(command == "s") { //smoothing group 
        read_s(components, group);
    } else if(command == "mg") { //merging group
        read_mg(components, group);
    } else if(command == "o") { //object name
        read_o(components, group);
    } 
    // Display/render attributes
    case("bevel"): //bevel interpolation
        break;
    case("c_interp"): //color interpolation
        break;
    case("d_interp"): //dissolve interpolaiton
        break;
    case("lod"): //level of detail
        break;*/
    /*
    else if("usemtl") { //material name
        table_name = "usemtl";
        read_usemtl(values, components);
    } 
    else if("mtllib") { //material library
        table_name = "mtllib";
        read_mtllib(values, components);
    }*//*
    case("shadow_obj"): //shadow casting
        break;
    case("trace_obj"): //ray tracing
        break;
    case("ctech"): //curve approximation technique
        break;
    case("stech"): //surface approximation technique
        break;
    default:
    */

    /////////////////Tree Components/////////////////////
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

