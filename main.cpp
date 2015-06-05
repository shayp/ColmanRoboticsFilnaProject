#include <iostream>
#include "Manager.h"
#include "Robot.h"
#include "Plans/PlnObstacleAvoid.h"

using namespace std;

int main(int argc, char** argv)
{
	Robot robot("localhost",6665);
	PlnObstacleAvoid pln(&robot);
	Manager m(&robot,&pln);
	m.run();

}
