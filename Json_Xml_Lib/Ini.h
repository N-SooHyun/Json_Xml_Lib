#pragma once

#include <stdio.h>
#include <iostream>

//Ini 파일 파싱 -> JNode를 활용해 Dict 구조로 변환 {"SECTION" : {"KEY" : VALUE }}
class IniParser{
protected:
	DynamicStr* IniStr;
	char CurChar;
	char PrvChar;
	char NxtChar;
	int glb_csr;
	JNode *IniNode;
	bool ParseFin;

	inline bool isFileCk(FILE* ckFile){
		if (!ckFile){
			printf("File Error: Please check the file path\n");
			return false;
		}
		return true;
	}

	void InitStr(int StrSize){
		IniStr = new DynamicStr(StrSize);
		CurChar = ' ';
		PrvChar = ' ';
		NxtChar = ' ';
		glb_csr = 0;
		IniNode = new JNode();
		ParseFin = false;
	}


	virtual void Parse(){
		short BrkCnt = 0;       // '['의 개수 추적
		bool isKey = false;		// KEY= 임을 확인 Section내부에 '\n'다음이면 무조건 true
		bool isSecArea = false;		// 특정 영역의 Section임을 확인 이를 통해 키인지 밸류인지 구분가능
		bool bfrVal = false;
		bool isVal = false;		// Value임을 확인

		enum IniStt{
			DFT,
			SEC,
			KEY,
			VAL,
			CMT,	//주석
		};

		DynamicStr* Section = new DynamicStr(128);
		DynamicStr* Key = new DynamicStr(128);
		DynamicStr* Val = new DynamicStr(128);

		JNode* KeyVal = new JNode();
		JObj* debugObj;



		IniStt stt = DFT;
		while (1){
			PrvChar = IniStr->Char_Get_Str(glb_csr - 1);
			CurChar = IniStr->Char_Get_Str(glb_csr);
			NxtChar = IniStr->Char_Get_Str(++glb_csr);

			if (CurChar == EOF){
				if (isSecArea){
					if (stt == VAL){
						char* SectKey = Key->Get_Str();
						(*KeyVal)[static_cast<const char*>(SectKey)] = JNode::JType::NULLTYPE;
					}
					isSecArea = false;
					isKey = false;
					isVal = false;
					//전에 있던거 넣어주기
					char* Sect = Section->Get_Str();

					(*IniNode)[static_cast<const char*>(Sect)] = KeyVal;


					//debug
					debugObj = static_cast<JObj*>(IniNode->P_Type);
					JObj* debugObjVal = static_cast<JObj*>(debugObj->Value->P_Type);
				}

				debugObj = static_cast<JObj*>(IniNode->P_Type);
				if (Section != nullptr){
					delete Section;
				}
				if (Key != nullptr){
					delete Key;
				}
				if (Val != nullptr){
					delete Val;
				}
				if (KeyVal != nullptr){
					delete KeyVal;
				}
				ParseFin = true;
				break;
			}

			//Status 확인
			if (stt == DFT){
				if (CurChar == '['){
					if (isSecArea){
						isSecArea = false;
						isKey = false;
						isVal = false;
						//전에 있던거 넣어주기
						char* Sect = Section->Get_Str();
						(*IniNode)[static_cast<const char*>(Sect)] = KeyVal;

						//debug
						debugObj = static_cast<JObj*>(IniNode->P_Type);
						JObj* debugObjVal = static_cast<JObj*>(debugObj->Value->P_Type);

						delete Section;
						Section = new DynamicStr(128);
					}
					BrkCnt++;
					isSecArea = true;
					stt = SEC;
					continue;
				}
				else if (CurChar == ']'){
					BrkCnt--;
					isKey = true;
					stt = KEY;
					continue;
				}
				else if (CurChar == '='){
					isVal = true;
					stt = VAL;
					continue;
				}
				else if (CurChar == '#' || CurChar == ';'){
					stt = CMT;
					continue;
				}
				else if (CurChar == '\n' || CurChar == '\t' || CurChar == ' '){
					continue;
				}
				else if (isSecArea){
					glb_csr--;
					stt = KEY;
					continue;
				}
			}

			switch (stt){
			case SEC:
			{
				Section->Append_Char(&CurChar);
				if (NxtChar == ']'){
					Section->Str_Trim_All();
					stt = DFT;
				}
				break;
			}
			case KEY:
			{
				Key->Append_Char(&CurChar);
				if (NxtChar == '='){
					Key->Str_Trim_All();
					stt = DFT;
					isKey = false;
				}
				break;
			}
			case VAL:
			{
				//NULL처리해줘야함
				if (CurChar == '\n'){
					//NULL값을 의미
					stt = DFT;
					isVal = false;

					char* SectKey = Key->Get_Str();
					(*KeyVal)[static_cast<const char*>(SectKey)] = JNode::JType::NULLTYPE;

					//debug 용
					debugObj = static_cast<JObj*>(KeyVal->P_Type);
					delete Key;
					delete Val;

					Key = new DynamicStr(128);
					Val = new DynamicStr(128);
					break;
				}
				Val->Append_Char(&CurChar);
				if (NxtChar == '\n' || NxtChar == EOF){
					Val->Str_Trim_All();
					stt = DFT;
					isVal = false;

					char* SectKey = Key->Get_Str();
					char* SectVal = Val->Get_Str();

					(*KeyVal)[static_cast<const char*>(SectKey)] = SectVal;

					//debug 용
					debugObj = static_cast<JObj*>(KeyVal->P_Type);

					delete Key;
					delete Val;

					Key = new DynamicStr(128);
					Val = new DynamicStr(128);
				}
				
				break;
			}
			case CMT:
			{
				if (CurChar == '\n'){
					stt = DFT;
				}
				break;
			}
			}
		}

	}

public:

	IniParser(){
		InitStr(1024);
	}

	IniParser(const char* Str){
		InitStr(1024);
		if (Str != nullptr) return;
		char c = ' ';
		for (int i = 0;; i++){
			if (c == '\0') break;

			c = Str[i];

			IniStr->Append_Char(&c);

		}
	}

	IniParser(FILE* rFile){
		if (!isFileCk(rFile))
			return;
		InitStr(1024);
		ReadFileIni(rFile);
	}

	~IniParser(){
		if (IniStr != nullptr) delete IniStr;
	}


	void ReadFileIni(FILE* rFile){
		char c = ' ';

		while (1){
			if (c == EOF) break;

			c = fgetc(rFile);
			IniStr->Append_Char(&c);
		}
	}

	void ParseMain(){
		if (IniStr != nullptr){
			Parse();
		}
		else
			printf("파일이 없거나 읽어온 문자열이 없습니다.\n");
	}

	JNode* getNode(){
		if (ParseFin){
			return IniNode;
		}
		return nullptr;
	}


};

//Error List TSHOOT 전용 ErrorList Ini Parser
class ErrLst_Ini : public IniParser{
public:
	ErrLst_Ini(){}

	ErrLst_Ini(const char* Str) : IniParser(Str){}

	ErrLst_Ini(FILE* rFile) : IniParser(rFile){}

	~ErrLst_Ini(){}

	virtual void Parse(){
		short BrkCnt = 0;       // '['의 개수 추적
		bool isKey = false;      // KEY= 임을 확인 Section내부에 '\n'다음이면 무조건 true
		bool isSecArea = false;      // 특정 영역의 Section임을 확인 이를 통해 키인지 밸류인지 구분가능
		bool bfrVal = false;
		bool isVal = false;      // Value임을 확인

		enum IniStt{
			DFT,
			SEC,
			KEY,
			VAL,
			CMT,   //주석
			TSH,   //TShoot 전용(ErrLst전용)
		};

		DynamicStr* Section = new DynamicStr(128);
		DynamicStr* Key = new DynamicStr(128);
		DynamicStr* Val = new DynamicStr(128);
		DynamicStr* Tsh = new DynamicStr(128);

		bool isTsh = false;   //Tsh값 유무체크
		short TshCnt = -1;	  //Tsh 배열 크기 체크

		JNode* KeyVal = new JNode();
		JNode* TshVal = new JNode();

		JObj* debugObj;



		IniStt stt = DFT;
		while (1){
			PrvChar = IniStr->Char_Get_Str(glb_csr - 1);
			CurChar = IniStr->Char_Get_Str(glb_csr);
			NxtChar = IniStr->Char_Get_Str(++glb_csr);

			if (CurChar == EOF){
				if (isSecArea){
					if (stt == VAL){
						char* SectKey = Key->Get_Str();
						(*KeyVal)[static_cast<const char*>(SectKey)] = JNode::JType::NULLTYPE;
					}
					else if (stt == TSH){
						(*TshVal) = JNode::JType::NULLTYPE;
						char* SectKey = Key->Get_Str();
						(*KeyVal)[static_cast<const char*>(SectKey)] = TshVal;	//배열을 넣기
					}
					isSecArea = false;
					isKey = false;
					isVal = false;
					isTsh = false;
					//전에 있던거 넣어주기
					char* Sect = Section->Get_Str();
					(*IniNode)[static_cast<const char*>(Sect)] = KeyVal;

					//debug
					debugObj = static_cast<JObj*>(IniNode->P_Type);
					JObj* debugObjVal = static_cast<JObj*>(debugObj->Value->P_Type);
				}

				debugObj = static_cast<JObj*>(IniNode->P_Type);
				if (Section != nullptr){
					delete Section;
				}
				if (Key != nullptr){
					delete Key;
				}
				if (Val != nullptr){
					delete Val;
				}
				if (KeyVal != nullptr){
					delete KeyVal;
				}
				ParseFin = true;
				break;
			}

			//Status 확인
			if (stt == DFT){
				if (CurChar == '['){
					if (isSecArea){
						isSecArea = false;
						isKey = false;
						isVal = false;
						//전에 있던거 넣어주기
						char* Sect = Section->Get_Str();

						(*IniNode)[static_cast<const char*>(Sect)] = KeyVal;

						//debug
						debugObj = static_cast<JObj*>(IniNode->P_Type);
						JObj* debugObjVal = static_cast<JObj*>(debugObj->Value->P_Type);


						delete Section;
						Section = new DynamicStr(128);
					}
					BrkCnt++;
					isSecArea = true;
					stt = SEC;
					continue;
				}
				else if (CurChar == ']'){
					BrkCnt--;
					isKey = true;
					stt = KEY;
					continue;
				}
				else if (CurChar == '='){
					if (Key->StrCmp("TSHOOT")){
						stt = TSH;
						if (NxtChar == '\n') glb_csr++;
					}
					else{
						isVal = true;
						stt = VAL;
					}
					continue;
				}
				else if (CurChar == '#' || CurChar == ';'){
					stt = CMT;
					continue;
				}
				else if (CurChar == '\n' || CurChar == '\t' || CurChar == ' '){
					continue;
				}
				else if (isSecArea){
					glb_csr--;
					stt = KEY;
					continue;
				}
			}

			switch (stt){
			case SEC:
			{
				Section->Append_Char(&CurChar);
				if (NxtChar == ']'){
					Section->Str_Trim_All();
					stt = DFT;
				}
				break;
			}
			case KEY:
			{
				Key->Append_Char(&CurChar);
				if (NxtChar == '='){
					Key->Str_Trim_All();
					stt = DFT;
					isKey = false;
				}
				break;
			}
			case VAL:
			{
				//NULL처리해줘야함
				if (CurChar == '\n'){
					//NULL값을 의미
					stt = DFT;
					isVal = false;

					char* SectKey = Key->Get_Str();
					(*KeyVal)[static_cast<const char*>(SectKey)] = JNode::JType::NULLTYPE;

					//debug 용
					debugObj = static_cast<JObj*>(KeyVal->P_Type);
					delete Key;
					delete Val;

					Key = new DynamicStr(128);
					Val = new DynamicStr(128);
					break;
				}
				Val->Append_Char(&CurChar);
				if (NxtChar == '\n' || NxtChar == EOF){
					Val->Str_Trim_All();
					stt = DFT;
					isVal = false;

					char* SectKey = Key->Get_Str();
					char* SectVal = Val->Get_Str();

					(*KeyVal)[static_cast<const char*>(SectKey)] = SectVal;

					//debug 용
					debugObj = static_cast<JObj*>(KeyVal->P_Type);

					delete Key;
					delete Val;

					Key = new DynamicStr(128);
					Val = new DynamicStr(128);
				}
				break;
			}
			case CMT:
			{
				if (CurChar == '\n'){
					stt = DFT;
				}
				break;
			}
			case TSH:
			{
				if (NxtChar == EOF || NxtChar == '['){
					//종료 처리
					if (isTsh){
						Tsh->Append_Char(&CurChar);
						Tsh->Str_Trim_All();
						(*TshVal)[TshCnt] = Tsh->Get_Str();
					}


					char* SectKey = Key->Get_Str();
					(*KeyVal)[static_cast<const char*>(SectKey)] = TshVal;	//배열을 넣기

					delete Key;
					Key = new DynamicStr(128);

					isTsh = false;
					stt = DFT;
					TshCnt = -1;
					break;
				}
				else if (CurChar == '['){
					//값이 NULL인 경우임
					(*TshVal) = JNode::JType::NULLTYPE;
					char* SectKey = Key->Get_Str();
					(*KeyVal)[static_cast<const char*>(SectKey)] = TshVal;	//배열을 넣기

					delete Key;
					Key = new DynamicStr(128);

					isTsh = false;
					stt = DFT;
					TshCnt = -1;
					glb_csr--;
					break;
				}
				else if (CurChar == '\n'){
					//새로운 배열이 있거나 혹은 값이 Null인 경우
					if (isTsh){
						Tsh->Str_Trim_All();
						(*TshVal)[TshCnt] = Tsh->Get_Str();

						isTsh = false;
						delete Tsh;
						Tsh = new DynamicStr(128);
					}
					else{
						//값이 NULL인 경우임
						(*TshVal) = JNode::JType::NULLTYPE;
						continue;
					}
				}
				else if (CurChar != '\n'){
					//값이 있는 경우
					if (!isTsh){
						isTsh = true;
						TshCnt++;
					}
					Tsh->Append_Char(&CurChar);
				}

				break;
			}
			}
		}

	}


};





//{Sect : {Key : Value}} to
//[Sect]
//Key=Value


class JsonToIni{
public:
	JsonToIni(){}

	~JsonToIni(){}

private:


};