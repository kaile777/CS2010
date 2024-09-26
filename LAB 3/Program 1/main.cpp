#include <iostream>

using namespace std;

extern const int given; 
extern int quarters, dimes, nickels, pennies,
    cost, change;

int main() {

    // User inputs the cost of the item to purchase
    cout << "\nEnter a positive integer (<= 100): ";
    cin >> cost;
    cout << endl;

    change = given - cost;

    // Prints formatted change to give
    cout << "\nCHANGE: $";
    (cost == 0) ? cout << "1.00" : cout << "0." << change;
    cout << endl << endl;

    /*
    Loop ensures that the least amount of total coins are used
    by starting from quarters, and working way down to nickels.
    */
    while (change != 0) {
        if ((change - 25) >= 0) {
            change -= 25;
            quarters++;
        }
        else if ((change - 10) >= 0) {
            change -= 10;
            dimes++;
        }
        else if ((change - 5) >= 0) {
            change -= 5;
            nickels++;
        }
        else if ((change - 1) >= 0) {
            change -= 1;
            pennies++;
        }
        else 
            break;
    }

    // Summary of total coins given in each category as change.
    cout << "Quarters : " << quarters << endl;
    cout << "Dimes    : " << dimes << endl;
    cout << "Nickels  : " << nickels << endl;
    cout << "Pennies  : " << pennies << endl;

    return 0;
    
}