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
		
		JsonCallObjArr push();
	private:
		JsonCallObjArr obj_push(const char* key);	//���� ���� ���� �Ⱦ��°� ������ ���⵵ �ϰ�
	public:

		JsonCallObjArr arr_del(int index);			//�����ؼ� ����
		JsonCallObjArr* arr_del();					//������ ����
		JsonCallObjArr obj_del(const char* key);	//�����ؼ� ����
		JsonCallObjArr* obj_del();					//������ ����

		//push del ���� �޼ҵ� ȣ��� �޼ҵ�
		JsonCallObjArr* del();
		void all_del();		//��� ��ü ����

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
		void operator=(char*);//������ ������ ��츦 ����
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
			//�����
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

			//1. Root_Node�� ���°� "{}" �̷� �����϶� �ƹ� ��ü�� ������
			if (Root_Node->ObjCnt == -1){
				if (trg_del == true){
					//���� �� ��ü�� �������� ������
					Cur_Obj = nullptr;
					Cur_Arr = nullptr;
					Cur_Node = nullptr;
					return;
				}
				Root_Obj->setKey(key);			//Ű�� ����
				Root_Obj->setValue(JNode::JType::NULLTYPE);	//�ϴ� �ʱ�ȭ�ϱ� NullType�־��ֱ�
				Root_Obj->next = nullptr;
				Root_Node->ObjCnt++;

				//������ �����ε����� ����� ���ҽ� �ʱ�ȭ ���ֱ�
				Cur_Obj = Root_Obj;
			}

			//2. Root_Node�� ���°� "{...}"�϶� ��ü�� �����Ҷ� �ش�Ű�� ��ü�� ã��
			
			else if (search_key_obj != nullptr){	//�̹� �ش� Ű�� ���� ��ü�� ������
				if (trg_del == true){
					//������ ��ü�� �����Ҷ�
					JObj* prev_obj = search_key_obj->getPrevObj(search_key_obj, Root_Node);
					//1. 1�� Ȥ�� ������ ������ 0�� ��ü�϶�
					if (prev_obj == nullptr){
						//1. 1���� ������
						if (search_key_obj->next == nullptr){
							Root_Node->delType();
							Root_Node->setType(JNode::JType::OBJ);
						}
						//2. ������ ������ 0�� ��ü�� ������� �Ҷ�
						else{
							JObj* next_root_obj = search_key_obj->next;
							search_key_obj->next = nullptr;
							Root_Node->delType();
							Root_Node->Cur_Type = JNode::JType::OBJ;
							Root_Node->P_Type = next_root_obj;
							Root_Node->ObjCnt--;
						}
					}
					//2. ������ ������
					else{
						prev_obj->next = search_key_obj->next;
						search_key_obj->next = nullptr;
						delete search_key_obj;
						Root_Node->ObjCnt--;
					}

					return;
				}
				//������ �����ε����� ó���ϵ��� �ش� Ű�� ���� ��ü�� �Ѱ��ֱ�
				Cur_Obj = search_key_obj;
			}
			else{//�ش� Ű�� ���� ��ü�� �������� ����
				if (trg_del == true){
					//������ ��ü�� �������� ������
					Cur_Obj = nullptr;
					Cur_Arr = nullptr;
					Cur_Node = nullptr;
					return;
				}

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
		JsonCallObjArr(JNode* node, int index, bool trg_del = false) : Root_Obj(nullptr){
			Root_Node = node;
			int max_idx = -1;
			Root_Arr = static_cast<JArr*>(Root_Node->P_Type);
			JArr* search_idx_arr = Root_Arr->RootSearchIndex(index);
			JArr* tail_arr = Root_Arr->getTailArr(&max_idx);

			if (index == -1) index = max_idx + 1;		//-1�̸� �׳� �ڿ� �߰�

			//1. Root_Node�� ���°� "[]" �̷� �����϶� �ƹ� �迭�� ���� ������ 
			if (Root_Node->ArrCnt == -1){
				if (trg_del == true){
					//������ �迭�� �������� ������
					Cur_Obj = nullptr;
					Cur_Arr = nullptr;
					Cur_Node = nullptr;
					return;
				}

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
				if (trg_del == true){
					//������ �ε����� ��Ұ� �����Ҷ�
					JArr* prev_arr = search_idx_arr->getPrevArr(search_idx_arr, Root_Node);
					//1. 1�� Ȥ�� ������ ������ 0�� ��ü�϶�
					if (prev_arr == nullptr){
						//1. 1���� ������
						if (search_idx_arr->next == nullptr){
							Root_Node->delType();
							Root_Node->setType(JNode::JType::ARR);
						}

						//2. ������ ������ 0�� ��ü�� ������� �Ҷ�
						else{
							JArr* next_root_arr = search_idx_arr->next;
							search_idx_arr->next = nullptr;
							Root_Node->delType();
							Root_Node->Cur_Type = JNode::JType::ARR;
							Root_Node->P_Type = next_root_arr;
							Root_Node->ArrCnt--;
						}
					}
					//2. ������ ������
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
			// �ش� idx�� ���� ���� �������� ������
			
			else{
				if (trg_del == true){
					//������ �ε����� ��Ұ� �������� ������
					Cur_Obj = nullptr;
					Cur_Arr = nullptr;
					Cur_Node = nullptr;
					return;
				}

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

		//�׳� �ǵڿ� push Ȥ�� del �ϱ� ���� ������
		JsonCallObjArr(JNode* node, JNode::JType curType, bool trg_del = false);

		
		

		//������ push or del �ϱ�
		//obj�� �Ⱦ�����
		void obj_push(JNode* node){
			Root_Arr = nullptr;
			//1. obj�� ó�����ֱ�
			Root_Node = node;
			Root_Obj = static_cast<JObj*>(Root_Node->P_Type);
			JObj* tail_obj = Root_Obj->getTailObj();
			//2. ��ü�� �ƹ����� �������� ������ �׳� ���Ӱ� �ϳ� �����
			if (Root_Node->ObjCnt == -1){
				
			}

			//3. ���� �����ؼ� �ǵڱ��� �����ؾ��Ҷ�
		}

		void arr_push(JNode* node){
			Root_Obj = nullptr;
			//1. arr�� ó�����ֱ�
			Root_Node = node;
			int max_idx = -1;
			Root_Arr = static_cast<JArr*>(Root_Node->P_Type);
			JArr* tail_arr = Root_Arr->getTailArr(&max_idx);
			//2. �迭�� �ƹ����� �������� ������ �׳� ���Ӱ� �ϳ� �����
			if (Root_Node->ArrCnt == -1){
				Root_Arr->setValue(JNode::JType::NULLTYPE);
				Root_Arr->next = nullptr;
				Root_Node->ArrCnt++;

				Cur_Arr = Root_Arr;
			}

			//3. ���� �����ؼ� �ǵڱ��� �����ؾ��Ҷ�
			else if(Root_Node->ArrCnt >= 0){
				JArr* new_arr = new JArr();
				new_arr->setValue(JNode::JType::NULLTYPE);
				new_arr->next = nullptr;
				Root_Node->ArrCnt++;

				tail_arr->next = new_arr;

				Cur_Arr = new_arr;
			}
			//������ �����ε����� ����� ���ҽ� �ʱ�ȭ ���ֱ�
			Cur_Node = Root_Node;
			Cur_Obj = Root_Obj;		//nullptr
		}

		void obj_del(JNode* node){
			Root_Arr = nullptr;
			//1. obj�� ó�����ֱ�
			Root_Node = node;
			Root_Obj = static_cast<JObj*>(Root_Node->P_Type);
			
			//2. ��ü ���°� "{}"�϶�
			if (Root_Node->ObjCnt == -1){
				return;
				//�������� �׳� ��ȯ
			}

			//3. ��ü ���°� "{..}"�϶�
			else{
				JObj* tail_obj = Root_Obj->getTailObj();
				JObj* prev_obj = Root_Obj->getPrevObj(tail_obj, Root_Node);

				if (prev_obj == nullptr){
					//1���� ����������
					Root_Node->delType();
					Root_Node->setType(JNode::JType::OBJ);
				}
				else{
					//�������� ����������
					prev_obj->next = nullptr;
					Root_Node->ObjCnt--;
					delete tail_obj;
				}
			}
		}

		void arr_del(JNode* node){
			Root_Obj = nullptr;
			//1. Arr�� ó�����ֱ�
			Root_Node = node;
			Root_Arr = static_cast<JArr*>(Root_Node->P_Type);

			//2. �迭 ���°� "[]"�϶�
			if (Root_Node->ArrCnt == -1) {
				return;
				//�������� �׳� ��ȯ
			}

			//3. �迭 ���°� "[..]"�϶�
			else{
				JArr* tail_arr = Root_Arr->getTailArr();
				JArr* prev_arr = Root_Arr->getPrevArr(tail_arr, Root_Node);

				if (prev_arr == nullptr){
					//1������������
					Root_Node->delType();
					Root_Node->setType(JNode::JType::ARR);
				}
				else{
					//������ ����������
					prev_arr->next = nullptr;
					Root_Node->ArrCnt--;
					delete tail_arr;
				}
				

			}
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
		void operator= (const char*);
		void operator=(char*);
		void operator=(JNode*);
		void operator=(JNode::JType curType);

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
						
						//���ڿ� �Ľ� ���ִ°� �ʿ�
						Cur_Obj->Value->isObjArrCk(lval);

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

						//���ڿ� �Ľ� ���ִ°� �ʿ�
						Cur_Arr->Value->isObjArrCk(lval);
					}
					else{//����
						DynamicStr* lval = static_cast<DynamicStr*>(Cur_Arr->Value->P_Type);
						char* rval = static_cast<char*>(rValue);
						lval->Set_Char(&rval[0]);
					}
				}
				else if (curType == JNode::JType::OBJ){
					//�ʿ���� Ȯ�� 99
					//���Խ� JNode["Key"] = JArr�� �ѱ�°� �����Ұű� ���� ������ ������ JNode�� �ѱ� �� ����
				}
				else if (curType == JNode::JType::ARR){
					//�ʿ���� Ȯ�� 99
					//���Խ� JNode["Key"] = JArr�� �ѱ�°� �����Ұű� ���� ������ ������ JNode�� �ѱ� �� ����
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




	class ValRss{
	public :
		ValRss() : /*FullVal(128),*/ Key(128), Value(128), curType(JNode::JType::NULLTYPE){}
		~ValRss(){}
		//Dynamic::DynamicStr FullVal;		//��� �ɵ� ���⼭ �������� ����
		Dynamic::DynamicStr Key;
		Dynamic::DynamicStr Value;
		JNode::JType curType;
	};

	//���� �迭
	class ValArr{
	public:
		ValArr(){
			Val = new ValRss[128];
			curCsr = 0;
		}
		ValArr(int capacity) {
			Val = new ValRss[capacity];
			curCsr = 0;
		}
		~ValArr(){
			if (Val != nullptr){
				delete[] Val;
			}
		}

	private:
#define KeyFst  0
#define KeyLst  1
#define ValFst  2
#define ValLst  3
#define IS_TRIM_CHAR(c) ((c) == ' '|| (c) == '\n' || (c) == '\t')

		void setTrim(){
			char key_fstWrd;
			char key_lstWrd;
			char val_fstWrd;
			char val_lstWrd;
			

			//0 1 - key     2,3 - Value
			int FstLstIdx[4] = { 0, Val[curCsr].Key.current_size - 1, 0, Val[curCsr].Value.current_size - 1 };
			


			key_fstWrd = Val[curCsr].Key.Char_Get_Str(FstLstIdx[KeyFst]);
			key_lstWrd = Val[curCsr].Key.Char_Get_Str(FstLstIdx[KeyLst]);

			val_fstWrd = Val[curCsr].Value.Char_Get_Str(FstLstIdx[ValFst]);
			val_lstWrd = Val[curCsr].Value.Char_Get_Str(FstLstIdx[ValLst]);

			DynamicStr* copyStr = new DynamicStr(128);

			while (IS_TRIM_CHAR(key_fstWrd) || IS_TRIM_CHAR(key_lstWrd) ||
				IS_TRIM_CHAR(val_fstWrd) || IS_TRIM_CHAR(val_lstWrd)){
				
				if (IS_TRIM_CHAR(key_fstWrd)){		//�ձ��ڸ� ���������
					Val[curCsr].Key.Str_Trim_Front();
					key_fstWrd = Val[curCsr].Key.Char_Get_Str(FstLstIdx[KeyFst]);
				}
				if (IS_TRIM_CHAR(key_lstWrd)){		//�ޱ��ڸ� ���������
					Val[curCsr].Key.Str_Trim_Back();
					key_lstWrd = Val[curCsr].Key.Char_Get_Str(FstLstIdx[KeyLst]);
				}
				if (IS_TRIM_CHAR(val_fstWrd)){		//�ձ��ڸ� ���������
					Val[curCsr].Value.Str_Trim_Front();
					val_fstWrd = Val[curCsr].Value.Char_Get_Str(FstLstIdx[ValFst]);
				}
				if (IS_TRIM_CHAR(val_lstWrd)){		//�ޱ��ڸ� ���������
					Val[curCsr].Value.Str_Trim_Back();
					val_lstWrd = Val[curCsr].Value.Char_Get_Str(FstLstIdx[ValLst]);
				}
			}
		}

	public:

		//������ �ø���
		void UpBuf(int _capacity){
			if (capacity >= _capacity){
				//���� �뷮���� �۾Ƽ� �Ұ���
				return;
			}
			ValRss* newVal = new ValRss[_capacity];
			for (int i = 0; i <= capacity; i ++){
				//newVal[i].FullVal.Set_Str(Val[i].FullVal.Get_Str());
				newVal[i].Key.Set_Str(Val[i].Key.Get_Str());
				newVal[i].Value.Set_Str(Val[i].Value.Get_Str());
			}
			delete[] Val;
			Val = nullptr;
			Val = newVal;
			capacity = _capacity;
		}

		//�ǵڿ� ����
		void setObjRss(Dynamic::DynamicStr* Key, Dynamic::DynamicStr* Value){
			if (curCsr >= capacity - 1){
				//������ Ŀ�� UpBuf�������
				UpBuf(capacity * 2);
			}
			Val[curCsr].Key.Set_Str(Key->Get_Str());
			Val[curCsr].Value.Set_Str(Value->Get_Str());
			//Val[curCsr].FullVal.Set_Str(FullVal->Get_Str());
			Val[curCsr].curType = JNode::JType::OBJ;

			//Ȥ�� �𸣴ϱ� �������ִ� �޼ҵ� ���
			setTrim();
			curCsr++;
		}

		//�迭���� �� �ֱ� �迭�϶��� Ű���� �ʿ�����ϱ� ��������
		void setArrRss(Dynamic::DynamicStr* Value){
			if (curCsr >= capacity - 1){
				//������ Ŀ�� UpBuf�������
				UpBuf(capacity * 2);
			}
			Val[curCsr].Value.Set_Str(Value->Get_Str());
			//Val[curCsr].FullVal.Set_Str(FullVal->Get_Str());
			Val[curCsr++].curType = JNode::JType::ARR;
		}

	protected:
		int capacity;		//�뷮	�������� �ø�����
		int curCsr;
		ValRss* Val;
		//FullVal ���� ������ �ұ�?
	};

	//���ڿ� �Ľ� -> JNode�� ��ȯ
	class StrParser : public ValArr {
	public:
		StrParser(JNode* RootNode, Dynamic::DynamicStr* RootStr, JNode::JType RootNodeType) : ValArr(64),
					RootNode(RootNode), RootStr(RootStr), RootNodeType(RootNodeType), gCsr(0), 
					Key(nullptr), Value(nullptr), FullVal(nullptr){
			ParserMain();
		}

		enum class WrdInfo{
			Init,
			KEY,
			STR,
			VALUE,
			IDLE,		//���� ��� Ȯ���� ���� ����
		};

		void Test(){
			
		}
		
		void ParserMain(){
			//if (RootNodeType == JNode::JType::OBJ){
			//	//RootNode�� P_Type(Str) ������� Obj "{}" ����� �Ľ�����
			//	ObjParser();
			//}
			//else if (RootNodeType == JNode::JType::ARR){
			//	//RootNode�� P_Type(Str) ������� Arr "[]" ����� �Ľ�����
			//	ArrParser();
			//}

			Parser();
		}

		//objValue.Value Ȥ�� arrValue.Value�� ���� ������ Ÿ�Ժ�ȯ ���ֱ�
		void ValueAsciiParser(){

			//���࿡ ��ø�Ȱ� ���Դٸ�
			//JNode ���Ӱ� ����� JNode = Str; �־ ��ø�Ȱ� �Ľ��ϸ� ��
		}


		// FullVal - (Key:Value), FullVal - (Value)
		void ValueParser(){
			

		}


		void Parser() {
			short BrcCnt = 0;      //'{'�� ���� ����
			short BrkCnt = 0;      //'['�� ���� ����
			bool qtStt = false;      //'"'���� ����

			FullVal = new DynamicStr(128);
			Key = new DynamicStr(128);
			Value = new DynamicStr(128);

			JNode::JType curType = RootNodeType;
			WrdInfo curWrdType = WrdInfo::IDLE;

			while (1) {
				PrvWrd = RootStr->Char_Get_Str(gCsr - 1);
				CurWrd = RootStr->Char_Get_Str(gCsr);
				NxtWrd = RootStr->Char_Get_Str(gCsr + 1);

				if (CurWrd == '{') {
					BrcCnt++;
				}
				else if (CurWrd == '}') {
					BrcCnt--;
				}
				if (CurWrd == '[') {
					BrkCnt++;
				}
				else if (CurWrd == ']') {
					BrkCnt--;
				}

				if (CurWrd == '"' && PrvWrd != '\\') {
					if (qtStt == true) qtStt = false;
					else if (qtStt == false) qtStt = true;
				}


				if (curType == JNode::JType::OBJ) {//Key�� Value�� �����ϱ�
					if (CurWrd == ',' && (BrcCnt == 1 && BrkCnt == 0)) {//�̶��� FullVal�� �߰���
						FullVal->Append_Char(&CurWrd);
						
						setObjRss(Key, Value);

						delete FullVal;
						delete Key;
						delete Value;

						//FullVal = new DynamicStr(128);
						Key = new DynamicStr(128);
						Value = new DynamicStr(128);

						curWrdType = WrdInfo::IDLE;
					}


					if (CurWrd == '}' && (BrcCnt == 0 && BrkCnt == 0)) {//���� �Ǻ�
						FullVal->Append_Char(&CurWrd);



						//���⼭ ���� ������ �Ľ��ϱ� ���� �޼ҵ尡 �ʿ��Ұ� ���� 
						break;
					}


					//FullVal ó��
					FullVal->Append_Char(&CurWrd);

					//Key ã��
					if (curWrdType == WrdInfo::IDLE && CurWrd == '"' && qtStt == true) {
						curWrdType = WrdInfo::KEY;
					}
					else if (curWrdType == WrdInfo::KEY) {
						if (CurWrd == '"' && qtStt == false) {   //Key��
							curWrdType = WrdInfo::IDLE;
						}
						else
							Key->Append_Char(&CurWrd);
					}

					//Value ã��
					else if (curWrdType == WrdInfo::IDLE && CurWrd == ':') {
						curWrdType = WrdInfo::VALUE;
					}
					else if (curWrdType == WrdInfo::VALUE) {
						Value->Append_Char(&CurWrd);
					}






				}
				else if (curType == JNode::JType::ARR) {//Value�� �����ϱ�
					if (CurWrd == ',' && (BrkCnt == 1 && BrcCnt == 0)) { //�̶��� FullVal�� �߰���
						//setArrRss();
						delete FullVal;
						delete Key;
						delete Value;

						FullVal = new DynamicStr(128);
						Key = new DynamicStr(128);
						Value = new DynamicStr(128);
					}

					if (CurWrd == ']' && (BrkCnt == 1 && BrcCnt == 0)) { //�����Ǻ�
						//setArrRss();
						break;
					}


					//FullVal ó��




				}
				gCsr++;
			}
			delete FullVal;
			delete Key;
			delete Value;
		}

		


	private:
		JNode* RootNode;		//��ü������ ����� �����Ǿ �ȵ� ���� ������ �ٲٴ°� ���������� �̹� ��ü ������ �Ȼ�����
		JNode* CtrlNode;
		DynamicStr* RootStr;		//�����ǵ� �ǹ̴� ���� RootNode�� ���� �߿��ѰŶ�
		DynamicStr* CtrlStr;

		DynamicStr* FullVal;		//����̱� ���� ���ڵ�
		DynamicStr* Key;
		DynamicStr* Value;

		JNode::JType RootNodeType;
		int gCsr;			//���� ��Ʈ���� ���� ����
		char CurWrd;		//
		char NxtWrd;		//
		char PrvWrd;		//
	};


	//JNode �Ľ� -> Json���� ��ȯ
	class JsonMaker {
	public:
		JsonMaker() {}
		~JsonMaker() {}

	private:

	};

}