#include "Header.h"

#define ADMIN_ID "admin"      // 관리자 아이디 매크로 상수
#define ADMIN_PW "password!"  // 관리자 비밀번호 매크로 상수

#define LEFT 75   // 키보드 왼쪽 화살표 코드
#define RIGHT 77  // 키보드 오른쪽 화살표 코드

/*
    비교 함수 (대출 기록 배열 borrowList를 정렬하는 부분)
    다른 파일(user.c)에 정의되어 있으므로 extern으로 선언해 사용
*/
extern int compareBorrowRecords(const void* a, const void* b);

/*
    관리자 로그인 기능
    ADMIN_ID, ADMIN_PW로만 로그인 가능
*/
int adminlogin()
{
    char name[20], password[20]; // 입력 받을 아이디와 비밀번호 저장

    system("cls"); // 화면 초기화
    drawMainMenu(); // 기본 메인 UI 출력

    drawBox(36, 1, 42, 28, ""); // 배경 박스
    drawBox(40, 3, 34, 3, "로그인"); // 로그인 제목 박스

    gotoxy(44, 7); printf("아이디        : "); // 아이디 입력 위치
    fgets(name, sizeof(name), stdin); // 아이디 입력
    name[strcspn(name, "\n")] = 0; // 엔터 제거

    gotoxy(44, 10); printf("비밀번호      : "); // 비밀번호 입력 위치

    int idx = 0; // 비밀번호 저장 인덱스
    char k; // 입력 문자 저장

    while (1) // 엔터 입력 전까지 반복
    {
        k = _getch(); // 화면에 안 보이게 한 글자 입력

        if (k == 13) // 엔터면 입력 종료
        {
            password[idx] = '\0'; // 문자열 끝 표시
            break;
        }
        else if (k == 8) // 백스페이스
        {
            printf("\b \b"); // 화면에서 별표 제거
        }
        else if (k >= 33 && k <= 126) // 출력 가능한 문자 범위
        {
            password[idx++] = k; // 실제 비밀번호 저장
            printf("*"); // 화면에는 별표 출력
        }
    }

    // 입력한 아이디, 비밀번호가 관리자 매크로와 일치하면 로그인 성공
    if (strcmp(name, ADMIN_ID) == 0 && strcmp(password, ADMIN_PW) == 0)
    {
        strcpy(currentUser, name); // 현재 사용자 전역 변수에 저장
        return 1; // 성공 반환
    }
    else // 실패하면 안내 메시지 출력
    {
        gotoxy(39, 22);
        setColor(RED);
        printf("정보가 일치하지 않습니다.");
        setColor(WHITE);
        gotoxy(39, 23);
        system("pause");
        return 0; // 실패 반환
    }
}

/*
    회원 조회 삭제 기능 (관리자)
    정상 회원 목록을 페이지로 보여주고
    대출중 회원은 삭제 불가, 연체중 회원도 삭제 불가
*/
void m_removeUser()
{
    Member nullMember = { 0 }; // 파일 읽기용 빈 회원
    Borrow nullBorrow = { 0 }; // 파일 읽기용 빈 대출
    Borrow borrowList[1000] = { 0 }; // 대출 목록 저장 배열

    int count = manageMemberFile(members, nullMember, 0, 0); // 회원 파일 읽기
    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0); // 대출 파일 읽기

    // 회원이 한 명도 없으면 안내 후 종료
    if (count == 0)
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "회원 조회 삭제");

        gotoxy(72, 12); printf("회원 데이터가 없습니다.");
        gotoxy(72, 14); printf("아무 키나 누르세요...");
        _getch();
        return;
    }

    int startIndex = 0; // 페이지 시작 인덱스
    const int ROWS = 15; // 한 페이지 출력 줄 수

    while (1) // 뒤로 가기 전까지 반복
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "회원 조회 삭제");

        gotoxy(27, 6);
        printf("번호│ 이름      │ 전화번호     │ 상태");
        gotoxy(26, 7);
        printf("├────────────────────────────────────────┤");

        int activeIdx[1000]; // 정상 회원 인덱스 모음
        int activeCount = 0; // 정상 회원 수

        // 정상 회원만 골라 activeIdx에 저장
        for (int i = 0; i < count; i++)
        {
            if (members[i].Mstate == 'N')
            {
                activeIdx[activeCount++] = i;
            }
        }

        getDate(0); // 오늘 날짜 갱신

        if (activeCount == 0) // 정상 회원이 없으면
        {
            gotoxy(27, 9); printf("현재 존재하는 회원이 없습니다.");
        }
        else
        {
            // 페이지 단위로 회원 출력
            for (int i = 0; i < ROWS; i++)
            {
                int viewIndex = startIndex + i; // 정상 회원 목록에서의 위치
                if (viewIndex >= activeCount) // 끝이면 중단
                {
                    break;
                }

                int mi = activeIdx[viewIndex]; // members 배열 실제 인덱스

                int borrowingNow = 0; // 현재 대출중 여부
                int overdueNow = 0;   // 현재 연체중 여부

                // 해당 회원의 대출 상태 확인
                for (int b = 0; b < borrowCount; b++)
                {
                    if (borrowList[b].state == 1) // 대출중 기록만
                    {
                        if (strcmp(borrowList[b].borrowerPhone, members[mi].phone) == 0) // 그 회원 번호면
                        {
                            borrowingNow = 1; // 대출중 표시

                            // 반납 예정일이 오늘보다 앞이면 연체 표시
                            if (isBeforeDate(borrowList[b].returnYear, borrowList[b].returnMonth, borrowList[b].returnDay, year, month, day))
                            {
                                overdueNow = 1;
                                break;
                            }
                        }
                    }
                }

                gotoxy(27, 8 + i);
                setColor(WHITE);
                printf(" %2d │ %-10s│ %-13s│ ",
                    viewIndex + 1,
                    members[mi].name,
                    members[mi].phone);

                // 상태 출력 색과 문구 결정
                if (overdueNow)
                {
                    setColor(RED);
                    printf("연체 중");
                }
                else if (borrowingNow)
                {
                    setColor(GREEN);
                    printf("대출 중");
                }
                else
                {
                    setColor(WHITE);
                    printf("정상");
                }
                setColor(WHITE);
            }
        }

        gotoxy(26, 26);
        printf("├────────────────────────────────────────┤");
        gotoxy(26, 28);
        printf("└────────────────────────────────────────┘");
        gotoxy(28, 27);
        printf("[1] 회원 삭제  [0] 뒤로 가기");

        int ch = _getch(); // 키 입력

        // 화살표 입력이면 페이지 이동
        if (ch == 0 || ch == 224)
        {
            ch = _getch();
            if (ch == LEFT && startIndex >= ROWS)
            {
                startIndex -= ROWS;
            }
            else if (ch == RIGHT && startIndex + ROWS < activeCount)
            {
                startIndex += ROWS;
            }
            continue;
        }

        if (ch == '0') // 뒤로 가기
        {
            return;
        }

        if (ch != '1') // 1이 아니면 무시하고 반복
        {
            continue;
        }

        if (activeCount == 0) // 삭제할 회원이 없으면 반복
        {
            continue;
        }

        // 삭제할 회원 번호 입력
        char input1[10] = { 0 };
        gotoxy(72, 9);  printf("삭제할 회원 번호 입력");
        gotoxy(72, 10); printf("번호 : ");
        fgets(input1, sizeof(input1), stdin);
        input1[strcspn(input1, "\n")] = 0;

        int select = atoi(input1); // 숫자로 변환

        // 범위 검사
        if (select < 1 || select > activeCount)
        {
            setColor(RED);
            gotoxy(72, 12); printf("잘못된 번호입니다.");
            setColor(WHITE);
            gotoxy(72, 14); printf("아무 키나 누르세요...");
            _getch();
            continue;
        }

        int removeIndex = activeIdx[select - 1]; // members에서 삭제할 실제 인덱스

        int borrowingNow = 0; // 삭제 대상이 대출중인지
        int overdueNow = 0;   // 삭제 대상이 연체중인지

        getDate(0);

        // 대출중인지 다시 확인
        for (int i = 0; i < borrowCount; i++)
        {
            if (borrowList[i].state == 1)
            {
                if (strcmp(borrowList[i].borrowerPhone, members[removeIndex].phone) == 0)
                {
                    borrowingNow = 1;

                    if (isBeforeDate(borrowList[i].returnYear, borrowList[i].returnMonth, borrowList[i].returnDay, year, month, day))
                    {
                        overdueNow = 1;
                    }
                    break;
                }
            }
        }

        // 대출중이면 삭제 불가
        if (borrowingNow)
        {
            setColor(RED);
            if (overdueNow)
            {
                gotoxy(72, 12); printf("연체 대출 중인 회원은 삭제할 수 없습니다.");
            }
            else
            {
                gotoxy(72, 12); printf("대출 중인 회원은 삭제할 수 없습니다.");
            }
            setColor(WHITE);
            gotoxy(72, 14); printf("아무 키나 누르세요...");
            _getch();
            continue;
        }

        // 삭제 확인 화면
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "회원 삭제 확인");

        setColor(RED);
        gotoxy(32, 7);  printf("정말로 삭제하시겠습니까?");
        setColor(WHITE);
        gotoxy(32, 9);  printf("이름 : %s", members[removeIndex].name);
        gotoxy(32, 10); printf("전화번호 : %s", members[removeIndex].phone);

        char input2[10] = { 0 };
        gotoxy(32, 14); printf("Y 예 N 아니오 : ");
        fgets(input2, sizeof(input2), stdin);
        input2[strcspn(input2, "\n")] = 0;

        if (input2[0] == 'y' || input2[0] == 'Y') // 삭제 확정
        {
            members[removeIndex].Mstate = 'D'; // 회원 상태를 삭제로 변경

            if (manageMemberFile(members, nullMember, 2, count)) // 회원 파일 저장
            {
                setColor(GREEN);
                gotoxy(72, 10); printf("회원이 삭제되었습니다.");
                setColor(WHITE);
            }
            else
            {
                setColor(RED);
                gotoxy(72, 10); printf("파일 갱신 실패.");
                setColor(WHITE);
            }

            gotoxy(72, 12); printf("아무 키나 누르세요...");
            _getch();
        }
        else // 삭제 취소
        {
            gotoxy(72, 10); printf("취소되었습니다.");
            gotoxy(72, 12); printf("아무 키나 누르세요...");
            _getch();
        }

        // 최신 데이터 다시 읽고 초기 페이지로
        count = manageMemberFile(members, nullMember, 0, 0);
        borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0);
        startIndex = 0;
    }
}

/*
    도서 추가 기능 (관리자)
    기존 목록을 보여주고 Enter를 누르면 새 책 입력
    같은 책이 이미 있으면 available, total만 증가
*/
void addBook()
{
    Book nullbook = { 0 }; // 파일 읽기용 빈 책
    Book newbook = { 0 };  // 새 책 정보 저장

    int count = manageBookFile(books, nullbook, 0, 0); // 책 목록 읽기

    // 현재 최대 ID를 찾아서 새 ID 만들기
    int maxId = 0;
    for (int i = 0; i < count; i++)
    {
        int v = atoi(books[i].id);
        if (v > maxId)
        {
            maxId = v;
        }
    }
    sprintf(newbook.id, "%d", maxId + 1); // 새 책 ID 설정

    int startIndex = 0; // 페이지 시작 인덱스
    const int ROWS = 15; // 한 페이지 보여줄 줄 수

    while (1) // Enter로 추가 화면 가기 전까지 목록 화면 반복
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "도서 추가");

        gotoxy(27, 6); printf("ID │제목                         │저자                   │출판사            │재고");
        gotoxy(26, 7); printf("├─────────────────────────────────────────────────────────────────────────────────┤");

        for (int i = 0; i < ROWS; i++) // 페이지 출력
        {
            int idx = startIndex + i;
            if (idx >= count)
            {
                break;
            }
            if (books[idx].Bstate != 'N') // 삭제된 책은 건너뜀
            {
                continue;
            }

            gotoxy(27, 8 + i);
            setColor(WHITE);
            printf(" %-2s│%-29s│%-23s│%-18s│%2d",
                books[idx].id,
                books[idx].bookTitle,
                books[idx].bookAuthor,
                books[idx].bookPublish,
                books[idx].total);
        }

        gotoxy(26, 26); printf("├─────────────────────────────────────────────────────────────────────────────────┤");
        gotoxy(26, 28); printf("└─────────────────────────────────────────────────────────────────────────────────┘");
        gotoxy(28, 27); printf("[←][→] 페이지 이동   [Enter] 도서 추가   [0] 뒤로 가기");

        int ch = _getch();

        if (ch == 0 || ch == 224) // 화살표 이동
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

        if (ch == '0') // 뒤로 가기
        {
            return;
        }

        if (ch == 13) // Enter 누르면 추가 입력 화면
        {
            break;
        }
    }

    // 새 도서 입력 화면
    system("cls");
    setColor(WHITE);
    drawBox(67, 1, 42, 28, "");
    setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
    setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
    setColor(RED); drawBox(16, 7, 11, 3, "");
    setColor(WHITE);
    drawBox(26, 1, 42, 28, "");
    drawBox(50, 3, 34, 3, "도서 추가");

    gotoxy(32, 7); printf("새 도서 등록");
    gotoxy(32, 9); printf("ID        : %s", newbook.id);

    // 제목 입력
    while (1)
    {
        gotoxy(32, 12); printf("제목      : ");
        fgets(newbook.bookTitle, sizeof(newbook.bookTitle), stdin);
        newbook.bookTitle[strcspn(newbook.bookTitle, "\n")] = 0;

        int empty = 1;
        for (int i = 0; newbook.bookTitle[i] != '\0'; i++)
        {
            if (newbook.bookTitle[i] != ' ' && newbook.bookTitle[i] != '\t')
            {
                empty = 0;
                break;
            }
        }

        if (empty)
        {
            setColor(RED);
            gotoxy(30, 19); printf("이름은 공백일 수 없습니다.");
            setColor(WHITE);
            gotoxy(30, 20);
            system("pause");
            continue;
        }
        break;
    }

    // 저자 입력
    while (1)
    {
        gotoxy(32, 15); printf("저자      : ");
        fgets(newbook.bookAuthor, sizeof(newbook.bookAuthor), stdin);
        newbook.bookAuthor[strcspn(newbook.bookAuthor, "\n")] = 0;

        int empty = 1;
        for (int i = 0; newbook.bookAuthor[i] != '\0'; i++)
        {
            if (newbook.bookAuthor[i] != ' ' && newbook.bookAuthor[i] != '\t')
            {
                empty = 0;
                break;
            }
        }

        if (empty)
        {
            setColor(RED);
            gotoxy(32, 19); printf("제목은 공백일 수 없습니다.");
            setColor(WHITE);
            gotoxy(32, 20);
            system("pause");
            continue;
        }
        break;
    }

    // 출판사 입력
    while (1)
    {
        gotoxy(32, 18); printf("출판사    : ");
        fgets(newbook.bookPublish, sizeof(newbook.bookPublish), stdin);
        newbook.bookPublish[strcspn(newbook.bookPublish, "\n")] = 0;

        int empty = 1;
        for (int i = 0; newbook.bookPublish[i] != '\0'; i++)
        {
            if (newbook.bookPublish[i] != ' ' && newbook.bookPublish[i] != '\t')
            {
                empty = 0;
                break;
            }
        }

        if (empty)
        {
            setColor(RED);
            gotoxy(32, 19); printf("출판사는 공백일 수 없습니다.");
            setColor(WHITE);
            gotoxy(32, 20);
            system("pause");
            continue;
        }
        break;
    }

    newbook.available = 1; // 기본 보유 수 1권
    newbook.total = 1;     // 현재 재고 1권
    newbook.Bstate = 'N';  // 정상 책 상태

    int c_Index = -1; // 동일 책 존재 여부 찾기

    // 제목 저자 출판사 모두 같은 책이 있으면 같은 책으로 처리
    for (int i = 0; i < count; i++)
    {
        if (strcmp(books[i].bookTitle, newbook.bookTitle) == 0 &&
            strcmp(books[i].bookAuthor, newbook.bookAuthor) == 0 &&
            strcmp(books[i].bookPublish, newbook.bookPublish) == 0)
        {
            c_Index = i;
            break;
        }
    }

    int result = 0;

    if (c_Index != -1) // 같은 책이 이미 있으면 수량만 증가
    {
        books[c_Index].available += 1;
        books[c_Index].total += 1;
        books[c_Index].Bstate = 'N';
        result = manageBookFile(books, nullbook, 2, count); // 전체 저장
    }
    else // 없으면 새 책 추가
    {
        result = manageBookFile(NULL, newbook, 1, 0); // append 저장
    }

    if (result) // 저장 성공
    {
        setColor(GREEN);
        gotoxy(72, 10); printf("도서 추가가 완료되었습니다.");
        setColor(WHITE);
    }
    else // 저장 실패
    {
        setColor(RED);
        gotoxy(72, 10); printf("도서 추가 실패.");
        setColor(WHITE);
    }

    gotoxy(72, 12); printf("아무 키나 누르면 돌아갑니다...");
    _getch();
}

/*
    도서 삭제 기능 (관리자)
    목록을 보여주고 ID로 삭제
    현재 대출중인 책은 삭제 불가
*/
void removeBook()
{
    Book nullbook = { 0 }; // 파일 읽기용 빈 책
    Borrow nullborrow = { 0 }; // 파일 읽기용 빈 대출
    Borrow borrowList[1000] = { 0 }; // 대출 목록 배열

    int startIndex = 0; // 페이지 시작
    char input1[10] = { 0 }; // 삭제할 책 ID 입력
    char input2[10] = { 0 }; // 삭제 확인 입력

    int count = manageBookFile(books, nullbook, 0, 0); // 책 목록 읽기
    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0); // 대출 목록 읽기

    if (count == 0) // 책이 없으면 안내 후 종료
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "도서 삭제");

        gotoxy(72, 12); printf("도서 데이터가 없습니다.");
        gotoxy(72, 14); printf("아무 키나 누르면 돌아갑니다...");
        _getch();
        return;
    }

    const int ROWS = 15; // 한 페이지 출력 줄 수

    while (1) // 뒤로 가기 전까지 반복
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "도서 삭제");

        gotoxy(27, 6); printf("ID │제목                         │저자                   │출판사            │재고");
        gotoxy(26, 7);
        printf("├─────────────────────────────────────────────────────────────────────────────────┤");

        for (int i = 0; i < ROWS; i++) // 페이지 출력
        {
            int bookIndex = startIndex + i;
            if (bookIndex >= count)
            {
                break;
            }
            if (books[bookIndex].Bstate != 'N') // 삭제된 책은 건너뜀
            {
                continue;
            }

            gotoxy(27, 8 + i);
            setColor(WHITE);
            printf(" %-2s│%-29s│%-23s│%-18s│%2d",
                books[bookIndex].id,
                books[bookIndex].bookTitle,
                books[bookIndex].bookAuthor,
                books[bookIndex].bookPublish,
                books[bookIndex].total);
        }

        gotoxy(26, 26); printf("├─────────────────────────────────────────────────────────────────────────────────┤");
        gotoxy(26, 28); printf("└─────────────────────────────────────────────────────────────────────────────────┘");
        gotoxy(28, 27); printf("[←][→] 페이지 이동   [1] 삭제할 도서 입력   [0] 뒤로 가기");

        char key = _getch();

        if (key == 0 || key == -32) // 화살표 처리
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
            continue;
        }
        else if (key == '0') // 뒤로 가기
        {
            return;
        }
        else if (key == '1') // 삭제 입력 모드
        {
            gotoxy(28, 27); printf("                                                           ");
            gotoxy(28, 27); printf("삭제할 도서 ID 입력 : ");
            fgets(input1, sizeof(input1), stdin);
            input1[strcspn(input1, "\n")] = 0;

            int removeIndex = -1; // 삭제 대상 찾기
            for (int i = 0; i < count; i++)
            {
                if (books[i].Bstate == 'N' && strcmp(books[i].id, input1) == 0)
                {
                    removeIndex = i;
                    break;
                }
            }

            if (removeIndex == -1) // 못 찾으면 재시도
            {
                setColor(RED);
                gotoxy(72, 10); printf("해당 ID의 도서를 찾을 수 없습니다.");
                setColor(WHITE);
                gotoxy(72, 12); printf("아무 키나 누르세요...");
                _getch();
                continue;
            }

            // 현재 대출중인 책인지 확인
            int borrowingNow = 0;
            for (int i = 0; i < borrowCount; i++)
            {
                if (strcmp(borrowList[i].id, books[removeIndex].id) == 0 && borrowList[i].state == 1)
                {
                    borrowingNow = 1;
                    break;
                }
            }

            if (borrowingNow) // 대출중이면 삭제 불가
            {
                setColor(RED);
                gotoxy(72, 10); printf("현재 대출 중인 도서는 삭제할 수 없습니다.");
                setColor(WHITE);
                gotoxy(72, 12); printf("아무 키나 누르세요...");
                _getch();
                continue;
            }

            // 삭제 확인 화면
            system("cls");
            setColor(WHITE);
            drawBox(67, 1, 42, 28, "");
            setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
            setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
            setColor(RED); drawBox(16, 7, 11, 3, "");
            setColor(WHITE);
            drawBox(26, 1, 42, 28, "");
            drawBox(50, 3, 34, 3, "도서 삭제 확인");

            setColor(RED);
            gotoxy(32, 7);  printf("정말로 삭제하시겠습니까?");
            setColor(WHITE);
            gotoxy(32, 9);  printf("제목 : %s", books[removeIndex].bookTitle);
            gotoxy(32, 10); printf("저자 : %s", books[removeIndex].bookAuthor);
            gotoxy(32, 11); printf("출판사 : %s", books[removeIndex].bookPublish);

            gotoxy(32, 14); printf("Y 예 N 아니오 : ");
            fgets(input2, sizeof(input2), stdin);
            input2[strcspn(input2, "\n")] = 0;

            if (input2[0] == 'y' || input2[0] == 'Y') // 삭제 확정
            {
                books[removeIndex].Bstate = 'D'; // 책 상태를 삭제로 변경

                if (manageBookFile(books, nullbook, 2, count)) // 책 파일 저장
                {
                    setColor(GREEN);
                    gotoxy(72, 10); printf("도서가 삭제되었습니다.");
                    setColor(WHITE);
                }
                else
                {
                    setColor(RED);
                    gotoxy(72, 10); printf("파일 갱신 실패.");
                    setColor(WHITE);
                }

                gotoxy(72, 12); printf("아무 키나 누르세요...");
                _getch();
                return; // 삭제 후 종료
            }
            else // 삭제 취소
            {
                gotoxy(72, 10); printf("취소되었습니다.");
                gotoxy(72, 12); printf("아무 키나 누르세요...");
                _getch();
                continue;
            }
        }
    }
}

/*
    대출 조회 기능 (관리자)
    전체 대출 기록을 연체 대출중, 정상 대출중, 연체 반납, 정상 반납 순으로 정렬해 출력
*/
void viewBorrowRecords()
{
    Borrow borrowList[1000] = { 0 }; // 전체 대출 목록
    Book booksLocal[1000] = { 0 };   // 책 목록 로컬 복사
    Borrow nullborrow = { 0 }; // 파일 읽기용 빈 대출
    Book nullbook = { 0 };     // 파일 읽기용 빈 책

    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0); // 대출 목록 읽기
    int bookCount = manageBookFile(booksLocal, nullbook, 0, 0);       // 책 목록 읽기

    getDate(0); // 오늘 날짜 갱신

    qsort(borrowList, borrowCount, sizeof(Borrow), compareBorrowRecords); // 전체 대출 정렬

    int startIndex = 0; // 페이지 시작
    const int ROWS = 15; // 한 페이지 출력 줄 수
    char titleShort[32]; // 제목 줄임 저장

    while (1) // 0 누를 때까지 반복
    {
        system("cls");
        setColor(WHITE);
        drawBox(67, 1, 42, 28, "");
        setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "전체 대출 내역");

        gotoxy(27, 6);
        printf("ID │ 제목                        │ 전화번호         │ 반납 예정일  │상태");
        gotoxy(26, 7);
        printf("├─────────────────────────────────────────────────────────────────────────────────┤");

        int check = 0; // 출력할 기록 존재 여부

        getDate(0); // 매 화면마다 오늘 날짜 재확인

        for (int i = 0; i < ROWS; i++) // 페이지 출력
        {
            int recordIndex = startIndex + i;
            if (recordIndex >= borrowCount)
            {
                break;
            }

            check = 1;

            // 책 제목 찾기
            char fullTitle[50] = "제목없음";
            for (int j = 0; j < bookCount; j++)
            {
                if (strcmp(borrowList[recordIndex].id, booksLocal[j].id) == 0)
                {
                    strcpy(fullTitle, booksLocal[j].bookTitle);
                    break;
                }
            }

            // 제목이 길면 잘라 저장
            if (strlen(fullTitle) > 29)
            {
                snprintf(titleShort, sizeof(titleShort), "%.29s", fullTitle);
            }
            else
            {
                strcpy(titleShort, fullTitle);
            }

            int s = borrowList[recordIndex].state; // 상태 값
            int overBorrowing = 0; // 연체 대출중 표시

            // 대출중 상태만 연체 체크
            if (s == 1)
            {
                if (isBeforeDate(borrowList[recordIndex].returnYear, borrowList[recordIndex].returnMonth, borrowList[recordIndex].returnDay, year, month, day))
                {
                    overBorrowing = 1;
                }
            }

            // 상태별 색 지정
            if (s == 1 && overBorrowing)
            {
                setColor(RED);
            }
            else if (s == 1)
            {
                setColor(GREEN);
            }
            else if (s == 2)
            {
                setColor(GRAY);
            }
            else if (s == 3)
            {
                setColor(RED);
            }
            else
            {
                setColor(WHITE);
            }

            const char* st =
                (s == 1 && overBorrowing) ? "연체 대출중" :
                (s == 1) ? "대출 중" :
                (s == 2) ? "정상 반납" :
                (s == 3) ? "연체 반납" : "알수없음";

            gotoxy(27, 8 + i);
            printf(" %-2s│ %-28s│ %-16s │ %4d-%02d-%02d   │ %s",
                borrowList[recordIndex].id,
                titleShort,
                borrowList[recordIndex].borrowerPhone,
                borrowList[recordIndex].returnYear,
                borrowList[recordIndex].returnMonth,
                borrowList[recordIndex].returnDay,
                st);
        }

        setColor(WHITE);

        if (!check) // 출력할 기록이 없으면
        {
            gotoxy(28, 10);
            printf("대출 내역이 없습니다.");
        }

        gotoxy(26, 26);
        printf("├─────────────────────────────────────────────────────────────────────────────────┤");
        gotoxy(26, 28);
        printf("└─────────────────────────────────────────────────────────────────────────────────┘");
        gotoxy(28, 27);
        printf("[←][→] 페이지 이동   [0] 뒤로 가기");

        char key = _getch(); // 키 입력

        if (key == 0 || key == 224) // 화살표 이동
        {
            key = _getch();
            if (key == LEFT && startIndex >= ROWS)
            {
                startIndex -= ROWS;
            }
            else if (key == RIGHT && startIndex + ROWS < borrowCount)
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
