#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
public:
    Character();
    Character(const Character& orig);
    virtual ~Character();
    void move();
    void peek();
    void pass();
    void rollDice();

    void addToken(token_t);
    void useToken(token_t);
    void shareLoot();
    bool virtual specialMove() = 0;
protected:
    Tile* location;
    unsigned actions;
    unsigned stealthTokens;

    //loot
};

class Juicer : public Character {
public:
private:

};

class Hacker : public Character {
public:
private:

};

class Acrobat : public Character {
public:
private:

};

class Spotter : public Character {
public:
private:

};

class Hawk : public Character {
public:
private:

};

class Raven : public Character {
public:
private:

};

class Peterman : public Character {
public:
private:

};


#endif /* CHARACTER_H */

