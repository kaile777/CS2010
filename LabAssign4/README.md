Name: Kaile Jones
Assignment #4

DETAILS:
This project simulates a game of Craps. In this game, the player starts with a bank roll of 100 credits.
The player may place a bet with their credits. With each turn, the player throws 2, 6-sided die. 
If the sum of the two die equals 7 or 11, the player wins the game, and earns their bet.
If the sum of the two die equals 2, 3 or 12, the player loses the game, and loses their bet.
If none of the two above scenarios occur, the sum of the die roll now equals the players "point".
From now on, the player will keep rolling. If during a roll, the player rolls 7, they lose. 
If the player rolls their point before rolling a 7, the player wins, earning their bet.

BUILD:
Developed using windows.
There is one .cpp file in this folder that needs to be compiled.
I used GNU G++.
    "g++ -o main main.cpp" or "g++ main.cpp" and launch the exe file that shows.

HOW-TO:
When you compile the program, find the executable and launch it by typing the exe file name.
Once opened. The program will diplay the name of the game, with your bankroll underneath. 
The bank roll should be set to $100.
You will then be prompted to enter a bet. This bet must be less than or equal to your bankroll.
If your bet is greater than your bankroll, you will be prompted to enter a new bet.
Once you place your bet, the program will automatically roll your two die, and display 
the value for each die. These values are then summed, and their values are used to 
determine if you won, lost, or need to keep rolling. The Program automatically rolls the die for you,
and will continue doing so until there is an outcome. If your bankroll reaches $0, the game will 
end and the program will terminate. 
At any point throughout the game, you may decide to discontinue playing. When you press "n" or "N" to
quit, the program will terminate and your progress will be lost. The next time the program launches,
the bankroll will be reset.

LIMITATIONS:
If player decides to quit the game at any point, their current progress will be lost.
