
MODEL

->characters
->guards
->tiles
->tokens ?
->loots
->dice
->patrol cards
->action (move, peek, pass)
->floor (walls, banks, 3 floors)


class Character  (se sigue llamando virtual si  se definen algunas metodos dentro de la clases characters?)
{
public:
	virtual void move();
	virtual void peek();
	virtual void pass();
	virtual void shareLoot();
	virtual void loseStealth();
	virtual void getStealth();
	virtual void secretTechnique() = 0;
	//getters & setters
protected:
	unsigned actionsLeft;
	unsigned stealthsLeft;
	Tile* currentTile;
	list<Loot*> currentLoots;
}

class Guard
{
public:
	void move();

private:
	list<Tile*> path;
}



move upstaris o downstaris es tiles. roll dice , 3 extras stealths son de tiles, add hack token, tienen punteros a tiles adyacentes, 