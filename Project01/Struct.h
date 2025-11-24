#pragma once

// 사용자 정보 구조체
typedef struct
{
    char name[20]; // 사용자 이름
    char phone[20]; // 전화번호
    char password[20]; // 비밀번호
    char Mstate; // 상태(N : 정상, D : 삭제)
} Member;

// 도서 정보 구조체
typedef struct
{
    char id[10]; // 도서 ID
    char bookTitle[50]; // 도서 제목
    char bookAuthor[30]; // 도서 저자
    char bookPublish[20]; // 출판사
    int total; // 초기 수량
    int available; // 잔여 수량
    char Bstate; // 상태(N : 정상, D : 삭제)

} Book;

// 대출 정보 구조체
typedef struct
{
    char id[10]; // 도서 ID
    char borrowerPhone[20]; // 대출자 전화번호
    int borrowYear; // 대출 연도
    int borrowMonth; // 대출 월
    int borrowDay; // 대출 일
    int returnYear; // 반납 연도
    int returnMonth; // 반납 월
    int returnDay; // 반납 일
    int state; // 대출 상태(1 : 대출중, 2 : 정상 반납, 3 : 연체 반납)
} Borrow;

/*
    전역 변수
*/
extern Member members[1000];
extern Book books[1000];
extern char currentUser[20]; // 현재 로그인한 사용자 이름 저장용
extern char currentPhone[20]; // 현재 로그인한 사용자 전화번호 저장용
extern int year, month, day;

/*
    함수 선언부
*/
void gotoxy(int x, int y); // 콘솔 커서 이동 함수 (xy 좌표)
void setColor(int color); // 콘솔 글자 색상 변경 함수
int manageMemberFile(Member members[], Member newMember, int mode, int memberCount); // member.txt 파일 읽거나 추가 함수
int manageBookFile(Book books[], Book newBook, int mode, int bookCount); // book.txt 파일 읽거나 추가 함수
int manageBorrowFile(Borrow borrowList[], Borrow newBorrow, int mode, int borrowCount); // borrowList.txt 파일 읽거나 추가 함수
void drawBox(int x, int y, int w, int h, char text[]); // 사각형 박스 그리기 함수
void drawMainMenu(); // 초기 메인 메뉴 UI 출력 함수
void getDate(int offset); // 날짜 계산 함수
int isBeforeDate(int y1, int m1, int d1, int y2, int m2, int d2); // 날짜 비교 함수

int mainLogin(); // 메인 화면 (맨처음 화면)
int selectLogin(); // 로그인 선택 (사용자? 관리자?)
int userMenu(); // 로그인 후 "사용자" 메인 메뉴 함수
int adminMenu(); // 로그인 후 "관리자" 메인 메뉴 함수

int login(); // 로그인 기능 함수
int adminlogin(); // 관리자 로그인 기능 함수
void signUp(); // 회원가입 기능 함수

/*
    사용자 주요 기능
*/
void handleBorrowSearch(); // 도서 대출 (검색 후 대출)
void handleReturn(); // 도서 반납
void viewBorrowHistory(); // 대출 내역
void userFix(); // 회원 수정 함수
void u_removeUser(); // 회원 탈퇴(사용자)

/*
    관리자 주요 기능
*/
int compareBorrowRecords(const void* a, const void* b); // 비교 함수 (대출 기록 배열 borrowList 정렬)
void addBook(); // 도서 등록
void removeBook(); // 도서 삭제
void viewBorrowRecords(); // 대출/연체 내역 조회
void m_removeUser(); // 회원 삭제(관리자)