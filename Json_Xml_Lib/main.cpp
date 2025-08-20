#include "Main.h"
using namespace JSON;

void test_str() {
	JNode node;

	const char* test = "Test";

	node = test;

	node["Key1"] = 123;
	node["Key2"] = true;
	node["Key0"] = test;

	node["Key3"] = "Test";
	node["Key4"] = R"("Test")";


	

}

int main() {

	test_str();

	char c = 'a';

	while (1){
		fflush(stdin);
		std::cout << "프로그램 종료(q or Q) : ";
		scanf_s("%c", &c);
		if (c == 'q' || c == 'Q') break;
		fflush(stdin);
		
	}

	return 0;
}