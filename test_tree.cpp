#include "obj_object.hpp"
#include <string>

int main(int argc, char** argv) {
    //std::string filename = argv[1];
	OBJ_object test_obj("test_tree.h5");
	test_obj.read_obj_file("test_tree.cmp");
	test_obj.test_read_db("branch");
	test_obj.test_read_db("stemend");
	test_obj.test_read_db("needle");
	test_obj.test_read_db("leafA");
	test_obj.test_read_db("leafB");
}
