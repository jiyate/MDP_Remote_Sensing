#ifndef IMPORTER_H
#define IMPORTER_H

#include <string>
#include "obj_object.hpp"

class Importer {
public:
	Importer(OBJ_object * target_in) : target(target_in) {}
	void read_file(std::string filename);
		
private:
	OBJ_object * target;
};

#endif
