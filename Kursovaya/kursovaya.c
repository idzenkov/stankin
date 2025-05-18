#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// СТРУКТУРЫ
// Двусвязный список
typedef struct listNode // описание структуры "двусвязный список"
{
    char value; // как данные храним символ
    struct listNode* next; // указатель на следующий элемент 
    struct listNode* prev;  // указатель на предыдущий элемент
} list;

// Дек
typedef struct decNode // описание структуры "дек" на базе односвязного списка
{
    list* valueStart; // как данные хранит параметры двусвязного списка
    list* valueEnd;
    struct decNode* next; // указатель на следующий элемент
} dec;

// Прототипы
// Print menu 
void decPrintMenu(); 
void listPrintMenu();

// Options
char input(); 
int decide();
int checkClear(void* head);

// Dec
void decShowLast(dec* tailDec);// Функция показывающая последний элемент, принимающая в себя указатель на конец дека
void decShowFirst(dec* headDec);// Функция показывающая первый элемент, принимающая в себя указатель на начало дека
void decAddFirst(dec** headDec, dec** tailDec);// Функция добавления элемента в начало дека, принимающая в себя указатели на начало и конец дека
void decAddLast(dec** headDec, dec** tailDec);// Функция добавления элемента в конец дека, принимающая в себя указатели на начало и конец дека
void decDelFirst(dec** headDec, dec** tailDec);// Функция удаления первого элемента, принимающая в себя указатели на начало и конец дека
void decDelLast(dec** headDec, dec** tailDec);// Функция удаления последнего элемента, принимающая в себя указатели на начало и конец дека
void decChangeFirst(dec** headDec, dec** tailDec);// Функция изменения первого элемента, принимающая в себя указатели на начало и конец дека
void decChangeLast(dec** headDec, dec** tailDec);// Функция изменения последнего элемента, принимающая в себя указатели на начало и конец дека
void decGetFirst(dec** headDec, dec** tailDec);// Функция которая берет первый элемент, принимающая в себя указатели на начало и конец дека 
void decGetLast(dec** headDec, dec** tailDec);// Функция которая берет последний элемент,принимающая в себя указатели на начало и конец дека
void decPrint(dec* headDec);// Функция печатющая дек, принимающая в себя указатель на начало дека
void decMakeEmpty(dec** headDec, dec** tailDec);// Функция очищающая дек, принимающая в себя указатели на начало и конец дека
void decEndWork(dec** headDec, dec** tailDec);// Функция завершения работы, принимающая в себя указатели на начало и конец дека

// List
void listMakeEmpty(list** head, list** tail);// Функция очищающая список, принимающая в себя указатели на начало и конец списка
void listBegin(list** work, list** head);// Функция ставящая рабочий указатель в начало списка, принимающая в себя рабочий указатель и указатель на начало списка
void listCheckFirst(list* head, list* work);// Функция проверяющая находится ли рабочий указатель в начале списка, принимающая в себя рабочий указатель и указатель на начало списка
void listCheckLast(list* work, list* tail);// Функция проверяющая находится ли рабочий указатель в конце списка,, принимающая в себя рабочий указатель и указатель на конец списка
void listForward(list** work, list* head);// Функция двигающая рабочий указатель на одну позицию вперед, принимающая в себя рабочий указатель и указатель на начало списка
void listBackward(list** work, list* tail);// Функция двигающая рабочий указатель на одну позицию назад, принимающая в себя рабочий указатель и указатель на конец списка
void listShowAfter(list* work, list* head);// Функция показывающая элемент после рабочего указателя, принимающая в себя рабочий указатель и указатель на начало списка
void listShowBefore(list* work, list* tail);// Функция показывающая элемент перед рабочим указателем, принимающая в себя рабочий указатель и указатель на конец списка
void listDelAfter(list** work, list** head, list** tail);// Функция удаления элемента после рабочего указателя, принимающая в себя рабочий указатель и указатели на начало и конец списка
void listDelBefore(list** work, list** head);// Функция удаления элемента перед рабочим указателем, принимающая в себя рабочий указатель и указатели на начало и конец списка
void listTakeAfter(list** work, list** head, list** tail);// Функция которая берет элемент после раочего указателя, принимающая в себя рабочий указатель и указатели на начало и конец списка
void listTakeBefore(list** work, list** head, list** tail);// Функция которая берет элемент перед рабочим указателем, принимающая в себя рабочий указатель и указатели на начало и конец списка
void listChangeAfter(list* work, list* head);// Функция изменения элемента после рабочего указателя, принимающая в себя рабочий указатель и указатель на начало списка
void listChangeBefore(list* work, list* head);// Функция изменения элемента перед рабочим указателем, принимающая в себя рабочий указатель и указатель на начало списка
void listAddAfter(char value, list** work, list** head, list** tail);// Функция добавления элемента после рабочего указателя, принимающая в себя символьное значение, рабочий указатель и указатели на начало и конец списка
void listAddBefore(char value, list** work, list** head, list** tail);// Функция добавления элемента перед рабочим указателя, принимающая в себя символьное значение, рабочий указатель и указатели на начало и конец списка
void listPrint(list* head, list* work);// Функция печатающая список, принимающая в себя рабочий указатель и указатель на начало списка

// menu
void mainMenu();
void decMenu();
void listMenu();
//константы для вывода сообщений
char* decEmtpy = "Пусто!\n";
char* noMemory = "Нет памяти\n";
char* listEmpty = "Список пуст\n";
char* notAllowMove = "Действие не разрешенно!\n";

int decCurrent = 0;// флаг отслеживающий количество элементов дека
int decMax = 2;// для ограничения кол-ва элементов дека 

int main()
{
    system("clear");
    mainMenu();
    printf("%s", "BB!\n");
    return 0;
}

// Print Menu
void decPrintMenu()// Функция печатающая меню дека
{
printf("%s", "\
    1. Сделать дек пустым.\n\
    2. Проверка(пуст / не пуст).\n\
    3. Показать значение в начале дека.\n\
    4. Показать значение в конце дека.\n\
    5. Удалить начало дека.\n\
    6. Удалить конец дека.\n\
    7. Взять элемент из начала дека.\n\
    8. Взять элемент из конца дека.\n\
    9. Изменить значение в начале дека.\n\
    10. Изменить значение в конце дека.\n\
    11. Распечатать структуру.\n\
    12. Добавить элемент в начало дека.\n\
    13. Добавить элемент в конец дека.\n\
    14. Закончить работу.\n\
");
}

void listPrintMenu()// Функция печатающая меню списка
{
printf("%s", "\
    1.  Сделать список пустым.\n\
    2.  Проверить список пуст или не пуст.\n\
    3.  Установить рабочий указатель в начало списка.\n\
    4.  Проверить рабочий указатель в конце списка.\n\
    5.  Проверить рабочий указатель в начале списка.\n\
    6.  Передвинуть раб ук вперед на одну позицию.\n\
    7.  Передвинуть раб ук назад на одну позицию.\n\
    8.  Показать значение элемента списка за указателем.\n\
    9.  Показать значение элемента списка до указателя.\n\
    10. Удалить элемент списка за указателем.\n\
    11. Удалить элемент списка до указателя.\n\
    12. Взять элемент списка за указателем.\n\
    13. Взять элемент списка до указателя.\n\
    14. Изменить значение элемента списка за указателем.\n\
    15. Изменить значение элемента списка до указателя.\n\
    16. Добавить элемент списка за указателем.\n\
    17. Добавить элемент списка до указателя.\n\
    18. Распечатать структуру данных.\n\
    19. Завершить работу со списком (Вернуться к деку).\n\
");
}

//+
void mainMenu()// Функция печатающая начальное меню
{
    printf("%s","1. Начало\n");
    printf("%s","2. Конец\n");
    switch (decide())
    {
    case 1:
        decMenu();
        break;
    case 2:
        return;
        break;
    }
}

//+
void listMenu(list** head, list** tail)// Функция работы с пунктами меню списка
{
    system("clear");
    list* work;
    if(*head == NULL)
        work = NULL;
    else
        work = *head;

    while (1)
    {
        printf("%s","Вывод: ");
        listPrint(*head, work);
        printf("%s","\n");
        listPrintMenu();
        
        int vibor = decide();
        system("clear");
        switch (vibor)
        {
        case 1:
        //Сделать список пустым
            listMakeEmpty(head, tail);
            break;
        
        case 2:
        //Проверить список пуст или не пуст
            if(!checkClear(*head))
                printf("%s","Пусто!\n");
            else
                printf("%s","Не пусто!\n");
            break;
        
        case 3:
        // Установить рабочий указатель в начало списка
            listBegin(&work, head);
            break;
        
        case 4:
        // Проверить рабочий указатель в конце списка
            listCheckLast(work, *tail);
            break;
        
        case 5:
        // Проверить рабочий указатель в начале списка
            listCheckFirst(*head, work);
            break;
        
        case 6:
        // Передвинуть раб ук вперед на одну позицию
            listForward(&work, *head);
            break;
        
        case 7:
        //Передвинуть раб ук назад на одну позицию
            listBackward(&work, *tail);
            break;
        
        case 8:
        //Показать значение элемента списка за указателем
            listShowAfter(work, *head);
            break;
        
        case 9:
        //Показать значение элемента списка до указателя
            listShowBefore(work, *tail);
            break;
        
        case 10:
        //Удалить элемент списка за указателем
            listDelAfter(&work, head, tail);
            break;
        
        case 11:
        //Удалить элемент списка до указателя
            listDelBefore(&work, head);
            break;
        
        case 12:
        // Взять элемент списка за указателем
            listTakeAfter(&work, head, tail);
            break;
        
        case 13:
        //Взять элемент списка до указателя
            listTakeBefore(&work, head, tail);
            break;
        
        case 14:
        //Изменить значение элемента списка за указателем
            listChangeAfter(work, *head);
            break;
        
        case 15:
        //Изменить значение элемента списка до указателя
            listChangeBefore(work, *head);
            break;
        
        case 16:
        //Добавить элемент списка за указателем
            listAddAfter(input(), &work, head, tail);
            break;
        
        case 17:
        //Добавить элемент списка до указателя
            listAddBefore(input(), &work, head, tail);
            break;
        
        case 18:
        //Распечатать структуру данных
            listPrint(*head, work);
            printf("%s","\n");
            break;

        case 19://Завершить работу со списком (Вернуться к деку)
            return;
            break;
        
        default:
            printf("%s","Такого пункта нет!!!\n");
            break;
        }
    
    }

}

void decMenu()// Функция работающая с пунктами меню дека
{
    system("clear");
    dec* headDec = NULL; 
    dec* tailDec = NULL;
    
    while (1)
    {
        printf("%s","\n");
        decPrint(headDec);
        decPrintMenu();
        printf("%s","\n");
        
        int vibor = decide();
        system("clear");
        switch (vibor)
        {
        case 1:
        // Сделать дек пустым.
            decMakeEmpty(&headDec, &tailDec);
            decCurrent = 0;
            break;
        
        case 2:
        // Проверка(пуст / не пуст).
            if(!checkClear(headDec))
                printf("%s","Пусто!\n");
            else
                printf("%s","Не пусто!\n");
            break;
        
        case 3:
        // Показать значение в начале дека.
            decShowFirst(headDec);
            break;
        
        case 4:
        // Показать значение в конце дека.
            decShowLast(tailDec);
            break;
        
        case 5:
        // Удалить начало дека.
            decDelFirst(&headDec, &tailDec);
            if(decCurrent != 0)
            decCurrent--;
            break;
        
        case 6:
        // Удалить конец дека.
            decDelLast(&headDec, &tailDec);
            if(decCurrent != 0)
            decCurrent--;
            break;
        
        case 7:
        // Взять элемент из начала дека.
            decGetFirst(&headDec, &tailDec);
            if(decCurrent != 0)
            decCurrent--;
            break;
        
        case 8:
        // Взять элемент из конца дека.
            decGetLast(&headDec, &tailDec);
            if(decCurrent != 0)
            decCurrent--;
            break;
        
        case 9: 
        // Изменить значение в начале дека.
            decChangeFirst(&headDec, &tailDec);
            break;
        
        case 10:
        // Изменить значение в конце дека
            decChangeLast(&headDec, &tailDec);
            break;
        
        case 11:
        //Распечатать структуру
            decPrint(headDec);
            break;

        case 12:
        //Добавить элемент в начало дека
            if(decCurrent != decMax)
            {
                decAddFirst(&headDec, &tailDec);
                decCurrent += 1;
            }
            else
            printf("%s", "Нельзя добавить.");
            break;
        
        case 13:
        //Добавить элемент в конец дека
            if(decCurrent != decMax)
            {
            decAddLast(&headDec, &tailDec);
            decCurrent += 1;
            }
            else
            printf("%s", "Нельзя добавить.");
            break;

        case 14:
        //Закончить работу
            decEndWork(&headDec, &tailDec);
            break;

        default:
            printf("%s","Такого пункта нет!!!\n");
            break;
        }
    }
}

char input()//Функция отвечающая за ввод символа
{
    getc(stdin);

    char c;
    printf("%s","Введите символ: ");
    scanf("%c", &c);

    while (getc(stdin) != '\n');
    
    return c;
}

int decide()//Функция 
{
    printf("%s","Сделайте ввод: ");

    char str[1024];
    scanf("%s", str);

    int length = strlen(str); //string length
    if (length > 2)
        return 0;

    for (int i = 0; i < length; i++)
    {
        if (isdigit(str[i]) == 0) //is - это ,digit - цифры ? Это цифра? 0 - нет. 1 - да
            return 0;
    }

    return atoi(str); //char* to int   "12" -> int(12)
}

///////////////////////////////////////////////////
//НАЧАЛО ФУНКЦИЙ РАБОТЫ СО СПИСКОМ

void listMakeEmpty(list** head, list** tail) // Функция очищающая список
{
    if(*head == NULL)//проверка не пуст ли уже список
    {
        printf("%s","Список уже пуст\n");
        return;
    }

    list* it = *head;
    while(it != NULL)//пока есть этот элемент чистим
    {
        it = (*head)->next;
        free(*head);
        *head = it;
    }
    *tail = *head = NULL;
}

void listBegin(list** work, list** head) // Функция которая ставит рабочий указатель в начало
{
    if(*head == NULL)//Проверка не пуст ли список
    {
        printf("%s",listEmpty);
        return;
    }
    *work = *head;
}

//+
void listCheckFirst(list* head, list* work)// Проверка рабочего указателя в начале
{
    if(head == NULL)// проверка не пуст ли список
    {
        printf("%s",listEmpty);
        return;
    }
    if(head == work) // если рабочий указатель находится в начале
        printf("%s","В начале!\n");
    else
        printf("%s","Нет!\n");
}

void listCheckLast(list* work, list* tail)// Проверка рабочего указателя в конце списка
{
    if(tail == NULL)// проверка не пуст ли список
    {
        printf("%s",listEmpty);
        return;
    }
    if(tail == work)// проверка находится ли рабочий указатель в конце списка
        printf("%s","В конце!\n");
    else
        printf("%s","Нет!\n");
}

//+
void listForward(list** work, list* head)//передвинуть рабочий указатель вперед на одну позицию
{
    if(head == NULL)// проверка не пуст ли список/
    {
        printf("%s","Список пуст\n");
        return;
    }

    if((*work)->next != NULL)//проверка на правую границу списка
        *work = (*work)->next;
    
}

void listBackward(list** work, list* tail)// передвинуть рабочий указатель назад на одну позицию
{
    if(tail == NULL)// проверка не пуст ли список
    {
        printf("%s","Список пуст\n");
        return;
    }

    if((*work)->prev != NULL)//проверка на левую границу списка
        *work = (*work)->prev;
}

//+
void listShowAfter(list* work, list* head)// показать значение элемента списка за указателем
{
    if(head == NULL)// проверка не пуст ли список
    {
        printf("%s","Список пуст\n");
        return;
    }

    if(work->next != NULL)// проверка на правую границу списка
        printf("%c \n", work->next->value);
    else
        printf("%s",notAllowMove);
    
}

void listShowBefore(list* work, list* tail)//показать значение элемента до указателя
{
    if(tail == NULL)// проверка не пуст ли список
    {
        printf("%s",listEmpty);
        return;
    }

    if(work->prev != NULL)// проверка на левую границу
        printf("%c \n", work->prev->value);
    else
        printf("%s",notAllowMove);
    
}

// +
void listDelAfter(list** work, list** head, list** tail)// удалить элемент списка за указателем
{
    if(*head == NULL)// проверка не пуст ли список
    {
        printf("%s",notAllowMove);
        return;
    }

    if((*work)->next == NULL)//проверка есть ли элемент за указателем
    {
        printf("%s",notAllowMove);
        return;
    }
    
    list* it = (*work)->next;
    if(it->next == NULL)//проверка есть ли после элемента за указателем элемент
    {
        (*work)->next = it->next;
        free(it);//
        *tail = *work;
        return;
    }

    it->next->prev = (*work);
    (*work)->next = it->next;
    free(it);//
    return;
    
}

void listDelBefore(list** work, list** head)
{
    if(*head == NULL)// проверка не пуст ли список
    {
        printf("%s",notAllowMove);
        return;
    }

    if((*work)->prev == NULL)//проверка есть ли элемент перед указателем
    {
        printf("%s",notAllowMove);
        return;
    }
    
    list* it = (*work)->prev;
    if(it->prev == NULL)//проверка есть ли перед элементом перед указателем элемент
    {
        (*work)->prev = it->prev;
        free(it);//
        *head = *work;
        return;
    }

    it->prev->next = (*work);
    (*work)->prev = it->prev;
    free(it);//
    return;
}

// +
void listTakeAfter(list** work, list** head, list** tail) //взять элемент после указателя
{
    if(*head == NULL || *work == NULL || (*work)->next == NULL)// проверка не пуст ли список и есть ли элемент за указателем
    {
        printf("%s",notAllowMove);
        return;
    }
    listShowAfter(*work, *head);
    listDelAfter(work, head, tail);
}

void listTakeBefore(list** work, list** head, list** tail) //взять элемент до указателя
{
    if(*head == NULL || *work == NULL || (*work)->prev == NULL)// проверка не пуст ли список и есть ли элемент до указателя
    {
        printf("%s",notAllowMove);
        return;
    }
    listShowBefore(*work, *tail);
    listDelBefore(work, head);
}


void listChangeAfter(list* work, list* head)//изменить значение элемента за указателем
{
    if(head == NULL || work == NULL || work->next == NULL )// проверка не пуст ли список и есть ли такой элемент
    {
        printf("%s",notAllowMove);
        return;
    }

    work->next->value = input();
}

void listChangeBefore(list* work, list* head)//изменить значение элемента до указателя
{
    if(head == NULL || work == NULL || work->prev == NULL )// проверка не пуст ли список и есть ли элемент до указателя
    {
        printf("%s",notAllowMove);
        return;
    }
    
    work->prev->value = input();
}



void listAddAfter(char value, list** work, list** head, list** tail)//добавить элемент за указателем
{
    list* tmp = (list*)malloc(sizeof(list));
    if(tmp == NULL)//проверка на выделение памяти
    {
        printf("%s","Not enough memory\n");
        exit(1);
    }
    tmp->value = value;

    if(*head == NULL)//проверка пуст ли список
    {
        tmp->prev = NULL;
        tmp->next = NULL;
        *head = tmp;
        *tail = tmp;
        *work = tmp;
    }
    else if ((*work)->next == NULL)//проверка является ли элемент правой границей списка
    {
        tmp->prev = *work;
        tmp->next = NULL;
        (*work)->next = tmp; 
        *tail = tmp;
    }
    else
    {
        tmp->next = (*work)->next;
        tmp->prev = *work;
        (*work)->next->prev = tmp;
        (*work)->next = tmp;
    }
    
}

void listAddBefore(char value, list** work, list** head, list** tail)//добавить элемент до указателя
{
    list* tmp = (list*)malloc(sizeof(list));
    if(tmp == NULL)//проверка выделения памяти
    {
        printf("%s","Not enough memory\n");
        exit(1);
    }
    tmp->value = value;

    if(*head == NULL)// проверка не пуст ли список
    {
        tmp->next = NULL;
        tmp->prev = NULL;
        *tail = tmp;
        *head = tmp;
        *work = tmp;
    }
    else if ((*work)->prev == NULL)//проверка не является ли элемент левой границей списка
    {
        tmp->next = *work;
        tmp->prev = NULL;
        (*work)->prev = tmp; 
        *head = tmp;
    }
    else
    {
        tmp->prev = (*work)->prev;
        tmp->next = *work;
        (*work)->prev->next = tmp;
        (*work)->prev = tmp;
    }
    
}



void listPrint(list* head, list* work)//распечатать структуру данных
{
    if(head == NULL)// проверка не пуст ли список
    {
        printf("%s","Пусто \n");
        return;
    }

    list* it = head;
    while (it != NULL)//пока этот элемент не является границей списка
    {
        if(it == work)
            printf("{ %c } ", it->value);
        else
            printf("%c ", it->value);
        
        it = it->next;
    }
    
}



int checkClear(void* head)//проверка пуст ли список или дек пустым
{
    if(head == NULL)
        return 0;

    return 1; 
}

////////////////////////////////////////////////////////////
// НАЧАЛО ФУНКЦИЙ РАБОТЫ С ДЕКОМ

void decShowFirst(dec* headDec)//показать значение в начале дека
{
    if(headDec == NULL)// проверка не пуст ли дек
    {
        printf("%s",decEmtpy);
        return;
    }

    listPrint(headDec->valueStart, NULL);
    printf("%s","\n");
}

void decShowLast(dec* tailDec)//показать значение в конце дека
{
    if(tailDec == NULL)// проверка не пуст ли дек
    {
        printf("%s",decEmtpy);
        return;
    }

    listPrint(tailDec->valueStart, NULL);
}

void decChangeFirst(dec** headDec, dec** tailDec)//изменить значение в начале дека
{
    if(*headDec == NULL)// проверка не пуст ли дек
    {
        printf("%s",decEmtpy);
        return;
    }

    listMenu(&(*headDec)->valueStart, &(*headDec)->valueEnd);
    if((*headDec)->valueStart == NULL) // Если опустошили элемент дека - удаляем
    { 
        decCurrent--;
        decDelFirst(headDec, tailDec);
    }
}

void decChangeLast(dec** headDec, dec** tailDec)//изменить значение в конце дека
{
    if(*headDec == NULL) // проверка не пуст ли дек
    {
        printf("%s",decEmtpy);
        return;
    }

    listMenu(&(*tailDec)->valueStart, &(*tailDec)->valueEnd);
    if((*tailDec)->valueEnd == NULL) // Если опустошили элемент дека - удаляем
    {
        decCurrent--;
        decDelLast(headDec, tailDec);
    }
}

void decAddFirst(dec** headDec, dec** tailDec)//добавить элемент в начало
{
    dec* tmp = (dec*)malloc(sizeof(dec));
    if(tmp == NULL) // Проверка на выделение памяти
    {
        printf("%s",noMemory);
        exit(1);
    }

    tmp->valueStart = NULL;
    tmp->valueEnd = NULL;

    listMenu(&tmp->valueStart, &tmp->valueEnd);
    if(tmp->valueStart == NULL) // Если добавили пустой элемент
    {
        free(tmp);
        return;
    }

    if(*headDec == NULL) // Если дек пуст
    {   
        tmp->next = NULL;
        (*headDec) = (*tailDec) = tmp;
    }
    else // Если дек не пуст
    {
        tmp->next = *headDec;
        (*headDec) = tmp;
    }
}

void decAddLast(dec** headDec, dec** tailDec)//добавить элемент в конец
{
    dec* tmp = (dec*)malloc(sizeof(dec));
    if(tmp == NULL) // проверка на выделение памяти
    {
        printf("%s",noMemory);
        exit(1);
    }

    tmp->valueStart = NULL;
    tmp->valueEnd = NULL;

    listMenu(&tmp->valueStart, &tmp->valueEnd);
    if(tmp->valueEnd == NULL) // Если добавили пустой элемент
    {
        free(tmp);
        return;
    }

    if(*tailDec == NULL) // если дек пуст
    {   
        tmp->next = NULL;
        (*headDec) = (*tailDec) = tmp;
    }
    else // если дек не пуст
    {
        tmp->next = NULL;
        (*tailDec)->next = tmp;
        (*tailDec) = tmp;
    }
}

void decDelFirst(dec** headDec, dec** tailDec)//удалить первый элемент
{
    if(*headDec == NULL) // проверка не пуст ли дек
    {
        printf("%s",decEmtpy);
        return;
    }

    dec* it = *headDec;
    if((*headDec)->next == NULL) // остался один элемент?
    {
        *headDec = *tailDec = NULL;
    }
    else // если осталось больше одного элемента
    {
        (*headDec) = (*headDec)->next;
    }
    
    listMakeEmpty(&(it->valueStart), &(it->valueEnd));
    free(it);
}

void decDelLast(dec** headDec, dec** tailDec)//удалить последний элемент
{
    if(*tailDec == NULL) // проверка не пуст ли дек
    {
        printf("%s",decEmtpy);
        return;
    }

    dec* it = *tailDec;
    dec* last = *headDec;
    if((*headDec)->next == NULL) // Остался один элемент?
    {
        *headDec = *tailDec = NULL;
    }
    else // если осталось больше одного элемента
    {
        while (last->next != it)
            last = last->next;
        
        last->next = NULL;
        (*tailDec) = last;
    }

    listMakeEmpty(&(it->valueStart), &(it->valueEnd));
    free(it);
}

void decGetFirst(dec** headDec, dec** tailDec)//взять первый элемент
{
    if(*headDec == NULL) // проверка не пуст ли дек
    {
        printf("%s",decEmtpy);
        return;
    }

    listPrint((*headDec)->valueStart, NULL);
    decDelFirst(headDec, tailDec);
}

void decGetLast(dec** headDec, dec** tailDec)//взять последний элемент
{
    if(*tailDec == NULL) // проверка не пуст ли дек
    {
        printf("%s",decEmtpy);
        return;
    }

    listPrint((*tailDec)->valueStart, NULL);
    decDelLast(headDec, tailDec);
}

void decPrint(dec* headDec)//распечатать структуру
{
    if(headDec == NULL) // проверка не пуст ли дек
    {
        printf("%s", decEmtpy);
        return;
    }

    dec* it = headDec;
    while (it != NULL) // пока не дойдёт до конца - печатает
    {
        listPrint(it->valueStart, NULL);
        printf("%s","| ");
        it = it->next;
    }
    printf("%s","\n");
    
}

void decMakeEmpty(dec** headDec, dec** tailDec)//сделать дек пустым
{
    if(*headDec == NULL) // проверка не пуст ли дек
    {
        printf("%s","Дек уже пуст!\n");
        return;
    }

    while(*headDec != NULL) // удаление элементов
        decDelFirst(headDec, tailDec);
    
}

void decEndWork(dec** headDec, dec** tailDec)//закончить работу
{
    if(*headDec != NULL) // проверка не пуст ли дек
        decMakeEmpty(headDec, tailDec);

    printf("Пока!\n");
    exit(0);
}
