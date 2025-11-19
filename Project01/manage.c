#include "Header.h"

#define ADMIN_ID "admin"
#define ADMIN_PW "password!"

#define LEFT 75
#define RIGHT 77

/*
    綠掖 л熱 (渠轎 晦煙 寡翮 borrowList蒂 薑溺ж朝 睡碟)
*/
int compareBorrowRecords(const void* a, const void* b)
{
    const Borrow* A = (const Borrow*)a;
    const Borrow* B = (const Borrow*)b;

    int overA = 0;
    int overB = 0;

    // 渠轎醞檣 晦煙虜 陳瞼煎 翱羹 渠轎醞 罹睡 っ薑
    if (A->state == 1)
    {
        if (isBeforeDate(A->returnYear, A->returnMonth, A->returnDay, year, month, day))
        {
            overA = 1;
        }
    }
    if (B->state == 1)
    {
        if (isBeforeDate(B->returnYear, B->returnMonth, B->returnDay, year, month, day))
        {
            overB = 1;
        }
    }

    /*
        薑溺 辦摹牖嬪 斜瑜
        3 : 翱羹 渠轎醞
        2 : 薑鼻 渠轎醞
        1 : 翱羹 奩陶
        0 : 薑鼻 奩陶
    */
    int groupA = 0;
    int groupB = 0;

    if (A->state == 1 && overA == 1)
    {
        groupA = 3;
    }
    else if (A->state == 1)
    {
        groupA = 2;
    }
    else if (A->state == 3)
    {
        groupA = 1;
    }
    else
    {
        groupA = 0;
    }

    if (B->state == 1 && overB == 1)
    {
        groupB = 3;
    }
    else if (B->state == 1)
    {
        groupB = 2;
    }
    else if (B->state == 3)
    {
        groupB = 1;
    }
    else
    {
        groupB = 0;
    }

    // 辦摹牖嬪 堪擎 斜瑜檜 試盪 螃紫煙 頂葡離牖 薑溺
    if (groupA != groupB)
    {
        return groupB - groupA;
    }

    // 偽擎 斜瑜檜賊 奩陶 蕨薑橾檜 緒艇 牖
    if (A->returnYear != B->returnYear)
    {
        return A->returnYear - B->returnYear;
    }
    if (A->returnMonth != B->returnMonth)
    {
        return A->returnMonth - B->returnMonth;
    }
    if (A->returnDay != B->returnDay)
    {
        return A->returnDay - B->returnDay;
    }

    // 斜楚紫 偽戲賊 ID 濛擎 牖
    return atoi(A->id) - atoi(B->id);
}

/*
    婦葬濠 煎斜檣 晦棟 : 衙觼煎 鼻熱 ADMIN_ID, ADMIN_PW戲煎虜 煎斜檣 陛棟
*/
int adminlogin()
{
    char name[20], password[20];

    system("cls");
    drawMainMenu();

    drawBox(36, 1, 42, 28, "");
    drawBox(40, 3, 34, 3, "煎斜檣");

    gotoxy(44, 7); printf("嬴檜蛤        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(44, 10); printf("綠塵廓��      : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(name, ADMIN_ID) == 0 && strcmp(password, ADMIN_PW) == 0)
    {
        strcpy(currentUser, name);
        return 1;
    }
    else
    {
        gotoxy(39, 22);
        setColor(RED);
        printf("薑爾陛 橾纂ж雖 彊蝗棲棻.");
        setColor(WHITE);
        gotoxy(39, 23);
        system("pause");
        return 0;
    }
}

/*
    紫憮 蹺陛 晦棟
*/
void addBook()
{
    Book nullbook = { 0 };
    Book newbook = { 0 };

    int count = manageBookFile(books, nullbook, 0, 0);

    int maxId = 0;
    for (int i = 0; i < count; i++)
    {
        int v = atoi(books[i].id);
        if (v > maxId)
        {
            maxId = v;
        }
    }
    sprintf(newbook.id, "%d", maxId + 1);

    int startIndex = 0;
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
        drawBox(50, 3, 34, 3, "紫憮 蹺陛");

        gotoxy(27, 6); printf("ID 弛薯跡                         弛盪濠                   弛轎っ餌            弛營堅");
        gotoxy(26, 7); printf("戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣");

        for (int i = 0; i < ROWS; i++)
        {
            int idx = startIndex + i;
            if (idx >= count)
            {
                break;
            }
            if (books[idx].Bstate != 'N')
            {
                continue;
            }

            gotoxy(27, 8 + i);
            setColor(WHITE);
            printf(" %-2s弛%-29s弛%-23s弛%-18s弛%2d",
                books[idx].id,
                books[idx].bookTitle,
                books[idx].bookAuthor,
                books[idx].bookPublish,
                books[idx].total);
        }

        gotoxy(26, 26); printf("戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣");
        gotoxy(26, 28); printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
        gotoxy(28, 27); printf("[∠][⊥] む檜雖 檜翕   [Enter] 紫憮 蹺陛   [0] 菴煎 陛晦");

        int ch = _getch();

        if (ch == 0 || ch == 224)
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
            return;
        }

        if (ch == 13)
        {
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
    drawBox(26, 1, 42, 28, "");
    drawBox(50, 3, 34, 3, "紫憮 蹺陛");

    gotoxy(32, 7); printf("億 紫憮 蛔煙");
    gotoxy(32, 9); printf("ID        : %s", newbook.id);

    while (1)
    {
        gotoxy(32, 12); printf("薯跡      : ");
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
            gotoxy(30, 19); printf("檜葷擎 奢寥橾 熱 橈蝗棲棻.");
            setColor(WHITE);
            gotoxy(30, 20);
            system("pause");
            continue;
        }
        break;
    }

    while (1)
    {
        gotoxy(32, 15); printf("盪濠      : ");
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
            gotoxy(32, 19); printf("薯跡擎 奢寥橾 熱 橈蝗棲棻.");
            setColor(WHITE);
            gotoxy(32, 20);
            system("pause");
            continue;
        }
        break;
    }

    while (1)
    {
        gotoxy(32, 18); printf("轎っ餌    : ");
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
            gotoxy(32, 19); printf("轎っ餌朝 奢寥橾 熱 橈蝗棲棻.");
            setColor(WHITE);
            gotoxy(32, 20);
            system("pause");
            continue;
        }
        break;
    }


    newbook.available = 1;
    newbook.total = 1;
    newbook.Bstate = 'N';

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
        books[c_Index].available += 1;
        books[c_Index].total += 1;
        books[c_Index].Bstate = 'N';
        result = manageBookFile(books, nullbook, 2, count);
    }
    else
    {
        result = manageBookFile(NULL, newbook, 1, 0);
    }

    if (result)
    {
        setColor(GREEN);
        gotoxy(72, 10); printf("紫憮 蹺陛陛 諫猿腎歷蝗棲棻.");
        setColor(WHITE);
    }
    else
    {
        setColor(RED);
        gotoxy(72, 10); printf("紫憮 蹺陛 褒ぬ.");
        setColor(WHITE);
    }

    gotoxy(72, 12); printf("嬴鼠 酈釭 援腦賊 給嬴骨棲棻...");
    _getch();
}

/*
    紫憮 餉薯 晦棟
*/
void removeBook()
{
    Book nullbook = { 0 };
    Borrow nullborrow = { 0 };
    Borrow borrowList[1000] = { 0 };

    int startIndex = 0;
    char input1[10] = { 0 };
    char input2[10] = { 0 };

    int count = manageBookFile(books, nullbook, 0, 0);
    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0);

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
        drawBox(50, 3, 34, 3, "紫憮 餉薯");

        gotoxy(72, 12); printf("紫憮 等檜攪陛 橈蝗棲棻.");
        gotoxy(72, 14); printf("嬴鼠 酈釭 援腦賊 給嬴骨棲棻...");
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
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "紫憮 餉薯");

        gotoxy(27, 6); printf("ID 弛薯跡                         弛盪濠                   弛轎っ餌            弛營堅");
        gotoxy(26, 7); printf("戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣");

        for (int i = 0; i < ROWS; i++)
        {
            int bookIndex = startIndex + i;
            if (bookIndex >= count)
            {
                break;
            }
            if (books[bookIndex].Bstate != 'N')
            {
                continue;
            }

            gotoxy(27, 8 + i);
            setColor(WHITE);
            printf(" %-2s弛%-29s弛%-23s弛%-18s弛%2d",
                books[bookIndex].id,
                books[bookIndex].bookTitle,
                books[bookIndex].bookAuthor,
                books[bookIndex].bookPublish,
                books[bookIndex].total);
        }

        gotoxy(26, 26); printf("戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣");
        gotoxy(26, 28); printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
        gotoxy(28, 27); printf("[∠][⊥] む檜雖 檜翕   [1] 餉薯й 紫憮 殮溘   [0] 菴煎 陛晦");

        char key = _getch();

        if (key == 0 || key == -32)
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
        else if (key == '0')
        {
            return;
        }
        else if (key == '1')
        {
            gotoxy(28, 27); printf("                                                           ");
            gotoxy(28, 27); printf("餉薯й 紫憮 ID 殮溘 : ");
            fgets(input1, sizeof(input1), stdin);
            input1[strcspn(input1, "\n")] = 0;

            int removeIndex = -1;
            for (int i = 0; i < count; i++)
            {
                if (books[i].Bstate == 'N' && strcmp(books[i].id, input1) == 0)
                {
                    removeIndex = i;
                    break;
                }
            }

            if (removeIndex == -1)
            {
                setColor(RED);
                gotoxy(72, 10); printf("п渡 ID曖 紫憮蒂 瓊擊 熱 橈蝗棲棻.");
                setColor(WHITE);
                gotoxy(72, 12); printf("嬴鼠 酈釭 援腦撮蹂...");
                _getch();
                continue;
            }

            int borrowingNow = 0;
            for (int i = 0; i < borrowCount; i++)
            {
                if (strcmp(borrowList[i].id, books[removeIndex].id) == 0 && borrowList[i].state == 1)
                {
                    borrowingNow = 1;
                    break;
                }
            }

            if (borrowingNow)
            {
                setColor(RED);
                gotoxy(72, 10); printf("⑷營 渠轎 醞檣 紫憮朝 餉薯й 熱 橈蝗棲棻.");
                setColor(WHITE);
                gotoxy(72, 12); printf("嬴鼠 酈釭 援腦撮蹂...");
                _getch();
                continue;
            }

            system("cls");
            setColor(WHITE);
            drawBox(67, 1, 42, 28, "");
            setColor(DarkGreen); drawBox(16, 1, 11, 3, "");
            setColor(darkSkyBlue); drawBox(16, 4, 11, 3, "");
            setColor(RED); drawBox(16, 7, 11, 3, "");
            setColor(WHITE);
            drawBox(26, 1, 42, 28, "");
            drawBox(50, 3, 34, 3, "紫憮 餉薯 �挫�");

            setColor(RED);
            gotoxy(32, 7);  printf("薑蜓煎 餉薯ж衛啊蝗棲梱?");
            setColor(WHITE);
            gotoxy(32, 9);  printf("薯跡 : %s", books[removeIndex].bookTitle);
            gotoxy(32, 10); printf("盪濠 : %s", books[removeIndex].bookAuthor);
            gotoxy(32, 11); printf("轎っ餌 : %s", books[removeIndex].bookPublish);

            gotoxy(32, 14); printf("Y 蕨 N 嬴棲螃 : ");
            fgets(input2, sizeof(input2), stdin);
            input2[strcspn(input2, "\n")] = 0;

            if (input2[0] == 'y' || input2[0] == 'Y')
            {
                books[removeIndex].Bstate = 'D';

                if (manageBookFile(books, nullbook, 2, count))
                {
                    setColor(GREEN);
                    gotoxy(72, 10); printf("紫憮陛 餉薯腎歷蝗棲棻.");
                    setColor(WHITE);
                }
                else
                {
                    setColor(RED);
                    gotoxy(72, 10); printf("だ橾 偵褐 褒ぬ.");
                    setColor(WHITE);
                }

                gotoxy(72, 12); printf("嬴鼠 酈釭 援腦撮蹂...");
                _getch();
                return;
            }
            else
            {
                gotoxy(72, 10); printf("鏃模腎歷蝗棲棻.");
                gotoxy(72, 12); printf("嬴鼠 酈釭 援腦撮蹂...");
                _getch();
                continue;
            }
        }
    }
}

/*
    渠轎 褻�� 晦棟 (婦葬濠) (翱羹 > 渠轎 > 奩陶諫猿 薑溺)
*/
void viewBorrowRecords()
{
    Borrow borrowList[1000] = { 0 };
    Book booksLocal[1000] = { 0 };
    Borrow nullborrow = { 0 };
    Book nullbook = { 0 };

    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0);
    int bookCount = manageBookFile(booksLocal, nullbook, 0, 0);

    getDate(0);

    qsort(borrowList, borrowCount, sizeof(Borrow), compareBorrowRecords);

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
        setColor(RED); drawBox(16, 7, 11, 3, "");
        setColor(WHITE);
        drawBox(26, 1, 42, 28, "");
        drawBox(50, 3, 34, 3, "瞪羹 渠轎 頂羲");

        gotoxy(27, 6);
        printf("ID 弛 薯跡                        弛 瞪�食醽�         弛 奩陶 蕨薑橾  弛鼻鷓");
        gotoxy(26, 7);
        printf("戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣");

        int check = 0;

        getDate(0);

        for (int i = 0; i < ROWS; i++)
        {
            int recordIndex = startIndex + i;
            if (recordIndex >= borrowCount)
            {
                break;
            }

            check = 1;

            char fullTitle[50] = "薯跡橈擠";
            for (int j = 0; j < bookCount; j++)
            {
                if (strcmp(borrowList[recordIndex].id, booksLocal[j].id) == 0)
                {
                    strcpy(fullTitle, booksLocal[j].bookTitle);
                    break;
                }
            }

            if (strlen(fullTitle) > 29)
            {
                snprintf(titleShort, sizeof(titleShort), "%.29s", fullTitle);
            }
            else
            {
                strcpy(titleShort, fullTitle);
            }

            int s = borrowList[recordIndex].state;
            int overBorrowing = 0;

            if (s == 1)
            {
                if (isBeforeDate(borrowList[recordIndex].returnYear, borrowList[recordIndex].returnMonth, borrowList[recordIndex].returnDay, year, month, day))
                {
                    overBorrowing = 1;
                }
            }

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
                (s == 1 && overBorrowing) ? "翱羹 渠轎醞" :
                (s == 1) ? "渠轎 醞" :
                (s == 2) ? "薑鼻 奩陶" :
                (s == 3) ? "翱羹 奩陶" : "憲熱橈擠";

            gotoxy(27, 8 + i);
            printf(" %-2s弛 %-28s弛 %-16s 弛 %4d-%02d-%02d   弛 %s",
                borrowList[recordIndex].id,
                titleShort,
                borrowList[recordIndex].borrowerPhone,
                borrowList[recordIndex].returnYear,
                borrowList[recordIndex].returnMonth,
                borrowList[recordIndex].returnDay,
                st);
        }

        setColor(WHITE);

        if (!check)
        {
            gotoxy(28, 10);
            printf("渠轎 頂羲檜 橈蝗棲棻.");
        }

        gotoxy(26, 26);
        printf("戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣");
        gotoxy(26, 28);
        printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
        gotoxy(28, 27);
        printf("[∠][⊥] む檜雖 檜翕   [0] 菴煎 陛晦");

        char key = _getch();

        if (key == 0 || key == 224)
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
        else if (key == '0')
        {
            return;
        }
    }
}