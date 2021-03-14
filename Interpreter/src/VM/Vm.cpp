#include "Vm.hpp"
#include <iostream>
#include <array>

inline uint8_t Vm::readByte()
{
	return m_Frames.top().read_instruction();
}

template <class T>
void Vm::push(T p_Value)
{
#ifdef DEBUG_TRACE_EXECUTION
	if (std::is_same<T, Lix_Bool>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Bool);
	}
	else if (std::is_same<T, Lix_Byte>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Byte);
	}
	else if (std::is_same<T, Lix_Double>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Double);
	}
	else if (std::is_same<T, Lix_Float>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Float);
	}
	else if (std::is_same<T, Lix_Int>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Int);
	}
	else if (std::is_same<T, Lix_LongInt>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_LongInt);
	}
	else if (std::is_same<T, Lix_ShortInt>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_ShortInt);
	}
	else if (std::is_same<T, Lix_Func>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_FUNC);
	}
#endif
	uint8_t *data = reinterpret_cast<uint8_t *>(&p_Value);
	std::copy(data, data + sizeof(T), std::back_inserter(m_Stack));
}

template <>
void Vm::push(Lix_Bool p_Value)
{
#ifdef DEBUG_TRACE_EXECUTION
	m_TypeStack.push_back(LixDatatype::LD_Bool);
#endif

	m_Stack.push_back(static_cast<uint8_t>(p_Value));
}

template <class T>
inline T Vm::pop()
{
#ifdef DEBUG_TRACE_EXECUTION
	m_TypeStack.pop_back();
#endif
	T tmp = *reinterpret_cast<T *>(&m_Stack[0] + m_Stack.size() - sizeof(T));
	for (size_t i = 0; i < sizeof(T); i++)
	{
		m_Stack.pop_back();
	}
	return tmp;
}

inline void Vm::popMultiple(uint8_t number)
{
	m_Stack.erase(m_Stack.end() - number, m_Stack.end());
#ifdef DEBUG_TRACE_EXECUTION
	unsigned int size = 0;
	while (size < number)
	{
		size += getSize(m_TypeStack.back());
		m_TypeStack.pop_back();
	}

#endif
}

template <>
inline Lix_Bool Vm::pop()
{
#ifdef DEBUG_TRACE_EXECUTION
	m_TypeStack.pop_back();
#endif
	Lix_Bool tmp = static_cast<Lix_Bool>(m_Stack.back());
	m_Stack.pop_back();
	return tmp;
}

template <class T>
inline void Vm::pushConstant()
{
#ifdef DEBUG_TRACE_EXECUTION
	if (std::is_same<T, Lix_Bool>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Bool);
	}
	else if (std::is_same<T, Lix_Byte>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Byte);
	}
	else if (std::is_same<T, Lix_Double>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Double);
	}
	else if (std::is_same<T, Lix_Float>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Float);
	}
	else if (std::is_same<T, Lix_Int>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Int);
	}
	else if (std::is_same<T, Lix_LongInt>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_LongInt);
	}
	else if (std::is_same<T, Lix_ShortInt>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_ShortInt);
	}
	else if (std::is_same<T, Lix_Func>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_FUNC);
	}
#endif
	const uint8_t *data = m_Frames.top().getFunction()->getChunk()->getConstant(readByte());
	std::copy(data, data + sizeof(T), std::back_inserter(m_Stack));
}
template <class T>
inline void Vm::pushConstantLong()
{
#ifdef DEBUG_TRACE_EXECUTION
	if (std::is_same<T, Lix_Bool>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Bool);
	}
	else if (std::is_same<T, Lix_Byte>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Byte);
	}
	else if (std::is_same<T, Lix_Double>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Double);
	}
	else if (std::is_same<T, Lix_Float>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Float);
	}
	else if (std::is_same<T, Lix_Int>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_Int);
	}
	else if (std::is_same<T, Lix_LongInt>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_LongInt);
	}
	else if (std::is_same<T, Lix_ShortInt>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_ShortInt);
	}
	else if (std::is_same<T, Lix_Func>::value)
	{
		m_TypeStack.push_back(LixDatatype::LD_FUNC);
	}
#endif
	uint8_t a = readByte();
	uint8_t b = readByte();
	uint16_t offset = (a | (b << 8));
	const uint8_t *data = m_Frames.top().getFunction()->getChunk()->getConstant(readByte());
	std::copy(data, data + sizeof(T), std::back_inserter(m_Stack));
}

template <class T>
inline void Vm::BinaryAdd()
{
	T a = pop<T>();
	T b = pop<T>();
	push<T>(a + b);
}
template <class T>
inline void Vm::BinarySub()
{
	T a = pop<T>();
	T b = pop<T>();
	push<T>(b - a);
}
template <class T>
inline void Vm::BinaryMul()
{
	T a = pop<T>();
	T b = pop<T>();
	push<T>(a * b);
}
template <class T>
inline void Vm::BinaryDiv()
{
	T a = pop<T>();
	T b = pop<T>();
	push<T>(b / a);
}

template <class F, class T>
inline void Vm::cast()
{
	F tmp = pop<F>();
	push<T>(static_cast<T>(tmp));
}

template <class T>
inline void Vm::isGreater()
{
	T a = pop<T>();
	T b = pop<T>();
	push<Lix_Bool>(b > a);
}

template <class T>
inline void Vm::isEqual()
{
	T a = pop<T>();
	T b = pop<T>();
	push<Lix_Bool>(a == b);
}

template <class T>
inline void Vm::isLess()
{
	T a = pop<T>();
	T b = pop<T>();
	push<Lix_Bool>(b < a);
}

template <class T>
inline void Vm::negate()
{
	T tmp = pop<T>();
	push<T>(-tmp);
}

template <>
inline void Vm::negate<Lix_Bool>()
{
	Lix_Bool tmp = pop<Lix_Bool>();
	push<Lix_Bool>(!tmp);
}

template <class T>
inline void Vm::get()
{
	uint8_t a = readByte();
	uint8_t b = readByte();
	uint16_t offset = (a | (b << 8));
	T tmp = *reinterpret_cast<T *>(&m_Stack[0] + offset + m_Frames.top().get_offset());
	push<T>(tmp);
}

template <class T>
inline void Vm::set()
{
	uint8_t a = readByte();
	uint8_t b = readByte();
	uint16_t offset = (a | (b << 8));
	T *tmp = reinterpret_cast<T *>(&m_Stack[0] + offset + m_Frames.top().get_offset());
	*tmp = peek<T>();
}

template <class T>
inline T Vm::peek()
{
	T tmp = *reinterpret_cast<T *>(&m_Stack[0] + m_Stack.size() - sizeof(T));
	return tmp;
}

template <class T>
inline void Vm::isTrue()
{
	T tmp = pop<T>();
	pop<Lix_Bool>(tmp == T(1));
}

Vm::Vm()
{
}

Vm::~Vm()
{
}
Vm::InterpretResult Vm::interpret(ObjFunction *p_function)
{
	m_Frames.emplace(p_function);

	for (;;)
	{
#ifdef DEBUG_TRACE_EXECUTION
		std::cout << "          ";
		unsigned int counter = 0;
		for (auto &&item : m_TypeStack)
		{
			switch (item)
			{
			case LixDatatype::LD_Bool:
				std::cout << "bool[" << *reinterpret_cast<Lix_Bool *>(&m_Stack[0] + counter);
				counter += sizeof(Lix_Bool);
				break;
			case LixDatatype::LD_Byte:
				std::cout << "byte[" << (int)*reinterpret_cast<Lix_Byte *>(&m_Stack[0] + counter);
				counter += sizeof(Lix_Byte);
				break;
			case LixDatatype::LD_Double:
				std::cout << "double[" << *reinterpret_cast<Lix_Double *>(&m_Stack[0] + counter);
				counter += sizeof(Lix_Double);
				break;
			case LixDatatype::LD_Float:
				std::cout << "float[" << *reinterpret_cast<Lix_Float *>(&m_Stack[0] + counter);
				counter += sizeof(Lix_Float);
				break;
			case LixDatatype::LD_Int:
				std::cout << "int[" << *reinterpret_cast<Lix_Int *>(&m_Stack[0] + counter);
				counter += sizeof(Lix_Int);
				break;
			case LixDatatype::LD_LongInt:
				std::cout << "long[" << *reinterpret_cast<Lix_LongInt *>(&m_Stack[0] + counter);
				counter += sizeof(Lix_LongInt);
				break;
			case LixDatatype::LD_ShortInt:
				std::cout << "short[" << *reinterpret_cast<Lix_ShortInt *>(&m_Stack[0] + counter);
				counter += sizeof(Lix_ShortInt);
				break;
			case LixDatatype::LD_FUNC:
				std::cout << "func[" << (*reinterpret_cast<Lix_Func *>(&m_Stack[0] + counter))->getName();
				counter += sizeof(Lix_Func);
				break;
			}
			std::cout << "] ";
		}
		std::cout << std::endl;
		m_Frames.top().disassemble();
#endif
		Chunk::OpCode instruction = static_cast<Chunk::OpCode>(readByte());
		switch (instruction)
		{
#pragma region //constant
		case Chunk::OpCode::OP_CONSTANT_BYTE:
			pushConstant<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_CONSTANT_INT:
			pushConstant<Lix_Int>();
			break;
		case Chunk::OpCode::OP_CONSTANT_SHORTINT:
			pushConstant<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_CONSTANT_FLOAT:
			pushConstant<Lix_Float>();
			break;
		case Chunk::OpCode::OP_CONSTANT_DOUBLE:
			pushConstant<Lix_Double>();
			break;
		case Chunk::OpCode::OP_CONSTANT_LONGINT:
			pushConstant<Lix_LongInt>();
			break;
#pragma endregion //constant

#pragma region //constantlong
		case Chunk::OpCode::OP_CONSTANT_LONG_BYTE:
			pushConstantLong<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_CONSTANT_LONG_INT:
			pushConstantLong<Lix_Int>();
			break;
		case Chunk::OpCode::OP_CONSTANT_LONG_SHORTINT:
			pushConstantLong<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_CONSTANT_LONG_FLOAT:
			pushConstantLong<Lix_Float>();
			break;
		case Chunk::OpCode::OP_CONSTANT_LONG_DOUBLE:
			pushConstantLong<Lix_Double>();
			break;
		case Chunk::OpCode::OP_CONSTANT_LONG_LONGINT:
			pushConstantLong<Lix_LongInt>();
			break;
#pragma endregion //constantlong

#pragma region //add
		case Chunk::OpCode::OP_ADD_BYTE:
			BinaryAdd<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_ADD_INT:
			BinaryAdd<Lix_Int>();
			break;
		case Chunk::OpCode::OP_ADD_FLOAT:
			BinaryAdd<Lix_Float>();
			break;
		case Chunk::OpCode::OP_ADD_DOUBLE:
			BinaryAdd<Lix_Double>();
			break;
		case Chunk::OpCode::OP_ADD_SHORTINT:
			BinaryAdd<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_ADD_LONGINT:
			BinaryAdd<Lix_LongInt>();
			break;
#pragma endregion //add

#pragma region //subtract
		case Chunk::OpCode::OP_SUBTRACT_BYTE:
			BinarySub<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_SUBTRACT_INT:
			BinarySub<Lix_Int>();
			break;
		case Chunk::OpCode::OP_SUBTRACT_FLOAT:
			BinarySub<Lix_Float>();
			break;
		case Chunk::OpCode::OP_SUBTRACT_DOUBLE:
			BinarySub<Lix_Double>();
			break;
		case Chunk::OpCode::OP_SUBTRACT_SHORTINT:
			BinarySub<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_SUBTRACT_LONGINT:
			BinarySub<Lix_LongInt>();
			break;
#pragma endregion //subtract

#pragma region //multiply
		case Chunk::OpCode::OP_MULTIPLY_BYTE:
			BinaryMul<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_MULTIPLY_INT:
			BinaryMul<Lix_Int>();
			break;
		case Chunk::OpCode::OP_MULTIPLY_FLOAT:
			BinaryMul<Lix_Float>();
			break;
		case Chunk::OpCode::OP_MULTIPLY_DOUBLE:
			BinaryMul<Lix_Double>();
			break;
		case Chunk::OpCode::OP_MULTIPLY_SHORTINT:
			BinaryMul<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_MULTIPLY_LONGINT:
			BinaryMul<Lix_LongInt>();
			break;
#pragma endregion //multiply

#pragma region //divide
		case Chunk::OpCode::OP_DIVIDE_BYTE:
			BinaryDiv<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_DIVIDE_INT:
			BinaryDiv<Lix_Int>();
			break;
		case Chunk::OpCode::OP_DIVIDE_FLOAT:
			BinaryDiv<Lix_Float>();
			break;
		case Chunk::OpCode::OP_DIVIDE_DOUBLE:
			BinaryDiv<Lix_Double>();
			break;
		case Chunk::OpCode::OP_DIVIDE_SHORTINT:
			BinaryDiv<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_DIVIDE_LONGINT:
			BinaryDiv<Lix_LongInt>();
			break;
#pragma endregion //divide

#pragma region //cast

		case Chunk::OpCode::OP_CAST_BYTE_SHORTINT:
			cast<Lix_Byte, Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_CAST_BYTE_INT:
			cast<Lix_Byte, Lix_Int>();
			break;
		case Chunk::OpCode::OP_CAST_BYTE_FLOAT:
			cast<Lix_Byte, Lix_Float>();
			break;
		case Chunk::OpCode::OP_CAST_BYTE_DOUBLE:
			cast<Lix_Byte, Lix_Double>();
			break;
		case Chunk::OpCode::OP_CAST_BYTE_LONGINT:
			cast<Lix_Byte, Lix_LongInt>();
			break;

		case Chunk::OpCode::OP_CAST_SHORTINT_BYTE:
			cast<Lix_ShortInt, Lix_Byte>();
			break;
		case Chunk::OpCode::OP_CAST_SHORTINT_INT:
			cast<Lix_ShortInt, Lix_Int>();
			break;
		case Chunk::OpCode::OP_CAST_SHORTINT_FLOAT:
			cast<Lix_ShortInt, Lix_Float>();
			break;
		case Chunk::OpCode::OP_CAST_SHORTINT_DOUBLE:
			cast<Lix_ShortInt, Lix_Double>();
			break;
		case Chunk::OpCode::OP_CAST_SHORTINT_LONGINT:
			cast<Lix_ShortInt, Lix_LongInt>();
			break;

		case Chunk::OpCode::OP_CAST_INT_BYTE:
			cast<Lix_Int, Lix_Byte>();
			break;
		case Chunk::OpCode::OP_CAST_INT_FLOAT:
			cast<Lix_Int, Lix_Float>();
			break;
		case Chunk::OpCode::OP_CAST_INT_DOUBLE:
			cast<Lix_Int, Lix_Double>();
			break;
		case Chunk::OpCode::OP_CAST_INT_LONGINT:
			cast<Lix_Int, Lix_LongInt>();
			break;
		case Chunk::OpCode::OP_CAST_INT_SHORTINT:
			cast<Lix_Int, Lix_ShortInt>();
			break;

		case Chunk::OpCode::OP_CAST_FLOAT_BYTE:
			cast<Lix_Float, Lix_Byte>();
			break;
		case Chunk::OpCode::OP_CAST_FLOAT_INT:
			cast<Lix_Float, Lix_Int>();
			break;
		case Chunk::OpCode::OP_CAST_FLOAT_DOUBLE:
			cast<Lix_Float, Lix_Double>();
			break;
		case Chunk::OpCode::OP_CAST_FLOAT_LONGINT:
			cast<Lix_Float, Lix_LongInt>();
			break;
		case Chunk::OpCode::OP_CAST_FLOAT_SHORTINT:
			cast<Lix_Float, Lix_ShortInt>();
			break;

		case Chunk::OpCode::OP_CAST_DOUBLE_BYTE:
			cast<Lix_Double, Lix_Byte>();
			break;
		case Chunk::OpCode::OP_CAST_DOUBLE_INT:
			cast<Lix_Double, Lix_Int>();
			break;
		case Chunk::OpCode::OP_CAST_DOUBLE_FLOAT:
			cast<Lix_Double, Lix_Float>();
			break;
		case Chunk::OpCode::OP_CAST_DOUBLE_LONGINT:
			cast<Lix_Double, Lix_LongInt>();
			break;
		case Chunk::OpCode::OP_CAST_DOUBLE_SHORTINT:
			cast<Lix_Double, Lix_ShortInt>();
			break;

		case Chunk::OpCode::OP_CAST_LONGINT_BYTE:
			cast<Lix_LongInt, Lix_Byte>();
			break;
		case Chunk::OpCode::OP_CAST_LONGINT_INT:
			cast<Lix_LongInt, Lix_Int>();
			break;
		case Chunk::OpCode::OP_CAST_LONGINT_FLOAT:
			cast<Lix_LongInt, Lix_Float>();
			break;
		case Chunk::OpCode::OP_CAST_LONGINT_DOUBLE:
			cast<Lix_LongInt, Lix_Double>();
			break;
		case Chunk::OpCode::OP_CAST_LONGINT_SHORTINT:
			cast<Lix_LongInt, Lix_ShortInt>();
			break;

#pragma endregion //cast

#pragma region //compare

		case Chunk::OpCode::OP_EQUAL_BOOL:
			isEqual<Lix_Bool>();
			break;
		case Chunk::OpCode::OP_EQUAL_BYTE:
			isEqual<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_EQUAL_SHORTINT:
			isEqual<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_EQUAL_INT:
			isEqual<Lix_Int>();
			break;
		case Chunk::OpCode::OP_EQUAL_FLOAT:
			isEqual<Lix_Float>();
			break;
		case Chunk::OpCode::OP_EQUAL_DOUBLE:
			isEqual<Lix_Double>();
			break;
		case Chunk::OpCode::OP_EQUAL_LONGINT:
			isEqual<Lix_LongInt>();
			break;

		case Chunk::OpCode::OP_LESS_BYTE:
			isLess<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_LESS_SHORTINT:
			isLess<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_LESS_INT:
			isLess<Lix_Int>();
			break;
		case Chunk::OpCode::OP_LESS_FLOAT:
			isLess<Lix_Float>();
			break;
		case Chunk::OpCode::OP_LESS_DOUBLE:
			isLess<Lix_Double>();
			break;
		case Chunk::OpCode::OP_LESS_LONGINT:
			isLess<Lix_LongInt>();
			break;

		case Chunk::OpCode::OP_GREATER_BYTE:
			isGreater<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_GREATER_SHORTINT:
			isGreater<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_GREATER_INT:
			isGreater<Lix_Int>();
			break;
		case Chunk::OpCode::OP_GREATER_FLOAT:
			isGreater<Lix_Float>();
			break;
		case Chunk::OpCode::OP_GREATER_DOUBLE:
			isGreater<Lix_Double>();
			break;
		case Chunk::OpCode::OP_GREATER_LONGINT:
			isGreater<Lix_LongInt>();
			break;

#pragma endregion //compare

#pragma region //negate

		case Chunk::OpCode::OP_NEGATE_BOOL:
			negate<Lix_Bool>();
			break;
		case Chunk::OpCode::OP_NEGATE_BYTE:
			negate<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_NEGATE_SHORTINT:
			negate<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_NEGATE_INT:
			negate<Lix_Int>();
			break;
		case Chunk::OpCode::OP_NEGATE_FLOAT:
			negate<Lix_Float>();
			break;
		case Chunk::OpCode::OP_NEGATE_DOUBLE:
			negate<Lix_Double>();
			break;
		case Chunk::OpCode::OP_NEGATE_LONGINT:
			negate<Lix_LongInt>();
			break;

#pragma endregion //negate

#pragma region //istrue

		case Chunk::OpCode::OP_ISTRUE_BYTE:
			negate<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_ISTRUE_SHORTINT:
			negate<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_ISTRUE_INT:
			negate<Lix_Int>();
			break;
		case Chunk::OpCode::OP_ISTRUE_FLOAT:
			negate<Lix_Float>();
			break;
		case Chunk::OpCode::OP_ISTRUE_DOUBLE:
			negate<Lix_Double>();
			break;
		case Chunk::OpCode::OP_ISTRUE_LONGINT:
			negate<Lix_LongInt>();
			break;

#pragma endregion //istrue

#pragma region //pop

		case Chunk::OpCode::OP_POP_BOOL:
			pop<Lix_Bool>();
			break;
		case Chunk::OpCode::OP_POP_BYTE:
			pop<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_POP_SHORTINT:
			pop<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_POP_INT:
			pop<Lix_Int>();
			break;
		case Chunk::OpCode::OP_POP_FLOAT:
			pop<Lix_Float>();
			break;
		case Chunk::OpCode::OP_POP_DOUBLE:
			pop<Lix_Double>();
			break;
		case Chunk::OpCode::OP_POP_LONGINT:
			pop<Lix_LongInt>();
			break;
		case Chunk::OpCode::OP_POP_FUNC:
			pop<Lix_Func>();
			break;
		case Chunk::OpCode::OP_POP:
			popMultiple(readByte());
			break;

#pragma endregion //pop

#pragma region //print

		case Chunk::OpCode::OP_PRINT_BOOL:
			std::cout << pop<Lix_Bool>() << std::endl;
			break;
		case Chunk::OpCode::OP_PRINT_BYTE:
			std::cout << (int)pop<Lix_Byte>() << std::endl;
			break;
		case Chunk::OpCode::OP_PRINT_SHORTINT:
			std::cout << pop<Lix_ShortInt>() << std::endl;
			break;
		case Chunk::OpCode::OP_PRINT_INT:
			std::cout << pop<Lix_Int>() << std::endl;
			break;
		case Chunk::OpCode::OP_PRINT_FLOAT:
			std::cout << pop<Lix_Float>() << std::endl;
			break;
		case Chunk::OpCode::OP_PRINT_DOUBLE:
			std::cout << pop<Lix_Double>() << std::endl;
			break;
		case Chunk::OpCode::OP_PRINT_LONGINT:
			std::cout << pop<Lix_LongInt>() << std::endl;
			break;

#pragma endregion //print

#pragma region //get

		case Chunk::OpCode::OP_GET_BOOL:
			get<Lix_Bool>();
			break;
		case Chunk::OpCode::OP_GET_BYTE:
			get<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_GET_SHORTINT:
			get<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_GET_INT:
			get<Lix_Int>();
			break;
		case Chunk::OpCode::OP_GET_FLOAT:
			get<Lix_Float>();
			break;
		case Chunk::OpCode::OP_GET_DOUBLE:
			get<Lix_Double>();
			break;
		case Chunk::OpCode::OP_GET_LONGINT:
			get<Lix_LongInt>();
			break;
		case Chunk::OpCode::OP_GET_FUNC:
			get<Lix_Func>();
			break;

#pragma endregion //get

#pragma region //set

		case Chunk::OpCode::OP_SET_BOOL:
			set<Lix_Bool>();
			break;
		case Chunk::OpCode::OP_SET_BYTE:
			set<Lix_Byte>();
			break;
		case Chunk::OpCode::OP_SET_SHORTINT:
			set<Lix_ShortInt>();
			break;
		case Chunk::OpCode::OP_SET_INT:
			set<Lix_Int>();
			break;
		case Chunk::OpCode::OP_SET_FLOAT:
			set<Lix_Float>();
			break;
		case Chunk::OpCode::OP_SET_DOUBLE:
			set<Lix_Double>();
			break;
		case Chunk::OpCode::OP_SET_LONGINT:
			set<Lix_LongInt>();
			break;

#pragma endregion //set

#pragma region //zero

		case Chunk::OpCode::OP_ZERO_BYTE:
			push<Lix_Byte>(0);
			break;
		case Chunk::OpCode::OP_ZERO_SHORTINT:
			push<Lix_ShortInt>(0);
			break;
		case Chunk::OpCode::OP_ZERO_INT:
			push<Lix_Int>(0);
			break;
		case Chunk::OpCode::OP_ZERO_FLOAT:
			push<Lix_Float>(0);
			break;
		case Chunk::OpCode::OP_ZERO_DOUBLE:
			push<Lix_Double>(0);
			break;
		case Chunk::OpCode::OP_ZERO_LONGINT:
			push<Lix_LongInt>(0);
			break;

#pragma endregion //zero

		case Chunk::OpCode::OP_TRUE:
			push<Lix_Bool>(true);
			break;

		case Chunk::OpCode::OP_FALSE:
			push<Lix_Bool>(false);
			break;

		case Chunk::OpCode::OP_PUSH_FUNC:
			pushConstant<Lix_Func>();
			break;

		case Chunk::OpCode::OP_CALL_FUNC:
		{
			Lix_Func function = pop<Lix_Func>();
			uint8_t offset = readByte();
			m_Frames.emplace(function, offset);
			break;
		}

		case Chunk::OpCode::OP_JUMP_IF_FALSE:
		{
			Lix_Bool condition = peek<Lix_Bool>();
			if (!condition)
			{
				uint8_t a = readByte();
				uint8_t b = readByte();
				uint16_t offset = (a | (b << 8));
				m_Frames.top().jump(offset);
			}
			else
			{
				m_Frames.top().jump(2);
			}
		}
		break;

		case Chunk::OpCode::OP_JUMP:
		{
			uint8_t a = readByte();
			uint8_t b = readByte();
			uint16_t offset = (a | (b << 8));
			m_Frames.top().jump(offset);
		}
		break;

		case Chunk::OpCode::OP_LOOP:
		{
			uint8_t a = readByte();
			uint8_t b = readByte();
			uint16_t offset = (a | (b << 8));
			m_Frames.top().loop(offset);
		}
		break;

		case Chunk::OpCode::OP_RETURN:
			//return INTERPRET_OK;
			//popMultiple(m_Stack.size() - m_Frames.top().get_offset());
			m_Frames.pop();
			if (m_Frames.size() == 0)
			{
				std::cout << "Return: " << pop<Lix_Int>() << std::endl;
				return INTERPRET_OK;
			}
			break;
		}
	}
}
