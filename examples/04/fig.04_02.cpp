// fig04_02.cpp
// Simulating the dice game craps.

// Game Rules:
// 1. The player rolls two six-sided dice and their values are added together.
// 2. On the first roll:
//    - A total of 7 or 11 is an immediate win.
//    - A total of 2, 3, or 12 is an immediate loss.
//    - Any other total becomes the player's "point" and the game continues.
// 3. If a point is established:
//    - The player continues rolling the two dice.
//    - If the player rolls the same point again before rolling a 7, the player wins.
//    - If the player rolls a 7 before making the point, the player loses.
// 4. After each roll, the program displays the values of both dice and their sum.
// 5. At the end of the game, the program displays whether the player wins or loses.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tuple>

enum class GameStatus { WON, LOST, CONTINUE };

/*
// Roll two dice and return their face values as a tuple.
std::tuple<int, int> rollDice() {
    int die1 = (rand() % 6) + 1;
    int die2 = (rand() % 6) + 1;
    return std::make_tuple(die1, die2);
}

// Display one roll of the two dice.
void displayDice(const std::tuple<int, int>& dice) {
    int die1 = std::get<0>(dice);
    int die2 = std::get<1>(dice);
    std::cout << "Player rolled " << die1 << " + " << die2
               << " = " << (die1 + die2) << '\n';
}
*/

struct DiceRoll{
    int die1, die2; 

    int sumDie() const {return die1 + die2; }
};

DiceRoll rollDice(){
    int die1 = (rand() % 6 ) + 1; 
    int die2 = (rand() % 6 ) + 1; 
    return DiceRoll{die1, die2}; 
}


void displayDice(const DiceRoll& dice) {
    std::cout << "Player rolled " << dice.die1 << " + " << dice.die2 << " = " << dice.sumDie() << std::endl;  
}



int main() {
     // returns the current time as a number -> time_t -> cast to unsigned int -> seed
    srand(static_cast<unsigned int>(time(nullptr)));

    auto dieValues = rollDice();  // first roll
    displayDice(dieValues);

    // determine game status and point, based on first roll
    // int sumOfDice = std::get<0>(dieValues) + std::get<1>(dieValues);

    int sumOfDice = dieValues.sumDie(); 
    GameStatus gameStatus{};
    int myPoint = 0;

    switch (sumOfDice) {
        case 7:
        case 11:  // win
            gameStatus = GameStatus::WON;
            break;
        case 2:
        case 3:
        case 12:  // lose
            gameStatus = GameStatus::LOST;
            break;
        default:  // remember point
            gameStatus = GameStatus::CONTINUE;
            myPoint = sumOfDice;
            std::cout << "Point is " << myPoint << '\n';
            break;
    }

    // continue rolling until player wins or loses
    while (gameStatus == GameStatus::CONTINUE) {
        dieValues = rollDice();
        displayDice(dieValues);
        //sumOfDice = std::get<0>(dieValues) + std::get<1>(dieValues);
        sumOfDice = dieValues.sumDie();

        if (sumOfDice == myPoint) {  // win by making point
            gameStatus = GameStatus::WON;
        } else if (sumOfDice == 7) {  // lose by rolling 7
            gameStatus = GameStatus::LOST;
        }
    }

    // display "wins" or "loses" message
    std::cout << (gameStatus == GameStatus::WON ? "Player wins" : "Player loses") << '\n';
}
