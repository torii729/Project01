#include "Header.h"

#define ADMIN_ID "admin"
#define ADMIN_PW "password!"

#define LEFT 75
#define RIGHT 77

/*
    °ü¸®ÀÚ ·Î±×ÀÎ ±â´É : ¸ÅÅ©·Î »ó¼ö ADMIN_ID, ADMIN_PWÀ¸·Î¸¸ ·Î±×ÀÎ °¡´É
*/
int adminlogin()
{
    char name[20], phone[20], password[20];

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "·Î±×ÀÎ");

    gotoxy(44, 7); printf("¾ÆÀÌµð        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(44, 10); printf("ºñ¹Ð¹øÈ£      : ");
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
        printf("Á¤º¸°¡ ÀÏÄ¡ÇÏÁö ¾Ê½À´Ï´Ù.\n");
        setColor(WHITE);
        gotoxy(39, 23); system("pause");
        return 0;
    }
}

/*
    µµ¼­ Ãß°¡ ±â´É
*/
void addBook()
{
    Book nullbook = { 0 };
    Book newbook = { 0 };
    int  count = manageBookFile(books, nullbook, 0, 0);
    sprintf(newbook.id, "%d", count + 1); // »õ µµ¼­ ID

    int startIndex = 0;
    const int ROWS = 15;

    // 1´Ü°è : µµ¼­ ¸ñ·Ï + ¾È³», ¡ç/¡æ ÆäÀÌÁö ÀÌµ¿, Enter·Î ÀÔ·Â ´Ü°è ÁøÀÔ
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
        drawBox(50, 3, 34, 3, "µµ¼­ Ãß°¡");

        // °¡¿îµ¥ ¹Ú½º(26~67) ¾È¿¡¼­ Ãâ·Â
        gotoxy(27, 6); printf("ID ¦¢Á¦¸ñ                         ¦¢ÀúÀÚ                   ¦¢ÃâÆÇ»ç            ¦¢Àç°í");
        gotoxy(26, 7); printf("¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©");

        for (int i = 0; i < ROWS; i++)
        {
            int idx = startIndex + i;
            if (idx >= count)
            {
                break;
            }

            gotoxy(27, 8 + i);
            setColor(WHITE);
            printf(" %-2s¦¢%-29s¦¢%-23s¦¢%-18s¦¢%2d",
                books[idx].id, books[idx].bookTitle, books[idx].bookAuthor, books[idx].bookPublish, books[idx].total);
        }

        gotoxy(26, 26); printf("¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©");
        gotoxy(26, 28); printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
        gotoxy(28, 27); printf("[¡ç][¡æ] ÆäÀÌÁö ÀÌµ¿   [Enter] µµ¼­ Ãß°¡   [0] µÚ·Î °¡±â");

        int ch = _getch();

        if (ch == 0 || ch == 224)  // ¹æÇâÅ°
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

        if (ch == '0')
        {
            return; // µÚ·Î °¡±â
        }

        if (ch == 13) // Enter ¡æ ÀÔ·Â ´Ü°è
        {
            break;
        }
    }

    // 2´Ü°è : Á¦¸ñ / ÀúÀÚ / ÃâÆÇ»ç ÀÔ·Â
    system("cls");
    setColor(WHITE);
    drawBox(67, 1, 42, 28, "");
    setColor(DarkGreen);   drawBox(16, 1, 11, 3, "");
    setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
    setColor(DarkYellow);  drawBox(16, 7, 11, 3, "");
    setColor(RED);         drawBox(16, 10, 11, 3, "");
    setColor(WHITE);
    drawBox(26, 1, 42, 28, "");
    drawBox(50, 3, 34, 3, "µµ¼­ Ãß°¡");

    gotoxy(32, 7);  printf("»õ µµ¼­ µî·Ï");
    gotoxy(32, 9);  printf("ID        : %s", newbook.id);

    gotoxy(32, 12); printf("Á¦¸ñ      : ");
    fgets(newbook.bookTitle, sizeof(newbook.bookTitle), stdin);
    newbook.bookTitle[strcspn(newbook.bookTitle, "\n")] = 0;

    gotoxy(32, 15); printf("ÀúÀÚ      : ");
    fgets(newbook.bookAuthor, sizeof(newbook.bookAuthor), stdin);
    newbook.bookAuthor[strcspn(newbook.bookAuthor, "\n")] = 0;

    gotoxy(32, 18); printf("ÃâÆÇ»ç    : ");
    fgets(newbook.bookPublish, sizeof(newbook.bookPublish), stdin);
    newbook.bookPublish[strcspn(newbook.bookPublish, "\n")] = 0;

    // »õ µµ¼­ ±âº» Àç°í 1
    newbook.total = 1;

    // °°Àº Ã¥(Á¦¸ñ, ÀúÀÚ, ÃâÆÇ»ç ¸ðµÎ µ¿ÀÏ) ÀÖ´ÂÁö È®ÀÎ
    int c_Index = -1;
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

    if (c_Index != -1)
    {
        // ±âÁ¸ µµ¼­ Àç°í +1 ÈÄ ÆÄÀÏ µ¤¾î¾²±â
        books[c_Index].total += 1;
        result = manageBookFile(books, nullbook, 2, count);
    }
    else
    {
        // »õ·Î¿î µµ¼­·Î Ãß°¡ (Àç°í 1)
        result = manageBookFile(NULL, newbook, 1, 0);
    }

    if (result)
    {
        setColor(GREEN);
        gotoxy(72, 10); printf("µµ¼­ Ãß°¡°¡ ¿Ï·áµÇ¾ú½À´Ï´Ù.");
        setColor(WHITE);
    }
    else
    {
        setColor(RED);
        gotoxy(72, 10); printf("µµ¼­ Ãß°¡ ½ÇÆÐ.");
        setColor(WHITE);
    }

    gotoxy(72, 12); printf("¾Æ¹« Å°³ª ´©¸£¸é µ¹¾Æ°©´Ï´Ù...");
    _getch();
}

/*
    µµ¼­ »èÁ¦ ±â´É
*/
void removeBook()
{
    Book nullbook = { 0 };
    int startIndex = 0;
    int removeIndex = 0;
    char input1[10] = { 0 };
    char input2[10] = { 0 };

    int count = manageBookFile(books, nullbook, 0, 0); // µµ¼­ ¸ñ·Ï ÀÐ±â

    if (count == 0)
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
        drawBox(50, 3, 34, 3, "µµ¼­ »èÁ¦");

        gotoxy(72, 12); printf("µµ¼­ µ¥ÀÌÅÍ°¡ ¾ø½À´Ï´Ù.");
        gotoxy(72, 14); printf("¾Æ¹« Å°³ª ´©¸£¸é µ¹¾Æ°©´Ï´Ù...");
        _getch();
        return;
    }

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
        drawBox(50, 3, 34, 3, "µµ¼­ »èÁ¦");

        // °¡¿îµ¥ ¹Ú½º(26~67) ¾È¿¡¼­ addBook()°ú µ¿ÀÏ Æ÷¸ËÀ¸·Î Ãâ·Â
        gotoxy(27, 6); printf("ID ¦¢Á¦¸ñ                         ¦¢ÀúÀÚ                   ¦¢ÃâÆÇ»ç            ¦¢Àç°í");
        gotoxy(26, 7); printf("¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©");

        for (int i = 0; i < ROWS; i++)
        {
            int bookIndex = startIndex + i;
            if (bookIndex >= count)
            {
                break;
            }

            gotoxy(27, 8 + i);
            setColor(WHITE);
            printf(" %-2s¦¢%-29s¦¢%-23s¦¢%-18s¦¢%2d",
                books[bookIndex].id,
                books[bookIndex].bookTitle,
                books[bookIndex].bookAuthor,
                books[bookIndex].bookPublish,
                books[bookIndex].total);
        }

        gotoxy(26, 26); printf("¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©");
        gotoxy(26, 28); printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
        gotoxy(28, 27); printf("[¡ç][¡æ] ÆäÀÌÁö ÀÌµ¿   [1] »èÁ¦ÇÒ µµ¼­ ÀÔ·Â   [0] µÚ·Î °¡±â");

        char key = _getch();

        if (key == 0 || key == -32)  // ¹æÇâÅ°
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
        else if (key == '0')  // µÚ·Î°¡±â
        {
            return;
        }
        else if (key == '1')
        {
            // »èÁ¦ÇÒ µµ¼­ ¹øÈ£ ÀÔ·Â
            gotoxy(28, 27); printf("                                               ");
            gotoxy(28, 27); printf("»èÁ¦ÇÒ µµ¼­ ¹øÈ£(ID) ÀÔ·Â : ");
            fgets(input1, sizeof(input1), stdin);
            input1[strcspn(input1, "\n")] = 0;

            int select = atoi(input1);

            if (select > count || select < 1)
            {
                setColor(RED);
                gotoxy(72, 10); printf("Àß¸øµÈ ¹øÈ£ÀÔ´Ï´Ù.");
                setColor(WHITE);
                gotoxy(72, 12); printf("¾Æ¹« Å°³ª ´©¸£¸é µ¹¾Æ°©´Ï´Ù...");
                _getch();
                continue;
            }

            removeIndex = select - 1;

            // È®ÀÎ È­¸é
            system("cls");
            setColor(WHITE);
            drawBox(67, 1, 42, 28, "");
            setColor(DarkGreen);   drawBox(16, 1, 11, 3, "");
            setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
            setColor(DarkYellow);  drawBox(16, 7, 11, 3, "");
            setColor(RED);         drawBox(16, 10, 11, 3, "");
            setColor(WHITE);
            drawBox(26, 1, 42, 28, "");
            drawBox(50, 3, 34, 3, "µµ¼­ »èÁ¦ È®ÀÎ");

            setColor(RED);
            gotoxy(32, 7);  printf("Á¤¸»·Î »èÁ¦ÇÏ½Ã°Ú½À´Ï±î?");
            setColor(WHITE);
            gotoxy(32, 9);  printf("Á¦¸ñ : %s", books[removeIndex].bookTitle);
            gotoxy(32, 10); printf("ÀúÀÚ : %s", books[removeIndex].bookAuthor);
            gotoxy(32, 11); printf("ÃâÆÇ»ç : %s", books[removeIndex].bookPublish);

            gotoxy(32, 14); printf("[Y] ¿¹  [N] ¾Æ´Ï¿À(µÚ·Î °¡±â) : ");
            fgets(input2, sizeof(input2), stdin);
            input2[strcspn(input2, "\n")] = 0;

            if (input2[0] == 'y' || input2[0] == 'Y')
            {
                // ÇÑ Ä­¾¿ ´ç°Ü¼­ »èÁ¦
                for (int i = removeIndex; i < count - 1; i++)
                {
                    books[i] = books[i + 1];
                }
                count--; // Ç×¸ñ ¼ö °¨¼Ò

                // ID ÀçºÎ¿©
                for (int i = 0; i < count; i++)
                {
                    snprintf(books[i].id, sizeof(books[i].id), "%d", i + 1);
                }

                // ÆÄÀÏ ÀçÀúÀå
                if (manageBookFile(books, nullbook, 2, count))
                {
                    setColor(GREEN);
                    gotoxy(72, 10); printf("µµ¼­°¡ »èÁ¦µÇ¾ú½À´Ï´Ù.");
                    setColor(WHITE);
                }
                else
                {
                    setColor(RED);
                    gotoxy(72, 10); printf("ÆÄÀÏ °»½Å ½ÇÆÐ.");
                    setColor(WHITE);
                }

                gotoxy(72, 12); printf("¾Æ¹« Å°³ª ´©¸£¸é µ¹¾Æ°©´Ï´Ù...");
                _getch();
                return;
            }
            else if (input2[0] == 'n' || input2[0] == 'N')
            {
                gotoxy(72, 10); printf("Ãë¼ÒµÇ¾ú½À´Ï´Ù.");
                gotoxy(72, 12); printf("¾Æ¹« Å°³ª ´©¸£¸é µ¹¾Æ°©´Ï´Ù...");
                _getch();
                continue;
            }
            else
            {
                setColor(RED);
                gotoxy(72, 10); printf("Àß¸øµÈ ÀÔ·ÂÀÔ´Ï´Ù.");
                setColor(WHITE);
                gotoxy(72, 12); printf("¾Æ¹« Å°³ª ´©¸£¸é µ¹¾Æ°©´Ï´Ù...");
                _getch();
                continue;
            }
        }
    }
}

/*
    ´ëÃâ Á¶È¸ ±â´É (°ü¸®ÀÚ) (¿¬Ã¼ > ´ëÃâ > ¹Ý³³¿Ï·á Á¤·Ä ¤¡¤¡)
*/
void viewBorrowRecords()
{
    Borrow borrowList[1000] = { 0 };
    Book books[1000] = { 0 };
    Borrow nullborrow = { 0 };
    Book nullbook = { 0 };

    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0);
    int bookCount = manageBookFile(books, nullbook, 0, 0);

    // state ±âÁØ ³»¸²Â÷¼ø Á¤·Ä (¿¬Ã¼ > ´ëÃâ Áß > ¹Ý³³ ¿Ï·á)
    for (int i = 0; i < borrowCount - 1; i++)
    {
        for (int j = i + 1; j < borrowCount; j++)
        {
            if (borrowList[i].state < borrowList[j].state)
            {
                Borrow temp = borrowList[i];
                borrowList[i] = borrowList[j];
                borrowList[j] = temp;
            }
        }
    }

    int startIndex = 0;
    const int ROWS = 15;
    char titleShort[32];

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
        drawBox(50, 3, 34, 3, "ÀüÃ¼ ´ëÃâ ³»¿ª");

        gotoxy(27, 6);
        printf("ID ¦¢Á¦¸ñ                         ¦¢ÀüÈ­¹øÈ£       ¦¢¹Ý³³ ¿¹Á¤ÀÏ ¦¢»óÅÂ");
        gotoxy(26, 7);
        printf("¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©");

        int check = 0;

        for (int i = 0; i < ROWS; i++)
        {
            int recordIndex = startIndex + i;
            if (recordIndex >= borrowCount)
                break;

            check = 1;

            // Á¦¸ñ Ã£±â
            char fullTitle[50] = "Á¦¸ñ¾øÀ½";
            for (int j = 0; j < bookCount; j++)
            {
                if (strcmp(borrowList[recordIndex].id, books[j].id) == 0)
                {
                    strcpy(fullTitle, books[j].bookTitle);
                    break;
                }
            }

            if (strlen(fullTitle) > 29)
                snprintf(titleShort, sizeof(titleShort), "%.29s", fullTitle);
            else
                strcpy(titleShort, fullTitle);

            // »óÅÂº° »ö»ó
            if (borrowList[recordIndex].state == 2)
                setColor(RED); // ¿¬Ã¼
            else if (borrowList[recordIndex].state == 1)
                setColor(GREEN); // ´ëÃâ Áß
            else if (borrowList[recordIndex].state == 0)
                setColor(GRAY); // ¹Ý³³ ¿Ï·á
            else
                setColor(WHITE);

            gotoxy(27, 8 + i);
            printf(" %-2s¦¢%-29s¦¢%-13s¦¢ %4d-%02d-%02d ¦¢ %s",
                borrowList[recordIndex].id,
                titleShort,
                borrowList[recordIndex].borrowerPhone,
                borrowList[recordIndex].returnYear,
                borrowList[recordIndex].returnMonth,
                borrowList[recordIndex].returnDay,
                borrowList[recordIndex].state == 0 ? "¹Ý³³ ¿Ï·á"
                : (borrowList[recordIndex].state == 1 ? "´ëÃâ Áß" : "¿¬Ã¼ Áß"));
        }

        setColor(WHITE);
        if (check == 0)
        {
            gotoxy(27, 8);
            printf("´ëÃâ ³»¿ªÀÌ ¾ø½À´Ï´Ù.");
        }

        gotoxy(26, 26);
        printf("¦§¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦©");
        gotoxy(26, 28);
        printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
        gotoxy(28, 27);
        printf("[¡ç][¡æ] ÆäÀÌÁö ÀÌµ¿   [0] µÚ·Î °¡±â");

        char key = _getch();

        if (key == 0 || key == 224) // ¹æÇâÅ°
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
        else if (key == '0') // µÚ·Î °¡±â
        {
            return;
        }
    }
}
