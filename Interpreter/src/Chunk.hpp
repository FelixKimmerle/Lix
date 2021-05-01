#pragma once
#include <cstdint>
#include <vector>
#include <string>

#include "LixTypenames.hpp"

class Chunk
{
public:
	enum class OpCode : uint8_t
	{
		OP_CONSTANT_BYTE,
		OP_CONSTANT_SHORTINT,
		OP_CONSTANT_INT,
		OP_CONSTANT_FLOAT,
		OP_CONSTANT_DOUBLE,
		OP_CONSTANT_LONGINT,

		OP_CONSTANT_LONG_BYTE,
		OP_CONSTANT_LONG_SHORTINT,
		OP_CONSTANT_LONG_INT,
		OP_CONSTANT_LONG_FLOAT,
		OP_CONSTANT_LONG_DOUBLE,
		OP_CONSTANT_LONG_LONGINT,

		OP_ADD_BYTE,
		OP_ADD_SHORTINT,
		OP_ADD_INT,
		OP_ADD_FLOAT,
		OP_ADD_DOUBLE,
		OP_ADD_LONGINT,

		OP_SUBTRACT_BYTE,
		OP_SUBTRACT_SHORTINT,
		OP_SUBTRACT_INT,
		OP_SUBTRACT_FLOAT,
		OP_SUBTRACT_DOUBLE,
		OP_SUBTRACT_LONGINT,

		OP_MULTIPLY_BYTE,
		OP_MULTIPLY_SHORTINT,
		OP_MULTIPLY_INT,
		OP_MULTIPLY_FLOAT,
		OP_MULTIPLY_DOUBLE,
		OP_MULTIPLY_LONGINT,

		OP_DIVIDE_BYTE,
		OP_DIVIDE_SHORTINT,
		OP_DIVIDE_INT,
		OP_DIVIDE_FLOAT,
		OP_DIVIDE_DOUBLE,
		OP_DIVIDE_LONGINT,

		OP_CAST_BYTE_SHORTINT,
		OP_CAST_BYTE_INT,
		OP_CAST_BYTE_FLOAT,
		OP_CAST_BYTE_DOUBLE,
		OP_CAST_BYTE_LONGINT,

		OP_CAST_SHORTINT_BYTE,
		OP_CAST_SHORTINT_INT,
		OP_CAST_SHORTINT_FLOAT,
		OP_CAST_SHORTINT_DOUBLE,
		OP_CAST_SHORTINT_LONGINT,

		OP_CAST_INT_BYTE,
		OP_CAST_INT_SHORTINT,
		OP_CAST_INT_FLOAT,
		OP_CAST_INT_DOUBLE,
		OP_CAST_INT_LONGINT,

		OP_CAST_FLOAT_BYTE,
		OP_CAST_FLOAT_SHORTINT,
		OP_CAST_FLOAT_INT,
		OP_CAST_FLOAT_DOUBLE,
		OP_CAST_FLOAT_LONGINT,

		OP_CAST_DOUBLE_BYTE,
		OP_CAST_DOUBLE_SHORTINT,
		OP_CAST_DOUBLE_INT,
		OP_CAST_DOUBLE_FLOAT,
		OP_CAST_DOUBLE_LONGINT,

		OP_CAST_LONGINT_BYTE,
		OP_CAST_LONGINT_SHORTINT,
		OP_CAST_LONGINT_INT,
		OP_CAST_LONGINT_FLOAT,
		OP_CAST_LONGINT_DOUBLE,

		OP_EQUAL_BYTE,
		OP_EQUAL_SHORTINT,
		OP_EQUAL_INT,
		OP_EQUAL_FLOAT,
		OP_EQUAL_DOUBLE,
		OP_EQUAL_LONGINT,
		OP_EQUAL_BOOL,

		OP_LESS_BYTE,
		OP_LESS_SHORTINT,
		OP_LESS_INT,
		OP_LESS_FLOAT,
		OP_LESS_DOUBLE,
		OP_LESS_LONGINT,

		OP_GREATER_BYTE,
		OP_GREATER_SHORTINT,
		OP_GREATER_INT,
		OP_GREATER_FLOAT,
		OP_GREATER_DOUBLE,
		OP_GREATER_LONGINT,

		OP_NEGATE_BYTE,
		OP_NEGATE_SHORTINT,
		OP_NEGATE_INT,
		OP_NEGATE_FLOAT,
		OP_NEGATE_DOUBLE,
		OP_NEGATE_LONGINT,
		OP_NEGATE_BOOL,

		OP_ISTRUE_BYTE,
		OP_ISTRUE_SHORTINT,
		OP_ISTRUE_INT,
		OP_ISTRUE_FLOAT,
		OP_ISTRUE_DOUBLE,
		OP_ISTRUE_LONGINT,

		OP_TRUE,
		OP_FALSE,

		OP_POP_BYTE,
		OP_POP_SHORTINT,
		OP_POP_INT,
		OP_POP_FLOAT,
		OP_POP_DOUBLE,
		OP_POP_LONGINT,
		OP_POP_BOOL,
		OP_POP_FUNC,
		OP_POP,

		OP_PRINT_BYTE,
		OP_PRINT_SHORTINT,
		OP_PRINT_INT,
		OP_PRINT_FLOAT,
		OP_PRINT_DOUBLE,
		OP_PRINT_LONGINT,
		OP_PRINT_BOOL,

		OP_GET_BYTE,
		OP_GET_SHORTINT,
		OP_GET_INT,
		OP_GET_FLOAT,
		OP_GET_DOUBLE,
		OP_GET_LONGINT,
		OP_GET_BOOL,
		OP_GET_FUNC,

		OP_SET_BYTE,
		OP_SET_SHORTINT,
		OP_SET_INT,
		OP_SET_FLOAT,
		OP_SET_DOUBLE,
		OP_SET_LONGINT,
		OP_SET_BOOL,

		OP_ZERO_BYTE,
		OP_ZERO_SHORTINT,
		OP_ZERO_INT,
		OP_ZERO_FLOAT,
		OP_ZERO_DOUBLE,
		OP_ZERO_LONGINT,

		OP_PUSH_FUNC,
		OP_CALL_FUNC,

		OP_JUMP,
		OP_JUMP_IF_FALSE,
		OP_LOOP,

		OP_RETURN,
	};

private:
	std::vector<uint8_t> m_vCode;
	std::vector<uint8_t> m_vConstants;
	std::vector<unsigned int> m_vLines;
	std::vector<unsigned int> m_vLinesnumber;
	void addLine(unsigned int p_uiLine);
	unsigned int getLine(unsigned int offset) const;
	unsigned int disassembleInstruction(unsigned int p_uiOffset, unsigned int p_uiLine, unsigned int p_uiPrevline) const;
	unsigned int simpleInstruction(const std::string& p_sName, unsigned int p_uiOffset) const;
	unsigned int popInstruction(const std::string& p_sName, unsigned int p_uiOffset) const;
	unsigned int variableInstruction(const std::string& p_sName, unsigned int p_uiOffset)const;
	unsigned int jumpInstruction(const std::string& p_sName, int p_iSign, unsigned int p_uiOffset)const;
	unsigned int callInstruction(const std::string& p_sName, unsigned int p_uiOffset)const;

	unsigned int constantInstruction(const std::string& p_sName, unsigned int p_uiOffset, LixDatatype p_Type) const;

	unsigned int longconstantInstruction(const std::string& p_sName, unsigned int p_uiOffset, LixDatatype p_Type) const;

	std::string lixValueToString(LixDatatype p_Type, uint16_t p_uiOffset) const;

	template <class T>
	const T* readConstant(u_int16_t p_iuID) const;

public:
	Chunk(/* args */);
	void write(uint8_t p_bByte, unsigned int p_uiLine = 0);
	void write(OpCode p_bByte, unsigned int p_uiLine = 0);
	template <class T>
	u_int16_t addConstant(const T p_Constant);
	void disassemble(const std::string& p_sName) const;
	void disassembleInstruction(unsigned int p_uiOffset) const;

	unsigned int emitJump(OpCode p_bByte,unsigned int p_uiLine = 0);
	void patchJump(unsigned int p_uiOffset);
	void emitLoop(unsigned int loopStart,unsigned int p_uiLine = 0);

	unsigned int getChunkPos();

	const uint8_t* getConstant(uint16_t p_uiID)const;
	const std::vector<uint8_t>::const_iterator begin()const;
	const std::vector<uint8_t>::const_iterator end()const;
};
