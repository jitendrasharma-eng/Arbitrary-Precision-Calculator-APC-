#include "apc.h"

Dlist *Rhead = NULL;
Dlist *Rtail = NULL;

// for multiplication
Dlist *R1head = NULL, *R1tail = NULL;
Dlist *R2head = NULL, *R2tail = NULL;

void invalid()
{
    printf("Invalic Input !!\n");
    printf("Comant should be Include: ./a.out (integer_number1) (operator) (interger_number2)\n");
    printf("Operators\n");
    printf("+ : For Addition\n");
    printf("- : For Subtraction\n");
    printf("x : For Multiplication\n");
    printf("/ : For Division\n");
    printf("Example: ./a.out 1234 + 5678\n");
}
int main(int argc, char *argv[]) // or mian(int argc, char **argv)
{
    if (argc != 4)
    {
        invalid();
        return 0;
    }
    int choice;

    Dlist *head1 = NULL, *tail1 = NULL; // num1
    Dlist *head2 = NULL, *tail2 = NULL; // num2

    int i = 0, num;
    while (argv[1][i] != '\0')
    {
        if (argv[1][i] >= '0' && argv[1][i] <= '9')
        {
            num = (argv[1][i] - '0');
            dl_insert_last(&head1, &tail1, num);
        }
        else
        {
            invalid();
            return 0;
        }
        i++;
    }

    i = 0;
    while (argv[3][i] != '\0')
    {
        if (argv[3][i] >= '0' && argv[3][i] <= '9')
        {
            num = (argv[3][i] - '0');
            dl_insert_last(&head2, &tail2, num);
        }
        else
        {
            printf("Invalid input!!");
            return 0;
        }
        i++;
    }

    switch (argv[2][0])
    {
    case '+':
        if (addition(&tail1, &tail2) == SUCCESS)
        {
            printf("INFO: Addition Done Successfull\n");
            printf("Result: ");
            display(&Rhead);
        }
        else
        {
            printf("INFO: Addition Failed, Lis is empty\n");
        }
        break;

    case '-':
        if (subtraction(&tail1, &tail2, &head1, &head2) == SUCCESS)
        {
            printf("INFO: Subtraction Done Successfull\n");
             printf("Result: ");
            int ret = compare_numbers(&head1, &head2);

            if (ret == -1)
                printf("-");
            display(&Rhead);
        }
        else
        {
            printf("INFO: Subtraction Failed, Lis is empty\n");
        }
        break;

    case 'x':
        if (multiplication(&tail1, &tail2) == SUCCESS)
        {
            printf("INFO: Multiplication Done Successfull\n");
             printf("Result: ");
            display(&Rhead);
        }
        else
        {
            printf("INFO: Multiplication Failed, Lis is empty\n");
        }
        break;

    case '/':
        if (division(&head1, &tail1, &head2, &tail2) == SUCCESS)
        {
            printf("INFO: Division Done Successfull\n");
             printf("Result: ");
            display(&Rhead);
        }
        else
        {
            printf("INFO: Division Failed, Lis is empty\n");
        }
        break;
    }

    return 0;
}
