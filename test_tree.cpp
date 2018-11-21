#include "obj_object.hpp"
#include "Exporter.hpp"
#include <string>

int main(int argc, char** argv) {
    //std::string filename = argv[1];
	OBJ_object test_obj("test_tree.h5");
	test_obj.read_obj_file("test_tree.cmp");

	Exporter exp(&test_obj);
	exp.export_to("test.out");
	/*
	test_obj.test_read_db("branch");
	test_obj.test_read_db("stemend");
	test_obj.test_read_db("needle");
	test_obj.test_read_db("leafA");
	test_obj.test_read_db("leafB");
	*/
}
