#include "Header.h"

#define LEFT 75 // 키보드 왼쪽 화살표 코드
#define RIGHT 77 // 키보드 오른쪽 화살표 코드

/*
    비교 함수 (대출 기록 배열 borrowList를 정렬하는 부분)
    qsort에서 두 대출 기록의 순서를 비교할 때 호출
*/
int compareBorrowRecords(const void* a, const void* b)
{
    const Borrow* A = (const Borrow*)a; // 첫 번째 대출 기록을 Borrow로 바꾼 포인터
    const Borrow* B = (const Borrow*)b; // 두 번째 대출 기록을 Borrow로 바꾼 포인터

    int overA = 0; // A 기록이 연체 대출중인지 표시하는 값
    int overB = 0; // B 기록이 연체 대출중인지 표시하는 값

    // 대출중인 기록만 날짜로 연체 대출중 여부 판정
    if (A->state == 1) // A가 현재 대출중 상태면
    {
        if (isBeforeDate(A->returnYear, A->returnMonth, A->returnDay, year, month, day)) // 반납 예정일이 오늘보다 앞이면
        {
            overA = 1; // 연체 대출중 표시
        }
    }
    if (B->state == 1) // B도 현재 대출중 상태면
    {
        if (isBeforeDate(B->returnYear, B->returnMonth, B->returnDay, year, month, day)) // 반납 예정일이 오늘보다 앞이면
        {
            overB = 1; // 연체 대출중 표시
        }
    }

    /*
        정렬 우선순위 그룹
        3 : 연체 대출중
        2 : 정상 대출중
        1 : 연체 반납
        0 : 정상 반납
    */
    int groupA = 0; // A가 어느 그룹인지 저장
    int groupB = 0; // B가 어느 그룹인지 저장

    if (A->state == 1 && overA == 1) // A가 대출중이고 연체면
    {
        groupA = 3; // 제일 높은 우선순위
    }
    else if (A->state == 1) // A가 대출중인데 연체는 아니면
    {
        groupA = 2; // 두 번째 우선순위
    }
    else if (A->state == 3) // A가 연체 반납 상태면
    {
        groupA = 1; // 세 번째 우선순위
    }
    else // 그 외는 정상 반납
    {
        groupA = 0; // 가장 낮은 우선순위
    }

    if (B->state == 1 && overB == 1) // B가 대출중이고 연체면
    {
        groupB = 3; // 제일 높은 우선순위
    }
    else if (B->state == 1) // B가 대출중인데 연체는 아니면
    {
        groupB = 2; // 두 번째 우선순위
    }
    else if (B->state == 3) // B가 연체 반납 상태면
    {
        groupB = 1; // 세 번째 우선순위
    }
    else // 그 외는 정상 반납
    {
        groupB = 0; // 가장 낮은 우선순위
    }

    // 우선순위 높은 그룹이 먼저 오도록 내림차순 정렬
    if (groupA != groupB) // 그룹이 다르면
    {
        return groupB - groupA; // 큰 그룹 번호가 앞에 오게 비교값 반환
    }

    // 같은 그룹이면 반납 예정일이 빠른 순
    if (A->returnYear != B->returnYear) // 반납 예정 연도가 다르면
    {
        return A->returnYear - B->returnYear; // 연도 작은 것이 먼저
    }
    if (A->returnMonth != B->returnMonth) // 반납 예정 달이 다르면
    {
        return A->returnMonth - B->returnMonth; // 달 작은 것이 먼저
    }
    if (A->returnDay != B->returnDay) // 반납 예정 일이 다르면
    {
        return A->returnDay - B->returnDay; // 일 작은 것이 먼저
    }

    // 그래도 같으면 ID 작은 순
    return atoi(A->id) - atoi(B->id); // 숫자 ID로 바꿔 비교
}

/*
    날짜 비교 함수
    y1 m1 d1이 y2 m2 d2보다 과거면 1, 아니면 0 반환
*/
int isBeforeDate(int y1, int m1, int d1, int y2, int m2, int d2)
{
    if (y1 != y2) // 연도가 다르면
    {
        return y1 < y2; // 연도가 더 작으면 과거
    }
    if (m1 != m2) // 달이 다르면
    {
        return m1 < m2; // 달이 더 작으면 과거
    }
    return d1 < d2; // 일이 더 작으면 과거
}

/*
    로그인 기능
    입력한 이름 전화번호 비밀번호가 맞는지 검사
*/
int login()
{
    char name[20], phone[20], password[20]; // 사용자가 입력할 정보 저장
    Member nullMember = { 0 }; // 파일 읽기에 쓰는 빈 회원
    int count = manageMemberFile(members, nullMember, 0, 0); // member.txt에서 회원 목록 읽기

    if (count == 0) // 회원이 한 명도 없으면
    {
        return 0; // 로그인 실패
    }

    system("cls"); // 화면 지우기
    drawMainMenu(); // 기본 메인 UI 그리기

    drawBox(36, 1, 42, 28, ""); // 배경 박스
    drawBox(40, 3, 34, 3, "로그인"); // 로그인 제목 박스

    gotoxy(44, 7); printf("이름        : "); // 이름 입력 위치
    fgets(name, sizeof(name), stdin); // 이름 입력받기
    name[strcspn(name, "\n")] = 0; // 끝의 엔터 제거

    gotoxy(44, 11); printf("전화번호    : "); // 전화번호 입력 위치
    fgets(phone, sizeof(phone), stdin); // 전화번호 입력받기
    phone[strcspn(phone, "\n")] = 0; // 끝의 엔터 제거

    gotoxy(44, 15); printf("비밀번호    : "); // 비밀번호 입력 위치

    int idx = 0; // 비밀번호 저장 위치 인덱스
    char k; // 키보드에서 누른 문자 저장

    while (1) // 엔터 누를 때까지 반복
    {
        k = _getch(); // 화면에 안 보이게 한 글자 입력받기

        if (k == 13) // 엔터치면 입력 완료
        {
            password[idx] = '\0'; // 비밀번호 문자열 끝 표시
            break; // 입력 종료
        }
        else if (k == 8) // 백스페이스 누르면 지워져야 하는데...
        {
            printf("\b \b"); // 화면에서 별표 한 칸 지우기
        }
        else if (k >= 33 && k <= 126) // !부터 ~까지인데 뭔지모르겟으면 톡방 사진 참고
        {
            // 입력한 문자를 저장하나, 실제로 출력되는 건 *임
            password[idx++] = k; // 입력한 문자 저장
            printf("*"); // 화면에는 별표 출력
        }
    }

    int check = 0; // 로그인 성공 여부 표시

    for (int i = 0; i < count; i++) // 회원 목록을 처음부터 끝까지 검사
    {
        if (members[i].Mstate == 'N') // 정상 회원만 검사
        {
            if (strcmp(name, members[i].name) == 0 &&
                strcmp(phone, members[i].phone) == 0 &&
                strcmp(password, members[i].password) == 0) // 세 정보가 모두 같으면
            {
                check = 1; // 성공 표시
                break; // 더 볼 필요 없음
            }
        }
    }

    if (check) // 로그인 성공이면
    {
        strcpy(currentUser, name); // 전역 변수에 현재 이름 저장
        strcpy(currentPhone, phone); // 전역 변수에 현재 전화번호 저장
        return 1; // 성공 반환
    }
    else // 실패면
    {
        gotoxy(39, 22); // 오류 글자 위치
        setColor(RED); // 빨간색
        printf("정보가 일치하지 않습니다."); // 실패 안내
        setColor(WHITE); // 색 원래대로
        gotoxy(39, 23);
        system("pause"); // 잠깐 멈춤
        return 0; // 실패 반환
    }
}

/*
    회원가입 기능
    이름 전화번호 비밀번호를 입력받아 새 회원 저장
*/
void signUp()
{
    Member newMember = { 0 }; // 새 회원 정보 저장 공간
    Member nullMember = { 0 }; // 파일 읽기용 빈 회원
    int count = manageMemberFile(members, nullMember, 0, 0); // 기존 회원 읽기

    system("cls"); // 화면 지우기
    drawMainMenu(); // 기본 메인 UI

    drawBox(36, 1, 42, 28, ""); // 배경 박스
    drawBox(40, 3, 34, 3, "회원가입"); // 회원가입 제목

    while (1) // 이름이 제대로 들어올 때까지 반복
    {
        gotoxy(44, 7); printf("이름        : "); // 이름 입력 위치
        fgets(newMember.name, sizeof(newMember.name), stdin); // 이름 입력
        newMember.name[strcspn(newMember.name, "\n")] = 0; // 엔터 제거

        int empty = 1; // 이름이 공백만인지 검사할 변수
        for (int i = 0; newMember.name[i] != '\0'; i++) // 한 글자씩 확인
        {
            if (newMember.name[i] != ' ' && newMember.name[i] != '\t') // 공백이 아닌 글자 발견
            {
                empty = 0; // 공백만이 아님
                break;
            }
        }

        if (empty) // 공백만이면
        {
            setColor(RED);
            gotoxy(39, 19); printf("이름은 공백일 수 없습니다."); // 오류 안내
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause"); // 멈춤
            gotoxy(39, 19); printf("                                "); // 오류 문장 지우기
            gotoxy(39, 20); printf("                                "); // 오류 문장 지우기
            continue; // 다시 입력
        }
        break; // 정상 입력이면 종료
    }

    while (1) // 전화번호가 제대로 들어올 때까지 반복
    {
        int dup = 0; // 중복 여부 표시

        gotoxy(44, 11); printf("전화번호    : "); // 전화번호 입력 위치
        fgets(newMember.phone, sizeof(newMember.phone), stdin); // 전화번호 입력
        newMember.phone[strcspn(newMember.phone, "\n")] = 0; // 엔터 제거

        int len = 0; // 전화번호 길이
        int lastDash = 0; // 바로 전 글자가 - 인지 표시
        int format = 1; // 형식 맞는지 표시

        for (; newMember.phone[len] != '\0'; len++) // 한 글자씩 검사
        {
            char ch = newMember.phone[len];
            if (!((ch >= '0' && ch <= '9') || ch == '-')) // 숫자나 - 아니면
            {
                format = 0; // 형식 틀림
                break;
            }
            if (ch == '-') // - 입력이면
            {
                if (lastDash) // 연속으로 - 두 번이면
                {
                    format = 0; // 형식 틀림
                    break;
                }
                lastDash = 1; // 이번 글자가 - 표시
            }
            else // 숫자면
            {
                lastDash = 0; // 연속 - 상태 해제
            }
        }

        if (len == 0 || newMember.phone[0] == '-' || newMember.phone[len - 1] == '-') // 비거나 앞뒤가 -면
        {
            format = 0; // 형식 틀림
        }

        if (!format) // 형식 틀리면
        {
            setColor(RED);
            gotoxy(39, 19); printf("전화번호 형식이 올바르지 않습니다."); // 오류 안내
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");
            gotoxy(54, 11); printf("                  "); // 입력칸 지우기
            gotoxy(39, 19); printf("                                       "); // 오류 지우기
            gotoxy(39, 20); printf("                                       "); // 오류 지우기
            continue; // 다시 입력
        }

        for (int i = 0; i < count; i++) // 기존 회원과 중복 검사
        {
            if (members[i].Mstate == 'N') // 정상 회원만
            {
                if (strcmp(newMember.phone, members[i].phone) == 0) // 같은 전화번호면
                {
                    dup = 1; // 중복 표시
                    gotoxy(39, 19);
                    setColor(RED); printf("이미 등록된 전화번호입니다."); // 중복 안내
                    setColor(WHITE);
                    gotoxy(39, 20);
                    system("pause");
                    gotoxy(54, 11); printf("                  "); // 입력칸 지우기
                    gotoxy(39, 19); printf("                                      "); // 안내 지우기
                    gotoxy(39, 20); printf("                                      ");
                    break;
                }
            }
        }

        if (!dup) // 중복 아니면
        {
            break; // 전화번호 입력 종료
        }
    }

    while (1) // 비밀번호가 제대로 들어올 때까지 반복
    {
        gotoxy(44, 15); printf("비밀번호    : "); // 비밀번호 입력 위치
        fgets(newMember.password, sizeof(newMember.password), stdin); // 비밀번호 입력
        newMember.password[strcspn(newMember.password, "\n")] = 0; // 엔터 제거

        int hasSpace = 0; // 공백 포함 여부 표시
        for (int i = 0; newMember.password[i] != '\0'; i++) // 한 글자씩 검사
        {
            if (newMember.password[i] == ' ' || newMember.password[i] == '\t') // 공백 발견
            {
                hasSpace = 1; // 공백 있음 표시
                break;
            }
        }

        if (hasSpace) // 공백 있으면
        {
            setColor(RED);
            gotoxy(39, 19); printf("비밀번호에 공백을 포함할 수 없습니다."); // 오류 안내
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");
            gotoxy(54, 15); printf("                  "); // 입력칸 지우기
            gotoxy(39, 19); printf("                                "); // 오류 지우기
            gotoxy(39, 20); printf("                                ");
            continue; // 다시 입력
        }
        break; // 정상 입력이면 종료
    }

    newMember.Mstate = 'N'; // 새 회원 상태를 정상으로 설정

    int check = manageMemberFile(NULL, newMember, 1, 0); // 새 회원을 파일에 추가 저장

    if (check == 1) // 저장 성공이면
    {
        setColor(GREEN);
        gotoxy(39, 19); printf("회원가입 완료"); // 성공 안내
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
    }
}

/*
    회원 수정 기능
    현재 로그인한 회원의 이름 전화번호 비밀번호 변경
*/
void userFix()
{
    Member nullMember = { 0 }; // 파일 읽기용 빈 회원
    int count = manageMemberFile(members, nullMember, 0, 0); // 회원 목록 읽기

    system("cls"); // 화면 지우기
    drawMainMenu(); // 기본 메인 UI

    drawBox(36, 1, 42, 28, ""); // 배경 박스
    drawBox(40, 3, 34, 3, "회원 수정"); // 제목 박스

    if (count == 0) // 회원이 없으면
    {
        setColor(RED);
        gotoxy(39, 19); printf("회원 데이터가 없습니다.");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
        return; // 수정 불가라서 종료
    }

    int idx = -1; // 현재 회원 위치를 찾기 위한 변수
    for (int i = 0; i < count; i++) // 회원 목록 검사
    {
        if (members[i].Mstate == 'N') // 정상 회원만
        {
            if (strcmp(members[i].phone, currentPhone) == 0) // 로그인 전화번호와 같으면
            {
                idx = i; // 그 위치 저장
                break;
            }
        }
    }

    if (idx == -1) // 못 찾았으면
    {
        setColor(RED);
        gotoxy(39, 19); printf("현재 로그인된 회원을 찾을 수 없습니다.");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
        gotoxy(39, 19); printf("                                ");
        gotoxy(39, 20); printf("                                ");
        return; // 수정 불가라서 종료
    }

    char oldPhone[20] = { 0 }; // 기존 전화번호 저장 공간
    strcpy(oldPhone, members[idx].phone); // 나중에 대출 기록 전화번호 바꾸려고 저장

    char newName[20] = { 0 }; // 새 이름 입력 공간
    char newPhone[20] = { 0 }; // 새 전화번호 입력 공간
    char newPw[20] = { 0 }; // 새 비밀번호 입력 공간

    int changed = 0; // 실제로 바뀐 값이 있는지 표시

    gotoxy(44, 7);  printf("현재 이름      : %s", members[idx].name); // 현재 이름 보여주기
    gotoxy(44, 9);  printf("현재 전화번호  : %s", members[idx].phone); // 현재 전화번호 보여주기
    gotoxy(44, 11); printf("현재 비밀번호  : %s", members[idx].password); // 현재 비밀번호 보여주기

    while (1) // 새 이름 입력 반복
    {
        gotoxy(44, 16); printf("새 이름 : ");
        fgets(newName, sizeof(newName), stdin); // 새 이름 입력
        newName[strcspn(newName, "\n")] = 0; // 엔터 제거

        if (strlen(newName) == 0) // 그냥 엔터면 이름 변경 안 함
        {
            break;
        }

        int empty = 1; // 공백만인지 검사
        for (int i = 0; newName[i] != '\0'; i++)
        {
            if (newName[i] != ' ' && newName[i] != '\t')
            {
                empty = 0;
                break;
            }
        }

        if (empty) // 공백만이면
        {
            setColor(RED);
            gotoxy(39, 19); printf("이름은 공백일 수 없습니다.");
            setColor(WHITE);
            gotoxy(39, 20);
            system("pause");
            gotoxy(39, 19); printf("                                    ");
            gotoxy(39, 20); printf("                                    ");

            continue; // 다시 입력
        }

        if (strcmp(members[idx].name, newName) != 0) // 기존 이름과 다르면
        {
            strcpy(members[idx].name, newName); // 배열 값 수정
            strcpy(currentUser, newName); // 로그인 이름도 같이 수정
            changed = 1; // 변경 표시
        }
        break; // 이름 처리 끝
    }

    while (1) // 새 전화번호 입력 반복
    {
        int dup = 0; // 중복 여부 표시

        gotoxy(44, 18); printf("새 전화번호 : ");
        fgets(newPhone, sizeof(newPhone), stdin); // 새 전화번호 입력
        newPhone[strcspn(newPhone, "\n")] = 0; // 엔터 제거

        if (strlen(newPhone) == 0) // 그냥 엔터면 전화번호 변경 안 함
        {
            break;
        }

        int len = 0; // 길이 검사
        int lastDash = 0; // 연속 - 검사
        int check = 1; // 형식 맞는지 표시

        for (; newPhone[len] != '\0'; len++)
        {
            char ch = newPhone[len];

            if (!((ch >= '0' && ch <= '9') || ch == '-')) // 숫자나 - 아니면
            {
                check = 0; // 형식 틀림
                break;
            }

            if (ch == '-') // -면
            {
                if (lastDash) // 연속 -면
                {
                    check = 0; // 형식 틀림
                    break;
                }
                lastDash = 1;
            }
            else
            {
                lastDash = 0;
            }
        }

        if (len == 0 || newPhone[0] == '-' || newPhone[len - 1] == '-') // 앞뒤 -거나 비면
        {
            check = 0;
        }

        if (!check) // 형식 틀리면
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

        for (int i = 0; i < count; i++) // 다른 회원과 중복 검사
        {
            if (i == idx) // 자기 자신은 건너뜀
            {
                continue;
            }

            if (members[i].Mstate == 'N')
            {
                if (strcmp(newPhone, members[i].phone) == 0) // 같은 번호면
                {
                    dup = 1;
                    break;
                }
            }
        }

        if (dup) // 중복이면
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

        if (strcmp(members[idx].phone, newPhone) != 0) // 기존 번호와 다르면
        {
            strcpy(members[idx].phone, newPhone); // 회원 배열 수정
            strcpy(currentPhone, newPhone); // 로그인 번호도 수정
            changed = 1; // 변경 표시
        }
        break;
    }

    while (1) // 새 비밀번호 입력 반복
    {
        gotoxy(44, 20); printf("새 비밀번호 : ");
        fgets(newPw, sizeof(newPw), stdin); // 새 비밀번호 입력
        newPw[strcspn(newPw, "\n")] = 0; // 엔터 제거

        if (strlen(newPw) == 0) // 그냥 엔터면 비밀번호 변경 안 함
        {
            break;
        }

        int hasSpace = 0; // 공백 포함 여부
        for (int i = 0; newPw[i] != '\0'; i++)
        {
            if (newPw[i] == ' ' || newPw[i] == '\t')
            {
                hasSpace = 1;
                break;
            }
        }

        if (hasSpace) // 공백 있으면
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

        if (strcmp(members[idx].password, newPw) != 0) // 기존 비번과 다르면
        {
            strcpy(members[idx].password, newPw); // 비번 수정
            changed = 1; // 변경 표시
        }
        break;
    }

    if (!changed) // 아무 것도 안 바뀌었으면
    {
        setColor(WHITE);
        gotoxy(39, 23); printf("변경된 내용이 없습니다.");
        gotoxy(39, 24);
        system("pause");
        return;
    }

    int saved = manageMemberFile(members, nullMember, 2, count); // 바뀐 회원 목록을 파일에 다시 저장

    if (saved == 1) // 저장 성공이면
    {
        if (strcmp(oldPhone, members[idx].phone) != 0) // 전화번호가 바뀌었으면
        {
            Borrow nullBorrow = { 0 }; // 파일 읽기용 빈 대출
            Borrow borrowList[1000] = { 0 }; // 대출 목록 배열
            int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0); // 대출 목록 읽기

            for (int i = 0; i < borrowCount; i++) // 대출 기록에서 번호 바꾸기
            {
                if (strcmp(borrowList[i].borrowerPhone, oldPhone) == 0) // 옛 번호가 있으면
                {
                    strcpy(borrowList[i].borrowerPhone, members[idx].phone); // 새 번호로 교체
                }
            }

            manageBorrowFile(borrowList, nullBorrow, 2, borrowCount); // 수정된 대출 목록 다시 저장
        }

        setColor(GREEN);
        gotoxy(39, 23); printf("회원 정보가 수정되었습니다.");
        setColor(WHITE);
        gotoxy(39, 24);
        system("pause");
    }
    else // 저장 실패면
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
    현재 로그인한 회원을 삭제 상태로 바꿈
*/
void u_removeUser()
{
    Member nullMember = { 0 }; // 파일 읽기용 빈 회원
    Borrow nullBorrow = { 0 }; // 파일 읽기용 빈 대출
    Borrow borrowList[1000] = { 0 }; // 대출 목록 배열

    int count = manageMemberFile(members, nullMember, 0, 0); // 회원 목록 읽기
    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0); // 대출 목록 읽기

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "회원 탈퇴");

    if (count == 0) // 회원이 없으면
    {
        setColor(RED);
        gotoxy(39, 19); printf("회원 데이터가 없습니다.");
        setColor(WHITE);
        gotoxy(39, 20);
        system("pause");
        return;
    }

    int idx = -1; // 현재 회원 위치 찾기
    for (int i = 0; i < count; i++)
    {
        if (members[i].Mstate == 'N')
        {
            if (strcmp(members[i].phone, currentPhone) == 0) // 로그인 번호와 같으면
            {
                idx = i;
                break;
            }
        }
    }

    if (idx == -1) // 못 찾으면
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

    int borrowingNow = 0; // 지금 빌린 책이 있는지 표시
    for (int i = 0; i < borrowCount; i++)
    {
        if (borrowList[i].state == 1) // 대출중 기록만
        {
            if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0) // 내 번호면
            {
                borrowingNow = 1; // 대출중 책 있음
                break;
            }
        }
    }

    gotoxy(44, 7);  printf("현재 이름      : %s", members[idx].name);
    gotoxy(44, 9);  printf("현재 전화번호  : %s", members[idx].phone);

    if (borrowingNow) // 빌린 책이 있으면
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

    char input[10] = { 0 }; // Y N 입력 저장

    gotoxy(44, 13); printf("정말로 탈퇴하시겠습니까?");
    gotoxy(44, 15); printf("Y 예 N 아니오 : ");
    fgets(input, sizeof(input), stdin); // 입력 받기
    input[strcspn(input, "\n")] = 0; // 엔터 제거

    if (input[0] == 'y' || input[0] == 'Y') // Y면
    {
        members[idx].Mstate = 'D'; // 회원 상태를 삭제로 바꿈

        int saved = manageMemberFile(members, nullMember, 2, count); // 회원 파일 전체 저장

        if (saved == 1) // 저장 성공이면
        {
            setColor(GREEN);
            gotoxy(39, 23); printf("회원 탈퇴가 완료되었습니다.");
            setColor(WHITE);

            currentUser[0] = '\0'; // 로그인 이름 지우기
            currentPhone[0] = '\0'; // 로그인 번호 지우기

            gotoxy(39, 24);
            system("pause");
            _getch();

            mainLogin(); // 처음 화면으로 이동
            return;
        }
        else // 저장 실패면
        {
            setColor(RED);
            gotoxy(39, 23); printf("회원 탈퇴 저장 실패.");
            setColor(WHITE);
            gotoxy(39, 24);
            system("pause");
            return;
        }
    }
    else // Y가 아니면 취소
    {
        gotoxy(39, 23); printf("취소되었습니다.");
        gotoxy(39, 24);
        system("pause");
        return;
    }
}

/*
    도서 대출 기능
    책을 검색하고 선택해서 대출 기록 저장
*/
void handleBorrowSearch()
{
    Book nullbook = { 0 }; // 파일 읽기용 빈 책
    Borrow nullborrow = { 0 }; // 파일 읽기용 빈 대출
    Borrow temp[1000] = { 0 }; // 대출 목록 임시 저장

    int bookCount = manageBookFile(books, nullbook, 0, 0); // 책 목록 읽기
    int borrowCount = manageBorrowFile(temp, nullborrow, 0, 0); // 대출 목록 읽기

    if (bookCount == 0) // 책이 하나도 없으면
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

    getDate(0); // 오늘 날짜 갱신

    for (int i = 0; i < borrowCount; i++) // 내 대출 기록 검사
    {
        if (temp[i].state == 1 && strcmp(temp[i].borrowerPhone, currentPhone) == 0) // 내가 빌린 책 중 대출중이면
        {
            if (isBeforeDate(temp[i].returnYear, temp[i].returnMonth, temp[i].returnDay, year, month, day)) // 연체면
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
                return; // 연체 있으면 대출 막기
            }
        }
    }

    int userBorrowing = 0; // 내가 대출중인 권수
    for (int i = 0; i < borrowCount; i++)
    {
        if (temp[i].state == 1 && strcmp(temp[i].borrowerPhone, currentPhone) == 0) // 대출중 내 기록이면
        {
            userBorrowing++; // 권수 증가
        }
    }

    if (userBorrowing >= 3) // 3권 이상이면
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
        return; // 더 못 빌리게 종료
    }

    char word[50]; // 검색어 저장

    while (1) // 검색을 계속 할 수 있게 반복
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
        fgets(word, sizeof(word), stdin); // 검색어 입력받기
        word[strcspn(word, "\n")] = 0; // 엔터 제거

        if (strcmp(word, "0") == 0) // 0이면 뒤로 가기
        {
            return;
        }

        int matchIdx[1000]; // 검색에 걸린 책의 인덱스 모음
        int matchCount = 0; // 검색에 걸린 책 개수

        for (int i = 0; i < bookCount; i++) // 모든 책 검사
        {
            if (books[i].Bstate != 'N') // 삭제된 책은 건너뜀
            {
                continue;
            }
            if (strstr(books[i].bookTitle, word) || strstr(books[i].bookAuthor, word)) // 제목이나 저자에 검색어가 있으면
            {
                matchIdx[matchCount++] = i; // 해당 책 위치 저장
            }
        }

        if (matchCount == 0) // 검색 결과 없으면
        {
            setColor(RED);
            gotoxy(74, 16); printf("검색 결과가 없습니다.");
            setColor(WHITE);
            gotoxy(74, 18); printf("아무 키나 누르면 다시 검색합니다.");
            _getch();
            continue; // 다시 검색
        }

        int startIndex = 0; // 현재 페이지의 시작 위치
        const int ROWS = 15; // 한 페이지에 보여줄 줄 수
        char borrowId[10] = { 0 }; // 대출할 책 ID 입력 저장
        int len = 0; // borrowId 길이

        while (1) // 검색 결과 페이지에서 조작 반복
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

            char titleShort[30]; // 긴 제목 줄여서 저장
            char authorShort[20]; // 긴 저자명 줄여서 저장

            for (int r = 0; r < ROWS; r++) // 한 페이지 분량 출력
            {
                int pos = startIndex + r; // 실제 검색 결과 위치
                if (pos >= matchCount) // 범위를 넘으면
                {
                    break; // 출력 종료
                }

                int bi = matchIdx[pos]; // 실제 books 배열 인덱스

                if (strlen(books[bi].bookTitle) > 12) // 제목이 길면
                {
                    snprintf(titleShort, sizeof(titleShort), "%.14s...", books[bi].bookTitle); // 앞부분만 잘라 표시
                }
                else
                {
                    strcpy(titleShort, books[bi].bookTitle); // 짧으면 그대로
                }

                if (strlen(books[bi].bookAuthor) > 12) // 저자명이 길면
                {
                    snprintf(authorShort, sizeof(authorShort), "%.10s...", books[bi].bookAuthor); // 잘라 표시
                }
                else
                {
                    strcpy(authorShort, books[bi].bookAuthor);
                }

                int canBorrow = 0; // 대출 가능 여부
                if (books[bi].total > 0) // 재고가 있으면
                {
                    canBorrow = 1; // 가능 표시
                }

                gotoxy(27, 8 + r);
                setColor(WHITE);
                printf(" %-2s│%-17s│%-13s│", books[bi].id, titleShort, authorShort); // 한 줄 출력

                if (canBorrow) // 가능하면 초록색
                {
                    setColor(GREEN);
                    printf("가능");
                }
                else // 불가면 빨간색
                {
                    setColor(RED);
                    printf("불가");
                }

                setColor(WHITE);
                printf("│%2d", books[bi].total); // 재고 출력
            }

            gotoxy(26, 26); printf("├─────────────────────────────────────────────┤");
            gotoxy(26, 28); printf("└─────────────────────────────────────────────┘");
            gotoxy(28, 27); printf("[←][→] 목록 넘기기");

            gotoxy(76, 9);  printf("대출할 책 ID 입력 : %s", borrowId); // 현재 입력된 ID 보여주기
            gotoxy(76, 11); printf("Enter 대출");
            gotoxy(76, 12); printf("0 Enter 이전 검색");

            int ch = _getch(); // 키 하나 입력받기

            if (ch == 0 || ch == 224) // 특수키면
            {
                ch = _getch(); // 실제 키 코드 한 번 더 받기
                if (ch == LEFT && startIndex >= ROWS) // 왼쪽이면 이전 페이지
                {
                    startIndex -= ROWS;
                }
                else if (ch == RIGHT && startIndex + ROWS < matchCount) // 오른쪽이면 다음 페이지
                {
                    startIndex += ROWS;
                }
                continue; // 다시 화면 출력
            }

            if (ch == 13) // Enter면
            {
                borrowId[len] = '\0'; // 문자열 끝 표시
                if (len == 0) // 아무 것도 안 쳤으면
                {
                    continue; // 다시 입력
                }
                if (strcmp(borrowId, "0") == 0) // 0이면 이전 검색으로
                {
                    break; // 검색어 입력 화면으로 돌아가기
                }

                int bi = -1; // 선택한 책 위치 찾기용
                for (int k = 0; k < matchCount; k++)
                {
                    int idxb = matchIdx[k];
                    if (strcmp(books[idxb].id, borrowId) == 0) // 입력한 ID와 같은 책이면
                    {
                        bi = idxb; // 그 위치 저장
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

                if (bi == -1 || books[bi].Bstate != 'N') // 책이 없거나 삭제된 책이면
                {
                    setColor(RED);
                    gotoxy(73, 12); printf("해당 ID의 도서를 찾을 수 없습니다.");
                    setColor(WHITE);
                    gotoxy(74, 14); printf("아무 키나 누르세요...");
                    _getch();
                    continue; // 다시 입력 화면으로
                }

                if (books[bi].total <= 0) // 재고가 없으면
                {
                    setColor(RED);
                    gotoxy(73, 12); printf("해당 도서는 현재 대출 불가입니다.");
                    setColor(WHITE);
                    gotoxy(74, 14); printf("아무 키나 누르세요...");
                    _getch();
                    continue;
                }

                Borrow newBorrow = { 0 }; // 새 대출 기록 만들기
                strcpy(newBorrow.id, borrowId); // 대출할 책 ID 저장
                strcpy(newBorrow.borrowerPhone, currentPhone); // 대출자 전화번호 저장

                getDate(0); // 오늘 날짜
                newBorrow.borrowYear = year;
                newBorrow.borrowMonth = month;
                newBorrow.borrowDay = day;

                getDate(10); // 10일 뒤 날짜
                newBorrow.returnYear = year;
                newBorrow.returnMonth = month;
                newBorrow.returnDay = day;

                newBorrow.state = 1; // 대출중 상태로 저장

                if (manageBorrowFile(NULL, newBorrow, 1, 0) == 1) // 대출 기록 파일에 추가 성공이면
                {
                    books[bi].total--; // 책 재고 줄이기
                    manageBookFile(books, nullbook, 2, bookCount); // 책 파일 전체 저장

                    setColor(GREEN);
                    gotoxy(75, 12); printf("대출이 완료되었습니다.");
                    gotoxy(75, 13); printf("반납 기한 : %d년 %d월 %d일", newBorrow.returnYear, newBorrow.returnMonth, newBorrow.returnDay);
                    setColor(WHITE);
                }
                else // 저장 실패면
                {
                    setColor(RED);
                    gotoxy(76, 12); printf("대출 정보 저장 실패.");
                    setColor(WHITE);
                }

                gotoxy(75, 15); printf("아무 키나 누르세요...");
                _getch();

                return; // 대출 처리 끝
            }

            if (ch == 8) // 백스페이스면
            {
                if (len > 0) // 지울 글자가 있으면
                {
                    len--; // 길이 줄이고
                    borrowId[len] = '\0'; // 끝 표시
                }
                continue;
            }

            if (ch >= '0' && ch <= '9') // 숫자 키면
            {
                if (len < (int)sizeof(borrowId) - 1) // 배열 범위 안이면
                {
                    borrowId[len++] = (char)ch; // 글자 추가
                    borrowId[len] = '\0'; // 끝 표시
                }
                continue;
            }
        }
    }
}

/*
    도서 반납 기능
    내가 빌린 책 목록 보여주고 반납 처리
*/
void handleReturn()
{
    Borrow borrowList[1000] = { 0 }; // 전체 대출 목록
    Borrow nullBorrow = { 0 }; // 파일 읽기용 빈 대출
    Book nullBook = { 0 }; // 파일 읽기용 빈 책

    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0); // 대출 목록 읽기
    int bookCount = manageBookFile(books, nullBook, 0, 0); // 책 목록 읽기

    if (borrowCount == 0) // 대출 기록이 없으면
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

    int userBorrowList[1000]; // 내 대출중 기록의 인덱스 모음
    int userCount = 0; // 내 대출중 개수

    for (int i = 0; i < borrowCount; i++) // 대출 목록 전부 확인
    {
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0 && borrowList[i].state == 1) // 내 번호이고 대출중이면
        {
            userBorrowList[userCount++] = i; // 그 위치 저장
        }
    }

    if (userCount == 0) // 내 대출중이 없으면
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

    getDate(0); // 오늘 날짜 갱신

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

    char titleShort[30]; // 제목 짧게 만든 값
    int maxRows = (userCount < 15) ? userCount : 15; // 최대 15줄까지만 표시

    for (int i = 0; i < maxRows; i++) // 내 대출중 목록 출력
    {
        int idx = userBorrowList[i]; // 실제 borrowList 인덱스

        char fullTitle[50] = "(제목 없음)"; // 책 제목 찾기용
        for (int j = 0; j < bookCount; j++)
        {
            if (strcmp(borrowList[idx].id, books[j].id) == 0) // 같은 책이면
            {
                strcpy(fullTitle, books[j].bookTitle); // 제목 가져오기
                break;
            }
        }

        if (strlen(fullTitle) > 12)
            snprintf(titleShort, sizeof(titleShort), "%.14s...", fullTitle); // 길면 줄이기
        else
            strcpy(titleShort, fullTitle); // 짧으면 그대로

        int overdue = isBeforeDate(borrowList[idx].returnYear, borrowList[idx].returnMonth, borrowList[idx].returnDay, year, month, day); // 연체 확인

        gotoxy(27, 8 + i);
        setColor(WHITE);
        printf(" %2d │%-15s│ %4d-%02d-%02d │ %-4s",
            i + 1,
            titleShort,
            borrowList[idx].returnYear,
            borrowList[idx].returnMonth,
            borrowList[idx].returnDay,
            overdue ? "연체" : "정상"); // 상태 출력
    }

    gotoxy(26, 26); printf("├────────────────────────────────────────┤");
    gotoxy(26, 28); printf("└────────────────────────────────────────┘");
    gotoxy(28, 27); printf("반납할 번호를 입력하세요.");

    gotoxy(72, 9);  printf("반납할 번호를 입력하세요.");
    gotoxy(72, 11); printf("번호 입력 후 Enter : 반납");
    gotoxy(72, 12); printf("0 입력 후 Enter : 취소");

    char input[10]; // 번호 입력 저장
    gotoxy(72, 14);
    printf("번호 : ");
    fgets(input, sizeof(input), stdin); // 입력 받기
    input[strcspn(input, "\n")] = 0; // 엔터 제거

    int select = atoi(input); // 숫자로 변환

    if (select == 0) return; // 0이면 취소

    if (select < 1 || select > userCount) // 범위 밖이면
    {
        setColor(RED);
        gotoxy(72, 16); printf("잘못된 번호 입력입니다.");
        setColor(WHITE);
        gotoxy(72, 18); printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    int idx = userBorrowList[select - 1]; // 선택한 대출 기록 위치

    int overdue = isBeforeDate(borrowList[idx].returnYear, borrowList[idx].returnMonth, borrowList[idx].returnDay, year, month, day); // 연체 확인
    borrowList[idx].state = overdue ? 3 : 2; // 연체면 3, 정상 반납이면 2

    for (int j = 0; j < bookCount; j++) // 책 재고 돌려놓기
    {
        if (strcmp(books[j].id, borrowList[idx].id) == 0) // 같은 책이면
        {
            if (books[j].total < books[j].available) books[j].total++; // 재고 증가
            break;
        }
    }

    if (manageBorrowFile(borrowList, nullBorrow, 2, borrowCount) && manageBookFile(books, nullBook, 2, bookCount)) // 두 파일 저장 성공이면
    {
        setColor(GREEN);
        gotoxy(72, 16); printf("도서가 성공적으로 반납되었습니다!");
        setColor(WHITE);
    }
    else // 저장 실패면
    {
        setColor(RED);
        gotoxy(72, 17); printf("반납 처리 중 오류가 발생했습니다.");
        setColor(WHITE);
    }

    gotoxy(72, 18); printf("계속하려면 아무 키나 누르세요...");
    _getch();
}

/*
    대출 조회 기능 (사용자) (연체 > 대출 > 반납완료 정렬)
    내가 빌린 기록을 날짜와 상태 순으로 보여줌
*/
void viewBorrowHistory()
{
    Borrow borrowList[1000] = { 0 }; // 전체 대출 목록
    Borrow nullborrow = { 0 }; // 파일 읽기용 빈 대출
    Book nullbook = { 0 }; // 파일 읽기용 빈 책

    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0); // 대출 목록 읽기
    int bookCount = manageBookFile(books, nullbook, 0, 0); // 책 목록 읽기

    Borrow userList[1000]; // 내 대출 기록만 모은 배열
    int count1 = 0; // 내 기록 개수

    for (int i = 0; i < borrowCount; i++) // 전체 대출에서 내 기록만 추출
    {
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0) // 내 번호면
        {
            userList[count1++] = borrowList[i]; // userList에 복사
        }
    }

    getDate(0); // 오늘 날짜 갱신
    qsort(userList, count1, sizeof(Borrow), compareBorrowRecords); // 우선순위 기준 정렬

    int startIndex = 0; // 현재 페이지 시작 위치
    char title[31]; // 책 제목 저장
    const int ROWS = 15; // 한 페이지 출력 줄 수

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
        drawBox(50, 3, 34, 3, "대출 내역 조회");

        gotoxy(27, 6);
        printf("ID │제목                         │대출일       │반납 예정일 │상태");
        gotoxy(26, 7);
        printf("├─────────────────────────────────────────────────────────────────────────────────┤");

        int check = 0; // 출력할 기록이 있는지 표시

        getDate(0); // 화면 갱신마다 오늘 날짜 다시 저장

        for (int i = 0; i < ROWS; i++) // 한 페이지 출력
        {
            int recordIndex = startIndex + i; // 실제 userList 인덱스
            if (recordIndex >= count1) // 끝까지 가면
            {
                break;
            }

            check = 1; // 기록 있음 표시

            strcpy(title, "(제목 없음)"); // 제목 기본값
            for (int j = 0; j < bookCount; j++) // 책 제목 찾기
            {
                if (strcmp(userList[recordIndex].id, books[j].id) == 0)
                {
                    strcpy(title, books[j].bookTitle);
                    break;
                }
            }

            int s = userList[recordIndex].state; // 상태 값
            int overdueBorrowing = 0; // 연체 대출중 표시

            if (s == 1) // 대출중일 때만 연체 체크
            {
                overdueBorrowing = isBeforeDate(
                    userList[recordIndex].returnYear,
                    userList[recordIndex].returnMonth,
                    userList[recordIndex].returnDay,
                    year, month, day
                );
            }

            if (s == 1 && overdueBorrowing) // 연체 대출중
            {
                setColor(RED);
            }
            else if (s == 1) // 정상 대출중
            {
                setColor(GREEN);
            }
            else if (s == 2) // 정상 반납
            {
                setColor(GRAY);
            }
            else if (s == 3) // 연체 반납
            {
                setColor(RED);
            }
            else // 알 수 없는 상태
            {
                setColor(WHITE);
            }

            const char* st =
                (s == 1 && overdueBorrowing) ? "연체 대출중" :
                (s == 1) ? "대출 중" :
                (s == 2) ? "정상 반납" :
                (s == 3) ? "연체 반납" : "알수없음"; // 상태 문장 결정

            gotoxy(27, 8 + i);
            printf(" %-2s│%-29s│ %4d-%02d-%02d │ %4d-%02d-%02d │ %s",
                userList[recordIndex].id, title,
                userList[recordIndex].borrowYear,
                userList[recordIndex].borrowMonth,
                userList[recordIndex].borrowDay,
                userList[recordIndex].returnYear,
                userList[recordIndex].returnMonth,
                userList[recordIndex].returnDay,
                st); // 한 줄 출력
        }

        setColor(WHITE);

        if (!check) // 내 기록이 없으면
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

        char key = _getch(); // 키 입력

        if (key == 0 || key == 224) // 특수키면
        {
            key = _getch();
            if (key == LEFT && startIndex >= ROWS) // 왼쪽 이동
            {
                startIndex -= ROWS;
            }
            else if (key == RIGHT && startIndex + ROWS < count1) // 오른쪽 이동
            {
                startIndex += ROWS;
            }
        }
        else if (key == '0') // 0이면 나가기
        {
            return;
        }
    }
}
