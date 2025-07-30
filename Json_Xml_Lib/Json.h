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
	public:
		operator JNode();			//JNode = JNode �̷���� lValue�� ���Ǳ⿡ ��ȯ�� ȣ���� �ȵ�
		operator JNode*();			//��� ������ ���� ��ȯ�� ������ ��������

		//����
		void operator=(int);
		void operator=(int*);
		void operator=(double);
		void operator=(double*);
		void operator=(bool);
		void operator=(bool*);
		void operator=(char);
		void operator=(char*);
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
			if (Value != nullptr) return;//����
			Key.Set_Str(key);
		}

		void setKeyValue(const char* key, JNode::JType setNodeType){
			//Ű���� �ش��ϴ� Value�� ����� ������ �߰��� �����ϵ��� �����
			//�ϴ� ��� ����
			Value->delType();
			Value->Cur_Type = setNodeType;
			Value->setType(Value->Cur_Type);
		}

		void setValue(JNode::JType setNodeType){
			//����°���
			Value->delType();
			Value->Cur_Type = setNodeType;
			Value->setType(Value->Cur_Type);
		}

		//������ Value�ǵ帱���� ���� �����ͼ� �ǵ帱��	
		JNode* getCurValue(){		
			return Value;
		}

	//private:
		DynamicStr Key;		//Ű��
		JNode* const Value;		//��ģ���� ���ȭ ���Ѿ� �ϳ�
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
			//Cur_Node->P_Type(JObj)�� ���� Ű���� ã�� �� �߰�
			JObj* head_obj = static_cast<JObj*>(Cur_Node->P_Type);
			JObj* ctrl_obj = head_obj;

			if (Cur_Node->ObjCnt == -1){
				//0�� Obj���� Ű�� �־������
				ctrl_obj->Key.Set_Str(key);
				Cur_Node->ObjCnt++;

				obj = ctrl_obj;
				return;
			}

			//Ű�� ã��
			ctrl_obj = head_obj->searchKey(key);
			if (ctrl_obj == nullptr){
				//Ű�� ���� ��Ȳ Ű�� �߰��������
				//���� �� Objã��
				ctrl_obj = head_obj->getTailObj();
				//���ο� Obj�����
				JObj* new_obj = new JObj(key);
				//�������� key �̾��ֱ�
				ctrl_obj->next = new_obj;
				Cur_Node->ObjCnt++; 

				//������ �����ε����� ����� obj�� obj�ֱ�
				obj = new_obj;
			}
			else{
				//Ű�� �ִ� ��Ȳ(Ű�� ã�������)
				//������ �����ε����� ����� obj�� obj�ֱ�
				obj = ctrl_obj;
			}	

		}
		JsonCallObjArr(JNode* Cur_Node, int index) : node(Cur_Node), obj(nullptr){
			//Cur_Node->P_Type(JArr)�� ���� index ã�� �� �߰�
			
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

	private:
		JNode* node;	//node->P_Type == Obj; �ΰ��� obj�� Value node �ƴ�
						//node->P_Type == Arr; �ΰ��� arr�� Value node �ƴ�
		JObj* obj;		//node->P_Type �� ����Ű�� key�� Obj��
		JArr* arr;		//node->P_Type �� ����Ű�� index�� Arr��
	};
}