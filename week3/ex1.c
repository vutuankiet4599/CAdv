#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PHONE_NUMBER 1000


typedef struct {
	long number;
	char name[80];
}PhoneEntry;

typedef struct {
	PhoneEntry entries[MAX_PHONE_NUMBER];
	int total;
}PhoneBook;

void addPhoneNumber(long number, char *name, PhoneBook *book)
{
	int i = book->total;
	book->entries[i].number=number;
	strcpy(book->entries[i].name,name);
	book->total++;
}

void swap(PhoneBook *book, int i, int j)
{
	PhoneEntry temp;
	temp = book->entries[i];
	book->entries[i] = book->entries[j];
	book->entries[j] = temp;
}

void qsort3way(PhoneBook *a, int left, int right)
{
	if(right <= left)return;
	int i = left-1, j = right;
	int m = left-1, n = right;
	while(1)
	{
		while(a->entries[++i].number<a->entries[right].number);
		while(a->entries[right].number<a->entries[--j].number) if(j==1)break;
		if (i>=j)break;
		swap(a,i,j);
		if(a->entries[i].number==a->entries[right].number)swap(a,++m,i);
		if(a->entries[j].number==a->entries[right].number)swap(a,--n,j);
	}
	swap(a, i, right);
	j=i-1;
	i=i+1;
	for(int k = left; k<=m; k++)swap(a,k,j--);
	for(int k = right-1; k>=n; k--)swap(a,k,i++);
	qsort3way(a,left,j);
	qsort3way(a,i,right);
}

char *getPhoneNumber(long number, PhoneBook* book,int l, int r)
{
	int i=(l+r)/2;
	if(number==book->entries[i].number)return book->entries[i].name;
	else if(number<book->entries[i].number)return getPhoneNumber(number, book, l, i-1);
	else return getPhoneNumber(number, book, i+1, r);
	return NULL;
	
}
int main()
{
	PhoneBook book[1];
	book[0].total=0;
	long number;
	char name[80];
	for (int i=0;i<5;i++)
	{
		printf("Nhap sdt :");
		scanf("%ld",&number);
		fflush(stdin);
		printf("Nhap ten: ");
		gets(name);
		addPhoneNumber(number,name,book);
	}

	qsort3way(&book[0],0,book->total-1);
	char name1[80];
	strcpy(name1,getPhoneNumber(345,book,0,4));
	if(NULL!=name1)
	printf("%s",name1);
	return 1;
}
