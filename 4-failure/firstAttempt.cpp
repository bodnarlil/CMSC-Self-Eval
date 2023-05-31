// Lilia Bodnar
// In-class week 2 day 1
// Worked on: 3/30/23 and 3/31/23

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// class organism
class organism {
public:
	int age = (rand() % 1000);
	std::string name = "not named";
	bool aliveOrNot = true;

	// operator override to compare by age
	bool operator< (organism& organismTwo) {
		if (age < organismTwo.age)
			return true;
		else
			return false;
	};
};

// class population
class population {
public:
	vector<organism>popvec;

	// make 20 random organism objects using a for-loop
	void populate() {
		for (int i = 0; i < 20; i++) {
			organism newOrganism;
			popvec.push_back(newOrganism);
		};
	};

	void populate();

	// sort using st::sort
	sort(popvec.begin(), popvec.end());
};

main() {
	population();
};