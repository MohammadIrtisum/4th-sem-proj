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

void Create_IIUC_map() {
    keys.pb("Main Gate");
    keys.pb("Library");
    keys.pb("Mosque");
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
    // coordinates = {{100, 100}, {200, 100}, {300, 100}, {400, 100}, {500, 100}, {600, 100},
    //                {100, 200}, {200, 200}, {300, 200}, {400, 200}, {500, 200}, {600, 200},
    //                {700, 200}};

    // coordinates = {{100, 100}, {250, 50}, {400, 100}, {550, 100}, {700, 100}, {850, 100},
    //            {100, 250}, {250, 250}, {400, 250}, {550, 250}, {700, 250}, {850, 250},
    //            {1000, 250}};

    coordinates = {{100, 100}, {250, 50}, {400, 100}, {550, 50}, {700, 100}, {850, 50},
               {100, 250}, {250, 200}, {400, 250}, {550, 200}, {700, 250}, {850, 200},
               {1000, 250}};
               

    addEdge("Main Gate", "CSE Faculty", 6);
    addEdge("Library", "Mosque", 3);
    addEdge("Mosque", "CSE Faculty", 4);
    addEdge("Central Field", "Extension Building", 23);
    addEdge("LAW Faculty", "ACAD", 7);
    addEdge("ACAD", "ACAD", 0);
    addEdge("BBA Faculty", "CSE Faculty", 10);
    addEdge("EEE Faculty", "Extension Building", 8);
    addEdge("Extension Building", "CSE Faculty", 15);
    addEdge("Extension Building", "BBA Faculty", 9);
    addEdge("Extension Building", "Mosque", 25);
    addEdge("Extension Building", "Library", 8);
}

void displaystations() {
    int x = 100, y = 100;
    setcolor(WHITE);
    new Field(25, 50, 785, 80, CYAN,WHITE ,"Places in IIUC");
    int v = 0;
    for (int i = 0; i < keys.size(); i++) {
        string station = to_string(i + 1) + ". " + keys[i];
        char c_station[100];
        strcpy(c_station, station.c_str());
        new Field(25, 80+v, 785, 110+v, CYAN,WHITE ,c_station);
        delay(500);
        y += 20;
        v+=30;
    }
    outtextxy(280, 400, "Press 1 to exit the window");
}

void displaystations2() {
    int x = 100, y = 100;
    setcolor(WHITE);
    int v = 0;
    for (int i = 0; i < keys.size(); i++) {
        string station = to_string(i + 1) + ". " + keys[i];
        char c_station[100];
        strcpy(c_station, station.c_str());
        outtextxy(x, y, c_station);
        delay(100);
        y += 20;
    }
}

void drawIIUCMap() {
    cleardevice();
    setcolor(WHITE);

    for (int i = 0; i < sz; i++) {
        for (auto x : adj[i]) {
            int u = i;
            int v = x.first;
            if (u < v) {
                int x1 = coordinates[u].first;
                int y1 = coordinates[u].second;
                int x2 = coordinates[v].first;
                int y2 = coordinates[v].second;

                setcolor(LIGHTGRAY);
                line(x1, y1, x2, y2);

                char distance[10];
                sprintf(distance, "%d", x.second);
                int mid_x = (x1 + x2) / 2 + 10;
                int mid_y = (y1 + y2) / 2 - 10;
                setcolor(WHITE);
                outtextxy(mid_x, mid_y, distance);
            }
        }
    }

    for (int i = 0; i < sz; i++) {
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        fillellipse(coordinates[i].first, coordinates[i].second, 10, 10);
        char c_station[100];
        strcpy(c_station, int2s[i].c_str());
        outtextxy(coordinates[i].first - 30, coordinates[i].second - 30, c_station);
    }
    //outtextxy(230, 400, "Press 2 to exit the window");
}

int shortestdistance(int src,int dest, vector<int>&a){
    vector<int>dist(sz,INT_MAX);
    bool visi[100] = {};
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
                if(visi[dis_ver]==0) a.push_back(dis_ver), visi[dis_ver] = 1;
                dist[vertex]=dis+dis_ver;
                pq.push({vertex,dist[vertex]});
            }
        }
    }
    return dist[dest];
}

void printMessage(const char* message) {
    char tempMessage[100];
    strcpy(tempMessage, message);
    outtextxy(5, 485, tempMessage);
}

void getInput(char* input, int maxLen) {
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r' && i < maxLen - 1) {
        if (ch == '\b') {
            if (i > 0) {
                i--;
                input[i] = '\0';
                outtextxy(50 + i * 10, 200, " ");
                outtextxy(50 + i * 10, 220, " ");
            }
        } else {
            input[i] = ch;
            input[i + 1] = '\0';
            outtextxy(50 + i * 10, 200, input);
            outtextxy(50 + i * 10, 220, input);
            i++;
        }
    }
    input[i] = '\0';
}

void Footers() {
    setfillstyle(SOLID_FILL, CYAN);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
    setbkcolor(CYAN);
    outtextxy(500 - textwidth("Developed By Spartan")/2, 585 - textheight("A") / 2, "Developed By Spartan");
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 3);
}

void choice3() {
    setbkcolor(LIGHTCYAN);
    cleardevice();
    Footers();
    settextstyle(6, 0, 4);
    new Field(0,0,900,80,BLACK,WHITE,"All Destination");
    settextstyle(8, 0, 2);
    new Field(100, 350, 350, 400, GREEN,WHITE, "ENTER Destinations");
    displaystations2();
    Button back(15, 525, 130, 565, BLUE, "Exit");
    Input userName;
    userName.Name(350, 350,700, 400);
    Button submit(370,430,450,480, BLUE, "OK");

    while(true) {
        int tr=0;
        submit.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0)) {
            if(userName.cursor()){ userName.getName(name1); tr=1; }
            else if(submit.cursor()) {
                if(strlen(name1)==3){
                    int x = name1[0] - '0' - 1;
                    int y = name1[2] - '0' - 1;
                    vector<int>a;
                    a.push_back(x);
                    int p = shortestdistance(x, y,a);

                    string message ="                            NO Edge Available                                                    ";
                    if(p==INT_MAX){
                        printMessage(message.c_str());
                    }
                    else{
                        a.push_back(y);
                        for(auto k: a)cout<< int2s[k] <<  "=>";
                        cout<<endl;
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



void visualizeShortestPath(int src, int dest) {
    // Initialize new window
    initwindow(900, 600, "Shortest Path Visualization");

    // Draw IIUC map initially
    drawIIUCMap();

    // Convert node indices to graphical coordinates
    int x1 = coordinates[src].first;
    int y1 = coordinates[src].second;
    int x2 = coordinates[dest].first;
    int y2 = coordinates[dest].second;

    // Visualize starting and ending nodes with larger circles
    setcolor(GREEN);
    circle(x1, y1, 20); // Green circle for start
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(x1, y1, GREEN);
    
    setcolor(CYAN);
    circle(x2, y2, 20); // Cyan circle for end
    setfillstyle(SOLID_FILL, CYAN);
    floodfill(x2, y2, CYAN);

    // Implement Dijkstra's algorithm to find the shortest path
    vector<int> dist(sz, INT_MAX);
    vector<int> prev(sz, -1);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }


    // Reconstruct the path
    vector<int> path;
    for (int at = dest; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    if (path.size() == 1 && path[0] != src) {
        cout<< "No path found." <<endl;
        //outtextxy(230, 570, "No path found.");
    } else {
        // Visualize the path on the map
        setcolor(YELLOW);
        for (int i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            for (int j = -2; j <= 2; ++j) {
                    line(coordinates[u].first + j, coordinates[u].second + j, coordinates[v].first + j, coordinates[v].second + j);
            }
            //line(coordinates[u].first, coordinates[u].second, coordinates[v].first, coordinates[v].second);
            delay(2000); // delay for visualization speed
        }
    }

    outtextxy(230, 570, "Press any key to continue...");
    getch();
    closegraph();
}


void choice4() {
    setbkcolor(LIGHTCYAN);
    cleardevice();
    Footers();
    settextstyle(6, 0, 4);
    new Field(0,0,900,80,BLACK,WHITE,"All Destination");
    settextstyle(8, 0, 2);
    new Field(100, 350, 350, 400, GREEN,WHITE, "ENTER Destinations");
    displaystations2();
    Button back(15, 525, 130, 565, BLUE, "Exit");
    Input userName;
    userName.Name(350, 350,700, 400);
    Button submit(370,430,450,480, BLUE, "OK");

    while(true) {
        int tr=0;
        submit.hover(GREEN);
        if(GetAsyncKeyState(VK_LBUTTON) & (0x8000 != 0)) {
            if(userName.cursor()){ userName.getName(name1); tr=1; }
            else if(submit.cursor()) {
                if(strlen(name1)==3){
                    int x = name1[0] - '0' - 1;
                    int y = name1[2] - '0' - 1;
                    visualizeShortestPath(x,y);
                }
            }
            else if(back.cursor()) {
                closegraph();
            }
        }
    }
}









void graph_function() {
    Create_IIUC_map();
    initwindow(900, 600, "IIUC MAP");
    setbkcolor(CYAN);
    setcolor(WHITE);

    while (true) {
        setbkcolor(CYAN);
        setcolor(WHITE);
        cleardevice();
        outtextxy(275, 20, "****WELCOME TO THE IIUC MAP*****");
        outtextxy(280, 400, "Press 4 to Exit the program");
        Button actions(170, 90, 675, 140, MAGENTA, "~~LIST OF ACTIONS(Press 1,2,3 or 4)~~");
        Button oneee(170, 160, 675, 210, MAGENTA, "1. LIST ALL THE Destinations IN THE MAP");
        Button twooo(170, 230, 675, 280, MAGENTA, "2. SHOW THE IIUC MAP");
        Button threee(170, 300, 675, 350, MAGENTA, "3. GET SHORTEST TIME FROM A 'SOURCE' STATION TO 'DESTINATION'");
        Button fourr(170, 370, 675, 420, MAGENTA, "4. Visualization");

        char choice = getch();
        cleardevice();
        if (choice == '1') {
            displaystations();
        } else if (choice == '2') {
            drawIIUCMap();
        } else if (choice == '3') {
            choice3();
        } else if (choice == '4') {
            choice4();
            //visualizeShortestPath(4,5);
        } else if(choice=='4') {
            closegraph();
        }
        getch();
    }
}
