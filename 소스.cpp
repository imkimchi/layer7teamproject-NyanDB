#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list
{
	char tname[40];
	int i;
	struct list *next;
	struct list *prev;
	struct node *head, *tail, *current;

}list;

typedef struct node
{
	int id;

	char name[20];
	char number[20];
	char addr[100];

	struct node *next;
	struct node *prev;

}node;

list *makelist(void);
void putlist(list **head, list**tail, list *current);
void inputtable(list *head);
list *findtable(list *head);
void printtable(node *head);
void printmode(list *head);
node *makedata(list *head);
void putdata(node **head, node **tail, node *current);
void printall(list *head);
void killlist(list **head, list **tail);
void delall(node *head);
void search(list *head);
void finddata(node *head);
void delnode(list *head);
void killdata(node **head, node **tail);

int main(void)
{
	list *head, *tail, *current;
	int mode;
	int mode2;
	head = tail = current = NULL;
	while (1)
	{
		puts("[1] 테이블 생성");
		puts("[2] 테이블 편집");
		puts("[3] 테이블 출력");
		puts("[4] 테이블 삭제");
		puts("[5] 종료");
		scanf("%d%*c", &mode);
		if (mode == 1)
		{
			current = makelist();
			putlist(&head, &tail, current);
		}
		else if (mode == 2)
		{
			while (1)
			{
				puts("[1] 입력");
				puts("[2] 검색");
				puts("[3] 삭제");
				puts("[4] 수정");
				puts("[5] 삽입");
				puts("[6] 출력");
				puts("[7] 되돌아가기");
				scanf("%d", &mode2);
				if (mode2 == 1)
				{
					inputtable(head);
				}
				else if (mode2 == 2)
				{
					search(head);
				}
				else if (mode2 == 3)
				{
					delnode(head);
				}
				else if (mode2 == 4)
				{

				}
				else if (mode2 == 5)
				{

				}
				else if (mode2 == 6)
				{
					printmode(head);
				}
				else if (mode2 == 7)
				{
					break;
				}
				else
					continue;
			}
		}
		else if (mode == 3)
		{
			printall(head);
		}
		else if (mode == 4)
		{
			killlist(&head, &tail);
		}
		else if (mode == 5)
		{
			exit(1);
		}
		else
		{
			continue;
		}
	}
}

list *makelist(void)
{
	list *temp;
	temp = (list*)calloc(1, sizeof(list));
	temp->i = 1;
	puts("테이블의 이름을 입력하여 주십시오.");
	scanf("%s%*c", temp->tname);
	return temp;
}
void putlist(list **head, list**tail, list *current)
{
	if (*head == NULL)
	{
		*head = *tail = current;
	}
	else
	{
		(*tail)->next = current;
		current->prev = *tail;
		*tail = current;
	}
}
void inputtable(list *head)
{
	list *temp;
	temp = findtable(head);
	if (temp == NULL)
	{
		puts("입력한 테이블이 없습니다.");
	}
	else
	{
		temp->current = makedata(head);
		putdata(&temp->head, &temp->tail, temp->current);
	}
}

list *findtable(list *head)
{
	char tname[40];
	puts("테이블의 이름을 입력하여 주십시오.");
	scanf("%s%*c", tname);
	while (head)
	{
		if (strcmp(tname, head->tname) == 0)
			return head;
		else
			head = head->next;
	}
	return NULL;
}
node *makedata(list *head)
{
	node *temp;
	temp = (node *)calloc(1, sizeof(node));
	temp->id = head->i++;
	puts("이름을 입력하여 주십시오.");
	scanf("%s%*c", temp->name);
	puts("번호를 입력하여 주십시오.");
	scanf("%s%*c", temp->number);
	puts("주소를 입력하여 주십시오.");
	scanf("%s%*c", temp->addr);
	return temp;
}
void putdata(node **head, node **tail, node *current)
{
	if (*head == NULL)
	{
		*head = *tail = current;
	}
	else
	{
		(*tail)->next = current;
		current->prev = *tail;
		*tail = current;
	}
}
void printtable(node *head)
{
	while (head)
	{
		printf("id : %d 이름 : %s 번호 : %s 주소 : %s\n", head->id, head->name, head->number, head->addr);
		head = head->next;
	}
}
void printmode(list *head)
{
	list *temp;
	temp = findtable(head);
	printtable(temp->head);
}
void printall(list *head)
{
	while (head)
	{
		printf("\"%s\" :\n{\n", head->tname);
		printtable(head->head);
		printf("}\n");
		head = head -> next;
	}
}
void killlist(list **head, list **tail)
{
	list *temp;
	temp = findtable(*head);
	if (temp == NULL)
	{
		puts("테이블이 없습니다.");
		return;
	}
	else if (temp == *head)
	{
		(*head) = temp->next;
		if (*head != NULL)
			(*head)->prev = NULL;
		delall(temp->head);
		free(temp);
	}
	else if (temp == *tail)
	{
		*tail = (*tail)->prev;
		(*tail)->next = NULL;
		delall(temp->head);
		free(temp);
	}
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delall(temp->head);
		free(temp);
	}
}
void delall(node *head)
{
	node *temp;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}
void search(list *head)
{
	list *temp;
	
	temp = findtable(head);
	finddata(temp->head);
}
void finddata(node *head)
{
	char name[20];
	puts("검색할 자료의 이름을 입력하여 주십시오.");
	scanf("%s%*c", name);
	while (head)
	{
		if (strcmp(head->name, name) == 0)
		{
			printf("%d : 이름 : %s 번호 : %s 주소 : %s\n", head->id, head->name, head->number, head->addr);
			return;
		}
		head = head->next;
	}
	puts("검색하는 자료가 없습니다.");
}
void delnode(list *head)
{
	list *temp;
	temp = findtable(head);
	killdata(&temp->head, &temp->tail);
}
void killdata(node **head, node **tail)
{

}