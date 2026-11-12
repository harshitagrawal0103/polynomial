
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int coeff, exp;
    struct Node *next;
};

// Create and insert a node
void insert(struct Node **head, int c, int e)
{
    struct Node *newNode, *temp;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = c;
    newNode->exp = e;
    newNode->next = NULL;

    if (*head == NULL)
        *head = newNode;
    else
    {
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }
}

// Polynomial Creation Module
struct Node* create()
{
    struct Node *head = NULL;
    int n, c, e, i;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter coefficient and exponent: ");
        scanf("%d%d", &c, &e);
        insert(&head, c, e);
    }
    return head;
}

// Polynomial Display Module
void display(struct Node *p)
{
    while (p != NULL)
    {
        printf("%dx^%d", p->coeff, p->exp);
        if (p->next != NULL)
            printf(" + ");
        p = p->next;
    }
    printf("\n");
}

// Addition and Subtraction Module
struct Node* calculate(struct Node *p, struct Node *q, int sign)
{
    struct Node *r = NULL, *t;

    for (t = p; t != NULL; t = t->next)
        insert(&r, t->coeff, t->exp);

    for (t = q; t != NULL; t = t->next)
    {
        struct Node *temp = r;
        while (temp != NULL && temp->exp != t->exp)
            temp = temp->next;

        if (temp != NULL)
            temp->coeff += sign * t->coeff;
        else
            insert(&r, sign * t->coeff, t->exp);
    }
    return r;
}

// Multiplication Module
struct Node* multiply(struct Node *p, struct Node *q)
{
    struct Node *r = NULL, *a, *b;

    for (a = p; a != NULL; a = a->next)
    {
        for (b = q; b != NULL; b = b->next)
        {
            int c = a->coeff * b->coeff;
            int e = a->exp + b->exp;
            insert(&r, c, e);
        }
    }
    return r;
}

// Evaluation Module
int evaluate(struct Node *p, int x)
{
    int sum = 0, power;

    while (p != NULL)
    {
        power = 1;
        for (int i = 0; i < p->exp; i++)
            power *= x;

        sum += p->coeff * power;
        p = p->next;
    }
    return sum;
}

int main()
{
    struct Node *p = NULL, *q = NULL, *r = NULL;
    int ch, x;

    while (1)
    {
        printf("\n1.Create Polynomial");
        printf("\n2.Display Polynomial");
        printf("\n3.Addition");
        printf("\n4.Subtraction");
        printf("\n5.Multiplication");
        printf("\n6.Evaluation");
        printf("\n7.Exit");

        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                p = create();
                q = create();
                break;

            case 2:
                printf("First: ");
                display(p);
                printf("Second: ");
                display(q);
                break;

            case 3:
                r = calculate(p, q, 1);
                display(r);
                break;

            case 4:
                r = calculate(p, q, -1);
                display(r);
                break;

            case 5:
                r = multiply(p, q);
                display(r);
                break;

            case 6:
                printf("Enter x: ");
                scanf("%d", &x);
                printf("Result = %d", evaluate(p, x));
                break;

            case 7:
                return 0;

            default:
                printf("Invalid choice!");
        }
    }
}
