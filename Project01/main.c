#include "Enum.h"
#include "Header.h"
#include "Struct.h"

/*
    전역 변수(원본과 동일)
*/
Member members[1000];
Book books[1000];
char currentUser[20]; // 현재 로그인한 사용자 이름 저장용
char currentPhone[20]; // 현재 로그인한 사용자 전화번호 저장용

/*
    메인 함수
*/
int main()
{
    mainLogin();
    return 0;
}