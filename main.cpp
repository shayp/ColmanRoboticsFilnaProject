#include <iostream>
#include "Src/RobotAPI/Robot.h"
#include "Src/Plans/PlnObstacleAvoid.h"
#include "Src/Managers/SimManager.h"
#include "Src/Managers/Manager.h"
#include "Src/Utils/PositionUtils.h"
#define SIMULATOR_ROBOT		1
const char* CPG_FILE_PATH =  "parameters.txt";

using namespace std;
using namespace Utils;

int main(int argc, char** argv)
{
	SimManager::GetInstance()->Init(CPG_FILE_PATH);
	SimManager::GetInstance()->run();
	SimManager::GetInstance()->GetAllWayPoints();
	Location* startLocation = SimManager::GetInstance()->GetAllWayPoints()[0];
	cout << "Start yaw: " << startLocation->getYaw() << endl;
#ifdef SIMULATOR_ROBOT
	Robot robot("localhost",6665, startLocation);
#else
	Robot robot("10.10.245.65",6665, startLocation);
#endif
	PlnObstacleAvoid pln(&robot);
	Manager m(&robot,&pln);
	m.run();

}
