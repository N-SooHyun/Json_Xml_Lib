#include "Main.h"

using namespace std;
using namespace Dynamic;
using namespace JSON;


//<JNode class>--------------------------------------------------------------------------------------
void JNode::delType(){
	//이중소멸을 막기 위한 예외
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
		//P_Type이 존재하기 떄문에 소멸하고 해줘야 하기에 반환
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
			P_Type = new int(); // 기본적으로 int로 초기화
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
			P_Type = nullptr; // null 타입은 포인터를 사용하지 않음
			break;
		}
		default:
		{
			P_Type = nullptr; // 기본적으로 nullptr로 초기화
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


//문자열 파싱 부분
void JNode::isObjArrCk(DynamicStr* str){
	const char* Str = str->Get_Str();
	short first_focus = 0;
	short last_focus = str->str_last_focus;

	if (Str[first_focus] == '\"' && Str[last_focus] == '\"'){
		first_focus++;
		last_focus--;
	}

	if (Str[first_focus] == '{' && Str[last_focus] == '}'){
		//객체임 
		//Parsing 시작 함수 호출 하든가 하셈
	}
	else if (Str[first_focus] == '[' && Str[last_focus] == ']'){
		//배열임
		//Parsing 시작 함수 호출 하든가 하셈
	}	
}


//예외처리목록
bool JNode::isTypeNull(){
	if (P_Type != nullptr) return false;
	return true;
}
bool JNode::isTypeMatch(JType match_type){
	if (Cur_Type == match_type) return true;
	return false;
}

//반환 연산자 = P_Type을 반환
JNode::operator int(){
	if (isTypeNull() && !isTypeMatch(JType::NUMBER)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return -1;
	}
	
	int* num = static_cast<int*>(P_Type);

	return *num;
}
JNode::operator int*(){
	if (isTypeNull() && !isTypeMatch(JType::NUMBER)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return nullptr;
	}

	int* num = static_cast<int*>(P_Type);

	return num;	
}
JNode::operator double(){
	if (isTypeNull() && !isTypeMatch(JType::DOUBLE)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return -1.0;
	}
	double* dnum = static_cast<double*>(P_Type);

	return *dnum;
}
JNode::operator double*(){
	if (isTypeNull() && !isTypeMatch(JType::DOUBLE)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return nullptr;
	}
	double* dnum = static_cast<double*>(P_Type); 
	return dnum;
}
JNode::operator bool(){
	if (isTypeNull() && !isTypeMatch(JType::BOOL)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return false;
	}
	bool* bl = static_cast<bool*>(P_Type);
	return *bl;
}
JNode::operator bool*(){
	if (isTypeNull() && !isTypeMatch(JType::BOOL)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return nullptr;
	}
	bool* pbl = static_cast<bool*>(P_Type);
	return pbl;
}
JNode::operator char(){
	if (isTypeNull() && !isTypeMatch(JType::STRING)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return '\0';
	}
	DynamicStr* str = static_cast<DynamicStr*>(P_Type);
	char* c = str->Get_Str();
	return c[0];
}
JNode::operator char*(){
	if (isTypeNull() && !isTypeMatch(JType::STRING)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return nullptr;
	}
	DynamicStr* str = static_cast<DynamicStr*>(P_Type); 
	return str->Get_Str();
}
//Node를 반화할때 처리


//대입 연산자 P_Type = 대입
void JNode::operator=(int _num){
	if (!isTypeMatch(JType::NUMBER)){
		//타입이 안맞으면 덮어쓸거니까 지워주셈
		delType();
		Cur_Type = JType::NUMBER;
		setType(Cur_Type);
	}

	int* num = static_cast<int*>(P_Type);
	*num = _num; //복사
}
void JNode::operator=(int* _pnum){
	if (!isTypeMatch(JType::NUMBER)){
		//타입이 안맞으면 덮어쓸거니까 지워주셈
		delType();
		Cur_Type = JType::NUMBER;
		setType(Cur_Type);
	}
	int* pnum = static_cast<int*>(P_Type);
	*pnum = *_pnum; //복사 참조X
}
void JNode::operator=(double _dnum){
	if (!isTypeMatch(JType::DOUBLE)){
		//타입이 안맞으면 덮어쓸거니까 지워주셈
		delType();
		Cur_Type = JType::DOUBLE;
		setType(Cur_Type);
	}
	double* dnum = static_cast<double*>(P_Type); 
	*dnum = _dnum;	//복사
}
void JNode::operator=(double* _pdnum){
	if (!isTypeMatch(JType::DOUBLE)){
		//타입이 안맞으면 덮어쓸거니까 지워주셈
		delType();
		Cur_Type = JType::DOUBLE;
		setType(Cur_Type);
	}
	double* dnum = static_cast<double*>(P_Type);
	*dnum = *_pdnum; //복사 참조 X
}
void JNode::operator=(bool _bl){
	if (!isTypeMatch(JType::BOOL)){
		//타입이 안맞으면 덮어쓸거니까 지워주셈
		delType();
		Cur_Type = JType::BOOL;
		setType(Cur_Type);
	}
	bool* bl = static_cast<bool*>(P_Type);
	*bl = _bl;	//복사
}
void JNode::operator=(bool* _pbl){
	if (!isTypeMatch(JType::BOOL)){
		//타입이 안맞으면 덮어쓸거니까 지워주셈
		delType();
		Cur_Type = JType::BOOL;
		setType(Cur_Type);
	}
	bool* bl = static_cast<bool*>(P_Type);
	*bl = *_pbl;	//복사 참조X
}
void JNode::operator=(char _c){
	if (!isTypeMatch(JType::STRING)){
		//타입이 안맞으면 덮어쓸거니까 지워주셈
		delType();
		Cur_Type = JType::STRING;
		setType(Cur_Type);
	}
	DynamicStr* c = static_cast<DynamicStr*>(P_Type);
	char* pc = &_c;
	c->Set_Char(pc);	//복사
}
void JNode::operator=(char* _str){
	if (!isTypeMatch(JType::STRING)){
		//타입이 안맞으면 덮어쓸거니까 지워주셈
		delType();
		Cur_Type = JType::STRING;
		setType(Cur_Type);
	}
	DynamicStr* str = static_cast<DynamicStr*>(P_Type);
	str->Set_Str(_str);	//복사

	//문자열 파싱 부분
	isObjArrCk(str);
}
//Node를 받을때 처리


//객체와 배열에 대한 연산자
//Node["Key"]
JsonCallObjArr JNode::operator[](const char* key){
	//Obj타입이 아닌경우? 1. 덮어쓰기, 2. 실패하기 1번 선택
	if (!isTypeMatch(JType::OBJ)){
		//타입이 안맞는경우 덮어쓸꺼니까 지워주셈
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
	//Arr타입이 아닌경우? 1. 덮어쓰기 2. 실패하기 1번 선택
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

//반환 연산자 = Obj["Key"] 값을 반환
//= Arr[1]
JsonCallObjArr::operator int(){
	if (obj == nullptr) return -1; //실패 하는 경우
	if (!obj->Value->isTypeMatch(JNode::JType::NUMBER)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return -1;
	}

	int* num = static_cast<int*>(obj->Value->P_Type);

	return *num;
}
JsonCallObjArr::operator int*(){
	if (obj == nullptr) return nullptr; //실패 하는 경우
	if (!obj->Value->isTypeMatch(JNode::JType::NUMBER)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return nullptr;
	}

	int* num = static_cast<int*>(obj->Value->P_Type);

	return num;
}
JsonCallObjArr::operator double(){
	if (obj == nullptr) return -1.0; //실패 하는 경우
	if (!obj->Value->isTypeMatch(JNode::JType::DOUBLE)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return -1.0;
	}

	double* num = static_cast<double*>(obj->Value->P_Type);

	return *num;
}
JsonCallObjArr::operator double*(){
	if (obj == nullptr) return nullptr; //실패 하는 경우
	if (!obj->Value->isTypeMatch(JNode::JType::DOUBLE)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return nullptr;
	}

	double* num = static_cast<double*>(obj->Value->P_Type);

	return num;
}
JsonCallObjArr::operator bool(){
	if (obj == nullptr) return false; //실패 하는 경우
	if (!obj->Value->isTypeMatch(JNode::JType::BOOL)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return false;
	}

	bool* num = static_cast<bool*>(obj->Value->P_Type);

	return *num;
}
JsonCallObjArr::operator bool*(){
	if (obj == nullptr) return false; //실패 하는 경우
	if (!obj->Value->isTypeMatch(JNode::JType::BOOL)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return nullptr;
	}

	bool* num = static_cast<bool*>(obj->Value->P_Type);

	return num;
}
JsonCallObjArr::operator char(){
	if (obj == nullptr) return '\0'; //실패 하는 경우
	if (!obj->Value->isTypeMatch(JNode::JType::STRING)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return '\0';
	}

	DynamicStr* str = static_cast<DynamicStr*>(obj->Value->P_Type);
	char* c = str->Get_Str();
	return c[0];
}
JsonCallObjArr::operator char*(){
	if (obj == nullptr) return nullptr; //실패 하는 경우
	if (!obj->Value->isTypeMatch(JNode::JType::STRING)){
		//실패하는 경우 타입이 Null이거나 타입매치가 안맞는경우
		return nullptr;
	}

	DynamicStr* str = static_cast<DynamicStr*>(obj->Value->P_Type);
	return str->Get_Str();
}

//대입 연산자 Obj["Key"] = 값을 대입 있던값이 어도 덮어쓰기
// Arr[1] = 
void JsonCallObjArr::operator=(int _num){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::NUMBER);
	int* num = static_cast<int*>(obj->Value->P_Type);
	*num = _num; //복사
}
void JsonCallObjArr::operator=(int* _pnum){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::NUMBER);
	int* num = static_cast<int*>(obj->Value->P_Type);
	*num = *_pnum; //복사
}
void JsonCallObjArr::operator=(double _dnum){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::DOUBLE);
	double* dnum = static_cast<double*>(obj->Value->P_Type);
	*dnum = _dnum; //복사
}
void JsonCallObjArr::operator=(double* _pdnum){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::DOUBLE);
	double* dnum = static_cast<double*>(obj->Value->P_Type);
	*dnum = *_pdnum; //복사
}
void JsonCallObjArr::operator=(bool _bl){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::BOOL);
	bool* bl = static_cast<bool*>(obj->Value->P_Type);
	*bl = _bl; //복사
}
void JsonCallObjArr::operator=(bool* _pbl){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::BOOL);
	bool* bl = static_cast<bool*>(obj->Value->P_Type);
	*bl = *_pbl; //복사
}
void JsonCallObjArr:: operator=(char _c){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::STRING);
	DynamicStr* c = static_cast<DynamicStr*>(obj->Value->P_Type);
	char* pc = &_c;
	c->Set_Char(pc);	//복사
}
void JsonCallObjArr::operator=(char* _str){
	if (obj == nullptr) return;
	obj->setValue(JNode::JType::STRING);
	DynamicStr* str = static_cast<DynamicStr*>(obj->Value->P_Type);
	str->Set_Str(_str);	//복사

	//문자열 파싱 부분
	obj->Value->isObjArrCk(str);
}
