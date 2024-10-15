
#include "cub.h"

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	t_map 	tmap;
	t_color floor;
	t_color celling;
	char north[23] = "../resources/wall1.xpm";
	char south[23] = "../resources/wall2.xpm";
	char east[23] = "../resources/wall3.xpm";
	char west[23] = "../resources/wall4.xpm";

	floor.r = 93;
	floor.g = 97;
	floor.b = 94;

	celling.r = 89;
	celling.g = 30;
	celling.r = 30;

	tmap.north = north;
	tmap.south = south;
	tmap.east = east;
	tmap.west = west;
	tmap.floor = floor;
	tmap.celling = celling; 
	init_game(tmap);
}
