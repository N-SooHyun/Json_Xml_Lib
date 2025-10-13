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
      "name": "��ö��",
      "email": "chulsoo@example.com",
      "isActive": true,
      "orders": [
        {
          "orderId": "ORD-1001",
          "date": "2025-08-01",
          "items": [
            {
              "product": "��Ʈ��",
              "price": 1200000,
              "quantity": 1
            },
            {
              "product": "���� ���콺",
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
      "name": "�̿���",
      "email": "younghee@example.com",
      "isActive": false,
      "orders": []
    }
  ]
})";

    //const char* json_str_2 = R"({"ueser": 123, "Test": true, "Test2": 10.2, "Test3" : "good"})";
    //const char* json_str_2 = R"({"Key0" : 123, "Key1" : -123, "Key2" : 123.123, "Key3" : -123.123})"; 
    //const char* json_str_2 = R"({"Key0" : {"Key1" : 123}, "Key1" : {"Key1" : -123} })";

    const char* json_str_2 = R"([
  {
    "name": "aa",
    "age": 25,
    "email": "hong@example.com"
  },
  {
    "name": "cc",
    "age": 30,
    "email": "kim@example.com"
  },
  {
    "name": "bb",
    "age": 28,
    "email": "park@example.com"
  }
])";

    json_obj = json_str_2;

	JObj* jobj = static_cast<JObj*>(json_obj.P_Type);

    JNode* user_node = json_obj["company"];

	JObj* user_obj = static_cast<JObj*>(user_node->P_Type);

    JNode* address_node = (*user_node)["address"];

	JObj* address_obj = static_cast<JObj*>(address_node->P_Type);

    int num = 10;


}

void Test_Json() {
    JNode node;

    node.push() = "Test";
    node.push() = 123;

	JArr* arr = static_cast<JArr*>(node.P_Type);

    JNode* arr_node = static_cast<JNode*>(arr->getTailArr()->Value);

	int* arr_num = static_cast<int*>(arr_node->P_Type);

	const char* json_str_2 = R"({
  "user": {
    "id": "u123",
    "name": {
      "first": "Alice",
      "last": "Kim"
    },
    "contact": {
      "email": "alice@example.com",
      "phone": {
        "mobile": "010-1234-5678",
        "home": "02-987-6543"
      }
    },
    "address": {
      "city": "Seoul",
      "zip": "04524",
      "geo": {
        "lat": 37.5665,
        "lng": 126.9780
      }
    },
    "preferences": {
      "language": "Korean",
      "notifications": {
        "email": true,
        "sms": false
      }
    }
  },
  "system": {
    "version": "1.4.2",
    "status": "active",
    "maintenance": {
      "scheduled": false,
      "last_checked": "2025-09-20T12:34:56Z"
    }
  },
  "metadata": {
    "created_at": "2025-09-23T08:00:00Z",
    "updated_by": {
      "admin_id": "admin42",
      "role": "superuser"
    }
  }
}
)";

	const char* PlainJson = R"({
  "name": "gilDong",
  "Test" :    false      ,
  "score":      true      ,
  "Flt" : 123.123,
  "age": 30,
  "email": -123,
  "isMember": 123
})";

	const char* dbJson = R"({
  "name": "gildong",
  "age": 30,
  "address": {
    "city": "seoul",
    "zip": "12345"
  }
})";

	const char* plainArr = R"([1,2,3,4,5])";

	const char* fin_obj_arr = R"({
  "users": [
    {
      "id": 1,
      "name": "John Doe",
      "profile": {
        "bio": "Software developer, lover of travel and books.",
        "location": "Seoul, South Korea",
        "skills": ["Python", "JavaScript", "React"]
      },
      "posts": [
        {
          "id": 101,
          "content": "Sharing ideas for a new project today!",
          "comments": [
            {
              "user": "Jane Smith",
              "comment": "Very interesting idea! I hope the project goes well."
            },
            {
              "user": "Michael Brown",
              "comment": "I'd love to hear more about the direction of the project."
            }
          ]
        },
        {
          "id": 102,
          "content": "Sharing my amazing experience from a recent trip. It was great learning about the people and culture there.",
          "comments": [
            {
              "user": "Emily Davis",
              "comment": "Where did you go? I��d love to visit!"
            }
          ]
        }
      ]
    },
    {
      "id": 2,
      "name": "Jane Williams",
      "profile": {
        "bio": "Digital marketing expert, passionate about art and design.",
        "location": "Busan, South Korea",
        "skills": ["SEO", "Content Strategy", "Adobe Suite"]
      },
      "posts": [
        {
          "id": 103,
          "content": "Let's talk about digital marketing strategies. I want to emphasize the importance of SEO and content strategy again.",
          "comments": [
            {
              "user": "David Lee",
              "comment": "I didn��t realize how important SEO was. Thanks for the insight!"
            }
          ]
        }
      ]
    }
  ]
}
)";

	//node = json_str_2;
	//node = PlainJson;
	//node = dbJson;

	node = fin_obj_arr;

	JObj* pobj = static_cast<JObj*>(node.P_Type);

	JArr* parr = static_cast<JArr*>(pobj->Value->P_Type);

	int debug = 10;
}

int main() {

	//test_str();

    Test_Json();

	char c = 'a';

	while (1){
		fflush(stdin);
		std::cout << "�ƹ�Ű�� �Է��Ͻø� ����˴ϴ�";
		getchar();
		break;
		fflush(stdin);
		
	}

	return 0;
}