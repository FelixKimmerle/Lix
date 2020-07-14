#include "LixTypenames.hpp"
LixDatatype maxType(LixDatatype left, LixDatatype right)
{
	if (left >= right)
	{
		return left;
	}
	return right;
}

std::string lixDatatypeToString(LixDatatype p_Type)
{
	switch (p_Type)
	{
	case LixDatatype::LD_ShortInt:
		return "short";
	case LixDatatype::LD_Double:
		return "double";
	case LixDatatype::LD_Float:
		return "float";
	case LixDatatype::LD_Int:
		return "int";
	case LixDatatype::LD_LongInt:
		return "long";
	case LixDatatype::LD_Bool:
		return "bool";
	case LixDatatype::LD_Byte:
		return "byte";
	}
}

unsigned int getSize(LixDatatype p_Type)
{
	switch (p_Type)
	{
	case LixDatatype::LD_Bool:
		return sizeof(Lix_Bool);
		break;
	case LixDatatype::LD_Byte:
		return sizeof(Lix_Byte);
		break;
	case LixDatatype::LD_ShortInt:
		return sizeof(Lix_ShortInt);
		break;
	case LixDatatype::LD_Int:
		return sizeof(Lix_Int);
		break;
	case LixDatatype::LD_Float:
		return sizeof(Lix_Float);
		break;
	case LixDatatype::LD_Double:
		return sizeof(Lix_Double);
		break;
	case LixDatatype::LD_LongInt:
		return sizeof(Lix_LongInt);
		break;
	}
}