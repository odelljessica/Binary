#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Starship {
public:
    class Weapon {
    public:
        Weapon(string s, int i, float f) {
            this->weaponName = s;
            this->power = i;
            this->consumption = f;
        }
        Weapon(){}

        void printWeapons() {
            cout << weaponName << ", " << power << ", " << consumption << endl;

        }

        string weaponName;
        int power = 0;
        float consumption = 0;

    };

    Starship(string n, string c, short l, int cap, float s, vector<Weapon> i) {
        this->name = n;
        this->shipClass = c;
        this->length = l;
        this->capacity = cap;
        this->speed = s;
        this->inventory = i;

    }
    Starship() {}

    int firePower() {
        unsigned i = 0;
        int firepower = 0;
        while (i < inventory.size()) {
            firepower = firepower + inventory[i].power;
            i++;
        }
        return firepower;
    }

    void printOut() {
        this->name = name;
        this->shipClass = shipClass;
        this->capacity = capacity;
        this->inventory = inventory;
        this->length = length;
        this->speed = speed;
        cout << "Name: " << name << "\nClass: " << shipClass << "\nLength: " << length << "\nShield capacity: " << capacity << "\nMaximum Warp: " << speed << endl;
        cout << "Armaments: " << endl;
        unsigned i = 0;
        int firepower = 0;
        while (i < inventory.size()) {
            inventory[i].printWeapons();
            firepower = firepower + inventory[i].power;
            i++;
        }
        if (inventory.size() != 0) {
            cout << "Total firepower: " << firepower << endl;
        }
        else cout << "Unarmed" << endl;

    }

    string shipClass = "";
    string name = "";
    int capacity = 0;
    int weaponCount = 0;
    short length = 0;
    float speed = 0;
    Weapon weapon;
    vector<Weapon> inventory;

};

Starship starship;
Starship::Weapon weapon;
vector<Starship> vectorStarships;
string filename = "";


    vector<Starship> FileConverter(string filename) {
        vector<Starship> vectorStarships;
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            int count;
            file.read((char *)&count, 4);
            int i = 0, j = 0;
            int length;
            while (i < count) {
                vectorStarships.push_back(starship);
                file.read((char *) &length, 4);
                char * shipName = new char[length];
                file.read(shipName, length * sizeof(shipName[0]));
                string shipName2(shipName);
                vectorStarships[i].name = shipName2;
                delete[] shipName;

                file.read((char *) &length, 4);
                char * newClass = new char[length];
                file.read(newClass, length * sizeof(newClass[0]));
                string newClass2(newClass);
                vectorStarships[i].shipClass = newClass2;
                delete[] newClass;

                file.read((char *) &vectorStarships[i].length, 2);
                file.read((char *) &vectorStarships[i].capacity, 4);
                file.read((char *) &vectorStarships[i].speed, 4);
                file.read((char *) &vectorStarships[i].weaponCount, 4);

                if (vectorStarships[i].weaponCount == 0) {
                }
                else {
                    j = 0;
                    while (j < vectorStarships[i].weaponCount) {
                        vectorStarships[i].inventory.push_back(weapon);
                        file.read((char *) &length, 4);
                        char * newName = new char[length];
                        file.read(newName, length * sizeof(newName[0]));
                        string newName2(newName);
                        vectorStarships[i].inventory[j].weaponName = newName2;
                        delete[] newName;
                        file.read((char *) &vectorStarships[i].inventory[j].power, 4);
                        file.read((char *) &vectorStarships[i].inventory[j].consumption, 4);
                        j++;
                    }

                }
                i++;
            }
            file.close();
        }
        return vectorStarships;
}

int main()
{
    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;

    if (option == 1) {
        filename = "friendlyships.shp";
        vectorStarships = FileConverter(filename);
    }
    if (option == 2) {
        filename = "enemyships.shp";
        vectorStarships = FileConverter(filename);
    }
    if (option == 3) {
        vector<Starship> starships1, starships2;
        filename = "friendlyships.shp";
        starships1 = FileConverter(filename);
        vectorStarships.insert(vectorStarships.end(), starships1.begin(), starships1.end());
        filename = "enemyships.shp";
        starships2 = FileConverter(filename);
        vectorStarships.insert(vectorStarships.end(), starships2.begin(), starships2.end());

    }

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;

    cin >> option;

    if (option == 1) {
        unsigned i = 0;
        while (i < vectorStarships.size()) {
            vectorStarships[i].printOut();
            cout << endl;
            i++;
        }
    }

    if (option == 2) {
        unsigned i = 0, j = 0;
        Starship strong = vectorStarships[0];
        Starship::Weapon strongest = vectorStarships[0].inventory[0];
        while (i < vectorStarships.size()) {
            if (vectorStarships[i].weaponCount != 0) {
                while (j < vectorStarships[i].inventory.size()) {
                    if (vectorStarships[i].inventory[j].power > strongest.power) {
                        strongest = vectorStarships[i].inventory[j];
                        strong = vectorStarships[i];
                    }
                    j++;
                }
            }
            i++;
            }
        strong.printOut();
    }

    if (option == 3) {
        unsigned i = 0;
        Starship strongest = vectorStarships[0];
        while (i < vectorStarships.size()) {
            if (vectorStarships[i].firePower() > strongest.firePower()) {
                strongest = vectorStarships[i];
            }
            i++;
        }
        strongest.printOut();
    }

    if (option == 4) {
        unsigned i = 0;
        Starship weakest = vectorStarships[0];
        while (i < vectorStarships.size()) {
            if ((vectorStarships[i].firePower() < weakest.firePower()) && (vectorStarships[i].inventory.size() != 0)) {
                weakest = vectorStarships[i];
            }
            i++;
        }
        weakest.printOut();
    }

    if (option == 5) {
        unsigned i = 0;
        vector<Starship> unarmed;
        while (i < vectorStarships.size()) {
            if (vectorStarships[i].inventory.size() == 0) {
                unarmed.push_back(vectorStarships[i]);
            }
            i++;
        }
        for (unsigned j = 0; j < unarmed.size(); j++) {
            unarmed[j].printOut();
        }
     }
    return 0;
}