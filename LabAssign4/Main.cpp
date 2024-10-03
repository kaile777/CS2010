#include <iostream>
#include <cstdlib>

using namespace std;

void playGame(int& bank_roll);
int die();
void checkWin(bool win, int& back_roll, int bet);

// returns one roll of die
// call this function for each die roll
// returns a value from 1-6, representing a 6-sided dice
int die() {
    int die, min = 1, max = 6;
    die = min + (rand() % (max - min + 1));

    return die;    
}

// output win or lose message based off win or loss
// updates bank_roll with appropriate addition or subtraction of bet
void checkWin(bool win, int& bank_roll, int bet) {
    if (win == true) {
        cout << "You Win!" << endl;
        cout << "Balance: $" << bank_roll << " + " << bet << endl;

        bank_roll += bet;
        cout << "$" << bank_roll << endl;
    }
    else {
        cout << "You Lose!" << endl;
        cout << "Balance: $" << bank_roll << " - " << bet << endl;

        bank_roll -= bet;
        cout << "$" << bank_roll << endl;
    }
}

void playGame(int& bank_roll) {

    int bet = 1; 
    bool win;

    // Lets user enter wager if their bank roll is greater than 1
    // If users bank roll = 1, program auto bets 1 credit without input
    if (bank_roll > 1) {
        while (true) {
            cout << endl << "Enter Bet Amount: ";
            cin >> bet;
            cout << endl;
            if (bet <= bank_roll)
                break;
            else {
                cout << "You can't bet more than your bank roll" << endl;
            }
        }
    }

    int die1 = die();
    int die2 = die();
    int sum = die1 + die2;
    int point;

    // check for win
    if (sum == 7 || sum == 11) 
        win = true;
    else if (sum == 2 || sum == 3 || sum == 12)
        win = false;
    else {
        point = sum;
        while (true) {
            die1 = die();
            die2 = die();

            cout << "DIE 1: " << die1 << endl;
            cout << "DIE 2: " << die2 << endl;

            sum = die1 + die2;

            if (sum == 7) {
                win = false;
                break;
            }
            else if (sum == point) {
                win = true;
                break;
            }
        }
    }

    checkWin(win, bank_roll, bet);

}

int main() {

    char ans;
    bool done = false;
    int bank_roll = 100;

    cout << endl << "CRAPS DICE GAME" << endl;
    cout << "Bank Roll: $" << bank_roll << endl;

    while ( ! done ) {

        playGame(bank_roll);

        if (bank_roll > 0) {
            cout << "Play Again (Y/N)? ";
            cin >> ans; 
            cout << endl;
            ans = toupper(ans);
            (ans == 'N') ? done = true : done = false;
        }
        else {
            cout << "Game Over" << endl;
            cout << "You ran out of credits" << endl;
            break;
        }
            
    }

    return 0;
}