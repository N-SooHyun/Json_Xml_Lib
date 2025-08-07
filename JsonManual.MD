# JSON 설명서

## 개요

이 문서는 `Json_Xml Library`에서 JSON 관련 기능에 대해 설명합니다.

## 주요 기능

- JSON 문자열 파싱
- JSON 객체 생성 및 수정
- 직렬화 (Serialize) 및 역직렬화 (Deserialize)
- 키-값 탐색, 삭제, 추가 기능

## 사용 예시

```c
const char* jsonStr = "{\"name\": \"OpenAI\", \"type\": \"AI\"}";
JsonObject* obj = json_parse(jsonStr);
const char* name = json_get_string(obj, "name");
printf("Name: %s\n", name);
json_free(obj);
