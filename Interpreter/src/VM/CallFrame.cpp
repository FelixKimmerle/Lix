#include "CallFrame.hpp"

CallFrame::CallFrame(ObjFunction *p_function, unsigned int p_stack_offset) : function(p_function), stack_offset(p_stack_offset)
{
    m_iterInstructionPointer = p_function->getChunk()->begin();
}

CallFrame::~CallFrame()
{
}

ObjFunction *CallFrame::getFunction()
{
    return function;
}

unsigned int CallFrame::get_offset()
{
    return stack_offset;
}

void CallFrame::jump(unsigned int offset)
{
    m_iterInstructionPointer += offset;
}
void CallFrame::loop(unsigned int offset)
{
    m_iterInstructionPointer -= offset;
}

uint8_t CallFrame::read_instruction()
{
    return *m_iterInstructionPointer++;
}

void CallFrame::disassemble()
{
    function->getChunk()->disassembleInstruction(std::distance(function->getChunk()->begin(), m_iterInstructionPointer));
}
