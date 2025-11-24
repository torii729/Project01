#include "Header.h"

/*
    전역 변수
    프로그램 어디서든 쓰려고 미리 만든 큰 상자
    회원, 책, 대출 정보 저장 공간
*/
Member members[1000]; // 회원 정보를 최대 1000명까지 저장하는 배열
Book books[1000]; // 책 정보를 최대 1000권까지 저장하는 배열
char currentUser[20]; // 지금 로그인한 사람 이름을 잠깐 기억하는 공간
char currentPhone[20]; // 지금 로그인한 사람 전화번호를 잠깐 기억하는 공간
int year, month, day; // 오늘 날짜를 숫자로 저장하는 변수

/*
    메인 함수
    프로그램 시작하면 제일 먼저 실행되는 곳
*/
int main()
{
    Borrow list[1000] = { 0 }; // 대출 기록을 담는 배열, 처음은 전부 비어 있는 상태
    Borrow null = { 0 }; // 빈 대출 정보, 파일 처리 함수에 넘길 때 쓰는 값
    int borrowCount = manageBorrowFile(list, null, 0, 0); // 대출 파일을 읽어 list에 넣고 개수 받아오기

    getDate(0); // 오늘 날짜 구해서 year, month, day에 저장, 0이면 오늘 그대로

    // 연체 여부는 목록 출력이나 반납 처리할 때 날짜 비교로만 판단
    // 여기서는 연체를 미리 계산하지 않고 필요할 때만 날짜를 비교

    mainLogin(); // 로그인 화면 실행, 로그인 후 메뉴로 이동
    return 0; // 프로그램 정상 종료
}

/*
    날짜 계산
    컴퓨터의 현재 날짜를 가져와 year, month, day에 저장
    offset으로 날짜를 앞뒤로 이동 가능, 1은 내일, -1은 어제
*/
void getDate(int offset)
{
    time_t now = time(NULL); // 지금 시간을 컴퓨터에서 가져오기
    struct tm date = *localtime(&now); // 지금 시간을 연, 월, 일로 바꾼 값

    date.tm_mday += offset; // 일에 offset만큼 더하거나 빼기
    mktime(&date); // 날짜가 32일 같은 이상한 값이 되면 자동으로 맞추기

    year = date.tm_year + 1900; // 1900년 기준으로 저장된 값을 실제 연도로 바꾸기
    month = date.tm_mon + 1; // 0부터 시작하는 달 값을 실제 달로 바꾸기
    day = date.tm_mday; // 오늘의 일 저장
}
