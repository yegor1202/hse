#include <iostream>
#include "MyPipeline.h"

int main() {

    std::cout << "MyPipeline<int>:" << std::endl;

    MyPipeline<int> intPipe;

    intPipe.addStep("Add 5", [](int x) { return x + 5; });
    intPipe.addStep("Multiply by 2", [](int x) { return x * 2; });
    intPipe.addStep("Minus 3", [](int x) { return x - 3; });

    std::cout << intPipe << std::endl;

    int value = 10;

    std::cout << "Run result: " << intPipe.run(value) << std::endl;

    auto trace = intPipe.trace(value);

    std::cout << "Trace results:" << std::endl;
    for (auto v : trace) {
        std::cout << v << std::endl;
    }


    std::cout << "\nMyPipeline<string>:" << std::endl;

    MyPipeline<std::string> strPipe;

    strPipe.addStep("Add !!!", [](std::string s) { return s + "!!!"; });
    strPipe.addStep("Add prefix", [](std::string s) { return "Hello " + s; });
    strPipe.addStep("Add suffix", [](std::string s) { return s + " :)"; });

    std::string text = "World";

    std::cout << "Result: " << strPipe.run(text) << std::endl;


    std::cout << "\nException demo:" << std::endl;

    try {
        intPipe.removeStep(100);
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    std::cin.get();
    return 0;
}