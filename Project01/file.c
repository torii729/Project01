#include "Header.h"

/*
    파일 관리 함수 (member.txt)
    회원 정보를 파일에서 읽거나 파일에 저장하는 함수
    mode 값에 따라 읽기, 추가, 전체 저장으로 나뉨
*/
int manageMemberFile(Member members[], Member newMember, int mode, int memberCount)
{
    FILE* file; // 파일을 열 때 쓰는 손잡이 같은 변수
    int count = 0; // 읽어온 회원 수를 세는 변수

    if (mode == 0) // 회원 파일 읽기 모드
    {
        file = fopen("member.txt", "r"); // member.txt를 읽기용으로 열기
        if (file == NULL) // 파일이 없거나 못 열면
        {
            setColor(RED); gotoxy(42, 19); printf("회원 데이터 파일이 없습니다."); // 파일 없음 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤
            return 0; // 읽은 회원이 없다는 뜻으로 0 반환
        }

        // 파일에서 한 줄씩 회원 정보 4개를 읽어 members 배열에 저장
        while (fscanf(file, "%s %s %s %c", members[count].name, members[count].phone, members[count].password, &members[count].Mstate) == 4)
        {
            count++; // 한 명 읽었으니 개수 증가
        }

        fclose(file); // 파일 닫기
        return count; // 읽은 회원 수 반환
    }

    else if (mode == 1) // 회원 파일에 새 회원 추가 모드
    {
        file = fopen("member.txt", "a"); // member.txt를 뒤에 이어쓰기용으로 열기
        if (file == NULL) // 파일을 못 열면
        {
            setColor(RED); gotoxy(42, 19); printf("회원 데이터 파일이 없습니다."); // 파일 없음 안내
            setColor(WHITE);  gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤

            return 0; // 실패 의미로 0 반환
        }

        if (newMember.Mstate == 0) // 상태 값이 비어 있으면
        {
            newMember.Mstate = 'N'; // 기본 상태로 N 넣기
        }

        // 새 회원 정보를 파일 맨 아래에 한 줄 추가
        fprintf(file, "\n%s %s %s %c", newMember.name, newMember.phone, newMember.password, newMember.Mstate);
        fclose(file); // 파일 닫기

        return 1; // 성공 의미로 1 반환
    }

    else if (mode == 2) // 회원 파일 전체 다시 저장 모드
    {
        FILE* tempFile = fopen("tempMember.txt", "w"); // 임시 파일 새로 만들기
        if (tempFile == NULL) // 임시 파일을 못 만들면
        {
            setColor(RED); gotoxy(42, 19); printf("임시 파일 생성 실패"); // 실패 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤
            return 0; // 실패 의미로 0 반환
        }

        // members 배열에 있는 회원들을 임시 파일에 전부 다시 쓰기
        for (int i = 0; i < memberCount; i++)
        {
            if (i == 0) // 첫 줄은 줄바꿈 없이 저장
            {
                fprintf(tempFile, "%s %s %s %c",
                    members[i].name,
                    members[i].phone,
                    members[i].password,
                    members[i].Mstate);
            }
            else // 두 번째 줄부터는 줄바꿈 후 저장
            {
                fprintf(tempFile, "\n%s %s %s %c",
                    members[i].name,
                    members[i].phone,
                    members[i].password,
                    members[i].Mstate);
            }
        }

        fclose(tempFile); // 임시 파일 닫기

        // 기존 member.txt 삭제 후 임시 파일 이름을 member.txt로 바꾸기
        if (remove("member.txt") != 0 || rename("tempMember.txt", "member.txt") != 0)
        {
            setColor(RED); gotoxy(42, 19); printf("파일 갱신 실패."); // 바꾸기 실패 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤
            return 0; // 실패 의미로 0 반환
        }
        return 1; // 성공 의미로 1 반환
    }

    return 0; // mode가 이상하면 실패 의미로 0 반환
}

/*
    파일 관리 함수 (book.txt)
    책 정보를 파일에서 읽거나 파일에 저장하는 함수
    mode 값에 따라 읽기, 추가, 전체 저장으로 나뉨
*/
int manageBookFile(Book books[], Book newBook, int mode, int bookCount)
{
    int count = 0; // 읽어온 책 수를 세는 변수
    FILE* file; // 파일 손잡이 변수

    if (mode == 0) // 책 파일 읽기 모드
    {
        file = fopen("book.txt", "r"); // book.txt를 읽기용으로 열기
        if (file == NULL) // 파일이 없거나 못 열면
        {
            setColor(RED);  gotoxy(42, 19); printf("데이터 파일이 없습니다."); // 파일 없음 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤
            return 0; // 읽은 책이 없다는 뜻으로 0 반환
        }

        // id, 제목, 저자, 출판사, 재고 읽기
        // 파일에서 한 줄씩 책 정보 7개를 읽어 books 배열에 저장
        while (fscanf(file, "%s %s %s %s %d %d %c",
            books[count].id,
            books[count].bookTitle,
            books[count].bookAuthor,
            books[count].bookPublish,
            &books[count].total,
            &books[count].available,
            &books[count].Bstate) == 7)
        {
            count++; // 한 권 읽었으니 개수 증가
        }

        fclose(file); // 파일 닫기
        return count; // 읽은 책 수 반환
    }

    else if (mode == 1) // 책 파일에 새 책 추가 모드
    {
        file = fopen("book.txt", "a"); // book.txt를 뒤에 이어쓰기용으로 열기
        if (file == NULL) // 파일을 못 열면
        {
            setColor(RED); gotoxy(42, 19); printf("데이터 파일이 없습니다."); // 파일 없음 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤
            return 0; // 실패 의미로 0 반환
        }

        // 새 도서 정보 + 재고 그대로 저장
        // 새 책 정보를 파일 맨 아래에 한 줄 추가
        fprintf(file, "\n%s %s %s %s %d %d %c",
            newBook.id,
            newBook.bookTitle,
            newBook.bookAuthor,
            newBook.bookPublish,
            newBook.total,
            newBook.available,
            newBook.Bstate);

        fclose(file); // 파일 닫기
        return 1; // 성공 의미로 1 반환
    }

    else if (mode == 2) // 책 파일 전체 다시 저장 모드
    {
        FILE* tempBookFile = fopen("tempBook.txt", "w"); // 임시 책 파일 새로 만들기
        if (tempBookFile == NULL) // 임시 파일을 못 만들면
        {
            setColor(RED); gotoxy(42, 19); printf("임시 파일 생성 실패함"); // 실패 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤

            return 0; // 실패 의미로 0 반환
        }

        // books 배열에 있는 책들을 임시 파일에 전부 다시 쓰기
        for (int i = 0; i < bookCount; i++)
        {
            if (i == 0) // 첫 줄은 줄바꿈 없이 저장
            {
                fprintf(tempBookFile, "%s %s %s %s %d %d %c",
                    books[i].id,
                    books[i].bookTitle,
                    books[i].bookAuthor,
                    books[i].bookPublish,
                    books[i].total,
                    books[i].available,
                    books[i].Bstate);
            }
            else // 두 번째 줄부터는 줄바꿈 후 저장
            {
                fprintf(tempBookFile, "\n%s %s %s %s %d %d %c",
                    books[i].id,
                    books[i].bookTitle,
                    books[i].bookAuthor,
                    books[i].bookPublish,
                    books[i].total,
                    books[i].available,
                    books[i].Bstate);
            }
        }

        fclose(tempBookFile); // 임시 파일 닫기

        // 기존 book.txt 삭제 후 임시 파일 이름을 book.txt로 바꾸기
        if (remove("book.txt") != 0 || rename("tempBook.txt", "book.txt") != 0)
        {
            setColor(RED);  gotoxy(42, 19); printf("파일 갱신 실패."); // 바꾸기 실패 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤
            return 0; // 실패 의미로 0 반환
        }
        return 1; // 성공 의미로 1 반환
    }

    return 0; // mode가 이상하면 실패 의미로 0 반환
}

/*
    파일 관리 함수 (borrowList.txt)
    대출 기록을 파일에서 읽거나 파일에 저장하는 함수
    mode 값에 따라 읽기, 추가, 전체 저장으로 나뉨
*/
int manageBorrowFile(Borrow borrowList[], Borrow newBorrow, int mode, int borrowCount)
{
    int count = 0; // 읽어온 대출 기록 수를 세는 변수
    FILE* file; // 파일 손잡이 변수

    if (mode == 0) // 대출 파일 읽기 모드
    {
        file = fopen("borrowList.txt", "r"); // borrowList.txt 읽기용으로 열기

        if (file == NULL) // 파일이 없거나 못 열면
        {
            setColor(RED);  gotoxy(42, 19); printf("대출 데이터 파일이 없습니다."); // 파일 없음 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤
            return 0; // 읽은 기록이 없다는 뜻으로 0 반환
        }

        // 파일에서 한 줄씩 대출 정보 9개를 읽어 borrowList 배열에 저장
        while (fscanf(file, "%s %s %d %d %d %d %d %d %d",
            borrowList[count].id, borrowList[count].borrowerPhone,
            &borrowList[count].borrowYear, &borrowList[count].borrowMonth, &borrowList[count].borrowDay,
            &borrowList[count].returnYear, &borrowList[count].returnMonth, &borrowList[count].returnDay,
            &borrowList[count].state) == 9)
        {
            count++; // 한 건 읽었으니 개수 증가
        }

        fclose(file); // 파일 닫기
        return count; // 읽은 대출 기록 수 반환
    }
    else if (mode == 1) // 대출 파일에 새 기록 추가 모드
    {
        file = fopen("borrowList.txt", "a"); // borrowList.txt를 뒤에 이어쓰기용으로 열기
        if (file == NULL) // 파일을 못 열면
        {

            setColor(RED);  gotoxy(42, 19); printf("대출 데이터 파일이 없습니다."); // 파일 없음 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤

            return 0; // 실패 의미로 0 반환
        }

        // 새 대출 기록을 파일 맨 아래에 한 줄 추가
        fprintf(file, "\n%s %s %d %d %d %d %d %d %d",
            newBorrow.id,
            newBorrow.borrowerPhone,
            newBorrow.borrowYear,
            newBorrow.borrowMonth,
            newBorrow.borrowDay,
            newBorrow.returnYear,
            newBorrow.returnMonth,
            newBorrow.returnDay,
            newBorrow.state);

        fclose(file); // 파일 닫기
        return 1; // 성공 의미로 1 반환
    }
    else if (mode == 2) // 대출 파일 전체 다시 저장 모드
    {
        FILE* tempFile = fopen("temp.txt", "w"); // 임시 대출 파일 새로 만들기
        if (tempFile == NULL) // 임시 파일을 못 만들면
        {
            setColor(RED);  gotoxy(42, 19); printf("임시 파일 생성 실패함"); // 실패 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤

            return 0; // 실패 의미로 0 반환
        }

        // borrowCount를 사용해 유효한 항목만 저장할 수 있다
        // borrowList 배열의 앞부분 borrowCount개만 저장

        for (int i = 0; i < borrowCount; i++)
        {
            if (i == 0) // 첫 줄은 줄바꿈 없이 저장
            {
                fprintf(tempFile, "%s %s %d %d %d %d %d %d %d",
                    borrowList[i].id, borrowList[i].borrowerPhone,
                    borrowList[i].borrowYear, borrowList[i].borrowMonth, borrowList[i].borrowDay,
                    borrowList[i].returnYear, borrowList[i].returnMonth, borrowList[i].returnDay,
                    borrowList[i].state);
            }
            else // 두 번째 줄부터는 줄바꿈 후 저장
            {
                fprintf(tempFile, "\n%s %s %d %d %d %d %d %d %d",
                    borrowList[i].id, borrowList[i].borrowerPhone,
                    borrowList[i].borrowYear, borrowList[i].borrowMonth, borrowList[i].borrowDay,
                    borrowList[i].returnYear, borrowList[i].returnMonth, borrowList[i].returnDay,
                    borrowList[i].state);
            }
        }

        fclose(tempFile); // 임시 파일 닫기

        // 기존 borrowList.txt 삭제 후 임시 파일 이름을 borrowList.txt로 바꾸기
        if (remove("borrowList.txt") != 0 || rename("temp.txt", "borrowList.txt") != 0)
        {
            setColor(RED); gotoxy(42, 19); printf("파일 갱신 실패."); // 바꾸기 실패 안내
            setColor(WHITE); gotoxy(42, 20); system("pause"); // 화면 잠깐 멈춤
            return 0; // 실패 의미로 0 반환
        }
        return 1; // 성공 의미로 1 반환
    }
    return 0; // mode가 이상하면 실패 의미로 0 반환
}
