#include <iostream>
#include <vector>

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

int main() {
    MealyMachine mealyMachine;

    bool input1, input2, input3;

    input1 = true; input2 = false; input3 = true;

    std::cout << "Input: " << input1 << ", " << input2 << ", " << input3 << std::endl;
    mealyMachine.processInput(input1, input2, input3);
    mealyMachine.printState();

    std::cout << std::endl;

    input1 = false; input2 = true; input3 = false;
    std::cout << "Input: " << input1 << ", " << input2 << ", " << input3 << std::endl;
    mealyMachine.processInput(input1, input2, input3);
    mealyMachine.printState();

    std::cout << std::endl;

    input1 = false; input2 = false; input3 = true;
    std::cout << "Input: " << input1 << ", " << input2 << ", " << input3 << std::endl;
    mealyMachine.processInput(input1, input2, input3);
    mealyMachine.printState();

    std::cout << std::endl;

    input1 = false; input2 = false; input3 = false;
    std::cout << "Input: " << input1 << ", " << input2 << ", " << input3 << std::endl;
    mealyMachine.processInput(input1, input2, input3);
    mealyMachine.printState();

    return 0;
}