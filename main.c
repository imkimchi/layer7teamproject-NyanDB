#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node // 1:n 관계를 지원하기위해, data 들을 연결하는 list
{
   char key[40];
   char value[40];
   struct node *next;
   struct node *prev;
}node;

typedef struct varnode // 1:n 관계를 지원하기위해, data를 그룹화 시키는 변수명
{
   char varname[40];
   int cnt;
   struct node *head, *tail, *current;
   struct varnode *next, *prev;
}varnode;

typedef struct list
{
   char tname[40];
   int varcnt;
   int tablecnt;
   struct varnode *head, *tail, *current;
   struct list *next, *prev;
}list;

list *makelist(void); // 3차원 리스트 생성
void putlist(list **head, list **tail, list *current); // 3차원 리스트에 항목 추가

void simpleinput(list *head); // 변수에 대입
void putvar(varnode **head, varnode **tail, varnode *current, list *thead);
void putnode(node **head, node **tail, node *current, list *thead);

varnode *makevarnode(void);

node * makedatanode(void);

list *findtable(list *head);
varnode *findvar(varnode *head);

void search(list *head);
int search_var(varnode *head);

void deltable(list **head, list **tail);
void delvar(varnode **head, varnode **tail);
void killvar(list *head);

void printtable(list *head);
void printlist(varnode *head);
void printnode(node *head);

void save(list *head);
void savevarnode(varnode *head, FILE *fp);
void savenode(node *head, FILE *fp);

void load(list **head, list **tail);
void firstload(list *head, FILE *fp);
void putvar_load(varnode **head, varnode **tail, varnode *current);
void putlist_load(list **head, list **tail, list *current);
void putnode_load(node **head, node **tail, node *current);

int main(void)
{
   list *head, *tail, *current;

   int mode = 0;

   head = tail = current = NULL;
   while (1)
   {
      puts("[1] 테이블 생성");
      puts("[2] 테이블 입력");
      puts("[3] 테이블 삭제");
      puts("[4] 데이터 삭제");
      puts("[5] 출력");
      puts("[6] 검색");
      puts("[7] 저장");
      puts("[8] 로드");
      puts("[0] 종료");
      scanf("%d%*c", &mode);
      if (mode == 1)
      {
         current = makelist();
         putlist(&head, &tail, current);
      }
      else if (mode == 2)
      {
         simpleinput(head);
      }
      else if (mode == 3)
      {
         deltable(&head, &tail);
      }
      else if (mode == 4)
      {
         killvar(head);
      }
      else if (mode == 5)
      {
         printtable(head);
      }
      else if (mode == 6)
      {
         search(head);
      }
      else if (mode == 7)
      {
         save(head);
      }
      else if (mode == 8)
      {
         head = tail = current = NULL;
         load(&head, &tail);
      }
      else if (mode == 0)
      {
         exit(1);
      }
      else
      {
         continue;
      }
   }
}


void putlist(list **head, list **tail, list *current)
{
   if (*head == NULL)
   {
      *head = *tail = current;
      (*head)->tablecnt++;
   }
   else
   {
      (*tail)->next = current;
      current->prev = *tail;
      *tail = current;
      (*head)->tablecnt++;
   }
}
void putlist_load(list **head, list **tail, list *current)
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
void putvar(varnode **head, varnode **tail, varnode *current, list *thead)
{
   if (*head == NULL)
   {
      *head = *tail = current;
      thead->varcnt++;
   }
   else
   {
      (*tail)->next = current;
      current->prev = *tail;
      *tail = current;
      thead->varcnt++;
   }
}
void putvar_load(varnode **head, varnode **tail, varnode *current)
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
void putnode(node **head, node **tail, node *current, list *thead)
{
   if (*head == NULL)
   {
      *head = *tail = current;
      thead->current->cnt++;
   }
   else
   {
      (*tail)->next = current;
      current->prev = *tail;
      *tail = current;
      thead->current->cnt++;
   }
}
void putnode_load(node **head, node **tail, node *current)
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
void simpleinput(list *head)
{
   list *temp;
   temp = findtable(head);
   if (temp != NULL)
   {
      temp->current = makevarnode();
      putvar(&temp->head, &temp->tail, temp->current, head);
      temp->current->current = makedatanode();
      putnode(&temp->current->head, &temp->current->tail, temp->current->current, head);
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
      {
         return head;
      }
      else
      {
         head = head->next;
      }
   }
   return NULL;
}
varnode *findvar(varnode *head)
{
   char varname[40];
   puts("변수명을 입력하여 주십시오.");
   scanf("%s%*c", varname);
   while (head)
   {
      if (strcmp(varname, head->varname) == 0)
         return head;
      else
         head = head->next;
   }
   return NULL;
}
list *makelist(void)
{
   list *temp;
   temp = (list*)calloc(1, sizeof(list));
   puts("테이블의 이름을 입력하여 주십시오.");
   scanf("%s%*c", temp->tname);
   return temp;
}

varnode *makevarnode(void)
{
   varnode *temp;
   temp = (varnode*)calloc(1, sizeof(varnode));
   puts("Key 를 입력하여 주십시오.");
   scanf("%s%*c", temp->varname);
   return temp;
}
node * makedatanode(void)
{
   node *temp;
   temp = (node*)calloc(1, sizeof(node));
   puts("Value 입력");
   scanf("%s%*c", temp->value);
   return temp;
}

void deltable(list **head, list **tail)
{
   list *temp;
   temp = findtable(*head);
   if (!temp)
      return;
   else if (temp == *head)
   {
      *head = (*head)->next;
      if (*head != NULL)
      {
         (*head)->prev = NULL;
      }
      free(temp);
   }
   else if (temp == *tail)
   {
      *tail = temp->prev;
      if (*tail != NULL)
         (*tail)->next = NULL;
      free(temp);
   }
   else
   {
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
      free(temp);
   }
}
void delvar(varnode **head, varnode **tail)
{
   varnode *temp;
   temp = findvar(*head);
   if (!temp)
      return;
   else if (temp == *head)
   {
      *head = (*head)->next;
      if (*head != NULL)
      {
         (*head)->prev = NULL;
      }
      free(temp);
   }
   else if (temp == *tail)
   {
      *tail = temp->prev;
      if (*tail != NULL)
         (*tail)->next = NULL;
      free(temp);
   }
   else
   {
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
      free(temp);
   }
}
void killvar(list *head)
{
   list *temp;
   temp = findtable(head);
   if (!temp)
      return;
   delvar(&temp->head, &temp->tail);
}

void printtable(list *head)
{
   list *temp;
   temp = findtable(head);
   if (temp != NULL)
   {
      printlist(temp->head);
   }
   else
   {
      puts("테이블이 없습니다.");
   }
}
void printlist(varnode *head)
{
   while (head)
   {
      printf("%s : ", head->varname);
      printnode(head->head);
      puts("");
      head = head->next;
   }
}
void printnode(node *head)
{
   while (head)
   {
      printf("%s", head->value);
      head = head->next;
   }
}
void search(list *head)
{
   list *temp;
   temp = findtable(head);
   if (!temp)
   {
      puts("테이블이 없습니다.");
   }
   else
   {
      if (!search_var(temp->head))
      {

      }
   }
}
int search_var(varnode *head)
{
   char varname[40];
   puts("검색할 변수를 입력하여 주십시오.");
   scanf("%s%*c", varname);
   while (head)
   {
      if (strcmp(head->varname, varname) == 0)
      {
         printf("%s : %s\n", head->varname, head->head->value);
         return 1;
      }
      else
      {
         head = head->next;
      }
   }
   return 0;
}
void save(list *head)
{
   FILE *fp;
   char fname[50] = {};
   if (head)
   {
      printf("저장할 파일의 이름 입력 :");
      scanf("%s%*c", fname);
      fp = fopen(fname, "wb");
      while (head)
      {
         fwrite(head, sizeof(list), 1, fp);
         savevarnode(head->head, fp);
         head = head->next;
      }
      fclose(fp);
   }
}
void savevarnode(varnode *head, FILE *fp)
{
   while (head)
   {
      fwrite(head, sizeof(varnode), 1, fp);
      savenode(head->head, fp);
      head = head->next;
   }
}
void savenode(node *head, FILE *fp)
{
   while (head)
   {
      fwrite(head, sizeof(node), 1, fp);
      head = head->next;
   }
}
void load(list **head, list **tail)
{
   int i;
   FILE *fp;
   list *current;

   char fname[50] = {};
   printf("불러올 파일의 이름 :");
   scanf("%s%*c", fname);
   fp = fopen(fname, "rb");
   current = (list*)calloc(1, sizeof(list));
   fread(current, sizeof(list), 1, fp);
   putlist_load(head, tail, current);
   firstload(current, fp);
   for (i = 0; i < (*head)->tablecnt-1; i++)
   {
      current = (list*)calloc(1, sizeof(list));
      fread(current, sizeof(list), 1, fp);
      putlist_load(head, tail, current);
      firstload(current, fp);
   }
   fclose(fp);
}
void firstload(list *head, FILE *fp)
{
   int i;
   head->current = (varnode*)calloc(1, sizeof(varnode));
   fread(head->current, sizeof(varnode), 1, fp);
   head->current->head = head->current->tail = NULL;
   head->head = head->tail = NULL;
   putvar_load(&head->head, &head->tail, head->current);
   for (i = 0; i < head->current->cnt; i++)
   {
      head->current->current = (node*)calloc(1, sizeof(node));
      fread(head->current->current, sizeof(node), 1, fp);
      putnode_load(&(head->current->head), &(head->current->tail), head->current->current);
   }
}
