#include "NumberExpr.hpp"
#include "VisitorExpr.hpp"

template <class T>
NumberExpr<T>::NumberExpr(T number, TokenPosition position) : Expr(position),
                                                              number(number)
{
}

template <class T>
void NumberExpr<T>::visit(VisitorExpr *visitor)
{
    visitor->visitNumber(this);
}

template <class T>
T NumberExpr<T>::get_number()
{
    return number;
}

template class NumberExpr<Lix_Byte>;
template class NumberExpr<Lix_Double>;
template class NumberExpr<Lix_Float>;
template class NumberExpr<Lix_Int>;
template class NumberExpr<Lix_LongInt>;
template class NumberExpr<Lix_ShortInt>;