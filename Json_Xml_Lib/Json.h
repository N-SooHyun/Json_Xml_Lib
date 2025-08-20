#pragma once

#include <stdio.h>
#include <iostream>
#include "Str.h"


using namespace std;
using namespace Dynamic;

namespace JSON {
	class JObj;
	class JArr;
	class JsonCallObjArr;

	class JNode {
	public:
		enum class JType {
			OBJ,
			ARR,
			NUMBER,
			DOUBLE,
			BOOL,
			STRING,
			NULLTYPE,	//널
		};

		//내부 리소스 Ptype을 삭제시켜줌
		void delType();

		JNode() : Cur_Type(JType::NULLTYPE){
			setType(Cur_Type);
		}
		JNode(JType Set_Node_Type) : Cur_Type(Set_Node_Type){
			setType(Cur_Type);
		}
		//소멸자
		~JNode(){
			delType();
		}

		//복사 생성자
		JNode(const JNode& other) : Cur_Type(other.Cur_Type), P_Type(other.P_Type){

		}
		// 이동 생성자
		JNode(const JNode&& other) : Cur_Type(other.Cur_Type), P_Type(other.P_Type) {

		}
		
		JsonCallObjArr push();
	private:
		JsonCallObjArr obj_push(const char* key);	//추후 생성 예정 안쓰는게 좋을거 같기도 하고
	public:

		JsonCallObjArr arr_del(int index);			//선택해서 삭제
		JsonCallObjArr* arr_del();					//끝에만 삭제
		JsonCallObjArr obj_del(const char* key);	//선택해서 삭제
		JsonCallObjArr* obj_del();					//끝에만 삭제

		//push del 통합 메소드 호출용 메소드
		JsonCallObjArr* del();
		void all_del();		//모든 객체 삭제

		void operator=(JType);

		bool isTypeNull();	//true면 P_Type == nullptr
		bool isTypeMatch(JType); //true면 P_Type == Type 매치된상태
		bool isOverWrite();	//덮어쓰기 혹은 생성하기

		void setType(JType);
		void* getPType();
		JType getType();

		//문자열 파싱 부분
		void isObjArrCk(DynamicStr* str);

		//반환
		operator int();
		operator int*();
		operator double();
		operator double*();
		operator bool();
		operator bool*();
		operator char();
		operator char*();
	private:
		operator JObj();			//안만들 예정 소멸할때 골치아픔(지역변수 동적변수 구분해야함)
		operator JArr();			//안만들 예정 소멸할때 골치아픔(지역변수 동적변수 구분해야함)
		operator JArr*();			//안만들 예정 소멸할때 골치아픔(지역변수 동적변수 구분해야함)
		operator JObj*();			//안만들 예정 소멸할때 골치아픔(지역변수 동적변수 구분해야함)
		operator JNode();			//JNode = JNode 이런경우 lValue만 사용되기에 반환은 호출이 안됨
		operator JNode*();			//고로 있으나 마나 반환은 쓰이지 않을예정
	public:

		//대입
		void operator=(int);
		void operator=(int*);
		void operator=(double);
		void operator=(double*);
		void operator=(bool);
		void operator=(bool*);
		void operator=(char);
		void operator=(const char*);
		void operator=(char*);//변수로 들어오는 경우를 위함
	private:
		void operator=(JObj);		//안만들 예정 소멸할때 골치아픔(지역변수 동적변수 구분해야함)
		void operator=(JArr);		//안만들 예정 소멸할때 골치아픔(지역변수 동적변수 구분해야함)
		void operator=(JNode);		//rValue를 복사후 rValue.P_Type = nullptr로 만들어주어도 복사생성자로 생성된 객체가 되어서 결국 이중소멸됨
		void operator=(JObj*);		
		void operator=(JArr*);		
	public:
		//해당 대입들은 rValue가 무조건 nullptr로 변한된다고 가정 즉, lValue = rValue에서 lValue로 완전한 이동인셈
		void operator=(JNode*);

		//객체 배열 연산자 오버로딩
		JsonCallObjArr operator[](const char* key);
		JsonCallObjArr operator[](int index);

		JType Cur_Type;
		void* P_Type;
		//JNode* prev_Node;
		//JObj* prev_obj;
		//JArr* prev_arr;
		int ObjCnt;
		int ArrCnt;
	private:
		friend JsonCallObjArr;
		friend JObj;
		friend JArr;
	};

	class JObj{
	public:
		JObj() :Key(128), Value(new JNode()), next(nullptr){}
		JObj(const char* key) : Key(128), Value(new JNode()), next(nullptr){
			Key.Set_Str(key);
		}
		~JObj() {
			if (Value != nullptr){
				delete Value;
				//Value = nullptr;
			}
			if (next != nullptr){
				delete next;
				next = nullptr;
			}
		}

		//자신의 Obj기준 next참조해서 key와 매치되는 Obj 반환
		JObj* searchKey(const char* key){
			//현재 위치를 기준으로 찾는거임
			JObj* cur_obj = this;
			
			do{
				if (cur_obj->Key.StrCat(key)) return cur_obj;
				cur_obj = cur_obj->next;
			} while (cur_obj != nullptr);

			return nullptr;
		}

		//자신의 Obj기준 Tail위치 반환
		JObj* getTailObj(){
			JObj* cur_obj = this;

			if (cur_obj == nullptr) return nullptr;

			for (; cur_obj->next != nullptr;){
				cur_obj = cur_obj->next;
			}

			return cur_obj;
		}
		
		JObj* getPrevObj(JObj* cur_obj, JNode* root_node){
			JObj* root_obj = static_cast<JObj*>(root_node->P_Type);
			
			if (cur_obj == nullptr) return nullptr;
			
			if (root_obj->next == nullptr)
				return nullptr;

			if (root_obj == cur_obj) return nullptr;

			for (;;){
				if (root_obj->next == cur_obj) break;
				root_obj = root_obj->next;
			}

			return root_obj;	//cur_obj == root_obj->next
		}

		//키값 생성
		void setKey(const char* key){
			if (Value->Cur_Type != JNode::JType::NULLTYPE) 
				return;//만약에 이런경우면 기존키값이 변경됨 그래서 실패
			Key.Set_Str(key);
		}

		void setValue(JNode::JType setNodeType){
			//덮어쓰는거임
			Value->delType();
			Value->setType(Value->Cur_Type);
		}

	//private:
		DynamicStr Key;		//키값
		JNode* const Value;		//이친구는 상수화 시켜야 하나
		JObj* next;
		friend JsonCallObjArr;
	};

	class JArr{
	public:
		JArr() : Value(new JNode()), next(nullptr){}
		
		~JArr(){
			if (Value != nullptr){
				delete Value;
				//Value = nullptr;
			}
			if (next != nullptr){
				delete next;
				next = nullptr;
			}
		}

		//Arr기준 Root라고 가정 next참조해서 index를 반환
		JArr* RootSearchIndex(int index){
			if (index <= -1) return nullptr;	//예외처리 -1

			JArr* cur_arr = this;
			
			int idx = 0;
			
			while (cur_arr != nullptr){
				if (idx == index){
					return cur_arr;
				}

				cur_arr = cur_arr->next;
				idx++;
			}			

			return nullptr;
		}

		//자신의 arr기준 tail위치 반환
		JArr* getTailArr(){
			JArr* cur_arr = this;

			if (cur_arr == nullptr) return nullptr;

			for (; cur_arr->next != nullptr;){
				cur_arr = cur_arr->next;
			}

			return cur_arr;
		}

		//자신의 arr기준 tail위치 반환 + idx값도 반환해줄 수 있음 포인터로
		JArr* getTailArr(int *idx){
			JArr* cur_arr = this;
			JArr* prev_arr = nullptr;

			*idx = -1;

			if (cur_arr == nullptr) return nullptr;

			for (; cur_arr != nullptr;){
				prev_arr = cur_arr;
				cur_arr = cur_arr->next;
				*idx += 1;
			}

			return prev_arr;
		}

		JArr* getPrevArr(JArr* cur_arr, JNode* root_node){
			JArr* root_arr = static_cast<JArr*>(root_node->P_Type);

			if (cur_arr == nullptr) return nullptr;

			if (root_arr->next == nullptr)
				return nullptr;

			if (root_arr == cur_arr) return nullptr;

			for (;;){
				if (root_arr->next == cur_arr) break;
				root_arr = root_arr->next;
			}

			return root_arr;
		}

		void setValue(JNode::JType setNodeType){
			//덮어쓰기
			Value->delType();
			Value->setType(Value->Cur_Type);
		}


	//private:
		JNode* const Value;
		JArr* next;
		friend JsonCallObjArr;
	};

	class JsonCallObjArr {
	public:
		JsonCallObjArr() : Root_Node(nullptr), Root_Obj(nullptr), Root_Arr(nullptr){}
		JsonCallObjArr(JNode* node, const char* key, bool trg_del = false) : Root_Arr(nullptr){
			Root_Node = node;
			Root_Obj = static_cast<JObj*>(Root_Node->P_Type);
			JObj* search_key_obj = Root_Obj->searchKey(key);
			JObj* tail_obj = Root_Obj->getTailObj();

			//1. Root_Node의 상태가 "{}" 이런 상태일때 아무 객체도 없을때
			if (Root_Node->ObjCnt == -1){
				if (trg_del == true){
					//삭제 할 객체가 존재하지 않을때
					Cur_Obj = nullptr;
					Cur_Arr = nullptr;
					Cur_Node = nullptr;
					return;
				}
				Root_Obj->setKey(key);			//키값 설정
				Root_Obj->setValue(JNode::JType::NULLTYPE);	//일단 초기화니까 NullType넣어주기
				Root_Obj->next = nullptr;
				Root_Node->ObjCnt++;

				//연산자 오버로딩에서 사용할 리소스 초기화 해주기
				Cur_Obj = Root_Obj;
			}

			//2. Root_Node의 상태가 "{...}"일때 객체가 존재할때 해당키인 객체를 찾기
			
			else if (search_key_obj != nullptr){	//이미 해당 키를 가진 객체가 존재함
				if (trg_del == true){
					//삭제할 객체가 존재할때
					JObj* prev_obj = search_key_obj->getPrevObj(search_key_obj, Root_Node);
					//1. 1개 혹은 여러개 있으나 0번 객체일때
					if (prev_obj == nullptr){
						//1. 1개만 있을때
						if (search_key_obj->next == nullptr){
							Root_Node->delType();
							Root_Node->setType(JNode::JType::OBJ);
						}
						//2. 여러개 있으나 0번 객체를 지우려고 할때
						else{
							JObj* next_root_obj = search_key_obj->next;
							search_key_obj->next = nullptr;
							Root_Node->delType();
							Root_Node->Cur_Type = JNode::JType::OBJ;
							Root_Node->P_Type = next_root_obj;
							Root_Node->ObjCnt--;
						}
					}
					//2. 여러개 있을때
					else{
						prev_obj->next = search_key_obj->next;
						search_key_obj->next = nullptr;
						delete search_key_obj;
						Root_Node->ObjCnt--;
					}

					return;
				}
				//연산자 오버로딩에서 처리하도록 해당 키를 가진 객체를 넘겨주기
				Cur_Obj = search_key_obj;
			}
			else{//해당 키를 가진 객체가 존재하지 않음
				if (trg_del == true){
					//삭제할 객체가 존재하지 않을때
					Cur_Obj = nullptr;
					Cur_Arr = nullptr;
					Cur_Node = nullptr;
					return;
				}

				//새롭게 키를 만들어줘야함
				JObj* new_obj = new JObj(key);
				new_obj->setValue(JNode::JType::NULLTYPE);
				new_obj->next = nullptr;
				Root_Node->ObjCnt++;

				tail_obj->next = new_obj;

				//연산자 오버로딩에서 처리하도록 해당 키를 가진 객체를 넘겨주기
				Cur_Obj = new_obj;
			}


			//연산자 오버로딩에서 사용할 리소스 초기화 해주기
			Cur_Node = Root_Node;
			Cur_Arr = Root_Arr;			//nullptr
		}
		JsonCallObjArr(JNode* node, int index, bool trg_del = false) : Root_Obj(nullptr){
			Root_Node = node;
			int max_idx = -1;
			Root_Arr = static_cast<JArr*>(Root_Node->P_Type);
			JArr* search_idx_arr = Root_Arr->RootSearchIndex(index);
			JArr* tail_arr = Root_Arr->getTailArr(&max_idx);

			if (index == -1) index = max_idx + 1;		//-1이면 그냥 뒤에 추가

			//1. Root_Node의 상태가 "[]" 이런 상태일때 아무 배열에 값도 없을때 
			if (Root_Node->ArrCnt == -1){
				if (trg_del == true){
					//삭제할 배열이 존재하지 않을때
					Cur_Obj = nullptr;
					Cur_Arr = nullptr;
					Cur_Node = nullptr;
					return;
				}

				if (index != 0){//실패
					Cur_Arr = nullptr;
				}
				else{
					Root_Arr->setValue(JNode::JType::NULLTYPE);
					Root_Arr->next = nullptr;
					Root_Node->ArrCnt++;

					Cur_Arr = Root_Arr;
				}
			}

			//2. Root_Node의 상태가 "[...]"이런 상태일때 배열의 값이 존재할때

			// 해당 idx를 가진 값이 존재할때
			else if (search_idx_arr != nullptr){
				if (trg_del == true){
					//삭제할 인덱스의 요소가 존재할때
					JArr* prev_arr = search_idx_arr->getPrevArr(search_idx_arr, Root_Node);
					//1. 1개 혹은 여러개 있으나 0번 객체일때
					if (prev_arr == nullptr){
						//1. 1개만 있을때
						if (search_idx_arr->next == nullptr){
							Root_Node->delType();
							Root_Node->setType(JNode::JType::ARR);
						}

						//2. 여러개 있으나 0번 객체를 지우려고 할때
						else{
							JArr* next_root_arr = search_idx_arr->next;
							search_idx_arr->next = nullptr;
							Root_Node->delType();
							Root_Node->Cur_Type = JNode::JType::ARR;
							Root_Node->P_Type = next_root_arr;
							Root_Node->ArrCnt--;
						}
					}
					//2. 여러개 있을때
					else{
						prev_arr->next = search_idx_arr->next;
						search_idx_arr->next = nullptr;
						delete search_idx_arr;
						Root_Node->ArrCnt--;
					}
					
					return;
				}
				Cur_Arr = search_idx_arr;
			}
			// 해당 idx를 가진 값이 존재하지 않을때
			
			else{
				if (trg_del == true){
					//삭제할 인덱스의 요소가 존재하지 않을때
					Cur_Obj = nullptr;
					Cur_Arr = nullptr;
					Cur_Node = nullptr;
					return;
				}

				if (index > max_idx+1){		//배열의 크기보다 클때 실패
					//연산자오버로딩에서 실패하도록 만들기
					Cur_Arr = nullptr;
				}
				else{
					JArr* new_arr = new JArr();
					new_arr->setValue(JNode::JType::NULLTYPE);
					new_arr->next = nullptr;
					Root_Node->ArrCnt++;

					tail_arr->next = new_arr;

					Cur_Arr = new_arr;
				}
			}
			
			//연산자 오버로딩에서 사용할 리소스 초기화 해주기
			Cur_Node = Root_Node;
			Cur_Obj = Root_Obj;		//nullptr
		}

		//그냥 맨뒤에 push 혹은 del 하기 위한 생성자
		JsonCallObjArr(JNode* node, JNode::JType curType, bool trg_del = false);

		
		

		//끝에만 push or del 하기
		//obj는 안쓸예정
		void obj_push(JNode* node){
			Root_Arr = nullptr;
			//1. obj만 처리해주기
			Root_Node = node;
			Root_Obj = static_cast<JObj*>(Root_Node->P_Type);
			JObj* tail_obj = Root_Obj->getTailObj();
			//2. 객체에 아무값도 존재하지 않을때 그냥 새롭게 하나 만들기
			if (Root_Node->ObjCnt == -1){
				
			}

			//3. 값이 존재해서 맨뒤까지 도달해야할때
		}

		void arr_push(JNode* node){
			Root_Obj = nullptr;
			//1. arr만 처리해주기
			Root_Node = node;
			int max_idx = -1;
			Root_Arr = static_cast<JArr*>(Root_Node->P_Type);
			JArr* tail_arr = Root_Arr->getTailArr(&max_idx);
			//2. 배열에 아무값도 존재하지 않을때 그냥 새롭게 하나 만들기
			if (Root_Node->ArrCnt == -1){
				Root_Arr->setValue(JNode::JType::NULLTYPE);
				Root_Arr->next = nullptr;
				Root_Node->ArrCnt++;

				Cur_Arr = Root_Arr;
			}

			//3. 값이 존재해서 맨뒤까지 도달해야할때
			else if(Root_Node->ArrCnt >= 0){
				JArr* new_arr = new JArr();
				new_arr->setValue(JNode::JType::NULLTYPE);
				new_arr->next = nullptr;
				Root_Node->ArrCnt++;

				tail_arr->next = new_arr;

				Cur_Arr = new_arr;
			}
			//연산자 오버로딩에서 사용할 리소스 초기화 해주기
			Cur_Node = Root_Node;
			Cur_Obj = Root_Obj;		//nullptr
		}

		void obj_del(JNode* node){
			Root_Arr = nullptr;
			//1. obj만 처리해주기
			Root_Node = node;
			Root_Obj = static_cast<JObj*>(Root_Node->P_Type);
			
			//2. 객체 상태가 "{}"일때
			if (Root_Node->ObjCnt == -1){
				return;
				//삭제못함 그냥 반환
			}

			//3. 객체 상태가 "{..}"일때
			else{
				JObj* tail_obj = Root_Obj->getTailObj();
				JObj* prev_obj = Root_Obj->getPrevObj(tail_obj, Root_Node);

				if (prev_obj == nullptr){
					//1개가 남아있을때
					Root_Node->delType();
					Root_Node->setType(JNode::JType::OBJ);
				}
				else{
					//여러개가 남아있을때
					prev_obj->next = nullptr;
					Root_Node->ObjCnt--;
					delete tail_obj;
				}
			}
		}

		void arr_del(JNode* node){
			Root_Obj = nullptr;
			//1. Arr만 처리해주기
			Root_Node = node;
			Root_Arr = static_cast<JArr*>(Root_Node->P_Type);

			//2. 배열 상태가 "[]"일때
			if (Root_Node->ArrCnt == -1) {
				return;
				//삭제못함 그냥 반환
			}

			//3. 배열 상태가 "[..]"일때
			else{
				JArr* tail_arr = Root_Arr->getTailArr();
				JArr* prev_arr = Root_Arr->getPrevArr(tail_arr, Root_Node);

				if (prev_arr == nullptr){
					//1개남아있을때
					Root_Node->delType();
					Root_Node->setType(JNode::JType::ARR);
				}
				else{
					//여러개 남아있을때
					prev_arr->next = nullptr;
					Root_Node->ArrCnt--;
					delete tail_arr;
				}
				

			}
		}


		//반환 연산자 = ObjArr["Key"] 값을 반환
		operator int();
		operator int*();
		operator double();
		operator double*();
		operator bool();
		operator bool*();
		operator char();
		operator char*();
		operator JNode*();

	private:
		operator JNode();
		operator JObj();
		operator JObj*();
		operator JArr();
		void operator=(JNode);
		void operator=(JObj);
		void operator=(JObj*);
		void operator=(JArr);
		void operator=(JArr*);
	public:

		//대입 연산자 ObjArr["Key"] = 값을 대입
		void operator=(int);
		void operator=(int*);
		void operator=(double);
		void operator=(double*);
		void operator=(bool);
		void operator=(bool*);
		void operator=(char);
		void operator= (const char*);
		void operator=(char*);
		void operator=(JNode*);
		void operator=(JNode::JType curType);

		//반환용 제어 (True 성공, False 실패)
		bool getOper_Ctrl(JNode::JType curType){
			//예외처리용도
			if (Cur_Obj == nullptr && Cur_Arr == nullptr){
				return false;
			}

			if (Cur_Obj != nullptr){
				switch (curType){
				case JNode::JType::NUMBER:
					if (Cur_Obj->Value->isTypeNull() && !Cur_Obj->Value->isTypeMatch(JNode::JType::NUMBER))
						return false;
					break;
				case JNode::JType::DOUBLE:
					if (Cur_Obj->Value->isTypeNull() && !Cur_Obj->Value->isTypeMatch(JNode::JType::DOUBLE))
						return false;
					break;
				case JNode::JType::BOOL:
					if (Cur_Obj->Value->isTypeNull() && !Cur_Obj->Value->isTypeMatch(JNode::JType::BOOL))
						return false;
					break;
				case JNode::JType::STRING:
					if (Cur_Obj->Value->isTypeNull() && !Cur_Obj->Value->isTypeMatch(JNode::JType::STRING))
						return false;
					break;
				case JNode::JType::OBJ:
					if (Cur_Obj->Value->isTypeNull() && !Cur_Obj->Value->isTypeMatch(JNode::JType::OBJ))
						return false;
					break;
				case JNode::JType::ARR:
					if (Cur_Obj->Value->isTypeNull() && !Cur_Obj->Value->isTypeMatch(JNode::JType::ARR))
						return false;
					break;
				case JNode::JType::NULLTYPE:
					if (Cur_Obj->Value->isTypeNull() && !Cur_Obj->Value->isTypeMatch(JNode::JType::NULLTYPE))
						return false;
					break;

				}
			}

			if (Cur_Arr != nullptr){
				switch (curType){
				case JNode::JType::NUMBER:
					if (Cur_Arr->Value->isTypeNull() && !Cur_Arr->Value->isTypeMatch(JNode::JType::NUMBER))
						return false;
					break;
				case JNode::JType::DOUBLE:
					if (Cur_Arr->Value->isTypeNull() && !Cur_Arr->Value->isTypeMatch(JNode::JType::DOUBLE))
						return false;
					break;
				case JNode::JType::BOOL:
					if (Cur_Arr->Value->isTypeNull() && !Cur_Arr->Value->isTypeMatch(JNode::JType::BOOL))
						return false;
					break;
				case JNode::JType::STRING:
					if (Cur_Arr->Value->isTypeNull() && !Cur_Arr->Value->isTypeMatch(JNode::JType::STRING))
						return false;
					break;
				case JNode::JType::OBJ:
					if (Cur_Arr->Value->isTypeNull() && !Cur_Arr->Value->isTypeMatch(JNode::JType::OBJ))
						return false;
					break;
				case JNode::JType::ARR:
					if (Cur_Arr->Value->isTypeNull() && !Cur_Arr->Value->isTypeMatch(JNode::JType::ARR))
						return false;
					break;
				case JNode::JType::NULLTYPE:
					if (Cur_Arr->Value->isTypeNull() && !Cur_Arr->Value->isTypeMatch(JNode::JType::NULLTYPE))
						return false;
					break;

				}
			}

			//성공
			return true;
		}

		//대입용 제어 (True 성공, False 실패)
		void setOper_Ctrl(JNode::JType curType, void* rValue, bool str = false){
			//예외처리용도
			if (Cur_Obj == nullptr && Cur_Arr == nullptr){
				return;
			}

			if (Cur_Obj != nullptr){
				if (curType == JNode::JType::NUMBER){
					if (!Cur_Obj->Value->isTypeMatch(JNode::JType::NUMBER)){
						Cur_Obj->Value->delType();
						Cur_Obj->Value->setType(JNode::JType::NUMBER);
					}
					int* lval = static_cast<int*>(Cur_Obj->Value->P_Type);
					int* rval = static_cast<int*>(rValue);

					*lval = *rval;
				}
				else if (curType == JNode::JType::DOUBLE){
					if (!Cur_Obj->Value->isTypeMatch(JNode::JType::DOUBLE)){
						Cur_Obj->Value->delType();
						Cur_Obj->Value->setType(JNode::JType::DOUBLE);
					}
					double* lval = static_cast<double*>(Cur_Obj->Value->P_Type);
					double* rval = static_cast<double*>(rValue);

					*lval = *rval;
				}
				else if (curType == JNode::JType::BOOL){
					if (!Cur_Obj->Value->isTypeMatch(JNode::JType::BOOL)){
						Cur_Obj->Value->delType();
						Cur_Obj->Value->setType(JNode::JType::BOOL);
					}
					bool* lval = static_cast<bool*>(Cur_Obj->Value->P_Type);
					bool* rval = static_cast<bool*>(rValue);

					*lval = *rval;
				}
				else if (curType == JNode::JType::STRING){
					if (!Cur_Obj->Value->isTypeMatch(JNode::JType::STRING)){
						Cur_Obj->Value->delType();
						Cur_Obj->Value->setType(JNode::JType::STRING);
					}
					if (str){//문자열
						DynamicStr* lval = static_cast<DynamicStr*>(Cur_Obj->Value->P_Type);
						char* rval = static_cast<char*>(rValue);
						lval->Set_Str(rval);
						
						//문자열 파싱 해주는거 필요
						Cur_Obj->Value->isObjArrCk(lval);
					}
					else{//문자
						DynamicStr* lval = static_cast<DynamicStr*>(Cur_Obj->Value->P_Type);
						char* rval = static_cast<char*>(rValue);
						lval->Set_Char(&rval[0]);
					}
				}
				else if (curType == JNode::JType::OBJ){

				}
				else if (curType == JNode::JType::ARR){

				}
				else if (curType == JNode::JType::NULLTYPE){

				}
			}

			if (Cur_Arr != nullptr){
				if (curType == JNode::JType::NUMBER){
					if (!Cur_Arr->Value->isTypeMatch(JNode::JType::NUMBER)){
						Cur_Arr->Value->delType();
						Cur_Arr->Value->setType(JNode::JType::NUMBER);
					}
					int* lval = static_cast<int*>(Cur_Arr->Value->P_Type);
					int* rval = static_cast<int*>(rValue);

					*lval = *rval;
				}
				else if (curType == JNode::JType::DOUBLE){
					if (!Cur_Arr->Value->isTypeMatch(JNode::JType::DOUBLE)){
						Cur_Arr->Value->delType();
						Cur_Arr->Value->setType(JNode::JType::DOUBLE);
					}
					double* lval = static_cast<double*>(Cur_Arr->Value->P_Type);
					double* rval = static_cast<double*>(rValue);

					*lval = *rval;
				}
				else if (curType == JNode::JType::BOOL){
					if (!Cur_Arr->Value->isTypeMatch(JNode::JType::BOOL)){
						Cur_Arr->Value->delType();
						Cur_Arr->Value->setType(JNode::JType::BOOL);
					}
					bool* lval = static_cast<bool*>(Cur_Arr->Value->P_Type);
					bool* rval = static_cast<bool*>(rValue);

					*lval = *rval;
				}
				else if (curType == JNode::JType::STRING){
					if (!Cur_Arr->Value->isTypeMatch(JNode::JType::STRING)){
						Cur_Arr->Value->delType();
						Cur_Arr->Value->setType(JNode::JType::STRING);
					}
					if (str){//문자열
						DynamicStr* lval = static_cast<DynamicStr*>(Cur_Arr->Value->P_Type);
						char* rval = static_cast<char*>(rValue);
						lval->Set_Str(rval);

						//문자열 파싱 해주는거 필요
						Cur_Arr->Value->isObjArrCk(lval);
					}
					else{//문자
						DynamicStr* lval = static_cast<DynamicStr*>(Cur_Arr->Value->P_Type);
						char* rval = static_cast<char*>(rValue);
						lval->Set_Char(&rval[0]);
					}
				}
				else if (curType == JNode::JType::OBJ){

				}
				else if (curType == JNode::JType::ARR){

				}
				else if (curType == JNode::JType::NULLTYPE){

				}
			}
			

		}

	private:
		JNode* Root_Node;	//node->P_Type == Obj; 인거임 obj의 Value node 아님
						//node->P_Type == Arr; 인거임 arr의 Value node 아님
		JObj* Root_Obj;		//node->P_Type 이 가리키는 key의 Obj임
		JArr* Root_Arr;		//node->P_Type 이 가리키는 index의 Arr임

		//operator에서 사용될 포인터 변수들
		JNode* Cur_Node;
		JObj* Cur_Obj;
		JArr* Cur_Arr;
	};


	//문자열 파싱 -> JNode로 변환
	class StrParser {
	public:
		//StrParser() : parserToJsonNode(nullptr), parserStr(nullptr){}
		StrParser(JNode* node, Dynamic::DynamicStr* str, bool isObjArr) 
			: parserToJsonNode(node), parserStr(str), isObjArr(isObjArr) {
			ctrl_parser();
		}
		~StrParser() {}

		//parse 메소드
		void ctrl_parser() {
			if( isObjArr) {
				obj_parser();
			} else {
				arr_parser();
			}
		}

		void obj_parser() {
			//모드 4개
			//1. '"' 키의 시작 부분 무조건 ':' 이거전에 '"'가 나와야 함
			//2. ':' 값의 시작 부분
			//3. ',' 다음에 오는 객체의 시작부분 ',' 다음은 무조건 '"'가 나와야함
			//4. '}' 객체의 끝부분 이거는 이미 인지를 하고 있는 상황임

			int glb_csr = 0;		//전체 문자열의 커서 역할
			while (1) {

			}
			

		}

		void arr_parser() {
			//허용 타입 7개
			//1. string 시작값 '"' 끝값 '"'
			//2. number
			//3. double
			//4. bool true false
			//5. null
			//6. {}		시작값 '{' 끝값 '}'
			//7. []		시작값 '[' 끝값 ']'
			//끝값은 무조건 ','혹은 ']'가 다음에 와야함
			

		}

	private:
		JNode* parserToJsonNode;
		Dynamic::DynamicStr* parserStr;
		bool isObjArr;		// true면 obj false면 arr
	};



	//JNode 파싱 -> Json으로 변환
	class JsonMaker {
	public:
		JsonMaker() {}
		~JsonMaker() {}

	private:

	};
	
}