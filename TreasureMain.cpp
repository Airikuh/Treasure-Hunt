#include <stack>
#include <iostream>
#include <string>
#include<vector>
#include<unordered_map>
#include <unordered_set>


using namespace std;

class City;

class Map {
public:
	City* _toCity;
	int noT;

	Map(City* toCity, int no){
		_toCity = toCity;
		noT = no;
	}
};

class City {
public:
	vector<Map*> maps;
	bool treasureFound;
	int sMap;


	City(bool treasure, int specialMap)	{
		treasureFound = treasure;
		sMap = treasure ? 0 : specialMap;
	}

	~City()	{
		for (auto map : maps) {
			delete map;
		}
	}
	void addCity(City* c, int no)	{
		bool found = false;
		for (auto map : maps) {
			if (map->_toCity == c) {
				found = true;
				break;
			}
		}
		if (!found && c != this)		{
			maps.push_back(new Map(c, no));
			c->addCity(this, no);
		}
	}
};

bool TreasureReachable(City const* sourceCity){
	unordered_map<int, City const*> unreachedMaps;
	unordered_set<int> waysToT;
	unordered_set<City const*> checked;
	stack<City const*> check;
	check.push(sourceCity);

	while (!check.empty()) {
		City const* city = check.top();
		check.pop();
		if (city->treasureFound) {
			return true;
		}
		if (checked.find(city) == checked.end()) {
			checked.insert(city);
			if (city->sMap) {
				waysToT.insert(city->sMap);
				if (unreachedMaps[city->sMap]) {
					checked.erase(unreachedMaps[city->sMap]);
					check.push(unreachedMaps[city->sMap]);
					unreachedMaps.erase(city->sMap);
				}
			}
			for (auto map : city->maps) {
				if (map->noT) {
					if (waysToT.find(map->noT) != waysToT.end()) {
						waysToT.erase(map->noT);
					}
					else {
						unreachedMaps[map->noT] = city;
						continue;
					}
				}
				check.push(map->_toCity);
			}
		}
	}
	return false;
}

void display(string c) {
	cout << "Treasure Found!!! " << endl;
	cout << "Head to City " << c << " And Collect Your Treasure!" << endl;
}

int displayChoices() {
	int choice;
	string cities1[] = { "Detroit","New York", "Boston", "Miami" };
	string cities2[] = { "Ann Arbor","San Diego", "Fremont", "Calexico" };
	string cities3[] = { "Imperial","Salt Lake City", "Phoenix", "Port Huron" };

	cout << "Which Map Would you like to check?" << endl;

		cout << "Press 1 For Map 1: " << endl;
	for (int i = 0; i < 4; i++) {
		cout << cities1[i] << " ";
	}
	cout << endl;
	cout << "Press 2 For Map 2: " << endl;
	for (int i = 0; i < 4; i++) {
		cout << cities2[i] << " ";
	}
	cout << endl;
	cout << "Press 3 For Map 3: " << endl;
	for (int i = 0; i < 4; i++) {
		cout << cities3[i] << " ";
	}
	cout << endl;
	cout << "Or Press 0 to Quit!" << endl;

	cin >> choice;
	return(choice);
}
void citiesCheck1() {
	City a(false, 2);
	City b(false, 0);
	City c(true, 1);
	City d(false, 0);

	b.addCity(&c, 1);
	c.addCity(&d, 1);
	d.addCity(&a, 0);

	if (TreasureReachable(&a)) {
		string d = "Detroit";
		display(d);
	}
	if (TreasureReachable(&b)) {
		string n = "New York";
		display(n);
	}
	if (TreasureReachable(&c)) {
		string d = "Boston";
		display(d);
	}
	if (TreasureReachable(&d)) {
		string d = "Miami";
		display(d);
	}

}

void citiesCheck2() {


	City e(false, 0);
	City f(false, 1);
	City g(false, 0);
	City h(true, 2);



	f.addCity(&h, 0);
	g.addCity(&f, 1);
	h.addCity(&g, 2);


	if (TreasureReachable(&e)) {
		string aa = "Ann Arbor";
		display(aa);
	}
	if (TreasureReachable(&f)) {
		string sd = "San Diego";
		display(sd);
	}
	if (TreasureReachable(&g)) {
		string ff = "Fremont";
		display(ff);
	}
	if (TreasureReachable(&h)) {
		string cc = "Calexico";
		display(cc);
	}
}

void citiesCheck3() {


	City i(false, 2);
	City j(false, 1);
	City k(false, 0);
	City l(true, 2);


	j.addCity(&l, 1);
	k.addCity(&j, 1);
	l.addCity(&i, 1);


	if (TreasureReachable(&i)) {
		string im = "Imperial";
		display(im);
	}
	if (TreasureReachable(&j)) {
		string slc = "Salt Lake City";
		display(slc);
	}
	if (TreasureReachable(&k)) {
		string p = "Phoenix";
		display(p);
	}
	if (TreasureReachable(&l)) {
		string ph = "Port Huron";
		display(ph);
	}
}

int main() {
	string cities1[] = { "Detroit","New York", "Boston", "Miami" };
	string cities2[] = { "Ann Arbor","San Diego", "Fremont", "Calexico" };
	string cities3[] = { "Imperial","Salt Lake City", "Phoenix", "Port Huron" };
	int quit = 1;
	
	while (quit != 0) {
		int option{ displayChoices() };
		switch (option) {
		case 1: {
			citiesCheck1();
			break; }
		case 2: {
			citiesCheck2();
			break; }
		case 3: {
			citiesCheck3();
			break;
		}
		case 0: {
			quit = 0;
			break;
		}
		default: {
			cout << "Invalid Operations Selected " << endl;
		}
		}
	}



	return 0;
}
