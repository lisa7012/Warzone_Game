#include<iostream>
#include "Map.h"

using namespace std;

extern int nbrOfCountries;
extern int nbrOfContinents;

void testFunction();

//int main()
//{
//	testFunction();
//	return 0;
//}

//void testFunction() // To avoid memory leak 
//{
//	Territory* T1 = new Territory(123, 1, 123, "P1", "T1");
//	Territory* T2 = new Territory(456, 2, 123, "P1", "T2");
//	Territory* T5 = new Territory(789, 3, 123, "P1", "T5");
//
//	Territory* T3 = new Territory(123, 1, 456, "P2", "T3");
//	Territory* T4 = new Territory(456, 2, 456, "P2", "T4");
//	Territory* T6 = new Territory(789, 3, 456, "P2", "T6");
//
//	cout << nbrOfCountries << " territories made." << endl;
//
//	vector<Territory*> TerritoryList = { T1, T2, T3, T4, T5, T6 };
//	vector<Territory*> TerritoryList1 = { T1, T2, T5 };
//	vector<Territory*> TerritoryList2 = { T3, T4, T6 };
//
//
//	Continent* C1 = new Continent("C1", TerritoryList1, 123);
//	Continent* C2 = new Continent("C2", TerritoryList2, 456);
//
//	cout << nbrOfContinents << " continents made." << endl;
//
//	vector<Continent*> ContinentList = { C1, C2 };
//
//	vector<int> row1 = { 0, 0, 0, 0, 0, 0 }; //C1 neighbors with C2
//	vector<int> row2 = { 1, 0, 0, 0, 1, 0 }; //C2 neighbors with C1 and C5
//	vector<int> row3 = { 0, 0, 0, 1, 0, 0 }; //C3 neighbors with C4
//	vector<int> row4 = { 0, 0, 1, 0, 0, 1 }; //C4 neighbors with C3 and C6
//	vector<int> row5 = { 0, 1, 0, 0, 0, 0 }; //C5 neighbors with C2
//	vector<int> row6 = { 0, 0, 0, 1, 0, 0 }; //C6 neighbors with C4
//
//	vector<vector<int>> matrix = { row1, row2, row3, row4, row5, row6 };
//
//	Map* worldMap = new Map(matrix, TerritoryList, ContinentList);
//
//	worldMap->displayMap();
//
//	cout << "\nChecking validity" << endl;
//	if (worldMap->validate())
//	{
//		cout << "valid map." << endl;
//	}
//	else
//	{
//		cout << "invalid map." << endl;
//	}
//
//	////deleting
//	T1 = nullptr;
//	T2 = nullptr;
//	T3 = nullptr;
//	T4 = nullptr;
//	T5 = nullptr;
//	T6 = nullptr;
//
//	for (int i = 0; i < TerritoryList.size(); i++)
//	{
//		TerritoryList[i] = nullptr;
//	}
//
//	for (int i = 0; i < TerritoryList1.size(); i++)
//	{
//		TerritoryList1[i] = nullptr;
//	}
//
//	for (int i = 0; i < TerritoryList2.size(); i++)
//	{
//		TerritoryList2[i] = nullptr;
//	}
//
//	matrix.clear();
//	row1.clear();
//	row2.clear();
//	row3.clear();
//	row4.clear();
//	row5.clear();
//	row6.clear();
//	delete worldMap;
//}
