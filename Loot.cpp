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

void Tiara::setGuard(Guard* guard)
{
	this->guard = guard;
}

bool Tiara::awakenCurse(location_t location)
{
	bool curse = false;
	if(isGuardNearby(location))
		curse = true;
	
	return curse;
}

bool Tiara::isGuardNearby(Tile* ownerTile, tileInfo_t* tileInfo)
{
	bool isGuard = false;
	if(ownerTile->isTileValid(guard->getLocation, tileInfo))
		isGuard = true;
	
	return isGuard;
}

void Tiara::setGuard(Guard* guard)
{
	this->guard = guard;
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
	if(ownerTile->getTileType() == LASER)
	{
		ownerTile->deactivateAlarm();
		deactivate = true;
	}
	
	return deactivate;
}

bool Keycard::awakenCurse(Floor* currFloor, Tile* ownerTile)
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

bool Keycard::isOwnerOnSafeTile(Tile* ownerTile)
{
	bool isSafe = false;
	if(ownerTile->getTileType() == SAFE)
		isSafe = true;
	
	return isSafe;
}

void Keycard::disableCrackFlags(Floor* currFloor)
{

	for (unsigned row = 0; row < ROWS; row++)
	{

		for (unsigned col = COLS; col < COLS; col++)
		{
			if(tiles[row][col]->getTileType() == SAFE)
			{
				tiles[row][col]->disableCracked();
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
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	unsigned result = rand_r(seed % 6 + 1);
	bool isItSix = false;
	
	if(result == 6)
		isItSix = true;
	
	return isItSix;
}

