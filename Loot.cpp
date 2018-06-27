#include "Loot.h"

Loot::Loot()
{
}

Loot::Loot(const Loot& orig)
{
}

Loot::~Loot()
{
}

loot_t Loot::getLootName()
{
    return lootName;
}

bool Kitty::isThereAnAlarmTile(Floor* currFloor)
{
	bool isThere = false;

	std::vector< std::vector<Tile*> > tiles;
	tiles = currFloor->getDeck();

	for (unsigned row = 0; row < ROWS; row++)
	{

		for (unsigned col = COLS; col < COLS; col++)
		{
			if((tiles[row][col]->isAlarmTile())&&(tiles[row][col]->isTileVisible()))
			{
				alarmTiles.push_back(tiles[row][col]->getCurrentLocation()); //meto la location de ese tile en el vector de alarm tiles

			}
			
			
		}

	}

	if(!alarmTiles.empty())
		isThere = true;     //si no esta vacío el vector, hay alarm tiles descubiertas

	return isThere;
}

bool Kitty::rollDice()
{
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//unsigned result = rand_r(seed % 6 + 1);

	srand(time(NULL));
	unsigned result = (rand() % 6) + 1;

	bool oneOrTwo = false;
	
	if((result == 1) || (result == 2))
		oneOrTwo = true;
	
	return oneOrTwo;
}

Tile* Kitty::calculateRoute()
{
	Tile* kittyTile;

	unsigned distance;
	unsigned minDistance;

	location_t minDistanceTile = alarmTiles[0];
	location_t currentLocation = currentTile->getCurrentLocation();

	//Obtengo las filas y columnas de la tile actual y la primera alarm tile del vector alarmTiles
	int rowCurrent = getRow(currentLocation);
	int colCurrent = getColumn(currentLocation);
	int rowAlarm = getRow(minDistanceTile);
	int colAlarm = getColumn(minDistanceTile);

	minDistance = abs(rowCurrent-rowAlarm) + abs(colCurrent-colAlarm); //calculo de distancia entre tiles (en numero de tiles)

	for(unsigned i=1; i<alarmTiles.size(); i++)
	{
		//busco la tile de alarm con menor distancia a la actual

		rowAlarm = getRow(alarmTiles[i]);
		colAlarm = getColumn(alarmTiles[i]);

		distance = abs(rowCurrent-rowAlarm) + abs(colCurrent-colAlarm);

		if(distance < minDistance)	//como no le puse <=, si llegara a haber varias iguales, la que va es la primera que agarra
		{
			minDistanceTile = alarmTiles[i];   
			minDistance = distance;
		}

	}

	//obtengo la fila y columna de la alarm tile mas cercana

	rowAlarm = getRow(minDistanceTile);
	colAlarm = getColumn(minDistanceTile);

	//veo en qué tile tengo que poner el kitty

	if(rowAlarm > rowCurrent)
		kittyTile = currentTile->getLowerTile();

	else if(rowAlarm < rowCurrent)
		kittyTile = currentTile->getUpperTile();

	else if(colAlarm > colCurrent)
		kittyTile = currentTile->getRightTile();

	else if(colAlarm < colCurrent)
		kittyTile = currentTile->getLeftTile();

	return kittyTile;

}

void Tiara::setGuard(Guard* guard)
{
	this->guard = guard;
}

bool Tiara::awakenCurse(Tile* ownerTile, tileInfo_t* tileInfo)
{
	bool curse = false;
	if(isGuardNearby(ownerTile,tileInfo))
		curse = true;
	
	return curse;
}

bool Tiara::isGuardNearby(Tile* ownerTile, tileInfo_t* tileInfo)
{
	bool isGuard = false;
	if(ownerTile->isTileValid(guard->getLocation(), tileInfo))
		isGuard = true;
	
	return isGuard;
}


bool Painting::awakenCurse(Tile* ownerTile)
{
	bool curse = false;
	if(onServiceDuctTile(ownerTile)||isSecretDoorNearby(ownerTile))
		curse = true;
	
	return curse;
}

bool Painting::onServiceDuctTile(Tile* ownerTile)
{
	bool serviceDuct = false;
	if(ownerTile->getTileType() == SERVICEDUCT)
		serviceDuct = true;
	
	return serviceDuct;
}

bool Painting::isSecretDoorNearby(Tile* ownerTile)
{
	bool secretDoor = false;
	if(ownerTile->getTileType() == SECRETDOOR)
		secretDoor = true;
	
	return secretDoor;
}

bool Mirror::awakenCurse(Tile* ownerTile)
{
	bool curse = false;
	decreaseActions();
	if(deactivateLaser(ownerTile))
		curse = true;
	
	return curse;
}

bool Mirror::deactivateLaser(Tile* ownerTile)
{
	bool deactivate = false;
	if((ownerTile->getTileType() == LASER) || (ownerTile->isAlarmTile()))
	{
		ownerTile->deactivateAlarm();
		deactivate = true;
	}
	
	return deactivate;
}

bool KeyCard::awakenCurse(Floor* currFloor, Tile* ownerTile)
{
	bool curse = false;
	disableCrackFlags(currFloor);
	if(isOwnerOnSafeTile(ownerTile))
	{
		enableCrackFlag(ownerTile);
		curse = true;
	}
	
	return curse;
}

bool KeyCard::isOwnerOnSafeTile(Tile* ownerTile)
{
	bool isSafe = false;
	if(ownerTile->getTileType() == SAFE)
		isSafe = true;
	
	return isSafe;
}

void KeyCard::disableCrackFlags(Floor* currFloor)
{
	std::vector< std::vector<Tile*> > tiles;
	tiles = currFloor->getDeck();

	for (unsigned row = 0; row < ROWS; row++)
	{

		for (unsigned col = COLS; col < COLS; col++)
		{
			if(tiles[row][col]->getTileType() == SAFE)
			{
				dynamic_cast <Safe*> (tiles[row][col])->disableCracked();
			}
			
			
		}

	}
}



bool Isotope::awakenCurse(Tile* ownerTile)
{
	bool curse = false;
	if(onThermoTile(ownerTile))
	{
		if(ownerTile->triggerAlarm())
			curse = true;
	}
	
	return curse;
}

bool Isotope::onThermoTile(Tile* ownerTile)
{
	bool thermo = false;
	if(ownerTile->getTileType() == THERMO)
		thermo = true;
	
	return thermo;
}

bool Gemstone::awakenCurse(Tile* ownerTile, Tile* partnerTile)
{
	bool curse = false;
	if(previousTile->getCurrentLocation() != ownerTile->getCurrentLocation())
	{
		if(onSameTileAsPartner(ownerTile, partnerTile))
			curse = true;
	}
	
	return curse;
}

void Gemstone::setPrevTile(Tile* prevTile)
{
	previousTile = prevTile;
}

bool Gemstone::onSameTileAsPartner(Tile* ownerTile, Tile* partnerTile)
{
	bool same = false;
	if(ownerTile->getCurrentLocation() == partnerTile->getCurrentLocation())
		same = true;
	
	return same;
}

bool Chihuahua::awakenCurse(Tile* ownerTile)
{
	bool curse = false;
	if(rollDice())
	{
		ownerTile->triggerAlarm();
		curse = true;
	}
	
	return curse;
}

bool Chihuahua::rollDice()
{
	/*unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	unsigned result = rand_r(seed % 6 + 1);*/

	srand(time(NULL));
	unsigned result = (rand() % 6) + 1;

	bool isItSix = false;
	
	if(result == 6)
		isItSix = true;
	
	return isItSix;
}
