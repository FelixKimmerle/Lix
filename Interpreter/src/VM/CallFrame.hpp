#pragma once
#include "../ObjFunction.hpp"

class CallFrame
{
private:
    ObjFunction *function;
    std::vector<uint8_t>::const_iterator m_iterInstructionPointer;
    unsigned int stack_offset;
public:
    CallFrame(ObjFunction *p_function, unsigned int p_stack_offset = 0);
    ~CallFrame();
    ObjFunction* getFunction();
    unsigned int get_offset();
    void jump(unsigned int offset);
    void loop(unsigned int offset);
    uint8_t read_instruction();
    void disassemble();
};
