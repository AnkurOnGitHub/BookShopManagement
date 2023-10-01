#include <iostream>
#include <stdio.h>
#include <string.h>
#include<fstream>
// #include<stdlib.h>
// #include <conio.h>
#include "LoginSystem.cpp"
using namespace std;
class Book
{
    private:
        int bookId;
        char BookName[50];
        char Author[50];
        int no_of_Books;
        float price;
    public:
        void input();
        void display();
        void storeData();
        void viewAllBooks();
        void editDetail();
        void deleteAllBook();
        void deleteBook();
        void viewBook();
};
void Book::input()
{
    cout<<"Enter the BookId : ";
    cin>>bookId;
    cout<<"Enter the Book Name : ";
    cin.ignore();
    cin.getline(BookName,50);
    cout<<"Enter the Name of Author : ";
    cin.ignore(0);
    cin.getline(Author,20);
    cout<<"Enter the number of Books : ";
    cin>>no_of_Books;
    cout<<"Enter the price of Book : ";
    cin>>price;
}
void Book::display()
{
    cout<<bookId<<"   "<<BookName<<"   "<<Author<<"   "<<no_of_Books<<"   "<<price<<endl;
}
void Book::storeData()
{
    ofstream fout;
    fout.open("BookShop.txt",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
}
void Book::viewAllBooks()
{
    ifstream fin;
    fin.open("BookShop.txt",ios::in|ios::binary);
    if(!fin)
        cout<<"File Not Found ";
    else
    {
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            display();
            fin.read((char*)this,sizeof(*this));
        }
    }
    fin.close();
    // getch();
    // system("cls");
}
void Book::editDetail()
{
    fstream data,data1;
    int id;
    cout<<"Enter the Id of book in which you want to make changes : ";
    cin>>id;
    int NewId;
    int token=0;
    char NewBookName[20];
    char NewAuthor[20];
    int New_no_of_Books;
    float Newprice;

    data.open("BookShop.txt",ios::in);
    if(!data)
    {
        cout<<"File does not exist ";
    }
    else
    {
        data1.open("BookShop1.txt",ios::app|ios::binary);
        Book B3;
        data.read((char*)&B3,sizeof(B3));

        while(!data.eof())
        {
            if(B3.bookId==id)
            {
                Book B2;
                cout<<"Enter the New BookId : ";
                cin>>B2.bookId;
                cout<<"Enter the New Book Name : ";
                cin.ignore();
                cin.getline(B2.BookName,20);
                cout<<"Enter the New Author : ";
                cin.ignore(0);
                cin.getline(B2.Author,20);
                cout<<"Enter the updated No. of books ";
                cin>>B2.no_of_Books;
                cout<<"Enter the new price : ";
                cin>>B2.price;
                data1.write((char*)&B2,sizeof(B2));
                cout<<"'BOOK UPDATED SUCCESSFULLY'";
                token=1;
            }
            else
            {
                data1.write((char*)&B3,sizeof(B3));                
            }
            data.read((char*)&B3,sizeof(B3));
        }
        data.close();
        data1.close();
        

    remove("BookShop.txt");
    rename("BookShop1.txt","BookShop.txt");
    if(token==0)
        cout<<"\nRecord not found";
         

    }
}
void Book::deleteAllBook()
{
    fstream obj1;
    obj1.open("BookShop1.txt",ios::out);
    obj1.close();
    remove("BookShop.txt");
    rename("BookShop1.txt","BookShop.txt");

}
void Book::deleteBook()
{
    fstream data,data1;
    int id;
    cout<<"Enter the Id of book for delete the book : ";
    cin>>id;
    data.open("BookShop.txt",ios::in);
    if(!data)
    {
        cout<<"File does not exist ";
    }
    else
    {
        data1.open("BookShop1.txt",ios::app|ios::binary);
        Book B3;
        data.read((char*)&B3,sizeof(B3));

        while(!data.eof())
        {
            if(B3.bookId==id)
            {

            }
            else
            {
                data1.write((char*)&B3,sizeof(B3));                
            }
            data.read((char*)&B3,sizeof(B3));
        }
        data.close();
        data1.close();
        

        remove("BookShop.txt");
        rename("BookShop1.txt","BookShop.txt");
    }

}
void Book::viewBook()
{
    fstream data;int id,token=0;
    data.open("BookShop.txt",ios::in);
    cout<<"Enter the BookId : ";
    cin>>id;
    Book B4;
    data.read((char*)&B4,sizeof(B4));
    while(!data.eof())
    {
        if(B4.bookId==id)
        {
            B4.display();
            token=1;
            break;
        }
        data.read((char*)&B4,sizeof(B4));
    }
    if(token==0)
        cout<<"INVALID BOOK ID";
    data.close();
}



int main()
{
    cout<<"Testing"<<endl;
    Person P;
    int choice;
    cout<<"\nFor registration press 1 : "<<endl;
    cout<<"For Login Press 2 : "<<endl;
    cout<<"For Forget Password Press 3 : "<<endl;
    cin>>choice;
    if(choice==1)
    {
        if(P.checkUserNameCopy())
        {
            P.registration();
            cout<<"\nRegistration Successful "<<endl<<"You can Login Now"<<endl;
        }

        else
            main();

    }
    if(choice==2)
    {
        if(P.login())
        {
            cout<<"\nYou can access the Book Shop Details"<<endl;
            bool flag=true;
            while(flag)
            {
                int choice;
                cout<<endl;
                cout<<"\nEnter 1 to Add New Books "<<endl;
                cout<<"Enter 2 for update the Info "<<endl;
                cout<<"Enter 3 for view specific Book "<<endl;
                cout<<"Enter 4 for view all Books "<<endl;
                cout<<"Enter 5 for Clear the file "<<endl;
                cout<<"Enter 6 for delete a Book "<<endl;
                cout<<"Enter 7 for EXIT "<<endl;
                cin>>choice;
                Book B1;
                switch (choice)
                {
                case 1:
                    B1.input();
                    B1.storeData();
                    break;
                case 2:
                    B1.editDetail();
                    break;
                case 3:
                    B1.viewBook();
                    break;
                case 4:
                    B1.viewAllBooks();
                    break;
                case 5:
                    B1.deleteAllBook();
                    break;
                case 6:
                    B1.deleteBook();
                    break;
                case 7:
                    flag=false;
                    break;
                default:
                    cout<<"Invalid Input ";
                }

            }
        }
    }
    if(choice==3)
        P.forgetPassword();
    cout<<"THANK YOU ";
    return 0;

}
/*

void writing()
{
    ofstream obj;
    obj.open("FileHandling.txt",ios::out);//ios::out because it is static variable in ios class
    char name[20];
    cout<<"Enter the string to insert in txt file : ";
    fflush(stdin);
    fgets(name,20,stdin);
    obj<<name;
    obj.close();
}
void reading()
{
    ifstream fin;
    char str[100];
    fin.open("FileHandling.txt",ios::in);
    if(!fin)
        cout<<"File not found ";
    else
    {
        char ch;
        ch=fin.get();
        while (!fin.eof())
        {
            cout<<ch;
            ch=fin.get();
        }
    }
    fin.close();
}
void append(string data)
{
    ofstream fout;
    fout.open("FileHandling.txt",ios::app);
    fout<<data;
    fout.close();
}

*/



/*
void writing()
{
    ofstream fout;                                      //1)creating an object of ofstream
    fout.open("FH.txt",ios::out);                       //2)open is a function which is already defined in ofstream --[out is used to open file for writing ]
    char str[]="Ankur mishra is the great";             //String******[ios and scope resolution then out because out is static variable of ios stream]
    fout<<str;                                          //3)outputting the string in text file 
    fout.close();                                       //4)close the file is important
}
void reading()
{
    ifstream fin;                                       //creating an object of ifstream
    char str;                                           //creating char variable
    fin.open("FH.txt",ios::in);                         //opening the file [In is used to open for reading ]
    if(!fin)                                            //checking the condition, is file exists in dictory or not
    cout<<"File not found";
    else                                                //else is run when file exists
    {
        str=fin.get();                                  //Here get function is working and provide the single charactar to variable
        while(!fin.eof())                               //Using loop to get a single single charactar one by one [EOF stands for end of file]
            {
                cout<<str;                              //printing the charactar
                str=fin.get();                          //Taking input with the help of loop
            }
        fin.close();                                    //closing the file
    }
}
void append(char data[])                                //To append the string with exisiting
{
    ofstream fout;                                      
    fout.open("FH.txt",ios::app);                       //[app is used to append the data]
    fout<<data;                                         
    fout.close();
}

void writing1()
{
    fstream fout;
    fout.open("Test.txt",ios::out);
    char character[30];
    cout<<"Enter the string : ";
    cin.ignore();
    cin.getline(character,30);
    fout<<character;
    fout.close();

}
void reading1()
{
    ifstream fin;
    char ch;
    fin.open("Test.txt",ios::in);
    if (!fin)
        {
        cout<<"File not found ";
        }
    else
    {
        ch=fin.get();
        while(!fin.eof())
        {
            cout<<ch;
            ch=fin.get();
        }
    }   
    fin.close();
}


//Assignment :39

char* question1()
{
    ifstream fin;
    fin.open("Test.txt",ios::in);
    char ch;
    char str[20];
    ch=fin.get();
    while(!fin.eof())
        {
            cout<<ch;
            ch=fin.get();
            strcpy(str,ch);
        }
}

int main()
{
    
    reading1();


    // char ch[]=" File Handling in c++";
    // append(ch);
    // cout<<endl;
    // reading();
    // cout<<endl;


    //reading;
    //writing;
    return 0;
}
*/