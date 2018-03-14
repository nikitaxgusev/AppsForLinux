//Creator: Gusev Nikita
//Time: 19/02/2017
//Description: Realization of some options of function `more` in Linux.
//Comment: taking account the size of console in linux, and using special
//function `getch`.
//*For other OC, you'd use another function for `size`*

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#define END std::endl
 
int getch();
void helpNote();
void cutString (std::vector<std::string>& lines,std::string nextString,int cutWid);
void printNextLine(std::vector<std::string>& lines,int& numStr);
void printNextScreen(int& numStr,struct winsize w, std::vector<std::string>& lines);
 
int main(int argc, char *argv[]) {
        struct winsize w;
        char ch;
        ioctl(STDOUT_FILENO,TIOCGWINSZ, &w);
        std::ifstream rRecord;
        std::vector<std::string> lines;
        std::string str;
        std::string help("-h");
 
        if(1==argc){
            std::cout<<"Warning: "<<END;
            std::cout<<"\t\t\t0 arguments"<<END;
            std::cout<<"\t\t\tCalling for help: ./more -h"<<END;
            exit(1);
        }
        if(argv[1]==help)
        {
            helpNote();
            exit(1);
        }
        if (argc>2){
            std::cout<<"Warning: "<<END;
            std::cout<<"\t\t\tToo much arguments"<<END;
            std::cout<<"\t\t\tCalling for help: ./more -h"<<END;
            exit(1);
        }
       
        rRecord.open(argv[1]);
        int numStr=0;
 
        while (getline(rRecord,str))
        {
          cutString(lines,str,w.winsize::ws_col);
        }
       printNextScreen(numStr,w, lines);
           
         ch=getch();
         
       while(ch!='q')
      {
        if (ch==32)
        {
          numStr--;
          printNextScreen(numStr,w,lines);  
        }
       
        if(ch=='\n')
           printNextLine(lines,numStr);
               
        if (numStr>=lines.size())
            break;
               
        ch=getch();
      }
       
    return 0;
}
 
void cutString (std::vector<std::string>& lines,std::string nextString,int cutWid)
{        
    if(nextString.size()<=cutWid)
       lines.push_back(nextString);
    else
    {
        size_t count=(nextString.size()/cutWid)+1;
           
        for(size_t i=0;i<count;i++)
        {
            lines.push_back(nextString.substr(i*cutWid,cutWid));
        }
    }
}
 
void printNextScreen(int& numStr,struct winsize w,std::vector<std::string>& lines)
{
    for (int i = numStr; i  <  numStr + w.winsize::ws_row-1; i++)
    {
        if (i>=lines.size())
            break;
        else
            std::cout << lines[i]<< std::endl;
    }
   
    numStr += w.winsize::ws_row;
}
 
void printNextLine(std::vector<std::string>& lines,int& numStr)
{
    for (int i=numStr;i<numStr+1;i++){
          if (i>=lines.size())
            break;
        else
            std::cout << lines[i]<< std::endl;
    }
   numStr++;
}
 
int getch()
{
    int ch;
 
    struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
 
    return ch;
}
 
void helpNote()
{
   
    std::cout<<"Help note: "<<END;
    std::cout<<"\t\t\t1)Using a program correctly"<<END;
    std::cout<<"\t\t\t./more filename.txt"<<END;
    std::cout<<"\t\t\t2)To ask for help"<<END;
    std::cout<<"\t\t\t./more -h"<<END;
}
