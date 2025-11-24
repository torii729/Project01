#include "Header.h"

#define LEFT 75
#define RIGHT 77

/*
    날짜 비교 함수
*/
int isBeforeDate(int y1, int m1, int d1, int y2, int m2, int d2)
{
    if (y1 != y2)
    {
        return y1 < y2;
    }
    if (m1 != m2)
    {
        return m1 < m2;
    }
    return d1 < d2;
}

/*
    로그인 기능
*/
int login()
{
    char name[20], phone[20], password[20];
    Member nullMember = { 0 };
    int count = manageMemberFile(members, nullMember, 0, 0);

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

    int idx = 0;
    char k;

    while (1)
    {
        k = _getch();

        if (k == 13) // 엔터치면 입력 완료
        {
            password[idx] = '\0'; // 어디까지가 문자열인지 배열에 엔터를 직접 넣음으로써 판단할 수 있게 한다.
            break;
        }
        else if (k == 8) // 백스페이스 누르면 지워져야 하는데...
        {
            printf("\b \b");
        }
        else if (k >= 33 && k <= 126) // !부터 ~까지인데 뭔지모르겟으면 톡방 사진 참고
        {
            // 입력한 문자를 저장하나, 실제로 출력되는 건 *임
            password[idx++] = k;
            printf("*");
        }
    }

    int check = 0;

    for (int i = 0; i < count; i++)
    {
        if (members[i].Mstate == 'N')
        {
            if (strcmp(name, members[i].name) == 0 &&
                strcmp(phone, members[i].phone) == 0 &&
                strcmp(password, members[i].password) == 0)
            {
                check = 1;
                break;
            }
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
        printf("정보가 일치하지 않습니다.");
        setColor(WHITE);
        gotoxy(39, 23);
        system("pause");
        return 0;
    }
}

/*
    회원가입 기능
*/
void signUp()
{
    Member newMember = { 0 };
    Member nullMember = { 0 };
    int count = manageMemberFile(members, nullMember, 0, 0);

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "회원가입");

    while (1)
    {
        gotoxy(44, 7); printf("이름        : ");
        fgets(newMember.name, sizeof(newMember.name), stdin);
        newMember.name[strcspn(newMember.name, "\n")] = 0;

        int empty = 1;
        for (int i = 0; newMember.name[i] != '\0'; i++)
        {
            if (newMember.name[i] != ' ' && newMember.name[i] != '\t')
            {
                empty = 0;
                break;
            }
        }

        if (empty)
        {
            setColor(RED);
            gotoxy(39, 19); printf("이름은 공백일 수 없습니다.");
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");
            gotoxy(39, 19); printf("                                ");
            gotoxy(39, 20); printf("                                ");
            continue;
        }
        break;
    }

    while (1)
    {
        int dup = 0;

        gotoxy(44, 11); printf("전화번호    : ");
        fgets(newMember.phone, sizeof(newMember.phone), stdin);
        newMember.phone[strcspn(newMember.phone, "\n")] = 0;

        int len = 0;
        int lastDash = 0;
        int format = 1;

        for (; newMember.phone[len] != '\0'; len++)
        {
            char ch = newMember.phone[len];
            if (!((ch >= '0' && ch <= '9') || ch == '-'))
            {
                format = 0;
                break;
            }
            if (ch == '-')
            {
                if (lastDash)
                {
                    format = 0;
                    break;
                }
                lastDash = 1;
            }
            else
            {
                lastDash = 0;
            }
        }

        if (len == 0 || newMember.phone[0] == '-' || newMember.phone[len - 1] == '-')
        {
            format = 0;
        }

        if (!format)
        {
            setColor(RED);
            gotoxy(39, 19); printf("전화번호 형식이 올바르지 않습니다.");
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");
            gotoxy(54, 11); printf("                  ");
            gotoxy(39, 19); printf("                                       ");
            gotoxy(39, 20); printf("                                       ");
            continue;
        }

        for (int i = 0; i < count; i++)
        {
            if (members[i].Mstate == 'N')
            {
                if (strcmp(newMember.phone, members[i].phone) == 0)
                {
                    dup = 1;
                    gotoxy(39, 19);
                    setColor(RED); printf("이미 등록된 전화번호입니다.");
                    setColor(WHITE);
                    gotoxy(39, 20);
                    system("pause");
                    gotoxy(54, 11); printf("                  ");
                    gotoxy(39, 19); printf("                                      ");
                    gotoxy(39, 20); printf("                                      ");
                    break;
                }
            }
        }

        if (!dup)
        {
            break;
        }
    }

    while (1)
    {
        gotoxy(44, 15); printf("비밀번호    : ");
        fgets(newMember.password, sizeof(newMember.password), stdin);
        newMember.password[strcspn(newMember.password, "\n")] = 0;

        int hasSpace = 0;
        for (int i = 0; newMember.password[i] != '\0'; i++)
        {
            if (newMember.password[i] == ' ' || newMember.password[i] == '\t')
            {
                hasSpace = 1;
                break;
            }
        }

        if (hasSpace)
        {
            setColor(RED);
            gotoxy(39, 19); printf("비밀번호에 공백을 포함할 수 없습니다.");
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");
            gotoxy(54, 15); printf("                  ");
            gotoxy(39, 19); printf("                                ");
            gotoxy(39, 20); printf("                                ");
            continue;
        }
        break;
    }

    newMember.Mstate = 'N';

    int check = manageMemberFile(NULL, newMember, 1, 0);

    if (check == 1)
    {
        setColor(GREEN);
        gotoxy(39, 19); printf("회원가입 완료");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
    }
}

/*
    회원 수정 기능
*/
void userFix()
{
    Member nullMember = { 0 };
    int count = manageMemberFile(members, nullMember, 0, 0);

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "회원 수정");

    if (count == 0)
    {
        setColor(RED);
        gotoxy(39, 19); printf("회원 데이터가 없습니다.");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
        return;
    }

    int idx = -1;
    for (int i = 0; i < count; i++)
    {
        if (members[i].Mstate == 'N')
        {
            if (strcmp(members[i].phone, currentPhone) == 0)
            {
                idx = i;
                break;
            }
        }
    }

    if (idx == -1)
    {
        setColor(RED);
        gotoxy(39, 19); printf("현재 로그인된 회원을 찾을 수 없습니다.");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
        gotoxy(39, 19); printf("                                ");
        gotoxy(39, 20); printf("                                ");
        return;
    }

    char oldPhone[20] = { 0 };
    strcpy(oldPhone, members[idx].phone);

    char newName[20] = { 0 };
    char newPhone[20] = { 0 };
    char newPw[20] = { 0 };

    int changed = 0;

    gotoxy(44, 7);  printf("현재 이름      : %s", members[idx].name);
    gotoxy(44, 9);  printf("현재 전화번호  : %s", members[idx].phone);
    gotoxy(44, 11); printf("현재 비밀번호  : %s", members[idx].password);

    while (1)
    {
        gotoxy(44, 16); printf("새 이름 : ");
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = 0;

        if (strlen(newName) == 0)
        {
            break;
        }

        int empty = 1;
        for (int i = 0; newName[i] != '\0'; i++)
        {
            if (newName[i] != ' ' && newName[i] != '\t')
            {
                empty = 0;
                break;
            }
        }

        if (empty)
        {
            setColor(RED);
            gotoxy(39, 19); printf("이름은 공백일 수 없습니다.");
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");
            gotoxy(39, 19); printf("                                    ");
            gotoxy(39, 20); printf("                                    ");

            continue;
        }

        if (strcmp(members[idx].name, newName) != 0)
        {
            strcpy(members[idx].name, newName);
            strcpy(currentUser, newName);
            changed = 1;
        }
        break;
    }

    while (1)
    {
        int dup = 0;

        gotoxy(44, 18); printf("새 전화번호 : ");
        fgets(newPhone, sizeof(newPhone), stdin);
        newPhone[strcspn(newPhone, "\n")] = 0;

        if (strlen(newPhone) == 0)
        {
            break;
        }

        int len = 0;
        int lastDash = 0;
        int check = 1;

        for (; newPhone[len] != '\0'; len++)
        {
            char ch = newPhone[len];

            if (!((ch >= '0' && ch <= '9') || ch == '-'))
            {
                check = 0;
                break;
            }

            if (ch == '-')
            {
                if (lastDash)
                {
                    check = 0;
                    break;
                }
                lastDash = 1;
            }
            else
            {
                lastDash = 0;
            }
        }

        if (len == 0 || newPhone[0] == '-' || newPhone[len - 1] == '-')
        {
            check = 0;
        }

        if (!check)
        {
            setColor(RED);
            gotoxy(39, 19); printf("전화번호 형식이 올바르지 않습니다.");
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");

            gotoxy(39, 19); printf("                                       ");
            gotoxy(39, 20); printf("                                       ");

            continue;
        }

        for (int i = 0; i < count; i++)
        {
            if (i == idx)
            {
                continue;
            }

            if (members[i].Mstate == 'N')
            {
                if (strcmp(newPhone, members[i].phone) == 0)
                {
                    dup = 1;
                    break;
                }
            }
        }

        if (dup)
        {
            setColor(RED);
            gotoxy(39, 19); printf("이미 등록된 전화번호입니다.");
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");

            gotoxy(39, 19); printf("                                      ");
            gotoxy(39, 20); printf("                                      ");

            continue;
        }

        if (strcmp(members[idx].phone, newPhone) != 0)
        {
            strcpy(members[idx].phone, newPhone);
            strcpy(currentPhone, newPhone);
            changed = 1;
        }
        break;
    }

    while (1)
    {
        gotoxy(44, 20); printf("새 비밀번호 : ");
        fgets(newPw, sizeof(newPw), stdin);
        newPw[strcspn(newPw, "\n")] = 0;

        if (strlen(newPw) == 0)
        {
            break;
        }

        int hasSpace = 0;
        for (int i = 0; newPw[i] != '\0'; i++)
        {
            if (newPw[i] == ' ' || newPw[i] == '\t')
            {
                hasSpace = 1;
                break;
            }
        }

        if (hasSpace)
        {
            setColor(RED);
            gotoxy(39, 19); printf("비밀번호에 공백을 포함할 수 없습니다.");
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");

            gotoxy(39, 19); printf("                                       ");
            gotoxy(39, 20); printf("                                       ");

            continue;
        }

        if (strcmp(members[idx].password, newPw) != 0)
        {
            strcpy(members[idx].password, newPw);
            changed = 1;
        }
        break;
    }

    if (!changed)
    {
        setColor(WHITE);
        gotoxy(39, 23); printf("변경된 내용이 없습니다.");
        gotoxy(39, 24);
        system("pause");
        return;
    }

    int saved = manageMemberFile(members, nullMember, 2, count);

    if (saved == 1)
    {
        if (strcmp(oldPhone, members[idx].phone) != 0)
        {
            Borrow nullBorrow = { 0 };
            Borrow borrowList[1000] = { 0 };
            int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0);

            for (int i = 0; i < borrowCount; i++)
            {
                if (strcmp(borrowList[i].borrowerPhone, oldPhone) == 0)
                {
                    strcpy(borrowList[i].borrowerPhone, members[idx].phone);
                }
            }

            manageBorrowFile(borrowList, nullBorrow, 2, borrowCount);
        }

        setColor(GREEN);
        gotoxy(39, 23); printf("회원 정보가 수정되었습니다.");
        setColor(WHITE);
        gotoxy(39, 24);
        system("pause");
    }
    else
    {
        setColor(RED);
        gotoxy(39, 23); printf("회원 정보 저장 실패.");
        setColor(WHITE);
        gotoxy(39, 24);
        system("pause");
    }
}

/*
    회원 탈퇴 기능
*/
void u_removeUser()
{
    Member nullMember = { 0 };
    Borrow nullBorrow = { 0 };
    Borrow borrowList[1000] = { 0 };

    int count = manageMemberFile(members, nullMember, 0, 0);
    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0);

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "회원 탈퇴");

    if (count == 0)
    {
        setColor(RED);
        gotoxy(39, 19); printf("회원 데이터가 없습니다.");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
        return;
    }

    int idx = -1;
    for (int i = 0; i < count; i++)
    {
        if (members[i].Mstate == 'N')
        {
            if (strcmp(members[i].phone, currentPhone) == 0)
            {
                idx = i;
                break;
            }
        }
    }

    if (idx == -1)
    {
        setColor(RED);
        gotoxy(39, 19); printf("현재 로그인된 회원을 찾을 수 없습니다.");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
        gotoxy(39, 19); printf("                                ");
        gotoxy(39, 20); printf("                                ");
        return;
    }

    int borrowingNow = 0;
    for (int i = 0; i < borrowCount; i++)
    {
        if (borrowList[i].state == 1)
        {
            if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0)
            {
                borrowingNow = 1;
                break;
            }
        }
    }

    gotoxy(44, 7);  printf("현재 이름      : %s", members[idx].name);
    gotoxy(44, 9);  printf("현재 전화번호  : %s", members[idx].phone);

    if (borrowingNow)
    {
        setColor(RED);
        gotoxy(39, 19); printf("대출 도서가 있어 탈퇴할 수 없습니다.");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
        gotoxy(39, 19); printf("                                           ");
        gotoxy(39, 20); printf("                                           ");
        return;
    }

    char input[10] = { 0 };

    gotoxy(44, 13); printf("정말로 탈퇴하시겠습니까?");
    gotoxy(44, 15); printf("Y 예 N 아니오 : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (input[0] == 'y' || input[0] == 'Y')
    {
        members[idx].Mstate = 'D';

        int saved = manageMemberFile(members, nullMember, 2, count);

        if (saved == 1)
        {
            setColor(GREEN);
            gotoxy(39, 23); printf("회원 탈퇴가 완료되었습니다.");
            setColor(WHITE);

            currentUser[0] = '\0';
            currentPhone[0] = '\0';

            gotoxy(39, 24);
            system("pause");
            _getch();

            mainLogin();
            return;
        }
        else
        {
            setColor(RED);
            gotoxy(39, 23); printf("회원 탈퇴 저장 실패.");
            setColor(WHITE);
            gotoxy(39, 24);
            system("pause");
            return;
        }
    }
    else
    {
        gotoxy(39, 23); printf("취소되었습니다.");
        gotoxy(39, 24);
        system("pause");
        return;
    }
}

/*
    도서 대출 기능
*/
void handleBorrowSearch()
{
    Book nullbook = { 0 };
    Borrow nullborrow = { 0 };
    Borrow temp[1000] = { 0 };

    int bookCount = manageBookFile(books, nullbook, 0, 0);
    int borrowCount = manageBorrowFile(temp, nullborrow, 0, 0);

    if (bookCount == 0)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 47, 28, "");
        drawBox(33, 3, 34, 3, "도서 대출");

        gotoxy(74, 12); printf("등록된 도서가 없습니다.");
        gotoxy(74, 14); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    getDate(0);

    for (int i = 0; i < borrowCount; i++)
    {
        if (temp[i].state == 1 && strcmp(temp[i].borrowerPhone, currentPhone) == 0)
        {
            if (isBeforeDate(temp[i].returnYear, temp[i].returnMonth, temp[i].returnDay, year, month, day))
            {
                system("cls");
                setColor(WHITE);
                drawBox(67, 1, 42, 28, "");
                setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
                setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
                setColor(RED); drawBox(16, 7, 11, 3, "");
                setColor(WHITE);
                drawBox(26, 1, 42, 28, "");
                drawBox(31, 3, 34, 3, "도서 대출");

                setColor(RED);
                gotoxy(74, 12); printf("연체 도서가 있어 대출이 제한됩니다.");
                setColor(WHITE);
                gotoxy(74, 14); printf("계속하려면 아무 키나 누르세요...");
                _getch();
                return;
            }
        }
    }

    int userBorrowing = 0;
    for (int i = 0; i < borrowCount; i++)
    {
        if (temp[i].state == 1 && strcmp(temp[i].borrowerPhone, currentPhone) == 0)
        {
            userBorrowing++;
        }
    }

    if (userBorrowing >= 3)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 47, 28, "");
        drawBox(33, 3, 34, 3, "도서 대출");

        setColor(RED);
        gotoxy(76, 12); printf("이미 3권 이상 대출 중입니다.");
        setColor(WHITE);
        gotoxy(76, 14); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    char word[50];

    while (1)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 47, 28, "");
        drawBox(33, 3, 34, 3, "도서 검색 후 대출");

        gotoxy(76, 11); printf("검색할 도서 제목 또는 저자");
        gotoxy(76, 12); printf("뒤로 가기 0");
        gotoxy(76, 13); printf("입력 : ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = 0;

        if (strcmp(word, "0") == 0)
        {
            return;
        }

        int matchIdx[1000];
        int matchCount = 0;

        for (int i = 0; i < bookCount; i++)
        {
            if (books[i].Bstate != 'N')
            {
                continue;
            }
            if (strstr(books[i].bookTitle, word) || strstr(books[i].bookAuthor, word))
            {
                matchIdx[matchCount++] = i;
            }
        }

        if (matchCount == 0)
        {
            setColor(RED);
            gotoxy(74, 16); printf("검색 결과가 없습니다.");
            setColor(WHITE);
            gotoxy(74, 18); printf("아무 키나 누르면 다시 검색합니다.");
            _getch();
            continue;
        }

        int startIndex = 0;
        const int ROWS = 15;
        char borrowId[10] = { 0 };
        int len = 0;

        while (1)
        {
            system("cls");
            setColor(WHITE);
            drawBox(67, 1, 42, 28, "");
            setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
            setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
            setColor(RED); drawBox(16, 7, 11, 3, "");
            setColor(WHITE);
            drawBox(26, 1, 47, 28, "");
            drawBox(33, 3, 34, 3, "검색 결과");

            gotoxy(27, 6); printf("ID │제목             │저자         │상태│재고");
            gotoxy(26, 7); printf("├─────────────────────────────────────────────┤");

            char titleShort[30];
            char authorShort[20];

            for (int r = 0; r < ROWS; r++)
            {
                int pos = startIndex + r;
                if (pos >= matchCount)
                {
                    break;
                }

                int bi = matchIdx[pos];

                if (strlen(books[bi].bookTitle) > 12)
                {
                    snprintf(titleShort, sizeof(titleShort), "%.14s...", books[bi].bookTitle);
                }
                else
                {
                    strcpy(titleShort, books[bi].bookTitle);
                }

                if (strlen(books[bi].bookAuthor) > 12)
                {
                    snprintf(authorShort, sizeof(authorShort), "%.10s...", books[bi].bookAuthor);
                }
                else
                {
                    strcpy(authorShort, books[bi].bookAuthor);
                }

                int canBorrow = 0;
                if (books[bi].total > 0)
                {
                    canBorrow = 1;
                }

                gotoxy(27, 8 + r);
                setColor(WHITE);
                printf(" %-2s│%-17s│%-13s│", books[bi].id, titleShort, authorShort);

                if (canBorrow)
                {
                    setColor(GREEN);
                    printf("가능");
                }
                else
                {
                    setColor(RED);
                    printf("불가");
                }

                setColor(WHITE);
                printf("│%2d", books[bi].total);
            }

            gotoxy(26, 26); printf("├─────────────────────────────────────────────┤");
            gotoxy(26, 28); printf("└─────────────────────────────────────────────┘");
            gotoxy(28, 27); printf("[←][→] 목록 넘기기");

            gotoxy(76, 9);  printf("대출할 책 ID 입력 : %s", borrowId);
            gotoxy(76, 11); printf("Enter 대출");
            gotoxy(76, 12); printf("0 Enter 이전 검색");

            int ch = _getch();

            if (ch == 0 || ch == 224)
            {
                ch = _getch();
                if (ch == LEFT && startIndex >= ROWS)
                {
                    startIndex -= ROWS;
                }
                else if (ch == RIGHT && startIndex + ROWS < matchCount)
                {
                    startIndex += ROWS;
                }
                continue;
            }

            if (ch == 13)
            {
                borrowId[len] = '\0';
                if (len == 0)
                {
                    continue;
                }
                if (strcmp(borrowId, "0") == 0)
                {
                    break;
                }

                int bi = -1;
                for (int k = 0; k < matchCount; k++)
                {
                    int idxb = matchIdx[k];
                    if (strcmp(books[idxb].id, borrowId) == 0)
                    {
                        bi = idxb;
                        break;
                    }
                }

                system("cls");
                setColor(WHITE);
                drawBox(67, 1, 42, 28, "");
                setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
                setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
                setColor(RED); drawBox(16, 7, 11, 3, "");
                setColor(WHITE);
                drawBox(26, 1, 47, 28, "");
                drawBox(33, 3, 34, 3, "도서 대출");

                if (bi == -1 || books[bi].Bstate != 'N')
                {
                    setColor(RED);
                    gotoxy(73, 12); printf("해당 ID의 도서를 찾을 수 없습니다.");
                    setColor(WHITE);
                    gotoxy(74, 14); printf("아무 키나 누르세요...");
                    _getch();
                    continue;
                }

                if (books[bi].total <= 0)
                {
                    setColor(RED);
                    gotoxy(73, 12); printf("해당 도서는 현재 대출 불가입니다.");
                    setColor(WHITE);
                    gotoxy(74, 14); printf("아무 키나 누르세요...");
                    _getch();
                    continue;
                }

                Borrow newBorrow = { 0 };
                strcpy(newBorrow.id, borrowId);
                strcpy(newBorrow.borrowerPhone, currentPhone);

                getDate(0);
                newBorrow.borrowYear = year;
                newBorrow.borrowMonth = month;
                newBorrow.borrowDay = day;

                getDate(10);
                newBorrow.returnYear = year;
                newBorrow.returnMonth = month;
                newBorrow.returnDay = day;

                newBorrow.state = 1;

                if (manageBorrowFile(NULL, newBorrow, 1, 0) == 1)
                {
                    books[bi].total--;
                    manageBookFile(books, nullbook, 2, bookCount);

                    setColor(GREEN);
                    gotoxy(75, 12); printf("대출이 완료되었습니다.");
                    gotoxy(75, 13); printf("반납 기한 : %d년 %d월 %d일", newBorrow.returnYear, newBorrow.returnMonth, newBorrow.returnDay);
                    setColor(WHITE);
                }
                else
                {
                    setColor(RED);
                    gotoxy(76, 12); printf("대출 정보 저장 실패.");
                    setColor(WHITE);
                }

                gotoxy(75, 15); printf("아무 키나 누르세요...");
                _getch();

                return;
            }

            if (ch == 8)
            {
                if (len > 0)
                {
                    len--;
                    borrowId[len] = '\0';
                }
                continue;
            }

            if (ch >= '0' && ch <= '9')
            {
                if (len < (int)sizeof(borrowId) - 1)
                {
                    borrowId[len++] = (char)ch;
                    borrowId[len] = '\0';
                }
                continue;
            }
        }
    }
}

/*
    도서 반납 기능
*/
void handleReturn()
{
    Borrow borrowList[1000] = { 0 };
    Borrow nullBorrow = { 0 };
    Book nullBook = { 0 };

    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0);
    int bookCount = manageBookFile(books, nullBook, 0, 0);

    if (borrowCount == 0)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(31, 3, 34, 3, "도서 반납");

        gotoxy(72, 12); printf("대출 데이터가 없습니다.");
        gotoxy(72, 14); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    int userBorrowList[1000];
    int userCount = 0;

    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0 && borrowList[i].state == 1)
        {
            userBorrowList[userCount++] = i;
        }
    }

    if (userCount == 0)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(31, 3, 34, 3, "도서 반납");

        gotoxy(72, 12); printf("현재 대출 중인 도서가 없습니다.");
        gotoxy(72, 14); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    getDate(0);

    system("cls");
    setColor(WHITE);
    drawBox(67, 1, 42, 28, "");
    setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
    setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
    setColor(RED); drawBox(16, 7, 11, 3, "");
    setColor(WHITE);
    drawBox(26, 1, 42, 28, "");
    drawBox(31, 3, 34, 3, "도서 반납");

    gotoxy(27, 6); printf("번호│제목           │ 반납 예정일│ 상태");
    gotoxy(26, 7); printf("├────────────────────────────────────────┤");

    char titleShort[30];
    int maxRows = (userCount < 15) ? userCount : 15;

    for (int i = 0; i < maxRows; i++)
    {
        int idx = userBorrowList[i];

        char fullTitle[50] = "(제목 없음)";
        for (int j = 0; j < bookCount; j++)
        {
            if (strcmp(borrowList[idx].id, books[j].id) == 0)
            {
                strcpy(fullTitle, books[j].bookTitle);
                break;
            }
        }

        if (strlen(fullTitle) > 12)
            snprintf(titleShort, sizeof(titleShort), "%.14s...", fullTitle);
        else
            strcpy(titleShort, fullTitle);

        int overdue = isBeforeDate(borrowList[idx].returnYear, borrowList[idx].returnMonth, borrowList[idx].returnDay, year, month, day);

        gotoxy(27, 8 + i);
        setColor(WHITE);
        printf(" %2d │%-15s│ %4d-%02d-%02d │ %-4s",
            i + 1,
            titleShort,
            borrowList[idx].returnYear,
            borrowList[idx].returnMonth,
            borrowList[idx].returnDay,
            overdue ? "연체" : "정상");
    }

    gotoxy(26, 26); printf("├────────────────────────────────────────┤");
    gotoxy(26, 28); printf("└────────────────────────────────────────┘");
    gotoxy(28, 27); printf("반납할 번호를 입력하세요.");

    gotoxy(72, 9);  printf("반납할 번호를 입력하세요.");
    gotoxy(72, 11); printf("번호 입력 후 Enter : 반납");
    gotoxy(72, 12); printf("0 입력 후 Enter : 취소");

    char input[10];
    gotoxy(72, 14);
    printf("번호 : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int select = atoi(input);

    if (select == 0) return;

    if (select < 1 || select > userCount)
    {
        setColor(RED);
        gotoxy(72, 16); printf("잘못된 번호 입력입니다.");
        setColor(WHITE);
        gotoxy(72, 18); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    int idx = userBorrowList[select - 1];

    int overdue = isBeforeDate(borrowList[idx].returnYear, borrowList[idx].returnMonth, borrowList[idx].returnDay, year, month, day);
    borrowList[idx].state = overdue ? 3 : 2;

    for (int j = 0; j < bookCount; j++)
    {
        if (strcmp(books[j].id, borrowList[idx].id) == 0)
        {
            if (books[j].total < books[j].available) books[j].total++;
            break;
        }
    }

    if (manageBorrowFile(borrowList, nullBorrow, 2, borrowCount) && manageBookFile(books, nullBook, 2, bookCount))
    {
        setColor(GREEN);
        gotoxy(72, 16); printf("도서가 성공적으로 반납되었습니다!");
        setColor(WHITE);
    }
    else
    {
        setColor(RED);
        gotoxy(72, 17); printf("반납 처리 중 오류가 발생했습니다.");
        setColor(WHITE);
    }

    gotoxy(72, 18); printf("계속하려면 아무 키나 누르세요...");
    _getch();
}

/*
    대출 조회 기능 (사용자) (도서 ID 순서)
*/
void viewBorrowHistory()
{
    Borrow borrowList[1000] = { 0 };
    Borrow nullborrow = { 0 };
    Book nullbook = { 0 };

    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0);
    int bookCount = manageBookFile(books, nullbook, 0, 0);

    for (int i = 0; i < borrowCount - 1; i++)
    {
        for (int j = i + 1; j < borrowCount; j++)
        {
            if (strcmp(borrowList[i].id, borrowList[j].id) > 0)
            {
                Borrow temp = borrowList[i];
                borrowList[i] = borrowList[j];
                borrowList[j] = temp;
            }
        }
    }

    Borrow userList[1000];
    int count1 = 0;

    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0)
        {
            userList[count1++] = borrowList[i];
        }
    }

    int startIndex = 0;
    char title[31];
    const int ROWS = 15;

    while (1)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "대출 내역 조회");

        gotoxy(27, 6);
        printf("ID │제목                         │대출일       │반납 예정일 │상태");
        gotoxy(26, 7);
        printf("├─────────────────────────────────────────────────────────────────────────────────┤");

        int check = 0;

        getDate(0);

        for (int i = 0; i < ROWS; i++)
        {
            int recordIndex = startIndex + i;
            if (recordIndex >= count1) break;

            check = 1;

            strcpy(title, "(제목 없음)");
            for (int j = 0; j < bookCount; j++)
            {
                if (strcmp(userList[recordIndex].id, books[j].id) == 0)
                {
                    strcpy(title, books[j].bookTitle);
                    break;
                }
            }

            int s = userList[recordIndex].state;
            int overdueBorrowing = 0;
            if (s == 1)
            {
                overdueBorrowing = isBeforeDate(userList[recordIndex].returnYear, userList[recordIndex].returnMonth, userList[recordIndex].returnDay, year, month, day);
            }

            if (s == 1 && overdueBorrowing) setColor(RED);
            else if (s == 1) setColor(GREEN);
            else if (s == 2) setColor(GRAY);
            else if (s == 3) setColor(RED);
            else setColor(WHITE);

            const char* st =
                (s == 1 && overdueBorrowing) ? "연체 대출중" :
                (s == 1) ? "대출 중" :
                (s == 2) ? "정상 반납" :
                (s == 3) ? "연체 반납" : "알수없음";

            gotoxy(27, 8 + i);
            printf(" %-2s│%-29s│ %4d-%02d-%02d │ %4d-%02d-%02d │ %s",
                userList[recordIndex].id, title,
                userList[recordIndex].borrowYear,
                userList[recordIndex].borrowMonth,
                userList[recordIndex].borrowDay,
                userList[recordIndex].returnYear,
                userList[recordIndex].returnMonth,
                userList[recordIndex].returnDay,
                st);
        }

        setColor(WHITE);

        if (!check)
        {
            gotoxy(27, 8);
            printf("대출 내역이 없습니다.");
        }

        gotoxy(26, 26);
        printf("├─────────────────────────────────────────────────────────────────────────────────┤");
        gotoxy(26, 28);
        printf("└─────────────────────────────────────────────────────────────────────────────────┘");
        gotoxy(28, 27);
        printf("[←][→] 페이지 이동   [0] 뒤로 가기");

        char key = _getch();

        if (key == 0 || key == 224)
        {
            key = _getch();
            if (key == LEFT && startIndex >= ROWS)
            {
                startIndex -= ROWS;
            }
            else if (key == RIGHT && startIndex + ROWS < count1)
            {
                startIndex += ROWS;
            }
        }
        else if (key == '0')
        {
            return;
        }
    }
}