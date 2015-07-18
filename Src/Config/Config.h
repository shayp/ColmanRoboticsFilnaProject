#ifndef CONFIG_H
#define CONFIG_H
enum
{
	eNotWayPoint = 0,
	eAStarWayPoint = 1,
	ePathWayPoint = 2,
}WayPointType;

// Waypoint Manager
#define WAYPOINT_RADIUS 1
#define DEFAULT_WAYPOINT_RESOLUTION 6
#define DEFAULT_WAYPOINT_ACCURACY (0.05)
#define DETECT_EVASION_RADIUS 0.6

#endif
