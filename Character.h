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
    bool virtual specialMove( ?) = 0;
private:

};

class EventGenerator {
public:
    bool virtual getEvent(userData_t*) = 0;
};

#endif /* CHARACTER_H */

