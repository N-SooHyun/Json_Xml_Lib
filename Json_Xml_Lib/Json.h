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

	class JObj_JArr_Del{
	public:
		JObj_JArr_Del(){}
		virtual ~JObj_JArr_Del(){}
	};

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
	public:
		operator JNode();			//JNode = JNode 이런경우 lValue만 사용되기에 반환은 호출이 안됨
		operator JNode*();			//고로 있으나 마나 반환은 쓰이지 않을예정

		//대입
		void operator=(int);
		void operator=(int*);
		void operator=(double);
		void operator=(double*);
		void operator=(bool);
		void operator=(bool*);
		void operator=(char);
		void operator=(char*);
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

	private:
		JType Cur_Type;
		void* P_Type;
		int ObjCnt;
		int ArrCnt;
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
		
		//키값 생성
		void setKey(const char* key){
			if (Value != nullptr) return;//실패
			Key.Set_Str(key);
		}

		void setKeyValue(const char* key, JNode::JType setNodeType){
			//키값에 해당하는 Value에 덮어쓰기 없으면 추가도 가능하도록 만들기
			//일단 사용 보류
			Value->delType();
			Value->Cur_Type = setNodeType;
			Value->setType(Value->Cur_Type);
		}

		void setValue(JNode::JType setNodeType){
			//덮어쓰는거임
			Value->delType();
			Value->Cur_Type = setNodeType;
			Value->setType(Value->Cur_Type);
		}

		//무조건 Value건드릴때는 여거 가져와서 건드릴것	
		JNode* getCurValue(){		
			return Value;
		}

	//private:
		DynamicStr Key;		//키값
		JNode* const Value;		//이친구는 상수화 시켜야 하나
		JObj* next;
		friend JsonCallObjArr;
	};

	class JArr{
	public:

	private:
		JNode* Value;
		JArr* next;
	};

	class JsonCtrl {

	};

	class JsonCallObjArr {
	public:
		JsonCallObjArr() : node(nullptr){}
		JsonCallObjArr(JNode* Cur_Node, const char* key) : node(Cur_Node), arr(nullptr){
			//Cur_Node->P_Type(JObj)를 토대로 키값을 찾기 및 추가
			JObj* head_obj = static_cast<JObj*>(Cur_Node->P_Type);
			JObj* ctrl_obj = head_obj;

			if (Cur_Node->ObjCnt == -1){
				//0번 Obj부터 키를 넣어줘야함
				ctrl_obj->Key.Set_Str(key);
				Cur_Node->ObjCnt++;

				obj = ctrl_obj;
				return;
			}

			//키값 찾기
			ctrl_obj = head_obj->searchKey(key);
			if (ctrl_obj == nullptr){
				//키값 없는 상황 키를 추가해줘야함
				//가장 끝 Obj찾기
				ctrl_obj = head_obj->getTailObj();
				//새로운 Obj만들기
				JObj* new_obj = new JObj(key);
				//마지막에 key 이어주기
				ctrl_obj->next = new_obj;
				Cur_Node->ObjCnt++; 

				//연산자 오버로딩에서 사용할 obj에 obj넣기
				obj = new_obj;
			}
			else{
				//키값 있는 상황(키값 찾아줘야함)
				//연산자 오버로딩에서 사용할 obj에 obj넣기
				obj = ctrl_obj;
			}	

		}
		JsonCallObjArr(JNode* Cur_Node, int index) : node(Cur_Node), obj(nullptr){
			//Cur_Node->P_Type(JArr)을 토대로 index 찾기 및 추가
			
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
		void operator=(char*);
		void operator=(JNode*);

	private:
		JNode* node;	//node->P_Type == Obj; 인거임 obj의 Value node 아님
						//node->P_Type == Arr; 인거임 arr의 Value node 아님
		JObj* obj;		//node->P_Type 이 가리키는 key의 Obj임
		JArr* arr;		//node->P_Type 이 가리키는 index의 Arr임
	};
}