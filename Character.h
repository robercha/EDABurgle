#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
public:
    Character();
    Character(const Character& orig);
    virtual ~Character();
    move( ?);
    peek( ?);
    pass( ?);
    useToken(token_t ?, ?);
    shareLoot( ?);
    bool virtual specialMove( ?) = 0;
protected:
    Tile* Tile;
    //stealth tokens
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

