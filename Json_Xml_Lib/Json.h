#pragma once

#include <stdio.h>
#include <iostream>
#include "Str.h"

#define DEL "del"
#define del "del"		//�̰Ŵ� ����� ���� ����� ���߿� �浹�� ���氡�ɼ��� ������

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
			NULLTYPE,	//��
		};

		//���� ���ҽ� Ptype�� ����������
		void delType();

		JNode() : Cur_Type(JType::NULLTYPE){
			setType(Cur_Type);
		}
		JNode(JType Set_Node_Type) : Cur_Type(Set_Node_Type){
			setType(Cur_Type);
		}
		//�Ҹ���
		~JNode(){
			delType();
		}

		//���� ������
		JNode(const JNode& other) : Cur_Type(other.Cur_Type), P_Type(other.P_Type){

		}
		// �̵� ������
		JNode(const JNode&& other) : Cur_Type(other.Cur_Type), P_Type(other.P_Type) {

		}
		
		JsonCallObjArr arr_push();	//���� ���� ����
		JsonCallObjArr obj_push();	//���� ���� ����

		JsonCallObjArr arr_del(int index);			//���� ���� ����
		JsonCallObjArr obj_del(const char* key);	//���� ���� ����

		void operator=(JType);

		bool isTypeNull();	//true�� P_Type == nullptr
		bool isTypeMatch(JType); //true�� P_Type == Type ��ġ�Ȼ���
		bool isOverWrite();	//����� Ȥ�� �����ϱ�

		void setType(JType);
		void* getPType();
		JType getType();

		//���ڿ� �Ľ� �κ�
		void isObjArrCk(DynamicStr* str);

		//��ȯ
		operator int();
		operator int*();
		operator double();
		operator double*();
		operator bool();
		operator bool*();
		operator char();
		operator char*();
	private:
		operator JObj();			//�ȸ��� ���� �Ҹ��Ҷ� ��ġ����(�������� �������� �����ؾ���)
		operator JArr();			//�ȸ��� ���� �Ҹ��Ҷ� ��ġ����(�������� �������� �����ؾ���)
		operator JArr*();			//�ȸ��� ���� �Ҹ��Ҷ� ��ġ����(�������� �������� �����ؾ���)
		operator JObj*();			//�ȸ��� ���� �Ҹ��Ҷ� ��ġ����(�������� �������� �����ؾ���)
		operator JNode();			//JNode = JNode �̷���� lValue�� ���Ǳ⿡ ��ȯ�� ȣ���� �ȵ�
		operator JNode*();			//��� ������ ���� ��ȯ�� ������ ��������
	public:

		//����
		void operator=(int);
		void operator=(int*);
		void operator=(double);
		void operator=(double*);
		void operator=(bool);
		void operator=(bool*);
		void operator=(char);
		void operator=(const char*);
	private:
		void operator=(JObj);		//�ȸ��� ���� �Ҹ��Ҷ� ��ġ����(�������� �������� �����ؾ���)
		void operator=(JArr);		//�ȸ��� ���� �Ҹ��Ҷ� ��ġ����(�������� �������� �����ؾ���)
		void operator=(JNode);		//rValue�� ������ rValue.P_Type = nullptr�� ������־ ��������ڷ� ������ ��ü�� �Ǿ �ᱹ ���߼Ҹ��
		void operator=(JObj*);		
		void operator=(JArr*);		
	public:
		//�ش� ���Ե��� rValue�� ������ nullptr�� ���ѵȴٰ� ���� ��, lValue = rValue���� lValue�� ������ �̵��μ�
		void operator=(JNode*);

		//��ü �迭 ������ �����ε�
		JsonCallObjArr operator[](const char* key);
		JsonCallObjArr operator[](int index);

		JType Cur_Type;
		void* P_Type;
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

		//�ڽ��� Obj���� next�����ؼ� key�� ��ġ�Ǵ� Obj ��ȯ
		JObj* searchKey(const char* key){
			//���� ��ġ�� �������� ã�°���
			JObj* cur_obj = this;
			
			do{
				if (cur_obj->Key.StrCat(key)) return cur_obj;
				cur_obj = cur_obj->next;
			} while (cur_obj != nullptr);

			return nullptr;
		}

		//�ڽ��� Obj���� Tail��ġ ��ȯ
		JObj* getTailObj(){
			JObj* cur_obj = this;

			if (cur_obj == nullptr) return nullptr;

			for (; cur_obj->next != nullptr;){
				cur_obj = cur_obj->next;
			}

			return cur_obj;
		}
		
		//Ű�� ����
		void setKey(const char* key){
			if (Value->Cur_Type != JNode::JType::NULLTYPE) 
				return;//���࿡ �̷����� ����Ű���� ����� �׷��� ����
			Key.Set_Str(key);
		}

		void setValue(JNode::JType setNodeType){
			//����°���
			Value->delType();
			Value->setType(Value->Cur_Type);
		}

	//private:
		DynamicStr Key;		//Ű��
		JNode* const Value;		//��ģ���� ���ȭ ���Ѿ� �ϳ�
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

		//Arr���� Root��� ���� next�����ؼ� index�� ��ȯ
		JArr* RootSearchIndex(int index){
			if (index <= -1) return nullptr;	//����ó�� -1

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

		//�ڽ��� arr���� tail��ġ ��ȯ
		JArr* getTailArr(){
			JArr* cur_arr = this;

			if (cur_arr == nullptr) return nullptr;

			for (; cur_arr->next != nullptr;){
				cur_arr = cur_arr->next;
			}

			return cur_arr;
		}

		//�ڽ��� arr���� tail��ġ ��ȯ + idx���� ��ȯ���� �� ���� �����ͷ�
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

		void setValue(JNode::JType setNodeType){
			//�����
			Value->delType();
			Value->setType(Value->Cur_Type);
		}


	//private:
		JNode* const Value;
		JArr* next;
		friend JsonCallObjArr;
	};

	class JsonCtrl {

	};

	class JsonCallObjArr {
	public:
		JsonCallObjArr() : Root_Node(nullptr), Root_Obj(nullptr), Root_Arr(nullptr){}
		JsonCallObjArr(JNode* node, const char* key) : Root_Arr(nullptr){
			Root_Node = node;
			Root_Obj = static_cast<JObj*>(Root_Node->P_Type);
			JObj* search_key_obj = Root_Obj->searchKey(key);
			JObj* tail_obj = Root_Obj->getTailObj();

			//1. Root_Node�� ���°� "{}" �̷� �����϶� �ƹ� ��ü�� ������
			if (Root_Node->ObjCnt == -1){
				Root_Obj->setKey(key);			//Ű�� ����
				Root_Obj->setValue(JNode::JType::NULLTYPE);	//�ϴ� �ʱ�ȭ�ϱ� NullType�־��ֱ�
				Root_Obj->next = nullptr;
				Root_Node->ObjCnt++;

				//������ �����ε����� ����� ���ҽ� �ʱ�ȭ ���ֱ�
				Cur_Obj = Root_Obj; 
			}

			//2. Root_Node�� ���°� "{...}"�϶� ��ü�� �����Ҷ� �ش�Ű�� ��ü�� ã��
			
			else if (search_key_obj != nullptr){	//�̹� �ش� Ű�� ���� ��ü�� ������
				//������ �����ε����� ó���ϵ��� �ش� Ű�� ���� ��ü�� �Ѱ��ֱ�
				Cur_Obj = search_key_obj;
			}
			else{//�ش� Ű�� ���� ��ü�� �������� ����
				//���Ӱ� Ű�� ����������
				JObj* new_obj = new JObj(key);
				new_obj->setValue(JNode::JType::NULLTYPE);
				new_obj->next = nullptr;
				Root_Node->ObjCnt++;

				tail_obj->next = new_obj;

				//������ �����ε����� ó���ϵ��� �ش� Ű�� ���� ��ü�� �Ѱ��ֱ�
				Cur_Obj = new_obj;
			}


			//������ �����ε����� ����� ���ҽ� �ʱ�ȭ ���ֱ�
			Cur_Node = Root_Node;
			Cur_Arr = Root_Arr;			//nullptr
		}
		JsonCallObjArr(JNode* node, int index) : Root_Obj(nullptr){
			Root_Node = node;
			int max_idx = -1;
			Root_Arr = static_cast<JArr*>(Root_Node->P_Type);
			JArr* search_idx_arr = Root_Arr->RootSearchIndex(index);
			JArr* tail_arr = Root_Arr->getTailArr(&max_idx);
			if (index == -1) index = max_idx + 1;		//-1�̸� �׳� �ڿ� �߰�
			//1. Root_Node�� ���°� "[]" �̷� �����϶� �ƹ� �迭�� ���� ������ 
			if (Root_Node->ArrCnt == -1){
				if (index != 0){//����
					Cur_Arr = nullptr;
				}
				else{
					Root_Arr->setValue(JNode::JType::NULLTYPE);
					Root_Arr->next = nullptr;
					Root_Node->ArrCnt++;

					Cur_Arr = Root_Arr;
				}
			}

			//2. Root_Node�� ���°� "[...]"�̷� �����϶� �迭�� ���� �����Ҷ�

			// �ش� idx�� ���� ���� �����Ҷ�
			else if (search_idx_arr != nullptr){
				Cur_Arr = search_idx_arr;
			}
			// �ش� idx�� ���� ���� �������� ������
			
			else{
				if (index > max_idx+1){		//�迭�� ũ�⺸�� Ŭ�� ����
					//�����ڿ����ε����� �����ϵ��� �����
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
			
			//������ �����ε����� ����� ���ҽ� �ʱ�ȭ ���ֱ�
			Cur_Node = Root_Node;
			Cur_Obj = Root_Obj;		//nullptr
		}


		//��ȯ ������ = ObjArr["Key"] ���� ��ȯ
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

		//���� ������ ObjArr["Key"] = ���� ����
		void operator=(int);
		void operator=(int*);
		void operator=(double);
		void operator=(double*);
		void operator=(bool);
		void operator=(bool*);
		void operator=(char);
		void operator=(char*);
		void operator=(JNode*);

		//��ȯ�� ���� (True ����, False ����)
		bool getOper_Ctrl(JNode::JType curType){
			//����ó���뵵
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

			//����
			return true;
		}

		//���Կ� ���� (True ����, False ����)
		void setOper_Ctrl(JNode::JType curType, void* rValue, bool str = false){
			//����ó���뵵
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
					if (str){//���ڿ�
						DynamicStr* lval = static_cast<DynamicStr*>(Cur_Obj->Value->P_Type);
						char* rval = static_cast<char*>(rValue);
						lval->Set_Str(rval);
					}
					else{//����
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
					if (str){//���ڿ�
						DynamicStr* lval = static_cast<DynamicStr*>(Cur_Arr->Value->P_Type);
						char* rval = static_cast<char*>(rValue);
						lval->Set_Str(rval);
					}
					else{//����
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
		JNode* Root_Node;	//node->P_Type == Obj; �ΰ��� obj�� Value node �ƴ�
						//node->P_Type == Arr; �ΰ��� arr�� Value node �ƴ�
		JObj* Root_Obj;		//node->P_Type �� ����Ű�� key�� Obj��
		JArr* Root_Arr;		//node->P_Type �� ����Ű�� index�� Arr��

		//operator���� ���� ������ ������
		JNode* Cur_Node;
		JObj* Cur_Obj;
		JArr* Cur_Arr;
	};
}