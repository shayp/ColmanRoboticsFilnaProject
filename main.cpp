#include <iostream>
#include "Src/RobotAPI/Manager.h"
#include "Src/RobotAPI/Robot.h"
#include "Src/Plans/PlnObstacleAvoid.h"

using namespace std;

int main(int argc, char** argv)
{
	Robot robot("localhost",6665);
	PlnObstacleAvoid pln(&robot);
	Manager m(&robot,&pln);
	m.run();

}
