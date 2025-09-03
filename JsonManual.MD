# C++ JSON 라이브러리

## 1. 개요
이 라이브러리는 C++에서 JSON 데이터를 **간단하고 안전하게** 다루기 위해 설계되었습니다.  
Visual Studio 2013과 2022 모두 호환되며, JSON의 파싱, 생성, 수정, 직렬화를 직관적인 인터페이스로 제공합니다.

**특징**
- 직관적인 문법 (`[]` 연산자 접근, `push_back` 지원)
- 안전한 타입 변환 (잘못된 변환 시 덮어쓰기 진행)
- 경량 설계 (추가 의존성 없음 단순 타입들을 통한 구조로 개발)
- C++14 이상 호환

**지원 환경**
- C++14 이상
- Windows / Linux
- Visual Studio 2013, 2022 테스트 완료

---

## 2. 사용 방법

### 2.1 설치
1. 소스 코드 다운로드
2. 프로젝트에 `JNode.h`와 `JNode.cpp` 포함
3. C++14 이상 컴파일 옵션 활성화

### 2.2 기본 사용 예시(생성 및 단일 타입)
##### 2.2.1 기본 생성
```cpp
JNode data;    // 비어 있는 JSON 인스턴스 생성
JNode* pdata = new JNode();  // 비어 있는 JSON 포인터 인스턴스 생성
JNode data(JNode::JType::NUMBER);       //단일 정수형 JSON 인스턴스 생성
JNode data(JNode::JType::DOUBLE);       //단일 실수형 JSON 인스턴스 생성
JNode data(JNode::JType::BOOL);         //단일 논리형 JSON 인스턴스 생성
JNode data(JNode::JType::STRING);       //단일 문자형 JSON 인스턴스 생성
JNode data(JNode::JType::NULLTYPE);     //단일 기본타입 JSON 인스턴스 생성
```
##### 2.2.2 타입 직접 지정
```cpp
JNode data;     //비어 있는 JSON 인스턴스 생성
data = JNode::JType::NUMBER;        //단일 정수형 타입 대입 기본값 - 0
data = JNode::JType::DOUBLE;        //단일 실수형 타입 대입 기본값 - 0.0
data = JNode::JType::BOOL;          //단일 논리형 타입 대입 기본값 - false
data = JNode::JType::STRING;        //단일 문자형 타입 대입 기본값 - '\0'
```
##### 2.2.3 단일 값 대입
```cpp
JNode data;     //기본타입 NULL 생성
data = 10;      //정수형으로 덮어씌워짐
data = 1.0;     //실수형으로 덮어씌워짐
data = true;    //논리형으로 덮어씌워짐
data = 'T';     //Json은 보통 문자열을 지원안하지만 'T' -> "T"식으로 단일 문자열 타입으로 덮어씌워짐
data = "Test";  //문자열 리터럴을 단일 문자열 타입으로 덮어씌움
data = rValue;  //변수를 통한 대입도 가능

//포인터를 사용하는 경우의 대입
int num = 10;
int* pnum = &num;

data = pnum;        //pnum이 참조한 &num의 값을 깊은복사하여 덮어씌워짐
data = *pnum;       //data = 10과 동일한 결과를 산출하여 10이 덮어씌워짐
```
##### 2.2.4 단일 값 반환
```cpp
JNode data;         //기본타입 NULL 생성
int num = data;     //data가 기본타입이라 num = -1; 로 실패 반환
data = 10;          //단일 정수형 으로 덮어씌워짐
int num = data;     //num = 10; 으로 반환성공

//포인터를 사용하는 경우의 반환
data = 10;
int* pnum = data;       //이런 경우 pnum이 가리키는 참조는 data의 내부 리소스 10을 가리키게 된다.
                        // 내부 리소스를 참조하는 포인터이므로, 
                        // 임의로 delete 하면 안 됨. 읽기 전용으로 활용 권장.
```
##### 2.2.5 JNode 간 대입
```cpp
JNode lValue;
JNode rValue;
lValue = 10;
rValue = 20;
lValue = rValue;        //변수 rValue를 대입하는 것은 컴파일 에러 또는 막혀 있음 (이중 소멸 방지)
lValue = &rValue;       //이런경우 rValue의 모든 정보가 lValue로 덮어씌워지게 되며
                        //rValue는 NULLTYPE이 된다. 빈 인스턴스가 된다.
```

### 2.3 기본 사용 예시(객체 타입)
##### 2.3.1 객체 생성
```cpp
JNode data(JNode::JType::OBJ);
JNode data;
data = JNode::JType::OBJ;
//이런식으로 만들어진 객체는 {} 이런 형태로 존재
```
##### 2.3.2 단일 값 덮어쓰기
```cpp
data = 10;                  //객체 타입에서 단일 값으로 덮어쓰기 가능 OBJ->NUMBER 타입 덮어쓰기
data = JNode::JType::OBJ;   //NUMBER->OBJ 타입 덮어쓰기
```

##### 2.3.3 키-값 접근 및 자동 생성
```cpp
data = 10;
data["Key0"];                           //NUMBER -> OBJ 타입으로 덮어쓰기 및 키생성 내부생김새 {"Key0" : null} 이런 구조
data["Key0"] = 10;                      //{"Key0" : 10}
data["Key0"] = true;                    //{"Key0" : true}
data["Key1"] = "Test";                  //{"Key0" : true, "Key1" : "Test"}
data["Key2"] = JNode::JType::OBJ;       //{"Key0" : true, "Key1" : "Test", "Key2" : {}}
//data["Key3"] = JNode::JType::ARR;       //{"Key0" : true, "Key1" : "Test", "Key2" : {}, "Key3" : []} 참고로 이것도 가능
JNode* key2 = data["Key2"];
key2["key2_0"] = 10;                    //{"Key0" : true, "Key1" : "Test", "Key2" : {"key2_0" : 10}}
key2 = data["Key1"];
key2["TestKey"] = true;                 //{"Key0" : true, "Key1" : {"TestKey" : true}, "Key2" : {"key2_0" : 10}}
```

##### 2.3.4 키-값 삭제
```cpp
data.obj_del("Key0");                   //특정 키-값 삭제 {"Key1" : {"TestKey" : true}, "Key2" : {"key2_0" : 10}}
data.obj_del();                         //맨뒤 키-값 삭제 {"Key1" : {"TestKey" : true}}
data.del();                             //맨뒤 키-값 삭제 {}
data.all_del();                         //전체 삭제
```

##### 2.3.5 키-값 읽기 및 단일 타입 지원
```cpp
data["Key0"] = 10;
int num = data["Key0"];             //int num = 10;
double dnum = data["Key0"];         //double dnum = 타입불일치 실패 -1.0;
double dnum = data["Key1"];         //double dnum = Key1 없음 실패 -1.0;
```

##### 2.3.6 주의사항 및 내부 구조
```cpp
JNode* key_obj = data["Key0"];      //이런 행위를 통해서 Key0의 Value에 접근이 가능합니다.
                                    //이런식으로 접근할때 주의할점은 delete key_obj를 하면 이중 delete 소멸이 일어납니다.
                                    //반드시 참조용도로만 사용하도록 주의해주세요
```


### 2.4 기본 사용 예시(배열 타입)
##### 2.3.1 배열 생성
```cpp
JNode data(JNode::JType::ARR);
JNode data;
data = JNode::JType::ARR;
//이런식으로 만들어진 객체는 [] 이런 형태로 존재
```

##### 2.3.2 단일 값 덮어쓰기
```cpp
data = 10;                      //배열 타입에서 단일값으로 덮어쓰기 가능 ARR->NUMBER타입 덮어씌워짐
data = JNode::JType::ARR;       //NUMBER->ARR로 타입 덮어쓰기
```

##### 2.3.3 인덱스 접근 및 자동 생성
```cpp
data = 10;
data[0];                                //NUMBER->ARR 타입으로 덮어쓰기 및 인덱스 생성 내부생김새 [null] 이런 구조
data[0] = true;                         //[true]
data[1] = "Test";                       //[true, "Test"]
data[2] = JNode::JType::ARR;            //[true, "Test", []]
data[3] = JNode::JType::OBJ;            //[true, "Test", [], {}]
JNode* arr_2 = data[2];                 
arr_2[0] = 10;                          //[true, "Test", [10], {}]
arr_2 = data[1];
arr_2[1] = true;                        //[true, true, [10], {}]
arr_2.push() = "JustPush";                 //[true, true, [10], {}, "JustPush"]
```

##### 2.3.4 인덱스 삭제
```cpp
data.arr_del(2);                        //[true, true,{}, "JustPush"]       특정인덱스 삭제
data.arr_del();                         //[true, true, "JustPush"]          맨뒤삭제
data.del();                             //[true, true]                      맨뒤삭제
data.all_del();                         //[]                                전체삭제
```

##### 2.3.5 인덱스 읽기 및 단일 타입 지원
```cpp
JNode* arr = data[0];       //이런 행위를 통해서 인덱스의 Value에 접근이 가능합니다.
                            //이런식으로 접근할때 주의할점은 delete arr을 하면 이중 delete소멸이 일어납니다.
                            //반드시 참조용으로만 사용하도록 주의해주세요
```


---



## 3. 사용 규칙

### 3.1 클래스 구조
라이브러리는 총 3개의 핵심 클래스와 그 하위 리소스로 구성됩니다.

#### JNode
- **리소스**
  - `enum type` : 현재 JNode가 어떤 데이터 타입을 보유하는지 나타냄
  - `void* resource` : 실제 데이터에 대한 포인터
- **역할**
  - JSON의 모든 데이터 타입을 표현하는 핵심 클래스
  - 타입에 따라 `resource`가 다른 객체(JObj, JArr 또는 단일 값)를 가리킴

#### JObj
- **리소스**
  - `char* key` : 객체의 키
  - `JNode* value` : 값
  - `JObj* next` : 다음 객체를 가리키는 연결 리스트 형태
- **역할**
  - JSON 객체(Object) 구조 표현

#### JArr
- **리소스**
  - `JNode* value` : 배열 원소
  - `JArr* next` : 다음 원소를 가리키는 연결 리스트 형태
- **역할**
  - JSON 배열(Array) 구조 표현

---

### 3.2 단일 타입 사용 규칙

#### 1) 기본 생성
```cpp
JNode* data; // 비어 있는 JSON 인스턴스 생성
