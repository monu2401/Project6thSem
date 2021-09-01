#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#define recsize 50
#define max 10
#define ADMINUSER "kavya"
#define ADMINPASSWORD "123"
#define fn "library.txt"
fstream file;
char buffer[100];
class Library
{
	 public:
		  char key[5],name[30],price[5],phno[15],book[12],issue_date[20],return_date[20];
		  void initial();
		  void read();
		  void store(int);
		  int remove(int,char *);
		  int hash(char *);
		  void displayall();
		  void retrieve(int addr,char k[]);
 };
void Library::initial()
{
	int i,j;
	file.open(fn,ios::in);
	if(!file)
	{
		file.open(fn,ios::out);
		if(!file)
		{
			cout<<"Unable to open the file";
			getch();
			exit(1);
		}
		for(i=0;i<max;i++)
		{
			file.seekp(i*recsize*5+i*2,ios::beg);
			for(j=0;j<(recsize)*5;j++)
				file<<"#";
			file<<endl;
		}
		cout<<"Empty file created"<<endl;
	}
	file.close();
	return;
 }
void Library::read()
{
	cout<<"Enter the record key:";	gets(key);
	cout<<"Enter the name:";        gets(name);
	cout<<"Enter the fine:";      	gets(price);
	cout<<"Enter the phone no:";  gets(phno);
	cout<<"Enter the book name:";  gets(book);
	cout<<"Enter the issue date:";      gets(issue_date);
	cout<<"Enter the return date:"; gets(return_date);
	strcpy(buffer,key);             strcat(buffer,"|");
	strcat(buffer,name);            strcat(buffer,"|");
	strcat(buffer,price);           strcat(buffer,"|");
	strcat(buffer,phno);      strcat(buffer,"|");
	strcat(buffer,book);           strcat(buffer,"|");
	strcat(buffer,issue_date);   strcat(buffer,"|");
	strcat(buffer,return_date);            strcat(buffer,"|");
	return;
 }
int Library::hash(char* key)
{
	int i=0,sum=0;
	while(key[i]!='\0')
	{
		sum=sum+(key[i]-48);
		i++;
	}
	return sum % max;
}
void Library::store(int addr)
{
	char dummy[10];
	int flag=0,i,j;
	file.open(fn,ios::in|ios::out);
	file.seekp(addr*recsize*5+addr*2);
	file.getline(dummy,5,'\n');
	if(strcmp(dummy,"####")==0)
	{
		 file.seekp(addr*recsize*5+i*2);
		 file<<buffer;
		 flag=1;
	}
	else
	{
		for(i=0;i<5;i++)
		{
			file.seekg(addr*recsize*5+i*recsize+addr*2);
			file.getline(dummy,5,'\n');
			//cout<<"dummy "<<dummy<<addr*recsize*5+i*recsize+addr*2<<"\t";
			if(strcmp(dummy,"####")==0)
			{
				cout<<"\n Collision has occured\n";
				cout<<"Home address is "<<addr*recsize*5+addr*2<<" Actual address is "<<addr*recsize*5+i*recsize+i*2<<"\n";
				file.seekp(addr*recsize*5+i*recsize+2*addr);
				file<<buffer;
				flag=1;
				//cout<<"break now\n";
				return;
			}
		}
		for(i=addr+1;i!=addr;i++)
		{
			if(i%max==0)
				i=0;
			for(j=0;j<5;j++)
			{
				file.seekg(i*recsize*5+j*recsize+2*i);
				file.getline(dummy,5,'\n');
				if(strcmp(dummy,"####")==0)
				{
					cout<<"\n Collision has occured\n";
					cout<<"Home address is "<<addr*recsize*5+i*2<<" Actual address is "<<i*recsize*5+j*recsize+i*2<<"\n";
					file.seekp(i*recsize*5+j*recsize+2*i);
					file<<buffer;
					flag=1;
					return;
					// cout<<"Break now\n";
				}
			}
		}
	}
	if(i==addr && (!flag))
		cout<<"Hash file is full,record cannot be inserted\n";
	file.close();
	return;
}
void Library::retrieve(int addr,char k[])
{
	int found=0,i;
	char dummy[10];
	i=addr;
	file.open(fn,ios::in|ios::out|ios::binary);
	do
	{
		file.seekg(i*recsize*5+i*2);
		file.getline(dummy,5,'\n');
		if(strcmp(dummy,"####")==0)
			break;
		file.seekg(i*recsize*5+i*2);
		file.getline(key,5,'|');
	   //	cout<<key<<endl;
		if(strcmp(key,k)==0)
		{
			found=1;
			cout<<"Record found"<<endl;
			file.getline(name,30,'|');
			file.getline(price,5,'|');
			file.getline(phno,20,'|');
			file.getline(book,10,'|');
			file.getline(issue_date,20,'|');
			file.getline(return_date,17,'|');
			cout<<setiosflags(ios::left);
			cout<<"Key="<<key<<"\n"<<"Name="<<name<<"\n"<<"Fine="<<price<<"\n"<<"Phone no="<<phno<<"\n"<<"book="<<book<<"\n"<<"issue date="<<issue_date<<"\n"<<"return date="<<return_date<<endl;
			return;
		}
		else
		{
			for(int j=0;j<5;j++){
				file.seekg(i*recsize*5+j*recsize+i*2);
				file.getline(dummy,5,'\n');
				//cout<<dummy<<" dummy "<<(i*recsize*5+j*recsize+i*2)<<"\t";
				if(strcmp(dummy,"####")==0)
					break;
				file.seekg(i*recsize*5+j*recsize+i*2);
				file.getline(key,5,'|');

			  //	cout<<key<<endl;
				if(strcmp(key,k)==0)
				{
					found=1;
					cout<<"Record found"<<endl;
					file.getline(name,30,'|');
					file.getline(price,5,'|');
					file.getline(phno,20,'|');
					file.getline(book,10,'|');
					file.getline(issue_date,20,'|');
					file.getline(return_date,17,'|');
					cout<<setiosflags(ios::left);
					cout<<"Key="<<key<<"\n"<<"Name="<<name<<"\n"<<"Fine="<<price<<"\n"<<"Phone no="<<phno<<"\n"<<"book="<<book<<"\n"<<"Issue date="<<issue_date<<"\n"<<"Return date="<<return_date<<endl;
					return;
				}
			}
			i++;
			if(i%max==0)
					i=0;
		}
	} while(i!=addr);
	if(found==0)
		cout<<"\nRecord does not exist in hash file\n";
	return;
}
int Library::remove(int addr,char k[])
{
	int found=0,i;
	char dummy[10];
	i=addr;
	file.open(fn,ios::in|ios::out);
	do
	{
		file.seekg(i*recsize*5+i*2);
		file.getline(dummy,5,'\n');
		//cout<<dummy<<endl;
		if(strcmp(dummy,"####")==0)
			break;
		file.seekg(i*recsize*5+i*2);
		file.getline(key,5,'|');
		//cout<<key<<"   "<<k<<endl;
		if(strcmp(key,k)==0)
		{
			found=1;
			cout<<"Record found"<<endl;
			file.getline(name,30,'|');
			file.getline(price,5,'|');
			file.getline(phno,20,'|');
			file.getline(book,10,'|');
			file.getline(issue_date,20,'|');
			file.getline(return_date,17,'|');
			cout<<setiosflags(ios::left);
			cout<<"Key="<<key<<"\n"<<"Name="<<name<<"\n"<<"Fine="<<price<<"\n"<<"Phone number="<<phno<<"\n"<<"book="<<book<<"\n"<<"Issue date="<<issue_date<<"\n"<<"Return Date="<<return_date<<endl;
			file.seekp(i*recsize*5+i*2);
			for(int i=0;i<recsize;i++)
				file.put('#');
			return(found);
		}
		else
		{
			for(int j=0;j<5;j++){
				file.seekg(i*recsize*5+j*recsize+i*2);
				file.getline(dummy,5,'\n');
				if(strcmp(dummy,"####")==0)
					return(found);
				file.seekg(i*recsize*5+j*recsize+i*2);
				file.getline(key,5,'|');
				if(strcmp(key,k)==0)
				{
					found=1;
					cout<<"Record found"<<endl;
					file.getline(name,30,'|');
					file.getline(price,5,'|');
					file.getline(phno,20,'|');
					file.getline(book,10,'|');
					file.getline(issue_date,20,'|');
					file.getline(return_date,17,'|');
					cout<<setiosflags(ios::left);
					cout<<"Key="<<key<<"\n"<<"Name="<<name<<"\n"<<"Fine="<<price<<"\n"<<"Phone no="<<phno<<"\n"<<"book="<<book<<"\n"<<"Issue Date="<<issue_date<<"\n"<<"Return Date="<<return_date<<endl;
					file.seekp(i*recsize*5+j*recsize+i*2);
					for(int i=0;i<recsize;i++)
						file.put('#');
					return(found);
				}
			}
			i++;
			if(i%max==0)
				i=0;
		}
	} while(i!=addr);
	return(found);
}
void Library::displayall(){
	file.open(fn,ios::in);
	char dummy[10];
	cout<<setiosflags(ios::left);
	cout<<setw(5)<<"KEY"<<setw(11)<<"NAME"<<setw(7)<<"FINE"<<setw(18)<<"PHONE NO"<<setw(10)<<"BOOK"<<setw(15)<<"ISSUE"<<setw(15)<<"RETURN"<<endl;
	for(int i=0;i<max;i++){
		for(int j=0;j<5;j++){
			file.seekg(i*recsize*5+j*recsize+i*2);
			file.getline(dummy,5,'\n');
			if(strcmp(dummy,"####")!=0){
				file.seekg(i*recsize*5+j*recsize+i*2);
				file.getline(key,5,'|');
				file.getline(name,30,'|');
				file.getline(price,5,'|');
				file.getline(phno,20,'|');
				file.getline(book,10,'|');
				file.getline(issue_date,20,'|');
				file.getline(return_date,17,'|');
				cout<<setiosflags(ios::left);
				cout<<setw(5)<<key<<setw(11)<<name<<setw(7)<<price<<setw(18)<<phno<<setw(10)<<book<<setw(15)<<issue_date<<setw(15)<<return_date<<endl;
			}
		}
 }
}
void main()
{
	int ch,addr;
	char skey[5];
	Library r;
	clrscr();
	r.initial();
	for(;;)
       {
	int outerchoice=0;
	while(outerchoice!=9)
	{
	system("cls");
	cout<<"\n================================================================================\n";
	cout<<" WELCOME TO LIBRARY MANAGEMENT SYSTEM\n";
	cout<<"================================================================================\n";
	cout<<"\n1. Login";
	cout<<"\n2. Exit";
	cout<<"\n\nEnter your choice : ";
	cin>>outerchoice;
	if( outerchoice == 1 )
	 {
	   char adminUser[10];
	   char adminPassword[10];
	   cout<<"\n ----------  Login -------";
	   cout<<"\n\n Enter username: ";
	   cin>>adminUser;
	   cout<<"\n Enter password:";
	   cin>>adminPassword;
	   if( (strcmp(adminUser, ADMINUSER) == 0) && ( strcmp(adminPassword, ADMINPASSWORD) == 0))
	   {
	      getchar();cout<<"\nAdmin Login is Successful !! press any key to continue ..\n";
	      getchar();
	      system("cls");
	      int innerChoice = 0;
	      cout<<"\n================================================================================\n";
	      cout<<" WELCOME TO LIBRARY MANAGEMENT SYSTEM\n";
	      cout<<"================================================================================\n";
	      while(innerChoice != 9)
	      {

		cout<< "\n0 : The books we have\n";
		cout<< "1 : To enter the user details\n";
		cout<< "2 : Check your current book status\n";
		cout<< "3 : Delete the user record\n";
		cout<< "4 : Modify the user the details or change your book\n";
		cout<< "5 : Dispay all\n";
		cout<< "6 : Exit\n";
		cin>>ch;
		int found;
		switch(ch)
		{
		    case 0: textcolor(LIGHTBLUE);
			    cprintf("***The Books we have****");
			    cout<<"\nDBMS\n";
			    cout<<"ATC\n";
			    cout<<"PYTHON\n";
			    cout<<"FS\n";
			    cprintf("*************\n");
			    break;
			case 1: textcolor(LIGHTBLUE);
				cprintf("***Enter Library details***");
				cout<<endl;
				r.read();
				addr=r.hash(r.key);
				r.store(addr);
				cout<<"Record inserted successfully\n";
				cprintf("*************");
				cout<<endl;
				break;
			case 2: textcolor(WHITE);
				cprintf("Enter key value:");
				cin>>skey;
				addr=r.hash(skey);
				r.retrieve(addr,skey);
				break;
			case 3: textcolor(YELLOW);
				cprintf("Enter key value:");
				cin>>skey;
				addr=r.hash(skey);
				found=r.remove(addr,skey);
				if(found==0)
					cout<<"\nRecord does not exist in hash file\n";
				else
					cout<<"Record Deleted sucessfully"<<endl;
				break;
			case 4: textcolor(RED);
				cprintf("Enter key value:");
				cin>>skey;
				addr=r.hash(skey);
				found=r.remove(addr,skey);
				file.close();
				cout<<found<<endl<<endl;
				if(found==0)
					cout<<"\nRecord does not exist in hash file"<<endl;
				else
				{
					cout<<endl<<"Enter modified Library details:"<<endl;
					r.read();
					addr=r.hash(r.key);
					r.store(addr);
					cout<<"Record updated sucessfully"<<endl;
				}
				break;
			case 5: textcolor(GREEN);
				cprintf("***The Library is***");
				cout<<endl;
				r.displayall();
				cprintf("**********");
				cout<<endl;
				break;
			default: cout<<"Press any key to exit:";
					getch();
					exit(0);
		}
		file.close();
	      }
	    }
	  else
		{	getchar();
			cout<<"Wrong username or password";getchar();
		}
	}
      }
    }
 }