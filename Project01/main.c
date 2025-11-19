#include "Header.h"

/*
    전역 변수
*/
Member members[1000];
Book books[1000];
char currentUser[20]; // 현재 로그인한 사용자 이름 저장용
char currentPhone[20]; // 현재 로그인한 사용자 전화번호 저장용
int year, month, day;

/*
    메인 함수
*/
int main()
{
    Borrow list[1000] = { 0 };
    Borrow null = { 0 };
    int borrowCount = manageBorrowFile(list, null, 0, 0);

    getDate(0);

    // 연체 여부는 목록 출력이나 반납 처리할 때 날짜 비교로만 판단

    mainLogin();
    return 0;
}


/*
    날짜 계산
*/
void getDate(int offset)
{
    time_t now = time(NULL);
    struct tm date = *localtime(&now);

    date.tm_mday += offset;
    mktime(&date);

    year = date.tm_year + 1900;
    month = date.tm_mon + 1;
    day = date.tm_mday;
}