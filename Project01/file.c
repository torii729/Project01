#include "Enum.h"
#include "Header.h"
#include "Struct.h"

/*
    파일 관리 함수 (member.txt)
*/
int manageMemberFile(Member members[], Member newMember, int mode)
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

        while (fscanf(file, "%s %s %s", members[count].name, members[count].phone, members[count].password) == 3)
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

        fprintf(file, "\n%s %s %s", newMember.name, newMember.phone, newMember.password);
        fclose(file);

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
            setColor(RED); gotoxy(42, 19); printf("데이터 파일이 없습니다.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }

        while (fscanf(file, "%s %s %s %s", books[count].id, books[count].bookTitle, books[count].bookAuthor, books[count].bookPublish) == 4)
        {
            count++;
        }

        fclose(file);
        return count;
    }
    else if (mode == 1) // 파일 append
    {
        // 도서 추가
        file = fopen("book.txt", "a");
        if (file == NULL)
        {
            setColor(RED); gotoxy(42, 19); printf("데이터 파일이 없습니다.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }

        fprintf(file, "\n%s %s %s %s", newBook.id, newBook.bookTitle, newBook.bookAuthor, newBook.bookPublish);
        fclose(file);

        return 1;
    }

    else if (mode == 2) // 파일 덮어쓰기
    {
        FILE* tempBookFile = fopen("tempBook.txt", "w");
        if (tempBookFile == NULL)
        {
            setColor(RED);   gotoxy(42, 19); printf("임시 파일 생성 실패함");
            setColor(WHITE); gotoxy(42, 20); system("pause");

            return 0;
        }

        // borrowCount를 사용해 유효한 항목만 저장할 수 있다고 함

        for (int i = 0; i < bookCount; i++)
        {
            if (i == 0) // 빈 파일에 최초 저장 시 
            {
                fprintf(tempBookFile, "%s %s %s %s", books[i].id, books[i].bookTitle, books[i].bookAuthor, books[i].bookPublish);
            }
            else
            {
                fprintf(tempBookFile, "\n%s %s %s %s", books[i].id, books[i].bookTitle, books[i].bookAuthor, books[i].bookPublish);
            }
        }
        fclose(tempBookFile);

        if (remove("book.txt") != 0 || rename("tempBook.txt", "book.txt") != 0)
        {
            setColor(RED); gotoxy(42, 19); printf("파일 갱신 실패.");
            setColor(WHITE); gotoxy(42, 20); system("pause");
            return 0;
        }
        return 1;
    }
    return 0;
}
