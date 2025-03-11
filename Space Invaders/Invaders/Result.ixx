export module Result;

import <string>;

export struct Result        //struktura pomagaj¹ca naam przy zapisyawaniu pseudonimu gracza i jego punktów
{
    std::string name;
    int points;
    std::string getResult()
    {
        return (name + " " + std::to_string(points));
    }
    Result(std::string n, int p)
        : name(n), points(p)
    {}
    Result()
    {}
};