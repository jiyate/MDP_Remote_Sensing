#include "obj_object.hpp"
#include "Importer.hpp"

void Importer::read_file(std::string filename) {
	target->read_obj_file(filename);
}
