#include "Enum.h"
#include "Header.h"
#include "Struct.h"

#define ADMIN_ID "admin"
#define ADMIN_PW "password!"

int adminlogin()
{
    char name[20], phone[20], password[20];

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "로그인");

    gotoxy(44, 7); printf("아이디        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(44, 10); printf("비밀번호      : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    int check = 0;

    if (strcmp(name, ADMIN_ID) == 0 && strcmp(password, ADMIN_PW) == 0)
    {
        strcpy(currentUser, name);
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