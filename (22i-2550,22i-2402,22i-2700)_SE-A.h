/*                        Name : Unzila Anjum
                          Roll Number : 22i-2550
                          Section: SE-A  
-----------------------------------------------------------------------------------------------

                          Name : Eshal Omar
                          Roll Number : 22i-2402
                          Section: SE-A 
------------------------------------------------------------------------------------------------
                          Name : Hadia
                          Roll Number : 22i-2700
                          Section: SE-A  


================================================================================================

----------------------------------------- 2D CAR RACING GAME------------------------------------

================================================================================================

                        */     


#pragma once
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <chrono>
#include <sstream>
#include<string>
#include"medium.h"
#include <thread>  //song library
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

struct PlayerInfo {
    string name;
    int score;
};
//Struct for items
struct CollectedItem {
    char type;  
    int Score;
    CollectedItem* next;


    //Parametrized Constructor
    CollectedItem(char type, int Score) {
        this->type = type;
        this->Score = Score;
        next = nullptr;
    }
};

// maanaging collected item in linked list here
class CollectedItemsList {
private:
    CollectedItem* head;

public:
    //default constructor
    CollectedItemsList() {
        this->head = nullptr;
    }

    // Add item to the list
    void addItem(char type, int Score) {
        CollectedItem* newItem = new CollectedItem(type, Score);
        newItem->next = head;
        head = newItem;
    }
    void PrintItems() {
        CollectedItem* current = head;
        while (current != nullptr) {
            cout << "Item Type: " << current->type << ", Score Value: " << current->Score << endl;
            current = current->next;
        }
    }

    // Total Score of the item
    int calculateTotalScore() {
        int Total_Score = 0;
        CollectedItem* current = head;
        while (current != nullptr) {
            Total_Score += current->Score;
            current = current->next;
        }
        return Total_Score;
    }


    //destructor
    ~CollectedItemsList() {
        while (head != nullptr) {
            CollectedItem* temp = head;
            head = head->next;
            delete temp;
        }
    }
};


//class for leaderboard
class Leaderboard {
private:
    PlayerInfo* scores;  
    int capacity;        
    int size;            


    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (scores[index].score > scores[parentIndex].score) {
               //swapping for leaderboard
                PlayerInfo temp = scores[index];
                scores[index] = scores[parentIndex];
                scores[parentIndex] = temp;

                index = parentIndex;
            }
            else {
                break;
            }
        }
    }

    //void heapifyDown(int index) {
    //    while (2 * index + 1 < size) {
    //        int leftChild = 2 * index + 1;
    //        int rightChild = 2 * index + 2;
    //        int maxIndex = index;

    //        if (scores[leftChild].score > scores[maxIndex].score) {
    //            maxIndex = leftChild;
    //        }

    //        if (rightChild < size && scores[rightChild].score > scores[maxIndex].score) {
    //            maxIndex = rightChild;
    //        }

    //        if (maxIndex != index) {
    //            // Swap elements
    //            PlayerInfo temp = scores[index];
    //            scores[index] = scores[maxIndex];
    //            scores[maxIndex] = temp;

    //            index = maxIndex;
    //        }
    //        else {
    //            break;
    //        }
    //    }
    //}
    void heapifyDown(int index) {
        while (2 * index + 1 < size) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int maxIndex = index;

            if (scores[leftChild].score > scores[maxIndex].score ||
                (scores[leftChild].score == scores[maxIndex].score && leftChild < maxIndex)) {
                maxIndex = leftChild;
            }

            if (rightChild < size &&
                (scores[rightChild].score > scores[maxIndex].score ||
                    (scores[rightChild].score == scores[maxIndex].score && rightChild < maxIndex))) {
                maxIndex = rightChild;
            }

            if (maxIndex != index) {
                PlayerInfo temp = scores[index];
                scores[index] = scores[maxIndex];
                scores[maxIndex] = temp;

                index = maxIndex;
            }
            else {
                break;
            }
        }
    }


public:
    Leaderboard(int capacity) : capacity(capacity), size(10) {
        scores = new PlayerInfo[capacity];
    }

    ~Leaderboard() {
        delete[] scores;
    }

    void addPlayer(string& name, int score) {
        if (size < capacity) {
            scores[size].name = name;
            scores[size].score = score;
            heapifyUp(size);
            size++;
        }
        else if (score > scores[0].score) {
            scores[0].name = name;
            scores[0].score = score;
            heapifyDown(0);
        }
    }
    void printLeaderboard() {

        for (int i = 0; i < size; ++i) {
            if (scores[i].name != "") {
                cout << scores[i].name << ": " << scores[i].score << endl;
            }
        }
    }
};

//elements for map
const char Empty = ' ';
const char Boundary = '|';
const char Power_Up = '*';
const char Start = 'S';
const char End = 'E';
const char coin = '$';
const char Trophy = '^';
const char grenade = '@';
const char obstacle = '#';
const char Empty2 = ' ';
const char Boundary2 = '|';
const char Power_Up2 = '*';
const char Start2 = 'S';
const char End2 = 'E';
const char coin2 = '$';
const char grenade2 = '@';
const char obstacle2 = '#';
const char Empty3 = ' ';
const char Boundary3 = '|';
const char Power_Up3 = '*';
const char Start3 = 'S';
const char End3 = 'E';
const char coin3 = '$';
const char grenade3 = '@';
const char obstacle3 = '#'; 
const char SPath = '&';


struct Predecessor
{
    int prevX;
    int prevY;
};

//Nodes structure For graph
struct Node {
    int x, y;
    char type;
    CollectedItemsList collectedItems;
    Node* neighbors[4];  // Moves 


    //Default Constructor
    Node() {
        x = 0;
        y = 0;
        type = '\0';
    }

    //parametrized constructor
    Node(int x, int y, char type) {
        this->x = x;
        this->y = y;
        this->type = type;
        for (int i = 0; i < 4; ++i) {
            neighbors[i] = nullptr;
        }
    }
};
// Function to set text color
void setConsoleColor(int textColor, int bgColor) {
    int colorCode = textColor + bgColor * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

// Function to reset text color to default
void resetConsoleColor() {
    setConsoleColor(7, 0); 
}

// Class for the game
class CarGame {
private:
    int levels;
    int x_car;
    int y_car;
    int score;
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point lastDisplayedTime;
    std::chrono::high_resolution_clock::time_point endTime;

public:

    //path lenght and width
    Node CarPath[10][10];

    //default constructor
    CarGame() {
        x_car = 0;
        y_car = 0;
        score = 0;
    }


    //getters 

    int getXCar() const {
        return x_car;
    }
    Node* getCarPath() {
        return &CarPath[0][0];
    }
    int getYCar() const {
        return y_car;
    }
    int getScore() {
        return score;
    }
    void startTimer() {
        startTime = std::chrono::high_resolution_clock::now();
    }
    void stopTimer() {
        endTime = std::chrono::high_resolution_clock::now();
    }

    int getElapsedTime() {
        /*auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        return duration.count();*/

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        return elapsedSeconds;

    }
    // Initialize the game map with random elements
    void Initializemap() {
        srand(time(0));
        {
            int c = 0;

         //randomly generating elements on the grid
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    char type = Empty;
                    if ((rand() % 15 == 0) && (i != 9) && (i != 0)) {
                        type = Boundary;
                    }
                    else if ((rand() % 13 == 0) && (i != 9) && (i != 0)) {
                        type = Power_Up;
                    }
                    else if ((rand() % 25 == 0) && (i != 9) && (i != 0)) {
                        type = grenade;
                    }
                    else if ((rand() % 15 == 0) && (i != 9) && (i != 0)) {
                        type = obstacle;
                    }
                    else if ((rand() % 30 == 0) && (i != 9) && (i != 0) && (c == 0)) {
                        c++;
                        type = Trophy;
                    }
                    else if ((rand() % 10 == 0) && (i != 9) && (i != 0)) {
                        type = coin;
                    }
                    else if (i == 0 && j == 0) {
                        type = Start;
                    }
                    else if (i == 9 && j == 9) {
                        type = End;
                    }

                    CarPath[i][j] = Node(i, j, type);
                    /* if (type != End ) {
                         CarPath[i][j] = Node(i, j, type);
                     }
                     else {
                         CarPath[i][j] = Node(i, j, End);
                     }*/



                    CarPath[i][j] = Node(i, j, type);
                    //for grenade on the map
                    if (type == grenade) {
                        int grenadeX = i;
                        int grenadeY = j;
                        CarPath[grenadeX][grenadeY].type = '@';
                    }
                }


                // Connecting neighboring nodes
                for (int i = 0; i < 10; ++i) {
                    for (int j = 0; j < 10; ++j) {
                        if (i > 0) CarPath[i][j].neighbors[0] = &CarPath[i - 1][j]; // Up
                        if (i < 9) CarPath[i][j].neighbors[1] = &CarPath[i + 1][j]; // Down
                        if (j > 0) CarPath[i][j].neighbors[2] = &CarPath[i][j - 1]; // Left
                        if (j < 9) CarPath[i][j].neighbors[3] = &CarPath[i][j + 1]; // Right
                    }
                }
            }
        }
    }





    void displayElapsedTime() {
        auto currenttime = std::chrono::high_resolution_clock::now();
        auto duratio = std::chrono::duration_cast<std::chrono::seconds>(currenttime - startTime);
        int elapsedTim = duratio.count();
        setConsoleColor(0, 42);
        //if (startTime == std::chrono::high_resolution_clock::time_point{}) {
        //    // If startTime is not set, return 0 or some default value
        //    return 0;
        //    //cout << "oops";
        //}

        //auto currentTime = std::chrono::high_resolution_clock::now();
        //auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

        //// Convert elapsed time to integer
        //int elapsedSecondsInt = static_cast<int>(elapsedSeconds.count());

        cout << "\t\t\t\t\t\t\t  ";
        cout << "Time: " << elapsedTim << "s\t\t\t\t\t\t\t" << endl;
        // cout << "\t\t\t\t\t\t\t   --------- " << "\t\t\t\t\t\t\t" << endl;
        resetConsoleColor();

    }

    void displayMap() {
        system("cls");

      //  cout << "\t\t\t\t\t\t\t --------- " << "\t\t\t\t\t\t\t" << endl;

        setConsoleColor(0, 42);
        cout << "\t\t\t\t\t\t\t Score: " << getScore() << " " << endl;
        //   cout << "\t\t\t\t\t\t\t --------- " << "\t\t\t\t\t\t\t" << endl;
        resetConsoleColor();
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        int elapsedTime = duration.count();
        if (elapsedTime % 1 == 0) {
            displayElapsedTime();
        }
        //cout << endl;



        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
              
                if (CarPath[i][j].type == 'C') {
                    setConsoleColor(0, 14);
                    cout << "=";  // Car
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }
                else if (CarPath[i][j].type == Boundary) {

                    cout << '|' << ' ' << ' '; // Boundary
                }
                else if (CarPath[i][j].type == Power_Up) {
                    setConsoleColor(10, 0);
                    cout << '*' << ' ' << ' '; // Power-up
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == Trophy) {
                    setConsoleColor(13, 40);
                    cout << '^'; // Power-up
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }
                else if (CarPath[i][j].type == obstacle) {
                    setConsoleColor(8, 0);

                    cout << "#";//Obstacle

                    resetConsoleColor();
                    cout << ' ' << ' ';
                }
                else if (CarPath[i][j].type == coin) {
                    setConsoleColor(14, 0);
                    cout << '$' << ' ' << ' '; //coins
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == Start) {
                    cout << 'S' << ' ' << ' '; // Start
                }
                else if (CarPath[i][j].type == grenade) {
                    setConsoleColor(4, 0);
                    cout << "@" << ' ' << ' ';
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == End) {
                    cout << 'E' << ' ' << ' '; // End
                }
             
                else {
                    bool isRoad = false;
                    for (int k = 0; k < 4; ++k) {
                        if (CarPath[i][j].neighbors[k] != nullptr &&
                            CarPath[i][j].neighbors[k]->type == Empty) {
                            isRoad = true;
                            break;
                        }
                    }

                    if (isRoad) {

                        cout << '.' << ' ' << ' '; // Road

                    }
                    else {
                        cout << ' ' << ' ' << ' '; // Empty cell
                    }
                }
            }
            cout << endl;
        }

        // Display instructions
        cout << endl;
        cout << endl;
        setConsoleColor(0, 6);
        cout << "Instructions:" << endl;
        cout << endl;
        resetConsoleColor();
        setConsoleColor(6, 0);
        cout << "1. Use 'W' to move up" << endl;
        cout << "2. 'S' to move down" << endl;
        cout << "3. 'A' to move left" << endl;
        cout << "4. 'D' to move right." << endl;
        cout << "5. Collect power-ups ('*') to increase your score." << endl;
        cout << "6. Avoid Boundary ('|')" << endl;
        cout << "7. Avoid obstacles for negative scores ('#')" << endl;
        cout << "8. Avoid grenades ('@')" << endl;
        cout << "9. reach the 'E' to finish the game." << endl;
        cout << "10. power up(*) will multpily your score by 2" << endl;
        cout << "11. Trophy(^) will increase your score to +100" << endl;
        cout << "12. ($) coins to increase score " << endl;
        resetConsoleColor();
    }

    void saveScore() {

    }

    // Controllers  
    int moves = 0;
    int powerup = 0;
    int obstacless = 0;
    void movePlayer(char Moves, CarGame& game, string n) {

        Node* nextNode = nullptr;

        switch (Moves) {
        case 'a':
            nextNode = CarPath[x_car][y_car].neighbors[2]; // Left
            moves++;
            break;
        case 'd':
            nextNode = CarPath[x_car][y_car].neighbors[3]; // Right
            moves++;
            break;
        case 'w':
            nextNode = CarPath[x_car][y_car].neighbors[0]; // Up
            moves++;
            break;
        case 's':
            nextNode = CarPath[x_car][y_car].neighbors[1]; // Down
            moves++;
            break;
        }

        if (nextNode != nullptr && nextNode->type != Boundary) {
            char itemType = nextNode->type;

            int itemScore = 0;

            switch (itemType) {
                //for power up
            case Power_Up:
            {
                itemScore = 2; 
                score *= itemScore;
                if (score == 0) {
                    score += 25;
                }
                PlaySound(TEXT("Powerup.wav"), nullptr, SND_FILENAME | SND_ASYNC);
                this_thread::sleep_for(std::chrono::milliseconds(100));
                powerup++;
            }
            break;

            //for coin
            case coin:
            {
                itemScore = 10;

                score += itemScore;
                PlaySound(TEXT("coin.wav"), nullptr, SND_FILENAME | SND_ASYNC);

                nextNode->type = Empty;
               
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = coin;

            }

            break;
            //for trophy
            case Trophy:
            {
                itemScore = 100;

                score += itemScore;
                PlaySound(TEXT("Trophy.wav"), nullptr, SND_FILENAME | SND_ASYNC);

                nextNode->type = Empty;
               
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = Trophy;

            }

            break;

            //for obstacles
            case obstacle:
                itemScore = 5;
                score -= itemScore;
                PlaySound(TEXT("obstacle.wav"), nullptr, SND_FILENAME | SND_ASYNC);

                // Remove the obstacle when hit by the car
                nextNode->type = Empty;

                obstacless++;
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = obstacle;
                break;

                //for grenade
            case grenade:
            {
                explodeGrenade(nextNode->x, nextNode->y, n);
            }
            break;
            default:
                break;
            }

            if (moves > 30) {
                score--;
            }

           
            CarPath[x_car][y_car].collectedItems.addItem(itemType, itemScore);
            CarPath[x_car][y_car].type = Empty;
            if (nextNode->type == End) {
                stopTimer();
                //cout << getElapsedTime();
                system("cls");
                PlaySound(TEXT("Winning.wav"), nullptr, SND_FILENAME | SND_ASYNC);
                this_thread::sleep_for(std::chrono::milliseconds(1000));

                setConsoleColor(6, 0);

                cout << "Congratulations! You have reached the end. Game over!" << endl;

                resetConsoleColor();

                setConsoleColor(9, 0);
                cout << "Your Score: " << getScore() << endl;


                cout << "Time taken to complete game: " << getElapsedTime() << " seconds" << endl;

                if (getElapsedTime() < 10) {
                    score += 100;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 10 seconds" << endl;
                }

                else if (getElapsedTime() < 30) {
                    score += 80;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 30 seconds" << endl;
                }
                else if (getElapsedTime() < 60) {
                    score += 40;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 60 seconds" << endl;
                }

                resetConsoleColor();
                //for saving the score before exiting the game
                game.saveScore(); 
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << n << ", Score: " << score << endl;
                    scoreFile.close();
                }
                exit(0);
            }

            x_car = nextNode->x;
            y_car = nextNode->y;
            CarPath[x_car][y_car].type = 'C';

        }

    }

    void Update_Game(CarGame& game) {
        //cout << "a";
        if (CarPath[x_car][y_car].type == Power_Up) {
            score += 50; 
            CarPath[x_car][y_car].type = Empty; // Removing the power-up
        }
        if (CarPath[x_car][y_car].type == End) {
            PlaySound(TEXT("Winning.wav"), nullptr, SND_FILENAME | SND_ASYNC);

            setConsoleColor(6, 0);


            cout << "Congratulations! You have reached the end. Game over!" << endl;
            resetConsoleColor();
            setConsoleColor(9, 0);

            cout << "Score: " << game.getScore() << endl;
            resetConsoleColor();
            // game.saveScore(); // Save the score before exiting
            exit(0);
        }
        /*if (CarPath[x_car][y_car].type == Boundary) {
            score -= 5;
        }*/
    }
  
//  grenade explosion
    void explodeGrenade(int grenadeX, int grenadeY, int carX, int carY, CarGame& game, string n) {
        
        if (grenadeX >= 0 && grenadeX < 10 && grenadeY >= 0 && grenadeY < 10) {
            // Explosion of nodes
            char originalType = game.CarPath[grenadeX][grenadeY].type;

         
            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                    if (i == grenadeX && j == grenadeY) {
                        game.CarPath[i][j].type = '*';
                    }
                    else {
                        game.CarPath[i][j].type = 'X';
                    }
                }
            }

            game.CarPath[grenadeX][grenadeY].type = '*';
            game.displayMap();

            // Sound effect of explosion
            PlaySound(TEXT("explosion.wav"), nullptr, SND_ALIAS);

            // For delay
            this_thread::sleep_for(chrono::milliseconds(100));

            // Check if the car is at the grenade explosion position
            if (carX >= max(0, grenadeX - 1) && carX <= min(9, grenadeX + 1) &&
                carY >= max(0, grenadeY - 1) && carY <= min(9, grenadeY + 1)) {

                system("cls"); 
                PlaySound(TEXT("gameover.wav"), nullptr, SND_ALIAS);
                cout << "\n\n\t\t\t\t\t\tGAME OVER\n\n";
                cout << "\t\t\t\t   You hit a car with a grenade!\n\n";
                cout << "Score: " << game.getScore() << endl;
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << n << ", Score: " << score << endl;
                    scoreFile.close();
                }
    
                exit(0);
            }
        }
    }
    void explodeGrenade(int grenadeX, int grenadeY, string n) {
        // Check if the specified position is valid
        if (grenadeX >= 0 && grenadeX < 10 && grenadeY >= 0 && grenadeY < 10) {
            // Explosion of nodes
            char originalType = CarPath[grenadeX][grenadeY].type;

            // Simulate the explosion by updating nearby nodes
            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                    // '*' for the center of the explosion
                    if (i == grenadeX && j == grenadeY) {
                        CarPath[i][j].type = '*';
                    }
                    else {
                        // 'X' for the nodes around the radius
                        CarPath[i][j].type = 'X';
                    }
                }
            }

            // Restore the original character at the center of the explosion
            CarPath[grenadeX][grenadeY].type = ' ';
            displayMap();

            // Sound effect of explosion
            PlaySound(TEXT("explosion.wav"), nullptr, SND_ALIAS);

            // For delay
            this_thread::sleep_for(chrono::milliseconds(100));

            // Check if the car is at the grenade explosion position
            if (getXCar() >= max(0, grenadeX - 1) && getXCar() <= min(9, grenadeX + 1) &&
                getYCar() >= max(0, grenadeY - 1) && getYCar() <= min(9, grenadeY + 1)) {

                system("cls");  // Clear the console screen
                setConsoleColor(11, 64);


                cout << "\n\n\t\t\t\t\t\tGAME OVER\n\n";
                cout << "\t\t\t\t\tYou hit a car with a grenade!\n\n";
                resetConsoleColor();

                setConsoleColor(112, 6);
                cout << "\t\t\t\t\tScore: " << getScore() << endl;
                resetConsoleColor();
                PlaySound(TEXT("gameover.wav"), nullptr, SND_ALIAS);
                this_thread::sleep_for(chrono::milliseconds(100));
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << n << ", Score: " << score << endl;
                    scoreFile.close();
                }

                // saveScore(); // Save the score before exiting
                exit(0);
            }

            // Destroy neighboring nodes
            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                    if (!(i == grenadeX && j == grenadeY)) {
                        CarPath[i][j].type = Empty;
                    }
                }
            }
        }
    }

    void displayMapA()
    {

        // system("cls");

        auto currentTime = chrono::high_resolution_clock::now();

        for (int i = 0; i < 10; ++i)
        {

            for (int j = 0; j < 10; ++j)
            {

                if (CarPath[i][j].type == 'C')
                {

                    setConsoleColor(0, 14);
                    cout << "=";  // Car
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }

                if (CarPath[i][j].type == SPath)
                {
                    setConsoleColor(1, 64);
                    cout << "&";  //Automatic Car
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }

                else if (CarPath[i][j].type == Boundary)
                {

                    cout << '|' << ' ' << ' '; // Boundary
                }

                else if (CarPath[i][j].type == Power_Up)
                {

                    setConsoleColor(10, 0);
                    cout << '*' << ' ' << ' '; // Power-up
                    resetConsoleColor();
                }

                else if (CarPath[i][j].type == Trophy)
                {
                    setConsoleColor(13, 0);
                    cout << '^';  // Power-up
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }

                else if (CarPath[i][j].type == obstacle)
                {
                    setConsoleColor(8, 0);

                    cout << "#";//Obstacle

                    resetConsoleColor();
                    cout << ' ' << ' ';
                }

                else if (CarPath[i][j].type == coin)
                {
                    setConsoleColor(14, 0);
                    cout << '$' << ' ' << ' '; //coins
                    resetConsoleColor();
                }

                else if (CarPath[i][j].type == Start)
                {
                    cout << 'S' << ' ' << ' '; // Start
                }

                else if (CarPath[i][j].type == grenade)
                {
                    setConsoleColor(4, 0);
                    cout << "@" << ' ' << ' ';
                    resetConsoleColor();
                }

                else if (CarPath[i][j].type == End)
                {
                    cout << 'E' << ' ' << ' '; // End
                }

                else
                {

                   

                    bool isRoad = false;
                    for (int k = 0; k < 4; ++k)
                    {
                        if (CarPath[i][j].neighbors[k] != nullptr &&
                            CarPath[i][j].neighbors[k]->type == Empty)
                        {
                            isRoad = true;
                            break;
                        }
                    }

                    if (isRoad)
                    {

                        cout << '.' << ' ' << ' '; // Road

                    }

                    else
                    {
                        cout << ' ' << ' ' << ' '; // Empty cell
                    }
                }
            }
            cout << endl;
        }

    }

    //for taking start and end point from user
    void UserInput(int& startX, int& startY, int& endX, int& endY)
    {
        cout << "Enter end coordinates (x y): ";
        cin >> startX >> startY;
        cout << "Enter start coordinates (x y): ";
        cin >> endX >> endY;
    }

    void Update_DisplayMap(int x, int y, char type)
    {
        CarPath[x][y].type = type; 
        system("cls");            
        displayMapA();           
        Sleep(5);             
    }

    int Calculating_Score(char type)
    {
        int score = 0;

        if (type == Power_Up)
        {
            score = 25;
            return score;
        }

        else if (type == coin)
        {
            score = 10;
            return score;
        }

        else if (type == obstacle)
        {
            score = -5;
            return score;
        }

        else if (type == Trophy)
        {
            score = 100;
            return score;
        }

        return 0; 
    }

    void findShortestPath(int startX, int startY, int endX, int endY)
    {
        int totalScore = 0;
        int dist[10][10];
        bool visited[10][10] = { false};
        // Array to store predecessors
        Predecessor pred[10][10]; 

      

        for (int i = 0; i < 10; i++)
        {

            for (int j = 0; j < 10; j++)
            {

                dist[i][j] = INT_MAX;
                pred[i][j] = { -1, -1 };
            }
        }

        dist[startX][startY] = 0;

        for (int count = 0; count < 10 * 10 - 1; count++)
        {

            int minDist = INT_MAX, minX = -1, minY = -1;

          

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (!visited[i][j] && dist[i][j] <= minDist)
                    {
                        minDist = dist[i][j], minX = i, minY = j;
                    }
                }
            }

            if (minX == -1 || minY == -1)
            {
                break; 
            }

            visited[minX][minY] = true;

            for (int i = 0; i < 4; i++)
            {

                Node* neighbor = CarPath[minX][minY].neighbors[i];

                if (neighbor != nullptr && !visited[neighbor->x][neighbor->y] && neighbor->type != Boundary)

                {
                    int alt = dist[minX][minY] + 1;

                    if (alt < dist[neighbor->x][neighbor->y])
                    {
                        dist[neighbor->x][neighbor->y] = alt;
                        pred[neighbor->x][neighbor->y] = { minX, minY };
                    }
                }
            }
        }

        if (dist[endX][endY] == INT_MAX)
        {
            cout << "No path found." << endl;
            return;
        }

        int x = endX, y = endY;
        system("cls");
        score = 0;

        while (!(x == startX && y == startY))
        {
            if (CarPath[x][y].type == grenade)
            {
                totalScore = 0;
            }

            else
            {
                totalScore += Calculating_Score(CarPath[x][y].type);
            }

            CarPath[x][y].type = SPath; // Move the car to the current position

            displayMapA();            // Display the map with the car's current position
            cout << endl;

            setConsoleColor(0, 42);
            cout << "\t Current Score : " << totalScore << endl;
            resetConsoleColor();

            Sleep(1000);  // Pause for a second

            system("cls");
            // Move to the predecessor
            int tempX = pred[x][y].prevX;
            int tempY = pred[x][y].prevY;
            x = tempX;
            y = tempY;
        }

        CarPath[startX][startY].type = 'C';

        if (CarPath[9][10].type = '.')
        {
            CarPath[9][10].type = ' ';
        }

        displayMapA(); // Display the final map

        setConsoleColor(6, 0);
        cout << endl;
        cout << endl;
        cout << "\t Congratualtions!! You have Reached to the destination." << endl;
        resetConsoleColor();
        setConsoleColor(6, 0);
        cout << "\t Total Score: " << totalScore << " " << endl << endl;
        resetConsoleColor();
    }

    void Automated()
    {
        Initializemap();
        cout << "Initial Map:" << endl;
        displayMapA();

        int startX, startY, endX, endY;
        UserInput(startX, startY, endX, endY);

        findShortestPath(startX, startY, endX, endY);
    }



    void menu() {
        int option;
        setConsoleColor(1, 0);
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                                   SETTINGS                                                               " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        resetConsoleColor();

        setConsoleColor(2, 0);
        cout << "                                        1.Manual" << endl;
        cout << "                                        2.Automatic" << endl;
        cout << "                                        3.Leaderboard" << endl;
        resetConsoleColor();

        cin >> option;
        system("cls");
        if (option == 1) {
            menu2();
        }
        if (option == 2) {
            Automated();
        }
        if (option == 3) {
            Leaderboard leaderboard(100);
            ifstream file("scores.txt");
            string line;

            while (getline(file, line)) {
                size_t comma = line.find(',');
                if (comma != string::npos) {
                    string name = line.substr(0, comma);
                    size_t scorePos = line.find("Score:");
                    if (scorePos != string::npos) {
                        string scoreStr = line.substr(scorePos + 7);
                        // cout << scoreStr;
                        try {
                            int score = stoi(scoreStr);
                            leaderboard.addPlayer(name, score);
                        }
                        catch (const exception& e) {
                            cout << "Error processing line: " << line << endl;
                        }
                    }
                    else {
                        cout << "Invalid line format: " << line << endl;
                    }
                }
            }

            leaderboard.printLeaderboard();

        }

    }
    void menu2() {
        int option;
        setConsoleColor(1, 0);

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                        CHOOSE YOUR LEVEL OF DIFFICULTY                                           " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        resetConsoleColor();
        setConsoleColor(2, 0);

        cout << "                                        1.Easy" << endl;
        cout << "                                        2.Medium" << endl;
        cout << "                                        3.Hard" << endl;
        resetConsoleColor();
        cin >> option;
        system("cls");
       
        if (option == 1) {

            string n;
            system("cls");
            cout << "enter player name" << endl;
            cin >> n;
            system("cls");
            char input;
            CarGame game;
           
            srand(time(0));
            Initializemap();
        
            int grenadeX = rand() % 10;
            int grenadeY = rand() % 10;
            CarPath[grenadeX][grenadeY].type = '@';
           
            game.Initializemap();
            startTimer();
            // Game loop
            while (true) {
                displayMap();
                input = _getch();
                switch (input) {
                case 'a':
                case 'd':
                case 'w':
                case 's':
                  
                    movePlayer(input, game, n);
                    // Check if the car hits the grenade
                    if (game.getXCar() == grenadeX && game.getYCar() == grenadeY) {
                        game.explodeGrenade(grenadeX, grenadeY, game.getXCar(), game.getYCar(), game, n);

                    }
                    break;
                case 'q':
                   
                    exit(0);
                }
                game.Update_Game(game);
            }
        }
        else if (option == 2) {
            string na;
            system("cls");
            cout << "enter player name" << endl;
            cin >> na;
            system("cls");
            char input;
            CarGame gamee;
            
            srand(time(0));
            initializeMap2();
            int grenadex = rand() % 10;
            int grenadey = rand() % 10;
            CarPath[grenadex][grenadey].type = '@';
            gamee.initializeMap2();
            startTimer();
            // Game loop
            while (true) {
                displayMap2();
                input = _getch();
                switch (input) {
                case 'a':
                case 'd':
                case 'w':
                case 's':
                   
                    movePlayer2(input, gamee, na);
                  
                    if (gamee.getXCar() == grenadex && gamee.getYCar() == grenadey) {
                        gamee.explodeGrenade2(grenadex, grenadey, gamee.getXCar(), gamee.getYCar(), gamee, na);

                    }
                    break;
                case 'q':
                    // game.saveScore();
                     // Quit the gameFor quitting the game
                    exit(0);
                }
                gamee.updateGame2(gamee);
            }
        }
        else if (option == 3) {
            string nam;
            system("cls");
            cout << "enter player name" << endl;
            cin >> nam;
            system("cls");
            char input;
            CarGame gameee;
          
            srand(time(0));
            initializeMap3();
           
            int Grenadex = rand() % 10;
            int Grenadey = rand() % 10;
            CarPath[Grenadex][Grenadey].type = '@';
            gameee.initializeMap3();
            startTimer();
            // Game loop
            while (true) {
                displayMap3();
                input = _getch();
                switch (input) {
                case 'a':
                case 'd':
                case 'w':
                case 's':
                 
                    movePlayer3(input, gameee, nam);
                    
                    if (gameee.getXCar() == Grenadex && gameee.getYCar() == Grenadey) {
                        gameee.explodeGrenade3(Grenadex, Grenadey, gameee.getXCar(), gameee.getYCar(), gameee, nam);

                    }
                    break;
                case 'q':
                
                    exit(0);
                }
                gameee.updateGame3(gameee);
            }
        }
       
    }
    void menu3() {
        int option;
        PlaySound(TEXT("gamestart.wav"), nullptr, SND_FILENAME | SND_ASYNC);

        setConsoleColor(1, 0);

        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                                    WELOCJME TO OUR 2D GAME                                             " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        resetConsoleColor();    
        setConsoleColor(2, 0);

        cout << "                                                              1.Start a new game" << endl;
        cout << "                                   2.Quit" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        resetConsoleColor();
        cin >> option;
        system("cls");
        if (option == 1) {
            menu();
        }
        else if (option == 2) {
            exit(0);
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
    void initializeMap2() {
        srand(time(0));
        {
            int count = 0;

     
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    char type = Empty2;
                    if ((rand() % 10 == 0) && (i != 9) && (i != 0)) {
                        type = Boundary2;
                    }
                    else if ((rand() % 20 == 0) && (i != 9) && (i != 0)) {
                        type = Power_Up2;
                    }
                    else if ((rand() % 13 == 0) && (i != 9) && (i != 0)) {
                        type = grenade2;
                    }
                    else if ((rand() % 13 == 0) && (i != 9) && (i != 0)) {
                        type = obstacle2;
                    }
                    else if ((rand() % 15 == 0) && (i != 9) && (i != 0)) {
                        type = coin2;
                    }
                    else if ((rand() % 30 == 0) && (i != 9) && (i != 0) && (count == 0)) {
                        count++;
                        type = Trophy;
                    }
                    else if (i == 0 && j == 0) {
                        type = Start2;
                    }
                    else if (i == 9 && j == 9) {
                        type = End2;
                    }

                    CarPath[i][j] = Node(i, j, type);
                   



                    CarPath[i][j] = Node(i, j, type);
                 
                    if (type == grenade) {
                        int grenadeX = i;
                        int grenadeY = j;
                        CarPath[grenadeX][grenadeY].type = '@';
                    }
                }


                // Connecting neighboring nodes
                for (int i = 0; i < 10; ++i) {
                    for (int j = 0; j < 10; ++j) {
                        if (i > 0) CarPath[i][j].neighbors[0] = &CarPath[i - 1][j]; // Up
                        if (i < 9) CarPath[i][j].neighbors[1] = &CarPath[i + 1][j]; // Down
                        if (j > 0) CarPath[i][j].neighbors[2] = &CarPath[i][j - 1]; // Left
                        if (j < 9) CarPath[i][j].neighbors[3] = &CarPath[i][j + 1]; // Right
                    }
                }
            }
        }
    }
    void displayMap2() {
        system("cls");

     
        setConsoleColor(0, 42);
        cout << "\t\t\t\t\t\t\t Score: " << getScore() << " " << endl;
       
        resetConsoleColor();
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        int elapsedTime = duration.count();
        if (elapsedTime % 1 == 0) {
            displayElapsedTime();
        }
        //cout << endl;



        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                /*  if (CarPath[i][j].type == '@') {
                      setConsoleColor(12,0 );
                       cout << '@'<<' '<<' ';
                        resetConsoleColor();

                  }*/
                if (CarPath[i][j].type == 'C') {
                    setConsoleColor(0, 14);
                    cout << "=";  // Car
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }
                else if (CarPath[i][j].type == Boundary2) {

                    cout << '|' << ' ' << ' '; // Boundary
                }
                else if (CarPath[i][j].type == Power_Up2) {
                    setConsoleColor(10, 0);
                    cout << '*' << ' ' << ' '; // Power-up
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == Trophy) {
                    setConsoleColor(13, 40);
                    cout << '^'; // Power-up
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }

                else if (CarPath[i][j].type == obstacle2) {
                    setConsoleColor(8, 0);

                    cout << "#";//Obstacle

                    resetConsoleColor();
                    cout << ' ' << ' ';
                }
                else if (CarPath[i][j].type == coin2) {
                    setConsoleColor(14, 0);
                    cout << '$' << ' ' << ' '; //coins
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == Start2) {
                    cout << 'S' << ' ' << ' '; // Start
                }
                else if (CarPath[i][j].type == grenade2) {
                    setConsoleColor(4, 0);
                    cout << "@" << ' ' << ' ';
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == End2) {
                    cout << 'E' << ' ' << ' '; // End
                }
             

                else {
                    // Check if the cell is part of the road
                    bool isRoad = false;
                    for (int k = 0; k < 4; ++k) {
                        if (CarPath[i][j].neighbors[k] != nullptr &&
                            CarPath[i][j].neighbors[k]->type == Empty2) {
                            isRoad = true;
                            break;
                        }
                    }

                    if (isRoad) {

                        cout << '.' << ' ' << ' '; // Road

                    }
                    else {
                        cout << ' ' << ' ' << ' '; // Empty cell
                    }
                }
            }
            cout << endl;
        }

        // Display instructions
        cout << endl;
        cout << endl;
        setConsoleColor(0, 6);
        cout << "Instructions:" << endl;
        cout << endl;
        resetConsoleColor();
        setConsoleColor(6, 0);
        cout << "1. Use 'W' to move up" << endl;
        cout << "2. 'S' to move down" << endl;
        cout << "3. 'A' to move left" << endl;
        cout << "4. 'D' to move right." << endl;
        cout << "5. Collect power-ups ('*') to increase your score." << endl;
        cout << "6. Avoid Boundary ('|')" << endl;
        cout << "7. Avoid obstacles for negative scores ('#')" << endl;
        cout << "8. Avoid grenades ('@')" << endl;
        cout << "9. reach the 'E' to finish the game." << endl;
        cout << "10. power up(*) will multpily your score by 2" << endl;
        cout << "11. Trophy(^) will increase your score to +100" << endl;
        cout << "12. ($) coins to increase score " << endl;
        resetConsoleColor();
    }
    int moves2 = 0;
    int powerup2 = 0;
    int obstacless2 = 0;
    void movePlayer2(char Moves, CarGame& gamee, string na) {

        Node* nextNode = nullptr;

        switch (Moves) {
        case 'a':
            nextNode = CarPath[x_car][y_car].neighbors[2]; // Left
            moves2++;
            break;
        case 'd':
            nextNode = CarPath[x_car][y_car].neighbors[3]; // Right
            moves2++;
            break;
        case 'w':
            nextNode = CarPath[x_car][y_car].neighbors[0]; // Up
            moves2++;
            break;
        case 's':
            nextNode = CarPath[x_car][y_car].neighbors[1]; // Down
            moves2++;
            break;
        }

        if (nextNode != nullptr && nextNode->type != Boundary2) {
            char itemType = nextNode->type;

            int itemScore = 0;

            switch (itemType) {
            case Power_Up2:
            {
                itemScore = 2; // Score for collecting a power-up
                score *= itemScore;
                if (score == 0) {
                    score += 20;
                }
                PlaySound(TEXT("Powerup.wav"), nullptr, SND_FILENAME | SND_ASYNC);
                this_thread::sleep_for(std::chrono::milliseconds(100));
                powerup2++;
            }
            break;

            case coin2:
            {
                itemScore = 10;

                score += itemScore;
                PlaySound(TEXT("coin.wav"), nullptr, SND_FILENAME | SND_ASYNC);

                nextNode->type = Empty2;
              
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = coin2;

            }

            break;
            case Trophy:
            {
                itemScore = 100;

                score += itemScore;
                PlaySound(TEXT("Trophy.wav"), nullptr, SND_FILENAME | SND_ASYNC);

                nextNode->type = Empty2;
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = Trophy;

            }

            break;
            case obstacle2:
                itemScore = 5;
                score -= itemScore;
                PlaySound(TEXT("obstacle.wav"), nullptr, SND_FILENAME | SND_ASYNC);

           
                nextNode->type = Empty2;

                obstacless2++;
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = obstacle2;
                break;
            case grenade2:
            {
                explodeGrenade2(nextNode->x, nextNode->y, na);
            }
            break;
            default:
                break;
            }

            if (moves2 > 25) {
              
                score--;
            }

            CarPath[x_car][y_car].collectedItems.addItem(itemType, itemScore);
            CarPath[x_car][y_car].type = Empty2;
         
            if (nextNode->type == End2) {
                stopTimer();
               
                system("cls");
                PlaySound(TEXT("Winning.wav"), nullptr, SND_FILENAME | SND_ASYNC);
                this_thread::sleep_for(std::chrono::milliseconds(1000));

                setConsoleColor(6, 0);

                cout << "Congratulations! You have reached the end. Game over!" << endl;

                resetConsoleColor();

                setConsoleColor(9, 0);
                cout << "Your Score: " << getScore() << endl;


                cout << "Time taken to complete game: " << getElapsedTime() << " seconds" << endl;

                if (getElapsedTime() < 10) {
                    score += 80;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 10 seconds" << endl;
                }

                else if (getElapsedTime() < 30) {
                    score += 40;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 30 seconds" << endl;
                }
                else if (getElapsedTime() < 60) {
                    score += 20;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 60 seconds" << endl;
                }

                resetConsoleColor();
                gamee.saveScore(); 
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << na << ", Score: " << score << endl;
                    scoreFile.close();
                }
                exit(0);
            }

            x_car = nextNode->x;
            y_car = nextNode->y;
            CarPath[x_car][y_car].type = 'C';

        }

      

    }
    void updateGame2(CarGame& gamee) {
        //cout << "a";
        if (CarPath[x_car][y_car].type == Power_Up2) {
            score += 50; 
            CarPath[x_car][y_car].type = Empty2; // Remove the power-up
        }
        if (CarPath[x_car][y_car].type == End2) {
            PlaySound(TEXT("Winning.wav"), nullptr, SND_FILENAME | SND_ASYNC);

            setConsoleColor(6, 0);


            cout << "Congratulations! You have reached the end. Game over!" << endl;
            resetConsoleColor();
            setConsoleColor(9, 0);

            cout << "Score: " << gamee.getScore() << endl;
            resetConsoleColor();
         
            exit(0);
        }
      
    }
    void explodeGrenade2(int grenadeX, int grenadeY, int carX, int carY, CarGame& gamee, string na) {
    
        if (grenadeX >= 0 && grenadeX < 10 && grenadeY >= 0 && grenadeY < 10) {
        
            char originalType = gamee.CarPath[grenadeX][grenadeY].type;

           
            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                   
                    if (i == grenadeX && j == grenadeY) {
                        gamee.CarPath[i][j].type = '*';
                    }
                    else {
                     
                        gamee.CarPath[i][j].type = 'X';
                    }
                }
            }

          
            gamee.CarPath[grenadeX][grenadeY].type = '*';
            gamee.displayMap();

           
            PlaySound(TEXT("explosion.wav"), nullptr, SND_ALIAS);

        
            this_thread::sleep_for(chrono::milliseconds(100));

           
            if (carX >= max(0, grenadeX - 1) && carX <= min(9, grenadeX + 1) &&
                carY >= max(0, grenadeY - 1) && carY <= min(9, grenadeY + 1)) {

                system("cls");  
                PlaySound(TEXT("gameover.wav"), nullptr, SND_ALIAS);
                cout << "\n\n\t\t\t\t\t\tGAME OVER\n\n";
                cout << "\t\t\t\t   You hit a car with a grenade!\n\n";
                cout << "Score: " << gamee.getScore() << endl;
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << na << ", Score: " << score << endl;
                    scoreFile.close();
                }
              
                exit(0);
            }
        }
    }void explodeGrenade2(int grenadeX, int grenadeY, string na) {
      
        if (grenadeX >= 0 && grenadeX < 10 && grenadeY >= 0 && grenadeY < 10) {
           
            char originalType = CarPath[grenadeX][grenadeY].type;

            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                 
                    if (i == grenadeX && j == grenadeY) {
                        CarPath[i][j].type = '*';
                    }
                    else {
                   
                        CarPath[i][j].type = 'X';
                    }
                }
            }

          
            CarPath[grenadeX][grenadeY].type = ' ';
            displayMap();

           
            PlaySound(TEXT("explosion.wav"), nullptr, SND_ALIAS);

         
            this_thread::sleep_for(chrono::milliseconds(100));

           
            if (getXCar() >= max(0, grenadeX - 1) && getXCar() <= min(9, grenadeX + 1) &&
                getYCar() >= max(0, grenadeY - 1) && getYCar() <= min(9, grenadeY + 1)) {

                system("cls");  
                setConsoleColor(11, 64);


                cout << "\n\n\t\t\t\t\t\tGAME OVER\n\n";
                cout << "\t\t\t\t\tYou hit a car with a grenade!\n\n";
                resetConsoleColor();

                setConsoleColor(112, 6);
                cout << "\t\t\t\t\tScore: " << getScore() << endl;
                resetConsoleColor();
                PlaySound(TEXT("gameover.wav"), nullptr, SND_ALIAS);
                this_thread::sleep_for(chrono::milliseconds(100));
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << na << ", Score: " << score << endl;
                    scoreFile.close();
                }

               
                exit(0);
            }

            // Destroy neighboring nodes
            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                    if (!(i == grenadeX && j == grenadeY)) {
                        CarPath[i][j].type = Empty2;
                    }
                }
            }
        }
    }
    void initializeMap3() {
        srand(time(0));
        {
            int co = 0;

       
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    char type = Empty3;
                    if ((rand() % 4 == 0) && (i != 9) && (i != 0)) {
                        type = Boundary3;
                    }
                    else if ((rand() % 22 == 0) && (i != 9) && (i != 0)) {
                        type = Power_Up3;
                    }
                    else if ((rand() % 10 == 0) && (i != 9) && (i != 0)) {
                        type = grenade3;
                    }
                    else if ((rand() % 5 == 0) && (i != 9) && (i != 0)) {
                        type = obstacle3;
                    }
                    else if ((rand() % 22 == 0) && (i != 9) && (i != 0)) {
                        type = coin3;
                    }
                    else if ((rand() % 13 == 0) && (i != 9) && (i != 0) && (co == 0)) {
                        co++;
                        type = Trophy;
                    }
                    else if (i == 0 && j == 0) {
                        type = Start3;
                    }
                    else if (i == 9 && j == 9) {
                        type = End3;
                    }

                    CarPath[i][j] = Node(i, j, type);
             



                    CarPath[i][j] = Node(i, j, type);
                    // Place a grenade on the map
                    if (type == grenade) {
                        int grenadeX = i;
                        int grenadeY = j;
                        CarPath[grenadeX][grenadeY].type = '@';
                    }
                }


                // Connect neighboring nodes
                for (int i = 0; i < 10; ++i) {
                    for (int j = 0; j < 10; ++j) {
                        if (i > 0) CarPath[i][j].neighbors[0] = &CarPath[i - 1][j]; // Up
                        if (i < 9) CarPath[i][j].neighbors[1] = &CarPath[i + 1][j]; // Down
                        if (j > 0) CarPath[i][j].neighbors[2] = &CarPath[i][j - 1]; // Left
                        if (j < 9) CarPath[i][j].neighbors[3] = &CarPath[i][j + 1]; // Right
                    }
                }
            }
        }
    }
    void displayMap3() {
        system("cls");

    

      //  cout << "\t\t\t\t\t\t\t --------- " << "\t\t\t\t\t\t\t" << endl;

        setConsoleColor(0, 42);
        cout << "\t\t\t\t\t\t\t Score: " << getScore() << " " << endl;
        //   cout << "\t\t\t\t\t\t\t --------- " << "\t\t\t\t\t\t\t" << endl;
        resetConsoleColor();
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        int elapsedTime = duration.count();
        if (elapsedTime % 1 == 0) {
            displayElapsedTime();
        }
     



        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
              
                if (CarPath[i][j].type == 'C') {
                    setConsoleColor(0, 14);
                    cout << "=";  // Car
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }
                else if (CarPath[i][j].type == Boundary3) {

                    cout << '|' << ' ' << ' '; // Boundary
                }
                else if (CarPath[i][j].type == Power_Up3) {
                    setConsoleColor(10, 0);
                    cout << '*' << ' ' << ' '; // Power-up
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == obstacle3) {
                    setConsoleColor(8, 0);

                    cout << "#";//Obstacle

                    resetConsoleColor();
                    cout << ' ' << ' ';
                }
                else if (CarPath[i][j].type == Trophy) {
                    setConsoleColor(13, 0);
                    cout << '^'; // Power-up
                    resetConsoleColor();
                    cout << ' ' << ' ';
                }
                else if (CarPath[i][j].type == coin3) {
                    setConsoleColor(14, 0);
                    cout << '$' << ' ' << ' '; //coins
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == Start3) {
                    cout << 'S' << ' ' << ' '; // Start
                }
                else if (CarPath[i][j].type == grenade3) {
                    setConsoleColor(4, 0);
                    cout << "@" << ' ' << ' ';
                    resetConsoleColor();
                }
                else if (CarPath[i][j].type == End3) {
                    cout << 'E' << ' ' << ' '; // End
                }
              
                else {
                    // Check if the cell is part of the road
                    bool isRoad = false;
                    for (int k = 0; k < 4; ++k) {
                        if (CarPath[i][j].neighbors[k] != nullptr &&
                            CarPath[i][j].neighbors[k]->type == Empty3) {
                            isRoad = true;
                            break;
                        }
                    }

                    if (isRoad) {

                        cout << '.' << ' ' << ' '; // Road

                    }
                    else {
                        cout << ' ' << ' ' << ' '; // Empty cell
                    }
                }
            }
            cout << endl;
        }

        // Display instructions
        cout << endl;
        cout << endl;
        setConsoleColor(0, 6);
        cout << "Instructions:" << endl;
        cout << endl;
        resetConsoleColor();
        setConsoleColor(6, 0);
        cout << "1. Use 'W' to move up" << endl;
        cout << "2. 'S' to move down" << endl;
        cout << "3. 'A' to move left" << endl;
        cout << "4. 'D' to move right." << endl;
        cout << "5. Collect power-ups ('*') to increase your score." << endl;
        cout << "6. Avoid Boundary ('|')" << endl;
        cout << "7. Avoid obstacles for negative scores ('#')" << endl;
        cout << "8. Avoid grenades ('@')" << endl;
        cout << "9. reach the 'E' to finish the game." << endl;
        cout << "10. power up(*) will multpily your score by 2" << endl;
        cout << "11. Trophy(^) will increase your score to +100" << endl;
        cout << "12. ($) coins to increase score " << endl;
        resetConsoleColor();
    }
    int moves3 = 0;
    int powerup3 = 0;
    int obstacless3 = 0;
    void movePlayer3(char Moves, CarGame& gamee, string na) {

        Node* nextNode = nullptr;

        switch (Moves) {
        case 'a':
            nextNode = CarPath[x_car][y_car].neighbors[2]; // Left
            moves3++;
            break;
        case 'd':
            nextNode = CarPath[x_car][y_car].neighbors[3]; // Right
            moves3++;
            break;
        case 'w':
            nextNode = CarPath[x_car][y_car].neighbors[0]; // Up
            moves3++;
            break;
        case 's':
            nextNode = CarPath[x_car][y_car].neighbors[1]; // Down
            moves3++;
            break;
        }

        if (nextNode != nullptr && nextNode->type != Boundary3) {
            char itemType = nextNode->type;

            int itemScore = 0;

            switch (itemType) {
            case Power_Up3:
            {
                itemScore = 2; // Score for collecting a power-up
                score *= itemScore;
                if (score == 0) {
                    score += 15;
                }
                PlaySound(TEXT("Powerup.wav"), nullptr, SND_FILENAME | SND_ASYNC);
                this_thread::sleep_for(std::chrono::milliseconds(100));
                powerup3++;
            }
            break;

            case coin3:
            {
                itemScore = 10;

                score += itemScore;
                PlaySound(TEXT("coin.wav"), nullptr, SND_FILENAME | SND_ASYNC);

                nextNode->type = Empty2;
                //for sound effect of coin
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = coin3;

            }

            break;
            case Trophy:
            {
                itemScore = 100;

                score += itemScore;
                PlaySound(TEXT("Trophy.wav"), nullptr, SND_FILENAME | SND_ASYNC);

                nextNode->type = Empty2;
              
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = Trophy;

            }

            break;
            case obstacle3:
                itemScore = 10;
                score -= itemScore;
                PlaySound(TEXT("obstacle.wav"), nullptr, SND_FILENAME | SND_ASYNC);

                // Remove the obstacle when hit by the car
                nextNode->type = Empty3;

                obstacless3++;
                this_thread::sleep_for(std::chrono::milliseconds(100));
                CarPath[x_car][y_car].type = obstacle3;
                break;
            case grenade3:
            {
                explodeGrenade3(nextNode->x, nextNode->y, na);
            }
            break;
            default:
                break;
            }

            if (moves3 > 22) {
             
                score--;
            }

         
            CarPath[x_car][y_car].collectedItems.addItem(itemType, itemScore);
            CarPath[x_car][y_car].type = Empty3;
        
            if (nextNode->type == End3) {
                stopTimer();
               
                system("cls");
                PlaySound(TEXT("Winning.wav"), nullptr, SND_FILENAME | SND_ASYNC);
                this_thread::sleep_for(std::chrono::milliseconds(1000));

                setConsoleColor(6, 0);

                cout << "Congratulations! You have reached the end. Game over!" << endl;

                resetConsoleColor();

                setConsoleColor(9, 0);
                cout << "Your Score: " << getScore() << endl;


                cout << "Time taken to complete game: " << getElapsedTime() << " seconds" << endl;

                if (getElapsedTime() < 10) {
                    score += 40;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 10 seconds" << endl;
                }

                else if (getElapsedTime() < 30) {
                    score += 20;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 30 seconds" << endl;
                }
                else if (getElapsedTime() < 60) {
                    score += 10;
                    cout << "Your Final Score:" << getScore() << " for completing the game under 60 seconds" << endl;
                }

                resetConsoleColor();
                gamee.saveScore(); // Save the score before exiting
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << na << ", Score: " << score << endl;
                    scoreFile.close();
                }
                exit(0);
            }

            x_car = nextNode->x;
            y_car = nextNode->y;
            CarPath[x_car][y_car].type = 'C';

        }

     

    }
    void updateGame3(CarGame& gamee) {
        //cout << "a";
        if (CarPath[x_car][y_car].type == Power_Up3) {
            score += 50; // Increment the score for collecting a power-up
            CarPath[x_car][y_car].type = Empty3; // Remove the power-up
        }
        if (CarPath[x_car][y_car].type == End3) {
            PlaySound(TEXT("Winning.wav"), nullptr, SND_FILENAME | SND_ASYNC);

            setConsoleColor(6, 0);


            cout << "Congratulations! You have reached the end. Game over!" << endl;
            resetConsoleColor();
            setConsoleColor(9, 0);

            cout << "Score: " << gamee.getScore() << endl;
            resetConsoleColor();
            // game.saveScore(); // Save the score before exiting
            exit(0);
        }
      
    }
    void explodeGrenade3(int grenadeX, int grenadeY, int carX, int carY, CarGame& gamee, string na) {
   
        if (grenadeX >= 0 && grenadeX < 10 && grenadeY >= 0 && grenadeY < 10) {
           
            char originalType = gamee.CarPath[grenadeX][grenadeY].type;

           
            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                   
                    if (i == grenadeX && j == grenadeY) {
                        gamee.CarPath[i][j].type = '*';
                    }
                    else {
                        
                        gamee.CarPath[i][j].type = 'X';
                    }
                }
            }

            
            gamee.CarPath[grenadeX][grenadeY].type = '*';
            gamee.displayMap();

            PlaySound(TEXT("explosion.wav"), nullptr, SND_ALIAS);

           
            this_thread::sleep_for(chrono::milliseconds(100));

           
            if (carX >= max(0, grenadeX - 1) && carX <= min(9, grenadeX + 1) &&
                carY >= max(0, grenadeY - 1) && carY <= min(9, grenadeY + 1)) {

                system("cls");  
                PlaySound(TEXT("gameover.wav"), nullptr, SND_ALIAS);
                cout << "\n\n\t\t\t\t\t\tGAME OVER\n\n";
                cout << "\t\t\t\t   You hit a car with a grenade!\n\n";
                cout << "Score: " << gamee.getScore() << endl;
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << na << ", Score: " << score << endl;
                    scoreFile.close();
                }
               
                exit(0);
            }
        }
    }
    void explodeGrenade3(int grenadeX, int grenadeY, string na) {
     
        if (grenadeX >= 0 && grenadeX < 10 && grenadeY >= 0 && grenadeY < 10) {
            // Explosion of nodes
            char originalType = CarPath[grenadeX][grenadeY].type;

          
            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                  
                    if (i == grenadeX && j == grenadeY) {
                        CarPath[i][j].type = '*';
                    }
                    else {
                       
                        CarPath[i][j].type = 'X';
                    }
                }
            }

            // Restore the original character at the center of the explosion
            CarPath[grenadeX][grenadeY].type = ' ';
            displayMap();

            // Sound effect of explosion
            PlaySound(TEXT("explosion.wav"), nullptr, SND_ALIAS);

           
            this_thread::sleep_for(chrono::milliseconds(100));

            //the car is at the grenade explosion position
            if (getXCar() >= max(0, grenadeX - 1) && getXCar() <= min(9, grenadeX + 1) &&
                getYCar() >= max(0, grenadeY - 1) && getYCar() <= min(9, grenadeY + 1)) {

                system("cls");  
                setConsoleColor(11, 64);


                cout << "\n\n\t\t\t\t\t\tGAME OVER\n\n";
                cout << "\t\t\t\t\tYou hit a car with a grenade!\n\n";
                resetConsoleColor();

                setConsoleColor(112, 6);
                cout << "\t\t\t\t\tScore: " << getScore() << endl;
                resetConsoleColor();
                PlaySound(TEXT("gameover.wav"), nullptr, SND_ALIAS);
                this_thread::sleep_for(chrono::milliseconds(100));
                ofstream scoreFile("scores.txt", ios::app);
                if ((scoreFile.is_open())) {
                    scoreFile << "Player " << na << ", Score: " << score << endl;
                    scoreFile.close();
                }

               
                exit(0);
            }

            // Destroying neighboring nodes
            for (int i = max(0, grenadeX - 1); i <= min(9, grenadeX + 1); ++i) {
                for (int j = max(0, grenadeY - 1); j <= min(9, grenadeY + 1); ++j) {
                    if (!(i == grenadeX && j == grenadeY)) {
                        CarPath[i][j].type = Empty3;
                    }
                }
            }
        }
    }

};