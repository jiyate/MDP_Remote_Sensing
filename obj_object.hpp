#ifndef OBJ_OBJECT_
#define OBJ_OBJECT_

#include <string>
#include <iostream>
#include "geostar.hpp"
#include "boost/filesystem.hpp"
#include "H5Cpp.h"
#include <SQLiteCpp.hpp>
#include <VariadicBind.hpp>
#include <sqlite3.h>
#include <spatialite/gaiageo.h>
#include <spatialite.h>
#include <deque>

struct Group {
    std::string group_type = "";
    std::deque<std::string> groups;
    bool valid = false;
};

class OBJ_object {
public:
    OBJ_object(std::string filename);
    ~OBJ_object();
    void read_obj_file(std::string filename);
    void test_read_db(std::string table_name);
private:
    GeoStar::File *file;
    std::string db_name;
    void init();
    std::deque<std::string> parse_line(std::string obj_file_line);
    void write_database(std::deque<std::string>);
    void read_v(std::deque<std::string> components);
    void read_vt(std::deque<std::string> components);
    void read_vn(std::deque<std::string> components);
    void read_vp(std::deque<std::string> components);
    /*
    void read_g(std::deque<std::string> components, Group &group);
    void read_s(std::deque<std::string> components, Group &group);
    void read_f(std::deque<std::string> components);
    void read_o(std::deque<std::string> components, Group &group);
    void read_mg(std::deque<std::string> components, Group &group);
    void read_usemtl(std::deque<std::string> components);
    void read_mtllib(std::deque<std::string> components);
    */
};

#endif
