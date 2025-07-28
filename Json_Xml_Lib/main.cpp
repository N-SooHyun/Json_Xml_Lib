#include "Main.h"
using namespace JSON;

void JsonAPI_Test(){
	//��ȯ ������
	JNode* pjs = new JNode(JNode::JType::NUMBER);	
	JNode js(JNode::JType::NUMBER);
	

	int num = *pjs;
	int* pnum = *pjs;
	num = js;
	pnum = js;

	pjs->delType();
	js.delType();
	
	pjs->setType(JNode::JType::DOUBLE);
	js.setType(JNode::JType::DOUBLE);

	double dnum = *pjs;
	double *pdnum = *pjs;
	dnum = js; 
	pdnum = js;

	pjs->delType();
	js.delType();
	pjs->setType(JNode::JType::BOOL);
	js.setType(JNode::JType::BOOL);

	bool bl = *pjs;
	bool* pbl = *pjs;
	bl = js; 
	pbl = js;

	pjs->delType();
	js.delType();
	pjs->setType(JNode::JType::STRING);
	js.setType(JNode::JType::STRING);

	char c = *pjs;
	char* str = *pjs;
	c = js;
	str = js;

	pjs->delType();
	js.delType();

	

	delete pjs;
}

void JsonAPI_Test2(){
	//���� ������ 
	JNode* pjs = new JNode(JNode::JType::NUMBER);
	JNode js(JNode::JType::NUMBER);

	int num = -1;
	int* pnum = &num;
	double dnum = -1.0;
	double* pdnum = &dnum;
	bool bl = true;
	bool* pbl = &bl;
	char c = 'a';
	char *str = "Test";

	*pjs = num;
	*pjs = pnum;
	js = num;
	js = pnum;

	pjs->delType();
	js.delType();
	pjs->setType(JNode::JType::DOUBLE);
	js.setType(JNode::JType::DOUBLE);

	*pjs = dnum;
	*pjs = pdnum;
	js = dnum;
	js = pdnum;

	pjs->delType();
	js.delType();
	pjs->setType(JNode::JType::BOOL);
	js.setType(JNode::JType::BOOL);

	*pjs = bl;
	*pjs = pbl;
	js = bl; 
	js = pbl;

	pjs->delType();
	js.delType();
	pjs->setType(JNode::JType::STRING);
	js.setType(JNode::JType::STRING);

	*pjs = c;
	*pjs = str;
	js = c;
	js = str;

	delete pjs;
}

void JsonAPI_Test3(){
	//���� ������ ����� ���ɿ��� Ȯ��
	JNode* pjs = new JNode(JNode::JType::DOUBLE);
	JNode js(JNode::JType::DOUBLE);

	int num = -1;
	int* pnum = &num;
	double dnum = -1.0;
	double* pdnum = &dnum;
	bool bl = true;
	bool* pbl = &bl;
	char c = 'a';
	char *str = "Test";

	*pjs = num;
	js = num;

	pjs->delType();
	js.delType();

	*pjs = pnum;
	js = pnum;

	pjs->delType();
	js.delType();

	*pjs = 2;
	js = 3;

	*pjs = 1.0;
	js = 2.0;

	pjs->delType();
	js.delType();

	*pjs = 2.0;
	js = 3.0;

	*pjs = true;
	js = true;

	*pjs = 'a';
	js = 'a'; 

	pjs->delType();
	js.delType();

	*pjs = "str";
	js = "Test";


}

void JOBj_JArr_Test(){
	//���� ��ȯ API ���� �׽�Ʈ
	JNode* pjs = new JNode(JNode::JType::DOUBLE);
	JNode js(JNode::JType::DOUBLE);

	int num = -1;
	int* pnum = &num;
	double dnum = -1.0;
	double* pdnum = &dnum;
	bool bl = true;
	bool* pbl = &bl;
	char c = 'a';
	char *str = "Test";

	*pjs = 1;
	js = 1;

	num = js;


	//��ü�� ȣ���ϴ� ȣ���� API �������̽�
	js["Key0"] = num;
	js["Key1"] = pnum;
	js["key2"] = dnum;
	js["key3"] = pdnum;
	js["key4"] = bl;
	js["key5"] = pbl;
	js["key6"] = c;
	js["key7"] = str;

	js["Key0"] = str;
	js["Key1"] = bl;

	num = js["Key0"];
	*pnum = js["Key1"];
	dnum = js["key2"];
	pdnum = js["key3"];
	bl = js["key4"];
	pbl = js["key5"]; 
	c = js["key6"];
	str = js["key7"];

	



}

void JObj_Test(){
	JNode node1(JNode::JType::NUMBER);
	JNode node2(JNode::JType::NUMBER);
	JNode node3(JNode::JType::NUMBER);

	JObj obj;		//Key0��
	JObj* root_obj = &obj;	//head
	JObj* cur_obj = &obj;	//tail
	
	cur_obj->setKey("Key0");

	//����� �߰�
	cur_obj->next = new JObj();
	cur_obj = cur_obj->next;

	cur_obj->setKey("Key1");

	//����� �߰�
	cur_obj->next = new JObj();
	cur_obj = cur_obj->next;

	cur_obj->setKey("Key2");
	

	JObj* search_obj;

	search_obj = obj.searchKey("Key3");

	
}

void JNode_Test(){
	JNode Def_Node;
	JNode *pDef_Node = new JNode();
	JNode L_Node(JNode::JType::NUMBER); 
	//�Ѵ� p_type�� ������
	
	//JNode::operator =�����̸鼭 ��ȯ
	Def_Node = pDef_Node;		//�������϶�
	//Def_Node = L_Node;			//���������϶�



}

int main() {

	//JsonAPI_Test();
	//JsonAPI_Test2();
	//JsonAPI_Test3();
	//JOBj_JArr_Test();

	//JObj_Test();

	JNode_Test();

	return 0;
}