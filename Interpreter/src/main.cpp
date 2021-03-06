#include <iostream>
#include <fstream>
#include <streambuf>
#include "VM/Vm.hpp"
#include "Converter.hpp"
#include "LixTypenames.hpp"
#include "Parser.hpp"
#include "Compiler.hpp"
#include "Timer.hpp"
#include "Logger.hpp"

int main()
{

    Logger logger;
    logger.set_log_level(100);
    logger.log("Logger init", Logger::Information);

    std::ifstream t("Interpreter/test.txt");
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
               std::istreambuf_iterator<char>());

    Timer timer;
    timer.reset();
    Parser parser(str, &logger);
    std::unique_ptr<BlockStmt> stmts = parser.parse();
    if (!parser.hadError())
    {
        Compiler compiler(&logger, LixDatatype::LD_Int);
        Lix_Func function = compiler.compile(*stmts.get());
        std::cout << timer.elapsed() * 1000000 << std::endl;

        function->getChunk()->disassemble("Main");
        std::cout << "============" << std::endl;
        Vm vm;
        timer.reset();
        vm.interpret(function);
        int time = timer.elapsed() * 1000000;
        std::cout << time << std::endl;
        timer.reset();
        delete function;
    }
}
