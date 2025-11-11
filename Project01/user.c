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