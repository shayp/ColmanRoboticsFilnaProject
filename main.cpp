#include <iostream>
#include "Src/RobotAPI/Robot.h"
#include "Src/Plans/PlnObstacleAvoid.h"
#include "Src/Managers/SimManager.h"
#include "Src/Managers/Manager.h"
#include "Src/Utils/PositionUtils.h"

const char* CPG_FILE_PATH =  "parameters.txt";

using namespace std;
using namespace Utils;

int main(int argc, char** argv)
{
	SimManager::GetInstance()->Init(CPG_FILE_PATH);
	SimManager::GetInstance()->run();
	Robot robot("localhost",6665);
	PlnObstacleAvoid pln(&robot);
	Manager m(&robot,&pln);
	m.run();

}
