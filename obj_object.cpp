// geostar lib
#include "geostar.hpp"
#include "boost/filesystem.hpp"
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
#include "OBJ_object.hpp"


void OBJ_object::read_obj_file(std::string filename) {
    std::ifstream obj_file(filename);
    if(obj_file.is_open) {
        std::string obj_file_line = "";
        while(std::getline(obj_file, obj_file_line)) {
            write_database(parse_line(obj_file_line));
        }
    } else {
        throw read_obj_error;
    }
}

std::deque<std::string> OBJ_object::parse_line(std::string obj_file_line) {
    std::istringstream iss(obj_file_line);
    return std::deque<std::string> result(std::istream_iterator<std::string>{iss},
                                          std::istream_iterator<std::string>())
}

void OBJ_object::write_database(std::deque<std::string> components) {
    
}

void OBJ_object::output_hdf_file(std::string filename) {
    std::ofstrema hdf_file(filename);

}