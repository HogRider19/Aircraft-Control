#include <iostream>
#include <vector>
#include <sstream>

class MealyMachine {
public:
    MealyMachine() : currentState(0) {}

    void processInput(bool input1, bool input2, bool input3) {
        int inputIndex = input1 + input2 + input3;
        currentState = transitionTable[inputIndex][currentState];
    }

    void printState() const {
        std::cout << "Current State: " << currentState << std::endl;
    }

private:
    int currentState;

    std::vector<std::vector<int>> transitionTable = {
        {1, 2, 3, 0, 5, 4},
        {2, 3, 0, 1, 4, 5},
        {3, 5, 1, 4, 2, 0},
        {4, 5, 2, 3, 0, 1}
    };
};


bool callNextState(MealyMachine& mealyMachine)
{
    std::string input;

    std::cout << "Inputs (Example: 0 1 1): ";
    std::getline(std::cin, input);

    std::istringstream iss(input);
    bool input1, input2, input3;

    if (!(iss >> input1 >> input2 >> input3) ||
        (input1 != 0 && input1 != 1) ||
        (input2 != 0 && input2 != 1) ||
        (input3 != 0 && input3 != 1)) {
        std::cout << "Invalid input" << std::endl;
        return true;
    }


    mealyMachine.processInput(input1, input2, input3);
    mealyMachine.printState();

    return false;
};


int main() {
    MealyMachine mealyMachine;

    while (true)
    {
        bool isComplete = callNextState(mealyMachine);
        if (isComplete)
            break;
    }

    return 0;
}