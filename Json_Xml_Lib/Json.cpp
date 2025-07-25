#include "Main.h"

using namespace std;
using namespace Dynamic;
using namespace JSON;


//<JNode class>--------------------------------------------------------------------------------------
void JNode::delType(){
	//���߼Ҹ��� ���� ���� ����
	if (isTypeNull()){
		return;
	}

	JType Del_Node_Type= this->Cur_Type;
	switch (Del_Node_Type){
		case JType::OBJ:
		{
			JObj* obj = static_cast<JObj*>(P_Type);
			delete obj;
			break;
		}
		case JType::ARR:
		{
			JArr* arr = static_cast<JArr*>(P_Type);
			delete arr;
			break;
		}
		case JType::STRING:
		{
			DynamicStr* str = static_cast<DynamicStr*>(P_Type);
			delete str;
			break;
		}
		case JType::NUMBER:
		{
			int* num = static_cast<int*>(P_Type);
			delete num;
			break;
		}
		case JType::BOOL:
		{
			bool* bl = static_cast<bool*>(P_Type);
			delete bl;
			break;
		}
		case JType::DOUBLE:
		{
			double* dnum = static_cast<double*>(P_Type);
			delete dnum;
			break;
		}
		default:
		case JType::NULLTYPE:
		{
			break;
		}
	}
	P_Type = nullptr;
	Cur_Type = JType::NULLTYPE;
}

void JNode::setType(JType Set_Node_Type){
	if (!isTypeNull()){
		//P_Type�� �����ϱ� ������ �Ҹ��ϰ� ����� �ϱ⿡ ��ȯ
		return;
	}
	ObjCnt = -2;
	ArrCnt = -2;
	Cur_Type = Set_Node_Type;
	switch (Cur_Type) {
		case JType::OBJ:
		{
			P_Type = new JObj();
			ObjCnt = -1;
			break;
		}
		case JType::ARR:
		{
			P_Type = new JArr();
			ArrCnt = -1;
			break;
		}
		case JType::STRING:
		{
			P_Type = new Dynamic::DynamicStr(128);
			Dynamic::DynamicStr* init_str = static_cast<Dynamic::DynamicStr*>(P_Type);
			init_str->Set_Str("0\0");
			break;
		}
		case JType::NUMBER:
		{
			P_Type = new int(); // �⺻������ int�� �ʱ�ȭ
			int* init_num = static_cast<int*>(P_Type);
			*init_num = 0;
			break;
		}
		case JType::BOOL:
		{
			P_Type = new bool();
			bool* init_bool = static_cast<bool*>(P_Type);
			*init_bool = false;
			break;
		}
		case JType::DOUBLE:
		{
			P_Type = new double();
			double* init_dnum = static_cast<double*>(P_Type);
			*init_dnum = 0.0;
			break;
		}
		case JType::NULLTYPE:
		{
			P_Type = nullptr; // null Ÿ���� �����͸� ������� ����
			break;
		}
		default:
		{
			P_Type = nullptr; // �⺻������ nullptr�� �ʱ�ȭ
			break;
		}
	}
}

void* JNode::getPType(){
	if (isTypeNull()){
		return P_Type;
	}
	return nullptr;
}

JNode::JType JNode::getType(){
	return this->Cur_Type;
}


//���ڿ� �Ľ� �κ�
void JNode::isObjArrCk(DynamicStr* str){
	const char* Str = str->Get_Str();
	short first_focus = 0;
	short last_focus = str->str_last_focus;

	if (Str[first_focus] == '\"' && Str[last_focus] == '\"'){
		first_focus++;
		last_focus--;
	}

	if (Str[first_focus] == '{' && Str[last_focus] == '}'){
		//��ü�� 
		//Parsing ���� �Լ� ȣ�� �ϵ簡 �ϼ�
	}
	else if (Str[first_focus] == '[' && Str[last_focus] == ']'){
		//�迭��
		//Parsing ���� �Լ� ȣ�� �ϵ簡 �ϼ�
	}	
}


//����ó�����
bool JNode::isTypeNull(){
	if (P_Type != nullptr) return false;
	return true;
}
bool JNode::isTypeMatch(JType match_type){
	if (Cur_Type == match_type) return true;
	return false;
}

//��ȯ ������ = P_Type�� ��ȯ
JNode::operator int(){
	if (isTypeNull() && !isTypeMatch(JType::NUMBER)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return -1;
	}
	
	int* num = static_cast<int*>(P_Type);

	return *num;
}
JNode::operator int*(){
	if (isTypeNull() && !isTypeMatch(JType::NUMBER)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}

	int* num = static_cast<int*>(P_Type);

	return num;	
}
JNode::operator double(){
	if (isTypeNull() && !isTypeMatch(JType::DOUBLE)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return -1.0;
	}
	double* dnum = static_cast<double*>(P_Type);

	return *dnum;
}
JNode::operator double*(){
	if (isTypeNull() && !isTypeMatch(JType::DOUBLE)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}
	double* dnum = static_cast<double*>(P_Type); 
	return dnum;
}
JNode::operator bool(){
	if (isTypeNull() && !isTypeMatch(JType::BOOL)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return false;
	}
	bool* bl = static_cast<bool*>(P_Type);
	return *bl;
}
JNode::operator bool*(){
	if (isTypeNull() && !isTypeMatch(JType::BOOL)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}
	bool* pbl = static_cast<bool*>(P_Type);
	return pbl;
}
JNode::operator char(){
	if (isTypeNull() && !isTypeMatch(JType::STRING)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return '\0';
	}
	DynamicStr* str = static_cast<DynamicStr*>(P_Type);
	char* c = str->Get_Str();
	return c[0];
}
JNode::operator char*(){
	if (isTypeNull() && !isTypeMatch(JType::STRING)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}
	DynamicStr* str = static_cast<DynamicStr*>(P_Type); 
	return str->Get_Str();
}
//Node�� ��ȭ�Ҷ� ó��


//���� ������ P_Type = ����
void JNode::operator=(int _num){
	if (!isTypeMatch(JType::NUMBER)){
		//Ÿ���� �ȸ����� ����Ŵϱ� �����ּ�
		delType();
		Cur_Type = JType::NUMBER;
		setType(Cur_Type);
	}

	int* num = static_cast<int*>(P_Type);
	*num = _num; //����
}
void JNode::operator=(int* _pnum){
	if (!isTypeMatch(JType::NUMBER)){
		//Ÿ���� �ȸ����� ����Ŵϱ� �����ּ�
		delType();
		Cur_Type = JType::NUMBER;
		setType(Cur_Type);
	}
	int* pnum = static_cast<int*>(P_Type);
	*pnum = *_pnum; //���� ����X
}
void JNode::operator=(double _dnum){
	if (!isTypeMatch(JType::DOUBLE)){
		//Ÿ���� �ȸ����� ����Ŵϱ� �����ּ�
		delType();
		Cur_Type = JType::DOUBLE;
		setType(Cur_Type);
	}
	double* dnum = static_cast<double*>(P_Type); 
	*dnum = _dnum;	//����
}
void JNode::operator=(double* _pdnum){
	if (!isTypeMatch(JType::DOUBLE)){
		//Ÿ���� �ȸ����� ����Ŵϱ� �����ּ�
		delType();
		Cur_Type = JType::DOUBLE;
		setType(Cur_Type);
	}
	double* dnum = static_cast<double*>(P_Type);
	*dnum = *_pdnum; //���� ���� X
}
void JNode::operator=(bool _bl){
	if (!isTypeMatch(JType::BOOL)){
		//Ÿ���� �ȸ����� ����Ŵϱ� �����ּ�
		delType();
		Cur_Type = JType::BOOL;
		setType(Cur_Type);
	}
	bool* bl = static_cast<bool*>(P_Type);
	*bl = _bl;	//����
}
void JNode::operator=(bool* _pbl){
	if (!isTypeMatch(JType::BOOL)){
		//Ÿ���� �ȸ����� ����Ŵϱ� �����ּ�
		delType();
		Cur_Type = JType::BOOL;
		setType(Cur_Type);
	}
	bool* bl = static_cast<bool*>(P_Type);
	*bl = *_pbl;	//���� ����X
}
void JNode::operator=(char _c){
	if (!isTypeMatch(JType::STRING)){
		//Ÿ���� �ȸ����� ����Ŵϱ� �����ּ�
		delType();
		Cur_Type = JType::STRING;
		setType(Cur_Type);
	}
	DynamicStr* c = static_cast<DynamicStr*>(P_Type);
	char* pc = &_c;
	c->Set_Char(pc);	//����
}
void JNode::operator=(char* _str){
	if (!isTypeMatch(JType::STRING)){
		//Ÿ���� �ȸ����� ����Ŵϱ� �����ּ�
		delType();
		Cur_Type = JType::STRING;
		setType(Cur_Type);
	}
	DynamicStr* str = static_cast<DynamicStr*>(P_Type);
	str->Set_Str(_str);	//����

	//���ڿ� �Ľ� �κ�
	isObjArrCk(str);
}
//Node�� ������ ó��


//��ü�� �迭�� ���� ������
//Node["Key"]
JsonCallObjArr JNode::operator[](const char* key){
	//ObjŸ���� �ƴѰ��? 1. �����, 2. �����ϱ� 1�� ����
	if (!isTypeMatch(JType::OBJ)){
		//Ÿ���� �ȸ´°�� ������ϱ� �����ּ�
		delType();
		setType(JType::OBJ);
		JsonCallObjArr Success(this, key);
		return Success;
	}
	JsonCallObjArr Success(this, key);
	return Success;
}
//Node[1]
JsonCallObjArr JNode::operator[](int index){
	//ArrŸ���� �ƴѰ��? 1. ����� 2. �����ϱ� 1�� ����
	if (!isTypeMatch(JType::ARR)){
		delType();
		Cur_Type = JType::ARR; 
		JsonCallObjArr Success(this, index);
		return Success;
	}
	JsonCallObjArr Success(this, index);
	return Success;
}

//<JObj class>--------------------------------------------------------------------------------------


//<JArr class>--------------------------------------------------------------------------------------


//<JsonCtrl class>----------------------------------------------------------------------------------


//<JsonCallObjArr class>-------------------------------------------------------------------------------


//<JsonCallArr class>-------------------------------------------------------------------------------

//��ȯ ������ = Obj["Key"] ���� ��ȯ
//= Arr[1]
JsonCallObjArr::operator int(){
	if (obj == nullptr) return -1; //���� �ϴ� ���
	if (!obj->Value->isTypeMatch(JNode::JType::NUMBER)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return -1;
	}

	int* num = static_cast<int*>(obj->Value->P_Type);

	return *num;
}
JsonCallObjArr::operator int*(){
	if (obj == nullptr) return nullptr; //���� �ϴ� ���
	if (!obj->Value->isTypeMatch(JNode::JType::NUMBER)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}

	int* num = static_cast<int*>(obj->Value->P_Type);

	return num;
}
JsonCallObjArr::operator double(){
	if (obj == nullptr) return -1.0; //���� �ϴ� ���
	if (!obj->Value->isTypeMatch(JNode::JType::DOUBLE)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return -1.0;
	}

	double* num = static_cast<double*>(obj->Value->P_Type);

	return *num;
}
JsonCallObjArr::operator double*(){
	if (obj == nullptr) return nullptr; //���� �ϴ� ���
	if (!obj->Value->isTypeMatch(JNode::JType::DOUBLE)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}

	double* num = static_cast<double*>(obj->Value->P_Type);

	return num;
}
JsonCallObjArr::operator bool(){
	if (obj == nullptr) return false; //���� �ϴ� ���
	if (!obj->Value->isTypeMatch(JNode::JType::BOOL)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return false;
	}

	bool* num = static_cast<bool*>(obj->Value->P_Type);

	return *num;
}
JsonCallObjArr::operator bool*(){
	if (obj == nullptr) return false; //���� �ϴ� ���
	if (!obj->Value->isTypeMatch(JNode::JType::BOOL)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}

	bool* num = static_cast<bool*>(obj->Value->P_Type);

	return num;
}
JsonCallObjArr::operator char(){
	if (obj == nullptr) return '\0'; //���� �ϴ� ���
	if (!obj->Value->isTypeMatch(JNode::JType::STRING)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return '\0';
	}

	DynamicStr* str = static_cast<DynamicStr*>(obj->Value->P_Type);
	char* c = str->Get_Str();
	return c[0];
}
JsonCallObjArr::operator char*(){
	if (obj == nullptr) return nullptr; //���� �ϴ� ���
	if (!obj->Value->isTypeMatch(JNode::JType::STRING)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}

	DynamicStr* str = static_cast<DynamicStr*>(obj->Value->P_Type);
	return str->Get_Str();
}

//���� ������ Obj["Key"] = ���� ���� �ִ����� � �����
// Arr[1] = 
void JsonCallObjArr::operator=(int _num){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::NUMBER);
	int* num = static_cast<int*>(obj->Value->P_Type);
	*num = _num; //����
}
void JsonCallObjArr::operator=(int* _pnum){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::NUMBER);
	int* num = static_cast<int*>(obj->Value->P_Type);
	*num = *_pnum; //����
}
void JsonCallObjArr::operator=(double _dnum){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::DOUBLE);
	double* dnum = static_cast<double*>(obj->Value->P_Type);
	*dnum = _dnum; //����
}
void JsonCallObjArr::operator=(double* _pdnum){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::DOUBLE);
	double* dnum = static_cast<double*>(obj->Value->P_Type);
	*dnum = *_pdnum; //����
}
void JsonCallObjArr::operator=(bool _bl){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::BOOL);
	bool* bl = static_cast<bool*>(obj->Value->P_Type);
	*bl = _bl; //����
}
void JsonCallObjArr::operator=(bool* _pbl){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::BOOL);
	bool* bl = static_cast<bool*>(obj->Value->P_Type);
	*bl = *_pbl; //����
}
void JsonCallObjArr:: operator=(char _c){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::STRING);
	DynamicStr* c = static_cast<DynamicStr*>(obj->Value->P_Type);
	char* pc = &_c;
	c->Set_Char(pc);	//����
}
void JsonCallObjArr::operator=(char* _str){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::STRING);
	DynamicStr* str = static_cast<DynamicStr*>(obj->Value->P_Type);
	str->Set_Str(_str);	//����

	//���ڿ� �Ľ� �κ�
	obj->Value->isObjArrCk(str);
}
