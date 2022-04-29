#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;



struct position
{
position *previous;
char number;
position *next;
}*head=NULL,*tail=NULL ;


bool upwardmovability;
bool downwardmovability;
bool rightmovability;
bool leftmovability;
bool back_to_menu;
bool restart_game;
bool p;
bool pa;
bool resume;
bool play_again;
int chances;
bool didnt_win;
int score;
int scoring;

void main_menu();
bool checknumbers(position* newvalue);
void setempty();
void setnumbers();
void game_interface();
void help();
void pause();
void move_empty_tile();
void winner();
void looser();
void start_game();

int main()
{
 do
  {
   char choice;
   bool invalid=1;
   do
   {
     main_menu();
     choice=getch();
     switch(choice)
      {
        case '1':
         start_game();
         invalid=0;
          break;

        case '3':
         exit(1);
         break;
      }
   }while(invalid);
 }while(back_to_menu);

    return 0;
}


void main_menu()
{
    system("CLS");
    cout<<"\n\n\t_______________________________________________________________\n";
    cout<<"\t\twelcome to the number slider puzzle game!!!!\n";
    cout<<"\t_______________________________________________________________\n\n\n\n";

    cout<<"\t\t *  *  *  *  *  *  *  *  *  *  *  *  *  * * \n";
    cout<<"\t\t*                                          *\n";
    cout<<"\t\t*  \t\tMAIN MENU\t\t   *\n";
    cout<<"\t\t*                                          *\n";
    cout<<"\t\t*                                          *\n";
    cout<<"\t\t*  \tStart game --> press 1\t\t   *\n";
    cout<<"\t\t*                                          *\n";
    cout<<"\t\t*  \texit --> press 3\t\t   *\n";
    cout<<"\t\t *  *  *  *  *  *  *  *  *  *  *  *  *  * * \n\n";

}

bool checknumbers(position* newvalue)
{
 bool found=0;
 position *temp=head;

 while(temp!=NULL)
  {
     if(newvalue->number==temp->number)
      {
        found=1;
        break;
      }
      else
        found=0;

     temp=temp->next;
  }

 return found;
}

void setempty()
{
    char location;//insert after the location specified
    position * temp=head;
    position * emptynode=new position;
    emptynode->number=' ';


    location=(1+(rand()%8));
    while(temp->number!=location&&temp!=NULL)
      {
        temp=temp->next;

      }

    if(temp->next==NULL)
      {
          tail=emptynode;
      }
    else
      {
          (temp->next)->previous=emptynode;
      }

      emptynode->next=temp->next;
      emptynode->previous=temp;
      temp->next=emptynode;


}

void setnumbers()
{


srand(time(0));
for(int i=0;i<8;i++)
    {
      position *newnode=new position;
      newnode->previous=NULL;
        do{
          newnode->number=(1+(rand()%8));
          }while(checknumbers(newnode));


      if(head==NULL)
       {
        newnode->next=NULL;
        head=newnode;
        tail=newnode;
       }

       else
        {
            newnode->next=head;
            head->previous=newnode;
            head=newnode;
        }


    }

setempty();

}

void game_interface()
{

 system("CLS");
 position *temp=head;
 cout<<"\n\n\n\n\t\t\t\t\t\tChances left:"<<chances<<endl;
 cout<<"\n\t\t\t\t\t\tYour score  :"<<score<<endl;
 for(int i=0;i<3;i++)
  {

   cout<<"\t-------------------------\n";
   cout<<"\t|\t|\t|       |\n";
    for(int j=0;j<3;j++)
      {
        if((int)temp->number==32)
          cout<<"\t|   "<<temp->number<<" ";
        else
          cout<<"\t|   "<<(int)temp->number<<" ";
        if(j==2)
            cout<<"  |";
        temp=temp->next;
      }

        cout<<endl;
  }
   cout<<"\t-------------------------\n";

}


void pause()
{

 char key;
 bool invalid=1;
 do{
    system("CLS");
    cout<<"\n\n\n\n\n\t_________________________________\n";
    cout<<"\t|\t   Pause\t\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t|\tContinue(Press C)\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t|\tRestart game(Press R)\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t|\tMain menu(Press M)\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t|\tExit(Press E)\t\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t---------------------------------\n";
    key=getch();
    if(key=='C'||key=='c')
    {
        resume=1;
        didnt_win=1;
        invalid=0;
    }
    else
    {
        didnt_win=0;
        resume=0;
    }

    if(key=='R'||key=='r')
    {
        restart_game=1;
        play_again=1;
        p=1;
        head=NULL;
        invalid=0;
    }
    else
    {
        restart_game=0;
        play_again=0;
        p=0;
    }

    if(key=='M'||key=='m')
    {
        back_to_menu=1;
        head=NULL;
        pa=1;
        invalid=0;
    }
    else
    {
        back_to_menu=0;
        pa=0;
    }

    if(key=='E'||key=='e')
    {
        exit(1);
    }

  }while(invalid);
}


void move_empty_tile()
{
 int row,column;
 position *temp=head;
 for(int i=0;i<3;i++)
  {

    bool exit_second_loop=0;
    for(int j=0;j<3;j++)
     {
        if((int)temp->number==32)
         {
          row=i;
          column=j;
          exit_second_loop=1;
          break;
         }

        temp=temp->next;
     }

    if(exit_second_loop)
        break;
  }

 if(row>0)
    upwardmovability=1;
 else
    upwardmovability=0;

 if(row<2)
    downwardmovability=1;
 else
    downwardmovability=0;

 if(column<2)
    rightmovability=1;
 else
    rightmovability=0;

 if(column>0)
    leftmovability=1;
 else
    leftmovability=0;

 bool invalid=1;
 char control;
 do{
     control=getch();
     if(upwardmovability&&(control=='W'||control=='w'))
          invalid=0;
     if(downwardmovability&&(control=='S'||control=='s'))
          invalid=0;
     if(leftmovability&&(control=='A'||control=='a'))
          invalid=0;
     if(rightmovability&&(control=='D'||control=='d'))
          invalid=0;
     if(control=='P'||control=='p')
          invalid=0;
   }while(invalid);

 switch(control)
 {
  position * swapper;
  char store;

  case 'W':
  case 'w':
     swapper=temp->previous;
     for(int i=1;i<=2;i++)
        swapper=swapper->previous;

     store=temp->number;
     temp->number=swapper->number;
     swapper->number=store;
     chances--;
     p=0;
     pa=0;
    break;
  case 'S':
  case 's':
     swapper=temp->next;
     for(int i=1;i<=2;i++)
        swapper=swapper->next;

     store=temp->number;
     temp->number=swapper->number;
     swapper->number=store;
     chances--;
     p=0;
     pa=0;
    break;
  case 'A':
  case 'a':
     swapper=temp->previous;
     store=temp->number;
     temp->number=swapper->number;
     swapper->number=store;
     chances--;
     p=0;
     pa=0;
    break;
  case 'D':
  case 'd':
     swapper=temp->next;
     store=temp->number;
     temp->number=swapper->number;
     swapper->number=store;
     chances--;
     p=0;
     pa=0;
    break;
  case 'P':
  case 'p':
     pause();
   break;
 }

}


void winner()
{

  position *temp=head;
  for(int i=1;i<=8;i++)
   {
     if((int)temp->number!=i)
      {
        didnt_win=1;
        resume=1;
        break;
      }
      else
      {
       didnt_win=0;
       resume=0;

       if(!didnt_win&&i==8)
        {
         char key;
         bool invalid;
            system("CLS");
            game_interface();
            cout<<"\n\n\t\tYou you won the game !!!!!\n\n";
                 Sleep(6000);
                 exit(1);
        }

      }

     temp=temp->next;
   }

}

void looser()
{
    char key;
    bool invalid;
     system("CLS");
     cout<<"\n\n\t\tYou are a looser !!!!!";
     Sleep(6000);
     exit(1);

}

void start_game()
{
  do{
    chances=80;
    scoring=10;
    setnumbers();

    do{

        score=chances*scoring;
        game_interface();
        move_empty_tile();

        if(chances==0)
        {
         didnt_win=0;
         resume=0;
         looser();
        }
        else
        {
          if(restart_game&&p)
          {
            resume=0;
            didnt_win=0;
          }
          else if(back_to_menu&&pa)
          {
            resume=0;
            didnt_win=0;
            restart_game=0;
            play_again=0;
          }
          else
          winner();
        }

      }while(didnt_win && resume);


   }while(restart_game&&play_again);

}


