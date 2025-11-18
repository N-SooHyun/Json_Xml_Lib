#pragma once

#include "Str.h"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace Dynamic;


//연산자 오버로딩
class OperCls{
public:

	//반환
	operator int();
	operator int*();
	operator double();
	operator double*();
	operator bool();
	operator bool*();
	operator char();
	operator char*();

	//대입은 상속이 안되는 특별한 경우라서 안된답니다.
	//void operator=(int);
	//void operator=(int*);
	//void operator=(double);
	//void operator=(double*);
	//void operator=(bool);
	//void operator=(bool*);
	//void operator=(char);
	//void operator=(const char*);
	//void operator=(char*);//변수로 들어오는 경우
};

/*
<Root  AttrObj=Value>
<Child>
</CHild>
</Root>

*/

//XmlObj
namespace XML{

	//속성용 객체(이름, 값) -> 연결리스트구조
	class AttrObj : public OperCls{
	public:
		DynamicStr* AtrName;
		DynamicStr* AtrVal;
		AttrObj* NxtAtr;
		AttrObj(){}
		~AttrObj(){}
	};


	//객체(MyName, 자식, 자식타입, 속성객체)	-> 연결구조는 아님 계층구조
	class XmlObj : public OperCls{
	public:
		enum class XmlType{
			OBJ,
			NUMBER,
			DOUBLE,
			BOOL,
			STRING,
			NULLTYPE,	//널 빈값을 의미
		};
		DynamicStr* MyName;
		//객체 혹은 데이터이며 객체는 여러개 데이터는 1개로 간주
		//데이터인경우 무조건 문자열이지만 자료구조로 표현하기위해서 void로 타입 구조를 맞출예정
		void* Chld;		//ChldTyp == OBJ면 Chld = XmlObj를 가리키는셈
		XmlType ChldTyp;
		AttrObj AtrObj;
	public:
		

		XmlObj(){}
		~XmlObj(){}


		void operator=(int);
		void operator=(int*);
		void operator=(double);
		void operator=(double*);
		void operator=(bool);
		void operator=(bool*);
		void operator=(char);
		void operator=(const char*);
		void operator=(char*);//변수로 들어오는 경우

	};

}