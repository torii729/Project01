#include "Enum.h"
#include "Header.h"
#include "Struct.h"

/*
    콘솔 커서 위치 이동 함수
*/
void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
    콘솔 글자 색상 변경 함수
*/
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*
    사각형 박스를 출력하는 함수
*/
void drawBox(int x, int y, int width, int height, char text[])
{
    // 상단
    gotoxy(x, y); printf("┌");
    for (int i = 0; i < width - 2; i++)
    {
        printf("─");
    }
    printf("┐");

    // 중간
    for (int i = 1; i < height - 1; i++)
    {
        gotoxy(x, y + i); printf("│");
        for (int j = 0; j < width - 2; j++)
        {
            printf(" ");
        }
        printf("│");
    }

    // 하단
    gotoxy(x, y + height - 1); printf("└");
    for (int i = 0; i < width - 2; i++)
    {
        printf("─");
    }
    printf("┘");

    // 텍스트 출력 (중앙 정렬)
    if (text != NULL)
    {
        int textX = x + (width - (int)strlen(text)) / 2;
        int textY = y + 1;
        gotoxy(textX, textY);
        printf("%s", text);
    }
}

/*
    메인 화면 UI 출력
*/
void drawMainMenu()
{
    system("cls");
    setColor(WHITE);

    setColor(DarkGreen); drawBox(77, 1, 11, 3, "1| 로그인");
    setColor(darkSkyBlue); drawBox(77, 4, 11, 3, "2| 가입  ");
    setColor(DarkYellow); drawBox(77, 7, 11, 3, "3| 수정  ");
    setColor(RED); drawBox(77, 10, 11, 3, "4| 종료  ");

    setColor(WHITE);
    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "도서관 대출 프로그램"); // 전체 메인 박스
}

/*
    메인 화면 (맨처음 화면)
*/
int mainLogin()
{
    char input[10];

    while (1)  // 무한 반복 (예시 : 회원가입 완료하고 여기로 다시 돌아와야 함, 반복하지 않으면 회원가입 완료 시 프로그램이 종료됨)
    {
        drawMainMenu(); // 메인 화면 출력
        gotoxy(42, 21); printf("──────────────────────────────");

        gotoxy(43, 20);
        printf("우측 번호를 입력하세요 : ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '1')
        {
            selectLogin();
        }
        else if (input[0] == '2')
        {
            // signUp();
        }
        else if (input[0] == '3')
        {
            // signFix();
        }
        else if (input[0] == '4')
        {
            return 0;
        }
        else
        {
            gotoxy(39, 22);
            setColor(RED);
            printf("잘못된 입력입니다. 다시 입력해주세요.");
            setColor(WHITE);
            gotoxy(39, 23); system("pause");
        }
    }
    return 0;
}

/*
    로그인 선택 화면
*/
int selectLogin()
{
    char input[10];

    drawMainMenu(); // 메인 화면 출력

    drawBox(40, 3, 34, 3, " 로그인 선택");
    drawBox(49, 7, 16, 3, " 1. 사용자"); // 사용자 로그인
    drawBox(49, 11, 16, 3, " 2. 관리자"); // 관리자 로그인

    setColor(RED);
    drawBox(49, 15, 16, 3, " 3. 뒤로 가기"); // 메인 화면으로 돌아가기
    setColor(WHITE);

    gotoxy(42, 21); printf("──────────────────────────────");
    gotoxy(43, 20);
    printf("중앙 번호를 입력하세요 : ");
    fgets(input, sizeof(input), stdin);

    if (input[0] == '1')
    {
        if (login())  // 로그인
        {
            userMenu(); // 로그인 성공 시 사용자 메뉴로 이동
            return 1;
        }
    }
    else if (input[0] == '2')
    {
        if (adminlogin())  // 로그인
        {
            adminMenu();
            return 1;
        }
    }
    else if (input[0] == '3')
    {
        return 1;
    }
    else
    {
        gotoxy(39, 22);
        setColor(RED);
        printf("잘못된 입력입니다. 다시 입력해주세요.");
        setColor(WHITE);
        gotoxy(39, 23); system("pause");
    }
    return 0;
}

/*
    로그인 후 사용자 메뉴 화면
*/
int userMenu()
{
    char welcome[60];
    char input[10];

    while (1)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(DarkYellow); drawBox(16, 7, 11, 3, "");
        setColor(RED); drawBox(16, 10, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(31, 3, 34, 3, "차례"); // 전체 메인 박스

        sprintf(welcome, "   %s 님, 환영합니다!", currentUser); // sprintf -> welcome 배열에 " currentUser님 환영합니다!" 문자열 저장하는 것
        setColor(GREEN);
        gotoxy(35, 6); printf("%s", welcome);
        setColor(WHITE);

        gotoxy(32, 11); printf("I. 사용자");
        gotoxy(31, 12); printf("──────────────────────────────────");

        gotoxy(42, 14); printf("1. 도서 대출");
        gotoxy(42, 15); printf("2. 도서 반납");
        gotoxy(42, 16); printf("3. 도서 목록");
        gotoxy(42, 17); printf("4. 도서 검색");
        gotoxy(42, 18); printf("5. 대출 내역");

        setColor(RED);  gotoxy(42, 20); printf("6. 로그아웃");

        setColor(WHITE);  gotoxy(73, 20); printf("──────────────────────────────");
        gotoxy(31, 22); printf("──────────────────────────────────");
        gotoxy(74, 19); printf("좌측 번호를 입력하세요 : ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '1')
        {
            // handleBorrow();
        }
        else if (input[0] == '2')
        {
            // handleReturn();
        }
        else if (input[0] == '3')
        {
            // showBookList();
        }
        else if (input[0] == '4')
        {
            // searchBook();
        }
        else if (input[0] == '5')
        {
            // viewBorrowHistory();
        }
        else if (input[0] == '6')
        {
            return 0;
        }
        else
        {
            gotoxy(43, 22); setColor(12);
            printf("잘못된 입력입니다. 다시 입력해주세요.");
            setColor(7);
            gotoxy(43, 20); system("pause");
        }
    }
}

/*
    로그인 후 관리자 메뉴 화면
*/
int adminMenu()
{
    char welcome[60];
    char input[10];

    while (1)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(DarkYellow); drawBox(16, 7, 11, 3, "");
        setColor(RED); drawBox(16, 10, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(31, 3, 34, 3, "차례"); // 전체 메인 박스

        sprintf(welcome, "   %s 님, 환영합니다.", currentUser); // sprintf -> welcome 배열에 " currentUser님 환영합니다!" 문자열 저장하는 것
        setColor(GREEN);
        gotoxy(35, 6); printf("%s", welcome);
        setColor(WHITE);

        gotoxy(32, 11); printf("II. 관리자");
        gotoxy(31, 12); printf("──────────────────────────────────");

        gotoxy(42, 14); printf("1. 도서 등록");
        gotoxy(42, 15); printf("2. 도서 삭제");
        gotoxy(42, 16); printf("3. 대출 현황");
        gotoxy(42, 17); printf("4. 회원 관리");

        setColor(RED);  gotoxy(42, 19); printf("5. 로그아웃");

        setColor(WHITE);  gotoxy(73, 20); printf("──────────────────────────────");
        gotoxy(31, 22); printf("──────────────────────────────────");
        gotoxy(74, 19); printf("좌측 번호를 입력하세요 : ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '1')
        {
            // addBook();
        }
        else if (input[0] == '2')
        {
            // removeBook();
        }
        else if (input[0] == '3')
        {
            // viewBorrowRecords();
        }
        else if (input[0] == '4')
        {
            // userFix();
        }
        else if (input[0] == '5')
        {
            return 0;
        }
        else
        {
            gotoxy(43, 22); setColor(WHITE);
            printf("잘못된 입력입니다. 다시 입력해주세요.");
            setColor(RED);
            gotoxy(43, 20); system("pause");
        }
    }
}
