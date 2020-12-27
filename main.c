#include <stdio.h>
#include <stdlib.h>

#include "STD_TYPES.h"
s32 slot_av[6] = {99, 99, 99, 99, 99, 99};
char slots[6][40] = {"000", "2pm-2:30pm", "2:30pm-3pm", "3pm-3:30pm", "4pm-4:30pm", "4:30pm-5pm"};
u8 count = 0;
Node *st;
void view_res(void)
{

    u8 id;
    for (s32 i = 1; i < 6; i++)
    {
        if (slot_av[i]!= 99)
        {
            id=slot_av[i];
            if (find(st, id))
            {
                Node *p;
                p = get_pointer(st, id);
                printf("\nID: %d, Name: %s, Gender: %c, Age: %d\n", p->Info, p->name, p->gender, p->age);
                printf("Slot: %d at %s\n",i,slots[i]);

                
            }
        }
    }
}
void user(void)
{

    u8 state = 9;

    u8 go_back = 1;
    u8 flag = 1;

    while (go_back)
    {
        printf("\n-------------------------user-------------------\n");

        switch (state)
        {
        case 9: //admin main menu
            printf("view patient: 1\n");
            printf("view reservation: 2\n");
            printf("back: 3\n");
            scanf("%d", &state);
            break;
        case 1: //add new patient
            state = 9;
            printf("#######-----view patient record-----########\n");
            printf("enter the valid id you to change it's info: \n");
            u8 id;
            scanf("%d", &id);
            if (find(st, id))
            {
                Node *p;
                p = get_pointer(st, id);
                printf("\nID: %d, Name: %s, Gender: %c, Age: %d\n", p->Info, p->name, p->gender, p->age);
                printf("patient reservation:\n");

                for (s32 i = 1; i < 6; i++)
                {
                    printf("%d", i);
                    if (p->Info == slot_av[i])
                    {
                        printf("\nSlot: %d Time: %s", i, slots[i]);
                    }
                }
                fflush(stdin);
                fflush(stdout);
            }
            else
            {
                printf("not found !\n");
            }
            state = 9;
            break;
        case 2: //edit a patient
            state = 9;
            printf("######-----view reservation-----####\n");
            view_res();

            state = 9;
            break;

        case 3:
            printf("back: 3\n");
            flag = 0;
            go_back = 0;
            break;

        default:
            break;
        }
    }
}
void add_patient(void)
{
    if (count == 0) //first patient in the list ;
    {
        Node *temp = (Node *)malloc(sizeof(Node));
        printf("Patient ID: %d", count);
        temp->Info = count;
        temp->Link = NULL;
        printf("\n enter patient name:");
        scanf("%s", temp->name);
        fflush(stdin);
        fflush(stdout);
        printf("\n Name: %s", temp->name);
        printf("\n enter patient gender (f/m):");
        scanf("%c", &temp->gender);
        fflush(stdin);
        fflush(stdout);
        printf("\n enter patient age :");
        scanf("%d", &temp->age);
        fflush(stdin);
        fflush(stdout);
        st = temp;

        count++;
    }
    else
    {
        Node *p;
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->Info = count;
        printf("\nPatient ID: %d", count);
        printf("\n enter patient name:");
        scanf("%s", temp->name);
        fflush(stdin);
        fflush(stdout);
        printf("\n Name: %s", temp->name);
        printf("\n enter patient gender (f/m):");
        scanf("%c", &temp->gender);
        fflush(stdin);
        fflush(stdout);
        printf("\n enter patient age:");
        scanf("%d", &temp->age);
        fflush(stdin);
        fflush(stdout);
        p = st;
        while (p->Link != NULL)
        {
            p = p->Link;
        }
        /* Insert Node At the end */
        p->Link = temp;
        temp->Link = NULL;
        count++;
    }
}

u8 check_password(void)
{
    u8 ret = 0;
    u16 user_pw;
    printf("please enter password:");
    scanf("%d", &user_pw);
    if (user_pw == 1234)
    {
        printf("you are an admin");
        ret = 1;
    }
    return ret;
}

void reserve_slot(u8 delete)
{

    printf("enter id to operate on slot:\n");
    u8 id;
    scanf("%d", &id);

    printf("Slots:\n");
    for (u8 i = 1; i < 6; i++)
    {
        if (slot_av[i] == 99)
        {
            printf("\n slot: %d => %s", i, slots[i]);
        }
    }

    if (find(st, id))
    {
        Node *p;
        p = get_pointer(st, id);
        if (delete == 0)
        {
            printf("\n reserving a slot");
            printf("\n --------id found choose-------");
            printf("\nenter the slot number to reserve it: ");
            s32 slot_num;
            scanf("%d", &slot_num);
            slot_av[slot_num] = p->Info;
            printf("\n%d", slot_av[slot_num]);
        }
        else
        {

            printf("\ndeleting a reservation");
            printf("\n --------id found-------");
            printf("\nenter the slot number to reserve it: ");
            printf("\nenter slot number to be deleted");
            u8 del;
            scanf("%d", &del);
            for (s32 i = 1; i < 6; i++)
            {
                if (slot_av[i] == p->Info && i == del)
                {
                    slot_av[i] = 99;
                }
            }
        }
    }
    else
    {
        printf("\nnot found !\n");
    }
}

u8 admin_mode(void)
{
    u8 ret;
    u8 state = 9;

    u8 go_back = 0;
    u8 admin_counter = 0;
    u8 pw_state;
    u8 flag = 1;
    while (admin_counter < 3 && flag)
    {
        pw_state = check_password();
        if (pw_state)
        {
            state = 9;
            go_back = 1;

            break;
        }
        else
        {
            admin_counter++;
        }
    }
    if (admin_counter == 3)
    {
        return 1;
    }
    while (go_back)
    {
        printf("\n-------------------------admin-------------------\n");

        switch (state)
        {
        case 9: //admin main menu
            printf("enter new patient: 1\n");
            printf("edit patient: 2\n");
            printf("reserve a slot: 3\n");
            printf("cancel reservation: 4\n");
            printf("back: 5\n");
            printf("your option: ");
            scanf("%d", &state);
            break;
        case 1: //add new patient
            state = 9;
            printf("#######-----enter new patient-----########");
            add_patient();
            break;
        case 2: //edit a patient
            state = 9;
            printf("######-----edit patient-----####\n");
            printf("enter the valid id you to change it's info: \n");
            u8 id;
            scanf("%d", &id);
            if (find(st, id))
            {
                Node *p;
                p = get_pointer(st, id);
                printf("\nID: %d, Name: %s, Gender: %c, Age: %d", p->Info, p->name, p->gender, p->age);
                fflush(stdin);
                fflush(stdout);
                printf("\n enter patient new gender (f/m):");
                scanf("%c", &p->gender);
                fflush(stdin);
                fflush(stdout);
                printf("\n enter patient new age :");
                scanf("%d", &p->age);
                fflush(stdin);
                fflush(stdout);
            }
            else
            {
                printf("not found !\n");
            }
            state = 9;
            break;
        case 3: //reserve a slot
            state = 9;
            printf("######-----reserve a slot--------#\n");
            reserve_slot(0);
            state = 9;
            break;
        case 4: //cancel a slot
            state = 9;
            printf("\n--------------canel reservation-----------\n");
            reserve_slot(1);
            state = 9;
            break;
        case 5:
            printf("back: 5\n");
            flag = 0;
            go_back = 0;
            break;

        default:
            break;
        }
    }
}
u8 main(void)
{

    u8 admin_mode_counter = 0;
    u8 state = 9;
    while (1)
    {

        switch (state)
        {
        case 9: //main menu
            printf("Please choose the mode:\n");
            printf("User Mode: 0\n");
            printf("Admin Mode: 1\n");
            printf("Choice:");
            fflush(stdin);
            fflush(stdout);
            scanf("%d", &state);
            fflush(stdin);
            fflush(stdout);
            break;
        case 0: //user mode
            printf("user");
            user();
            state = 9;
            break;
        case 1: //admin mode
            printf("Admin Mode:\n");
            if (admin_mode() == 1)
            {
                return 1;
            }
            state = 9;

        default:
            break;
        }
    }
}

Node *CreateList(Node *Start)
{
    s32 n, Data, i;
    n = 1;

    if (0 == n)
    {
        return Start;
    }

    Start = InsertInBeginning(Start, 1);

    return Start;
}

Node *InsertInBeginning(Node *Start, s32 Data)
{
    /* Create Node */
    Node *temp = (Node *)malloc(sizeof(Node));
    if (temp != NULL)
    {
        temp->Info = Data;
        temp->Link = Start;
        Start = temp;
    }
    return Start;
}
void InsertAtEnd(Node *Start, s32 Data)
{
    Node *p;
    /* Create Node */
    Node *temp = (Node *)malloc(sizeof(Node));
    if (temp != NULL)
    {
        temp->Info = Data;

        p = Start;
        while (p->Link != NULL)
        {
            p = p->Link;
        }
        /* Insert Node At the end */
        p->Link = temp;
        temp->Link = NULL;
    }
}
void InsertAfter(Node *Start, s32 x, s32 Data)
{
    Node *temp;
    Node *P;
    P = Start;

    while (P != NULL)
    {
        if (P->Info == x)
        {
            break;
        }
        P = P->Link;
    }
    if (P == NULL)
    {
        printf("The value %d is not in the List \n", x);
    }
    else
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->Info = Data;
        temp->Link = P->Link;
        P->Link = temp;
    }
}
Node *InsertBefore(Node *Start, s32 x, s32 Data)
{
    Node *temp, *p;
    if (Start == NULL)
    {
        printf("List is empty\n");
        return Start;
    }
    /* if x is in the first node, insert node at the beginning of the list */
    if (Start->Info == x)
    {
        Start = InsertInBeginning(Start, Data);
        return Start;
    }
    /* Find pointer to predecessor of the node containing x */
    p = Start;
    while (p->Link != NULL)
    {
        if (p->Link->Info == x)
        {
            break;
        }
        p = p->Link;
    }
    if (p->Link == NULL)
    {
        printf("The Value %d is not in the List\n", x);
    }
    else
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->Info = Data;
        temp->Link = p->Link;
        p->Link = temp;
    }
    return Start;
}
Node *InsertAtPosition(Node *Start, s32 Data, s32 Pos)
{
    Node *temp, *p;
    s32 i;
    if (Pos == 1) /* Insert At the beginning */
    {
        Start = InsertInBeginning(Start, Data);
        return Start;
    }
    p = Start;
    for (i = 1; (i < Pos - 1) && (p != NULL); i++)
    {
        p = p->Link;
    }
    if (p == NULL)
    {
        printf("You can insert only upto %d th position \n", i);
    }
    else
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->Info = Data;
        temp->Link = p->Link;
        p->Link = temp;
    }
    return Start;
}
void DisplayList(Node *Start)
{
    Node *p;
    if (Start == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("List is : ");
    p = Start;
    while (p != NULL)
    {
        printf("%d ", p->Info);
        p = p->Link;
    }
    printf("\n");
}
u8 find(Node *Start, u8 id)
{

    Node *p = Start;
    while (p != NULL)
    {
        if (p->Info == id)
        {
            return 1;
        }
        p = p->Link;
    }
    return 0;
}

Node *get_pointer(Node *Start, u8 id)
{

    Node *p = Start;
    while (p != NULL)
    {
        if (p->Info == id)
        {
            return p;
        }
        p = p->Link;
    }
    return NULL;
}
void Search(Node *Start, s32 x)
{
    Node *p;
    s32 counter = 0;
    /*if(Start == NULL)
	{
		printf("List is empty\n");
		return;
	}*/
    p = Start;
    while ((p != NULL) && (p->Info != x))
    {
        counter++;
        p = p->Link;
    }
    if (p == NULL)
    {
        printf("The value %d is not at the List\n", x);
    }
    else
    {
        printf("The value %d is at %d th position at the List", x, counter);
    }
}
Node *DeleteNode(Node *Start, s32 Data)
{
    Node *temp, *p;
    if (Start == NULL) /* List is empty */
    {
        printf("List is empty \n");
        return Start;
    }
    /* Delete the first Node at the List */
    if (Start->Info == Data)
    {
        temp = Start;
        Start = Start->Link;
        free(temp);
        return Start;
    }
    /* Delete in between the Nodes or at the end */
    p = Start;
    while (p->Link != NULL)
    {
        if (p->Link->Info == Data)
        {
            temp = p->Link;
            break;
        }
        p = p->Link;
    }
    if (p->Link == NULL)
    {
        printf("Element of the value %d is not in the List\n", Data);
    }
    else
    {
        p->Link = temp->Link;
        free(temp);
    }
    return Start;
}
Node *ReverseList(Node *Start)
{
    Node *prev, *ptr, *next;
    prev = NULL;
    ptr = Start;
    while (ptr != NULL)
    {
        next = ptr->Link;
        ptr->Link = prev;
        prev = ptr;
        ptr = next;
    }
    Start = prev;

    return Start;
}
