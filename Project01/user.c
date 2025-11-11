#include "Header.h"

#define LEFT 75
#define RIGHT 77

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
    회원가입 기능
*/
void signUp()
{
    Member newMember = { 0 };
    Member null = { 0 };
    int count = manageMemberFile(members, null, 0);

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "회원가입");

    while (1)
    {
        gotoxy(44, 7); printf("이름        : ");
        fgets(newMember.name, sizeof(newMember.name), stdin);
        newMember.name[strcspn(newMember.name, "\n")] = 0;

        // 이름이 공백인지 체크
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
            gotoxy(39, 20); system("pause");
            continue;
        }
        break;
    }

    while (1)
    {
        int check = 0;

        gotoxy(44, 11); printf("전화번호    : ");
        fgets(newMember.phone, sizeof(newMember.phone), stdin);
        newMember.phone[strcspn(newMember.phone, "\n")] = 0;

        int len = 0;
        int lastWasDash = 0;
        int validFormat = 1;

        for (; newMember.phone[len] != '\0'; len++)
        {
            char ch = newMember.phone[len];
            if (!((ch >= '0' && ch <= '9') || ch == '-'))
            {
                validFormat = 0;
                break;
            }
            if (ch == '-')
            {
                if (lastWasDash)
                {
                    validFormat = 0;
                    break;
                }
                lastWasDash = 1;
            }
            else
            {
                lastWasDash = 0;
            }
        }
        if (len == 0 || newMember.phone[0] == '-' || newMember.phone[len - 1] == '-')
            validFormat = 0;

        if (!validFormat)
        {
            setColor(RED);
            gotoxy(39, 19); printf("전화번호 형식이 올바르지 않습니다.");
            setColor(WHITE);
            gotoxy(39, 20); system("pause");
            continue;
        }

        for (int i = 0; i < count; i++)
        {
            if (strcmp(newMember.phone, members[i].phone) == 0)
            {
                check = 1;
                gotoxy(39, 19);
                setColor(RED); printf("이미 등록된 전화번호입니다.");
                setColor(WHITE);
                gotoxy(39, 20); system("pause");
                break;
            }
        }
        if (check == 0) break;
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
            gotoxy(39, 20); system("pause");
            continue;
        }
        break;
    }

    int check = manageMemberFile(NULL, newMember, 1);

    if (check == 1)
    {
        setColor(GREEN);
        gotoxy(39, 19); printf("회원가입 완료");
        setColor(WHITE);
        gotoxy(39, 20); system("pause");
    }
}

/*
    도서 대출 기능
*/
void handleBorrow()
{
    Book nullbook = { 0 };
    Borrow nullborrow = { 0 };
    Borrow temp[1000] = { 0 };

    int count = manageBookFile(books, nullbook, 0, 0); // 도서 목록
    int borrowCount = manageBorrowFile(temp, nullborrow, 0, 0); // 대출 목록

    // 연체 중인지 체크
    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(temp[i].borrowerPhone, currentPhone) == 0 && temp[i].state == 2) // state 2 = 연체
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
            drawBox(31, 3, 34, 3, "도서 대출");

            setColor(RED);
            gotoxy(72, 12);
            printf("연체 도서가 있어 대출이 제한됩니다.");
            setColor(WHITE);
            gotoxy(72, 14);
            printf("계속하려면 아무 키나 누르세요...");
            _getch();
            return;
        }
    }

    // 3권 이상 대출 제한
    int userBorrowCount = 0;
    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(temp[i].borrowerPhone, currentPhone) == 0 && temp[i].state == 1)
        {
            userBorrowCount++;
        }
    }

    if (userBorrowCount >= 3)
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
        drawBox(31, 3, 34, 3, "도서 대출");

        setColor(RED);
        gotoxy(72, 12); printf("이미 3권 이상 대출 중입니다.");
        setColor(WHITE);
        gotoxy(72, 14);
        printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    if (count == 0)
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
        drawBox(31, 3, 34, 3, "도서 대출");

        gotoxy(72, 12); printf("등록된 도서가 없습니다.");
        gotoxy(72, 14); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    int  startIndex = 0; // 현재 페이지의 첫 도서 인덱스
    char borrowId[10] = { 0 }; // 오른쪽에서 입력할 도서 번호
    int  len = 0;
    const int ROWS = 15;

    while (1)
    {
        system("cls");
        setColor(WHITE);
        // 오른쪽 큰 박스 + 좌측 색 박스들 (고정 UI)
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(DarkYellow); drawBox(16, 7, 11, 3, "");
        setColor(RED);  drawBox(16, 10, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(31, 3, 34, 3, "도서 대출");

        // 왼쪽 도서 목록 헤더
        gotoxy(27, 6); printf("ID │제목             │저자        │상태");
        gotoxy(26, 7); printf("├────────────────────────────────────────┤");

        // 왼쪽 도서 목록 출력 (페이지)
        char titleShort[30];
        char nameShort[20];

        for (int i = 0; i < ROWS; i++)
        {
            int bookIndex = startIndex + i;
            if (bookIndex >= count)
            {
                break;
            }

            if (strlen(books[bookIndex].bookTitle) > 12)
            {
                snprintf(titleShort, sizeof(titleShort), "%.14s...", books[bookIndex].bookTitle);
            }
            else
            {
                strcpy(titleShort, books[bookIndex].bookTitle);
            }

            if (strlen(books[bookIndex].bookAuthor) > 8)
            {
                snprintf(nameShort, sizeof(nameShort), "%.8s...", books[bookIndex].bookAuthor);
            }
            else
            {
                strcpy(nameShort, books[bookIndex].bookAuthor);
            }

            // 해당 도서의 상태 계산 (0: 가능, 1: 대출중, 2: 연체)
            int state = 0;
            for (int j = 0; j < borrowCount; j++)
            {
                if (strcmp(temp[j].id, books[bookIndex].id) == 0 &&
                    (temp[j].state == 1 || temp[j].state == 2))
                {
                    state = temp[j].state;
                    if (state == 2)
                    {
                        break;
                    }
                }
            }

            gotoxy(27, 8 + i);
            setColor(WHITE);
            printf(" %-2s│%-17s│%-12s│", books[bookIndex].id, titleShort, nameShort);

            if (state == 0)
            {
                setColor(GREEN); printf("가능");
            }
            else if (state == 1)
            {
                setColor(YELLOW); printf("불가");
            }
            else
            {
                setColor(RED); printf("불가");
            }
            setColor(WHITE);
        }

        gotoxy(26, 26); printf("├────────────────────────────────────────┤");
        gotoxy(26, 28); printf("└────────────────────────────────────────┘");
        gotoxy(28, 27); printf("[←][→] 목록 넘기기");

        gotoxy(72, 9);
        printf("책 번호를 입력하세요 : %s", borrowId);
        gotoxy(72, 11);
        printf("번호 입력 후 Enter : 대출");
        gotoxy(72, 12);
        printf("0 입력 후 Enter : 취소");

        // 키 입력 처리
        int ch = _getch();

        if (ch == 0 || ch == 224) // 방향키
        {
            ch = _getch();
            if (ch == LEFT && startIndex >= ROWS)
            {
                startIndex -= ROWS;
            }
            else if (ch == RIGHT && startIndex + ROWS < count)
            {
                startIndex += ROWS;
            }
            continue;
        }

        // 엔터 : 현재 입력된 borrowId를 사용
        if (ch == 13)
        {
            borrowId[len] = '\0';

            if (len == 0)
            {
                // 아무것도 입력 안 했으면 다시 돌아감
                continue;
            }

            if (strcmp(borrowId, "0") == 0)
            {
                return; // 취소
            }
            break; // 입력 완료 > 대출 처리 단계
        }

        // 백스페이스
        if (ch == 8)
        {
            if (len > 0)
            {
                len--;
                borrowId[len] = '\0';
            }
            continue;
        }

        // 숫자 입력만 허용
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

    system("cls");
    setColor(WHITE);
    drawBox(67, 1, 42, 28, "");
    setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
    setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
    setColor(DarkYellow); drawBox(16, 7, 11, 3, "");
    setColor(RED); drawBox(16, 10, 11, 3, "");
    setColor(WHITE);
    drawBox(26, 1, 42, 28, "");
    drawBox(31, 3, 34, 3, "도서 대출");

    int found = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(borrowId, books[i].id) == 0)
        {
            found = 1;

            // 선택 도서 상태 다시 확인
            int state = 0;
            for (int a = 0; a < borrowCount; a++)
            {
                if (strcmp(temp[a].id, borrowId) == 0 &&
                    (temp[a].state == 1 || temp[a].state == 2))
                {
                    state = temp[a].state;
                    break;
                }
            }

            if (state == 1 || state == 2)
            {
                setColor(RED);
                gotoxy(72, 12);
                if (state == 1)
                {
                    printf("해당 도서는 현재 대출 중입니다.");
                }
                else
                {
                    printf("해당 도서는 연체 도서입니다.");
                }
                setColor(WHITE);
                gotoxy(72, 14);
                printf("계속하려면 아무 키나 누르세요...");
                _getch();
                return;
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
                setColor(GREEN);
                gotoxy(72, 12);
                printf("대출이 완료되었습니다!");
                gotoxy(72, 13);
                printf("반납 기한 : %d년 %d월 %d일까지", year, month, day);
                setColor(WHITE);
            }
            else
            {
                setColor(RED);
                gotoxy(72, 12);
                printf("대출 정보 저장 실패.");
                setColor(WHITE);
            }
            break;
        }
    }

    if (found == 0)
    {
        gotoxy(72, 12);
        printf("해당 ID의 도서를 찾을 수 없습니다.");
    }

    gotoxy(72, 15);
    printf("계속하려면 아무 키나 누르세요...");
    _getch();
}

/*
    도서 반납 기능
*/
void handleReturn()
{
    Borrow borrowList[1000] = { 0 };
    Borrow nullBorrow = { 0 };
    Book nullBook = { 0 };

    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0); // 대출 목록
    int bookCount = manageBookFile(books, nullBook, 0, 0); // 도서 목록(제목 찾을 때 사용)

    // 대출 데이터 없을 때
    if (borrowCount == 0)
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
        drawBox(31, 3, 34, 3, "도서 반납");

        gotoxy(72, 12); printf("대출 데이터가 없습니다.");
        gotoxy(72, 14); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    // 로그인한 사용자가 빌린 책만 모으기 (state 1: 대출중, 2: 연체중)
    int userBorrowList[1000];
    int userCount = 0;

    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0 &&
            (borrowList[i].state == 1 || borrowList[i].state == 2))
        {
            userBorrowList[userCount++] = i;
        }
    }

    // 현재 사용자 대출 없음
    if (userCount == 0)
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
        drawBox(31, 3, 34, 3, "도서 반납");

        gotoxy(72, 12); printf("현재 대출 중인 도서가 없습니다.");
        gotoxy(72, 14); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    system("cls");
    setColor(WHITE);
    drawBox(67, 1, 42, 28, "");
    setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
    setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
    setColor(DarkYellow); drawBox(16, 7, 11, 3, "");
    setColor(RED); drawBox(16, 10, 11, 3, "");
    setColor(WHITE);
    drawBox(26, 1, 42, 28, "");
    drawBox(31, 3, 34, 3, "도서 반납");

    // 왼쪽 목록 헤더
    gotoxy(27, 6); printf("번호│제목           │ 반납 예정일│ 상태");
    gotoxy(26, 7); printf("├────────────────────────────────────────┤");

    char titleShort[30];

    // 최대 15개까지만 표시(실제론 3권 제한이라 충분)
    int maxRows = (userCount < 15) ? userCount : 15;

    for (int i = 0; i < maxRows; i++)
    {
        int idx = userBorrowList[i];

        // 제목 찾기
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
        {
            snprintf(titleShort, sizeof(titleShort), "%.14s...", fullTitle);
        }
        else
        {
            strcpy(titleShort, fullTitle);
        }

        const char* stateStr = (borrowList[idx].state == 2) ? "연체" : "정상";

        gotoxy(27, 8 + i);
        setColor(WHITE);
        printf(" %2d │%-15s│ %4d-%02d-%02d │ %-4s",
            i + 1,
            titleShort,
            borrowList[idx].returnYear,
            borrowList[idx].returnMonth,
            borrowList[idx].returnDay,
            stateStr);
    }

    gotoxy(26, 26); printf("├────────────────────────────────────────┤");
    gotoxy(26, 28); printf("└────────────────────────────────────────┘");
    gotoxy(28, 27); printf("반납할 번호를 입력하세요.");

    gotoxy(72, 9);
    printf("반납할 번호를 입력하세요.");
    gotoxy(72, 11);
    printf("번호 입력 후 Enter : 반납");
    gotoxy(72, 12);
    printf("0 입력 후 Enter : 취소");

    char input[10];
    gotoxy(72, 14);
    printf("번호 : ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int select = atoi(input);

    if (select == 0)
    {
        return;
    }

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

    // 정상 반납 처리
    borrowList[idx].state = 0;

    if (manageBorrowFile(borrowList, nullBorrow, 2, borrowCount))
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

/*
    도서 목록 조회 기능
*/
void showBookList()
{
    Book null = { 0 };
    int count = manageBookFile(books, null, 0, 0); // 도서 개수
    int startIndex = 0;
    const int ROWS = 15;

    while (1)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen);   drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(DarkYellow);  drawBox(16, 7, 11, 3, "");
        setColor(RED);         drawBox(16, 10, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "도서 목록");

        gotoxy(27, 6); printf("ID │제목                         │저자                   │출판사            │재고");
        gotoxy(26, 7); printf("├─────────────────────────────────────────────────────────────────────────────────┤");

        for (int i = 0; i < ROWS; i++)
        {
            int bookIndex = startIndex + i;
            if (bookIndex >= count)
            {
                break;
            }

            setColor(WHITE);
            gotoxy(27, 8 + i);
            printf(" %-2s│%-29s│%-23s│%-18s│%2d",
                books[bookIndex].id,
                books[bookIndex].bookTitle,
                books[bookIndex].bookAuthor,
                books[bookIndex].bookPublish,
                books[bookIndex].total);
        }

        gotoxy(26, 26); printf("├─────────────────────────────────────────────────────────────────────────────────┤");
        gotoxy(26, 28); printf("└─────────────────────────────────────────────────────────────────────────────────┘");
        gotoxy(28, 27); printf("[←][→] 페이지 이동   [0] 뒤로 가기");

        char key = _getch();

        if (key == 0 || key == -32)  // 방향키
        {
            key = _getch();

            if (key == LEFT && startIndex >= ROWS)
            {
                startIndex -= ROWS;
            }
            else if (key == RIGHT && startIndex + ROWS < count)
            {
                startIndex += ROWS;
            }
        }
        else if (key == '0')  // 뒤로가기
        {
            return;
        }
    }
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

    // ID 기준 오름차순 정렬
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

    // 현재 로그인한 사용자의 기록만 추출
    Borrow userList[1000];
    int count1 = 0;

    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0)
        {
            userList[count1++] = borrowList[i];
        }
    }

    int  startIndex = 0;
    char title[31];
    const int ROWS = 15;

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
        drawBox(50, 3, 34, 3, "대출 내역 조회");

        gotoxy(27, 6);
        printf("ID │제목                         │대출일       │반납 예정일 │상태");
        gotoxy(26, 7);
        printf("├─────────────────────────────────────────────────────────────────────────────────┤");

        int check = 0;

        for (int i = 0; i < ROWS; i++)
        {
            int recordIndex = startIndex + i;

            if (recordIndex >= count1)
                break; // 현재 사용자 기록 끝

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

            if (userList[recordIndex].state == 2)
                setColor(RED); // 연체
            else if (userList[recordIndex].state == 1)
                setColor(GREEN); // 대출 중
            else if (userList[recordIndex].state == 0)
                setColor(GRAY);// 반납 완료
            else
                setColor(WHITE);

            gotoxy(27, 8 + i);
            printf(" %-2s│%-29s│ %4d-%02d-%02d │ %4d-%02d-%02d │ %s",
                userList[recordIndex].id, title,
                userList[recordIndex].borrowYear,
                userList[recordIndex].borrowMonth,
                userList[recordIndex].borrowDay,
                userList[recordIndex].returnYear,
                userList[recordIndex].returnMonth,
                userList[recordIndex].returnDay,
                userList[recordIndex].state == 0 ? "반납 완료"
                : (userList[recordIndex].state == 1 ? "대출 중" : "연체 중"));
        }

        setColor(WHITE);

        if (check == 0)
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

        if (key == 0 || key == 224) // 방향키
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
        else if (key == '0') // 뒤로 가기
        {
            return;
        }
    }
}