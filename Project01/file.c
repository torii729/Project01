#include "Header.h"

/*
    파일 관리 함수 (member.txt)
*/
int manageMemberFile(Member members[], Member newMember, int mode, int memberCount)
{
    FILE* file;
    int count = 0;

    if (mode == 0) // 파일 read
    {
        file = fopen("member.txt", "r");
        if (file == NULL)
        {
            setColor(RED); gotoxy(42, 19); printf("회원 데이터 파일이 없습니다.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }

        while (fscanf(file, "%s %s %s %c", members[count].name, members[count].phone, members[count].password, &members[count].Mstate) == 4)
        {
            count++;
        }

        fclose(file);
        return count;
    }

    else if (mode == 1) // 파일 append
    {
        file = fopen("member.txt", "a");
        if (file == NULL)
        {
            setColor(RED); gotoxy(42, 19); printf("회원 데이터 파일이 없습니다.");
            setColor(WHITE);  gotoxy(42, 20); system("pause");

            return 0;
        }

        if (newMember.Mstate == 0)
        {
            newMember.Mstate = 'N';
        }

        fprintf(file, "\n%s %s %s %c", newMember.name, newMember.phone, newMember.password, newMember.Mstate);
        fclose(file);

        return 1;
    }

    else if (mode == 2) // 파일 덮어쓰기 write
    {
        FILE* tempFile = fopen("tempMember.txt", "w");
        if (tempFile == NULL)
        {
            setColor(RED); gotoxy(42, 19); printf("임시 파일 생성 실패");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }

        for (int i = 0; i < memberCount; i++)
        {
            if (i == 0)
            {
                fprintf(tempFile, "%s %s %s %c",
                    members[i].name,
                    members[i].phone,
                    members[i].password,
                    members[i].Mstate);
            }
            else
            {
                fprintf(tempFile, "\n%s %s %s %c",
                    members[i].name,
                    members[i].phone,
                    members[i].password,
                    members[i].Mstate);
            }
        }

        fclose(tempFile);

        if (remove("member.txt") != 0 || rename("tempMember.txt", "member.txt") != 0)
        {
            setColor(RED); gotoxy(42, 19); printf("파일 갱신 실패.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }
        return 1;
    }

    return 0;
}

/*
    파일 관리 함수 (book.txt)
*/
int manageBookFile(Book books[], Book newBook, int mode, int bookCount)
{
    int count = 0;
    FILE* file;

    if (mode == 0) // 파일 read
    {
        file = fopen("book.txt", "r");
        if (file == NULL)
        {
            setColor(RED);  gotoxy(42, 19); printf("데이터 파일이 없습니다.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }

        // id, 제목, 저자, 출판사, 재고 읽기
        while (fscanf(file, "%s %s %s %s %d %d %c",
            books[count].id,
            books[count].bookTitle,
            books[count].bookAuthor,
            books[count].bookPublish,
            &books[count].total,
            &books[count].available,
            &books[count].Bstate) == 7)
        {
            count++;
        }

        fclose(file);
        return count;
    }

    else if (mode == 1) // 파일 append (새 도서 추가)
    {
        file = fopen("book.txt", "a");
        if (file == NULL)
        {
            setColor(RED); gotoxy(42, 19); printf("데이터 파일이 없습니다.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }

        // 새 도서 정보 + 재고 그대로 저장
        fprintf(file, "\n%s %s %s %s %d %d %c",
            newBook.id,
            newBook.bookTitle,
            newBook.bookAuthor,
            newBook.bookPublish,
            newBook.total,
            newBook.available,
            newBook.Bstate);

        fclose(file);
        return 1;
    }

    else if (mode == 2) // 파일 덮어쓰기 (전체 갱신, 재고 포함)
    {
        FILE* tempBookFile = fopen("tempBook.txt", "w");
        if (tempBookFile == NULL)
        {
            setColor(RED); gotoxy(42, 19); printf("임시 파일 생성 실패함");
            setColor(WHITE); gotoxy(42, 20); system("pause");

            return 0;
        }

        for (int i = 0; i < bookCount; i++)
        {
            if (i == 0)
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
            else
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

        fclose(tempBookFile);

        if (remove("book.txt") != 0 || rename("tempBook.txt", "book.txt") != 0)
        {
            setColor(RED);  gotoxy(42, 19); printf("파일 갱신 실패.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }
        return 1;
    }

    return 0;
}

/*
    파일 관리 함수 (borrowList.txt)
*/
int manageBorrowFile(Borrow borrowList[], Borrow newBorrow, int mode, int borrowCount)
{
    int count = 0;
    FILE* file;

    if (mode == 0) // 파일 읽기
    {
        file = fopen("borrowList.txt", "r");

        if (file == NULL)
        {
            setColor(RED);  gotoxy(42, 19); printf("대출 데이터 파일이 없습니다.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }

        while (fscanf(file, "%s %s %d %d %d %d %d %d %d",
            borrowList[count].id, borrowList[count].borrowerPhone,
            &borrowList[count].borrowYear, &borrowList[count].borrowMonth, &borrowList[count].borrowDay,
            &borrowList[count].returnYear, &borrowList[count].returnMonth, &borrowList[count].returnDay,
            &borrowList[count].state) == 9)
        {
            count++;
        }

        fclose(file);
        return count;
    }
    else if (mode == 1) // 파일 추가
    {
        file = fopen("borrowList.txt", "a");
        if (file == NULL)
        {

            setColor(RED);  gotoxy(42, 19); printf("대출 데이터 파일이 없습니다.");
            setColor(WHITE); gotoxy(42, 20); system("pause");

            return 0;
        }

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

        fclose(file);
        return 1;
    }
    else if (mode == 2) // 파일 덮어쓰기
    {
        FILE* tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL)
        {
            setColor(RED);  gotoxy(42, 19); printf("임시 파일 생성 실패함");
            setColor(WHITE); gotoxy(42, 20); system("pause");

            return 0;
        }

        // borrowCount를 사용해 유효한 항목만 저장할 수 있다

        for (int i = 0; i < borrowCount; i++)
        {
            if (i == 0) // 빈 파일에 최초 저장 시 
            {
                fprintf(tempFile, "%s %s %d %d %d %d %d %d %d",
                    borrowList[i].id, borrowList[i].borrowerPhone,
                    borrowList[i].borrowYear, borrowList[i].borrowMonth, borrowList[i].borrowDay,
                    borrowList[i].returnYear, borrowList[i].returnMonth, borrowList[i].returnDay,
                    borrowList[i].state);
            }
            else
            {
                fprintf(tempFile, "\n%s %s %d %d %d %d %d %d %d",
                    borrowList[i].id, borrowList[i].borrowerPhone,
                    borrowList[i].borrowYear, borrowList[i].borrowMonth, borrowList[i].borrowDay,
                    borrowList[i].returnYear, borrowList[i].returnMonth, borrowList[i].returnDay,
                    borrowList[i].state);
            }
        }

        fclose(tempFile);

        if (remove("borrowList.txt") != 0 || rename("temp.txt", "borrowList.txt") != 0)
        {
            setColor(RED); gotoxy(42, 19); printf("파일 갱신 실패.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }
        return 1;
    }
    return 0;
}