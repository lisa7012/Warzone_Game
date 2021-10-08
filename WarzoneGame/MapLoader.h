#pragma once
#include <iostream> 
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>
#include "Map.h"
#include <map>

using namespace std;

//MapLoader for Domination styled .map
class MapLoader {
protected:
	//instance variable
	string* _fileName;
	bool validMap;
	bool _mapTypeValidDomination; // ADDED *********

public:
	//stream operator
	friend ostream& operator<<(ostream& out, const MapLoader& mapL);
	//assignment operator
	MapLoader& operator=(const MapLoader& mapL);
	//Functions to extract the information from a .map file 
	//to be defined in MapLoader.cpp
	vector<string> parseLine(string s);
	vector<string> parseRows(string s);
	vector<vector<int>> parseBorderMatrix(string s);
	vector<Territory*> parseTerritoryList(string s);
	vector<Continent*> parseContinentList(string s, vector<Territory*> territoryList);

	//Constructors and Destroyer
	MapLoader();
	MapLoader(string fileName);
	MapLoader(MapLoader& mapL);
	~MapLoader();

	//Function to load a map
	Map* parseDominationMap();

	bool getValidMap() { return validMap; };
	void setValidMap(bool b) { validMap = b; };

	//ADDED ***********************************
	bool getMapTypeValid() { return _mapTypeValidDomination; };
	void setMapTypeValid(bool b) { _mapTypeValidDomination = b; };
};

//MapLoader for Conquest styled .map
class ConquestFileReader {
protected:
	//instance variable
	string* _fileName;
	bool validMap;
	bool _mapTypeValidConquest; //ADDED *******************

public:
	//stream operator
	friend ostream& operator<<(ostream& out, const ConquestFileReader& mapL);
	//assignment operator
	ConquestFileReader& operator=(const ConquestFileReader& mapL);
	//Functions to extract the information from a .map file 
	//to be defined in MapLoader.cpp
	//Parsing methods for new file
	vector<string> parseContinentsName(string s);
	vector<string> parseRows(string s);
	vector<vector<int>> parseBorderMatrix(string s, vector<Territory*>& countryList);
	vector<Territory*> parseTerritoryList(string s, vector<string> continentList);
	vector<Continent*> parseContinentList(vector<string> continentName, vector<Territory*>& countryList);

	//Constructors and Destroyer
	ConquestFileReader();
	ConquestFileReader(string fileName);
	ConquestFileReader(ConquestFileReader& mapL);
	~ConquestFileReader();

	//Function to load a map
	Map* parseConquestMap();

	bool getValidMap() { return validMap; };
	void setValidMap(bool b) { validMap = b; };

	//ADDED ***********************************
	bool getMapTypeValidConquest() { return _mapTypeValidConquest; };
	void setMapTypeValidConquest(bool b) { _mapTypeValidConquest = b; };
};

//ConquestFileReaderAdapter
class ConquestFileReaderAdapter : public MapLoader, public ConquestFileReader {
private:
	string* _fileName;
	bool _validMap;
	bool _conquestMap;
public:
	//stream operator
	friend ostream& operator<<(ostream& out, const ConquestFileReaderAdapter& mapL);
	//assignment operator
	ConquestFileReaderAdapter& operator=(const ConquestFileReaderAdapter& mapL);
	//Constructors and Destroyer
	ConquestFileReaderAdapter();
	ConquestFileReaderAdapter(string filename);
	ConquestFileReaderAdapter(ConquestFileReaderAdapter& mapL);
	~ConquestFileReaderAdapter();

	bool getConquestMap();
	void setConquestMap(int conquestMap);

	string getFileName();
	void setFileName(string fileName);

	bool getValidMap() { return _validMap; };
	void setValidMap(bool validMap) { _validMap = validMap; };

	Map* parseMap();
};