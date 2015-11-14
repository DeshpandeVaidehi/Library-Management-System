
/*****************************************************************************
 * "Library Management" 
 *
 * This code performs various operations mainly used in college library.
 *
 * Copyright (C) 2015 Vaidehi V. Dehpande
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#define RETURNTIME 15
#include<stdio.h>                  
#include <stdlib.h>
#include<string.h>
#include<time.h>  

struct lastdate {
    int mm, dd, yy;
};
struct books {
    int id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct lastdate issued;
    struct lastdate duedate;
};
struct books a;

struct student {
	int mis;
	int contact;
	char name[50], email[50], branch[20];
};
struct student stud;

int start();
int  getdata();
void mainmenu();
void login();
void addbooks();
void addstudent();
void deletebooks();
void searchbooks();
void issuebooks();
int  checkid(int);
int  checkmis(int);
void issuerecord();
void editbooks();
void viewbooks();
void viewstudent();
char branch[][15] = {"Computer", "IT", "Electrical", "Civil", "Mechnnical", "Architecture"};
FILE *fp, *ft, *st;
int s;
int flag;

int main() {
	start();
	return 0;
}

int start() {
	system("clear");
	int log;
	printf("************************Libary Management************************\n");
	printf("1. Student Section\n");
	printf("2. Administrator\n");
	scanf("%d", &log);
	switch(log) {
		case 1: 
			login();
			break;
		case 2:
			mainmenu();
			break;
	}
	return 0;
}

void login() {		
	system("clear");
	int t, y, ch;
	printf(" \n");
	printf("1. Add Member\n");
	printf("2. View Member\n");
	printf("3. Back to Administrator\n");
	printf("4. Close application\n\n");
	scanf("%d", &ch);	
	switch(ch) {
		case 1: 
			addstudent();
			break;
		case 2:
			viewstudent();
			break;
		case 3:
			start();
			break;

		case 4: {
			system("clear");
			exit(0);
	   	}
		default: 
			printf("\aYou entered wrong chioce");
			start();
	}
}
void addstudent() {		/* This function adds student member and details of student */
	int t, y;
	st = fopen("Student.txt","ab+");
	printf("	Add student member :\n");
	printf("MIS :\t");
	scanf("%d", &t);
	if(checkmis(t) == 0) {
		printf("This MIS is already registered\t");
		login();
		
	}
	stud.mis = t;
	printf("\nName of student :\t");
	scanf("%s", stud.name);
	printf("\nContact No :\t");
	scanf("%d", &stud.contact);
	printf("\nEmail ID :\t");
	scanf("%s", stud.email);
	printf("\nBranch :\t");
	scanf("%s", stud.branch);
	fseek(st, 0, SEEK_END);
	fwrite(&stud, sizeof(stud), 1, st);
	fclose(st);
	printf("The record is sucessfully saved\n");
	printf("Save any more?(Y / N) press 1 for YES and 2 for NO:");
	scanf("%d", &y);
	if(y == 2) {
		start();
	}
	else {
		system("clear");
		login();
	}
	
}
void viewstudent() {		/* This fuction shows the registered student members */
	int j, y;
	system("clear");
	printf("********************************* Student Data *****************************\n");
	st = fopen("Student.txt", "rb+");
	//rewind(fp);
	while(fread(&stud, sizeof(stud), 1, st) == 1) {
		printf("\nMIS :%d		", stud.mis);
		printf("\nName :%s	", stud.name);
		printf("\nEmail Id :%s	", stud.email);
		printf("\nContact No. :%d		", stud.contact);
		printf("\nBranch :%s	", stud.branch);
		printf("\n\n");
		
	}
	printf("Press 1 to go main menu :");
	scanf("%d", &y);
	if(y == 1) 
		start();	
}
void mainmenu() {		/* Call every function handle from Administrator */
      	int i,r;
	system("clear");
	printf(" \n");
	printf("************************ Libary Management ************************\n");
	printf("     Main Menu\n\n");
	printf("1. Add Books\n");
	printf("2. Delete books\n");
	printf("3. View Book list\n");
	printf("4. Edit Book's Record\n");
	printf("5. Search Books\n");
	printf("6. Issue Books\n");
	printf("7. Back to Student Section\n");
	printf("8. Close Application\n");
	printf("Enter your choice:\n");
	scanf("%d", &r);
	switch(r) {
		case 1:
			addbooks();
			break;
		case 2:
			deletebooks();
			break;
		
	    	case 3:
			viewbooks();
			break;
	   	case 4:
			editbooks();
			break; 
		case 5:
			searchbooks();
			break;  
		case 6:
			issuebooks();
			break;
		case 7:
			start();
			break;  

	    	case 8: {
			system("clear");
			exit(0);
	   	}
		default: 
			printf("\aYou entered wrong chioce\n");
			mainmenu();
	   
    }
}
void addbooks() {		/* Add new book to library. Details of books and on which shelf it is*/	
	int y;
	system("clear");
	int i;
	printf("SELECT CATEGOIES\n");
	printf("1.Computer\n");
	printf("2.IT\n");
	printf("3.Electrical\n");
	printf("4.Civil\n");
	printf("5.Mechanical\n");
	printf("6.Architecture\n");
	printf("7.Back to main menu\n");
	printf("Enter your choice:");
	scanf("%d",&s);
	if(s == 8) {
		mainmenu() ;
	}
	
	system("clear");
	fp = fopen("Library.dat", "ab+");
	if(getdata() == 1) {
		a.cat = branch[s-1];
		fseek(fp, 0, SEEK_END);
		fwrite(&a, sizeof(a), 1, fp);
		fclose(fp);
		printf("The record is sucessfully saved\n");
		printf("Save any more?(Y / N) press 1 for YES and 2 for NO:");
		scanf("%d", &y);
		if(y == 2) {
	    		mainmenu();
		}
		else {
	    		system("clear");
	    		addbooks();
		}
	}
}
int getdata() {		/* accept data to add book */
	int t;
	printf("Enter the Information Below\n");
	printf("Category:");
	printf("%s",branch[s-1]);
	printf("\nBook ID:\t");
	scanf("%d",&t);
	if(checkid(t) == 0) {
		printf("The book id checkid exists\t");
		mainmenu();
	}
	a.id = t;
	printf("\nBook Name:");
	scanf("%s", a.name);
	printf("\nAuthor:");
	scanf("%s", a.Author);
	printf("\nQuantity:");
	scanf("%d", &a.quantity);
	printf("\nPrice:");
	scanf("%f", &a.Price);
	printf("\nRack No:");
	scanf("%d", &a.rackno);
	return 1;
}
int checkid(int t) {		/* check whether book id is already present or not */
	rewind(fp);
	while(fread(&a, sizeof(a), 1, fp) == 1)
	if(a.id == t) {
		return 0;
	}
      return 1; 
}
int checkmis(int t) {		/* check whether student is already registered or not */
	rewind(st);
	while(fread(&stud, sizeof(stud), 1, st) == 1)
	if(stud.mis == t) {
		return 0;
	}
      return 1; 
}

void deletebooks() {		/* Delete books from library on basis of book id */
	system("clear");
	int d, y;
        while(1) {
		system("clear");
		printf("Enter the Book ID to delete:");
		scanf("%d", &d);
		fp = fopen("Library.dat", "rb+");
		rewind(fp);
		while(fread(&a, sizeof(a), 1, fp) == 1) {
			if(a.id == d) {
				printf("The book record is available\n");
				printf("Book name is    %s\n", a.name);
				printf("Rack No. is    %d\n", a.rackno);
				flag = 10;
	  	  	}
		}
		if(flag != 10) {
			printf("No record is found modify the search");
			mainmenu();
		}
		if(flag == 10) {
			printf("Do you want to delete it?(Y/N) press 1 for YES and 2 for NO:");
			scanf("%d", &y);
			if(y == 1) {
				ft = fopen("test.dat", "w+");		/* create new file test.dat copy all data remove Library.dat an then 											rename test.dat to Librarydat */ 
				rewind(fp);
				while(fread(&a, sizeof(a), 1, fp) == 1) {
					if(a.id != d) {
						fseek(ft, 0, SEEK_CUR);
						fwrite(&a, sizeof(a), 1, ft); 
		    			}                              
				}
				fclose(ft);
				fclose(fp);
				remove("Library.dat");
				rename("test.dat", "Library.dat"); 
				if(flag == 10) {
					printf("The record is sucessfully deleted\n");
					printf("Delete another record?(Y/N) press 1 for YES and 2 for NO\n");	
					scanf("%d", &y);
					if(y == 2) 
		        			mainmenu();	
					else 
						deletebooks();
				}
			}
			else 
				mainmenu();
		}
	}
}

void viewbooks(void) {		/* View all the books present in library */
	int i = 0, j, y;
	system("clear");
	printf("*********************************Book List*****************************\n");
	j = 4;
	fp = fopen("Library.dat", "rb+");
	while(fread(&a, sizeof(a), 1, fp) == 1) {
		printf("BRANCH :	%s\n", a.cat);
		printf("BOOK ID :		%d\n", a.id);
		printf("BOOK NAME :	%s\n", a.name);
		printf("AUTHOR :	%s\n", a.Author);
		printf("QUANTY :	%d\n", a.quantity);
		printf("PRICE :		%.2f\n", a.Price);
		printf("RACK NO :	%d\n", a.rackno);
		printf("\n\n");
		j++;
		i = i + a.quantity;
	}
	printf("Total Books = %d\n",i);

	printf("Press 1 to go main menu :");
	scanf("%d", &y);
	if(y == 1) 
		mainmenu();
	
}

void editbooks() {		/* Edit details of books like shelf, no. of copies, etc.*/
	system("clear");
	int c = 0, y, d, e;
	printf("	Edit Books\n");
	while(1) {
		system("clear");
		printf("Enter Book Id to be edited:");
		scanf("%d", &d);
		fp = fopen("Library.dat", "rb+");
		while(fread(&a, sizeof(a), 1, fp) == 1) {
			if(checkid(d) == 0) {
				printf("The book is availble\n");
				printf("The Book ID:");
				scanf("%d", &a.id);
				printf("Enter new name:");	
				scanf("%s", a.name);
				printf("Enter new Author:");
				scanf("%s" ,a.Author);
				printf("Enter new quantity:");
				scanf("%d", &a.quantity);
				printf("Enter new price:");
				scanf("%f", &a.Price);
				printf("Enter new rackno:");
				scanf("%d", &a.rackno);
				printf("The record is modified\n");
				fseek(fp, ftell(fp) - sizeof(a), 0);
				fwrite(&a, sizeof(a), 1, fp);
				fclose(fp);
				c = 1;
			}
			if(c == 0) {
				printf("No record found\n");
			}
		}
		printf("Modify another Record?(Y/N) pres 1 for YES and 2 for NO");
		scanf("%d", &y);
		if(y == 2) {
	    		mainmenu();
		}
		else {
	    		system("clear");
	    		editbooks();
		}
	}
}
void searchbooks() {		/* Search book on the basis of book name and book id */
system("clear");
	int d, ch, y;
	printf("Search Books\n");
	printf("1. Search By ID\n");
	printf("2. Search By Name\n");
	printf("Enter Your Choice\n");
	scanf("%d", &ch);
	fp = fopen("Library.dat", "rb+"); 
	rewind(fp);
	switch(ch) {
		case 1:	{
	    		system("clear");
			printf("	Search Books By Id\n");
			printf("Enter the book id:");
			scanf("%d", &d);
			while(fread(&a, sizeof(a), 1, fp) == 1) {
				if(a.id == d) {
					printf("The Book is available\n");
		    			printf("ID:%d\n", a.id);
		   			printf("Name:%s\n", a.name);
		    			printf("Author:%s\n", a.Author);
		  			printf("Qantity:%d\n", a.quantity);
		    			printf("Price:Rs.%.2f\n", a.Price);
					printf("Rack No:%d\n", a.rackno);
		   			flag = 10;
				}
	
	   		}
	    		if(flag != 10) {
	    			printf("No Record Found\n");
			}
	    		printf("Try another search?(Y/N) press 1 for YES and 2 for NO");
			scanf("%d", &y);
	    		if(y == 1)
	    			searchbooks();
	    		else
	   			 mainmenu();
	    		break;
		}
		case 2: {
			char s[15];
			system("clear");
			printf("	Search Books By Name\n");
	    		printf("Enter Book Name:");
	    		scanf("%s", s);
			int d = 0;
			while(fread(&a, sizeof(a), 1, fp) == 1) {
				if(strcmp(a.name, (s)) == 0) {
					printf("The Book is available\n");
		    			printf("ID:%d\n", a.id);
		   			printf("Name:%s\n", a.name);
		    			printf("Author:%s\n", a.Author);
		    			printf("Qantity:%d\n", a.quantity);
		    			printf("Price:Rs.%.2f\n", a.Price);
		    			printf("Rack No:%d\n", a.rackno);
		    			d++;
				}
			}
	    		if(d == 0) 
	  			printf("No Record Found\n");

	     		printf("Try another search?(Y/N) press 1 for YES and 2 for NO");
			scanf("%d", &y);
	   		if(y == 1)
	    			searchbooks();
	    		else
	    			mainmenu();
	   		break;
		}
		default :
			searchbooks();
		}
		fclose(fp);
}
void issuebooks() {		/* Issue perticular book to student also check for returntime which is 15 days */		
	time_t td = time(0);   // get time now
	struct tm * now = localtime( & td );
	//int dd1, mm1, yy1;
	a.issued.dd = now->tm_mday;
	a.issued.mm = now->tm_mon;
	a.issued.yy = now->tm_year;
	printf("\n\n******** %d  %d  %d\n\n",a.issued.dd, a.issued.mm, a.issued.yy);
	int t, ch, y;
	system("clear");
	printf("BOOK ISSUE SECTION\n");
	printf("1. Issue a Book\n");
    	printf("2. View Issued Book\n");
    	printf("3. Search Issued Book\n");
   	printf("4. Remove Issued Book\n");
	printf("5. Retutn to mainmemu\n");
    	printf("Enter a Choice:\n");
	scanf("%d", &ch);
	FILE *fs;
	switch(ch) {
		x1:	case 1: {		/* issue book*/
				system("clear");
				int c = 0,y;
				while(1) {
					system("clear");
					printf("	Book Issue Section\n");
					printf("Enter the Book Id:\n");
					scanf("%d", &t);
					fp = fopen("Library.dat","rb+");
					fs = fopen("Issue.txt","ab+");
					if(checkid(t) == 0) {
			     			printf("The book record is available\n");
			     			printf("There are %d unissued books in library\n", a.quantity);
			     			printf("The name of book is %s\n", a.name);
			    			printf("Enter student name:\n");
			    			scanf("%s", a.stname);
						a.issued.dd = now->tm_mday;
						a.issued.mm = now->tm_mon;
						a.issued.yy = now->tm_year;
			    	 		printf("Issued date = %d - %d - %d\n", a.issued.dd, a.issued.mm, a.issued.yy);
			    			printf("The BOOK of ID %d is issued ", a.id);
			    	 		a.duedate.dd = a.issued.dd+RETURNTIME; 
			    	 		a.duedate.mm = a.issued.mm;
			    	 		a.duedate.yy = a.issued.yy;
			    	 		if(a.duedate.dd > 30) {
					 		a.duedate.mm += a.duedate.dd / 30;
					 		a.duedate.dd -= 30;
			    			 }
			    	 		if(a.duedate.mm > 12) {
							a.duedate.yy += a.duedate.mm / 12;
							a.duedate.mm -= 12;
			    	 		}
			    	 		printf("To be return:%d-%d-%d", a.duedate.dd, a.duedate.mm, a.duedate.yy);
			    			fseek(fs, sizeof(a), SEEK_END);
			    	 		fwrite(&a, sizeof(a), 1, fs);
			    	 		fclose(fs);
			    		 	c = 1;
					}
					if(c == 0) {
						printf("No record found\n");
					}
					fclose(fp);
					printf("\nIssue any more(Y/N) press 1 for YES and 2 for NO:");
					scanf("%d", &y);
					if(y == 1)
						goto x1;
					else 
						issuebooks();	
				
				}
				break;
			}
			case 2:  {		/* view issued books */
				system("clear");
				int j = 4;
				printf("\tIssued book list\n");
			        fs = fopen("Issue.txt","rb");
				while(fread(&a,sizeof(a),1,fs)==1) {
					printf("\n\nSTUDENT NAME:	%s", a.stname);
					printf("\nCATEGORY :	%s", a.cat);
					printf("\nID :	%d", a.id);
					printf("\nBOOK NAME: 	%s", a.name);
					printf("\nISSUED DATE :	%d-%d-%d", a.issued.dd, a.issued.mm, a.issued.yy );
					printf("\nRETURN DATE :	%d-%d-%d\n", a.duedate.dd, a.duedate.mm, a.duedate.yy);
					j++;
				}
				fclose(fs);
				printf("Press 1 to go issue books again:");
				scanf("%d", &y);
				if(y == 1) 
					issuebooks();
			}
			break;
		x2:	case 3: {		/* Search for issued  book */
				system("clear");
				int p, c = 0;
				printf("Enter Book ID:");
				scanf("%d", &p);
				while(1) {
					
					fs = fopen("Issue.txt", "rb");
					while(fread(&a, sizeof(a), 1, fs) == 1) {
						if(a.id == p) 
							issuerecord();
						c = 1;
					}

				fclose(fs);
				if(c == 0)
				printf("No Record Found");
				printf("Try Another Search?(Y/N) press 1 for YES and 2 for NO:");
				scanf("%d", &y);
				if(y == 1)
					goto x2;
				else 
					issuebooks();
				}
			}
			break;
		x3:	case 4: {		/* Remove issued book */
				int y;
				system("clear");
				int b;
				FILE *fg;  
				while(1) {
					printf("Enter book id to remove:");
					scanf("%d", &b);
					fs = fopen("Issue.txt", "rb+");
					while(fread(&a, sizeof(a), 1, fs) == 1) {
						if(a.id == b) {
							issuerecord();
							flag = 10;
						}
						if(flag == 10) {
							printf("Do You Want to Remove it?(Y/N) press 1 for YES and 2 for NO");
							scanf("%d", &y);
							if(y == 1) { 
								fg = fopen("record.txt", "wb+");
								rewind(fs);
								while(fread(&a, sizeof(a), 1, fs) == 1) {
									if(a.id!=b) {
										fseek(fs, 0, SEEK_CUR);
										fwrite(&a, sizeof(a), 1, fg);
									}
								}
								fclose(fs);
								fclose(fg);
								remove("Issue.txt");
								rename("record.dat", "Issue.txt");
								printf("The issued book is removed from list\n");
								printf("Delete any more?(Y/N) press 1 fo1r YES and 2 for NO");
								scanf("%d", &y);
								if(y == 1)
									goto x3;
								else 
									issuebooks();
			
							}
						}
						if(flag!= 10) {
							printf("No Record Found\n");
							printf("Press 1 to go issue books again:");
							scanf("%d", &y);
							if(y == 1) 
								issuebooks();
						}
					}
				
				}
			}
			case 5: 
				mainmenu();
				break;
			default:
				printf("Wrong Entry!!\n");
   				return 0;
				issuebooks();
				break;
	}
}
void issuerecord() {		/* Record of issued books. this fucton get called from remove case of issuebooks*/
	system("clear");
	printf("The Book has taken by %s\n", a.stname);
	printf("Issued Date: %d-%d-%d\n", a.issued.dd,a.issued.mm,a.issued.yy);
	printf("Returning Date: %d-%d-%d\n", a.duedate.dd,a.duedate.mm,a.duedate.yy);
}

