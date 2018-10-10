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

class OBJ_exception: public exception {
    virtual const char* what() const throw() {
        return "Error: cannot read obj file";
    }
} read_obj_error;

class OBJ_object {
public:
    OBJ_object();
    ~OBJ_object();
    void read_obj_file(std::string filename);

private:
    std::deque<std::string> parse_line(std::string obj_file_line);
    void write_database(std::deque<std::string>);
};