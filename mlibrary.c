#include<stdio.h>                  
#include <stdlib.h>
#include<string.h>     
char branch[][15]={"Computer","IT","Electrical","Civil","Mechnnical","Architecture"};
int  getdata();
void mainmenu();
void addbooks();
void deletebooks();
void searchbooks();
void issuebooks();
int  already(int);
void issuerecord();
void editbooks();
void viewbooks();
FILE *fp,*ft;
int s;
int flag;
struct lastdate
{
    int mm,dd,yy;
};
struct books
{
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
int main() {
	mainmenu();
	return 0;
}
void mainmenu() {
      	int i,r;
	system("clear");
	printf("************************Libary Management************************\n");
	printf("     Main Menu\n");
	printf("1. Add Books\n");
	printf("2. Delete books\n");
	printf("3. View Book list\n");
	printf("4. Edit Book's Record\n");
	printf("5. Search Books\n");
	printf("6. Close Application\n");
	printf("Enter your choice:\n");
	scanf("%d",&r);
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
	    	case 6: {
			system("clear");
			exit(0);
	   	}
	    default: 
			printf("\aYou entered wrong chioce");
			mainmenu();
	   
    }
}
void addbooks() {	
	int y;
	system("clear");
	int i;
	printf("            SELECT BRANCH\n");
	printf("1.Computer\n");
	printf("2.IT\n");
	printf("3.Electrical\n");
	printf("4.Civil\n");
	printf("5.Mechanical\n");
	printf("6.Architecture\n");
	printf("7.Back to main menu\n");
	printf("Enter your choice:");
	scanf("%d",&s);
	if(s==8) {
		mainmenu() ;
	}
	
	system("clear");
	fp=fopen("library.dat","a");
	if(getdata()==1)
	{
		a.cat=branch[s-1];
		fseek(fp,0,SEEK_END);
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);
		printf("The record is sucessfully saved\n");
		printf("Save any more?(Y / N) press 1 for YES and 2 for NO:");
		scanf("%d",&y);
		if(y==2) {
	    		mainmenu();
		}
		else {
	    		system("clear");
	    		addbooks();
		}
	}
}
int getdata()
{
	int t;
	printf("Enter the Information Below\n");
	printf("BRANCH: ");
	printf("%s\n",branch[s-1]);
	printf("Book ID:\t");
	scanf("%d",&t);
	if(already(t) == 0)
	{
		printf("\aThe book id already exists\n\n");
		mainmenu();
	}
	a.id=t;
	printf("Book Name:");
	scanf("%s",a.name);
	printf("Author:");
	scanf("%s",a.Author);
	printf("Quantity:");
	scanf("%d",&a.quantity);
	printf("Price:");
	scanf("%f",&a.Price);
	printf("Rack No:");
	scanf("%d",&a.rackno);
	return 1;
}
int already(int t)  
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t) {
		return 0;
	}
      return 1; 
}
void deletebooks() {
	system("clear");
	int d, y;
        while(1) {
		system("clear");
		printf("Enter the Book ID to delete:");
		scanf("%d",&d);
		fp=fopen("library.dat","rb+");
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1) {
			if(a.id==d) {
				printf("The book record is available\n");
				printf("Book name is    %s\n",a.name);
				printf("Rack No. is    %d\n",a.rackno);
				flag=10;
	  	  	}
		}
		if(flag!=10) {
			printf("No record is found modify the search");
			mainmenu();
		}
		if(flag==10) {
			printf("Do you want to delete it?(Y/N) press 1 for YES and 2 for NO:");
			scanf("%d",&y);
			if(y==1) {
				ft=fopen("test.dat","w+"); 
				rewind(fp);
				while(fread(&a,sizeof(a),1,fp)==1) {
					if(a.id!=d) {
						fseek(ft,0,SEEK_CUR);
						fwrite(&a,sizeof(a),1,ft); 
		    			}                              
				}
				fclose(ft);
				fclose(fp);
				remove("library.dat");
				rename("test.dat","library.dat"); 
				//fp=fopen("library.dat","rb+");   
				if(flag==10) {
					printf("The record is sucessfully deleted\n");
					printf("Delete another record?(Y/N) press 1 for YES and 2 for NO\n");	
					scanf("%d",&y);
					if(y==2) 
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

void viewbooks(void) {
	int i=0, j, y;
	system("clear");
	printf("*********************************Book List*****************************\n");
	printf("BRANCH     ID     BOOK NAME     AUTHOR     QTY     PRICE     RackNo \n");
	j=4;
	fp=fopen("library.dat","rb+");
	while(fread(&a,sizeof(a),1,fp)==1) {
		printf("%s     ",a.cat);
		printf("%d     ",a.id);
		printf("%s     ",a.name);
		printf("%s     ",a.Author);
		printf("%d     ",a.quantity);
		printf("%.2f     ",a.Price);
		printf("%d     ",a.rackno);
		printf("\n\n");
		j++;
		i=i+a.quantity;
	}
	printf("Total Books =%d\n",i);
	printf("Press 1 to go main menu :");
	scanf("%d", &y);
	if(y==1) 
		mainmenu();
	
}

void editbooks() {
	system("clear");
	int c = 0, y, d, e;
	printf("	Edit Books\n");
	while(1) {
		system("clear");
		printf("Enter Book Id to be edited:");
		scanf("%d",&d);
		fp=fopen("library.dat","rb+");
		while(fread(&a,sizeof(a),1,fp)==1) {
			if(already(d)==0) {
				printf("The book is availble\n");
				printf("The Book ID:");scanf("%d",&a.id);
				printf("Enter new name:");scanf("%s",a.name);
				printf("Enter new Author:");scanf("%s",a.Author);
				printf("Enter new quantity:");scanf("%d",&a.quantity);
				printf("Enter new price:");scanf("%f",&a.Price);
				printf("Enter new rackno:");scanf("%d",&a.rackno);
				printf("The record is modified\n");
				fseek(fp,ftell(fp)-sizeof(a),0);
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				printf("No record found\n");
			}
		}
		printf("Modify another Record?(Y/N) pres 1 for YES and 2 for NO");
		scanf("%d",&y);
		if(y==2) {
	    		mainmenu();
		}
		else {
	    		system("clear");
	    		editbooks();
		}
	}
}
void searchbooks() {
system("clear");
	int d, ch, y;
	printf("Search Books\n");
	printf("1. Search By ID\n");
	printf("2. Search By Name\n");
	printf("Enter Your Choice\n");
	scanf("%d",&ch);
	fp=fopen("library.dat","rb+"); 
	rewind(fp);
	switch(ch) {
		case 1:	{
	    		system("clear");
			printf("	Search Books By Id\n");
			printf("Enter the book id:");
			scanf("%d",&d);
			while(fread(&a,sizeof(a),1,fp)==1) {
				if(a.id==d) {
					printf("The Book is available\n");
		    			printf("ID:%d\n",a.id);
		   			printf("Name:%s\n",a.name);
		    			printf("Author:%s\n",a.Author);
		  			printf("Qantity:%d\n",a.quantity);
		    			printf("Price:Rs.%.2f\n",a.Price);
					printf("Rack No:%d\n",a.rackno);
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
	    		scanf("%s",s);
			int d = 0;
			while(fread(&a,sizeof(a),1,fp)==1) {
				if(strcmp(a.name,(s))==0) {
					printf("The Book is available\n");
		    			printf("ID:%d\n",a.id);
		   			printf("Name:%s\n",a.name);
		    			printf("Author:%s\n",a.Author);
		    			printf("Qantity:%d\n",a.quantity);
		    			printf("Price:Rs.%.2f\n",a.Price);
		    			printf("Rack No:%d\n",a.rackno);
		    			d++;
				}
			}
	    		if(d == 0) 
	  			printf("No Record Found\n");

	     		printf("Try another search?(Y/N) press 1 for YES and 2 for NO");
			scanf("%d",&y);
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
void issuebooks() {
}

