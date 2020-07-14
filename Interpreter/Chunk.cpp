#include "Chunk.hpp"
#include <iostream>
#include <iomanip>
#include "LixTypenames.hpp"
#include "Converter.hpp"
#include <sstream>
#include <string>

void Chunk::addLine(unsigned int p_uiLine)
{
	if (m_vLines.size() != 0 && m_vLines[m_vLines.size() - 1] == p_uiLine)
	{
		m_vLinesnumber[m_vLines.size() - 1]++;
	}
	else
	{
		m_vLines.push_back(p_uiLine);
		m_vLinesnumber.push_back(1);
	}
}

unsigned int Chunk::getLine(unsigned int offset) const
{
	unsigned int counter = 0;
	unsigned int index = 0;

	for (auto &number : m_vLinesnumber)
	{
		counter += number;
		if (counter > offset)
		{
			return m_vLines[index];
		}
		index++;
	}
	return -1;
}

unsigned int Chunk::disassembleInstruction(unsigned int p_uiOffset, unsigned int p_uiLine, unsigned int p_uiPrevline) const
{
	std::cout << std::setfill('0') << std::setw(4) << p_uiOffset << " ";
	if (p_uiOffset > 0 && p_uiLine == p_uiPrevline)
	{
		std::cout << "   | ";
	}
	else
	{
		std::cout << std::setfill(' ') << std::setw(4) << p_uiLine << " ";
	}

	OpCode instruction = OpCode(m_vCode[p_uiOffset]);
	switch (instruction)
	{

	case OpCode::OP_CONSTANT_BYTE:
		return constantInstruction("OP_CONSTANT_BYTE", p_uiOffset, LixDatatype::LD_Byte);
	case OpCode::OP_CONSTANT_DOUBLE:
		return constantInstruction("OP_CONSTANT_DOUBLE", p_uiOffset, LixDatatype::LD_Double);
	case OpCode::OP_CONSTANT_FLOAT:
		return constantInstruction("OP_CONSTANT_FLOAT", p_uiOffset, LixDatatype::LD_Float);
	case OpCode::OP_CONSTANT_INT:
		return constantInstruction("OP_CONSTANT_INT", p_uiOffset, LixDatatype::LD_Int);
	case OpCode::OP_CONSTANT_LONGINT:
		return constantInstruction("OP_CONSTANT_LONGINT", p_uiOffset, LixDatatype::LD_LongInt);
	case OpCode::OP_CONSTANT_SHORTINT:
		return constantInstruction("OP_CONSTANT_SHORTINT", p_uiOffset, LixDatatype::LD_ShortInt);

	case OpCode::OP_CONSTANT_LONG_BYTE:
		return longconstantInstruction("OP_CONSTANT_LONG_BYTE", p_uiOffset, LixDatatype::LD_Byte);
	case OpCode::OP_CONSTANT_LONG_DOUBLE:
		return longconstantInstruction("OP_CONSTANT_LONG_DOUBLE", p_uiOffset, LixDatatype::LD_Double);
	case OpCode::OP_CONSTANT_LONG_FLOAT:
		return longconstantInstruction("OP_CONSTANT_LONG_FLOAT", p_uiOffset, LixDatatype::LD_Float);
	case OpCode::OP_CONSTANT_LONG_INT:
		return longconstantInstruction("OP_CONSTANT_LONG_INT", p_uiOffset, LixDatatype::LD_Int);
	case OpCode::OP_CONSTANT_LONG_LONGINT:
		return longconstantInstruction("OP_CONSTANT_LONG_LONGINT", p_uiOffset, LixDatatype::LD_LongInt);
	case OpCode::OP_CONSTANT_LONG_SHORTINT:
		return longconstantInstruction("OP_CONSTANT_LONG_SHORTINT", p_uiOffset, LixDatatype::LD_ShortInt);

	case OpCode::OP_TRUE:
		return simpleInstruction("OP_TRUE", p_uiOffset);
	case OpCode::OP_FALSE:
		return simpleInstruction("OP_FALSE", p_uiOffset);

	case OpCode::OP_ADD_BYTE:
		return simpleInstruction("OP_ADD_BYTE", p_uiOffset);
	case OpCode::OP_ADD_DOUBLE:
		return simpleInstruction("OP_ADD_DOUBLE", p_uiOffset);
	case OpCode::OP_ADD_FLOAT:
		return simpleInstruction("OP_ADD_FLOAT", p_uiOffset);
	case OpCode::OP_ADD_INT:
		return simpleInstruction("OP_ADD_INT", p_uiOffset);
	case OpCode::OP_ADD_LONGINT:
		return simpleInstruction("OP_ADD_LONGINT", p_uiOffset);
	case OpCode::OP_ADD_SHORTINT:
		return simpleInstruction("OP_ADD_SHORTINT", p_uiOffset);

	case OpCode::OP_SUBTRACT_BYTE:
		return simpleInstruction("OP_SUBTRACT_BYTE", p_uiOffset);
	case OpCode::OP_SUBTRACT_DOUBLE:
		return simpleInstruction("OP_SUBTRACT_DOUBLE", p_uiOffset);
	case OpCode::OP_SUBTRACT_FLOAT:
		return simpleInstruction("OP_SUBTRACT_FLOAT", p_uiOffset);
	case OpCode::OP_SUBTRACT_INT:
		return simpleInstruction("OP_SUBTRACT_INT", p_uiOffset);
	case OpCode::OP_SUBTRACT_LONGINT:
		return simpleInstruction("OP_SUBTRACT_LONGINT", p_uiOffset);
	case OpCode::OP_SUBTRACT_SHORTINT:
		return simpleInstruction("OP_SUBTRACT_SHORTINT", p_uiOffset);

	case OpCode::OP_MULTIPLY_BYTE:
		return simpleInstruction("OP_MULTIPLY_BYTE", p_uiOffset);
	case OpCode::OP_MULTIPLY_DOUBLE:
		return simpleInstruction("OP_MULTIPLY_DOUBLE", p_uiOffset);
	case OpCode::OP_MULTIPLY_FLOAT:
		return simpleInstruction("OP_MULTIPLY_FLOAT", p_uiOffset);
	case OpCode::OP_MULTIPLY_INT:
		return simpleInstruction("OP_MULTIPLY_INT", p_uiOffset);
	case OpCode::OP_MULTIPLY_LONGINT:
		return simpleInstruction("OP_MULTIPLY_LONGINT", p_uiOffset);
	case OpCode::OP_MULTIPLY_SHORTINT:
		return simpleInstruction("OP_MULTIPLY_SHORTINT", p_uiOffset);

	case OpCode::OP_DIVIDE_BYTE:
		return simpleInstruction("OP_DIVIDE_BYTE", p_uiOffset);
	case OpCode::OP_DIVIDE_DOUBLE:
		return simpleInstruction("OP_DIVIDE_DOUBLE", p_uiOffset);
	case OpCode::OP_DIVIDE_FLOAT:
		return simpleInstruction("OP_DIVIDE_FLOAT", p_uiOffset);
	case OpCode::OP_DIVIDE_INT:
		return simpleInstruction("OP_DIVIDE_INT", p_uiOffset);
	case OpCode::OP_DIVIDE_LONGINT:
		return simpleInstruction("OP_DIVIDE_LONGINT", p_uiOffset);
	case OpCode::OP_DIVIDE_SHORTINT:
		return simpleInstruction("OP_DIVIDE_SHORTINT", p_uiOffset);

	case OpCode::OP_CAST_BYTE_SHORTINT:
		return simpleInstruction("OP_CAST_BYTE_SHORTINT", p_uiOffset);
	case OpCode::OP_CAST_BYTE_INT:
		return simpleInstruction("OP_CAST_BYTE_INT", p_uiOffset);
	case OpCode::OP_CAST_BYTE_FLOAT:
		return simpleInstruction("OP_CAST_BYTE_FLOAT", p_uiOffset);
	case OpCode::OP_CAST_BYTE_DOUBLE:
		return simpleInstruction("OP_CAST_BYTE_DOUBLE", p_uiOffset);
	case OpCode::OP_CAST_BYTE_LONGINT:
		return simpleInstruction("OP_CAST_BYTE_LONGINT", p_uiOffset);

	case OpCode::OP_CAST_SHORTINT_BYTE:
		return simpleInstruction("OP_CAST_SHORTINT_BYTE", p_uiOffset);
	case OpCode::OP_CAST_SHORTINT_INT:
		return simpleInstruction("OP_CAST_SHORTINT_INT", p_uiOffset);
	case OpCode::OP_CAST_SHORTINT_FLOAT:
		return simpleInstruction("OP_CAST_SHORTINT_FLOAT", p_uiOffset);
	case OpCode::OP_CAST_SHORTINT_DOUBLE:
		return simpleInstruction("OP_CAST_SHORTINT_DOUBLE", p_uiOffset);
	case OpCode::OP_CAST_SHORTINT_LONGINT:
		return simpleInstruction("OP_CAST_SHORTINT_LONGINT", p_uiOffset);

	case OpCode::OP_CAST_INT_BYTE:
		return simpleInstruction("OP_CAST_INT_BYTE", p_uiOffset);
	case OpCode::OP_CAST_INT_FLOAT:
		return simpleInstruction("OP_CAST_INT_FLOAT", p_uiOffset);
	case OpCode::OP_CAST_INT_DOUBLE:
		return simpleInstruction("OP_CAST_INT_DOUBLE", p_uiOffset);
	case OpCode::OP_CAST_INT_LONGINT:
		return simpleInstruction("OP_CAST_INT_LONGINT", p_uiOffset);
	case OpCode::OP_CAST_INT_SHORTINT:
		return simpleInstruction("OP_CAST_INT_SHORTINT", p_uiOffset);

	case OpCode::OP_CAST_FLOAT_BYTE:
		return simpleInstruction("OP_CAST_FLOAT_BYTE", p_uiOffset);
	case OpCode::OP_CAST_FLOAT_INT:
		return simpleInstruction("OP_CAST_FLOAT_INT", p_uiOffset);
	case OpCode::OP_CAST_FLOAT_DOUBLE:
		return simpleInstruction("OP_CAST_FLOAT_DOUBLE", p_uiOffset);
	case OpCode::OP_CAST_FLOAT_LONGINT:
		return simpleInstruction("OP_CAST_FLOAT_LONGINT", p_uiOffset);
	case OpCode::OP_CAST_FLOAT_SHORTINT:
		return simpleInstruction("OP_CAST_FLOAT_SHORTINT", p_uiOffset);

	case OpCode::OP_CAST_DOUBLE_BYTE:
		return simpleInstruction("OP_CAST_DOUBLE_BYTE", p_uiOffset);
	case OpCode::OP_CAST_DOUBLE_INT:
		return simpleInstruction("OP_CAST_DOUBLE_INT", p_uiOffset);
	case OpCode::OP_CAST_DOUBLE_FLOAT:
		return simpleInstruction("OP_CAST_DOUBLE_FLOAT", p_uiOffset);
	case OpCode::OP_CAST_DOUBLE_LONGINT:
		return simpleInstruction("OP_CAST_DOUBLE_LONGINT", p_uiOffset);
	case OpCode::OP_CAST_DOUBLE_SHORTINT:
		return simpleInstruction("OP_CAST_DOUBLE_SHORTINT", p_uiOffset);

	case OpCode::OP_CAST_LONGINT_BYTE:
		return simpleInstruction("OP_CAST_LONGINT_BYTE", p_uiOffset);
	case OpCode::OP_CAST_LONGINT_INT:
		return simpleInstruction("OP_CAST_LONGINT_INT", p_uiOffset);
	case OpCode::OP_CAST_LONGINT_FLOAT:
		return simpleInstruction("OP_CAST_LONGINT_FLOAT", p_uiOffset);
	case OpCode::OP_CAST_LONGINT_DOUBLE:
		return simpleInstruction("OP_CAST_LONGINT_DOUBLE", p_uiOffset);
	case OpCode::OP_CAST_LONGINT_SHORTINT:
		return simpleInstruction("OP_CAST_LONGINT_SHORTINT", p_uiOffset);

	case OpCode::OP_EQUAL_BOOL:
		return simpleInstruction("OP_EQUAL_BOOL", p_uiOffset);
	case OpCode::OP_EQUAL_BYTE:
		return simpleInstruction("OP_EQUAL_BYTE", p_uiOffset);
	case OpCode::OP_EQUAL_SHORTINT:
		return simpleInstruction("OP_EQUAL_SHORTINT", p_uiOffset);
	case OpCode::OP_EQUAL_INT:
		return simpleInstruction("OP_EQUAL_INT", p_uiOffset);
	case OpCode::OP_EQUAL_FLOAT:
		return simpleInstruction("OP_EQUAL_FLOAT", p_uiOffset);
	case OpCode::OP_EQUAL_DOUBLE:
		return simpleInstruction("OP_EQUAL_DOUBLE", p_uiOffset);
	case OpCode::OP_EQUAL_LONGINT:
		return simpleInstruction("OP_EQUAL_LONGINT", p_uiOffset);

	case OpCode::OP_LESS_BYTE:
		return simpleInstruction("OP_LESS_BYTE", p_uiOffset);
	case OpCode::OP_LESS_SHORTINT:
		return simpleInstruction("OP_LESS_SHORTINT", p_uiOffset);
	case OpCode::OP_LESS_INT:
		return simpleInstruction("OP_LESS_INT", p_uiOffset);
	case OpCode::OP_LESS_FLOAT:
		return simpleInstruction("OP_LESS_FLOAT", p_uiOffset);
	case OpCode::OP_LESS_DOUBLE:
		return simpleInstruction("OP_LESS_DOUBLE", p_uiOffset);
	case OpCode::OP_LESS_LONGINT:
		return simpleInstruction("OP_LESS_LONGINT", p_uiOffset);

	case OpCode::OP_GREATER_BYTE:
		return simpleInstruction("OP_GREATER_BYTE", p_uiOffset);
	case OpCode::OP_GREATER_SHORTINT:
		return simpleInstruction("OP_GREATER_SHORTINT", p_uiOffset);
	case OpCode::OP_GREATER_INT:
		return simpleInstruction("OP_GREATER_INT", p_uiOffset);
	case OpCode::OP_GREATER_FLOAT:
		return simpleInstruction("OP_GREATER_FLOAT", p_uiOffset);
	case OpCode::OP_GREATER_DOUBLE:
		return simpleInstruction("OP_GREATER_DOUBLE", p_uiOffset);
	case OpCode::OP_GREATER_LONGINT:
		return simpleInstruction("OP_GREATER_LONGINT", p_uiOffset);

	case OpCode::OP_NEGATE_BOOL:
		return simpleInstruction("OP_NEGATE_BOOL", p_uiOffset);
	case OpCode::OP_NEGATE_BYTE:
		return simpleInstruction("OP_NEGATE_BYTE", p_uiOffset);
	case OpCode::OP_NEGATE_SHORTINT:
		return simpleInstruction("OP_NEGATE_SHORTINT", p_uiOffset);
	case OpCode::OP_NEGATE_INT:
		return simpleInstruction("OP_NEGATE_INT", p_uiOffset);
	case OpCode::OP_NEGATE_FLOAT:
		return simpleInstruction("OP_NEGATE_FLOAT", p_uiOffset);
	case OpCode::OP_NEGATE_DOUBLE:
		return simpleInstruction("OP_NEGATE_DOUBLE", p_uiOffset);
	case OpCode::OP_NEGATE_LONGINT:
		return simpleInstruction("OP_NEGATE_LONGINT", p_uiOffset);

	case OpCode::OP_ISTRUE_BYTE:
		return simpleInstruction("OP_ISTRUE_BYTE", p_uiOffset);
	case OpCode::OP_ISTRUE_SHORTINT:
		return simpleInstruction("OP_ISTRUE_SHORTINT", p_uiOffset);
	case OpCode::OP_ISTRUE_INT:
		return simpleInstruction("OP_ISTRUE_INT", p_uiOffset);
	case OpCode::OP_ISTRUE_FLOAT:
		return simpleInstruction("OP_ISTRUE_FLOAT", p_uiOffset);
	case OpCode::OP_ISTRUE_DOUBLE:
		return simpleInstruction("OP_ISTRUE_DOUBLE", p_uiOffset);
	case OpCode::OP_ISTRUE_LONGINT:
		return simpleInstruction("OP_ISTRUE_LONGINT", p_uiOffset);

	case OpCode::OP_POP_BOOL:
		return simpleInstruction("OP_POP_BOOL", p_uiOffset);
	case OpCode::OP_POP_BYTE:
		return simpleInstruction("OP_POP_BYTE", p_uiOffset);
	case OpCode::OP_POP_SHORTINT:
		return simpleInstruction("OP_POP_SHORTINT", p_uiOffset);
	case OpCode::OP_POP_INT:
		return simpleInstruction("OP_POP_INT", p_uiOffset);
	case OpCode::OP_POP_FLOAT:
		return simpleInstruction("OP_POP_FLOAT", p_uiOffset);
	case OpCode::OP_POP_DOUBLE:
		return simpleInstruction("OP_POP_DOUBLE", p_uiOffset);
	case OpCode::OP_POP_LONGINT:
		return simpleInstruction("OP_POP_LONGINT", p_uiOffset);
	case OpCode::OP_POP:
		return popInstruction("OP_POP", p_uiOffset);

	case OpCode::OP_PRINT_BOOL:
		return simpleInstruction("OP_PRINT_BOOL", p_uiOffset);
	case OpCode::OP_PRINT_BYTE:
		return simpleInstruction("OP_PRINT_BYTE", p_uiOffset);
	case OpCode::OP_PRINT_SHORTINT:
		return simpleInstruction("OP_PRINT_SHORTINT", p_uiOffset);
	case OpCode::OP_PRINT_INT:
		return simpleInstruction("OP_PRINT_INT", p_uiOffset);
	case OpCode::OP_PRINT_FLOAT:
		return simpleInstruction("OP_PRINT_FLOAT", p_uiOffset);
	case OpCode::OP_PRINT_DOUBLE:
		return simpleInstruction("OP_PRINT_DOUBLE", p_uiOffset);
	case OpCode::OP_PRINT_LONGINT:
		return simpleInstruction("OP_PRINT_LONGINT", p_uiOffset);

	case OpCode::OP_GET_BOOL:
		return variableInstruction("OP_GET_BOOL", p_uiOffset);
	case OpCode::OP_GET_BYTE:
		return variableInstruction("OP_GET_BYTE", p_uiOffset);
	case OpCode::OP_GET_SHORTINT:
		return variableInstruction("OP_GET_SHORTINT", p_uiOffset);
	case OpCode::OP_GET_INT:
		return variableInstruction("OP_GET_INT", p_uiOffset);
	case OpCode::OP_GET_FLOAT:
		return variableInstruction("OP_GET_FLOAT", p_uiOffset);
	case OpCode::OP_GET_DOUBLE:
		return variableInstruction("OP_GET_DOUBLE", p_uiOffset);
	case OpCode::OP_GET_LONGINT:
		return variableInstruction("OP_GET_LONGINT", p_uiOffset);

	case OpCode::OP_SET_BOOL:
		return variableInstruction("OP_SET_BOOL", p_uiOffset);
	case OpCode::OP_SET_BYTE:
		return variableInstruction("OP_SET_BYTE", p_uiOffset);
	case OpCode::OP_SET_SHORTINT:
		return variableInstruction("OP_SET_SHORTINT", p_uiOffset);
	case OpCode::OP_SET_INT:
		return variableInstruction("OP_SET_INT", p_uiOffset);
	case OpCode::OP_SET_FLOAT:
		return variableInstruction("OP_SET_FLOAT", p_uiOffset);
	case OpCode::OP_SET_DOUBLE:
		return variableInstruction("OP_SET_DOUBLE", p_uiOffset);
	case OpCode::OP_SET_LONGINT:
		return variableInstruction("OP_SET_LONGINT", p_uiOffset);

	case OpCode::OP_ZERO_BYTE:
		return simpleInstruction("OP_ZERO_BYTE", p_uiOffset);
	case OpCode::OP_ZERO_SHORTINT:
		return simpleInstruction("OP_ZERO_SHORTINT", p_uiOffset);
	case OpCode::OP_ZERO_INT:
		return simpleInstruction("OP_ZERO_INT", p_uiOffset);
	case OpCode::OP_ZERO_FLOAT:
		return simpleInstruction("OP_ZERO_FLOAT", p_uiOffset);
	case OpCode::OP_ZERO_DOUBLE:
		return simpleInstruction("OP_ZERO_DOUBLE", p_uiOffset);
	case OpCode::OP_ZERO_LONGINT:
		return simpleInstruction("OP_ZERO_LONGINT", p_uiOffset);

	case OpCode::OP_JUMP:
		return jumpInstruction("OP_JUMP", 1, p_uiOffset);
	case OpCode::OP_JUMP_IF_FALSE:
		return jumpInstruction("OP_JUMP_IF_FALSE", 1, p_uiOffset);
	case OpCode::OP_LOOP:
		return jumpInstruction("OP_LOOP", -1, p_uiOffset);

	case OpCode::OP_RETURN:
		return simpleInstruction("OP_RETURN", p_uiOffset);
	default:
		std::cout << "Unknown opcode: " << (int)m_vCode[p_uiOffset] << std::endl;
		return p_uiOffset + 1;
	}
}

unsigned int Chunk::simpleInstruction(const std::string &p_sName, unsigned int offset) const
{
	std::cout << p_sName << std::endl;
	return offset + 1;
}

unsigned int Chunk::popInstruction(const std::string &p_sName, unsigned int p_uiOffset) const
{
	std::cout << p_sName << " " << (int)m_vCode[p_uiOffset + 1] << std::endl;
	return p_uiOffset + 2;
}

unsigned int Chunk::constantInstruction(const std::string &p_sName, unsigned int p_uiOffset, LixDatatype p_Type) const
{
	u_int8_t offset = m_vCode[p_uiOffset + 1];
	std::cout << p_sName << " " << (int)offset << " [" << lixDatatypeToString(p_Type) << "] " << lixValueToString(p_Type, offset) << std::endl;
	return p_uiOffset + 2;
}

unsigned int Chunk::longconstantInstruction(const std::string &p_sName, unsigned int p_uiOffset, LixDatatype p_Type) const
{
	u_int8_t a = m_vCode[p_uiOffset + 1];
	u_int8_t b = m_vCode[p_uiOffset + 2];
	uint16_t offset = (a | (b << 8));

	std::cout << p_sName << " " << (int)offset << " [" << lixDatatypeToString(p_Type) << "] " << lixValueToString(p_Type, offset) << std::endl;
	return p_uiOffset + 3;
}

unsigned int Chunk::variableInstruction(const std::string &p_sName, unsigned int p_uiOffset) const
{
	u_int8_t a = m_vCode[p_uiOffset + 1];
	u_int8_t b = m_vCode[p_uiOffset + 2];
	uint16_t offset = (a | (b << 8));

	std::cout << p_sName << " " << (int)offset << std::endl;
	return p_uiOffset + 3;
}

unsigned int Chunk::jumpInstruction(const std::string &p_sName, int p_iSign, unsigned int p_uiOffset) const
{
	u_int8_t a = m_vCode[p_uiOffset + 1];
	u_int8_t b = m_vCode[p_uiOffset + 2];
	uint16_t jump = (a | (b << 8));

	std::cout << p_sName << " " << std::setfill('0') << std::setw(4) << p_uiOffset << " -> " << std::setfill('0') << std::setw(4) << p_uiOffset + 3 + p_iSign * jump << std::endl;

	return p_uiOffset + 3;
}

std::string Chunk::lixValueToString(LixDatatype p_Type, uint16_t p_uiOffset) const
{
	std::stringstream ss;
	switch (p_Type)
	{
	case LixDatatype::LD_ShortInt:
		ss << *readConstant<Lix_ShortInt>(p_uiOffset);
		break;
	case LixDatatype::LD_Double:
		ss << *readConstant<Lix_Double>(p_uiOffset);
		break;
	case LixDatatype::LD_Float:
		ss << *readConstant<Lix_Float>(p_uiOffset);
		break;
	case LixDatatype::LD_Int:
		ss << *readConstant<Lix_Int>(p_uiOffset);
		break;
	case LixDatatype::LD_LongInt:
		ss << *readConstant<Lix_LongInt>(p_uiOffset);
		break;
	case LixDatatype::LD_Bool:
		ss << *readConstant<Lix_Bool>(p_uiOffset);
		break;
	case LixDatatype::LD_Byte:
		ss << (int)*readConstant<Lix_Byte>(p_uiOffset);
		break;
	}
	return ss.str();
}

Chunk::Chunk(/* args */)
{
}

Chunk::~Chunk()
{
}

void Chunk::write(uint8_t p_bByte, unsigned int p_uiLine)
{
	m_vCode.push_back(p_bByte);
	addLine(p_uiLine);
}
void Chunk::write(OpCode p_bByte, unsigned int p_uiLine)
{
	m_vCode.push_back(static_cast<uint8_t>(p_bByte));
	addLine(p_uiLine);
}
template u_int16_t Chunk::addConstant<Lix_ShortInt>(const Lix_ShortInt &p_Constant);
template u_int16_t Chunk::addConstant<Lix_Double>(const Lix_Double &p_Constant);
template u_int16_t Chunk::addConstant<Lix_Float>(const Lix_Float &p_Constant);
template u_int16_t Chunk::addConstant<Lix_Int>(const Lix_Int &p_Constant);
template u_int16_t Chunk::addConstant<Lix_LongInt>(const Lix_LongInt &p_Constant);
template u_int16_t Chunk::addConstant<Lix_Bool>(const Lix_Bool &p_Constant);
template u_int16_t Chunk::addConstant<Lix_Byte>(const Lix_Byte &p_Constant);

template <class T>
u_int16_t Chunk::addConstant(const T &p_Constant)
{
	T tmp = p_Constant;
	auto tmparray = Converter::encode(&tmp);
	m_vConstants.insert(m_vConstants.end(), tmparray->begin(), tmparray->end());
	return static_cast<u_int16_t>(m_vConstants.size() - tmparray->size());
}

void Chunk::disassemble(const std::string &p_sName) const
{
	std::cout << "=== " << p_sName << " ===" << std::endl;

	unsigned int prevline = 0;
	unsigned int line = 0;

	for (unsigned int offset = 0; offset < m_vCode.size();)
	{
		line = getLine(offset);
		offset = disassembleInstruction(offset, line, prevline);
		prevline = line;
	}
}

void Chunk::disassembleInstruction(unsigned int offset) const
{
	disassembleInstruction(offset, getLine(offset), getLine(offset - 1));
}

unsigned int Chunk::emitJump(OpCode p_bByte, unsigned int p_uiLine)
{
	write(p_bByte, p_uiLine);
	write(0xff, p_uiLine);
	write(0xff, p_uiLine);
	return m_vCode.size() - 2;
}

void Chunk::patchJump(unsigned int p_uiOffset)
{
	int jump = m_vCode.size() - p_uiOffset - 2;
	if (jump > UINT16_MAX)
	{
		//error TODO
	}
	m_vCode[p_uiOffset] = jump & 0xff;
	m_vCode[p_uiOffset + 1] = (jump >> 8) & 0xff;
}

void Chunk::emitLoop(unsigned int loopStart, unsigned int p_uiLine)
{
	write(OpCode::OP_LOOP, p_uiLine);
	unsigned int offset = m_vCode.size() - loopStart + 2;
	if (offset > UINT16_MAX)
	{
		//error TODO
	}

	write(offset & 0xff);
	write((offset >> 8) & 0xff, p_uiLine);
}

unsigned int Chunk::getChunkPos()
{
	return m_vCode.size();
}

template <class T>
const T *Chunk::readConstant(u_int16_t p_iuID) const
{
	return reinterpret_cast<const T *>(&m_vConstants[p_iuID]);
}

const uint8_t *Chunk::getConstant(uint16_t p_uiID) const
{
	return &m_vConstants[p_uiID];
}

const std::vector<uint8_t>::const_iterator Chunk::begin()const
{
	return m_vCode.begin();
}
const std::vector<uint8_t>::const_iterator Chunk::end()const
{
	return m_vCode.end();
}