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
    int borrowCount = manageBorrowFile(list, null, 0, 0); // 전체 대출 목록 불러오기

    getDate(0); // 오늘 날짜 (year, month, day)

    for (int i = 0; i < borrowCount; i++)
    {
        if (list[i].state == 1) // 대출 중이면
        {
            // 반납 예정일이 오늘 날짜보다 앞서는 경우에 연체로(state를 2로) 변경하는 조건문
            if (list[i].returnYear < year
                || (list[i].returnYear == year && list[i].returnMonth < month)
                || (list[i].returnYear == year && list[i].returnMonth == month && list[i].returnDay < day))
            {
                list[i].state = 2; // 연체로 변경
            }
        }
    }
    manageBorrowFile(list, null, 2, borrowCount); // 파일 덮어쓰기 저장

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