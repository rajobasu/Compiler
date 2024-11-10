#include <iostream>
#include <sysexits.h>
#include <fstream>
#include <filesystem>
#include "scanner.h"
#include "errors.h"
#include "Parser.h"
#include "ExpressionVisitors.h"

using namespace std;

void run(const string& content) {
    Scanner scanner(content);
    auto tokens = scanner.scanTokens();

    Parser parser(tokens);
    auto expression = parser.parse();
    if (error_handling::hadError) return;

    ExpressionEvaluator evaluator;
    evaluator.interpret(*expression);
}



void runFile(const filesystem::path& file_path) {
    ifstream fin;
    fin.open(file_path, ios_base::in);
    if (not fin.is_open()) {
        cout << "File Not Found : " << file_path << endl;
        return;
    }

    // load the file into a string
    fin.seekg(0, std::ios::end);
    const auto size = fin.tellg();

    std::string file_contents(size, ' ');
    fin.seekg(0);
    fin.read(&file_contents[0], size);

    // now run the file using the data
    run(file_contents);
    cout << file_contents << endl;
    if (error_handling::hadError) {
        exit(EX_DATAERR);
    }
    if (error_handling::hadRuntimeError) {
        exit(EX_SOFTWARE);
    }
}

void runPrompt() {

}


int main(int argc, char** argv) {

    if (argc > 2) {
        cout << "Usage: jlox [script.lox]" << endl;
        return EX_USAGE;
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }
    return 0;
}
