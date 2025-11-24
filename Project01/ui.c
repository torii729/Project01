#include "Header.h"

/*
    콘솔 커서 위치 이동 함수
    화면에서 글자를 찍을 위치를 옮기는 기능
*/
void gotoxy(int x, int y)
{
    COORD pos = { x, y }; // x, y 좌표를 pos에 묶어 저장
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // 커서를 pos 위치로 이동
}

/*
    콘솔 글자 색상 변경 함수
    글자 색을 바꿔서 더 보기 쉽게 만드는 기능
*/
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); // color 값대로 글자 색 설정
}

/*
    사각형 박스를 출력하는 함수
    네모 테두리를 그려서 메뉴나 제목을 보기 좋게 만드는 기능
*/
void drawBox(int x, int y, int width, int height, char text[])
{
    // 상단
    gotoxy(x, y); printf("┌"); // 박스 왼쪽 위 모서리 출력
    for (int i = 0; i < width - 2; i++)
    {
        printf("─"); // 위쪽 가로줄 길이만큼 출력
    }
    printf("┐"); // 박스 오른쪽 위 모서리 출력

    // 중간
    for (int i = 1; i < height - 1; i++)
    {
        gotoxy(x, y + i); printf("│"); // 왼쪽 세로줄 출력
        for (int j = 0; j < width - 2; j++)
        {
            printf(" "); // 박스 안쪽을 공백으로 채움
        }
        printf("│"); // 오른쪽 세로줄 출력
    }

    // 하단
    gotoxy(x, y + height - 1); printf("└"); // 박스 왼쪽 아래 모서리 출력
    for (int i = 0; i < width - 2; i++)
    {
        printf("─"); // 아래쪽 가로줄 길이만큼 출력
    }
    printf("┘"); // 박스 오른쪽 아래 모서리 출력

    // 텍스트 출력 (중앙 정렬)
    if (text != NULL) // 넣을 글자가 있을 때만 실행
    {
        int textX = x + (width - (int)strlen(text)) / 2; // 글자를 가로로 가운데로 오게 할 x 계산
        int textY = y + 1; // 글자를 박스 위쪽에서 한 줄 아래에 배치
        gotoxy(textX, textY); // 커서를 글자 위치로 이동
        printf("%s", text); // 글자 출력
    }
}

/*
    메인 화면 UI 출력
    프로그램 처음 화면에 나오는 박스와 글자 그리기
*/
void drawMainMenu()
{
    system("cls"); // 화면 지우기
    setColor(WHITE); // 기본 글자 색 흰색으로 설정

    setColor(DarkGreen); drawBox(77, 1, 11, 3, "1| 로그인"); // 로그인 메뉴 박스
    setColor(darkSkyBlue); drawBox(77, 4, 11, 3, "2| 가입  "); // 회원가입 메뉴 박스
    setColor(RED); drawBox(77, 7, 11, 3, "3| 종료  "); // 종료 메뉴 박스

    setColor(WHITE); // 다시 흰색으로 돌려놓기
    drawBox(36, 1, 42, 28, ""); // 큰 바깥 테두리 박스
    drawBox(40, 3, 34, 3, "도서관 대출 프로그램"); // 전체 메인 박스
}

/*
    메인 화면 (맨처음 화면)
    로그인, 가입, 종료를 고르는 곳
*/
int mainLogin()
{
    char input[10]; // 사용자가 입력한 글자를 담는 배열

    while (1)  // 무한 반복 (예시 : 회원가입 완료하고 여기로 다시 돌아와야 함, 반복하지 않으면 회원가입 완료 시 프로그램이 종료됨)
    {
        drawMainMenu(); // 메인 화면 출력
        gotoxy(42, 21); printf("──────────────────────────────"); // 화면 구분선 출력

        gotoxy(43, 20); // 입력 안내 글자 위치
        printf("우측 번호를 입력하세요 : "); // 오른쪽 메뉴 번호 입력 안내
        fgets(input, sizeof(input), stdin); // 키보드 입력을 input에 저장

        if (input[0] == '1') // 1번을 누르면
        {
            selectLogin(); // 로그인 종류 선택 화면으로 이동
        }
        else if (input[0] == '2') // 2번을 누르면
        {
            signUp(); // 회원가입 화면 실행
        }
        else if (input[0] == '3') // 3번을 누르면
        {
            return 0; // 프로그램 끝내기
        }
        else // 1,2,3이 아니면
        {
            gotoxy(39, 22); // 오류 글자 위치
            setColor(RED); // 빨간색으로 바꿈
            printf("잘못된 입력입니다. 다시 입력해주세요."); // 잘못 입력 안내
            setColor(WHITE); // 다시 흰색
            gotoxy(39, 23); system("pause"); // 잠깐 멈추고 다시 입력 받기
        }
    }
    return 0; // 보통은 여기까지 오지 않지만 안전용 반환
}

/*
    로그인 선택 화면
    사용자 로그인, 관리자 로그인 중 고르는 곳
*/
int selectLogin()
{
    char input[10]; // 사용자가 입력한 글자를 담는 배열

    drawMainMenu(); // 메인 화면 출력

    drawBox(40, 3, 34, 3, " 로그인 선택"); // 로그인 선택 제목 박스
    drawBox(49, 7, 16, 3, " 1. 사용자"); // 사용자 로그인
    drawBox(49, 11, 16, 3, " 2. 관리자"); // 관리자 로그인

    setColor(RED);
    drawBox(49, 15, 16, 3, " 3. 뒤로 가기"); // 메인 화면으로 돌아가기
    setColor(WHITE);

    gotoxy(42, 21); printf("──────────────────────────────"); // 구분선
    gotoxy(43, 20);
    printf("중앙 번호를 입력하세요 : "); // 가운데 번호 입력 안내
    fgets(input, sizeof(input), stdin); // 입력 저장

    if (input[0] == '1') // 사용자 선택
    {
        if (login())  // 로그인
        {
            userMenu(); // 로그인 성공 시 사용자 메뉴로 이동
            return 1; // 정상 처리 의미
        }
    }
    else if (input[0] == '2') // 관리자 선택
    {
        if (adminlogin())  // 로그인
        {
            adminMenu(); // 로그인 성공 시 관리자 메뉴로 이동
            return 1; // 정상 처리 의미
        }
    }
    else if (input[0] == '3') // 뒤로 가기 선택
    {
        return 1; // 메인으로 돌아감
    }
    else // 잘못 입력
    {
        gotoxy(39, 22);
        setColor(RED);
        printf("잘못된 입력입니다. 다시 입력해주세요."); // 입력 오류 안내
        setColor(WHITE);
        gotoxy(39, 23); system("pause"); // 잠깐 멈춤
    }
    return 0; // 로그인 실패나 잘못 입력 후 끝
}

/*
    로그인 후 사용자 메뉴 화면
    사용자 기능을 고르는 곳
*/
int userMenu()
{
    char welcome[60]; // 환영 문장 저장 배열
    char input[10]; // 메뉴 입력 저장 배열

    while (1) // 로그아웃하기 전까지 계속 반복
    {
        system("cls"); // 화면 지우기
        setColor(WHITE); // 기본 색 흰색

        drawBox(67, 1, 42, 28, ""); // 오른쪽 메뉴 영역 박스
        setColor(DarkGreen); drawBox(16, 1, 11, 3, ""); // 왼쪽 위 색 박스 장식
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, ""); // 왼쪽 중간 색 박스 장식
        setColor(RED); drawBox(16, 7, 11, 3, ""); // 왼쪽 아래 색 박스 장식
        setColor(WHITE);

        drawBox(26, 1, 42, 28, ""); // 가운데 메뉴 영역 박스
        drawBox(31, 3, 34, 3, "차례"); // 전체 메인 박스

        sprintf(welcome, "   %s 님, 환영합니다!", currentUser); // 출력할 환영 문장 만들기
        setColor(GREEN);
        gotoxy(35, 6); printf("%s", welcome); // 환영 문장 화면 출력
        setColor(WHITE);

        gotoxy(32, 11); printf("I. 사용자"); // 사용자 메뉴 제목
        gotoxy(31, 12); printf("──────────────────────────────────"); // 구분선

        gotoxy(34, 15); printf("1. 도서 대출"); // 1번 기능 안내
        gotoxy(34, 16); printf("2. 도서 반납"); // 2번 기능 안내
        gotoxy(34, 17); printf("3. 대출 내역"); // 3번 기능 안내
        gotoxy(48, 15); printf("4. 회원 수정"); // 4번 기능 안내
        gotoxy(48, 16); printf("5. 회원 탈퇴"); // 5번 기능 안내
        setColor(RED);  gotoxy(48, 17); printf("6. 로그아웃"); // 6번 로그아웃 강조

        setColor(WHITE);
        gotoxy(73, 20); printf("──────────────────────────────"); // 오른쪽 구분선
        gotoxy(31, 22); printf("──────────────────────────────────"); // 아래 구분선
        gotoxy(74, 19); printf("좌측 번호를 입력하세요 : "); // 왼쪽 번호 입력 안내
        fgets(input, sizeof(input), stdin); // 입력 받기

        if (input[0] == '1') // 도서 대출 선택
        {
            handleBorrowSearch(); // 대출 검색 및 처리
        }
        else if (input[0] == '2') // 도서 반납 선택
        {
            handleReturn(); // 반납 처리
        }
        else if (input[0] == '3') // 대출 내역 선택
        {
            viewBorrowHistory(); // 내가 빌린 기록 보기
        }
        else if (input[0] == '4') // 회원 수정 선택
        {
            userFix(); // 내 정보 고치기
        }
        else if (input[0] == '5') // 회원 탈퇴 선택
        {
            u_removeUser(); // 회원 삭제 처리
        }
        else if (input[0] == '6') // 로그아웃 선택
        {
            return 0; // 사용자 메뉴 끝내고 로그인 화면으로 돌아감
        }
        else // 잘못 입력
        {
            gotoxy(74, 21); setColor(RED);
            printf("잘못된 입력입니다. 다시 입력해주세요."); // 입력 오류 안내
            setColor(WHITE);
            gotoxy(74, 22); system("pause"); // 잠깐 멈춤
        }
    }
}

/*
    로그인 후 관리자 메뉴 화면
    관리자 기능을 고르는 곳
*/
int adminMenu()
{
    char welcome[60]; // 환영 문장 저장 배열
    char input[10]; // 메뉴 입력 저장 배열

    while (1) // 로그아웃하기 전까지 계속 반복
    {
        system("cls"); // 화면 지우기
        setColor(WHITE); // 기본 색 흰색

        drawBox(67, 1, 42, 28, ""); // 오른쪽 메뉴 영역 박스
        setColor(DarkGreen); drawBox(16, 1, 11, 3, ""); // 왼쪽 위 색 박스 장식
        setColor(darkSkyBlue); drawBox(16, 4, 11, 3, ""); // 왼쪽 중간 색 박스 장식
        setColor(RED); drawBox(16, 7, 11, 3, ""); // 왼쪽 아래 색 박스 장식
        setColor(WHITE);

        drawBox(26, 1, 42, 28, ""); // 가운데 메뉴 영역 박스
        drawBox(31, 3, 34, 3, "차례"); // 전체 메인 박스

        sprintf(welcome, "   %s 님, 환영합니다.", currentUser); // 출력할 환영 문장 만들기
        setColor(GREEN);
        gotoxy(35, 6); printf("%s", welcome); // 환영 문장 출력
        setColor(WHITE);

        gotoxy(32, 11); printf("II. 관리자"); // 관리자 메뉴 제목
        gotoxy(31, 12); printf("──────────────────────────────────"); // 구분선

        gotoxy(34, 16); printf("1. 도서 등록"); // 책 새로 넣기
        gotoxy(34, 17); printf("2. 도서 삭제"); // 책 지우기
        gotoxy(34, 18); printf("3. 대출 현황"); // 누가 빌렸는지 보기
        gotoxy(48, 16); printf("4. 회원 조회/삭제"); // 회원 목록 보고 삭제
        setColor(RED);  gotoxy(48, 17); printf("5. 로그아웃"); // 로그아웃 강조

        setColor(WHITE);
        gotoxy(73, 20); printf("──────────────────────────────"); // 오른쪽 구분선
        gotoxy(31, 22); printf("──────────────────────────────────"); // 아래 구분선
        gotoxy(74, 19); printf("좌측 번호를 입력하세요 : "); // 왼쪽 번호 입력 안내
        fgets(input, sizeof(input), stdin); // 입력 받기

        if (input[0] == '1') // 도서 등록 선택
        {
            addBook(); // 책 추가 화면 실행
        }
        else if (input[0] == '2') // 도서 삭제 선택
        {
            removeBook(); // 책 삭제 화면 실행
        }
        else if (input[0] == '3') // 대출 현황 선택
        {
            viewBorrowRecords(); // 대출 기록 전체 보기
        }
        else if (input[0] == '4') // 회원 조회/삭제 선택
        {
            m_removeUser(); // 관리자용 회원 관리
        }
        else if (input[0] == '5') // 로그아웃 선택
        {
            return 0; // 관리자 메뉴 끝내고 로그인 화면으로 돌아감
        }
        else // 잘못 입력
        {
            gotoxy(74, 21); setColor(RED);
            printf("잘못된 입력입니다. 다시 입력해주세요."); // 입력 오류 안내
            setColor(WHITE);
            gotoxy(74, 22); system("pause"); // 잠깐 멈춤
        }
    }
}
