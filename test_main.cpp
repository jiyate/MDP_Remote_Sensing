#include "obj_object.hpp"
#include <string>

int main(int argc, char** argv) {
    //std::string filename = argv[1];
	OBJ_object test_obj("test.h5");
	test_obj.read_obj_file("test.obj");
	test_obj.test_read_db("v");
	test_obj.test_read_db("vt");
	test_obj.test_read_db("vn");
}
