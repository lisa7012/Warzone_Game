#include "MapLoader.h"

int main()
{
	string* input = new string(); //string for user input

	std::cout << "Executing MapLoader Main()\n----------------------------------------\n" << endl;

	//valid .map
	std::cout << "Please input a valid .map file" << endl;
	std::cin >> *input;
	MapLoader* mapload = new MapLoader(*input);
	Map* map;
	map = mapload->parseMap();

	std::cout << "\n\n";

	//invalid .map
	std::cout << "Please input an invalid .map file" << endl;
	std::cin >> *input;
	MapLoader* maploadBad = new MapLoader(*input);
	Map* mapBad;
	mapBad = maploadBad->parseMap();

	//deleting pointers to avoid memory leaks
	delete input;
	input = nullptr;
	delete map;
	map = nullptr;
	delete mapBad;
	mapBad = nullptr;
	delete input;
	input = nullptr;
	delete maploadBad;
	maploadBad = nullptr;
	delete mapload;
	mapload = nullptr; 

	std::cout << "\n\n----------------------------------------\nFinished executing MapLoader Main()!";

	return 0;
}
