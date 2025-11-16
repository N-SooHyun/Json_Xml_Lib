#pragma once

/*
	<전체 구조>
	.ini -> Str생성 -> Json화
*/


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

	void AsciiToVal(JNode* KeyValNode, DynamicStr* KeyStr, DynamicStr* ValStr){
		//ValStr 기준으로 가는거임 이걸 기준으로 실값인지 아닌지 판단해서 넣어주기
		//숫자, 논리, 문자열만 파싱해주고 {} []타입은 그냥 Node에 넣어주면 알아서 해줄거임
		int RstInt = 0;
		double RstDbl = 0.0;
		bool IsDbl = false;      //false -> int, true -> double
		bool RstBl = false;

		int ValStrCsr = 0;	//Value 문자열용 커서

		enum CkWrd{
			DFT,
			STR,
			M_NUM,
			P_NUM,
			OBJ,   //Str로 넣어버리기
			ARR,   //Str로 넣어버리기
			BL,
			END
		};

		CkWrd CrntVal = DFT;
		char PrvWrd, CurWrd, NxtWrd = ' ';
		char* SectKey = KeyStr->Get_Str();


		for (;; ValStrCsr++){
			PrvWrd = ValStr->Char_Get_Str(ValStrCsr - 1);
			CurWrd = ValStr->Char_Get_Str(ValStrCsr);
			NxtWrd = ValStr->Char_Get_Str(ValStrCsr + 1);

			//시작 판별
			if (CrntVal == DFT){
				//음의 숫자일 경우(음의 정수, 음의 실수)
				if (CurWrd == '-' && (NxtWrd >= '0' && NxtWrd <= '9')) {
					CrntVal = M_NUM;
				}
				//양의 숫자일 경우(양의 정수, 양의 실수)
				else if (CurWrd >= '0' && CurWrd <= '9') {
					CrntVal = P_NUM;
					ValStrCsr--;
				}
				//bool일 경우
				else if (CurWrd == 't' || CurWrd == 'f') {
					CrntVal = BL;
					ValStrCsr--;
				}
				else if (CurWrd == '{'){
					if (ValStr->Char_Get_Str(ValStr->current_size - 1) == '}'){
						CrntVal = OBJ;
						ValStrCsr--;
					}
				}
				else if (CurWrd == '['){
					if (ValStr->Char_Get_Str(ValStr->current_size - 1) == ']'){
						CrntVal = ARR;
						ValStrCsr--;
					}
				}
				else{	//위에거 제외하면 그냥 문자열로 처리하셈 귀찮으니까
					CrntVal = STR;
					ValStrCsr--;
				}
			continue;
			}
			//종료 판별
			else if (CrntVal == END){
				break;
			}
			//값 처리
			else{
				switch (CrntVal){
				case STR:
				case OBJ:
				case ARR:
					
					//OBJ든 ARR이든 그냥 문자열로 JNode에 넣어주면 알아서 객체라고 판단해서 결과 내보내줄거임
					(*KeyValNode)[static_cast<const char*>(SectKey)] = ValStr->Get_Str();
					CrntVal = END;
					break;
				case M_NUM: 
				case P_NUM:
				{
					if (CurWrd < '0' || CurWrd > '9') {
						//값자기 값이  123T 이러면 문자열이니까 문자열로 처리해주기
						CrntVal = STR;
						break;
					}
					//값 넣기
					RstInt = RstInt * 10 + (CurWrd - '0');

					//소수 판별
					if (NxtWrd == '.'){
						IsDbl = true;
						ValStrCsr += 2;
						double decimal_part = 0;
						int divisor = 10;
						bool isStr = false;
						for (;; ValStrCsr++){
							PrvWrd = ValStr->Char_Get_Str(ValStrCsr - 1);
							CurWrd = ValStr->Char_Get_Str(ValStrCsr);
							NxtWrd = ValStr->Char_Get_Str(ValStrCsr + 1);
							if (CurWrd < '0' || CurWrd > '9') {
								//값자기 값이  123.12T 이러면 문자열이니까 문자열로 처리
								CrntVal = STR;
								isStr = true;
								break;
							}
							decimal_part = decimal_part + (CurWrd - '0') / (double)divisor;
							divisor *= 10;
							if (NxtWrd == '\0') break;
						}
						if (isStr) break;
						RstDbl = RstInt + decimal_part;
					}

					//정수 밸류 완성 종료 판별
					if (NxtWrd == '\0'){
						if (CrntVal == M_NUM){
							RstInt = RstInt * -1;
							RstDbl = RstDbl * -1;
						}
						if (IsDbl) 
							(*KeyValNode)[static_cast<const char*>(SectKey)] = RstDbl;
						else (*KeyValNode)
							[static_cast<const char*>(SectKey)] = RstInt;
						//(*KeyValNode)[static_cast<const char*>(SectKey)] = IsDbl==true ? RstDbl : RstInt;
						CrntVal = END;
					}
				}
					break;
				case BL:
				{
					char FstWrd = ValStr->Char_Get_Str(0);
					char ScdWrd = ValStr->Char_Get_Str(1);
					char ThdWrd = ValStr->Char_Get_Str(2);
					char FrWrd = ValStr->Char_Get_Str(3);
					char FivWrd = ValStr->Char_Get_Str(4);
					char SixWrd = ValStr->Char_Get_Str(5);
					if (FstWrd == 't' || FstWrd == 'T'){
						if (ScdWrd == 'r' && ThdWrd == 'u' && FrWrd == 'e' && FivWrd == '\0'){
							RstBl = true;
						}
						else{
							CrntVal = STR;
							break;
						}
					}
					else if (FstWrd == 'f' || FstWrd == 'F'){
						if (ScdWrd == 'a' && ThdWrd == 'l' && FrWrd == 's' && FivWrd == 'e' && SixWrd == '\0'){
							RstBl = false;
						}
						else{
							CrntVal = STR;
							break;
						}
					}
				}
					(*KeyValNode)[static_cast<const char*>(SectKey)] = RstBl ? true : false;
					CrntVal = END;
					break;				
				}

			}

		}



		
		(*KeyValNode)[static_cast<const char*>(SectKey)];	// = 실제 타입 값 넣어주기 Ascii 파싱해서

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
					//Ascii 처리해주기 문자열에서 -> 실제값으로 처리해주기
					AsciiToVal(KeyVal, Key, Val);
					stt = DFT;
					isVal = false;

					//char* SectKey = Key->Get_Str();
					//char* SectVal = Val->Get_Str();

					//(*KeyVal)[static_cast<const char*>(SectKey)] = SectVal;

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
		//if (IniNode != nullptr) delete IniNode;
	}


	void ReadFileIni(FILE* rFile){
		char c = ' ';

		while (1){
			c = fgetc(rFile);
			if (c == EOF) break;
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

private:
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

			if (CurChar == EOF || CurChar == '\0'){
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
				if (NxtChar == '\n' || NxtChar == EOF || NxtChar == '\0'){
					Val->Str_Trim_All();
					AsciiToVal(KeyVal, Key, Val);
					stt = DFT;
					isVal = false;

					//char* SectKey = Key->Get_Str();
					//char* SectVal = Val->Get_Str();
					//
					//(*KeyVal)[static_cast<const char*>(SectKey)] = SectVal;

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
				if (NxtChar == EOF || NxtChar == '[' || NxtChar == '\0'){
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
class JsonToIni : public IniParser{
private:
	union MyUnion {
		int num;
		bool bl;
		double dnum;
	};
	MyUnion Val;
	void PrtNode(JNode& node){
		DynamicStr* Str;
		switch (node.Cur_Type){
		case JNode::JType::NULLTYPE:   //종료
			printf("null");
			return;
		case JNode::JType::NUMBER:
			Val.num = node;
			printf("%d", Val.num);
			break;
		case JNode::JType::STRING:
			Str = static_cast<DynamicStr*>(node.P_Type);
			Str->Str_Trim_Quote();
			printf("%s", Str->Get_Str());
			break;
		case JNode::JType::BOOL:
			Val.bl = node;
			printf("%s", Val.bl == true ? "true" : "false");
			break;
		case JNode::JType::DOUBLE:
			Val.dnum = node;
			printf("%.3f", Val.dnum);
			break;
		case JNode::JType::OBJ:
			printf("{");
			JObj* obj;
			obj = static_cast<JObj*>(node.P_Type);

			for (int i = 0; i <= node.ObjCnt; i++, obj = obj->next){
				printf("\"%s\" : ", obj->Key.Get_Str());
				PrtNode(*obj->Value);

				if (i != node.ObjCnt) printf(", ");
			}

			printf("}");
			break;
		case JNode::JType::ARR:
			printf("[");
			JArr* arr;
			arr = static_cast<JArr*>(node.P_Type);
			for (int i = 0; i <= node.ArrCnt; i++, arr = arr->next){
				PrtNode(*arr->Value);

				if (i != node.ArrCnt) printf(",");
			}
			printf("]");
			break;
		default:
			break;
		}
	}

	void FPrtNode(FILE* fp, JNode& node) {
		DynamicStr* Str;

		switch (node.Cur_Type) {
		case JNode::JType::NULLTYPE:   // 종료
			//fprintf(fp, "null");
			return;

		case JNode::JType::NUMBER:
			Val.num = node;
			fprintf(fp, "%d", Val.num);
			break;

		case JNode::JType::STRING:
			Str = static_cast<DynamicStr*>(node.P_Type);
			Str->Str_Trim_Quote();
			fprintf(fp, "%s", Str->Get_Str());
			break;

		case JNode::JType::BOOL:
			Val.bl = node;
			fprintf(fp, "%s", Val.bl == true ? "true" : "false");
			break;

		case JNode::JType::DOUBLE:
			Val.dnum = node;
			fprintf(fp, "%.3f", Val.dnum);
			break;

		case JNode::JType::OBJ: {
			fprintf(fp, "{");
			JObj* obj = static_cast<JObj*>(node.P_Type);

			for (int i = 0; i <= node.ObjCnt; i++, obj = obj->next) {
				fprintf(fp, "\"%s\" : ", obj->Key.Get_Str());
				FPrtNode(fp, *obj->Value);

				if (i != node.ObjCnt)
					fprintf(fp, ", ");
			}

			fprintf(fp, "}");
			break;
		}

		case JNode::JType::ARR: {
			fprintf(fp, "[");
			JArr* arr = static_cast<JArr*>(node.P_Type);

			for (int i = 0; i <= node.ArrCnt; i++, arr = arr->next) {
				FPrtNode(fp, *arr->Value);

				if (i != node.ArrCnt)
					fprintf(fp, ",");
			}

			fprintf(fp, "]");
			break;
		}

		default:
			break;
		}
	}

	virtual void Parse(){
		enum NdStt{
			DFT,
			SCT,
			KEY,
			VAL,
		};

		//IniNode가 Root임
		(*IniNode) = IniStr->Get_Str();
		IniStr = nullptr;
		ParseFin = true;
	}
public:
	JsonToIni(){ InitStr(1024); }
	JsonToIni(const char* Str){
		InitStr(1024);
		if (Str != nullptr) return;
		char c = ' ';
		for (int i = 0;; i++){
			if (c == '\0') break;

			c = Str[i];
			IniStr->Append_Char(&c);
		}
	}
	JsonToIni(FILE* rFile){
		if (!isFileCk(rFile))
			return;
		InitStr(1024);
		ReadFileIni(rFile);
	}
	JsonToIni(JNode* node){
		IniNode = node;
		ParseFin = true;
	}
	~JsonToIni(){}

	void IniPrt(){
		Parse();
		if (ParseFin == false) return;

		JObj* RootObj = static_cast<JObj*>(IniNode->P_Type);
		JObj* JmpObj = RootObj;
		char* pSectKey;
		for (;;){
			if (JmpObj == nullptr)
				break;

			pSectKey = JmpObj->Key.Get_Str();
			JObj* KeyVal = static_cast<JObj*>(JmpObj->Value->P_Type);
			printf("[%s]\n", pSectKey);
			char* pKey = nullptr;
			char* pVal = nullptr;
			for (;;){
				if (KeyVal == nullptr) break;
				//Sect모드
				KeyVal->Key.Str_Trim_Quote();
				printf("%s=", KeyVal->Key.Get_Str());
				PrtNode(*KeyVal->Value);
				printf("\n");
				KeyVal = KeyVal->next;
			}
			JmpObj = JmpObj->next;

		}

	}

	void IniFPrt(FILE* pf){
		//Parse();
		if (ParseFin == false) return;

		JObj* RootObj = static_cast<JObj*>(IniNode->P_Type);
		JObj* JmpObj = RootObj;
		char* pSectKey;
		for (;;){
			if (JmpObj == nullptr)
				break;

			pSectKey = JmpObj->Key.Get_Str();
			JObj* KeyVal = static_cast<JObj*>(JmpObj->Value->P_Type);
			fprintf(pf, "[%s]\n", pSectKey);
			char* pKey = nullptr;
			char* pVal = nullptr;
			for (;;){
				if (KeyVal == nullptr) break;
				//Sect모드
				KeyVal->Key.Str_Trim_Quote();
				fprintf(pf, "%s=", KeyVal->Key.Get_Str());
				FPrtNode(pf, *KeyVal->Value);
				fprintf(pf, "\n");
				KeyVal = KeyVal->next;
			}
			JmpObj = JmpObj->next;

		}

	}
};



namespace INI_FUNC{
	FILE* RdFile(const char* rPath);

	FILE* WtFile(const char* wPath);

	//Ini -> Parse -> Json
	void Ini_To_Js();
	//Json -> Parse -> Ini
	void Js_To_Ini();

	//Ini 읽고 Json화 해서 -> Ini로 다시 파일 만들어내기
	void Ini_To_Js_To_Ini();
	//.ini 파일 읽어서 json에 추가하기
	void Ini_AddTo_Js();

	void Api_Js();
}


