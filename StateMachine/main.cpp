#include <iostream>
#include <vector>

class MealyMachine {
public:
    MealyMachine() : currentState(0) {}

    void processInput(bool input1, bool input2) {
        int inputIndex = input1 * 2 + input2;
        currentState = transitionTable[currentState][inputIndex];
        output1 = outputTable[currentState][inputIndex][0];
        output2 = outputTable[currentState][inputIndex][1];
    }

    void printState() const {
        std::cout << "Current State: " << currentState << std::endl;
    }

    void printOutput() const {
        std::cout << "Output: " << output1 << ", " << output2 << std::endl;
    }

private:
    int currentState;
    bool output1;
    bool output2;

    std::vector<std::vector<int>> transitionTable = {
        {1, 2, 3, 0},
        {2, 3, 0, 1},
        {3, 0, 1, 2},
        {0, 1, 2, 3}
    };

    std::vector<std::vector<std::vector<bool>>> outputTable = {
        {{false, true}, {true, false}, {true, true}, {false, false}},
        {{true, false}, {true, true}, {false, false}, {false, true}},
        {{true, true}, {false, false}, {false, true}, {true, false}},
        {{false, false}, {false, true}, {true, false}, {true, true}}
    };
};

int main() {
    MealyMachine mealyMachine;

    bool input1, input2;

    input1 = true; input2 = false;

    std::cout << "Input: " << input1 << ", " << input2 << std::endl;
    mealyMachine.processInput(input1, input2);
    mealyMachine.printState();
    mealyMachine.printOutput();

    std::cout << std::endl;

    input1 = false; input2 = true;
    std::cout << "Input: " << input1 << ", " << input2 << std::endl;
    mealyMachine.processInput(input1, input2);
    mealyMachine.printState();
    mealyMachine.printOutput();

    std::cout << std::endl;

    input1 = false; input2 = false;
    std::cout << "Input: " << input1 << ", " << input2 << std::endl;
    mealyMachine.processInput(input1, input2);
    mealyMachine.printState();
    mealyMachine.printOutput();

    std::cout << std::endl;

    input1 = false; input2 = true;
    std::cout << "Input: " << input1 << ", " << input2 << std::endl;
    mealyMachine.processInput(input1, input2);
    mealyMachine.printState();
    mealyMachine.printOutput();

    return 0;
}