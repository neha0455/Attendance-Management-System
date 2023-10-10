#include<iostream>
#include<conio.h>
#include <string>
#include<fstream>
#include<iomanip>
using namespace std;

struct student{
	int rollno;
	string name;
	int attend;
}s;


class Student{
	public:
		addStudents(){
			int i,n;
			ofstream fout;
			fout.open("Stu_Records.csv",ios::app);
			ofstream fattend("attend.csv",ios::app);
			cout<<"\n\t\t Enter number of students to add: ";
			cin>>n;
			
			for(i=0;i<n;i++){
				cout<<"\n\t\t Enter Roll No: ";
				cin>>s.rollno;
				cout<<"\t\t Enter Name: ";
				cin>>s.name;
				fout<<s.rollno;
				fout<<"\t"<<s.name<<"\n";
				fattend<<s.rollno<<"\t";
				fattend<<0<<"\n";
			}
			fout.close();
			fattend.close();
			system("cls");
			cout<<"\n\n\t\t"<<n<<" Records inserted!!";
		}
};
class Attendance:public Student{
	public:
		mark_attendance(){
			int p;
			ifstream fattend("attend.csv");
			ofstream ftemp("temp.csv");
			if(!fattend){
				cout<<"Unable to open attend file";
				getch();
				return 0;
			}
			if(!ftemp){
				cout<<"Unable to open temp file";
				getch();
				return 0;
			}
			cout<<"\n\n Mark attendance against each roll no. \n\t 1 for present\n\t 0 for absent.";
			cout<<"\n\nRollNo\tAttendance";
			while(fattend>>s.rollno>>s.attend){
				cout<<"\n"<<s.rollno<<"\t";
				cin>>p;
				ftemp<<s.rollno<<"\t";
				s.attend+=p;
				ftemp<<s.attend<<"\n";
		}
			fattend.close();
			ftemp.close();
			remove("attend.csv");
			rename("temp.csv","attend.csv");
			cout<"\n\tAttendance Marked!!!!";
		}
		
		show_attendance(){
			int temp;
			ifstream fstud("Stu_Records.csv");
			ifstream fattend("attend.csv");
			if(!fattend){
				cout<<"unable to open file";
				getch();
			}
			cout<<"\n\n************************************************";
			cout<<"\n\tDISPLAYING STUDENT ATTENDANCE";
			cout<<"\n************************************************\n";
			cout<<setw(8)<<"\n\nRollNo\t"<<setw(15)<<"Name\t"<<setw(10)<<"\tAttendance";
			cout<<"\n------------------------------------------------";
			while(fstud>>s.rollno>>s.name){
				fattend>>temp;
				fattend>>s.attend;
				cout<<"\n"<<setw(4)<<s.rollno;
				cout<<"\t"<<setw(15)<<s.name;
				cout<<"\t\t"<<setw(5)<<s.attend;
			}
			fstud.close();
			fattend.close();
			
		}
		elligible(int l){
			double att_per;
			int count=0;
			ifstream fattend("attend.csv");
			if(!fattend){
				cout<<"Unable to open file";
				getch();
				return 0;
			}
			cout<<"\n\n************************************************";
			cout<<"\n\tLIST OF ELLIGIBLE STUDENTS FOR EXAMINATION";
			cout<<"\n************************************************\n";
			cout<<"\nRollNo"<<"\t\tAttendance";
			cout<<"\n-----------------------------------";
			while(fattend>>s.rollno>>s.attend){
				att_per=s.attend/l*100;
				if(att_per>=75){
					cout<<"\n"<<s.rollno<<"\t\t";
					cout<<att_per<<"\t";
					cout<<"\tElligible";
					count++;
				}	
			}
			if(count==0){
				cout<<"\n\n  NO STUDENTS ELLIGIBLE...!";
			}
			cout<<"\n\n\tPress any key to exit....";
			fattend.close();
		}
};

int main(){
	string uname,pass; //user entered username and password
	char pass_ch;
	bool con; //to continue or not in case of some error
	string user="admin", pwd="admin"; //actual username and password
	int ch; //choice for menu
	char ast;//set asterisk in password
	Attendance a;
	q:cout<<"\n\n\t";
    cout<<"************************************************";
    cout<<"\n\t\t ATTENDANCE MANAGEMENT SYSTEM";
    cout<<"\n\t************************************************";
    cout<<"\n\n\t\t Enter username: ";
    cin>>uname;
    if(uname==user)
    {
    	cout<<"\t\t Enter password: ";
    	pass_ch = _getch();
   	while(pass_ch != 13) //char 13 is return
	{
      pass.push_back(pass_ch);
      cout << '*';
      pass_ch = _getch();
   }

    	if(pass==pwd){
    		menu: system("cls");
    		cout<<"\n\t************************************************";
			cout<<"\n\t\t Access Granted!!";
    		cout<<"\n\t************************************************";
    		cout<<"\n\t\t 01. Add Student";
    		cout<<"\n\t\t 02. Mark Attendance";
    		cout<<"\n\t\t 03. Show Attendance";
    		cout<<"\n\t\t 04. Check Eligibility";
    		cout<<"\n\t\t 05. Exit";
    		cout<<"\n\n\t\t Enter your choice: ";
    		cin>>ch;
    		
    		switch(ch){
    			case 1:
    				system("cls");
    				a.addStudents();
    				goto menu;
    				
    			case 2:
    				system("cls");
    				a.mark_attendance();
    				goto menu;
    				
    			case 3:
    				system("cls");
    				a.show_attendance();
    				cout<<"\n\n\t\tPress any key to exit!!";
    				getch();
    				goto menu;
    				
    			case 4:
    				system("cls");
    				int lec;
    				cout<<"\n\n\tEnter total number of lectures delivered: ";
    				cin>>lec;
    				a.elligible(lec);
    				getch();
    				goto menu;
    				
    			case 5:
    				cout<<"\n\t\t Exiting....";
    				exit(0);
    			default:
    				cout<<"\n\t\t Invalid Choice!!";
    				cout<<"\n\t\t Press 1 to continue\n\t\t Press 0 to exit";
    				cin>>con;
    				if(con)
    					goto menu;
    				else{
    					cout<<"\n\t\t Exiting....";
    					exit(0);
					}
    				
			}
    		
		}
		else{
			cout<<"\n\t\t Invalid Password!";
			cout<<"\n\t\t Press 1 to try again\n\t\t Press 0 to exit: ";
			cin>>con;
			pass="";
			if(con){
				system("cls");
				goto q;
			}
			else{
				cout<<"\n\t\t Exiting....";
    			exit(0);
			}
		}
	}
	else{
		cout<<"\n\t\t Invalid Username!";
		cout<<"\n\t\t Press 1 to try again\n\t\t Press 0 to exit: ";
		cin>>con;
		if(con){
			system("cls");
			goto q;
		}
		else{
			cout<<"\n\t\t Exiting....";
    		exit(0);
		}
	}
	
	return 0;
}
