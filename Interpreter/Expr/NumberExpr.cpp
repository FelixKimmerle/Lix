#include "NumberExpr.hpp"
#include "VisitorExpr.hpp"

template <class T>
NumberExpr<T>::NumberExpr(T p_Number, unsigned int p_uiLine) : Expr(p_uiLine)
{
    m_Number = p_Number;
}

template <class T>
NumberExpr<T>::~NumberExpr()
{
}

template <class T>
void NumberExpr<T>::visit(VisitorExpr *p_pVisitor)
{
    p_pVisitor->visitNumber(this);
}

template <class T>
T NumberExpr<T>::getNumber()
{
    return m_Number;
}

template class NumberExpr<Lix_Byte>;
template class NumberExpr<Lix_Double>;
template class NumberExpr<Lix_Float>;
template class NumberExpr<Lix_Int>;
template class NumberExpr<Lix_LongInt>;
template class NumberExpr<Lix_ShortInt>;