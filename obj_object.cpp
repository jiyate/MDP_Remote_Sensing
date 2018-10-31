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
    db.exec("CREATE TABLE v (x FLOAT, y FLOAT, z FLOAT, w FLOAT, PRIMARY KEY(x, y, z))");
    /*
    sqldb->exec("CREATE TABLE vn (\
                                  i FLOAT, \
                                  j FLOAT, \
                                  k FLOAT, \
                                  PRIMARY(i, j, k))");
    sqldb->exec("CREATE TABLE vp (\
                                 u FLOAT, v FLOAT, \
                                 w FLOAT, \
                                 PRIMARY(u, v, w))"); //w default to 1.0
    */
    /*
    sqldb->exec("CREATE TABLE vt (vtid BIGINT, \
                                  u FLOAT NOT NULL, v FLOAT, w FLOAT, \
                                  PRIMARY KEY(vtid), \
                                  UNIQUE(u, v, w))");
    sqldb->exec("CREATE TABLE f (fid BIGINT, \
                                 v1 INTEGER NOT NULL, \
                                 vt1 INTEGER, vn1 INTEGER, \
                                 v2 INTEGER NOT NULL, \
                                 vt2 INTEGER, vn2 INTEGER, \
                                 v3 INTEGER NOT NULL, \
                                 vt3 INTEGER, vn3 INTEGER, \
                                 PRIMARY KEY(fid), \
                                 UNIQUE(v1, v2, v3))");
    */
    /*
    sqldb->exec("CREATE TABLE s (Group_Number INTEGER, \
                                 PRIMARY KEY(Group_Number))"); //just for vertex normal vn
    sqldb->exec("CREATE TABLE o (Object_Name VARCHAR(30), \
                                 PRIMARY KEY(Object_Name))");
    sqldb->exec("CREATE TABLE g (Group_Name VARCHAR(30), \
                                 PRIMARY KEY(Group_Name))");
    sqldb->exec("CREATE TABLE mg (Group_Name VARCHAR(30), \
                                  res INTEGER NOT NULL,
                                  PRIMARY KEY(Group_Name), \
                                  CHECK(res > 0))"); //just for free form vp
    sqldb->exec("CREATE TABLE ov (vx FLOAT, vy FLOAT, vz FLOAT, \
                                  Group_Name VARCHAR(30) NOT NULL, \
                                  PRIMARY KEY(vx, vy, vz), \
                                  FOREIGN KEY(vx) REFERENCES v(x), \
                                  FOREIGN KEY(vy) REFERENCES v(y), \
                                  FOREIGN KEY(vz) REFERENCES v(z), \
                                  FOREIGN KEY(Group_Name) REFERENCES o(Group_Name))");
    sqldb->exec("CREATE TABLE ovn (vni FLOAT, vnj FLOAT, vnk FLOAT, \
                                   Group_Name VARCHAR(30) NOT NULL, \
                                   PRIMARY KEY(vni, vnj, vnk), \
                                   FOREIGN KEY(vni) REFERENCES vn(i), \
                                   FOREIGN KEY(vnj) REFERENCES vn(j), \
                                   FOREIGN KEY(vnk) REFERENCES vn(k), \
                                   FOREIGN KEY(Group_Name) REFERENCES o(Group_Name))");
    sqldb->exec("CREATE TABLE ovp (vpu FLOAT, vpv FLOAT, vpw FLOAT, \
                                   Group_Name VARCHAR(30) NOT NULL, \
                                   PRIMARY KEY(vpu, vpv, vpw), \
                                   FOREIGN KEY(vpu) REFERENCES vp(u), \
                                   FOREIGN KEY(vpv) REFERENCES vp(v), \
                                   FOREIGN KEY(vpw) REFERENCES vp(w), \
                                   FOREIGN KEY(Group_Name) REFERENCES o(Group_Name))");
    */
    /*
    sqldb->exec("CREATE TABLE usemtl (usemtlid BIGINT, \
                                      group_number TEXT, \
                                      PRIMARY KEY(usemtlid))");
    sqldb->exec("CREATE TABLE mtllib (mtllibid BIGINT, \
                                      files TEXT, \
                                      PRIMARY KEY(mtllibid))");
    */

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
            write_database(parse_line(obj_file_line));
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
    while(query.executeStep()) {
        double x = query.getColumn(0);
        double y = query.getColumn(1);
        double z = query.getColumn(2);
        double w = query.getColumn(3);
        std::cout << table_name << " " << x << " " << y << " " << z << " " << w << "\n";
    }
}

void OBJ_object::read_v(std::deque<std::string> components) {
    SQLite::Database db = file->open_sqldatabase(db_name);
    std::string values = "(" + components[1] + ", " + components[2] + ", " + components[3]; 
    if(components.size() == 5) {
        values = values + ", " + components[4] + ")";
    } else { //components.size() == 4
        // The default value for w is 1.0
        values = values + ", " + std::to_string(1.0) + ")";
    }
    db.exec("INSERT INTO v VALUES" + values);
}
/*
void OBJ_object::read_vt(std::deque<std::string> components, Group &group) {
    std::string values = "("; 
    for(size_t i = 1; i < components.size() - 1; ++ i) {
        values = values + components[i] + ", ";
    }
    values = values + components[components.size() - 1];
    if(components.size() == 4) {
        values = values + ")";
    } else if(components.size() == 3) {
        // The default value for w is 1.0
        values = values + ", " + std::to_string(0.0) + ")";
    } else { //components.size() == 2
        values = values + ", " + std::to_string(0.0) + ", " + std::to_string(0.0) + ")";
    }
    sqldb.exec("INSERT INTO vt VALUES" + values);
}

void OBJ_object::read_vn(std::deque<std::string> components, Group &group) {
    std::string values = "("; 
    for(size_t i = 1; i < components.size() - 1; ++ i) {
        values = values + components[i] + ", ";
    }
    values = values + components[components.size() - 1] + ")";
    sqldb.exec("INSERT INTO vn VALUES" + values);
}

void OBJ_object::read_vp(std::deque<std::string> components, Group &group) {
    std::string values = "("; 
    for(size_t i = 1; i < components.size() - 1; ++ i) {
        values = values + components[i] + ", ";
    }
    values = values + components[components.size() - 1];
    if(components.size() == 3) {
        values = values + "1.0";
    } 
    sqldb.exec("INSERT INTO vp VALUES" + values + ")");
}

*/
/*
void OBJ_object::read_f(std::string &values,
                        std::deque<std::string> components) {
    std::string comma = "";
    for(size_t i = 1; i < components.size(); ++ i) {
        std::deque<std::string> elements;
        boost::split(elements, components[i], boost::is_any_of("/"));
        for(auto element : elements) {
            if(element != "") {
                values = values + comma + "NULL";
            } else {
                values = values + comma + element;
            }
            comma = ", ";
        }    
    }
    values = values + ")";
}

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
    /*
    else if (command == "vt") { //texture vertices
        read_vt(components, group);
    } 
    else if (command == "vn") { //vertex normals
        read_vn(components, group);
    } 
    else if (command == "vp") { //parameter space vertices
        read_vp(components, group);
    } 
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
    /*else if("f") { //face
        table_name = "f";
        read_f(values, components);
    }*//*
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
    //std::string command = "INSERT INTO " + table_name + " VALUES " + values;
    //sqldb->exec(command);
}

