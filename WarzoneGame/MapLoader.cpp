#pragma once
#include "MapLoader.h"

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//
//										MapLoader
//
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//stream insertion operator
MapLoader& MapLoader::operator=(const MapLoader& mapL) {
	this->_fileName = mapL._fileName;
	return *this;
}

//assignment operator
ostream& operator<<(ostream& out, const MapLoader& mapL) {
	out << "MapLoader's File Name: " << endl;
	out << "------------------------------" << endl;
	if (!mapL._fileName->compare("")) {
		out << "No File Name Detected" << endl;
	}
	else {
		out << mapL._fileName << endl;
	}
	return out;
}

//defining parseLine method
//will be used in parseTerritoryList, parseContinentList to verify validity of .map File
vector<string> MapLoader::parseLine(string s) {
	vector<string> rows;

	//Define the regex for the split
	const regex separator{ " " };

	//Create the iterator object with the regex separator
	sregex_token_iterator iterator(s.begin(), s.end(), separator, -1);
	sregex_token_iterator end;

	//Loop on the iterator and remove the commented and empty row. Put each row in a vector called rows
	while (iterator != end) {
		string row = (*iterator).str(); //returns a string with a copy of the contents referred by the iterator object.
		if (row.length() == 0 || row[0] == ';') { //ignores new lines and lines with starting with a ';'
			++iterator;
			continue;
		}
		rows.push_back(*iterator); //appends row to the end of string row
		++iterator; //increments iterator to check next line with regex separator "\\n"
	}
	return rows;
}

//defining parseRows method, 
//will be used in parseTerritoryList, parseContinentList, parseBorderMatrix definition
vector<string> MapLoader::parseRows(string s) {
	vector<string> rows;

	//Define the regex for the split
	const regex separator{ "\\n" };

	//Create the iterator object with the regex separator
	sregex_token_iterator iterator(s.begin(), s.end(), separator, -1);
	sregex_token_iterator end;

	//Loop on the iterator and remove the commented and empty row. Put each row in a vector called rows
	while (iterator != end) {
		string row = (*iterator).str(); //returns a string with a copy of the contents referred by the iterator object.
		if (row.length() == 0 || row[0] == ';') { //ignores new lines and lines with starting with a ';'
			++iterator;
			continue;
		}
		rows.push_back(*iterator); //appends row to the end of string row
		++iterator; //increments iterator to check next line with regex separator "\\n"
	}
	return rows;
}

//Create the vector of continent object out of the info in the map file
vector<Continent*> MapLoader::parseContinentList(string s, vector<Territory*> territoryList) {
	vector<Continent*> listContinent;
	vector<string> rows = parseRows(s);
	int EXPECTED_CONTINENT_COLUMNS = 3;

	//checks for invalidity for the current line; if it is invalid, return an empty vector<Territory*>
	for (int i = 0; i < size(rows); i++) {
		if (parseLine(rows[i]).size() != EXPECTED_CONTINENT_COLUMNS) {
			listContinent.clear();
			return listContinent;
		}
	}

	//Create the vector of continent 
	for (int i = 0; i < rows.size(); i++) {
		stringstream stream(rows[i]);
		string name;
		int bonusArmies;
		stream >> name;
		stream >> bonusArmies;

		vector<Territory*> list;
		Continent* continent = new Continent(name, list, i + 1, bonusArmies);
		listContinent.push_back(continent);
	}

	//Loop through all of the territories and add them to their appropriate continent
	for (int i = 0; i < size(territoryList); i++) {

		//Get the continent id of each territory and add them the to right continent territory list
		listContinent[territoryList[i]->getContinentID()]->addTerritory(territoryList[i]);
	}
	return listContinent;
}

//Create the vector of territory object out of the info in the map file
vector<Territory*> MapLoader::parseTerritoryList(string s) {
	vector<Territory*> listTerritory;
	vector<string> rows = parseRows(s);
	int EXPECTED_TERRITORY_COLUMNS = 5;

	//checks for invalidity for the current line; if it is invalid, return an empty vector<Territory*>
	for (int i = 0; i < size(rows); i++) {
		if (parseLine(rows[i]).size() != EXPECTED_TERRITORY_COLUMNS) {
			listTerritory.clear();
			return listTerritory;
		}
	}

	//Get the info neccessary to create a territory object from each row of the file
	for (int i = 0; i < size(rows); i++) {
		stringstream stream(rows[i]);
		int index, continentID;
		string name;
		stream >> index;
		stream >> name;
		stream >> continentID;
		Territory* territory = new Territory(index - 1, 0, continentID - 1, 0, name);  // CHANGED UNDEFINED TO 0 - Derek
		listTerritory.push_back(territory);
	}
	return listTerritory;
}

//This parses the borders section in the .map file and makes an adjacency matrix.
vector<vector<int>> MapLoader::parseBorderMatrix(string s) {
	vector<string> rows = parseRows(s);
	//Initialize a 2D vector array with the correct number of nodes.
	vector<vector<int>> matrix(size(rows), vector<int>(size(rows)));

	//Populate the matrix using the rows' information.
	for (int i = 0; i < size(rows); i++) {
		stringstream stream(rows[i]);
		int index, temp;
		stream >> index;
		while (stream >> temp) {
			matrix[index - 1][temp - 1] = 1;
		}
	}

	return matrix;
}

//Constructor with no file name
MapLoader::MapLoader() : _fileName(new string("No file.")) {
}

//Constructor with a file name
MapLoader::MapLoader(string fileName) : _fileName(new string(fileName)) {
}

//Copy Constructor
MapLoader::MapLoader(MapLoader& mapL) {
	_fileName = new string(*mapL._fileName);
}

//Destructor
MapLoader::~MapLoader() {
	delete _fileName;
}

//Define parseMap function
Map* MapLoader::parseDominationMap() {
	//Create an input stream to the file and turn the file content into a string
	ifstream inputStream(*_fileName);

	//If the file doesn't exist, return an empty map.
	if (!inputStream.is_open())
	{
		cout << "No such map!\n";
		Map* map = nullptr;
		return map;
	}

	string fileContent((istreambuf_iterator<char>(inputStream)), (istreambuf_iterator<char>()));

	//each section will be used to create Territories, Continents and the Border Matrix
	vector<string> section;

	//Define the regex for the split
	const regex separator{ "\\[\\w+\\]" };
	//Iterate through the fileContent string and split the string according to the regexp expression
	sregex_token_iterator iterator(fileContent.begin(), fileContent.end(), separator, -1);
	sregex_token_iterator end;

	while (iterator != end) {
		section.push_back(*iterator);
		++iterator;
	}


	if (section.size() < 5) {		// ADDED****
		cout << "Not a Domination Map." << endl;
		setValidMap(false);
		Map* map = nullptr;
		return map;
	}

	//Parse the different vectors needed for the creation of the map
	vector<Territory*> listTerritory = parseTerritoryList(section[3]);
	vector<Continent*> listContinent = parseContinentList(section[2], listTerritory);
	vector<vector<int>> borderMatrix = parseBorderMatrix(section[4]);
	Map* mapGame = new Map(borderMatrix, listTerritory, listContinent);


	//Checks validity of mapGame and returns Map object
	if (listTerritory.empty() || listContinent.empty()) {
		setValidMap(false);
		return mapGame;
	}
	else {
		setValidMap(true);
		return mapGame;
	}
	
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//
//										ConquestFileReader
//
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//stream insertion operator
ConquestFileReader& ConquestFileReader::operator=(const ConquestFileReader& mapL) {
	this->_fileName = mapL._fileName;
	return *this;
}

//assignment operator
ostream& operator<<(ostream& out, const ConquestFileReader& mapL) {
	out << "MapLoader's File Name: " << endl;
	out << "------------------------------" << endl;
	if (!mapL._fileName->compare("")) {
		out << "No File Name Detected" << endl;
	}
	else {
		out << mapL._fileName << endl;
	}
	return out;
}

//Constructor with no file name
ConquestFileReader::ConquestFileReader() : _fileName(new string("No file.")) {
}

//Constructor with a file name
ConquestFileReader::ConquestFileReader(string fileName) : _fileName(new string(fileName)) {
}

//Copy Constructor
ConquestFileReader::ConquestFileReader(ConquestFileReader& mapL) {
	_fileName = new string(*mapL._fileName);
	validMap = new bool(mapL.validMap);
}

//Destructor
ConquestFileReader::~ConquestFileReader() {
	delete _fileName;
	//delete validMap;
	//delete dominationMap;
	//delete conquestMap;
}

vector<string> ConquestFileReader::parseContinentsName(string s)
{
	vector<string> listContinentName;
	vector<string> rows = parseRows(s);

	//Create the vector of continent 
	for (int i = 0; i < size(rows); i++) {
		//replace(rows[i].begin(), rows[i].end(), ' ', '%');
		//replace(rows[i].begin(), rows[i].end(), '=', ' ');
		string delimiter = "=";
		string token = rows[i].substr(0, s.find(delimiter));

		///stringstream stream(rows[i]);
		stringstream stream(token);

		string name;
		stream >> name;

		//replace(name.begin(), name.end(), '%', ' ');
		listContinentName.push_back(name);
	}
	return listContinentName;
}

vector<string> ConquestFileReader::parseRows(string s)
{
	vector<string> rows;

	//Define the regex for the split
	const regex separator{ "\\n" };

	//Create the iterator object with the regex separator
	sregex_token_iterator iterator(s.begin(), s.end(), separator, -1);
	sregex_token_iterator end;

	//Loop on the iterator and remove the commented and empty row. Put each row in a vector called rows
	while (iterator != end) {
		string row = (*iterator).str(); //returns a string with a copy of the contents referred by the iterator object.
		if (row.length() == 0 || row[0] == ';') { //ignores new lines and lines with starting with a ';'
			++iterator;
			continue;
		}
		rows.push_back(*iterator); //appends row to the end of string row
		++iterator; //increments iterator to check next line with regex separator "\\n"
	}

	return rows;
}

vector<vector<int>> ConquestFileReader::parseBorderMatrix(string s, vector<Territory*>& territoryList)
{
	vector<string> rows = parseRows(s);
	vector<vector<int>> matrix(size(rows), vector<int>(size(rows)));

	//Map that maps a territory name to its index
	std::map<string, int> mapTerritory;
	for (int i = 0; i < territoryList.size(); i++) {
		mapTerritory[territoryList[i]->getName()] = i;
	}

	for (int i = 0; i < size(rows); i++) {
		replace(rows[i].begin(), rows[i].end(), ' ', '%');
		replace(rows[i].begin(), rows[i].end(), ',', ' ');
		stringstream stream(rows[i]);
		string blankString, name;
		int blankNum;
		//Remove non necessary string and int from the stream
		stream >> blankString;
		stream >> blankNum;
		stream >> blankNum;
		stream >> blankString;
		//Get all the neighbors of the territory and set them into the matrix
		while (stream >> name) {
			replace(name.begin(), name.end(), '%', ' ');
			matrix[i][mapTerritory[name]] = 1;
		}
	}
	return matrix;
}

vector<Territory*> ConquestFileReader::parseTerritoryList(string s, vector<string> continentList)
{
	vector<Territory*> listTerritory;
	vector<string> rows = parseRows(s);
	int index, continentID;
	string name, continentName;
	//Get the info neccessary to create a territory object from each row of the file
	for (int i = 0; i < rows.size(); i++) {
		replace(rows[i].begin(), rows[i].end(), ' ', '%');
		replace(rows[i].begin(), rows[i].end(), ',', ' ');
		stringstream stream(rows[i]);
		stream >> name;
		//To get past the coordinates
		stream >> index;
		stream >> index;
		stream >> continentName;
		replace(continentName.begin(), continentName.end(), '%', ' ');
		continentID = -1; //to be used for error checking later on-
		for (int i = 0; i < continentList.size(); i++) {
			if (continentName == continentList[i]) {
				continentID = i;
				break;
			}
		}
		replace(name.begin(), name.end(), '%', ' ');
		Territory* territory = new Territory(i, 0, continentID, 696969, name); //696969 -> Player?
		listTerritory.push_back(territory);
	}

	return listTerritory;
}

vector<Continent*> ConquestFileReader::parseContinentList(vector<string> continentName, vector<Territory*>& territoryList)
{
	vector<Continent*> listContinent;
	for (int i = 0; i < continentName.size(); i++) {
		vector<Territory*> listTerritory;
		for (int j = 0; j < territoryList.size(); j++) {
			if (territoryList[j]->getContinentID() == i) {
				listTerritory.push_back(territoryList[j]);
			}
		}
		listContinent.push_back(new Continent(continentName[i], listTerritory, i, 0)); //Continent(string name, vector<Territory*> territoryList, int id, int bonusArmies);
	}
	return listContinent;
}

Map* ConquestFileReader::parseConquestMap()
{
	//Create an input stream to the file and turn the file content into a string
	ifstream inputStream(*_fileName);
	string fileContent((istreambuf_iterator<char>(inputStream)), (istreambuf_iterator<char>()));

	if (!inputStream.is_open()) // ADDED******************************************************
	{
		cout << "No such map!\n";
		Map* map = nullptr;
		return map;
	}

	vector<string> section;

	//Define the regex for the split
	const regex separator{ "\\[\\w+\\]" };
	//Iterate through the fileContent string and split the string according to the regexp expression
	sregex_token_iterator iterator(fileContent.begin(), fileContent.end(), separator, -1);
	sregex_token_iterator end;

	while (iterator != end) {
		section.push_back(*iterator);
		++iterator;
	}

	if (section.size() > 4) { //ADDED**************
		cout << "Not a Conquest Map." << endl;
		setValidMap(false);
		Map* map = nullptr;
		return map;
	}

	//Parse the different vectors needed for the creation of the map
	vector<string> listNameContinent = parseContinentsName(section[2]);
	vector<Territory*> listTerritory = parseTerritoryList(section[3], listNameContinent);
	vector<vector<int>> borderMatrix = parseBorderMatrix(section[3], listTerritory);
	vector<Continent*> listContinent = parseContinentList(listNameContinent, listTerritory);

	Map* mapGame = new Map(borderMatrix, listTerritory, listContinent); //Map* mapGame = new Map(borderMatrix, listTerritory, listContinent);

	//Checks validity of mapGame and returns Map object
	if (listTerritory.empty() || listContinent.empty()) {
		setValidMap(false);
		return mapGame;
	}
	else {
		setValidMap(true);
		return mapGame;
	}

	
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//
//										ConquestFileReaderAdapter
//
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//stream insertion operator
ConquestFileReaderAdapter& ConquestFileReaderAdapter::operator=(const ConquestFileReaderAdapter& mapL)
{
	this->_fileName = mapL._fileName;
	return *this;
}

//assignment operator
ostream& operator<<(ostream& out, const ConquestFileReaderAdapter& mapL) {
	out << "MapLoader's File Name: " << endl;
	out << "------------------------------" << endl;
	if (!mapL._fileName->compare("")) {
		out << "No File Name Detected" << endl;
	}
	else {
		out << mapL._fileName << endl;
	}
	return out;
}

//Constructor with no file name
ConquestFileReaderAdapter::ConquestFileReaderAdapter() : _fileName(new string("No file.")) {
}

//Constructor with a file name
ConquestFileReaderAdapter::ConquestFileReaderAdapter(string fileName) : _fileName(new string(fileName)) {
}

//Copy Constructor
ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReaderAdapter& mapL) {
	_fileName = new string(*mapL._fileName);
	_validMap = new bool(mapL._validMap);
	_conquestMap = new bool(mapL._conquestMap);
}

//Destructor
ConquestFileReaderAdapter::~ConquestFileReaderAdapter() {
	delete _fileName;
	//delete validMap;
	//delete dominationMap;
	//delete conquestMap;
}

bool ConquestFileReaderAdapter::getConquestMap() {
	return _conquestMap;
}

void ConquestFileReaderAdapter::setConquestMap(int conquestMap) {
	if (conquestMap == 0) {
		_conquestMap = false;
	}
	else {
		_conquestMap = true;
	}
}

string ConquestFileReaderAdapter::getFileName() {
	return *_fileName;
}

void ConquestFileReaderAdapter::setFileName(string fileName) {
	*_fileName = fileName;
}

Map* ConquestFileReaderAdapter::parseMap() {

	MapLoader::_fileName = _fileName;
	ConquestFileReader::_fileName = _fileName;

	if (_conquestMap)
	{
		if (ConquestFileReader::getValidMap()) 
			_validMap = true; //I'm so mad about this I might go blind.
		return parseConquestMap();
	}
	else {
		//MapLoader* maploader = new MapLoader(*_fileName);
		if (MapLoader::getValidMap()) 
			_validMap = true;
		return parseDominationMap();
	}
}