#include <bits/stdc++.h>
using namespace std;
#include <graphics.h>

//for the button and field
#include "ui.h"
#include "graph.h"
//#include "leaderboard.cpp"//leaderboard


//Below are the functions that will run in the application
//function age pore likhsi bole age theke ekhane define kore disi

//easy() and easy2() are the games
void graph_function();
void Easy();
void Easy2();
//void loading();
void scoreGame();
void setTime();
void about_us();//it is the about us page
void leaderboard();//using leaderboard after declaring in the 527th line, so declaring it now, to find the leaderboard
void run_leaderboard();
void exit();
void menu();
void setTime();
void game1_start();
void game2_start();
void game3_start();
void game4_start();
void Header();
void Footer();
void storeAcc(int x);
void storeSpeed(int x,char name[]);
void storeAvg(int x);
//void LeaderBoard();




void frame()
{
    //cleardevice() is a function of graphics which clears the screen
    cleardevice();
    //Frame Start
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(0, 0, 15, 505);//For Left Side
    bar(785, 0, 800, 505);//For Right Side
    bar(15, 0, 800, 15);//For Top Side
    bar(0, 505, 800, 520);//For Bottom Side
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(16, 16, 784, 504);//For Middle rectangle
    //Frame End
}

char name[200] = "";
char cpyname[200]="";
int spd=0;
int Ac=0;


vector<string> readDataFromFile(char* fileName)
{
    vector<string>words;
    FILE *file = fopen(fileName, "r");
    char c;
    string word;
    while((c = fgetc(file)) != EOF)
    {
        if(c == ' ' || c == '\n')
        {
            words.push_back(word);
            word = "";
        }
        else word.push_back(c);
    }
    fclose(file);
    return words;
}


//This is the game
void startPracticing(int lavel, int time_limit)
{

    //graphics.h function
    cleardevice();
    frame();
    //creating the parameterized object of Field from ui.h
    new Field(16, 0, 200, 40, BLUE, WHITE, "Time Left");//Field(int left, int top, int right, int bottom, int bgColor, int textColor, char* title)
    new Field(200, 0, 350, 40, BLUE, WHITE, "Correct");
    new Field(350, 0, 480, 40, BLUE, WHITE, "Wrong");
    new Field(480, 0, 650, 40, BLUE, WHITE, "Accuracy");
    new Field(650, 0, 783, 40, BLUE, WHITE, "Speed");
    new Field(16, 40, 200, 80, WHITE, BLACK, "00 : 00");//Initial Time

    //for generating random time; time(0) - passing 0 for generating the current time
    srand(time(0));

    new Field(200, 40, 350, 80, WHITE, BLACK, "0");
    new Field(350, 40, 480, 80, WHITE, RED, "0");
    new Field(480, 40, 650, 80, WHITE, BLACK, "100%");
    new Field(650, 40, 783, 80, WHITE, BLACK, "0");
    new Field(16, 80, 783, 150, WHITE, BLACK, "");

    clock_t begin = clock();
    double time_spent = 0.0;
    settextstyle(4, 0, 3);//void settextstyle(int font, int direction, int font_size);

    vector<string>words;
    if(lavel == 1) words = readDataFromFile("level1.txt");
    else words = readDataFromFile("level2.txt");

    int length = words.size();
    string rand_word  = words[rand() % length];

    char *crand_word = new char[50];
    strcpy(crand_word, words[rand() % length].c_str());

    new Field(16, 80, 783, 150,WHITE,BLACK,crand_word);//Print Random Word
    new Field(16, 150, 783, 200,WHITE,BLACK,"");//To Print a White Background area

    Input word(250, 149, 550, 199);
    word.setTimeLimit(time_limit);
    if(lavel == 1) word.isCharacterInput = true;
    word.hideBorder();

    setcolor(WHITE);
    rectangle(17, 150, 783, 150);//To remove bottom line of rectangular area
    setcolor(BLACK);
    rectangle(200, 150, 600, 150);//To print a line

    Button back_button(15, 350, 250, 460, MAGENTA, "BACK");
    Button re_start(501, 350, 783, 460, CYAN, "RE-START");
    //Button next(501, 350, 783, 460, MAGENTA, "NEXT LEVEL");


    char typed_word[50] = "";
    int ccnt = 0, wcnt = 0;
    bool timeOverWarning = false;
    bool isStore = false;
    int mx = 0;

    Footer();

    while(true)
    {
        re_start.hover(GREEN);
        back_button.hover(GREEN);
        //next.hover(GREEN);
        //GetAsyncKeyState checks if the left mouse button is pressed using the GetAsyncKeyState
        //GetAsyncKeyState is for seeing where the mouse is moving
        //it will check whether a key is pressed or not.
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(re_start.cursor())
            {
                startPracticing(lavel, time_limit);
                return;
            }

            /*else if(next.cursor())
            {
                if(time_limit==60)startPracticing(lavel, 120);
                if(time_limit==120)startPracticing(lavel, 300);
            }*/

            else if(back_button.cursor())
            {
                if(lavel==1)Easy();
                else if(lavel==2)Easy2();
                return;
            }

            if(spd>10)//if speed is more than store
            {

               //storeAcc(Ac);
              // storeSpeed(spd,name);
               mx = spd;
               storeAvg((Ac+spd)/2);
               spd=0;
               Ac=0;
               isStore = true;
            }

        }
        char ch;

        if(word.time_speent() <= time_limit) ch = word.getText(typed_word);
        else if(!timeOverWarning)
        {
            Input current_word_remover(250, 149, 550, 199);
            current_word_remover.hideBorder();
            setcolor(BLACK);
            rectangle(200, 150, 600, 150);//To print a line
            //new Field(16, 200, 783, 348, LIGHTGRAY, RED, "Time is Over!");
            outtextxy(300,250,"Time is Over!");
            //new Field(100, 200, 700, 300, LIGHTGRAY, RED, "Time is Over!");

            timeOverWarning = true;
            //timeOver(int I);
            storeSpeed(Ac,name);//store word
            Ac = 0;
        }

        if(ch == 9 && word.time_speent() <= time_limit)
        {
            if(strcmp(typed_word, crand_word) == 0) ccnt++;
            else wcnt++;

            int speed = (ccnt + wcnt) * 60 / word.time_speent();
            spd=speed;
            char sspeed[10];
            char speed_result[20] = "";
            sprintf(sspeed, "%d", speed);
            strcat(speed_result, sspeed);


            new Field(650, 40, 783, 80, WHITE, BLACK, speed_result);

            char temp[100];
            sprintf(temp, "%d", ccnt);
            new Field(200, 40, 350, 80, WHITE, BLACK, temp);
            sprintf(temp, "%d", wcnt);
            new Field(350, 40, 480, 80, WHITE,RED, temp);
            int acc = (ccnt * 100) / (ccnt + wcnt);

            int vvvvv = ccnt / 60;

            Ac=spd;///add now

            sprintf(temp, "%d", acc);
            strcat(temp, "%");
            new Field(480, 40, 650, 80, WHITE, BLACK, temp);

            // if(lavel == 1)
            // {
            //     for (int c = 1; c <= 22760; c++)
            //     {
            //         for(int d = 1; d <= 2276; d++)
            //         {

            //         }
            //     }
            // }
            strcpy(typed_word, "");
            settextstyle(4, 0, 3);
            rand_word  = words[rand() % length];
            strcpy(crand_word, rand_word.c_str());

            new Field(16, 80, 783, 150,WHITE,BLACK,crand_word); //To print random word
            new Field(16, 150, 783, 200,WHITE,BLACK,"");

            setcolor(WHITE);
            rectangle(16, 150, 783, 150);

            setcolor(BLACK);
            rectangle(200, 150, 600, 150);
        }

    }

}


void Header()
{
    // Header Section



    //Set text color
    setcolor(BLACK);
    //set background color
    setbkcolor(LIGHTCYAN);
    //font style
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    //void outtextxy(int x, int y, char *string); displaying text at a specific position
    outtextxy(400 - textwidth("Typing Master") / 2, 58 - textheight("A") / 2, "Typing GAME");
    setlinestyle(1, 0, 1);
    //for drawing line in header
    line(16, 84.5 + textheight("A")/ 4, 784,84.5 + textheight("A")/ 4);
    setlinestyle(0, 0, 1);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
}
void Footer()
{
    //Footer Section

    //void setfillstyle(int pattern, int color)
    setfillstyle(SOLID_FILL, CYAN);
    //void bar(int left, int top, int right, int bottom); drawing the bar
    bar(16, 465, 783, 504);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
    setbkcolor(CYAN);
    setcolor(BLACK);
    outtextxy(400 - textwidth("Developed By Spartan")/2, 485 - textheight("A") / 2, "Developed By Spartan");
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
}
void game1_start()
{
    cleardevice();
     frame();
     Header();
     Footer();
    //creating the parameterized object from ui.h
    Button easy(200, 130, 600, 230, MAGENTA, "  Start Game1");
    //Button hard(200, 250, 600, 350, MAGENTA, "  HARD");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        easy.hover(GREEN);
        //hard.hover(GREEN);
        back.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(easy.cursor()) Easy();
            else if(back.cursor())menu();
        }
    }
}


void Easy()
{
    cleardevice();
    frame();

    Footer();
    new Field(0, 0, 800, 50, MAGENTA,WHITE, "Easy Labels");
    Button char_one_mnt(200, 130, 600, 230, CYAN, "Type Characters");
    //Button char_two_mnt(200, 230, 600, 330, MAGENTA, "Label 2");
    //Button char_five_mnt(200, 330, 600, 430, CYAN, "Label 3");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        char_one_mnt.hover(RED);
        //char_two_mnt.hover(BLUE);
        //char_five_mnt.hover(RED);
        back.hover(GREEN);

        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(char_one_mnt.cursor())  startPracticing(1, 60);
            //else if(char_two_mnt.cursor()) startPracticing(1, 120);
            //else if(char_five_mnt.cursor())startPracticing(1,300);
            else if(back.cursor())game1_start();
        }
        if(kbhit()) getch();
    }
}
void about_us()
{
    setbkcolor(DARKGRAY);
    cleardevice();
    frame();
    Footer();
    settextstyle(6, 0, 4);
    new Field(0, 0, 800, 70, GREEN,BLACK,"About Us");
    settextstyle(8, 0, 1);
    new Field(15, 200, 785, 230, CYAN,WHITE ,"Team Members");
    new Field(15, 230, 785, 260, CYAN,WHITE ,"Team Leader: Ahanaf");
    new Field(15, 260, 785, 290, CYAN,WHITE ,"Member 1: Apan");
    new Field(15, 290, 785, 320, CYAN,WHITE ,"Member 2: Irtisum");
    settextstyle(8, 0, 2);
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        back.hover(GREEN);

        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(back.cursor())menu();
        }
        if(kbhit()) getch();
    }
}





void storeAcc(int x)
{
    ofstream myfile;
    myfile.open("Previous Record.txt", std::ios_base::app);

    myfile<<x<<" ";
    myfile.close();
}
int mx = 0;
void storeSpeed(int x, char chh[])
{

    ofstream myfile;
    myfile.open("RecordSpeed.txt", std::ios_base::app);

    myfile<<chh<<" "<<x <<endl;
    myfile.close();

//     //
//     ifstream file_read;
//     file_read.open("RecordSpeed.txt");
//     vector<pair<string, int>> records;
//     string line;
//     while (getline(file_read, line)){
//         istringstream iss(line);
//         string sssss;
//         int xxxxxxx;

//         // Read string and integer from each line
//         if (iss >> sssss >> xxxxxxx)
//         {
// //            records.emplace_back({sssss, xxxxxxx}); // Add pair (chh, x) to records vector
//         }
//         //records.push_back(line);
//     }

//     file_read.close();

//     //update the higest one
//     for(auto [xx,y]: records){
//         if(y==chh && xx<x){
//             xx = x;
//         }
//     }

//     //update file
//     ofstream myfile;
//     myfile.open("RecordSpeed.txt", std::ios_base::app);
//     for(auto [xx,y]: records){
//         myfile<<xx<<" "<<y <<endl;
//     }
//     myfile.close();
}

void storeAvg(int x)
{
   ofstream myfile;
    myfile.open("Avg.txt", std::ios_base::app);

    myfile<<x<<" ";
    myfile.close();
}


//#######################################################################################
//#######################################################################################
//For game 2
//Main game function for the second game



void Easy2()
{
    //loading();
    cleardevice();
    frame();
    Footer();
    new Field(0, 0, 800, 50, MAGENTA,WHITE, "Hard Lavels");


    Button word_one_mnt(200, 130, 600, 230, CYAN, "Type Word by Word");
    //Button word_two_mnt(200, 230, 600, 330, MAGENTA, "Label 2");
    //Button word_five_mnt(200, 330, 600, 430, CYAN, "Label 3");
    Button back(15, 425, 130, 465, BLUE, "BACK");

    while(true)
    {
        word_one_mnt.hover(GREEN);
        //word_two_mnt.hover(GREEN);
        //word_five_mnt.hover(GREEN);
        back.hover(GREEN);



        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(word_one_mnt.cursor())  startPracticing(2, 60);
            //else if(word_two_mnt.cursor()) startPracticing(2, 120);
            //else if(word_five_mnt.cursor()) startPracticing(2, 300);
            else if(back.cursor())game2_start();
        }
        if(kbhit()) getch();//kbhit determines if a key has been pressed or not
    }
}



void game2_start()
{
    cleardevice();
     frame();
     Header();
     Footer();
    //creating the parameterized object from ui.h
    Button easy(200, 130, 600, 230, MAGENTA, "  Start Game2");
    //Button hard(200, 250, 600, 350, MAGENTA, "  HARD");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        easy.hover(GREEN);
        //hard.hover(GREEN);
        back.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(easy.cursor()) Easy2();
            //else if(hard.cursor())Hard();
            else if(back.cursor())menu();
        }
    }
}
void exit()
{
    setbkcolor(BLACK);
    cleardevice();
    frame();
    Footer();
    new Field(0, 0, 800, 40, MAGENTA,WHITE, "WHAT YOU WANT TO DO");
    Button back(15, 425, 130, 465, BLUE, "BACK");
    Button exit(650, 425, 785, 465, BLUE, "EXIT");
    while(true)
    {
        back.hover(GREEN);

        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(back.cursor())menu();
            else if(exit.cursor())closegraph();
        }
        if(kbhit()) getch();
    }

}
void menu()
{

    setbkcolor(CYAN);
    cleardevice();
    settextstyle(6, 0, 4);
    new Field(0, 0, 800, 70, GREEN,BLACK, "MAIN MENU");

    Footer();

    ////left,top,right,bottom

     // First row buttons for games
    //Button game1(50, 90, 300, 140, MAGENTA, "Game 1");
    Button game1(125, 90, 395, 150, MAGENTA, "Game 1");
    Button game2(405, 90, 675, 150, BLUE, "Game 2");
    Button game3(125, 160, 395, 220, MAGENTA, "Game 3");
    Button game4(405, 160, 675, 220, BLUE, "Game 4");

    // sescond row buttons
    Button leader(125, 230, 395, 290, MAGENTA, "LeaderBoard");
    Button graph(405, 230, 675, 290, BLUE, "IIUC MAP");
    Button aboutMe(125, 300, 675, 360, MAGENTA, "About Us");
    //Button ext(425, 300, 675, 360, BLUE, "Exit");

    Button ext(125, 370, 675, 430, RED, "Exit");
    //Button ext(50, 370, 600, 430, RED, "Exit");
    // Button game1(50, 95, 250, 165, MAGENTA, "Game 1");
    // Button game2(300, 95, 500, 165, BLUE, "Game 2");

    // Button game3(50, 170, 250, 240, MAGENTA, "Game 3");
    // Button leader(300, 170, 500, 240, BLUE, "LeaderBoard");

    // Button aboutMe(50, 245, 250, 315, BLUE, "About Us");
    // Button ext(300, 245, 500, 315, RED, "EXIT");
    // Button game1(200, 95, 400, 165, MAGENTA, "  Game 1");
    // Button game3(200, 95, 450, 165, MAGENTA, "  Game 3");
    // //Button aboutMe(200, 175, 600, 245, BLUE, "  Game 2");
    // Button game2(200, 170, 600, 240, BLUE, "Game 2");
    // //Button game3(200, 205, 600, 265, BLUE, "Game 1(Hard)");
    // //Button game4(200, 270, 600, 330, BLUE, "Game 2(Hard)");
    // Button leader(200, 245, 600, 315, BLUE, "  LeaderBoard");
    // //Button preb(200, 250, 600, 320, BLUE, "PREVIOUS RECORDs");
    // Button aboutMe(200, 320, 600, 390, BLUE, "  About Us");
    // //Button preb(200, 250, 600, 320, BLUE, "PREVIOUS RECORDs");
    // Button ext(200, 395, 600, 465, RED, "  EXIT");

    while(true)
    {
        //hovering over menu
        game1.hover(GREEN);
        game2.hover(GREEN);
        game3.hover(GREEN);
        game4.hover(GREEN);
        leader.hover(GREEN);
        aboutMe.hover(GREEN);
        graph.hover(GREEN);
        //newsfeed.hover(GREEN);
        ext.hover(GREEN);

        //pressing the windows
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(game1.cursor()) game1_start();
            else if(game2.cursor())game2_start();
            else if(game3.cursor())game3_start();
            else if(game4.cursor())game4_start();
            //else if(newsfeed.cursor()) leaderboard();
            else if(leader.cursor()) leaderboard();
            else if(graph.cursor()) {graph_function();}
            else if(aboutMe.cursor()) about_us();
           else if(ext.cursor()) exit();
        }
    }
}


void login()
{

    setbkcolor(LIGHTCYAN);
    cleardevice();

    settextstyle(6, 0, 4);
    new Field(0,0,800,80,BLACK,WHITE,"WELCOME TO TYPING GAME");//left,top,right,bottom
    settextstyle(8, 0, 2);//void settextstyle(int font, int direction, int font_size);
    new Field(100, 350, 350, 400, GREEN,WHITE, "ENTER YOUR NAME");//left,top,right,bottom
    Input userName;//creating input object from the ui.h
    userName.Name(350, 350,700, 400);//left,top,right,bottom
    Button submit(370,430,450,480, BLUE, "OK");

    while(true)
    {
        int tr=0;
        submit.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(userName.cursor()){ userName.getName(name); tr=1; }
            else if(submit.cursor())
            {
                if(strlen(name)>0){
                    //name[0]
                    menu();
                }
            }

        }
    }

}


//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//addition
//leaderboard
void leaderboard()
{
    setbkcolor(DARKGRAY);
    cleardevice();
    //frame();
    Footer();
    // settextstyle(6, 0, 4);
    // new Field(0, 0, 800, 70, GREEN,BLACK,"Leaderboard");
    // settextstyle(8, 0, 1);

    run_leaderboard();

    // settextstyle(8, 0, 2);
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
        back.hover(GREEN);

        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(back.cursor())menu();
        }
        if(kbhit()) getch();
    }
}



//sort the leaderboard data
void bubbleSort(int scores[], string names[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                swap(scores[j], scores[j + 1]);
                swap(names[j], names[j + 1]);
            }
        }
    }
}

// Function to print the leaderboard
void printLeaderboard(const int scores[], const string names[], int size) {
    //cout << "Leaderboard:\n";
    // new Field(15, 200, 785, 230, CYAN,WHITE ,"Team Members");
    // new Field(15, 230, 785, 260, CYAN,WHITE ,"Team Leader: Ahanaf");
    // new Field(15, 260, 785, 290, CYAN,WHITE ,"Member 1: Apan");
    outtextxy(150,10,"Name");
    outtextxy(350,10,"Score");

    int v = 30;
    for (int i = 0,v=0,v1=0; i < size; i++,v+=30,v1+=50) {
        char* name = const_cast<char*>(names[i].c_str());

        string score_str = to_string(scores[i]);
        const char* score_cstr = score_str.c_str(); // const char*
        char* score = const_cast<char*>(score_cstr); // cast to char*
        //l,t,r,b
       // new Field(10, 50+v1, 785, 100, CYAN,WHITE ,score);
       setcolor(YELLOW);
        outtextxy(150,v+50,name);
        outtextxy(350,v+50,score);
        delay(1000);
        v+=20;
       // cout << names[i] << "\t" << scores[i] << "\n";
    }

    Button back(15, 425, 130, 465, BLUE, "BACK");
}


void run_leaderboard() {
    const int MAX_SIZE = 100; // Maximum number of entries
    string names[MAX_SIZE];
    int scores[MAX_SIZE];
    int numEntries = 0;

    // Read data from the file
    ifstream inFile("leaderboards.txt");
    if (!inFile) {
        cerr << "Error: Unable to open file.\n";
        //return 1;
    }

    while (numEntries < MAX_SIZE && inFile >> names[numEntries] >> scores[numEntries]) {
        numEntries++;
    }
    inFile.close();

    // Sort the leaderboard data
    bubbleSort(scores, names, numEntries);

    // Print the leaderboard
    printLeaderboard(scores, names, numEntries);

    //return 0;
}



//leaderboard finishes
//------------------------------------------------------------------------------


//#############################################################################################
//Graph

//see graph.h file




//#############################################################################################
//Game 3
using namespace chrono;

const vector<string> sentences = {
    "The quick brown fox jumps over the lazy dog.",
    "A journey begins with a single step.",
    "To be or not to be, that is the question.",
    "All that glitters is not gold.",
    "A picture is worth a thousand words."
};

string getRandomSentence() {
    srand(static_cast<unsigned int>(time(0)));
    int index = rand() % sentences.size();
    return sentences[index];
}

void displayText(const string& text, int x, int y, int color) {
    setcolor(color);
    outtextxy(x, y, const_cast<char*>(text.c_str()));
}

void game3_start(){
     cleardevice();

//     Button back(15, 425, 130, 465, BLUE, "BACK");

//    int gd = DETECT, gm;
//    initgraph(&gd, &gm, "");
//
      setbkcolor(WHITE);
//    cleardevice();

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(BLACK);

    displayText("Typing Speed Test", 200, 50, BLUE);
    displayText("You have 60 seconds to type the following sentence", 50, 100, BLACK);

    string sentence = getRandomSentence();
    displayText("Sentence:", 50, 150, BLACK);
    outtextxy(50, 200, const_cast<char*>(sentence.c_str()));

    displayText("Press any key to start typing...", 50, 250, RED);
    getch();

    cleardevice();
    displayText("Start typing:", 50, 100, BLACK);
    outtextxy(50, 150, const_cast<char*>(sentence.c_str()));

    auto start = high_resolution_clock::now();
    string userInput;
    char ch;
    int x = 50, y = 200;
    while ((ch = getch()) != 13) { // Enter key
        if (ch == 8) { // Backspace
            if (!userInput.empty()) {
                userInput.pop_back();
                setcolor(WHITE);
                outtextxy(x, y, "_"); // Erase character
                setcolor(BLACK);
                x -= textwidth("_");
            }
        } else {
            userInput.push_back(ch);
            char temp[2] = {ch, '\0'};
            outtextxy(x, y, temp);
            x += textwidth(temp);
        }
    }

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    double seconds = elapsed.count();

    int correctChars = 0;
    for (size_t i = 0; i < min(sentence.size(), userInput.size()); ++i) {
        if (sentence[i] == userInput[i]) {
            correctChars++;
        }
    }

    int wpm = (userInput.size() / 5) / (seconds / 60);
    double accuracy = (static_cast<double>(correctChars) / sentence.size()) * 100;

    cleardevice();

    displayText("Results:", 50, 100, BLUE);
    string timeStr = "Time taken: " + to_string(seconds) + " seconds";
    displayText(timeStr, 50, 150, BLACK);
    string wpmStr = "Words per minute: " + to_string(wpm);
    displayText(wpmStr, 50, 200, BLACK);
    string accuracyStr = "Accuracy: " + to_string(accuracy) + "%";
    displayText(accuracyStr, 50, 250, BLACK);
    Button back(15, 425, 130, 464, BLUE, "BACK");
    while(true)
    {
//        easy.hover(GREEN);
        //hard.hover(GREEN);
        back.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
//            if(easy.cursor()) Easy2();
            //else if(hard.cursor())Hard();
             if(back.cursor())menu();
        }
    }

//    getch();
//    closegraph();

//    return ;
}

//#############################################################################################
//Game 4

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 40
#define MAX_LIVES 2


const char *words[MAX_WORDS] =
{
    "Computer Science & Engineering", "banana", "cherry", "date", "strawberry",
    "fig", "grape", "mango", "kiwi", "lemon"
};

char currentWord[MAX_WORD_LENGTH];
char userInput[MAX_WORD_LENGTH];
int score = 0;
int lives = MAX_LIVES;
int wordX, wordY;
time_t startTime;

void getRandomWord()
{
    int index = rand() % MAX_WORDS;
    strcpy(currentWord, words[index]);
    wordX = rand() % (getmaxx() - strlen(currentWord) * 8);
    wordY = 0;  // Start from the top of the screen
}

void displays( char *text, int x, int y, int color, int font, int direction, int size)
{
    setcolor(color);
    settextstyle(font, direction, size);
    outtextxy(x, y, text);
}

void updateDisplay()
{
    cleardevice();
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    displays(scoreText, 10, 10, WHITE, DEFAULT_FONT, HORIZ_DIR, 2);

    char livesText[20];
    sprintf(livesText, "Lives: %d", lives);
    displays(livesText, getmaxx() - 150, 10, WHITE, DEFAULT_FONT, HORIZ_DIR, 2);

    displays(currentWord, wordX, wordY, YELLOW, TRIPLEX_FONT, HORIZ_DIR, 3);
    displays(userInput, 10, getmaxy() - 50, GREEN, TRIPLEX_FONT, HORIZ_DIR, 2);
}
void game4_start()
{
    //setbkcolor(YELLOW);
    cleardevice();
    //int gd = DETECT, gm;
    //initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    srand(time(NULL));
    getRandomWord();
    userInput[0] = '\0';
    startTime = time(NULL);

    while (lives > 0)
    {
        updateDisplay();

        if (kbhit())
        {
            char ch = getch();
            if (ch == '\r')    // Enter key
            {
                if (strcmp(userInput, currentWord) == 0)
                {
                    score += 10;
                    getRandomWord();
                }
                else
                {
                    lives--;
                }
                userInput[0] = '\0';
            }
            else if (ch == '\b')      // Backspace key
            {
                int len = strlen(userInput);
                if (len > 0)
                {
                    userInput[len - 1] = '\0';
                }
            }
            else if (ch >= ' ' && ch <= '~')     // Ensure valid ASCII input
            {
                int len = strlen(userInput);
                if (len < MAX_WORD_LENGTH - 1)   // Ensure there's room for the new character
                {
                    userInput[len] = ch;
                    userInput[len + 1] = '\0';
                }
            }
        }

        wordY += 5;
        if (wordY > getmaxy())
        {
            lives--;
            getRandomWord();
        }

        delay(200);
    }

    cleardevice();
    char endText[50];
    sprintf(endText, "Game Over! Final Score: %d", score);
    displays(endText, getmaxx() / 2 - strlen(endText) * 8, getmaxy() / 2, WHITE, TRIPLEX_FONT, HORIZ_DIR, 3);
    Button back(15, 425, 130, 465, BLUE, "BACK");
    while(true)
    {
       // easy.hover(GREEN);
        //hard.hover(GREEN);
        back.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            //if(easy.cursor()) Easy2();
            //else if(hard.cursor())Hard();
            if(back.cursor())menu();
        }
    }

    //getch();

    //closegraph();
//return 0;
}