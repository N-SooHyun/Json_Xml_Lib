#include "Main.h"
using namespace JSON;


//대입 테스트
void Ver_Set_Test_Before(JNode& node) {
	printf("<대입 이전>\n");
	printf("기존 Cur_Type : ");
	
	switch (node.Cur_Type){
		case JNode::JType::NUMBER:
			std::cout << "NUMBER" << std::endl;
			break;
		case JNode::JType::DOUBLE:
			std::cout << "DOUBLE" << std::endl;
			break;
		case JNode::JType::BOOL:
			std::cout << "BOOL" << std::endl;
			break;
		case JNode::JType::STRING:
			std::cout << "STRING" << std::endl;
			break;
		case JNode::JType::OBJ:
			std::cout << "OBJ" << std::endl;
			break;
		case JNode::JType::ARR:
			std::cout << "ARR" << std::endl;
			break;
		case JNode::JType::NULLTYPE:
			std::cout << "NULLTYPE" << std::endl;
			break;
	}

	printf("기존 P_Type : ");

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		printf("new int() -> %p\n", node.P_Type);
		break;
	case JNode::JType::DOUBLE:
		printf("new double() -> %p\n", node.P_Type);
		break;
	case JNode::JType::BOOL:
		printf("new bool() -> %p\n", node.P_Type);
		break;
	case JNode::JType::STRING:
		printf("new char() -> %p\n", node.P_Type);
		break;
	case JNode::JType::OBJ:
		printf("new obj() -> %p\n", node.P_Type);
		break;
	case JNode::JType::ARR:
		printf("new arr() -> %p\n", node.P_Type);
		break;
	case JNode::JType::NULLTYPE:
		printf("nullptr -> %p\n", node.P_Type);
		break;
	}
	printf("---------------------\n");
}

void Ver_Set_Test_Before_2(JNode& node){
	printf("<대입 이전>\n");
	printf("기존 Cur_Type : ");

	int* pnum = nullptr;
	double* pdnum = nullptr;
	bool* pbl = nullptr;
	DynamicStr* str = nullptr;
	char* pstr = nullptr;

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		std::cout << "NUMBER" << std::endl;
		pnum = static_cast<int*>(node.P_Type);
		printf("node.P_Type(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		std::cout << "DOUBLE" << std::endl;
		pdnum = static_cast<double*>(node.P_Type);
		printf("node.P_Type(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		std::cout << "BOOL" << std::endl;
		pbl = static_cast<bool*>(node.P_Type);
		printf("node.P_Type(bool) = %d\n", *pbl);
		break;
	case JNode::JType::STRING:
		std::cout << "STRING" << std::endl;
		str = static_cast<DynamicStr*>(node.P_Type);
		printf("node.P_Type(int) = %s\n", str->Get_Str());
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		pnum = static_cast<int*>(node.P_Type);
		printf("node.P_Type(int) = %d\n", *pnum);
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}

	printf("기존 P_Type : ");

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		printf("new int() -> %p\n", node.P_Type);
		pnum = static_cast<int*>(node.P_Type);
		printf("node.P_Type(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		printf("new double() -> %p\n", node.P_Type);
		pdnum = static_cast<double*>(node.P_Type);
		printf("node.P_Type(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		printf("new bool() -> %p\n", node.P_Type);
		pbl = static_cast<bool*>(node.P_Type);
		printf("node.P_Type(bool) = %d\n", *pbl);
		break;
	case JNode::JType::STRING:
		printf("new char() -> %p\n", node.P_Type);
		str = static_cast<DynamicStr*>(node.P_Type);
		printf("node.P_Type(int) = %s\n", str->Get_Str());
		break;
	case JNode::JType::OBJ:
		printf("new obj() -> %p\n", node.P_Type);
		break;
	case JNode::JType::ARR:
		printf("new arr() -> %p\n", node.P_Type);
		break;
	case JNode::JType::NULLTYPE:
		printf("nullptr -> %p\n", node.P_Type);
		break;
	}
	printf("---------------------\n");
}

void Ver_Set_Test_After(JNode& node, JNode::JType curType) {
	printf("<대입 이후>\n");
	printf("대입한 타입 : ");

	switch (curType){
	case JNode::JType::NUMBER:
		std::cout << "NUMBER" << std::endl;
		break;
	case JNode::JType::DOUBLE:
		std::cout << "DOUBLE" << std::endl;
		break;
	case JNode::JType::BOOL:
		std::cout << "BOOL" << std::endl;
		break;
	case JNode::JType::STRING:
		std::cout << "STRING" << std::endl;
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}

	printf("대입 이후 node.Cur_Type : ");

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		std::cout << "NUMBER" << std::endl;
		break;
	case JNode::JType::DOUBLE:
		std::cout << "DOUBLE" << std::endl;
		break;
	case JNode::JType::BOOL:
		std::cout << "BOOL" << std::endl;
		break;
	case JNode::JType::STRING:
		std::cout << "STRING" << std::endl;
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}


	printf("대입 이후 P_Type : ");

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		printf("new int() -> %p\n", node.P_Type);
		break;
	case JNode::JType::DOUBLE:
		printf("new double() -> %p\n", node.P_Type);
		break;
	case JNode::JType::BOOL:
		printf("new bool() -> %p\n", node.P_Type);
		break;
	case JNode::JType::STRING:
		printf("new char() -> %p\n", node.P_Type);
		break;
	case JNode::JType::OBJ:
		printf("new obj() -> %p\n", node.P_Type);
		break;
	case JNode::JType::ARR:
		printf("new arr() -> %p\n", node.P_Type);
		break;
	case JNode::JType::NULLTYPE:
		printf("nullptr -> %p\n", node.P_Type);
		break;
	}
	printf("---------------------\n");
}

void Ver_Set_Test_After_2(JNode& node, JNode::JType curType) {
	printf("<대입 이후>\n");
	printf("대입한 타입 : ");

	int* pnum = nullptr;
	double* pdnum = nullptr;
	bool* pbl = nullptr;
	DynamicStr* str = nullptr;
	char* pstr = nullptr;

	switch (curType){
	case JNode::JType::NUMBER:
		std::cout << "NUMBER" << std::endl;
		pnum = static_cast<int*>(node.P_Type);
		printf("node.P_Type(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		std::cout << "DOUBLE" << std::endl;
		pdnum = static_cast<double*>(node.P_Type);
		printf("node.P_Type(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		std::cout << "BOOL" << std::endl;
		pbl = static_cast<bool*>(node.P_Type);
		printf("node.P_Type(bool) = %d\n", *pbl);
		break;
	case JNode::JType::STRING:
		std::cout << "STRING" << std::endl;
		str = static_cast<DynamicStr*>(node.P_Type);
		printf("node.P_Type(str) = %s\n", str->Get_Str());
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}

	printf("대입 이후 node.Cur_Type : ");

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		std::cout << "NUMBER" << std::endl;
		pnum = static_cast<int*>(node.P_Type);
		printf("node.P_Type(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		std::cout << "DOUBLE" << std::endl;
		pdnum = static_cast<double*>(node.P_Type);
		printf("node.P_Type(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		std::cout << "BOOL" << std::endl;
		pbl = static_cast<bool*>(node.P_Type);
		printf("node.P_Type(bool) = %d\n", *pbl);
		break;
	case JNode::JType::STRING:
		std::cout << "STRING" << std::endl;
		str = static_cast<DynamicStr*>(node.P_Type);
		printf("node.P_Type(int) = %s\n", str->Get_Str());
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}


	printf("대입 이후 P_Type : ");

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		printf("new int() -> %p\n", node.P_Type);
		pnum = static_cast<int*>(node.P_Type);
		printf("node.P_Type(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		printf("new double() -> %p\n", node.P_Type);
		pdnum = static_cast<double*>(node.P_Type);
		printf("node.P_Type(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		printf("new bool() -> %p\n", node.P_Type);
		pbl = static_cast<bool*>(node.P_Type);
		printf("node.P_Type(bool) = %B\n", *pbl);
		break;
	case JNode::JType::STRING:
		printf("new char() -> %p\n", node.P_Type);
		str = static_cast<DynamicStr*>(node.P_Type);
		printf("node.P_Type(int) = %s\n", str->Get_Str());
		break;
	case JNode::JType::OBJ:
		printf("new obj() -> %p\n", node.P_Type);
		break;
	case JNode::JType::ARR:
		printf("new arr() -> %p\n", node.P_Type);
		break;
	case JNode::JType::NULLTYPE:
		printf("nullptr -> %p\n", node.P_Type);
		break;
	}
	printf("---------------------\n");
}


//반환 테스트
void Ver_Get_Test_Before(JNode& node, JNode::JType lValueType, void* lValue, bool c_ck=false) {
	int* pnum = nullptr;
	double* pdnum = nullptr;
	bool* pbl = nullptr;
	DynamicStr* str = nullptr;
	char* pstr = nullptr;
	char *c = nullptr;
	
	printf("<반환 이전>\n");
	printf("lValue 상태 : ");
	switch (lValueType){
	case JNode::JType::NUMBER:
		pnum = static_cast<int*>(lValue);
		printf("lValue(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		pdnum = static_cast<double*>(lValue);
		printf("lValue(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		pbl = static_cast<bool*>(lValue);
		printf("lValue(bool) = %d\n", *pbl);
		break;
	case JNode::JType::STRING:
		if (c_ck){
			c = static_cast<char*>(lValue);
			printf("lValue(char) = %c\n", c[0]); 
			break;
		}
		pstr = static_cast<char*>(lValue);
		printf("lValue(str) = %s\n", pstr);
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}

	printf("node.Cur_Type : ");
	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		std::cout << "NUMBER" << std::endl;
		break;
	case JNode::JType::DOUBLE:
		std::cout << "DOUBLE" << std::endl;
		break;
	case JNode::JType::BOOL:
		std::cout << "BOOL" << std::endl;
		break;
	case JNode::JType::STRING:
		std::cout << "STRING" << std::endl;
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		pnum = static_cast<int*>(node.P_Type);
		printf("node.P_Type(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		pdnum = static_cast<double*>(node.P_Type);
		printf("node.P_Type(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		pbl = static_cast<bool*>(node.P_Type);
		printf("node.P_Type(bool) = %d\n", *pbl);
		break;
	case JNode::JType::STRING:
		str = static_cast<DynamicStr*>(node.P_Type);
		printf("node.P_Type(str) = %s\n", str->Get_Str());
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}
}

void Ver_Get_Test_After(JNode& node, JNode::JType lValueType, void* lValue, bool c_ck = false) {
	int* pnum = nullptr;
	double* pdnum = nullptr;
	bool* pbl = nullptr;
	DynamicStr* str = nullptr;
	char* pstr = nullptr;
	char* c = nullptr;

	if (lValue == nullptr){
		printf("<반환 이후>\n");
		printf("lValue 상태 : ");
		printf("lValue == nullptr 실패\n");
		return;
	}

	printf("<반환 이후>\n");
	printf("lValue 상태 : ");
	switch (lValueType){
	case JNode::JType::NUMBER:
		pnum = static_cast<int*>(lValue);
		printf("lValue(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		pdnum = static_cast<double*>(lValue);
		printf("lValue(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		pbl = static_cast<bool*>(lValue);
		printf("lValue(bool) = %d\n", *pbl);
		break;
	case JNode::JType::STRING:
		if (c_ck){
			c = static_cast<char*>(lValue);
			printf("lValue(char) = %c\n", c[0]);
			break;
		}
		pstr = static_cast<char*>(lValue);
		printf("lValue(str) = %s\n", pstr);
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}

	printf("node.Cur_Type : ");
	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		std::cout << "NUMBER" << std::endl;
		break;
	case JNode::JType::DOUBLE:
		std::cout << "DOUBLE" << std::endl;
		break;
	case JNode::JType::BOOL:
		std::cout << "BOOL" << std::endl;
		break;
	case JNode::JType::STRING:
		std::cout << "STRING" << std::endl;
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}

	switch (node.Cur_Type){
	case JNode::JType::NUMBER:
		pnum = static_cast<int*>(node.P_Type);
		printf("node.P_Type(int) = %d\n", *pnum);
		break;
	case JNode::JType::DOUBLE:
		pdnum = static_cast<double*>(node.P_Type);
		printf("node.P_Type(double) = %.3f\n", *pdnum);
		break;
	case JNode::JType::BOOL:
		pbl = static_cast<bool*>(node.P_Type);
		printf("node.P_Type(bool) = %d\n", *pbl);
		break;
	case JNode::JType::STRING:
		str = static_cast<DynamicStr*>(node.P_Type);
		printf("node.P_Type(str) = %s\n", str->Get_Str());
		break;
	case JNode::JType::OBJ:
		std::cout << "OBJ" << std::endl;
		break;
	case JNode::JType::ARR:
		std::cout << "ARR" << std::endl;
		break;
	case JNode::JType::NULLTYPE:
		std::cout << "NULLTYPE" << std::endl;
		break;
	}
}


void JNode_Fin_Set_Test() {
	JNode node;
	JNode *pnode = new JNode();

	JNode* obj_node = new JNode(JNode::JType::OBJ);
	JNode* arr_node = new JNode(JNode::JType::ARR);


	//int 테스트 대입
	Ver_Set_Test_Before(node);
	printf("node = 10\n");
	node = 10;
	Ver_Set_Test_After(node, JNode::JType::NUMBER);

	printf("\n\n");

	//double 테스트 대입
	Ver_Set_Test_Before(node);
	printf("node = 1.0\n");
	node = 1.0;
	Ver_Set_Test_After(node, JNode::JType::DOUBLE);

	printf("\n\n");

	//bool 테스트 대입
	Ver_Set_Test_Before(node);
	printf("node = true\n");
	node = true;
	Ver_Set_Test_After(node, JNode::JType::BOOL);

	printf("\n\n");

	//string 테스트 대입
	Ver_Set_Test_Before(node);
	printf("node = 't'\n");
	node = 't';
	Ver_Set_Test_After(node, JNode::JType::STRING);

	printf("\n\n");

	Ver_Set_Test_Before(node);
	printf("node = OBJ\n");
	node = JNode::JType::OBJ;
	Ver_Set_Test_After(node, JNode::JType::OBJ);


	printf("\n\n");

	Ver_Set_Test_Before(node);
	printf("node = ARR\n");
	node = JNode::JType::ARR;
	Ver_Set_Test_After(node, JNode::JType::ARR);


	printf("\n\n");

	Ver_Set_Test_Before(node);
	printf("node = obj_node(JNode)\n");
	node = obj_node;
	Ver_Set_Test_After(node, JNode::JType::OBJ);
	printf("obj_node->P_Type : %p\n", obj_node->P_Type);


	printf("\n\n");

	Ver_Set_Test_Before(node);
	printf("node = arr_node(JNode)\n");
	node = arr_node;
	Ver_Set_Test_After(node, JNode::JType::ARR);
	printf("arr_node->P_Type : %p\n", arr_node->P_Type);

	int num = 10;
	int* pnum = &num;
	double dnum = 10.0;
	double* pdnum = &dnum;
	bool bl = true;
	bool* pbl = &bl;
	char c = 't';
	const char* str = "Test";
	
	Ver_Set_Test_Before_2(node);
	printf("node = num\n");
	node = num;
	Ver_Set_Test_After_2(node, JNode::JType::NUMBER);

	printf("\n\n");

	Ver_Set_Test_Before_2(node);
	printf("node = pnum\n");
	node = pnum;
	Ver_Set_Test_After_2(node, JNode::JType::NUMBER);

	printf("\n\n");

	Ver_Set_Test_Before_2(node);
	printf("node = dnum\n");
	node = dnum;
	Ver_Set_Test_After_2(node, JNode::JType::DOUBLE);

	printf("\n\n");

	Ver_Set_Test_Before_2(node);
	printf("node = pdnum\n");
	node = pdnum;
	Ver_Set_Test_After_2(node, JNode::JType::DOUBLE);

	printf("\n\n");

	Ver_Set_Test_Before_2(node);
	printf("node = bl\n");
	node = bl;
	Ver_Set_Test_After_2(node, JNode::JType::BOOL);

	printf("\n\n");

	Ver_Set_Test_Before_2(node);
	printf("node = pbl\n");
	node = pbl;
	Ver_Set_Test_After_2(node, JNode::JType::BOOL);

	printf("\n\n");

	Ver_Set_Test_Before_2(node);
	printf("node = *str\n");
	node = str;
	Ver_Set_Test_After_2(node, JNode::JType::STRING);

	printf("\n\n");

	Ver_Set_Test_Before_2(node);
	printf("node = c\n");
	node = c;
	Ver_Set_Test_After_2(node, JNode::JType::STRING);

	printf("\n\n");

	Ver_Set_Test_Before_2(node);
	printf("node = str\n");
	node = *str;
	Ver_Set_Test_After_2(node, JNode::JType::STRING);

	printf("\n\n");
}

void JNode_Fin_Get_Test(){
	JNode node;
	JNode* pnode = new JNode();

	int num = 10;
	int* pnum = &num;
	double dnum = 10.0;
	double* pdnum = &dnum;
	bool bl = true;
	bool* pbl = &bl;
	char c = 't';
	char* str = "Test";

	//반환 테스트 실패만
	printf("<실패의 경우만> \n\n");
	Ver_Get_Test_Before(node, JNode::JType::NUMBER, &num);
	printf("------------------------------\n");
	printf("★ num(%d) = node(P_Type==nullptr)\n", num);
	printf("------------------------------\n");
	num = node;
	Ver_Get_Test_After(node, JNode::JType::NUMBER, &num);

	printf("\n\n");
	num = 100;

	Ver_Get_Test_Before(node, JNode::JType::NUMBER, pnum);
	printf("------------------------------\n");
	printf("★ pnum(%d) = node(P_Type==nullptr)\n", *pnum);
	printf("------------------------------\n");
	pnum = node;
	Ver_Get_Test_After(node, JNode::JType::NUMBER, pnum);

	printf("\n\n");

	Ver_Get_Test_Before(node, JNode::JType::DOUBLE, &dnum);
	printf("------------------------------\n");
	printf("★ dnum(%.3f) = node(P_Type==nullptr)\n", dnum);
	printf("------------------------------\n");
	dnum = node;
	Ver_Get_Test_After(node, JNode::JType::DOUBLE, &dnum);

	printf("\n\n");
	dnum = 100.00;

	Ver_Get_Test_Before(node, JNode::JType::DOUBLE, pdnum);
	printf("------------------------------\n");
	printf("★ pdnum(%.3f) = node(P_Type==nullptr)\n", *pdnum);
	printf("------------------------------\n");
	pdnum = node;
	Ver_Get_Test_After(node, JNode::JType::DOUBLE, pdnum);

	printf("\n\n");

	Ver_Get_Test_Before(node, JNode::JType::BOOL, &bl);
	printf("------------------------------\n");
	printf("★ bl(%d) = node(P_Type==nullptr)\n", bl);
	printf("------------------------------\n");
	bl = node;
	Ver_Get_Test_After(node, JNode::JType::BOOL, &bl);

	printf("\n\n");
	bl = true;

	Ver_Get_Test_Before(node, JNode::JType::BOOL, pbl);
	printf("------------------------------\n");
	printf("★ pbl(%d) = node(P_Type==nullptr)\n", *pbl);
	printf("------------------------------\n");
	pbl = node;
	Ver_Get_Test_After(node, JNode::JType::BOOL, pbl);

	printf("\n\n");

	Ver_Get_Test_Before(node, JNode::JType::STRING, &c, true);
	printf("------------------------------\n");
	printf("★ c(%c) = node(P_Type==nullptr)\n", c);
	printf("------------------------------\n");
	c = node;
	Ver_Get_Test_After(node, JNode::JType::STRING, &c, true);

	printf("\n\n");

	Ver_Get_Test_Before(node, JNode::JType::STRING, str);
	printf("------------------------------\n");
	printf("★ str(%s) = node(P_Type==nullptr)\n", str);
	printf("------------------------------\n");
	str = node;
	Ver_Get_Test_After(node, JNode::JType::STRING, str);

}



void obj_prt(JNode& obj_node){
	JObj* root_obj = static_cast<JObj*>(obj_node.P_Type);
	JObj* cur_obj = root_obj;

	int* num = nullptr;
	double* dnum = nullptr;
	bool* bl = nullptr;
	char* c = nullptr;
	DynamicStr* str = nullptr;

	printf("\n <개수 : %d>\n", obj_node.ObjCnt);

	if (obj_node.ObjCnt == -1) {
		printf("{}\n");
		return;
	}
	printf("{");
	for (;;){
		printf("%s : ", cur_obj->Key.Get_Str());

		
		switch(cur_obj->Value->Cur_Type){
		case JNode::JType::NUMBER:
			num = static_cast<int*>(cur_obj->Value->P_Type);
			printf("%d", *num);
			break;
		case JNode::JType::DOUBLE:
			dnum = static_cast<double*>(cur_obj->Value->P_Type);
			printf("%.3f", *dnum);
			break;
		case JNode::JType::BOOL:
			bl = static_cast<bool*>(cur_obj->Value->P_Type);
			printf("%s", bl ? "true" : "false");
			break;
		case JNode::JType::STRING:
			str = static_cast<DynamicStr*>(cur_obj->Value->P_Type);
			printf("%s", str->Get_Str());
			break;
		case JNode::JType::OBJ:
			printf("{}");
			break;
		case JNode::JType::ARR:
			printf("[]");
			break;
		case JNode::JType::NULLTYPE:
			printf(" ");
			break;
		}

		if (cur_obj->next == nullptr){
			printf("}\n");
			break;
		}

		printf(", ");

		cur_obj = cur_obj->next;
	}
}

void arr_prt(JNode& arr_node){
	JArr* root_arr = static_cast<JArr*>(arr_node.P_Type);
	JArr* cur_arr = root_arr;

	int* num = nullptr;
	double* dnum = nullptr;
	bool* bl = nullptr;
	char* c = nullptr;
	DynamicStr* str = nullptr;

	printf("\n <개수 : %d>\n", arr_node.ArrCnt);

	if (arr_node.ArrCnt == -1){
		printf("[]\n");
		return;
	}

	printf("[");
	for (;;){
		switch (cur_arr->Value->Cur_Type){
		case JNode::JType::NUMBER:
			num = static_cast<int*>(cur_arr->Value->P_Type);
			printf("%d", *num);
			break;
		case JNode::JType::DOUBLE:
			dnum = static_cast<double*>(cur_arr->Value->P_Type);
			printf("%.3f", *dnum);
			break;
		case JNode::JType::BOOL:
			bl = static_cast<bool*>(cur_arr->Value->P_Type);
			printf("%s", bl ? "true" : "false");
			break;
		case JNode::JType::STRING:
			str = static_cast<DynamicStr*>(cur_arr->Value->P_Type);
			printf("%s", str->Get_Str());
			break;
		case JNode::JType::OBJ:
			printf("{}");
			break;
		case JNode::JType::ARR:
			printf("[]");
			break;
		case JNode::JType::NULLTYPE:
			printf(" ");
			break;
		}

		if (cur_arr->next == nullptr){
			printf("]\n");
			break;
		}

		printf(", ");

		cur_arr = cur_arr->next;
	}

}

void JNode_Obj_Test(){
	//JNode["Key"]에 대한 대입
	JNode obj_node(JNode::JType::OBJ);

	//obj_node["Key0"] = 1;

	obj_prt(obj_node);

	printf("\n\n");

	obj_node["Key0"] = 1;
	obj_node["Key1"] = 1.0;

	obj_prt(obj_node);

	obj_node["Key0"] = 'T';
	obj_node["Key1"] = "Test";

	obj_prt(obj_node);

	obj_node["Key0"] = true;
	obj_node["Key1"] = 1000;

	obj_prt(obj_node);

	int num = 10;
	double dnum = 1.0;
	bool bl = true;
	char c = 'A';

	obj_node["Key0"] = num;
	obj_node["Key1"] = dnum;
	obj_node["Key2"] = bl;
	obj_node["Key3"] = c;

	obj_prt(obj_node);

	int* pnum = &num;
	double* pdnum = &dnum;
	bool* pbl = &bl;
	char* str = "Test";

	obj_node["Key0"] = pnum;
	obj_node["Key1"] = pdnum;
	obj_node["Key2"] = pbl;
	obj_node["Key3"] = str;

	obj_prt(obj_node);

	JNode node_obj(JNode::JType::OBJ);
	JNode node_arr(JNode::JType::ARR);
	//obj_node["Key0"] = node_arr;
	//obj_node["Key0"] = node_obj; 안되는거 맞음 내가 막아놓음

	JNode* pnode_obj = new JNode(JNode::JType::OBJ);
	JNode* pnode_arr = new JNode(JNode::JType::ARR);
	obj_node["Key0"] = pnode_obj;
	obj_node["Key1"] = pnode_arr;

	obj_prt(obj_node);

	obj_node["Key0"] = 10;
	obj_node["Key1"] = 10.0;
	obj_node["Key2"] = true;
	obj_node["Key3"] = 'T';
	obj_node["Key4"] = "Test";

	obj_prt(obj_node);

	num = obj_node["Key0"];
	dnum = obj_node["Key1"];
	bl = obj_node["Key2"];
	c = obj_node["Key3"];
	str = obj_node["Key4"];

	printf("num : %d\n", num);
	printf("dnum : %.3f\n", dnum);
	printf("bl : %s\n", bl ? "True" : "False");
	printf("c : %c\n", c);
	printf("str : %s\n", str);

	pnum = obj_node["Key0"];
	pdnum = obj_node["Key1"];
	pbl = obj_node["Key2"];

	printf("num : %d\n", *pnum);
	printf("dnum : %.3f\n", *pdnum);
	printf("bl : %s\n", *pbl ? "True" : "False");



}

void JNode_Arr_Test(){
	JNode arr_node(JNode::JType::ARR);

	arr_prt(arr_node);

	arr_node[0] = 10;
	arr_node[1] = 1.0;
	arr_node[2] = true;
	arr_node[3] = 'T';
	arr_node[4] = "Test";

	arr_prt(arr_node);

	arr_node[0] = 1.0;
	arr_node[1] = 10;
	arr_node[2] = 'T';
	arr_node[3] = "Test";
	arr_node[4] = false;

	arr_prt(arr_node);

	JNode* obj = new JNode(JNode::JType::OBJ);

	arr_node[5] = obj;

	JNode* arr = new JNode(JNode::JType::ARR); 

	arr_node[6] = arr;

	arr_prt(arr_node);

	int num = 10;
	double dnum = 1.0;
	bool bl = true;
	char c = 'A';

	arr_node[0] = num;
	arr_node[1] = dnum;
	arr_node[2] = bl;
	arr_node[3] = c;

	arr_prt(arr_node);

	int* pnum = &num;
	double* pdnum = &dnum;
	bool* pbl = &bl;
	char* str = "Test";

	arr_node[0] = pnum;
	arr_node[1] = pdnum;
	arr_node[2] = pbl;
	arr_node[3] = str;

	arr_prt(arr_node);

	arr_node[0] = 10;
	arr_node[1] = 10.0;
	arr_node[2] = true;
	arr_node[3] = 'T';
	arr_node[4] = "Test";

	num = arr_node[0];
	dnum = arr_node[1];
	bl = arr_node[2];
	c = arr_node[3];
	str = arr_node[4];

	printf("num : %d\n", num);
	printf("dnum : %.3f\n", dnum);
	printf("bl : %s\n", bl ? "True" : "False");
	printf("c : %c\n", c);
	printf("str : %s\n", str);

	pnum = arr_node[0];
	pdnum = arr_node[1];
	pbl = arr_node[2];

	printf("num : %d\n", *pnum);
	printf("dnum : %.3f\n", *pdnum);
	printf("bl : %s\n", *pbl ? "True" : "False");

	arr_node[-1] = false;

	arr_prt(arr_node);

	//arr_node[4] = DEL;

	JNode* lNode;

	lNode = arr_node[4];

	if (lNode->Cur_Type == JNode::JType::STRING){
		printf("lNode String 타입\n");
		char* new_str = *lNode;
		printf("lNode->P_Type == %s\n", new_str);
	}

	lNode->push() = 10;

	arr_prt(arr_node);

	arr_prt(*lNode);

	//삭제

	printf("\n\n<삭제 부분>\n");

	arr_prt(arr_node);
	

	


}

void JNode_Obj_Arr_Del_Test(){
	JNode obj_node(JNode::JType::OBJ);
	JNode arr_node(JNode::JType::ARR);

	obj_node["Key0"] = 1;
	obj_node["Key1"] = 2;
	obj_node["Key2"] = "A";
	obj_node["Key3"] = true;
	obj_node["Key4"] = "Obj_Test";

	arr_node.push() = 1;
	arr_node.push() = 2;
	arr_node.push() = "A";
	arr_node.push() = true;
	arr_node.push() = "Arr_Test";

	obj_prt(obj_node);
	arr_prt(arr_node);

	//삭제 진행
	arr_node.arr_del(1);

	arr_prt(arr_node);

	arr_node.arr_del();

	arr_prt(arr_node);

	arr_node.arr_del();
	arr_node.arr_del();
	arr_node.arr_del();
	arr_node.arr_del();

	arr_prt(arr_node);

	obj_prt(obj_node);

	obj_node.obj_del();

	obj_prt(obj_node);

	obj_node.obj_del("Key0");
	obj_node.obj_del("Key1");
	obj_node.obj_del("Key3");
	obj_node.obj_del("Key4");

	obj_prt(obj_node);

	arr_node.push() = 1;
	arr_node.push() = 2;
	arr_node.push() = "A";
	arr_node.push() = true;
	arr_node.push() = "Arr_Test";

	arr_prt(arr_node);

	arr_node[0] = "T";

	arr_prt(arr_node);

	arr_node.arr_del(0);

	obj_node["Key0"] = 1;
	obj_node["Key10"] = true;


	printf("\n\n\n last Test\n");
	arr_prt(arr_node);
	obj_prt(obj_node);


	obj_node.del();
	arr_node.del();

	arr_prt(arr_node);
	obj_prt(obj_node);
	
	arr_node.push() = 10;
	obj_node.push() = 10;

	arr_prt(arr_node);



}

int main() {

	//JsonAPI_Test();
	//JsonAPI_Test2();
	//JsonAPI_Test3();
	
	//JNode_Test();


	//JNode_Fin_Set_Test();

	//JNode_Fin_Get_Test();

	//JNode_Obj_Test();

	//JNode_Arr_Test(); 
	JNode_Obj_Arr_Del_Test();

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