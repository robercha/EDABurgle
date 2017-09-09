
class Controller
{
public:
	void manageEvent(void);
	void updateGraphics(void);
	bool initGame(void);
	bool buildPacket(packet_t packet); //enum
	translateUserData(void);
	translatePackage(void);
private:
	userData_t* userData;
	gameData_t* gameData;
	graphics_t* graphics;
	FSM* FSM;
	eventGenerator* user;
	eventGenerator* networking;
}


Controller::manageEvent(void)
{
	user->getEvent(userData);
	translateUserData();
	FSMCycle(userData->event, gameData);

	networking->getEvent(userData);
	translatePackage();
	FSMCycle(userData->event, gameData);

}

Controller::initGame()
{
	if(networking.getLastPacketSent == NULL) //null o noEvent, lo q sea
		buildPacket(NAME);
	switch(userData.event.trueEvent)
	{
		case TIMEOUT: 
		buildPacket(networking.getLastPacketSent);
		break;
		case ERROR: ???
		break;
		case QUIT: ???
		break;
		case NAME:
	}
}