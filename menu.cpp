#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Student
{
	char name[25];
	char province[25];
	int birth_year;
	float english;

} Object;

int length = 0;
Object *list = NULL;

time_t t = time(NULL);
struct tm tm = *localtime(&t);
int now = tm.tm_year + 1900;

void columns()
{
	puts("+-------------------------------------------------------------------+");
	puts("| No# | Name                 | Province    |Birth Year|English Level|");
	puts("+-------------------------------------------------------------------+");
}

void row(Object obj, int num)
{
	printf("| %-3d | %-20s | %-11s | %9d | %11.2f|",num, obj.name, obj.province, obj.birth_year, obj.english);
	puts("\n+-------------------------------------------------------------------+");
}

void output()
{
	columns(); 

	int i;
	for (i = 0; i < length; i++)
	{
		row(list[i], i + 1);	
	}
}

void input()
{
	puts("\n Enter array length: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &length);

	free(list);
	list = (Object*)malloc(length * sizeof(Object));

	int i,age,year;
	float eng;
	for (i = 0; i < length; i++)
	{
		printf("\n Enter data for student [%d]: ", i + 1);

		puts("\n Name: ");
		fflush(stdin); fflush(stdout);
		gets(list[i].name);
		
		puts("\n Province: ");
		fflush(stdin); fflush(stdout);
		gets(list[i].province);

		re_enter_year:
			puts("\n Birth Year: ");
			fflush(stdin); fflush(stdout);
			scanf("%d", &year);
			age = now - year;
			if((age <= 18) || (age >= 45)){
				goto re_enter_year;
			} else {
				list[i].birth_year = year;
			}
		
		re_enter_english:
			puts("\n English Level: ");
			fflush(stdin); fflush(stdout);
			scanf("%f", &eng);
			if ((eng < (float)0) || (eng > (float)10)){
				goto re_enter_english;
			} else {
				list[i].english = eng;
			}

	}
	printf("List of Students: \n");
	output();
}

void sort()
{

	if (list==NULL)
	{
		perror("Error-Cannot sort an empty list !");
		return;
	}
	
	int i, j;
	for (i = 0; i < length; i++)
	{
		for (j = i + 1; j < length; j++)
		{
			int logic = strcmp(list[i].name, list[j].name) < 0;
			if (!logic) 
			{
				Object temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
	printf("List of Students in ascending order: \n");
	output();
}

void analyze()
{
	if (list==NULL)
	{
		perror("Error-Cannot analyze an empty list !");
		return;
	}

	int sl[length];

	int i;
	for (i=0; i < length; i++)
	{
		sl[i] = 1;
	}

	for (i=0; i < length; i++)
	{
		int j;
		for (j=i+1; j < length; j++)
		{
			if (sl[j] != 0)
			{
				if (list[i].birth_year==list[j].birth_year)
				{
					sl[i]++;
					sl[j]--;
				}
			}
		}

	}

	for (i=0; i<length; i++)
	{
		if (sl[i] != 0)
		{
			printf("\n+ There are %d student(s) born in  %d.", sl[i], list[i].birth_year);
		}
	}
}

void find()
{
	if (list==NULL)
	{
		perror("Error-Cannot find in an empty list !");
		return;
	}
	
	int min = list[0].birth_year;
	int count = 0;

	int i;
	for (i=0; i < length; i++)
	{
		if (min > list[i].birth_year)
		{
			min = list[i].birth_year;
		}
	}

	printf("\n Search Results (Oldest Students): \n");
	for (i=0; i < length; i++)
	{
		if (min == list[i].birth_year)
		{
			count++;

			if (count == 1)
				columns();

			row(list[i], count);
		}
	}

	if (count)
	{
		printf("\n %d student(s) found.", count);
		return;
	}

	printf("\n Not found!");
}

void save()
{
	char file_name[255];
	puts("\n File name: ");
	fflush(stdin); fflush(stdout);
	gets(file_name);

	FILE *fp;
	fp = fopen(file_name, "wb");

	if (fp == NULL)
	{
		perror("\n Error-Cannot open file ! \n");
		fclose(fp);
		return;
	}

	int i;
	for (i=0; i < length; i++)
	{
		fwrite((char *)&list[i], sizeof(Object), 1, fp);
	}

	puts("\n File save successfully!");

	fclose(fp);
}

void open()
{
	char file_name[255];
	puts("\n File name: ");
	fflush(stdin); fflush(stdout);
	gets(file_name);

	FILE *fp;
	fp = fopen(file_name, "rb");

	if (fp == NULL)
	{
		perror("\n Error-Cannot open file ! \n");
		fclose(fp);
		return;
	}

	int count = 0;
	Object obj;

	while( fread((char *)&obj, sizeof(Object), 1, fp)  == 1 )
	{
		if(count==0)
			columns();

		row(obj,++count);
	}

	puts("\n File open completed !");

	fclose(fp);
}

void exit(){
	
}

void free_list()
{
	free(list);
	list=NULL;
}

main()
{
	while(1)
	{
		puts("+-------------------------------------------------------------------------+");
		puts("|                 STUDENT PROFILE MANAGEMENT PROGRAM                      |");
		puts("+-------------------------------------------------------------------------+");
		puts("| 1. Input | 2. Sort | 3. Analyze | 4. Find | 5. Save | 6. Open | 7. Exit |");
		puts("+-------------------------------------------------------------------------+");

		char choice;
	input_choice:
		puts("\n  Your Choice: ");
		fflush(stdin); fflush(stdout);
		scanf("%c", &choice);

		switch (choice)
		{
			case '1':
				input();
				break;
			case '2':
				sort();
				break;
			case '3':
				analyze();
				break;
			case '4':
				find();
				break;
			case '5':
				save();
				break;
			case '6':
				open();
				break;
			case '7':
			case 'n':
			case 'N':
				free_list();
				puts("\n Good bye!");
				exit(EXIT_SUCCESS);
			case 'y':
			case 'Y':
				continue;
			case 'c':
			case 'C':
				system("cls");
				break;
			default:
				puts("\n Invalid choice!");
				break;
		}

		puts("\n  Do you want to continue ?");
		puts("\n   - Yes, I do. (press 'y', 'Y')");
		puts("\n   - No, I do not. (press 'n', 'N')");
		puts("\n   - Please clear the screen ! (press 'c', 'C')");
		goto input_choice;
	}
}
