#pragma once
#include "Chunk.hpp"
#include <stack>
#include "CallFrame.hpp"

#define DEBUG_TRACE_EXECUTION
class Vm
{
public:
    enum InterpretResult
    {
        INTERPRET_OK,
        INTERPRET_COMPILE_ERROR,
        INTERPRET_RUNTIME_ERROR
    };

private:
    inline uint8_t readByte();

    template <class T>
    inline void pushConstant();
    template <class T>
    inline void pushConstantLong();

    template <class T>
    inline void BinaryAdd();
    template <class T>
    inline void BinarySub();
    template <class T>
    inline void BinaryMul();
    template <class T>
    inline void BinaryDiv();

    template <class F, class T>
    inline void cast();

    template <class T>
    inline void isGreater();

    template <class T>
    inline void isEqual();

    template <class T>
    inline void isLess();

    template <class T>
    inline void negate();

    template <class T>
    inline void isTrue();

    template <class T>
    inline void get();

    template <class T>
    inline void set();

    template <class T>
    inline T peek();

    template <class T>
    void push(T p_Value);

    template <class T>
    inline T pop();

    inline void popMultiple(uint8_t number);

    std::vector<uint8_t> m_Stack;
    std::stack<CallFrame> m_Frames;
#ifdef DEBUG_TRACE_EXECUTION
    std::vector<LixDatatype> m_TypeStack;
#endif

public:
    Vm();
    ~Vm();
    InterpretResult interpret(ObjFunction *p_function);
};
