#ifndef EXPORTER_H
#define EXPORTER_H 

#include <string>
#include <iostream>
#include "obj_object.hpp"

class Exporter {
public:
	Exporter(OBJ_object * source_in) : source(source_in) {}
	void export_to(std::string filename);

private:
	OBJ_object * source;
};


#endif 
