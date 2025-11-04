#pragma once

#define DEEP_COPY_STR(for_init, for_if, for_In_De, lvalue, rvalue) \
	for(for_init; for_if; for_In_De){\
		lvalue[i] = rvalue[i]; \
					}

namespace Dynamic {
	class DynamicStr {
	private:
		char* Str;
		int capacity_size;

		void Mem_Set(void* Data, char Val, size_t block_size){
			char* tmpData = static_cast<char*>(Data);
			for (size_t i = 0; i < block_size; i++){
				tmpData[i] = Val;
			}
		}

		//char* str_cat(char* dest, const char* src) {
		//	char* ptr = dest;

		//	// dest의 끝(널 문자 위치)로 이동
		//	while (*ptr != '\0') ptr++;

		//	// src를 끝까지 복사
		//	while (*src != '\0') {
		//		*ptr++ = *src++;
		//	}

		//	*ptr = '\0'; // 마지막에 널 문자 추가
		//	return dest;
		//}

		//int str_len(const char* src){
		//	for (int i = 0;; i++){
		//		if (src[i] == '\0') return i;
		//	}
		//}

		//void* mem_cpy(void* dest, const void* src, size_t n) {
		//	unsigned char* d = (unsigned char*)dest;
		//	unsigned char* s = (unsigned char*)src;

		//	for (size_t i = 0; i < n; i++) {
		//		d[i] = s[i]; // 한 바이트씩 복사
		//	}

		//	return dest;
		//}

	public:
		int current_size;	//마지막 '\0'까지의 값 ex) New Word\0 => 8
		int str_last_focus;	//마지막 문자까지의 값 ex) New Word]0 => 7
		//기본생성자로 호출하면 16비트정도만 가지게 됨
		DynamicStr() : capacity_size(16), current_size(-1), str_last_focus(-1) {
			Str = new char[capacity_size];
			Mem_Set(Str, '\0', capacity_size);
		}
		DynamicStr(int _size) : capacity_size(_size), current_size(-1), str_last_focus(-1) {
			Str = new char[capacity_size];
			Mem_Set(Str, '\0', capacity_size);
		}
		~DynamicStr() {
			if (Str != nullptr) {
				delete[] Str;
			}
		}

		//복사생성자 호출 (깊은복사)
		DynamicStr(const DynamicStr& other) : capacity_size(other.capacity_size),
			current_size(other.current_size), str_last_focus(other.str_last_focus) {
			Str = new char[capacity_size];
		}

		//이동생성자 호출 
		DynamicStr(const DynamicStr&& other) : capacity_size(other.capacity_size), current_size(other.current_size),
			str_last_focus(other.str_last_focus), Str(other.Str) {
		}

		bool StrCat(const char* Subject) {
			for (int i = 0; ; i++) {
				if (Str[i] != Subject[i]) return false;
				if (i == current_size) {
					if (Subject[i] != '\0') return false;
					return true;
				}
			}

			return true;
		}

		bool StrCmp(const char* lVal, const char* rVal){
			while (*lVal && *rVal){
				if (*lVal != *rVal){
					return false;
				}
				++lVal;
				++rVal;
			}

			return *lVal == *rVal;
		}

		char* Get_Str() {
			return Str;
		}


		char Char_Get_Str(int focus) {
			if(focus < 0 || focus >= current_size) {
				//예외처리
				return '\0';	//범위 벗어나면 Null 반환
			}
			return Str[focus];
		}

		char operator[](int focus) {
			return Str[focus];
		}

		//문자열 통으로 삽입하기
		void Set_Str(const char* new_str) {
			int i = 0;
			for (; new_str[i] != '\0'; i++) {
				if (i >= capacity_size) {
					SizeUpStr();
				}
				Str[i] = new_str[i];
				if (new_str[i + 1] == '\0') {
					if (i+1 >= capacity_size) {
						SizeUpStr();
					}
				}
			}

			Str[i] = new_str[i];	// \0삽입
			current_size = i;
			str_last_focus = i - 1;

			//FitSizeStr();
		}

		void Set_Char(const char* new_char){
			int i = 0;
			if (i >= capacity_size || (capacity_size <= 1)){
				SizeUpStr();
			}
			
			Str[i] = new_char[i++];
			Str[i] = '\0';
			current_size = i;
			str_last_focus = i - 1;
		}

		//문자 1개씩 추가
		void Append_Char(const char* new_char) {
			if (current_size+1 >= capacity_size) {
				SizeUpStr();
			}
			if (current_size == -1)
				current_size++;

			Str[current_size++] = new_char[0];
			Str[current_size] = '\0';
		}

		//문자열 추가(한글용) 안써도 될거 같은데
		/*void Append_Str(const char* new_str){
			if (!new_str) return;

			int len = strlen(new_str);

			while (current_size + len + 1 >= capacity_size){
				SizeUpStr();
			}

			mem_cpy(&Str[current_size], new_str, len);
			current_size += len;
			Str[current_size] = '\0';			
			
		}*/

		//맨앞글자를 지우기 앞으로 이동복사는 O(n) 시간복잡도 때문에 그냥 새롭게 버퍼 하나 파서 복사해줄 예정
		void Str_Trim_Front(){
			char* new_Str = new char[capacity_size];
			
			for (int idx=0; ; idx++){
				if (idx == capacity_size-1){
					new_Str[idx] = Str[idx];		//그냥 마지막은 마지막 넣어주기 '\0' 이게 있을수도 있어서 해줘야할듯
					break;
				}
				new_Str[idx] = Str[idx + 1];		//앞글자 제외하고 넣기
			}
			current_size = current_size > -1 ? (current_size-1) : -1;
			delete Str;
			Str = new_Str;
			new_Str = nullptr;
		}

		//맨뒤에 글자 지우기 이거는 그냥 앞뒤랑 복사붙여넣기 하면 될듯
		void Str_Trim_Back(){
			if (current_size >= capacity_size){
				SizeUpStr();
			}

			if (current_size <= 0){
				//지울게 없음 문자가 없으니까
				return;
			}
			current_size--;
			Str[current_size] = '\0';	//이론상 원래 '\0'일테지만 한번더 안전하게 넣어주기	
		}

		//앞뒤로 공백 \n \t 지워주기 전부
		void Str_Trim_All(){
			int fstIdx = 0;
			int lstIdx = current_size - 1;

			while ((Str[fstIdx] == ' ' || Str[fstIdx] == '\n' || Str[fstIdx] == '\t')
				|| (Str[lstIdx] == ' ' || Str[lstIdx] == '\n' || Str[lstIdx] == '\t')){
				if ((Str[fstIdx] == ' ' || Str[fstIdx] == '\n' || Str[fstIdx] == '\t')){
					//앞글자 지우기
					Str_Trim_Front();
					lstIdx = current_size - 1;
				}

				if ((Str[lstIdx] == ' ' || Str[lstIdx] == '\n' || Str[lstIdx] == '\t')){
					//뒤글자 지우기
					Str_Trim_Back();
					lstIdx = current_size - 1;
				}
			}
		}

		//앞뒤로 공백만 지워주기
		void Str_Trim(){
			int fstIdx = 0;
			int lstIdx = current_size - 1;

			while ((Str[fstIdx] == ' ')
				|| (Str[lstIdx] == ' ')){
				if ((Str[fstIdx] == ' ')){
					//앞글자 지우기
					Str_Trim_Front();
					lstIdx = current_size - 1;
				}

				if ((Str[lstIdx] == ' ')){
					//뒤글자 지우기
					Str_Trim_Back();
					lstIdx = current_size - 1;
				}
			}
		}

	private:
		//<문자열 처리 로직에 대한 API>

		//문자열 크기 증가 로직
		void SizeUpStr() {
			int old_capacity = capacity_size;
			capacity_size = (capacity_size / 2) > 2 ? (capacity_size / 2) + capacity_size : capacity_size + 2;
			char* new_size_str = new char[capacity_size + 1];		//Null포함위한 +1

			//Deep Copy (new_size_str <- Str)
			DEEP_COPY_STR(int i = 0, i < old_capacity, i++, new_size_str, Str);
			delete Str;

			Str = new_size_str;
		}

		//문자열 빈공간 제거 거의 사용하지 말것 오버헤드 발생
		void FitSizeStr() {
			int null_current_size = current_size + 1;			//Null 포함해서 넣어줘야함 +1
			char* new_size_str = new char[null_current_size];
			DEEP_COPY_STR(int i = 0, i < null_current_size, i++, new_size_str, Str);
			capacity_size = null_current_size;
			delete Str;
			Str = new_size_str;
		}
	};

}


