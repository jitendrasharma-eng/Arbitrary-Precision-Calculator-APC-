#include "apc.h"
//<-------------------------------ADDITION FUnction---------------------------->
int addition(Dlist **tail1, Dlist **tail2)
{
    Dlist *temp1 = *tail1, *temp2 = *tail2;
    int sum = 0;
    int carry = 0;
    while (temp1 != NULL || temp2 != NULL)
    {
        if (temp1 != NULL && temp2 != NULL)
        {
            sum = temp1->data + temp2->data + carry;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if (temp1 != NULL && temp2 == NULL)
        {
            sum = (temp1->data) + carry;
            temp1 = temp1->prev;
        }
        else if (temp1 == NULL && temp2 != NULL)
        {
            sum = (temp2->data) + carry;
            temp2 = temp2->prev;
        }

        if (sum > 9)
        {
            carry = sum / 10;
            sum = sum % 10;
        }
        dl_insert_first(&Rhead, &Rtail, sum);
    }
    if (carry == 1)
        dl_insert_first(&Rhead, &Rtail, sum);
    return SUCCESS;
}
//<---------------------------------------------------------------------------->

//<-------------------------------SUBTRACTION FUnction---------------------------->
int compare_numbers(Dlist **head1, Dlist **head2)
{
    Dlist *temp1 = *head1;
    Dlist *temp2 = *head2;
    int count1 = 0;
    int count2 = 0;

    while (temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }
    if (count1 > count2)
        return 1;
    if (count1 < count2)
        return -1;

    temp1 = *head1;
    temp2 = *head2;
    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->data > temp2->data)
            return 1;

        if (temp2->data > temp1->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return 0;
}

int subtraction(Dlist **tail1, Dlist **tail2, Dlist **head1, Dlist **head2)
{
    Dlist *temp1 = *tail1, *temp2 = *tail2;
    int res = 0;
    int borrow = 0;
    int ret = compare_numbers(head1, head2);

    if (ret == 0)
    {
        dl_insert_first(&Rhead, &Rtail, 0);
        return SUCCESS;
    }

    while (temp1 != NULL || temp2 != NULL)
    {
        if (ret == 1)
        {
            if (temp1 != NULL && temp2 != NULL)
            {
                res = temp1->data - temp2->data - borrow;
                temp1 = temp1->prev;
                temp2 = temp2->prev;
            }

            else if (temp1 != NULL && temp2 == NULL)
            {
                res = temp1->data - borrow;
                temp1 = temp1->prev;
            }

            else if (temp1 == NULL && temp2 != NULL)
            {
                res = temp2->data - borrow;
                temp2 = temp2->prev;
            }
        }
        if (ret == -1)
        {
            if (temp1 != NULL && temp2 != NULL)
            {
                res = temp2->data - temp1->data - borrow;
                temp1 = temp1->prev;
                temp2 = temp2->prev;
            }

            else if (temp2 != NULL && temp1 == NULL)
            {
                res = temp2->data - borrow;
                temp2 = temp2->prev;
            }

            else if (temp2 == NULL && temp1 != NULL)
            {
                res = temp1->data - borrow;
                temp1 = temp1->prev;
            }
        }
        if (res < 0)
        {
            res = res + 10;
            borrow = 1;
        }
        else
            borrow = 0;

        dl_insert_first(&Rhead, &Rtail, res);
    }

    // return SUCCESS;
}
//<------------------------------------------------------------------------------->

//<-------------------------------MULTIPLICATION FUnction---------------------------->

int addition_for_mul(Dlist **R1head, Dlist **R1tail, Dlist **R2head, Dlist **R2tail, Dlist **Rhead, Dlist **Rtail)
{
    Dlist *temp1 = *R1tail;
    Dlist *temp2 = *R2tail;

    int sum, carry = 0;

    while (temp1 || temp2 || carry)
    {
        sum = carry;

        if (temp1)
        {
            sum += temp1->data;
            temp1 = temp1->prev;
        }

        if (temp2)
        {
            sum += temp2->data;
            temp2 = temp2->prev;
        }

        carry = sum / 10;
        sum = sum % 10;

        dl_insert_first(Rhead, Rtail, sum);
    }

    return SUCCESS;
}

int multiplication(Dlist **tail1, Dlist **tail2)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    int res, carry = 0, count = 0;

    while (temp2)
    {
        temp1 = *tail1;
        carry = 0;

        for (int i = 0; i < count; i++)
        {
            dl_insert_first(&R2head, &R2tail, 0);
        }

        while (temp1)
        {
            res = temp2->data * temp1->data + carry;
            carry = res / 10;
            res = res % 10;

            if (count == 0)
                dl_insert_first(&R1head, &R1tail, res);
            else
                dl_insert_first(&R2head, &R2tail, res);

            temp1 = temp1->prev;
        }

        if (carry)
        {
            if (count == 0)
                dl_insert_first(&R1head, &R1tail, carry);
            else
                dl_insert_first(&R2head, &R2tail, carry);
        }

        if (count > 0)
        {
            addition_for_mul(&R1head, &R1tail, &R2head, &R2tail, &Rhead, &Rtail);
            // printf("After addition: Rhead = %d\n", Rhead->data );
            //  Update R1 with the accumulated result
            R1head = Rhead;
            R1tail = Rtail;

            R2head = NULL;
            R2tail = NULL;

            Rhead = NULL;
            Rtail = NULL;
        }

        temp2 = temp2->prev;
        count++;
    }
    Rhead = R1head;
    Rtail = R1tail;
    return SUCCESS;
}
//<------------------------------------------------------------------------------->

//<-------------------------------DIVISION FUnction---------------------------->

int subtraction_for_div(Dlist **head1, Dlist **tail1,
                        Dlist **head2, Dlist **tail2)
{
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    int borrow = 0, sub;

    while (temp1)
    {
        sub = temp1->data - borrow;

        if (temp2)
        {
            sub -= temp2->data;
            temp2 = temp2->prev;
        }

        if (sub < 0)
        {
            sub += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        temp1->data = sub;
        temp1 = temp1->prev;
    }

    // Remove leading zeros
    while (*head1 && (*head1)->data == 0 &&
           *head1 != *tail1)
    {
        Dlist *del = *head1;
        *head1 = (*head1)->next;
        (*head1)->prev = NULL;
        free(del);
    }

    return SUCCESS;
}
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    Dlist *temp = *head1;
    Dlist *remhead = NULL;
    Dlist *remtail = NULL;
    int count = 0;

    if (*head2 == NULL)
        return FAILURE;

    while (temp)
    {
        // bring down next dividend digit in reminder
        dl_insert_last(&remhead, &remtail, temp->data);
        count = 0;
        // printf("temp %d", temp->data);
        // subtract divisor until remainder is smaller
        while (compare_numbers(&remhead, head2) >= 0)
        {

            subtraction_for_div(&remhead, &remtail, head2, tail2);
            count++;
        }
        // Store quotient digit
        dl_insert_last(&Rhead, &Rtail, count);

        temp = temp->next;
    }

    // Remove leading zeros from quotient
    while (Rhead && Rhead->data == 0 && Rhead != Rtail)
    {
        Dlist *del = Rhead;
        Rhead = Rhead->next;
        Rhead->prev = NULL;
        free(del);
    }

    // Free remainder list
    while (remhead)
    {
        Dlist *del = remhead;
        remhead = remhead->next;
        free(del);
    }

    return SUCCESS;
}