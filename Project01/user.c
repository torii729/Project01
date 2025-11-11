#include "Enum.h"
#include "Header.h"
#include "Struct.h"

/*
    로그인 기능
*/
int login()
{
    char name[20], phone[20], password[20];
    Member null = { 0 };
    int count = manageMemberFile(members, null, 0);

    if (count == 0)
    {
        return 0;
    }

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "로그인");

    gotoxy(44, 7); printf("이름        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(44, 11); printf("전화번호    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(44, 15); printf("비밀번호    : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    int check = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(name, members[i].name) == 0 &&
            strcmp(phone, members[i].phone) == 0 &&
            strcmp(password, members[i].password) == 0)
        {
            check = 1;
            break;
        }
    }

    if (check)
    {
        strcpy(currentUser, name);
        strcpy(currentPhone, phone);
        return 1;
    }
    else
    {
        gotoxy(39, 22);
        setColor(RED);
        printf("정보가 일치하지 않습니다.\n");
        setColor(WHITE);
        gotoxy(39, 23); system("pause");
        return 0;
    }
}

/*
    도서 검색 기능
*/
void searchBook()
{
    Book null = { 0 };
    int count = manageBookFile(books, null, 0, 0); // 도서 정보 불러오기
    char word[50];

    while (1)
    {
        // ui 시작
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(DarkYellow); drawBox(16, 7, 11, 3, "");
        setColor(RED); drawBox(16, 10, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(31, 3, 34, 3, "도서 검색"); // 전체 메인 박스

        gotoxy(27, 7); printf(" 번호│ 제목           │ 저자         ");
        gotoxy(26, 8); printf("├────────────────────────────────────────┤");

        // 검색
        gotoxy(72, 11); printf("검색할 도서 제목 또는 저자");
        gotoxy(72, 12); printf("(뒤로 가기 : 0) : ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = 0; // 엔터 제거함

        if (strcmp(word, "0") == 0)
        {
            break; // ㄴㄴ
        }

        int check = 0;
        int b = 10;
        int c = 9;

        for (int i = 0; i < count; i++)
        {
            if (strstr(books[i].bookTitle, word) || strstr(books[i].bookAuthor, word))
            {
                check++;

                setColor(GREEN);
                gotoxy(28, c); printf(" %-2s │ %-14s │ %-10s\n", books[i].id,
                    books[i].bookTitle, books[i].bookAuthor);
                gotoxy(72, 14); printf("검색 완료");
                setColor(WHITE);

                b += 2;
                c += 2;
            }
        }

        if (check == 0)
        {
            setColor(RED);
            gotoxy(72, 23); printf("해당 키워드와 일치하는 도서를 찾을 수 없습니다.\n");
            setColor(WHITE);
        }
        gotoxy(72, 24); printf("아무 키나 누르면 다시 검색합니다.");
        _getch();
    }
}