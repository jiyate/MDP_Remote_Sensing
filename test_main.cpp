#include "obj_object.hpp"
#include "Importer.hpp"
#include "Exporter.hpp"
#include <string>

int main(int argc, char** argv) {
    //std::string filename = argv[1];
	OBJ_object obj_obj("test.h5");
	OBJ_object *obj_ptr = &obj_obj;
	Importer imp(obj_ptr);
	imp.read_file("test.obj");
	Exporter exp(obj_ptr);
	exp.export_to("test.out");
}
