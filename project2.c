/*Ioannis Bozionelos
AM:2022202300157
dit23157@uop.gr

Konstantinos Velentzas
AM:2022202300243
dit23243@uop.gr
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


typedef struct																									//dhlwsh struct gia thn hmeromhnia gennhshs tou disekatommyriouxou
{
int day;
int month;
int year;
} mydate;

typedef struct																									//dhlwsh struct gia thn wra gennhshs tou disekatommyriouxou
{
int hour;
int minutes;
} mytime;

typedef struct bilList																							//dhlwsh struct gia ola ta epithumita dedomena tou disekatommyriouxou
{
char name[100];
char location[100];
char activity[100];
char origin[100];
char sex;
mydate birthdate;
mytime birthtime;
float fortune;
char acc[14];
struct bilList *next;
struct bilList *prev;
} billionaire;

billionaire *head;																								//kefalh ths listas

int read_text(char str[], int size, int flag);
void capitalization(char *alf);
void Unknown(char *alf);
void addbillionaire(char *str);
void insertbillionaire(billionaire *newbill);
void deletebill(char xar);
void createaccount();
void findbill(char xar, char *str);
void savefile(char *str);
void loadfile(int number, char *str);
void printbill(char xar, char *str);

int main(void)
{
	printf("Welcome to the Billionaires Statistics Program! This program stores, manages, and generates statistical data for billionaires as published by Forbes magazine. Forbes is an American business magazine that publishes articles on economics, industry, investing, and marketing, as well as topics related to technologycommunications, science, politics, and law.\nWhy does Forbes interest us?\nSince March 1987, Forbes has annually released a ranking of individuals who are billionaires, meaning they have a net worth of $1 billion or more. This list is known as The World's Billionaires.\nFun Fact: In 2018, Amazon founder Jeff Bezos topped the list for the first time, becoming the first person with over $100 billion included in the list, surpassing Microsoft founder Bill Gates, who had topped the list for 18 of the previous 24 years. In 2022, after four consecutive years at the top, Elon Musk (head of Twitter, SpaceX, Tesla Inc., etc.) surpassed Bezos. In 2023, French entrepreneur Bernard Arnault of Louis Vuitton became the first Frenchman to reach the top of the list.\nEnjoy exploring the fascinating world of the richest people on the planet!\n\n\n");
	
	billionaire list;
	billionaire *i;
	char answer;
	float sum = 0;																								//dhlwsh metablhths sum gia thn ektypwsh ths sunolikhs periousias twn disekatommuriouxwn
	int arithmos;

	head=NULL;
	

	printf("!Function list!:\n1.For successfully adding a billionaire to the list type this exact command: newbill Name;City/Country;Activity;Motherland;Sex;Birthdate Birthtime;Fortune;\n2.For printing the total billionaires' fortune combined type sum\n3.Υοu can use the commands findN, findC, and findS followed by a word or part of a word to filter and display magnates whose names, cities/countries of origin or operation, or activities contain the specified alphanumeric string(findN will display magnates whose names contain the specified string, findC will display magnates whose city or country of origin or operation contains the specified string, findS will display magnates whose activity descriptions contain the specified string)\n4.Type the commands print+, print-, and print= followed by a numerical value, date, or time to filter and display magnates (along with their details and account number) based on their wealth, birthdate, or birth time(print+ will display magnates with values greater than the specified number, print- will display magnates with values less than the specified number, print= will display magnates with values equal to the specified number)\n");
	printf("5.For deleting the firt/last billionaire type deleteN/deleteO\n6.You can use the command save filename to save the data from the list into a file. The file created will be a text file, with each magnate's data stored on a separate line using a semicolon (;) as the field delimiter\n7.Υou can use the command load number filename to read data from a properly formatted fileou can use the command load number filename to read data from a properly formatted file\n");
	printf("!Note:If you don't recognise one of the billionaire's activity country/city type ? or Unknown and the programm will convert the questionmark to Unknown!\n");
	printf("!Note:If you wish to terminate the programma type exit or EXIT!\n\n\n");

	srand(time(NULL));
	while(1)	
	{
		printf("!Type the command you desire based on the function list!\n");
		char ar[100]={0};

		read_text(ar, sizeof(ar), 1);
		
		if(!strcmp(ar, "exit") || !strcmp(ar, "EXIT"))															//periptwsh o xrhsths na grapsei exit
		{
			printf("Are you sure you want to terminate the programm(y/n)?\n");
			do		
			{
				answer= getchar();
				getchar();
			}while(answer!='y' && answer!='n' && answer!='Y' && answer!='N');
			if(answer=='y' || answer=='Y')
			{
				if(head==NULL)
					exit(EXIT_FAILURE);
					
				billionaire *temp1=head, *temp2;
				do
				{
					temp1=temp2 -> next;
					free(temp1);
				}while(temp2!=head);
				free(head);

				printf("Programm terminated!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if(!strncmp(ar, "newbil ", 7))																		//periptwsh o xrhsths na grapsei newbill gia na eisagei enan disekatommuriouxou
		{
			if( strlen(ar)>7)
				addbillionaire(ar+7);
		}
		else if(!strcmp(ar, "sum"))																				//periptwsh o xrhsths na grapsei sum gia na tupwsei thn sunolikh periousia twn disekatommuriouxwn
		{

			if(head==NULL)
			{
				printf("The list is empty, the total fortune is 0$\n");
				continue;
			}
			
			sum = 0;     
			i=head;
			sum=sum + i -> fortune;
			i=i -> next;
			while(1)
			{
				if(i!=head)
				{
					sum=sum + i -> fortune;
					i=i -> next;
				}
				else
					break;
			}
			
			printf("The total fortune of the list's billionaires is %f$", sum); 
			
		}
		else if(!strncmp(ar, "findN ", 6))																		//periptwsh o xrhsths na epithumei na brei kai na tupwsei disekatommuriouxous pou ta onomata tous exoun mia lexh mesa tous
		{
			findbill('N', ar+6);
		}
		else if(!strncmp(ar, "findC ", 6))																		//periptwsh o xrhsths na epithumei na brei kai na tupwsei disekatommuriouxous pou oi poleis-xwres drasthriothtas tous exoun mia lexh mesa tous
		{
			findbill('C', ar+6);
		}
		else if(!strncmp(ar, "findS ", 6))																		//periptwsh o xrhsths na epithumei na brei kai na tupwsei disekatommuriouxous pou oi drasthriothtes tous exoun mia lexh mesa tous
		{
			findbill('S', ar+6);
		}
		else if(!strncmp(ar, "print+", 6))																		//periptwsh o xrhsths na epithumei na tupwsei disekatommuriouxous pou h hmeromnhnia gennhshs/wra gennhshs/periousia einai megaluterh/mikroterh/ish apo allous
		{
			printbill('+', ar+6);
		}
		else if(!strncmp(ar, "print-", 6))																		//periptwsh o xrhsths na epithumei na tupwsei disekatommuriouxous pou h hmeromnhnia gennhshs/wra gennhshs/periousia einai megaluterh/mikroterh/ish apo allous
		{
			printbill('-', ar+6);
		}
		else if(!strncmp(ar, "print=", 6))																		//periptwsh o xrhsths na epithumei na tupwsei disekatommuriouxous pou h hmeromnhnia gennhshs/wra gennhshs/periousia einai megaluterh/mikroterh/ish apo allous
		{
			printbill('=', ar+6);
		}
		else if(!strncmp(ar, "deleteN", 7))																		//periptwsh o xrhsths na diagrapsei ton pio prosfata prostithemeno apo tous uparxontes disekatommuriouxo
		{
			deletebill('N');
		}
		else if(!strncmp(ar, "deleteO", 7))																		//periptwsh o xrhsths na diagrapsei ton pio paliotera prostithemeno apo tous uparxontes disekatommuriouxo
		{
			deletebill('O');
		}
		else if(!strncmp(ar, "save ", 5))																		//periptwsh o xrhsths na apothikeysei disekatommuriouxous se ena arxeio keimenou
		{
			savefile(ar+5);
		}
		else if(!strncmp(ar, "load ", 5))																		//periptwsh o xrhsths na fortwsei dedomena apo ena arxeio
		{
			if(atoi(ar+5)<=9)
				arithmos=7;
			else if(atoi(ar+5)<=99)
				arithmos=8;
			else if(atoi(ar+5)<=999)
				arithmos=9;
			else if(atoi(ar+5)<=9999)
				arithmos=10;
			loadfile(atoi(ar+5), ar+arithmos);
		}
		else																									//periptwsh lathous
		{
			printf("Something went wrong...type CORRECTLY the function you desire to carry out out of the function list!\n");
		}
	}
	return 0;
}


	


	int read_text(char str[], int size, int flag)																//sunarthsh gia diabasma alfarhtmhtikwn
	{
		int len;

		if(fgets(str,size,stdin)== NULL)
		{
			printf("Error: fgets() failed\n");
			exit(EXIT_FAILURE);
		}
		len = strlen(str);
		if(len>0)
		{
			if(flag&&(str[len-1]=='\n'))
			{
				str[len-1] = '\0';
				len --;
			}
		}
		else
		{
			printf("Error: No input\n");
			exit(EXIT_FAILURE);
		}
		return len;
	}





	void addbillionaire(char *str)																			//sunarthsh gia thn eisagwgh enos neou disekatommuriouxou
	{
		int i, success=0;
		do
		{
			billionaire *temp;
			temp=(billionaire*)malloc(sizeof(billionaire));													//dunamikh desmeush mnhmnhs enos struckt(billionaire) me onoma temp
			if(temp==NULL)
			{
				printf("Error: Not available memory\n");
				exit(EXIT_FAILURE);
			}
			

			char id[100]={0}, locstr[100]={0}, *diax, strloc[100]={0};
			int barrier=0, digit=0;
			
			diax=strtok(str, ";");
			while(diax!=NULL)																				//spame to arxiko alfarithmitiko se kommatia kai kataxwroume ta dedomena opou prepei
			{																									
				switch(barrier)
				{
					case 0:
						capitalization(diax);
						strcpy(temp->name, diax);
						break;
					case 1:
						strcpy(strloc, diax);
						break;
					case 2:
						strcpy(temp->activity, diax);
						break;
					case 3:
						strcpy(temp->origin, diax);
						break;
					case 4:
						temp->sex = diax[0];
						break;
					case 5:
						sscanf(diax, "%d/%d/%d %d:%d", &temp->birthdate.day, &temp->birthdate.month, &temp->birthdate.year, &temp->birthtime.hour, &temp->birthtime.minutes);
						break;
					case 6:
						temp->fortune = atof(diax);
						break;
				}
				barrier++;
				diax=strtok(NULL, ";");
			}


			char *diax2;
			barrier=0;
			diax2=strtok(strloc, "/");
			while(diax2!=NULL)																
			{																									
				switch(barrier)
				{
					case 0:
						if(strcmp(diax2, "?") == 0)
							strcpy(temp -> location, "Unknown");
						else
							strcpy(temp -> location, diax2);
						break;
					case 1:
						if(strcmp(diax2, "?") == 0)
							strcat(temp -> location, "/Unknown");
						else
						{
							strcat(temp -> location, "/");
							strcat(temp -> location, diax2);
						}
						break;
				}
				barrier++;
				diax2 = strtok(NULL, "/");
			}



			if((temp -> sex=='F' || temp -> sex=='M') && (temp -> birthdate.day>=1 && temp -> birthdate.day<=31) && (temp -> birthdate.month>=1 && temp -> birthdate.month<=12) && (temp -> birthdate.year>=1850 && temp -> birthdate.year<=2024) && (temp -> birthtime.hour>=0 && temp -> birthtime.hour<=24) && (temp -> birthtime.minutes>=0 && temp -> birthtime.minutes<=59) && temp -> fortune>=0)
			{
				printf("Billionaire successfully ADDED!\n");
				insertbillionaire(temp);
				createaccount();
				success=1;
			}
			else 
			{
				printf("Incorrect input please try again!\n");
				free(temp);
				return;
			}
		}while(success!=1);
	}





	void capitalization(char *str)																				//sunarthsh gia thn metatroph twn prwtwn grammatwn(tou onomatos kai tou epithetou) apo mikra se megala
	{
		int i, len= strlen(str);
		
		for(i=0;i<len;i++)
		{
			if(i==0 || (i>0 && str[i-1]==' '))
				str[i]= toupper(str[i]);
			else
				str[i]= tolower(str[i]);
		}
	}






	void insertbillionaire(billionaire *newbill)																//sunarthsh gia eisagwgh tou neou disekatommuriouxou sthn lista					
	{
		if(head==NULL)
		{
			head = newbill;
			head -> next= newbill;
			head -> prev= newbill;
		}
		else
		{
			newbill -> next = head;
			newbill -> prev = head -> prev;
			head -> prev -> next = newbill;
			head -> prev = newbill;
		}
	}





	void deletebill(char xar)																					//sunarthsh gia diagrafh enos disekatommuriouxou apo thn lista	
	{
		if(head==NULL)
		{
			printf("The list is empty, there is no billionaire to be deleted");
			return;
		}

		if(head -> next == head)
		{
			printf("Billionaire successfully DELETED");
			free(head);
			head=NULL;
		}

		if(xar=='N')
		{
			billionaire *temp = head -> prev;
			head -> prev = temp -> prev;
			temp -> prev -> next = head;
			free(temp);
		}
		else
		{
			billionaire *temp = head -> prev;
			head = head -> next;
			temp -> next = head;
			free(head -> prev);
			head -> prev = temp;
		}
	}





	void createaccount()																						//sunarthsh gia thn dhmiourgia trapezikou logariasmou enos dikekatommuriouxou
	{
		int i;
		int pin[11], num=0, arithmos;
		char bank[14]={0};

		for(i=0;i<10;i++)
		{
			pin[i]=rand()%10;
			
			if(i%2==1)
				pin[i]=2*pin[i];
			
			if(pin[i]>9)
				pin[i]=pin[i]%10 + pin[i]/10;
			
			num=num+pin[i];
		}
		
		arithmos = num*9;
		
		pin[10]= arithmos%10;
		
		int j=0;
		for(i=0;i<13;i++)
		{
			if(i<=4)
			{
				bank[i]=pin[j]+'0';
				j++;
			}
			else if(i==5 || i==11)
			{
				bank[i]='-';
			}
			else if(i>=6)
			{
				bank[i]=pin[j]+'0';
				j++;
			}
		}
		
		for(i=0;i<14;i++)
			head -> prev -> acc[i] = bank[i];
	}





	void findbill(char xar, char *str)																				//sunarthsh gia thn euresh kai emfanish disekatommuriouxwn
	{
		if(head==NULL)
		{
			printf("The list is empty, there is no billionaire to be found");
			return;
		}	
		
		int headline=0;
		billionaire *temp = head;
		if(xar=='N')
		{
			do
			{
				if(strstr(temp -> name, str) != NULL)
				{
					if(headline==0)
						printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
					printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
					headline++;
				}
				temp=temp -> next;
			}while(temp!=head);
		}
		else if(xar=='C')
		{
			do
			{
				if(strstr(temp -> location, str) != NULL)
				{
					if(headline==0)
						printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
					printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
					headline++;
				}
				temp=temp -> next;
			}while(temp!=head);
		}
		else
		{
			do
			{
				if(strstr(temp -> activity, str) != NULL)
				{
					if(headline==0)
						printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
					printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
					headline++;
				}
				temp=temp -> next;
			}while(temp!=head);
		}
		return;
	}	





	void savefile(char *str)																						//sunarthsh gia thn apothikeush dedomenwn se arxeio keimenou
	{
		if(head==NULL)
		{
			printf("The list is empty you can not save data that don't exist!\n");
			return;
		}


		FILE *fp;
		fp=fopen(str, "w");
		if(fp==NULL)
		{
			printf("Error: File can not be opened\n");
			exit(EXIT_FAILURE);
		}
		printf("File is saved successfully\n");
		
		billionaire *temp = head;
		do
		{
			fprintf(fp, "%s;%s;%s;%s;%c;%d/%d/%d %d:%d;%2.f;%s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.hour, temp -> fortune, temp -> acc);
			temp=temp -> next;
		}while(temp!=head);
		
		fclose(fp);
	}





	void loadfile(int number, char *str)																			//sunarthsh gia thn fortwsh dedomenwn apo arxeio keimenou
	{
		FILE *fp;
		fp=fopen(str, "r");
		if(fp==NULL)
		{
			printf("Error: File doesn't exist\n");
			exit(EXIT_FAILURE);
		}


		char person[200]={0}, *check;
		int counter=0, i=0, j=0;
		for(i=0;i<number;i++)
		{	
			check=fgets(person, sizeof(person), fp);

			if(check==NULL)
				break;
			
			addbillionaire(person);
		}


		printf("File is loaded successfully\n");
		fclose(fp);
	}




	void printbill(char xar, char *str)																			//sunarthsh gia thn ektupwsh disekatommuriouxwn analoga me megaliterh/mikroterh/idia hmeromhnia gennhshs/wra gennhshs/periousia
	{
		billionaire *temp, person;
		int len= strlen(str), i;
		char type;
		
		for(i=0;i<len;i++)
		{
			if(str[i]=='/')
			{
				type='d';
				break;
			}
			else if(str[i]==':')
			{
				type='t';
				break;
			}
			else
				type='m';
		}
		
		int headline=0;
		if(type=='d')
		{
			sscanf(str, "%d/%d/%d", &person.birthdate.day, &person.birthdate.month, &person.birthdate.year);
			
			temp=head;
			do
			{
				if(xar=='+')
				{
					if(person.birthdate.year<temp->birthdate.year)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
					else if(person.birthdate.year==temp->birthdate.year && person.birthdate.month<temp->birthdate.month)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
					else if(person.birthdate.year==temp->birthdate.year && person.birthdate.month==temp->birthdate.month && person.birthdate.day<temp->birthdate.day)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
				}
				else if(xar=='-')
				{
					if(person.birthdate.year>temp->birthdate.year)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
					else if(person.birthdate.year==temp->birthdate.year && person.birthdate.month>temp->birthdate.month)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
					else if(person.birthdate.year==temp->birthdate.year && person.birthdate.month==temp->birthdate.month && person.birthdate.day>temp->birthdate.day)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}					
				}
				else if(xar=='=')
				{
					if(person.birthdate.day==temp->birthdate.day && person.birthdate.month==temp->birthdate.month&& person.birthdate.year==temp->birthdate.year)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
				}
				temp=temp->next;
			}while(temp!=head);
		}
		else if(type=='t')
		{
			sscanf(str, "%d:%d", &person.birthtime.hour, &person.birthtime.minutes);
			
			temp=head;
			do
			{
				if(xar=='+')
				{
					if(person.birthtime.hour<temp->birthtime.hour)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
					else if(person.birthtime.hour==temp->birthtime.hour && person.birthtime.minutes<temp->birthtime.minutes)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
				}
				else if(xar=='-')
				{
					if(person.birthtime.hour>temp->birthtime.hour)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
					else if(person.birthtime.hour==temp->birthtime.hour && person.birthtime.minutes>temp->birthtime.minutes)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}					
				}
				else if(xar=='=')
				{
					if(person.birthtime.hour==temp->birthtime.hour && person.birthtime.minutes==temp->birthtime.minutes)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
				}
				temp=temp->next;
			}while(temp!=head);
		}
		else if(type=='m')
		{
			sscanf(str, "%f", &person.fortune);
			
			temp=head;
			do
			{
				if(xar=='+')
				{
					if(person.fortune<temp->fortune)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
				}
				else if(xar=='-')
				{
					if(person.fortune>temp->fortune)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
				}
				else if(xar=='=')
				{
					if(person.fortune==temp->fortune)
					{
						if(headline==0)
							printf("%-30s %-30s %-30s %-15s %-10s %-30s %-10s %-20s", "Name:", "Activity location:", "Activity:", "Motherland:", "Sex:", "Birthdate and Birthtime:", "Fortune:", "Bank account:\n");
						printf("\b\b\b\b\b\b%-30s %-30s %-30s %-15s %-10c %-2d/%-2d/%-4d %-2d:%-16d %-10.2f %-20s\n", temp -> name, temp -> location, temp -> activity, temp -> origin, temp -> sex,  temp -> birthdate.day,temp -> birthdate.month, temp -> birthdate.year, temp -> birthtime.hour, temp -> birthtime.minutes, temp -> fortune, temp -> acc);
						headline++;
					}
				}
				temp=temp->next;
			}while(temp!=head);
		}
	}
