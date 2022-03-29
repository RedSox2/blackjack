#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <ctime>
#include <cmath>
#include <random>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <fstream>
#ifdef _WIN32
#include <direct.h>
#include <Windows.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
using namespace std;

void Clear(void);
void csleep(int millis);
int dealCards(void);
bool isAce(string cardsIndex);
void wait(void);
void checkHighScore(float score, string fileLocation);
string readLine(const string &filename, int N);
void displayHighScore(string fileLocation);
string GetCurrentDirectory(void);

// player and dealer card inventories
int dealerCards[5] = {0, 0, 0, 0, 0};
int dealerDealIndex = 0;
int playerCards[5] = {0, 0, 0, 0, 0};
int playerDealIndex = 0;
int dealerTotal;
int playerTotal = 7;
int aceValue;
string hitORstay;
bool blackjack = false;
bool dealerBlackjack = false;
bool busted = false;
bool dealerBusted = false;
bool fiveCard = false;
int playerDistance;
int dealerDistance;
int numCardsDealt = 0;
int aceCount = 0;
string highscoreFileLocation;

// loop variables
bool myRound = true;
bool YNhit = true;
bool deckThru = false;

// player money managment
float bet;
float balance = 5;

// different cards, the card values, and if they've already been dealt or not
array<string, 53> cards = {"", "AoS", "AoH", "AoD", "AoC", "KoS", "KoH", "KoD", "KoC", "QoS", "QoH", "QoD", "QoC", "JoS", "JoH", "JoD", "JoC", "10oS", "10oH", "10oD", "10oC", "9oS", "9oH", "9oD", "9oC", "8oS", "8oH", "8oD", "8oC", "7oS", "7oH", "7oD", "7oC", "6oS", "6oH", "6oD", "6oC", "5oS", "5oH", "5oD", "5oC", "4oS", "4oH", "4oD", "4oC", "3oS", "3oH", "3oD", "3oC", "2oS", "2oH", "2oD", "2oC"};
array<const string, 53> newDeck = {"", "AoS", "AoH", "AoD", "AoC", "KoS", "KoH", "KoD", "KoC", "QoS", "QoH", "QoD", "QoC", "JoS", "JoH", "JoD", "JoC", "10oS", "10oH", "10oD", "10oC", "9oS", "9oH", "9oD", "9oC", "8oS", "8oH", "8oD", "8oC", "7oS", "7oH", "7oD", "7oC", "6oS", "6oH", "6oD", "6oC", "5oS", "5oH", "5oD", "5oC", "4oS", "4oH", "4oD", "4oC", "3oS", "3oH", "3oD", "3oC", "2oS", "2oH", "2oD", "2oC"};
/* */ int cardVals[53] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 6, 6, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2};
const int deckVals[53] = {0, 1, 1, 1, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 8, 8, 8, 8, 7, 7, 7, 7, 6, 6, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2};
bool cardsDealt[53] = {true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
int cardsLeft = 52;


std::string GetExePath( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}



int main() {

    #ifdef _WIN32
    highscoreFileLocation = GetExePath() + "\\highscores.txt";
    #else
    highscoreFileLocation = GetExePath() + "/highscores.txt";
    #endif
    shuffle(cards.begin()+1, cards.end(), default_random_engine(time(NULL)));
    for (int i = 1; i <= 53; i++) {
        for (int n = 1; n <= 53; n++) {
            if (cards[i] == newDeck[n]) {
                cardVals[i] = deckVals[n];
            }
        }
    }

    Clear();

    cout << "                          WELCOME TO:                                      \n\n";
    cout << " _____       __           _________     __________    __    __               \n";
    cout << "|  _  \\     |  |         |   ___   |   |   _______|  |  | /  /              \n";
    cout << "| |_)  |    |  |         |  |   |  |   |  |          |  |/  /                \n";
    cout << "|     /     |  |         |  |___|  |   |  |          |     /                 \n";
    cout << "|  _  \\     |  |         |   ___   |   |  |          |     \\               \n";
    cout << "| |_)  |    |  |_____    |  |   |  |   |  |_______   |  |\\  \\              \n";
    cout << "|_____/     |________|   |__|   |__|   |__________|  |__| \\__\\             \n";
    cout << "                                                                             \n";
    cout << "           __    _________     __________    __    __                        \n";
    cout << "          |  |  |   ___   |   |   _______|  |  | /  /                        \n";
    cout << "          |  |  |  |   |  |   |  |          |  |/  /                         \n";
    cout << "          |  |  |  |___|  |   |  |          |     /                          \n";
    cout << "          |  |  |   ___   |   |  |          |     \\                         \n";
    cout << "     _____|  |  |  |   |  |   |  |_______   |  |\\  \\                       \n";
    cout << "     \\_______/  |__|   |__|   |__________|  |__| \\__\\                     \n";
    cout << "                                                                             \n";
    cout << "                                                                             \n";
    displayHighScore(highscoreFileLocation);

    csleep(10000);

    Clear();

    cout << "*You will start with $5 in chips.\n";
    cout << "*You can bet any amount including cent amounts.\n";
    cout << "*If you bet below a cent, you will bet $0.01.\n";
    cout << "*If you bet above your total amount, you will go all in\n";
    cout << "*You will be told your amount, your cards, the number of cards\nleft in the deck, and one of the dealer's card values" << endl;
    wait();
    Clear();

    numCardsDealt = 0;

    while (!deckThru)
    {

        blackjack = false;
        busted = false;
        dealerBusted = false;
        dealerBlackjack = false;
        playerCards[0] = 0;
        playerCards[1] = 0;
        playerCards[2] = 0;
        playerCards[3] = 0;
        playerCards[4] = 0;

        dealerCards[0] = 0;
        dealerCards[1] = 0;
        dealerCards[2] = 0;
        dealerCards[3] = 0;
        dealerCards[4] = 0;

        numCardsDealt += 4;
        
        Clear();
        
        playerCards[0] = dealCards();
        dealerCards[0] = dealCards();
        playerCards[1] = dealCards();
        dealerCards[1] = dealCards();
        // playerCards[0] = 22;
        // playerCards[1] = 2;
        
        // cout << cards[1] << " Should be player (card abbr) " << cards[playerCards[0]] << endl;
        // cout << cards[2] << " Should be dealer (card abbr) " << cards[dealerCards[0]] << endl;
        // cout << cards[3] << " Should be player (card indx) " << playerCards[1] << endl;
        // cout << cards[4] << " Should be dealer (card indx) " << dealerCards[1] << endl;

        playerTotal = cardVals[playerCards[0]] + cardVals[playerCards[1]];
        dealerTotal = cardVals[dealerCards[0]] + cardVals[dealerCards[1]];

        
        myRound = true;
        bet = 0;
        
        cout << "How much would you like to bet? (You have $" << balance << ")" << endl;
        cin >> bet;
        if (bet > balance) { bet = balance; }
        else if ( bet < 0.01) { bet = 0.01; }
            balance = floor((100 * balance) + 0.05) / 100;

        if ( playerTotal == 11 && (cardVals[playerCards[0]] == 10 || cardVals[playerCards[1]] == 10) ) {
            cout << "You have blackjack!" << endl;
            cout << "You had a " << cards[playerCards[0]] << " and a " << cards[playerCards[1]] << endl;
            myRound = false;
            blackjack = true;
            
        }
        
        while (myRound)
        {
            aceCount = 0;
            for (int i = 0; i <= 4; i++) {
                if (isAce(cards[playerCards[i]])) { 
                    aceCount = aceCount+1; 
                }
            }

            playerTotal = cardVals[playerCards[0]] + cardVals[playerCards[1]] + cardVals[playerCards[2]] + cardVals[playerCards[3]] + cardVals[playerCards[4]];
            for (int i = aceCount; i >= 0; i--) {
                if (playerTotal <= (21 - (10*i))) {
                    playerTotal += 10*i;
                    break;
                }
            }
            
            // cout << aceCount << endl;
            // cout << playerTotal << endl;

            csleep(2000);
            
            Clear();
            hitORstay = "";
                 if ( playerCards [0] == 0 ) { playerDealIndex = 0; }
            else if ( playerCards [1] == 0 ) { playerDealIndex = 1; }
            else if ( playerCards [2] == 0 ) { playerDealIndex = 2; }
            else if ( playerCards [3] == 0 ) { playerDealIndex = 3; }
            else if ( playerCards [4] == 0 ) { playerDealIndex = 4; }

            Clear();
            if (playerTotal < 21 && playerCards[4] == 0) 
            {
                
                blackjack = false;
                busted = false;
                
                cout << "There are " << (52 - numCardsDealt) << " cards left in the deck." << endl;
                cout << "Your current balance is: $" << balance << endl;
                cout << "You are betting: $" << bet << endl;
                cout << endl << "Your cards are: " << cards[playerCards[0]] << " " << cards[playerCards[1]] << " " << cards[playerCards[2]] << " " << cards[playerCards[3]] << " " << cards[playerCards[4]] << endl;
                cout << "(Max ace values credited) You have a total of: " << playerTotal << endl;
                cout << "The dealer is showing: " << cards[dealerCards[1]] << endl;

                cout << endl << "Would you like to hit (y) or stay (n)?" << endl;
                cin >> hitORstay;
                if (hitORstay != "y" && hitORstay != "Y" && hitORstay != "n" && hitORstay != "N") 
                {
                    hitORstay = "y";
                }

                if (hitORstay == "y" || hitORstay == "Y") {
                    playerCards[playerDealIndex] = dealCards();
                    cout << "Here is your next card: " << cards[playerCards[playerDealIndex]] << endl;
                    numCardsDealt++;
                } else {
                    myRound = false;
                }
                
            } else if (playerTotal == 21) { 
                cout << "There are " << (52 - numCardsDealt) << " cards left in the deck." << endl;
                cout << "Your current balance is: $" << balance << endl;
                cout << "You are betting: $" << bet << endl;
                cout << endl << "Your cards are: " << cards[playerCards[0]] << " " << cards[playerCards[1]] << " " << cards[playerCards[2]] << " " << cards[playerCards[3]] << " " << cards[playerCards[4]] << endl;
                cout << "You have 21!" << endl;
                cout << "The dealer is showing: " << cards[dealerCards[1]] << endl;
                csleep(1000);
                myRound = false;
            }
            else if (playerTotal > 21) { 
                cout << "You have busted!" << endl;
                cout << "Your cards were: " << cards[playerCards[0]] << " " << cards[playerCards[1]] << " " << cards[playerCards[2]] << " " << cards[playerCards[3]] << " " << cards[playerCards[4]] << endl;
                cout << "You had a total of: " << playerTotal << endl;
                myRound = false;
                busted = true;
            } else if (playerCards[4] != 0 && !blackjack && !busted) {
                cout << "You have 5 Card Charlie!" << endl;
                fiveCard = true;
                myRound = false;
                
            }
        }

        csleep(3000);
        Clear();
        
        dealerDealIndex = 2;
        dealerTotal = cardVals[dealerCards[0]] + cardVals[dealerCards[1]]+ cardVals[dealerCards[2]]+ cardVals[dealerCards[3]]+ cardVals[dealerCards[4]];
        cout << "The dealer has " << cards[dealerCards[0]] << " " << cards[dealerCards[1]] << " " << cards[dealerCards[2]] << " " << cards[dealerCards[3]] << " " << cards[dealerCards[4]] << endl;
        if (dealerTotal == 11 && (cardVals[dealerCards[0]] == 1 || cardVals[dealerCards[1]] == 1)){ 
            cout << "The dealer has blackjack!" << endl;
            dealerBlackjack = true;
        } else if (dealerTotal < 21) {
            cout << "The dealer's total is: " << dealerTotal << endl;
        } else if (dealerTotal > 21) {
            cout << "The dealer had busted!" << endl;
            dealerBusted = true;
        }
        csleep(3000);
        if (!blackjack && dealerTotal <= 16 && !dealerBlackjack) {
            while (dealerTotal <= 16 && dealerCards[4] == 0) 
            {
                Clear();
                dealerCards[dealerDealIndex] = dealCards();
                numCardsDealt++;
                dealerDealIndex++;
                dealerTotal = cardVals[dealerCards[0]] + cardVals[dealerCards[1]]+ cardVals[dealerCards[2]]+ cardVals[dealerCards[3]]+ cardVals[dealerCards[4]];
                cout << "The dealer has " << cards[dealerCards[0]] << " " << cards[dealerCards[1]] << " " << cards[dealerCards[2]] << " " << cards[dealerCards[3]] << " " << cards[dealerCards[4]] << endl;
                if (dealerTotal <= 21) {
                    cout << "The dealer's total is: " << dealerTotal << endl;
                } else if (dealerTotal > 21) {
                    cout << "The dealer had busted!" << endl;
                    dealerBusted = true;
                }
                csleep(3000);
            } 
        }

        aceCount = 0;
        for (int i = 0; i <= 4; i++) {
            if (isAce(cards[playerCards[i]])) { 
                aceCount = aceCount+1; 
            }
        }

        playerTotal = cardVals[playerCards[0]] + cardVals[playerCards[1]] + cardVals[playerCards[2]] + cardVals[playerCards[3]] + cardVals[playerCards[4]];
        for (int i = aceCount; i >= 0; i--) {
            if (playerTotal <= (21 - (10*i))) {
                playerTotal += 10*i;
                break;
            }
        }
        
        dealerTotal = cardVals[dealerCards[0]] + cardVals[dealerCards[1]] + cardVals[dealerCards[2]] + cardVals[dealerCards[3]] + cardVals[dealerCards[4]];

        playerDistance = 21;
        dealerDistance = 21;
        if (busted) {
            cout << "You lose!" << " Your bet ($" << bet << ") has been deducted from your total ($" << balance << ")." << endl;
            balance = balance - bet;
        } else if (fiveCard && !busted && !blackjack) {
            cout << "You win! " << "Your bet ($" << bet << ") has been added yo your total ($" << balance << ")!" << endl;
        } else if (blackjack && !dealerBlackjack) {
            cout << "You win! " << "Your bet ($" << bet << ") has been added to your total ($" << balance << ")" << endl;
            balance += bet*1.5;
        } else if (dealerBusted && !busted && !blackjack) {
            cout << "You win! " << "Your bet ($" << bet << ") has been added to your total ($" << balance << ")" << endl;
            balance = balance + bet;
        } else if (dealerBlackjack && !blackjack) {
            cout << "You lose!" << " Your bet ($" << bet << ") has been deducted from your total ($" << balance << ")." << endl;
            balance = balance - bet;
        } else if (blackjack && dealerBlackjack) {
            cout << "Push! " << "You both have blackjack!" << endl;
        } else {
            playerDistance = 21 - playerTotal;
            dealerDistance = 21 - dealerTotal;
            if (playerDistance < dealerDistance) {
                cout << "You win! " << "Your bet ($" << bet << ") has been added to your total ($" << balance << ")" << endl;
                balance = balance + bet;
            } else if (dealerDistance < playerDistance) {
                cout << "You lose!" << " Your bet ($" << bet << ") has been deducted from your total ($" << balance << ")." << endl;
                balance = balance - bet;
            } else if (playerDistance == dealerDistance) {
                cout << "Push! " << "No change has been made to your balance" << endl;
            }
        }

        csleep(5000);
        
        cardsLeft = 52 - numCardsDealt;

        if (cardsLeft < 10) { deckThru = true; }
        else if ( balance == 0 ) { deckThru = true; }
    }
    Clear();
    balance = floor((100 * balance) + 0.05) / 100;
    
    if (balance == 0) {
        cout << "You lost $" << bet << " and have no money left." << endl;
    } else if (balance > 0) {
        cout << "You finished with $" << balance << "! Great job!" << endl;
    }

    checkHighScore(balance, highscoreFileLocation);

    return EXIT_SUCCESS;
} 

void Clear(void)
{
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

void csleep(int millis)
{
    #ifdef _WIN32
    Sleep(millis);
    #else
    sleep(0.001*millis);
    #endif
}

int dealCards(void)
{
    int card;
    bool cardIsDealt = false;
    for (int i = 1; i <= 53; i++) {
        if (!cardsDealt[i]) {
            card = i;
            cardsDealt[i] = true;
            break;
        }
    }

    return card;
    
}

bool isAce(string cardsIndex)
{
    if (cardsIndex.front() == 'A') {
        return true;
    } else { return false; }
} 


void wait(void) {
    cout << endl << "Press [ENTER] to continue . . ." << endl;
    cin.get();
}

string readLine(const string& filename, int N)
{
  ifstream in(filename.c_str());

  string s;
  //for performance
  s.reserve(100);

  //skip N lines
  for (int i = 0; i < N - 1; ++i)
    std::getline(in, s);

  std::getline(in, s);
  return s;
}

void displayHighScore(string fileLocation)
{
  ifstream highScoreDisplay(fileLocation);
  string displayStr;
  cout << endl
       << "The current high score is: " << endl
       << endl
       << endl;

    while (!highScoreDisplay.eof()) {
        getline(highScoreDisplay, displayStr);
        cout << displayStr << endl;
    }
}
void checkHighScore(float score, string fileLocation)
{
    ofstream highScores;
    string urName;
    time_t myTime = time(0);
    char *dateTime = ctime(&myTime);
    
    if (score > stof( readLine(fileLocation, 3).erase(0,8) ))
    {
        cout << "Congrats!!!!!!!!!!!!!!!!!" << endl;
        cout << "You also got a highscore!" << endl;
        cout << "Please enter your name to be logged for the highscore: ";
        cin >> urName;
        highScores.open(fileLocation);
        highScores << "By: " << urName << endl;
        highScores << "Date: " << dateTime;
        highScores << "Score: $" << score << endl;
        highScores.close();
    }
}
