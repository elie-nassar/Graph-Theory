#pragma once

class literal {
    private:
        int id;
        bool neg;
    public:
        literal();
        literal(int id);
        literal(int id,bool neg);

        int get_id() const;
        bool is_neg() const;
        
        bool operator<(const literal& other) const;
};