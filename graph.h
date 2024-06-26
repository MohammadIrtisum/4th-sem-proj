#include <bits/stdc++.h>
#include <graphics.h>
//#include "ui.h"
//#include "function.h"

using namespace std;

vector<pair<int,int>> adj[100];
#define pb push_back
map<string,int> mp;
map<int,string> int2s;
int sz;
vector<string> keys;
vector<pair<int,int>> coordinates; // To store coordinates of stations
char name1[200] = "";
void graph_function();

void addEdge(string a, string b, int dis) {
    int x = mp[a];
    int y = mp[b];
    adj[x].pb({y, dis});
    adj[y].pb({x, dis});
}

void Create_Metro_map() {
    //keys.pb("Bus Station");
    keys.pb("Main Gate");
    keys.pb("Library");
    keys.pb("Mosque");
    //keys.pb("Central Field");
    //keys.pb("LAW Faculty");
    keys.pb("CSE Faculty");
    keys.pb("ACAD");
    keys.pb("BBA Faculty");
    keys.pb("EEE Faculty");
    keys.pb("CCE Faculty");
    keys.pb("Extension Building");

    for (int i = 0; i < keys.size(); i++) {
        mp[keys[i]] = i;
        int2s[i] = keys[i];
    }
    sz = keys.size();

    // Define coordinates for each station (x, y)
    coordinates = {{100, 100}, {200, 100}, {300, 100}, {400, 100}, {500, 100}, {600, 100},
                   {100, 200}, {200, 200}, {300, 200}, {400, 200}, {500, 200}, {600, 200},
                   {700, 200}};

    // Walking distance in time
    //addEdge("Bus Station", "ACAD", 11);
    addEdge("Main Gate", "CSE Faculty", 6);
    addEdge("Library", "Mosque", 3);
    addEdge("Mosque", "CSE Faculty", 4);
    //addEdge("Mosque", "Central Field", 3);
    addEdge("Central Field", "Extension Building", 23);
    addEdge("LAW Faculty", "ACAD", 7);
    //addEdge("CSE Faculty", "LAW Faculty", 8);
    addEdge("ACAD", "ACAD", 0);
    addEdge("BBA Faculty", "CSE Faculty", 10);
    addEdge("EEE Faculty", "Extension Building", 8);
   // addEdge("CCE Faculty", "CSE Faculty", 11);
   // addEdge("Extension Building", "ACAD", 13);
    addEdge("Extension Building", "CSE Faculty", 15);
    addEdge("Extension Building", "CSE Faculty", 15123);
    addEdge("Extension Building", "CSE Faculty", 115);
    addEdge("Extension Building", "BBA Faculty", 9);
    addEdge("Extension Building", "Mosque", 25);
    addEdge("Extension Building", "Library", 8);
}

void displaystations() {
    int x = 100, y = 100;
    setcolor(WHITE);
    //setbkcolor(CYAN);
    //settextstyle(8, 0, 1);
    new Field(25, 50, 785, 80, CYAN,WHITE ,"Places in IIUC");
    int v = 0;
    for (int i = 0; i < keys.size(); i++) {
        string station = to_string(i + 1) + ". " + keys[i];
        char c_station[100];
        strcpy(c_station, station.c_str());
        //new Field(15, 200, 785, 230, CYAN,WHITE ,"Team Members");
        new Field(25, 80+v, 785, 110+v, CYAN,WHITE ,c_station);
        delay(1000);
        //outtextxy(x, y, c_station);
        y += 20;
        v+=30;
    }


    outtextxy(280, 400, "Press 1 to exit the window");

    // settextstyle(6, 0, 4);
    // new Field(0, 0, 800, 70, GREEN,BLACK,"About Us");
    // //settextstyle(8, 0, 1);
   
    // new Field(15, 230, 785, 260, CYAN,WHITE ,"Team Leader: Ahanaf");
    // new Field(15, 260, 785, 290, CYAN,WHITE ,"Member 1: Apan");
    // new Field(15, 290, 785, 320, CYAN,WHITE ,"Member 2: Irtisum");
}
void displaystations2() {
    int x = 100, y = 100;
    setcolor(WHITE);
    //setbkcolor(CYAN);
    //settextstyle(8, 0, 1);
    //new Field(25, 50, 785, 80, CYAN,WHITE ,"Places in IIUC");
    int v = 0;
    for (int i = 0; i < keys.size(); i++) {
        string station = to_string(i + 1) + ". " + keys[i];
        char c_station[100];
        strcpy(c_station, station.c_str());
        //new Field(15, 200, 785, 230, CYAN,WHITE ,"Team Members");
        //new Field(25, 80+v, 785, 110+v, CYAN,WHITE ,c_station);
        outtextxy(x, y, c_station);
        delay(100);
        y += 20;
    }


    // settextstyle(6, 0, 4);
    // new Field(0, 0, 800, 70, GREEN,BLACK,"About Us");
    // //settextstyle(8, 0, 1);
   
    // new Field(15, 230, 785, 260, CYAN,WHITE ,"Team Leader: Ahanaf");
    // new Field(15, 260, 785, 290, CYAN,WHITE ,"Member 1: Apan");
    // new Field(15, 290, 785, 320, CYAN,WHITE ,"Member 2: Irtisum");
}

void drawMetroMap() {
    cleardevice();
    setcolor(WHITE);

    // Draw edges
    for (int i = 0; i < sz; i++) {
        for (auto x : adj[i]) {
            int u = i;
            int v = x.first;
            if (u < v) { // To ensure each edge is drawn only once
                int x1 = coordinates[u].first;
                int y1 = coordinates[u].second;
                int x2 = coordinates[v].first;
                int y2 = coordinates[v].second;

                // Draw the line
                setcolor(LIGHTGRAY);
                line(x1, y1, x2, y2);

                // Display the distance slightly offset from the line
                char distance[10];
                sprintf(distance, "%d", x.second);
                int mid_x = (x1 + x2) / 2 + 10; // Offset to avoid overlap
                int mid_y = (y1 + y2) / 2 - 10; // Offset to avoid overlap
                setcolor(WHITE);
                outtextxy(mid_x, mid_y, distance);
            }
        }
    }

    // Draw nodes
    for (int i = 0; i < sz; i++) {
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        fillellipse(coordinates[i].first, coordinates[i].second, 10, 10);
        char c_station[100];
        strcpy(c_station, int2s[i].c_str());
        outtextxy(coordinates[i].first - 30, coordinates[i].second - 30, c_station);
    }

    outtextxy(230, 400, "Press 2 to exit the window");
}


int shortestdistance(int src,int dest){
    vector<int>dist(sz,INT_MAX);
    dist[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({src,0});
    while(!pq.empty()){
        auto x=pq.top();
        pq.pop();
        int dis=x.second;
        for(auto y:adj[x.first]){
            int vertex=y.first;
            int dis_ver=y.second;
            if(dist[vertex]>dis+dis_ver){
                dist[vertex]=dis+dis_ver;
                pq.push({vertex,dist[vertex]});
            }
        }
    }
    return dist[dest];
}





void printMessage(const char* message) {
    //settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    char tempMessage[100];
    strcpy(tempMessage, message);
    outtextxy(5, 485, tempMessage);
}

void getInput(char* input, int maxLen) {
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < maxLen - 1) { // Read until Enter key or max length is reached
        if (ch == '\b') { // Handle backspace
            if (i > 0) {
                i--;
                input[i] = '\0';
                outtextxy(50 + i * 10, 200, " "); // Clear the character from the screen
                outtextxy(50 + i * 10, 220, " ");
            }
        } else {
            input[i] = ch;
            input[i + 1] = '\0';
            outtextxy(50 + i * 10, 200, input); // Display the character
            outtextxy(50 + i * 10, 220, input);
            i++;
        }
    }
    input[i] = '\0'; // Null-terminate the string
}

void Footers()
{
    //Footer Section

    //void setfillstyle(int pattern, int color)
    setfillstyle(SOLID_FILL, CYAN);
    //void bar(int left, int top, int right, int bottom); drawing the bar
    //bar(16, 465, 783, 504);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
    setbkcolor(CYAN);
    //setcolor(BLACK);
    outtextxy(500 - textwidth("Developed By Spartan")/2, 585 - textheight("A") / 2, "Developed By Spartan");
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
}

void choice3()
{

    setbkcolor(LIGHTCYAN);
    cleardevice();

    //frame();
    Footers();


    settextstyle(6, 0, 4);
    new Field(0,0,900,80,BLACK,WHITE,"All Destination");//left,top,right,bottom

    settextstyle(8, 0, 2);//void settextstyle(int font, int direction, int font_size);
    new Field(100, 350, 350, 400, GREEN,WHITE, "ENTER Destinations");//left,top,right,bottom
    displaystations2();
    Button back(15, 525, 130, 565, BLUE, "Exit");
    Input userName;//creating input object from the ui.h
    userName.Name(350, 350,700, 400);//left,top,right,bottom
    Button submit(370,430,450,480, BLUE, "OK");



    while(true)
    {
        int tr=0;
        submit.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0))
        {
            if(userName.cursor()){ userName.getName(name1); tr=1; }
            else if(submit.cursor())
            {
                //if source and destination is provided then do something
                if(strlen(name1)==2){
                        //cout<<name[0] << ' ' << name[1] <<endl;
                        //int x = atoi(&name[0]);
                        //int y = atoi(&name[1]);
                        int x = name1[0] - '0' - 1;//0 base index
                        int y = name1[1] - '0' - 1;//0 base indexing
                        //cout<<x<<endl;
                        //cout<<y <<endl;
                        //ERROR::::: if spaces is too much the program will close unexpectedly
                        int p = shortestdistance(x, y);
                        string message ="                            NO Edge Available                                                    ";
                        if(p==INT_MAX){
                            printMessage(message.c_str());
                        }
                        else{
                            string s1 = int2s[x];
                            string s2 = int2s[y];
                            string message = "Shortest distance between " + s1 + " and " + s2 +  " is " + to_string(p) + " Minutes by Walking                ";
                            printMessage(message.c_str());

                        }
                }
            }
            else if(back.cursor()) {
                closegraph();
            }

        }
    }

}

void graph_function() {
    Create_Metro_map();
    initwindow(900, 600, "IIUC MAP");
    setbkcolor(CYAN);
    setcolor(WHITE);
    //settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);


    //outtextxy(200, 20, "****WELCOME TO THE IIUC MAP*****");

    while (true) {
        setbkcolor(CYAN);
        setcolor(WHITE);
        cleardevice();

        //new Field(16, 0, 200, 40, BLUE, WHITE, "WELCOME TO THE IIUC MAP");
        outtextxy(275, 20, "****WELCOME TO THE IIUC MAP*****");
        outtextxy(280, 400, "Press 4 to Exit the program");
        //settextstyle(8, 0, 1);
        Button actions(170, 90, 675, 140, MAGENTA, "~~LIST OF ACTIONS(Press 1,2 or 3)~~");
        Button oneee(170, 160, 675, 210, MAGENTA, "1. LIST ALL THE Destinations IN THE MAP");
        Button twooo(170, 230, 675, 280, MAGENTA, "2. SHOW THE IIUC MAP");
        Button threee(170, 300, 675, 350, MAGENTA, "3. GET SHORTEST TIME FROM A 'SOURCE' STATION TO 'DESTINATION' ");
        //Button back(15, 525, 130, 565, MAGENTA, "Press 4 to Exit");
        //outtextxy(230, 700, "Press 4 to Exit");

        //new Field(125, 370, 375, 430, BLUE, WHITE, "ENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 3): ");
        //new Field(16, 0, 200, 40, BLUE, WHITE, "WELCOME TO THE IIUC MAP");

        //outtextxy(50, 50, "~~LIST OF ACTIONS~~");
        // outtextxy(50, 80, "1. LIST ALL THE Destinations IN THE MAP");
        // outtextxy(50, 100, "2. SHOW THE IIUC MAP");
        // outtextxy(50, 120, "3. GET SHORTEST TIME FROM A 'SOURCE' STATION TO 'DESTINATION' ");
        // outtextxy(50, 180, "ENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 3): ");

        // Button game1(125, 90, 375, 140, MAGENTA, "Game 1");
        // Button game2(425, 90, 675, 140, BLUE, "Game 2");
        // Button game3(125, 160, 375, 210, MAGENTA, "Game 3");

        char choice = getch();
        cleardevice();
        if (choice == '1') {
            displaystations();
        } else if (choice == '2') {
            drawMetroMap();
        } else if (choice == '3') {
            choice3();
            // cout<<"Enter the serial no. of Source and Destination"<<endl;
            // displaystations();
            // int x,y;
            // cin>>x>>y;
            // x--;
            // y--;
            // int p=shortestdistance(x,y);
            // cout<<"Shortest distance between source and destination is "<<p<<" Minutes by Walking\n";

            // printMessage("Enter the serial no. of Source and Destination");
            // displaystations();
            // int x, y;
            // char input[10];
            // outtextxy(50, 800, "Source: ");
            // getInput(input, 10);
            // x = atoi(input) - 1;
            // outtextxy(50, 820, "Destination: ");
            // getInput(input, 10);
            // y = atoi(input) - 1;
            // vector<int> path;
            // int p = shortestdistance(x, y, path);
            // cleardevice();
            // string message = "Shortest distance between source and destination is " + to_string(p) + " Minutes by Walking";
            // printMessage(message.c_str());
        }
        else if(choice=='4') {
            closegraph();
        }
        getch();
    }

    //closegraph();
    //return 0;
}
