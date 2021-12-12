#include<iostream.h>
#include<ctype.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<process.h>
#include<stdio.h>
#include<time.h>
#include<iomanip.h>
#include<fstream.h>

//Global Variables for Booking Info
int i=0, rt=0 , mopt=0, tflag=0, a,b,c;
float days=0, amt=0,tamt=0;
char phone[11], date[50], firstname[15], lname[10], tsport[20], tname[20],  tphone[10];
int btsteps[1]={0};

class HotelRoom
{
	public:
	char firstname[15];
	char lname[10];
	char phone[11];
	char date[50];
};

void addRecord(char firstname[15],char lname[10],char phone[11],char date[50])
{
	ofstream fout("Record.dat",ios::app);
	HotelRoom *h=new HotelRoom();
	strcpy(h->firstname,firstname);
	strcpy(h->lname,lname);
	strcpy(h->phone,phone);
	strcpy(h->date,date);
	fout.write((char*)h,sizeof(HotelRoom));
	fout.close();
}
void showRecords()
{
	ifstream fin("Record.dat",ios::in);
	clrscr();
	cout<<"\t\t\t\t"<<"BOOKING RECORDS\n\n"<<endl;

    while(!fin.eof())
    {
		HotelRoom *h=new HotelRoom();
			fin.read((char*)h,sizeof(HotelRoom));
			if(strcmp(h->firstname,"")!=0) cout<<"First Name :"<<h->firstname<<endl;
			if(strcmp(h->lname,"")!=0) cout<<"Last Name :"<<h->lname<<endl;
			if(strcmp(h->phone,"")!=0) cout<<"Phone :"<<h->phone<<endl;
			if(strcmp(h->date,"")!=0) cout<<"Date :"<<h->date<<endl;
    }
	fin.close();
}

//Used for Animated Display
void Display(int color,int delaytime,char* Displaychar)
{
	for(i=0;i<80;i++)
	{
		textcolor(color);
		delay(delaytime);
		cprintf(Displaychar);
	}
}

int AnimateBill()
{
textbackground(BLACK);
textcolor(WHITE);
clrscr();
textcolor(WHITE);
cout<<"\n\n\n\n\n\t\t\t\t";
 cprintf("Generating Bill");
 char a=176,b=219;
 cout<<"\r\t\t\t\t\n\n";
 for (int i=0;i<=15;i++)
 {
  textcolor(WHITE);
 cout<<a;
 cout<<"\r";
 cout<<"\t\t\t\t";
 for (i=0;i<=15;i++)
 {
 textcolor(WHITE);
	if(i<7)
	{
	textcolor(WHITE);
	 cout<<b;
	delay(250);
	}
	else
	{
	 textcolor(WHITE);
	cout<<b;
	delay(150);
	}
  }
}
 return 0;
}
struct Menu
{
	char *Item;
	float Price;
};

void setMenu(Menu menu[],int index,char * _item,float _price)
{
	menu[index].Item=_item;
	menu[index].Price=_price;
}

Menu MenuList[24];
int BillItems[24];
float TotalBillAmt=0;
void MenuInit()
{
	// //Breakfast and Dinner Index from 0-6
	setMenu(MenuList,0,"1.Plain Dosa",75);
	setMenu(MenuList,1,"2.Ghee Roast Dosa",100);
	setMenu(MenuList,2,"3.Chappati",60);
	setMenu(MenuList,3,"4.Idly",40);
	setMenu(MenuList,4,"5.Poori",50);
	setMenu(MenuList,5,"6.Pongal",50);
	// //Lunch Index from 6 - 11
	setMenu(MenuList,6,"7.Full Meals",75);
	setMenu(MenuList,7,"8.Mini Meals",50);
	setMenu(MenuList,8,"9.Sambar Rice",40);
	setMenu(MenuList,9,"10.Biriyani",70);
	setMenu(MenuList,10,"11.Curd Rice",50);
	setMenu(MenuList,11,"12.Tomato Rice",50);
	// //Snacks & Beverages Index from 12-17
	setMenu(MenuList,12,"13.Coffee",15);
	setMenu(MenuList,13,"14.Tea",15);
	setMenu(MenuList,14,"15.Samosa",40);
	setMenu(MenuList,15,"16.Vadai",45);
	setMenu(MenuList,16,"17.Chips",30);
	setMenu(MenuList,17,"18.Gulab Jamun",50);
	// //Ice Cream & Juices Index from 18-23
	setMenu(MenuList,18,"19.Pineapple Juice",75);
	setMenu(MenuList,19,"20.Apple Juice",50);
	setMenu(MenuList,20,"21.Pista Milkshake",100);
	setMenu(MenuList,21,"22.Vanilla IceCream",75);
	setMenu(MenuList,22,"23.Strawberry IceCream",90);
	setMenu(MenuList,23,"24.Chocolate IceCream",90);
	for(int i=0;i<24;i++) BillItems[i]=0;
}


void printMenu(char* title, int start,int end)
{
	cout<<title<<endl;
	cout<<setw(40)<<setfill('*')<<""<<endl;
	cout<<setfill(' ');
	for(int msection=start;msection<end;msection++) 
	{
		cout<<setw(25)<<setiosflags(ios::left)<<MenuList[msection].Item<<" : "<<MenuList[msection].Price<<endl;
	}
}

int AddtoMenu(int start,int end)
{
	int qty=0;
	int menuselection=0;
	cout<<"Select Item no. or 0 to quit to main menu."<<endl;
	cin>>menuselection;
	if(menuselection==0) return 0;
	if(menuselection < start+1 || menuselection >end)
	{
		cout<<"Wrong Menu choice... enter to continue"<<endl;
		getch();
		return 1;
	}
	cout<<"Enter the Quantity..."<<endl;
	cin>>qty;
	if(qty==0)
	{
		cout<<"Quantity cannot be zero... enter to continue"<<endl;
		getch();
		return 1;
	}
	BillItems[menuselection-1]=qty;
	return 100;
}

int ModifyMenu(int start,int end)
{
	int qty=0;
	int menuselection=0;
	cout<<"Select Item no. to modify or 0 to quit to main menu."<<endl;
	cin>>menuselection;
	if(menuselection==0) return 0;
	if(menuselection < start+1 || menuselection > end)
	{
		cout<<"Wrong Menu choice... enter to continue"<<endl;
		getch();
		return 1;
	}
	cout<<"Enter the Quantity..."<<endl;
	cin>>qty;
	if(qty<0)
	{
		cout<<"Quantity cannot be negative... enter to continue"<<endl;
		getch();
		return 1;
	}
	BillItems[menuselection-1]=qty;
	return 100;
}


void MenuItemSelection(char * title,int start,int end)
{

	int choice;
	int loop=1;
	int ret=0;
	clrscr();
	while(loop)
	{
		clrscr();
		printMenu(title,start,end);
		if(BillItems[start] > 0 || BillItems[start+1] > 0 || BillItems[start+2] > 0 || BillItems[start+3] > 0 ||BillItems[start+4] > 0 || BillItems[start+5] > 0)
		{
			choice=0;
			cout<<"Select 1 to Add 2 to Modify items to menu or Press 3 for main menu..."<<endl;
			cin>>int(choice);
			if(choice==2)
			{
				ret=ModifyMenu(start,end);
				if(ret==0) break;
				else if(ret==1) continue;
			}
			else if(choice==1)
			{
				ret=AddtoMenu(start,end);
				if(ret==0) break;
				else if(ret==1) continue;
			}

			else
			{
			break;
			}
			break;
		}
		else
		{
			ret=AddtoMenu(start,end);
			if(ret==0) break;
			else if(ret==1) continue;
		}
	}
}

void PreviewBill()
{
	clrscr();
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	TotalBillAmt=0;
	cprintf("Bill");
	cout<<endl;
	cout<<setw(10)<<setfill('*')<<""<<endl;
	cout<<setfill(' ');
	for(int i=0;i<24;i++)
	{
		if(BillItems[i]>0)
		{
			cout<<setw(40)<<setiosflags(ios::left)<<MenuList[i].Item<<" ( "<<MenuList[i].Price<< ") "<<" X "<<BillItems[i]<<" = "<<MenuList[i].Price*BillItems[i]<<endl;
			TotalBillAmt+=MenuList[i].Price*BillItems[i];
		}
	}
	cout<<setw(10)<<setfill('*')<<""<<endl;
	cout<<setfill(' ');
	cout<<"Total Amount : "<<TotalBillAmt<<endl;
	getch();
}

void GenerateBill()
{
	AnimateBill();
	PreviewBill();
}


int foodmanagement()
{
	int selection=0;
	clrscr();
	MenuInit();
	while(1)
	{
	      textbackground(BLACK);
		clrscr();
		Display(LIGHTBLUE,20,"#");
		textcolor(BLUE);
		cout<<"\t\t\t\t";
		cprintf("\nFOOD ORDERS");
		cout<<"\n\n";
		Display(LIGHTBLUE,20,"#");
		textbackground(BLACK);
		textcolor(GREEN);
		cout<<"Enter your choice..."<<endl;
		cout<<"Select 1 for Breakfast & Dinner Menu"<<endl;
		cout<<"Select 2 for Lunch Menu"<<endl;
		cout<<"Select 3 for Snacks & Beverages Menu"<<endl;
		cout<<"Select 4 for IceCream & Juices Menu"<<endl;
		cout<<"Select 5 to Preview Bill"<<endl;
		cout<<"Select 6 to Generate Bill"<<endl;
		cout<<"Select 7 to Exit"<<endl;
		cout<<"\n\n";
		cin>>selection;
		switch(selection)
		{
			case 1:
				MenuItemSelection("Breakfast and Dinner",0,6);
				break;
			case 2:
				MenuItemSelection("Lunch",6,12);
				break;
			case 3:
				MenuItemSelection("Snacks & Beverages",12,18);
				break;
			case 4:
				MenuItemSelection("IceCream & Juices",18,24);
				break;
			case 5:
				PreviewBill();
				textbackground(BLACK);
				textcolor(GREEN);
				break;
			case 6:
				GenerateBill();
				textbackground(BLACK);
				textcolor(GREEN);
				break;
			case 7: cout<<"Press any key to exit";
				return 0;
			default:
				cout<<"Invalid selection"<<endl;
				break;
		}

	}

}
float CalculateAmount(float noofdays)
{

	if(rt==1)
	{
		return noofdays*22000;
	}
	else if(rt==2)
	{
		return noofdays*10000;
	}
	else if(rt==3)
	{
		return noofdays*5000;
	}
	return 0;
}

int ShowBill()
{
	int i;
	textbackground(WHITE);
	clrscr();
	Display(BLACK,20,"*");
	textcolor(BLACK);
	cout<<"\t\t\t\t\t";
	cprintf("\nBILL");
	cout<<"\n\n";
	Display(BLACK,20,"*");
	textcolor(BLACK);
	cprintf(" NAME");
	cout<<"\t\t";
	cprintf("Phone No");
	cout<<"\t";
	cprintf("Room Type");
	cout<<"\t\t";
	cprintf("Amount Inclusive of tax\n\n\n");
	cout<<"  "<<firstname<<"  \t"<<phone<<"\t";
	if(rt==1)
		cout<<"Ultra deluxe";
	else if(rt==2)
		cout<<"Deluxe";
	else
		cout<<"Normal";

	cout<<"\t\t\t";
	cout<<amt;
	cout<<"\n "<<lname;
	getch();
	return 1;
}

void clearArray(char data[])
{
	data[0]='\0';
}
int Book()
{
			pas1:
			textbackground(BLACK);
			clrscr();
			textcolor(YELLOW);
			Display(BLUE,20,"*");
			textcolor(RED);
			cout<<"\t\t\t\t";
			cprintf("\nBOOKING");
			cout<<"\n\n";
			Display(BLUE,20,"*");
			textcolor(YELLOW);
			cout<<"\n\t\t\t\t";
			cout<<"Room types\n";
			cout<<"\n\t\t\t\t";
			cprintf("1.Ultra Deluxe               Rs15000");
			cout<<"\n\t\t\t\t";
			delay(100);
			cprintf("2.Deluxe                     Rs10000");
			cout<<"\n\t\t\t\t";
			delay(100);
			cprintf("3.Normal                     Rs5000");
			cout<<"\n\t\t\t\t";
			delay(100);
			cprintf("4.Exit");
			cout<<"\n\t\t\t\t";
			delay(100);
			cprintf("Choose your room type:");
			cout<<"\n\n\n\n ";
			cin>>rt;
			int bSteps[4]={0,0,0,0};
			if(rt<4)
			{
				validation:
				clrscr();
				textbackground(BLACK);
				textcolor(RED);
				cprintf("\nPersonal Information\n\n");
				cout<<"\t";
				textcolor(MAGENTA);
				cprintf("\nEnter the Person's first name : ");
				if(bSteps[0]==0)
				{
					cin>>firstname;
					if(strlen(firstname)>10)
					{
						firstname[0]='\0';
						cout<<"\t\t\tError : Name should be maximum 15 char length..."<<endl;
						getch();
						goto validation;
					}
					firstname[strlen(firstname)]='\0';
					bSteps[0]=1;
				}
				else
				{
					cout<<firstname;
				}
				cout<<endl;
				cout<<"\t\t\t";
				cprintf("\nEnter the Person's last name : ");
				if(bSteps[1]==0)
				{
					gets(lname);
					if(strlen(lname)>10)
					{
						lname[0]='\0';
						cout<<"\t\t\tError : Last Name should be maximum 10 char length..."<<endl;
						getch();
						goto validation;
					}
					lname[strlen(lname)]='\0';
					bSteps[1]=1;
					cout<<endl;
				}
				else
				{
					cout<<lname;
				}
				cout<<endl;
				cout<<"\t\t\t";
				cprintf("\nEnter Phone number : ");
				if(bSteps[2]==0)
				{
					gets(phone);
					for (i = 0; i < strlen(phone); i++)
					{

						if(isdigit(phone[i]))
						{
					  if(strlen(phone)==10)
					 {
					 continue;
					 }
					 else
					 {
					 cout<<"\t\t\tError : Phone Number should have 10 digits..."<<endl;
							getch();
							goto validation;
					 }

						}
						else
						{
							cout<<"\t\t\tError : Phone Number should have numeric digits..."<<endl;
							getch();
							goto validation;
						}
					}

					bSteps[2]=1;
				}
				else
				{
					cout<<phone;
				}
				cout<<endl;
				cout<<"\t\t\t";
				cprintf("\nEnter number of days of stay : ");
				if(bSteps[3]==0)
				{
					cin>>days;
					if(days>365)
					{
						cout<<"\t\t\tError : Days cannot be greater than 365..."<<endl;
						getch();
						goto validation;
					}
					else
						bSteps[3]=1;
				}
				else
				{
					cout<<days;
				}
				cout<<"\n\t\t\t";
				time_t rawtime;
				struct tm * timeinfo;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				strcpy(date,asctime(timeinfo));
				cout<<"\nDate : "<<date<<endl;
				amt=CalculateAmount(days);
				AnimateBill();
				ShowBill();
				addRecord(firstname,lname,phone,date);
			}
			else if(rt==4)
			{
				return 1;
			}
			else
			{
				cprintf("Entered wrong information");
				goto pas1;
			}
 return 0;
}





void tshowbill()
{
textbackground(WHITE);
textcolor(BLACK);
clrscr();
cout<<endl;
	Display(BLACK,20,"*");
	textcolor(BLACK);
	cout<<"\t\t\t\t";
	cprintf("\nBILL");
	cout<<"\n\n";
	Display(BLACK,20,"*");
cout<<"\r\t";
cprintf("Name :");
cout<<tname<<"\n\n"<<endl;
cout<<"\r\t";
cprintf("Phone :");
cout<<tphone<<"\n\n"<<endl;
sleep(1);
if(tflag==0)
{
cout<<"\n\n\nPayment of Rs"<<tamt<<" was Successful"<<"\n\nPress any key to continue...";
}
else if(tflag==1)
{
cout<<"\n\n\nYou can use "<<tsport<<" Without trainer For 1 month for free "<<"\n\nPress any key to continue...";
}
getch();
}
void trainernames()
{
tvalidation:
				cprintf("\nEnter the Person's name : ");
				if(btsteps[0]==0)
				{
					cin>>tname;
					if(strlen(tname)>10)
					{
						firstname[0]='\0';
						cout<<"\t\t\tError : Name should be maximum 15 char length..."<<endl;
						getch();
						goto tvalidation;
					}
					tname[strlen(tname)]='\0';
					tname[20]='\0';
					btsteps[0]=1;
				}
				else
				{
					cout<<tname;
				}

}
void trainer()
{
start2:
textbackground(BLACK);
textcolor(YELLOW);
 clrscr();
 Display(CYAN,20,"#");
	textcolor(MAGENTA);
	cout<<"\t\t\t\t\t";
	cprintf("\nTRAINER");
	cout<<"\n\n";
	Display(CYAN,20,"#");
 cprintf("Need Trainer?\n\n");
 cprintf("If Yes Press 1, if No Press 2");
 cout<<endl;
 cin>>c;

 switch(c)
 {
 case 1:   tvalidate:
 textbackground(BLACK);
 clrscr();
 textcolor(RED);
 cprintf("PERSONAL INFO");
 textcolor(YELLOW);
 cout<<endl;
 trainernames();

 cout<<endl;
 cout<<"\r";
 cprintf("\nEnter Phone number : ");
					gets(tphone);
					cout<<endl;
					for (i = 0; i < strlen(tphone); i++)
					{
					  if(isdigit(tphone[i]))
					  {
					  cout<<endl;
					    if(strlen(tphone)==10)
						{
						continue;
						}

					    else
					    {
					    cout<<endl;
					    cout<<"\t\t\tError : Phone Number should have 10 digits..."<<endl;
					    getch();
					    goto tvalidate;
					    }
					  }
					  else
					  {
					  cout<<endl;
					  cout<<"\t\t\tError : Phone Number should have numeric digits..."<<endl;
					  getch();
					  goto tvalidate;
					  }
					 }
cprintf("Trainer fees(Monthly) :Rs");
cout<<tamt;
getch();
tflag=0;
AnimateBill();
tshowbill();
break;

case 2:
tvalidate1:
textbackground(BLACK);
 clrscr();
 textcolor(RED);
 cprintf("PERSONAL INFO");
 textcolor(YELLOW);
 cout<<endl;
trainernames();
				cout<<endl;
				cout<<"\r";
				cprintf("\nEnter Phone number : ");

					gets(tphone);
					cout<<endl;
					for (i = 0; i < strlen(tphone); i++)
					{
						if(isdigit(tphone[i]))
						{
						cout<<endl;
							if(strlen(tphone)==10)
							{
							continue;
							 }
							else
							{

							cout<<"\t\t\tError : Phone Number should have 10 digits..."<<endl;
							getch();
							goto tvalidate1;
							}

						}
						else
						{
							cout<<"\t\t\tError : Phone Number should have numeric digits..."<<endl;
							getch();
							goto tvalidate1;
						}
					}


	tflag=1;
	AnimateBill();
	tshowbill();
	break;
default: cprintf("Wrong Choice");
getch();
goto start2;
}
getch();
}
int tennis()
{
pas3:
textbackground(BLACK);
textcolor(YELLOW);
clrscr();
Display(BLUE,20,"#");
	textcolor(GREEN);
	cout<<"\t\t\t\t\t";
	cprintf("\nTENNIS");
	cout<<"\n\n";
	Display(BLUE,20,"#");
 cout<<"\n1.Trainer"<<endl;
 cout<<"2.Timings"<<endl;
 cout<<"3.Exit"<<endl;
 cin>>b;
 switch(b)
 {
 case 1:tamt=12000;
	strcpy(tsport,"Tennis Court");
	trainer();
	break;
 case 2:cout<<"\n\n\nFrom 6:00 AM to 6:00 PM";
	getch();
	break;
case 3: return 0;
default: cprintf("Wrong Choice");
	getch();
	break;
}
goto pas3;
}

int swimming()
{
pas4:
textbackground(BLACK);
textcolor(YELLOW);
clrscr();
Display(BLUE,20,"#");
	textcolor(RED);
	cout<<"\t\t\t\t\t";
	cprintf("\nSwimming");
	cout<<"\n\n";
	Display(BLUE,20,"#");
cout<<endl;
 cout<<"1.Coach"<<endl;
 cout<<"2.Timings"<<endl;
 cout<<"3.Exit"<<endl;
 cin>>b;
 switch(b)
 {
 case 1:tamt=10000;
	strcpy(tsport,"Swimming Pool");
	trainer();
	break;
 case 2:cout<<"\n\n\nFrom 6:00 AM to 4:00 PM";
	getch();
	break;
case 3: return 0;

default:cprintf("Wrong Choice");
	getch();
break;
}
goto pas4;
}
int basketball()
{
pas5:
textbackground(BLACK);
textcolor(YELLOW);
clrscr();
Display(BLUE,20,"#");
	textcolor(RED);
	cout<<"\t\t\t\t  ";
	cprintf("\nBasketball");
	cout<<"\n\n";
	Display(BLUE,20,"#");
cout<<endl;
 cout<<"1.Coach"<<endl;
 cout<<"2.Timings"<<endl;
 cout<<"3.Exit"<<endl;
 cin>>b;
 switch(b)
 {
 case 1:tamt=20000;
	strcpy(tsport,"Basketball Court");
	trainer();
	break;
 case 2:cout<<"\n\n\nFrom 6:00 AM to 7:00 PM";
	getch();
	break;
case 3: return 0;

default:cprintf("Wrong Choice");
	getch();
	break;
}
goto pas5;
}
int gym()
{
pas1:
textbackground(BLACK);
textcolor(YELLOW);
clrscr();
Display(BLUE,20,"#");
	textcolor(BLUE);
	cout<<"\t\t\t\t\t";
	cprintf("\nGym");
	cout<<"\n\n";
	Display(BLUE,20,"#");
cout<<endl;
 cout<<"1.Trainer"<<endl;
 cout<<"2.Timings"<<endl;
 cout<<"3.Exit"<<endl;
 cin>>b;
 switch(b)
 {
 case 1:tamt=18000;
	strcpy(tsport,"Gym");
	trainer();
	break;
 case 2:cout<<"\n\n\nFrom 6:00 AM to 8:00 PM";
	getch();
	break;
case 3: return 0;

default:cprintf("Wrong Choice");
	getch();
	break;
}
goto pas1;
}
int sportsmanagement()
{
start1:
textbackground(BLACK);
textcolor(GREEN);
clrscr();
int a;
	Display(LIGHTRED,20,"#");
	textcolor(BLUE);
	cout<<"\t\t\t\t";
	cprintf("\nSPORTS");
	cout<<"\n\n";
	Display(LIGHTRED,20,"#");

cout<<"\n\n\n\n1.GYM";
cout<<"\n2.TENNIS";
cout<<"\n3.SWIMMING POOL";
cout<<"\n4.BASKET BALL";
cout<<"\n5.EXIT\n\n";
cin>>a;
switch(a)
{
case 1: gym();
	break;
case 2:tennis();
	break;
case 3:swimming();
	break;
case 4:basketball();
	break;
case 5:cprintf("\nPress any key to exit");
       return 0;

default:cout<<"wrong choice";
	getch();
	break;
}
goto start1;
}
void map()
{
textbackground(BLACK);
textcolor(LIGHTGRAY);
clrscr();
textbackground(BLACK);
textcolor(LIGHTGRAY);
cout<<"###########################################################################";
cout<<"\n";
cout<<"#*********************#                           #$$$$$$$$$$$$$$$$$$$$$$$#";
cout<<"\n";
cout<<"#*                   *#                           #$                      #";
cout<<"\n";
cout<<"#*                   *#                           #$                      #";
cout<<"\n";
cout<<"#*      TENNIS       *#       CAR PARKING         #$       Swimming       #";
cout<<"\n";
cout<<"#*                   *#                           #$        Pool          #";
cout<<"\n";
cout<<"#*                   *#                           #$                      #";
cout<<"\n";
cout<<"#*                   *#                           #$                      #";
cout<<"\n";
cout<<"#*********************#                           #$$$$$$$$$$$$$$$$$$$$$$$#";
cout<<"\n";
cout<<"#######################!!!!!!!!!!!!!!!!!!!!!!!!!!!#########################";
cout<<"\n";
cout<<"               !!!!!!!!!                         !!!!!!!!!!!!!!!!!";
cout<<"\n";
cout<<"               !                                                 !";
cout<<"\n";
cout<<"     GARDEN    !                 HOTEL                           !";
cout<<"\n";
cout<<"               !                                                 !";
cout<<"\n";
cout<<"               !!!!!!!!!                          !!!!!!!!!!!!!!!!";
cout<<"\n";
cout<<"#######################!                          !########################";
cout<<"\n";
cout<<"#&&&&&&&&&&&&&&&&&&&&&#!                          !#^^^^^^^^^^^^^^^^^^^^^^#";
cout<<"\n";
cout<<"#&                   &#!                          !#^                     #";
cout<<"\n";
cout<<"#&                   &#!                          !#^                     #";
cout<<"\n";
cout<<"#&     Basketball    &#!                          !#^        GYM          #";
cout<<"\n";
cout<<"#&                   &#!                          !#^                     #";
cout<<"\n";
cout<<"#&                   &#!                          !#^                     #";
cout<<"\n";
cout<<"#&&&&&&&&&&&&&&&&&&&&&#!!!!!!!!!!!!!!!!!!!!!!!!!!!!#^^^^^^^^^^^^^^^^^^^^^^#";
cout<<"\n";
cout<<"###########################################################################";
cout<<"\n\nPress any key to continue";
getch();
}
int More()
{ mpas:
textbackground(BLACK);
clrscr();

Display(YELLOW,1,"#");
		textcolor(BLUE);
		cout<<"\t\t\t\t\t";
		cprintf("\nMore");
		cout<<"\n\n";
		Display(YELLOW,1,"#");
		cout<<endl;
		textcolor(GREEN);
		cprintf("\n1.CONTACT US ON\n");
		cout<<"\r";
		cprintf("2.ADDRESS\n");
		cout<<"\r";
		cprintf("3.EMAIL\n");
		cout<<"\r";
		cprintf("4.MAP\n");
		cout<<"\r";
		cprintf("5.EXIT\n\n");
		cout<<"\r";
		cin>>mopt;
		switch(mopt)
		{
		case 1:cprintf("Phone:9877632166");
			cout<<endl;
			getch();
			break;
		case 2:cprintf("Address:NO.23,6th Street,Perambur,Chennai-600028");
			cout<<endl;
			getch();
			break;
		case 3:cprintf("Email:pasrt@gmail.com");
			cout<<endl;
			getch();
			break;
		case 4:map();
			getch();
			break;
		case 5: cprintf("\nPress any key to exit");
			return 0;
		default:
			cout<<"Wrong Choice"<<endl;
			break;
		}
goto mpas;
}
void main()
{
	while(1)
	{
		textbackground(CYAN);
		clrscr();
		int i;
		Display(BLACK,20,"#");
		textcolor(BLUE);
		cout<<"\t\t\t\t";
		cprintf("\nHotel Management");
		cout<<"\n\n";
		Display(BLACK,20,"#");
		cout<<endl;
		textbackground(CYAN);
		textcolor(BROWN);
		cout<<"\n\n\n\t\t\t\t" ;
		cprintf("1.Booking");
		cout<<"\n\t\t\t\t";
		delay(20);
		cprintf("2.Booking Records");
		cout<<"\n\t\t\t\t";
		delay(20);
		cprintf("3.Food Orders");
		cout<<"\n\t\t\t\t";
		delay(20);
		cprintf("4.Sports");
		cout<<"\n\t\t\t\t";
		delay(20);
		cprintf("5.More");
		cout<<"\n\t\t\t\t";
		delay(20);
		cprintf("6.Exit");
		cout<<"\n\n\n\n\n\t\t\t\t";
		int opt=0;
		cin>>opt;
		switch(opt)
		{
			case 6:
				exit(0);
				break;
			case 1:
				rt=0;
				amt=0;
				clearArray(phone);
				clearArray(date);
				clearArray(firstname);
				clearArray(lname);
				Book();

				break;
			case 2: showRecords();
				break;
			case 3:
				foodmanagement();
				break;
			case 4: sportsmanagement();
				break;
			case 5:More();
			       break;
			 default:cprintf("Entered Wrong Choice");
				 exit(0);
		}
		getch();
	}
}
