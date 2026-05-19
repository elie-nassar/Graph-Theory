#include "literal.hpp"

literal::literal() : literal(0,false) {}
literal::literal(int id) : literal(id,false) {}
literal::literal(int id, bool neg) : id(id), neg(neg) {}

int literal::get_id() const {return id;}
bool literal::is_neg() const {return neg;}

bool literal::operator<(const literal& other) const {
    if (id != other.id) return id < other.id;
    return neg < other.neg;
}
