#include <iostream>
#include "E101.h"

using namespace std;

// Phase functions
void phase0();					//Inlitialization
void phase1();					//Open Door
void phase2();					//Follow Line
void phase3();					//Maze
void phase4();					//Find pillars and ball
void phase5();					//Victory RITUAL

// Motor functions
void stopadjust(int adjustment); // Adjust with small left and right movement   
void goforward(int adjustment); // Go forward with left and right adjustment    
void goforwardfullspeed(); // Go forward with full speed NO ADJUSTMENT
void gobackward();  // Go backward NO ADJUSTMENT
void turnright();  // Turn right NO ADJUSTMENT
void turnleft();  // Turn left NO ADJUSTMENT
void turnleft360();
void turnright360();
void stopmoving();  // Stop moving
void goforwardmaze(int adjustment); //maze forward


// Door functions
void opendoor();

// Camera functions
void display_screen(int thr); // use only when testing for the int put 10 displays pic of camera on terminal
void lookdown(); // Move camera to look down
void lookup(); // Move camera to look up
int findline(); // Find the BLACK line and return the offset
bool findColor(int index, int compareIndex1, int compareIndex2); // Find if target color is prominant
int findColorEdges(int targetIndex, int compare1Index, int compare2Index); // Find edges of a color
int findColorRow(int targetIndex, int compare1Index, int compare2Index); // supporter method for finding edges
int getColorArea(int targetIndex, int compare1, int compare2);

// Maze functions
int findPosition(int rowStart, int rowEnd, int colStart, int colEnd);
int leftCheck(); // Checks if there are atleast 20 black pixels in the left bottom side of the image in a 20x20 square
int rightCheck(); // Checks if there are atleast 20 black pixels in the right bottom side of the image in a 20x20 square
int topCheck(); // Checks if there are atleast 100 black pixels in the top side of the image in a 240x20 rectangle (actually checks bottom lol)
bool xCheck();
void becomeStraight(); // Stops and becomes straight




////////////////////VARIABLES//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int margin = 5; //A Margin
static int colormargin = 60; // error margins for black
static int colcompare = 100; // color comparison value
static int colcompare2 = 60;
static int colcompare3 = 70;
static int linerow = 239; // row to check for edges for line following
static double Kp = 0.07; //min 0.05 kp for line following
static double Kp2 = 0.07;

static int speed1 = 5; // speed for line following normal movements
static int speed2 = 12; // speed for full speed used to cross the door asap
static int speed3 = 4; // speed for the maze
static int adj = 0;
static int msleep = 100; //sleep time for motor steps

 //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE.
static int m1 = 1;       // right motor //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.
static int m2 = 5;       // left motor //DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.
static int s0 = 48;      // stop speed //DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.
static int s1 = s0-speed1+adj; //Normal speed makes left motor go forward and right motor go backward  //DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE. 
static int s2 = s0+speed1; //Normal speed makes left motor go backward and right motor go forward //DO NOT TOUCH OR CHANGE.//DO NOT TOUCH OR CHANGE.
static int s3 = s0-speed3+adj;
static int s4 = s0+speed3;
static int fs1 = s0-speed2+adj; // full speed makes left motor go forward and right motor go backward //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE.
static int fs2 = s0+speed2; // full speed makes left motor go backward and right motor go forward //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE.
 //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE. //DO NOT TOUCH OR CHANGE.

char server_addr[15] = "130.195.3.53"; // ipadress for the door
int port = 1024;                       // port for the door
char magicword[24] = "Please";         // magic word for the door
char message[24];

static bool status = true; // running status to make infinite loops that can be broken

static int doorsleep = 3000; // time to sleep after opening the door

////////////////////MAIN FUNCTION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int err = init(0);
    cout << "Init Error Code: " << err << endl;
    open_screen_stream();
    //phase0(); // we dont use this anymore just keep the car behind the gate straight
    phase1();
    phase2();
    phase3();
    phase4();
    //phase5();

    close_screen_stream();
    return 0;
}

////////////////////THE PHASES////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Phase 0 Initilize!
void phase0()
{
    cout << "Starting Phase 0..." << endl;
    sleep1(500);
    lookdown(); // Move camera to look down
    
    while(status){
    int position = findline();
    if(abs(position) <= margin)
    {
    stopmoving();
    break;
    }
    else if(position == 9999)
    {gobackward();}
    else{
    int adjustment = (Kp2 * position);  //check the line below and straighten
    stopadjust(adjustment);
    }
    }

    stopmoving();
}

// Phase 1 the Door!
void phase1()
{
    cout << "Starting Phase 1..." << endl;
    sleep1(500);
    lookdown();
    opendoor();  // Open the door
    sleep1(1000); // Wait for the door to open
    goforwardfullspeed(); // Go forward before the door closes
    sleep1(doorsleep);
    stopmoving();
}

// Phase 2 follow the Line!
void phase2()
{
    cout << "Starting Phase 2..." << endl;
    sleep1(500);

    while(!findColor(0, 1, 2)){  // Untill Red is found keep moving forward while maintaining balance
        int position = findline();
        if(position == 9999)
        {gobackward();}
        else{
        int adjustment = (Kp * position);
        goforward(adjustment);
        }
    }

    stopmoving();
}

// Phase 3 the Maze!
void phase3() {
    cout << "Starting Phase 3..." << endl;
    sleep1(500);
    goforwardmaze(0); // Move past red line
    sleep1(4000);
    stopmoving();

    int backwardCount = 0;

    while (!findColor(0, 1, 2)) {  // Until red is found
        int top = topCheck();
        int left = leftCheck();
        int right = rightCheck();
        bool xSeen = xCheck();

        //cout << "top=" << top << " left=" << left << " right=" << right << endl;

        bool topSeen = abs(top) <= margin;
        bool leftSeen = abs(left) <= margin;
        bool rightSeen = abs(right) <= margin;

        // ==========JUNCTION & CORNER LOGIC ==========
        if (!topSeen || xSeen) {
            // LEFT + RIGHT junction (T we just turn left)
            if (leftSeen && rightSeen && !topSeen && !xSeen) {
                cout << "JUNCTION T TURNING LEFT" << endl;
                while (abs(topCheck()) >= margin) {
                    turnleft();
                }
            }

            // LEFT + RIGHT junction (X we just turn left)
            else if (xSeen) {
                cout << "JUNCTION X TURNING LEFT" << endl;
                //goforward(0);
                //sleep1(1000);
                turnleft();
                sleep1(1000);
                while (abs(topCheck()) >= margin) {
                    turnleft();
                }
            }
            // LEFT CORNER (only left seen, top and right not seen)
            else if (leftSeen && !rightSeen && !topSeen && !xSeen) {
                cout << "LEFT CORNER TURNING LEFT" << endl;
                while (abs(topCheck()) >= margin) {
                    turnleft();
                }
            }
            // RIGHT CORNER (only right seen, top and left not seen)
            else if (rightSeen && !leftSeen && !topSeen && !xSeen) {
                cout << "RIGHT CORNER TURNING RIGHT" << endl;
                while (abs(topCheck()) >= margin) {
                    turnright();
                }
            }
        }

        // ========== LINE FOLLOWING ==========
        int position = findline();
        if (position == 9999) {
            backwardCount++;
            if (backwardCount >= 8) {
                cout << "DEAD END TURNING LEFT" << endl;
                while (abs(topCheck()) >= margin) {
                    turnleft360();
                }
                backwardCount = 0;  // Reset if line is found
            } else {
                gobackward();
            }
        } else {
            int adjustment = Kp * position;
            goforwardmaze(adjustment);
        }
    }

    stopmoving();
}



// Phase 4: Seek and Approach Red, Green, and Blue Objects and fine and hit the ball
void phase4()
{
    cout << "Starting Phase 4..." << endl;
    sleep1(500);
    lookup(); // Move camera to look up
    int totalpixels = 0;

    while (!findColor(0, 1, 2)) { // Until red is found
        cout << "LOOKING FOR RED" << endl;
        turnright360(); // Turn right to find red
    }
    stopmoving(); // Stop moving when red is found
    totalpixels = getColorArea(0, 1, 2);
        cout << "RED FOUND" << endl;
    while(totalpixels <= 20000){ // Keep moving forward until close enought to red
        cout << "GOING CLOSE TO RED" << endl;
            totalpixels = getColorArea(0, 1, 2);
            int position = findColorEdges(0, 1, 2);
            int adjustment = (Kp2 * position);
            goforward(adjustment);
    }
    while (!findColor(1, 0, 2)) { // Until green is found  
        cout << "LOOKING FOR GREEN" << endl;
        turnleft360(); // Turn left to find green
    }
    stopmoving(); // Stop moving when green is found
    totalpixels = getColorArea(1, 0, 2);
        cout << "GREEN FOUND" << endl;
    while(totalpixels <= 22000){ // Keep moving forward until close enought to green
        cout << "GOING CLOSE TO GREEN" << endl;
            totalpixels = getColorArea(1, 0, 2);
            int position = findColorEdges(1, 0, 2);
            int adjustment = (Kp2 * position);
            goforward(adjustment);
    }
    stopmoving();
    while (!findColor(2, 0, 1)) { // Until blue is found
        cout << "LOOKING FOR BLUE" << endl;
        turnright360(); // Turn right to find blue
    }
    stopmoving(); // Stop moving when blue is found
    totalpixels = getColorArea(2, 0, 1);
        cout << "BLUE FOUND" << endl;
    while(totalpixels <= 15000){ // Keep moving forward until close enought to blue
        cout << "GOING CLOSE TO BLUE" << endl;
            totalpixels = getColorArea(2, 0, 1);
            int position = findColorEdges(2, 0, 1);
            int adjustment = (Kp2 * position);
            goforward(adjustment);
    }
    stopmoving(); 
    while (!findColor(0, 1, 2)) { // Until red is found
        cout << "LOOKING FOR BALL" << endl;
        turnleft360(); // Turn left to find red
    }
    stopmoving(); // Stop moving when red is found
    totalpixels = getColorArea(0, 1, 2);
        cout << "BALL FOUND" << endl;
    while(totalpixels <= 40000){ // Keep moving forward till ball can be hit with tail.
        cout << "GOING CLOSE TO BALL" << endl;
        totalpixels = getColorArea(0, 1, 2);
        int position = findColorEdges(0, 1, 2);
        int adjustment = (Kp2 * position);
        goforward(adjustment);
    }
    stopmoving(); // Stop moving when close to tail
    turnleft360();
    sleep1(4000);
    stopmoving();
}



// Phase 5 victory Ritual!
void phase5()
{
  cout << "Starting Phase 5..." << endl;
  sleep1(500);
  gobackward(); // Go backward
  sleep1(2000); // Wait for 2 second
  stopmoving(); // Stop moving
  turnright(); // Turn right
  lookup(); // Move camera to look up
  lookdown(); // Move camera to look down
  stopmoving(); // Stop moving
  lookup(); // Move camera to look up
  lookdown(); // Move camera to look down
  turnleft(); // Turn left
  lookdown(); // Move camera to look down
  lookup(); // Move camera to look up
  stopmoving(); // Stop moving
  lookdown(); // Move camera to look down
  lookup(); // Move camera to look up
  gobackward(); // Go backward
  sleep1(2000); // Wait for 2 second
  turnright(); // Turn right
  sleep1(2000); // Wait for 2 second
  turnleft(); // Turn left
  sleep1(2000); // Wait for 2 second
  stopmoving(); // Stop moving
}

////////////////////MOTOR FUNCTIONS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Adjust with small left and right movement
void stopadjust(int adjustment)
{
    set_motors(m1, s0 + adjustment);
    set_motors(m2, (s0 + 1) + adjustment);
    hardware_exchange();
}

// Go forward with left and right adjustment
void goforward(int adjustment)
{
    set_motors(m1, s1 + adjustment);
    set_motors(m2, s2 + adjustment);
    hardware_exchange();
}

// Go forward with full speed NO ADJUSTMENT
void goforwardfullspeed()
{
    set_motors(m1, fs1);
    set_motors(m2, fs2);
    hardware_exchange();
}


// Go backward with NO ADJUSTMENT
void gobackward()
{
    set_motors(m2, s1);
    set_motors(m1, s2);
    hardware_exchange();
}

// Turn right NO ADJUSTMENT
void turnright()
{
    set_motors(m1, s0);
    set_motors(m2, s4);
    hardware_exchange();
    //sleep1(msleep);
    //stopmoving();
}

// Turn left NO ADJUSTMENT but steps
void turnleft()
{
    set_motors(m1, s3);
    set_motors(m2, s0);
    hardware_exchange();
    //sleep1(msleep);
    //stopmoving();
}

// Turn right 360
void turnright360()
{
    set_motors(m1, s4);
    set_motors(m2, s4);
    hardware_exchange();
    //sleep1(msleep);
    //stopmoving();
}

// Turn left 360
void turnleft360()
{
    set_motors(m1, s3);
    set_motors(m2, s3);
    hardware_exchange();
    //sleep1(msleep);
    //stopmoving();
}

// Stop moving
void stopmoving()
{
    set_motors(m1, s0);
    set_motors(m2, s0);
    hardware_exchange();
}

// Go forward with left and right adjustment for the maze
void goforwardmaze(int adjustment)
{
    set_motors(m1, s3 + adjustment);
    set_motors(m2, s4 + adjustment);
    hardware_exchange();
}

////////////////////DOOR FUNCTIONS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Open Door
void opendoor()
{
    connect_to_server(server_addr, port);
    send_to_server(magicword);
    receive_from_server(message);
    send_to_server(message);
}

////////////////////CAMERA FUNCTIONS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_screen(int thr){ //use only when testing for the int put 60 displays pic of camera on terminal
    take_picture();
    for (int row = 0 ; row < 240; row = row + 5){
        for ( int col = 0 ; col < 320; col = col + 5){
            //printf("\033[48;2;%d;%d;%dm ", get_pixel(row,col,0),get_pixel(row,col,1),get_pixel(row,col,2));
            std::cout<< ((int)get_pixel(row,col,3) < thr );
        }
        printf("\033[0m");
        std::cout<<std::endl;
    }
    //update_screen();
}

// Makes camera look down
void lookdown()
{
    set_motors(3,31);
    hardware_exchange();
    sleep1(1000);
    set_motors(3,48);
    hardware_exchange();
    sleep1(1000);
    set_motors(3,61);
    hardware_exchange();
}

// Makes camera look up
void lookup()
{
    set_motors(3,61);
    hardware_exchange();
    sleep1(1000);
    set_motors(3,48);
    hardware_exchange();
    sleep1(1000);
    set_motors(3,31);
    hardware_exchange();
}

int findline()
{
    take_picture();
    int row = linerow;

    int blackCount = 0;
    int blackPositionSum = 0;

    for (int col = 0; col < 320; col++)
    {
        int brightness = get_pixel(row, col, 3);
        if (brightness < colormargin)
        {
            blackCount++;
            blackPositionSum += (col - 160);
        }
    }
    int position = 9999;

    if (blackCount > 5){
        position = blackPositionSum/blackCount;
    }
    return position;
}

// Find if target color is prominant
bool findColor(int index, int compareIndex1, int compareIndex2){
    take_picture();
    int colorCount = 0;
    for(int row = 0; row < 240; row++){
        for(int col = 100; col < 220; col++){
            int color = get_pixel(row, col, index);
            int compare1 = get_pixel(row, col, compareIndex1);
            int compare2 = get_pixel(row, col, compareIndex2);
            
            //cout<<"red="<<color<<"green="<<compare1<<"blue="<<compare2<<endl;

            if (index == 0){
                if(color > colcompare && color > compare1 * 1.5 && color > compare2 * 1.5){
                    colorCount++;
                    if(colorCount >= 10){
                        return true;
                    }
                }
            }
            else if (index == 1){
                if(color > colcompare2 && color > compare1 * 1.5 && color > compare2 * 1.5){
                    colorCount++;
                    if(colorCount >= 10){
                        return true;
                    }
                }
            }
            else if (index == 2){
                if(color > colcompare3 && color > compare1 && color > compare2){
                    colorCount++;
                    if(colorCount >= 10){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// a supporter function t get a row value for the color for finding color edges
int findColorRow(int index, int compareIndex1, int compareIndex2){
    take_picture();
    int colorCount = 0;
    int lastRow = -1;

    for(int row = 0; row < 240; row++){
        for(int col = 0; col < 321; col++){
            int color = get_pixel(row, col, index);
            int compare1 = get_pixel(row, col, compareIndex1);
            int compare2 = get_pixel(row, col, compareIndex2);

            if (index == 0){
                if(color > colcompare && color > compare1 * 1.5 && color > compare2 * 1.5){
                    colorCount++;
                    lastRow = row;
                    if(colorCount >= 5){
                        return lastRow;
                    }
                }
            }
            else if (index == 1){
                if(color > colcompare2 && color > compare1 * 1.5 && color > compare2 * 1.5){
                    colorCount++;
                    lastRow = row;
                    if(colorCount >= 5){
                        return lastRow;
                    }
                }
            }
            else if (index == 2){
                if(color > colcompare3 && color > compare1 && color > compare2){
                    colorCount++;
                    lastRow = row;
                    if(colorCount >= 5){
                        return lastRow;
                    }
                }
            }
        }
    }

    return 0; // If not found
}


////////////////////MAZE DETECTION FUNCTIONS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int findPositionCol(int rowStart, int rowEnd, int colStart, int colEnd){
    take_picture();
    int position = 0;
    int blackCount = 0;
    int blackPositionSum = 0;
    for(int row = rowStart; row < rowEnd; row++){
        for(int col = colStart; col < colEnd; col++){
            int brightness = get_pixel(row, col, 3);
            if(brightness < colormargin){
                blackCount++;
                blackPositionSum += (col - 160);
                if(blackCount >= 5){
                    position = blackPositionSum/blackCount;
                    return position;
                }
            }
        }
    }
    return 9999;
}

int findPositionRow(int rowStart, int rowEnd, int colStart, int colEnd){
    take_picture();
    int position = 0;
    int blackCount = 0;
    int blackPositionSum = 0;
    for(int col = colStart; col < colEnd; col++){
        for(int row = rowStart; row < rowEnd; row++){
            int brightness = get_pixel(row, col, 3);
            if(brightness < colormargin){
                blackCount++;
                blackPositionSum += (row - 120);  // Offset from vertical center
                if(blackCount >= 5){
                    position = blackPositionSum / blackCount;
                    return position;
                }
            }
        }
    }
    return 9999;
}

int leftCheck(){
   return findPositionRow(0, 240, 10, 11);
}

int rightCheck(){
    return findPositionRow(0, 240, 310, 311);
}

int topCheck(){
    return findPositionCol(120, 121, 0, 320);
}

bool xCheck(){
int blackCount = 0;
bool left = false;
bool right = false;
bool middle = false;
take_picture();

for(int col = 0; col < 20; col++){
        for(int row = 200; row < 240; row++){
            int brightness = get_pixel(row, col, 3);
            if(brightness < colormargin){
                blackCount++;
                if(blackCount >= 20){
                    left = true;
                }
            }
        }
    }

for(int col = 300; col < 320; col++){
        for(int row = 200; row < 240; row++){
            int brightness = get_pixel(row, col, 3);
            if(brightness < colormargin){
                blackCount++;
                if(blackCount >= 20){
                    right = true;
                }
            }
        }
    }

for(int col = 150; col < 170; col++){
        for(int row = 200; row < 240; row++){
            int brightness = get_pixel(row, col, 3);
            if(brightness < colormargin){
                blackCount++;
                if(blackCount >= 10){
                    middle = true;
                }
            }
        }
    }

if(left&&right&&middle){return true;}
else{return false;}

}

////////////////////PHASE 4 FUNCTIONS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Find color edges
int findColorEdges(int targetIndex, int compare1Index, int compare2Index) {
    take_picture();

    int count = 0;
    int positionSum = 0;
    int row = findColorRow(targetIndex, compare1Index, compare2Index); // Row to check for edges
    for (int col = 0; col <= 319; col++) {
        int target = get_pixel(row, col, targetIndex);
        int c1 = get_pixel(row, col, compare1Index);
        int c2 = get_pixel(row, col, compare2Index);

        // Check if the target color is significantly stronger
        if (targetIndex == 0){
            if(target > colcompare && target > c1 * 1.5 && target > c2 * 1.5) {
                count++;
                positionSum += (col - 160); // Offset from image center
            }
        }
        else if (targetIndex == 1){
            if(target > colcompare2 && target > c1 * 1.5 && target > c2 * 1.5) {
                count++;
                positionSum += (col - 160); // Offset from image center
            }
        }
        else if (targetIndex == 2){
            if(target > colcompare3 && target > c1 && target > c2) {
                count++;
                positionSum += (col - 160); // Offset from image center
            }
        }
    
}

    int position = 0; // Default if no target color found

    if (count > 5) {
        position = positionSum / count;
    }

    return position;
}

int getColorArea(int targetIndex, int compare1, int compare2){
    take_picture();
    int count = 0;

    for (int row = 0; row <= 239; row++) {
        for (int col = 0; col <= 319; col++) {
            int target = get_pixel(row, col, targetIndex);
            int c1 = get_pixel(row, col, compare1);
            int c2 = get_pixel(row, col, compare2);

            // Check if the target color is significantly stronger
            if (targetIndex == 0){
                if(target > colcompare && target > c1 * 1.5 && target > c2 * 1.5) {
                    count++;
                }
            }
            else if (targetIndex == 1){
                if(target > colcompare2 && target > c1 * 1.5 && target > c2 * 1.5) {
                    count++;
                }
            }
            else if (targetIndex == 2){
                if(target > colcompare3 && target > c1 && target > c2) {
                    count++;
                }
            }
        }
    }
    return count;
}
