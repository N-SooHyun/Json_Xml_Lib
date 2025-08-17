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

	//if (prev_Node != nullptr){
	//	//prev_Node���� del�� ���¸� �˷������ 
	//	//�ȱ׷��� ���� �Ҹ� �߻���
	//	//� ��ü�� �Ҹ��ߴ��� �˾ƾ� �Ұ�
	//	//� �迭�� �Ҹ��ߴ��� �˾ƾ� �Ұ�
	//	if (prev_obj != nullptr){
	//		
	//	} 
	//	if (prev_arr != nullptr){

	//	}

	//	
	//}
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
	if (!isTypeMatch(JType::NUMBER)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return -1;
	}
	
	int* num = static_cast<int*>(P_Type);

	return *num;
}
JNode::operator int*(){
	if (!isTypeMatch(JType::NUMBER)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}

	int* num = static_cast<int*>(P_Type);

	return num;	
}
JNode::operator double(){
	if (!isTypeMatch(JType::DOUBLE)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return -1.0;
	}
	double* dnum = static_cast<double*>(P_Type);

	return *dnum;
}
JNode::operator double*(){
	if (!isTypeMatch(JType::DOUBLE)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}
	double* dnum = static_cast<double*>(P_Type); 
	return dnum;
}
JNode::operator bool(){
	if (!isTypeMatch(JType::BOOL)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return false;
	}
	bool* bl = static_cast<bool*>(P_Type);
	return *bl;
}
JNode::operator bool*(){
	if (!isTypeMatch(JType::BOOL)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}
	bool* pbl = static_cast<bool*>(P_Type);
	return pbl;
}
JNode::operator char(){
	if (!isTypeMatch(JType::STRING)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return '\0';
	}
	DynamicStr* str = static_cast<DynamicStr*>(P_Type);
	char* c = str->Get_Str();
	return c[0];
}
JNode::operator char*(){
	if (!isTypeMatch(JType::STRING)){
		//�����ϴ� ��� Ÿ���� Null�̰ų� Ÿ�Ը�ġ�� �ȸ´°��
		return nullptr;
	}
	DynamicStr* str = static_cast<DynamicStr*>(P_Type); 
	return str->Get_Str();
}
//Node�� ��ȭ�Ҷ� ó��

//���� ������ P_Type = ����
void JNode::operator=(JType Set_Node_Type){
	if (!isTypeMatch(Set_Node_Type)) {
		//Ÿ���� �ȸ����� ������ϱ� �����ּ�
		delType();
		Cur_Type = Set_Node_Type;
		setType(Cur_Type);
	}
}
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
void JNode::operator=(const char* _str){
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
void JNode::operator=(char* _str) {
	if (!isTypeMatch(JType::STRING)) {
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
//rNode�� lNode�� �����ϴ� ��Ȳ�ε�
//�̷���� rNode->P_Type�� lNode->P_Type�� �����ϰ� �Ǵµ�
//P_Type�� 2���� �ν��Ͻ��� �����ϱ� ������ rNode�� lNode�� �Ҹ��Ҷ�
//���� �Ҹ��� �߻��� �� �����Ƿ�
//rNode�� P_Type�� nullptr�� ������־�� �Ѵ�.
//��, �̰� ����Ѵٴ°� rValue�� ���� ������ delType()���� �������� �ǹ�
//void JNode::operator=(JNode rNode) {
//	//�� �ش� �����ڴ� ���簡 �ƴ� �̵��̶�� �����ϸ� �ȴ�.
//	//�ش� rNode�� ���� ���������� �ƴ� ����������� ������ �ӽð�ü�̹Ƿ�
//	//rNode.P_Type = nullptr�� ���൵
//	//���� ȣ��� �Ű����� rNode.P_Type�� nullptr�� ���� �ʴ´�.
//	//��� �� ������ ����� �� ������ ���Ҵ�.
//	operator=(&rNode);
//}
void JNode::operator=(JNode* rNode) {
	//�� �ش� �����ڴ� ���簡 �ƴ� �̵��̶�� �����ϸ� �ȴ�.
	this->delType(); //���� Ÿ�� ����
	if (rNode->isTypeNull()) {
		//rNode�� NullŸ���ΰ��
		this->setType(JType::NULLTYPE);
		return;
	}
	this->Cur_Type = rNode->Cur_Type;
	this->P_Type = rNode->P_Type; //P_Type�� ����

	this->ObjCnt = rNode->ObjCnt; //��ü ī��Ʈ
	this->ArrCnt = rNode->ArrCnt; //�迭 ī��Ʈ

	//rNode�� P_Type�� nullptr�� ���� ���߼Ҹ� ����
	rNode->P_Type = nullptr;
	rNode->Cur_Type = JType::NULLTYPE; //rNode�� Ÿ���� Null�� ����
}

//��ü�� �迭�� ���� ������
//Node["Key"]
JsonCallObjArr JNode::operator[](const char* key){
	//ObjŸ���� �ƴѰ��? 1. �����, 2. �����ϱ� 1�� ����
	if (!isTypeMatch(JType::OBJ)){
		//Ÿ���� �ȸ´°�� ������ϱ� �����ּ�
		delType();
		setType(JType::OBJ);
		JsonCallObjArr Call(this, key);
		return Call;
	}
	JsonCallObjArr Call(this, key);
	return Call;
}
//Node[1]
JsonCallObjArr JNode::operator[](int index){
	//ArrŸ���� �ƴѰ��? 1. ����� 2. �����ϱ� 1�� ����
	if (!isTypeMatch(JType::ARR)){
		delType();
		setType(JType::ARR);
		JsonCallObjArr Call(this, index);
		return Call;
	}
	JsonCallObjArr Call(this, index);
	return Call;
}

//���� �� index�� �� �ֱ�
JsonCallObjArr JNode::push(){
	if (this->Cur_Type == JNode::JType::OBJ){
		JsonCallObjArr fail;
		return fail;
	}
	//ArrŸ���� �ƴѰ�� �����
	if (!isTypeMatch(JType::ARR)){
		delType();
		setType(JType::ARR);
		JsonCallObjArr call(this, JNode::JType::ARR);
		return call;
	}
	JsonCallObjArr call(this, JNode::JType::ARR);
	return call;
}

//���� �� ��ü�� �� �ֱ� �Ⱦ��°� ������ ���⵵ �� key�ߺ����� �� �־
JsonCallObjArr JNode::obj_push(const char* key){
	JsonCallObjArr j;
	return j;
}

//�ش� �ε��� �����ϱ�
JsonCallObjArr JNode::arr_del(int index){
	//ArrŸ���� �ƴѰ��? �׳� ���� �����ع�����
	if (!isTypeMatch(JType::ARR)){
		JsonCallObjArr failcall;
		return failcall;
	}
	JsonCallObjArr call(this, index, true);
	return call;
}

//�ش� Ű���� ��ü �����ϱ�
JsonCallObjArr JNode::obj_del(const char* key){
	//Obj Ÿ���� �ƴ� ���? �׳� ���� �����ع�����
	if (!isTypeMatch(JType::OBJ)){
		JsonCallObjArr failcall;
		return failcall;
	}
	JsonCallObjArr call(this, key, true);
	return call;
}

//������ ����
JsonCallObjArr* JNode::arr_del(){
	//ArrŸ���� �ƴѰ��? �׳� ���� �����ع�����
	if (!isTypeMatch(JType::ARR)){
		return nullptr;
	}
	return new JsonCallObjArr(this, JNode::JType::ARR, true);
}

//������ ����(�̰Ŵ� ��ȣ�ؼ� �Ⱦ��°� ������ ����)
JsonCallObjArr* JNode::obj_del(){
	//Obj Ÿ���� �ƴ� ���? �׳� ���� �����ع�����
	if (!isTypeMatch(JType::OBJ)){
		return nullptr;
	}
	return new JsonCallObjArr(this, JNode::JType::OBJ, true);
}

JsonCallObjArr* JNode::del(){
	if (this->Cur_Type == JNode::JType::ARR){
		JsonCallObjArr* arr = arr_del();
		//return &arr_del();
		return arr;
	}
	else if (this->Cur_Type == JNode::JType::OBJ){
		JsonCallObjArr* obj = obj_del();
		//return &obj_del();
		return obj;
	}
	return nullptr;
}

void JNode::all_del() {
	if (this->Cur_Type == JNode::JType::ARR) {
		delType();
		setType(JType::ARR);
	}
	else if (this->Cur_Type == JNode::JType::OBJ) {
		delType();
		setType(JType::OBJ);
	}
}


//<JObj class>--------------------------------------------------------------------------------------


//<JArr class>--------------------------------------------------------------------------------------


//<JsonCtrl class>----------------------------------------------------------------------------------


//<JsonCallObjArr class>-------------------------------------------------------------------------------
//��ȯ������
// = JNode["Key"]
// = JNode[1]
// = Cur_Obj->Value->P_Type(???)
JsonCallObjArr::operator int(){ 
	if (!getOper_Ctrl(JNode::JType::NUMBER)){	//�����ϴ°��
		return -1;
	}
	int* num = nullptr;

	if (Cur_Obj != nullptr){
		num = static_cast<int*>(Cur_Obj->Value->P_Type);
	}

	if (Cur_Arr != nullptr){
		num = static_cast<int*>(Cur_Arr->Value->P_Type);
	}	

	return *num;
}
JsonCallObjArr::operator int*(){
	if (!getOper_Ctrl(JNode::JType::NUMBER)){	//�����ϴ°��
		return nullptr;
	}

	int* num = nullptr;

	if (Cur_Obj != nullptr){
		num = static_cast<int*>(Cur_Obj->Value->P_Type);
	}

	if (Cur_Arr != nullptr){
		num = static_cast<int*>(Cur_Arr->Value->P_Type);
	}

	return num;
}
JsonCallObjArr::operator double(){
	if (!getOper_Ctrl(JNode::JType::DOUBLE)){	//�����ϴ°��
		return -1.0;
	}

	double* dnum = nullptr;

	if (Cur_Obj != nullptr){
		dnum = static_cast<double*>(Cur_Obj->Value->P_Type);
	}

	if (Cur_Arr != nullptr){
		dnum = static_cast<double*>(Cur_Arr->Value->P_Type);
	}

	return *dnum;
}
JsonCallObjArr::operator double*(){
	if (!getOper_Ctrl(JNode::JType::DOUBLE)){	//�����ϴ°��
		return nullptr;
	}

	double* dnum = nullptr;

	if (Cur_Obj != nullptr){
		dnum = static_cast<double*>(Cur_Obj->Value->P_Type);
	}

	if (Cur_Arr != nullptr){
		dnum = static_cast<double*>(Cur_Arr->Value->P_Type);
	}

	return dnum;
}
JsonCallObjArr::operator bool(){
	if (!getOper_Ctrl(JNode::JType::BOOL)){	//�����ϴ°��
		return false;
	}

	bool* bl = nullptr;

	if (Cur_Obj != nullptr){
		bl = static_cast<bool*>(Cur_Obj->Value->P_Type);
	}

	if (Cur_Arr != nullptr){
		bl = static_cast<bool*>(Cur_Arr->Value->P_Type);
	}

	return *bl;
}
JsonCallObjArr::operator bool*(){
	if (!getOper_Ctrl(JNode::JType::BOOL)){	//�����ϴ°��
		return nullptr;
	}

	bool* bl = nullptr;

	if (Cur_Obj != nullptr){
		bl = static_cast<bool*>(Cur_Obj->Value->P_Type);
	}

	if (Cur_Arr != nullptr){
		bl = static_cast<bool*>(Cur_Arr->Value->P_Type);
	}

	return bl;
}
JsonCallObjArr::operator char(){
	if (!getOper_Ctrl(JNode::JType::STRING)){	//�����ϴ°��
		return '\0';
	}

	DynamicStr* str = nullptr;

	if (Cur_Obj != nullptr){
		str = static_cast<DynamicStr*>(Cur_Obj->Value->P_Type);
	}

	if (Cur_Arr != nullptr){
		str = static_cast<DynamicStr*>(Cur_Arr->Value->P_Type);
	}

	char* c = str->Get_Str();
	return c[0];
}
JsonCallObjArr::operator char*(){
	if (!getOper_Ctrl(JNode::JType::STRING)){	//�����ϴ°��
		return nullptr;
	}

	DynamicStr* str = nullptr;

	if (Cur_Obj != nullptr){
		str = static_cast<DynamicStr*>(Cur_Obj->Value->P_Type);
	}

	if (Cur_Arr != nullptr){
		str = static_cast<DynamicStr*>(Cur_Arr->Value->P_Type);
	}

	return str->Get_Str();
}
JsonCallObjArr::operator JNode*(){
	//*JNode = Cur_Obj->Value;  Value�� ��ȯ�ؾ���
	if (Cur_Obj == nullptr && Cur_Arr == nullptr){
		return nullptr;
	}

	if (Cur_Node == nullptr){
		return nullptr;
	}
	
	JNode* lNode = new JNode();
	

	//���簡�ƴ� �̵��� ���־���� ���� lNode <- rNode(JNode[..])
	//lNode = rNode[4] �� ��
	//lNode = rNode->P_Type->4��° Value(Jnode)�� �����ϴ°���
	//��, ���簡 �ƴ� �����뵵�̱⿡ lNode�� delete�ϸ� �ȵ�
	
	if (Cur_Obj != nullptr){
		delete lNode;
		// lNode = Cur_Obj -> Value ����
		/*lNode->Cur_Type = Cur_Obj->Value->Cur_Type;
		lNode->P_Type = Cur_Obj->Value->P_Type;
		lNode->ArrCnt = Cur_Obj->Value->ArrCnt;
		lNode->ObjCnt = Cur_Obj->Value->ObjCnt;*/
		lNode = Cur_Obj->Value;
	} 
	if (Cur_Arr != nullptr){
		delete lNode;
		// lNode = Cur_Arr -> Value ����
		/*lNode->Cur_Type = Cur_Arr->Value->Cur_Type;
		lNode->P_Type = Cur_Arr->Value->P_Type;
		lNode->ArrCnt = Cur_Arr->Value->ArrCnt;
		lNode->ObjCnt = Cur_Arr->Value->ObjCnt;*/
		lNode = Cur_Arr->Value;
	}

	/*lNode->prev_Node = Cur_Node;
	lNode->prev_obj = Cur_Obj;
	lNode->prev_arr = Cur_Arr;*/
	return lNode;
}


//���Կ�����
// JNode["Key"] = 
// JNode[1] = 
// Cur_Obj->Value->P_Type(???) = 
void JsonCallObjArr::operator=(int _num){
	//���� ó�� �� �����뵵
	setOper_Ctrl(JNode::JType::NUMBER, &_num);
}
void JsonCallObjArr::operator=(int* _num){
	setOper_Ctrl(JNode::JType::NUMBER, _num);
}
void JsonCallObjArr::operator=(double _dnum){
	setOper_Ctrl(JNode::JType::DOUBLE, &_dnum);
}
void JsonCallObjArr::operator=(double* _dnum){
	setOper_Ctrl(JNode::JType::DOUBLE, _dnum);
}
void JsonCallObjArr::operator=(bool _bl){
	setOper_Ctrl(JNode::JType::BOOL, &_bl);
}
void JsonCallObjArr::operator=(bool* _bl){
	setOper_Ctrl(JNode::JType::BOOL, _bl);
}
void JsonCallObjArr::operator=(char _c){
	setOper_Ctrl(JNode::JType::STRING, &_c);
}
void JsonCallObjArr::operator=(char* _str){
	setOper_Ctrl(JNode::JType::STRING, _str, true);
}
void JsonCallObjArr::operator=(const char* _str) {
	setOper_Ctrl(JNode::JType::STRING, (void*)_str, true);
}
void JsonCallObjArr::operator=(JNode* jnode){
	//Cur_Arr->Value = JNode;  Value�� �����ϴ°ǵ�
	//Value�� ������ �ϴ°Ŷ�� �����ϸ� �ɱ�?

	if (Cur_Obj == nullptr && Cur_Arr == nullptr){
		return;
	}

	//2������ ������

	if (Cur_Obj != nullptr){
		if (jnode->isTypeNull()){
			//jnode->P_Type == nullptr�� ���
			Cur_Obj->Value->delType();
			Cur_Obj->Value->setType(JNode::JType::NULLTYPE);
		}
		else{
			Cur_Obj->Value->delType();
			Cur_Obj->Value->Cur_Type = jnode->Cur_Type;
			Cur_Obj->Value->P_Type = jnode->P_Type;

			//���� �Ҹ��� �����ϱ� ���� jnode�� P_Type�� ��������
			jnode->P_Type = nullptr;
			jnode->delType();
			jnode->setType(JNode::JType::NULLTYPE);
		}
	}

	if (Cur_Arr != nullptr){
		if (jnode->isTypeNull()){
			//jnode->P_Type == nullptr�� ���
			Cur_Arr->Value->delType();
			Cur_Arr->Value->setType(JNode::JType::NULLTYPE);
		}
		else{
			Cur_Arr->Value->delType();
			Cur_Arr->Value->Cur_Type = jnode->Cur_Type;
			Cur_Arr->Value->P_Type = jnode->P_Type;

			//���� �Ҹ��� �����ϱ� ���� jnode�� P_Type�� ��������
			jnode->P_Type = nullptr;
			jnode->delType();
			jnode->setType(JNode::JType::NULLTYPE);
		}
	}
}

void JsonCallObjArr::operator=(JNode::JType curType) {
	if (!Cur_Obj->Value->isTypeMatch(curType)) {
		//Ÿ���� �ȸ����� ������ϱ� �����ּ�
		Cur_Obj->Value->delType();
		Cur_Obj->Value->Cur_Type = curType;
		Cur_Obj->Value->setType(curType);
	}
}




//������ �κ�
JsonCallObjArr::JsonCallObjArr(JNode* node, JNode::JType curType, bool trg_del){
	if (trg_del){
		//del
		//1. Obj���� Arr���� �Ǵ�
		if (curType == JNode::JType::ARR){
			arr_del(node);
		}
		else if (curType == JNode::JType::OBJ){
			obj_del(node);
		}
	}
	else{
		//push
		//1. Obj���� Arr���� �Ǵ�
		if (curType == JNode::JType::ARR){
			arr_push(node);
		}
		else if (curType == JNode::JType::OBJ){
			obj_push(node);
		}
	}
}


