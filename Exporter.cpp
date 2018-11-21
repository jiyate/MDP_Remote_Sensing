#include <string>
#include <sstream>
#include <fstream>
#include "obj_object.hpp"

void Exporter::export_to(std::string filename) {
	std::ofstream outfile;
	outfile.open(filename);
	outfile << (source->test_read_db("v")).str();
	outfile << (source->test_read_db("vn")).str();
	outfile << (source->test_read_db("vp")).str();
	outfile << (source->test_read_db("vt")).str();
	outfile << (source->test_read_db("f")).str();
	outfile << (source->test_read_db("branch")).str();
	outfile << (source->test_read_db("stemend")).str();
	outfile << (source->test_read_db("leafA")).str();
	outfile << (source->test_read_db("leafB")).str();
	outfile.close();
}
