#include "Expression.h"

std::ostream &operator<<(std::ostream &o, const Expression& e) {
    e.printOn(o);
    return o;
}

void BinaryExpression::printOn(std::ostream &os) const {
    os << "[" << *left << " " << _operator << " " << *right << "]";
}

void GroupingExpression::printOn(std::ostream &os) const {
    os << "[" << "group " << *expression << "]";
}

void UnaryExpression::printOn(std::ostream &os) const {
    os << "[" << _operator << " " << *expression << "]";
}

void LiteralExpression::printOn(std::ostream &os) const {
    os << value;
}
