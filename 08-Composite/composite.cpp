#include "composite.h"  

class CreatureComp
{
private:
	enum Abilities {STR, AGL, INT, COUNT};
	std::array<int, COUNT> abilities;

public:
	CreatureComp() {}
	~CreatureComp() {}

	int getStrength() const {
		return abilities[STR];
	}

	void setStrength(int value) {
		this->abilities[STR] = value;
	}

	int getAgility() const {
		return abilities[AGL];
	}

	void setAgility(int value) {
		this->abilities[AGL] = value;
	}

	int getIntelligence() const {
		return abilities[INT];
	}

	void setIntelligence(int value) {
		this->abilities[INT] = value;
	}

	int sum() const {
		int res = std::accumulate(abilities.begin(), abilities.end(), 0);
		return res;
	}

	double average() const {
		return sum() / static_cast<double>(COUNT);
	}

	int max() {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};


void creatureExample() {

    CreatureComp creature;
    creature.setAgility(30);
    creature.setIntelligence(100);
    creature.setStrength(50);
    print("Composite Example: ", "Creature");
    print("sum: ", creature.sum());
    print("average: ", creature.average());
    print("max: ", creature.max());
}