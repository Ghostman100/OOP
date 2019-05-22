#pragma once

class Printable {
public:
    virtual std::string getInfo() = 0;
};


class Named : public Printable {
public:
    std::string getInfo() const
    {
        return m_name;
    }
    Named(std::string name): m_name(name)
    {
    }
private:
    std::string m_name;
};
