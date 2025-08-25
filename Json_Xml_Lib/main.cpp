#include "Main.h"
using namespace JSON;

void test_str() {
	JNode node;
    JNode* node2 = new JNode();

	const char* test = "Test";

	node = test;

	node["Key1"] = 123;
	node["Key2"] = true;
	node["Key0"] = test;

	node["Key3"] = "Test";
	node["Key4"] = R"("Test")";    

	JNode json_obj;

	const char* json_str_1 = R"({
  "users": [
    {
      "id": 1,
      "name": "±èÃ¶¼ö",
      "email": "chulsoo@example.com",
      "isActive": true,
      "orders": [
        {
          "orderId": "ORD-1001",
          "date": "2025-08-01",
          "items": [
            {
              "product": "³ëÆ®ºÏ",
              "price": 1200000,
              "quantity": 1
            },
            {
              "product": "¹«¼± ¸¶¿ì½º",
              "price": 25000,
              "quantity": 2
            }
          ],
          "totalPrice": 1250000
        }
      ]
    },
    {
      "id": 2,
      "name": "ÀÌ¿µÈñ",
      "email": "younghee@example.com",
      "isActive": false,
      "orders": []
    }
  ]
})";

    const char* json_str_2 = R"({"ueser": 123, "Test": true, "Test2": 10.2, "Test3" : "good"})";

    json_obj = json_str_2;

}

int main() {

	test_str();

	char c = 'a';

	while (1){
		fflush(stdin);
		std::cout << "ÇÁ·Î±×·¥ Á¾·á(q or Q) : ";
		scanf_s("%c", &c);
		if (c == 'q' || c == 'Q') break;
		fflush(stdin);
		
	}

	return 0;
}