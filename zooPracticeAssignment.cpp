#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class Animal {
public:
    Animal(std::string name, int age, std::string species) : name(name), age(age), species(species) {}

    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    std::string getSpecies() const {
        return species;
    }

    virtual std::string getEnclosure() const = 0;

protected:
    std::string name;
    int age;
    std::string species;
};

class Hyena : public Animal {
public:
    Hyena(std::string name, int age) : Animal(name, age, "Hyena") {}

    std::string getEnclosure() const override {
        return "Grassland";
    }
};

class Lion : public Animal {
public:
    Lion(std::string name, int age) : Animal(name, age, "Lion") {}

    std::string getEnclosure() const override {
        return "Savannah";
    }
};

class Tiger : public Animal {
public:
    Tiger(std::string name, int age) : Animal(name, age, "Tiger") {}

    std::string getEnclosure() const override {
        return "Jungle";
    }
};

class Bear : public Animal {
public:
    Bear(std::string name, int age) : Animal(name, age, "Bear") {}

    std::string getEnclosure() const override {
        return "Forest";
    }
};

void processAnimals(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile.is_open()) {
        std::cerr << "Error opening input file: " << inputFile << std::endl;
        return;
    }

    if (!outFile.is_open()) {
        std::cerr << "Error opening output file: " << outputFile << std::endl;
        return;
    }

    std::vector<Animal*> animals;
    std::map<std::string, int> speciesCount;

    std::string line;
    while (std::getline(inFile, line)) {
        std::string name, species;
        int age;
        std::istringstream iss(line);
        iss >> name >> age >> species;

        Animal* animal;
        if (species == "Hyena") {
            animal = new Hyena(name, age);
        }
        else if (species == "Lion") {
            animal = new Lion(name, age);
        }
        else if (species == "Tiger") {
            animal = new Tiger(name, age);
        }
        else if (species == "Bear") {
            animal = new Bear(name, age);
        }
        else {
            std::cerr << "Unknown species: " << species << std::endl;
            continue;
        }

        animals.push_back(animal);
        speciesCount[species]++;
    }

    outFile << "Species\tName\tAge\tCount" << std::endl;
    for (const auto& animal : animals) {
        outFile << animal->getSpecies() << "\t" << animal->getName() << "\t" << animal->getAge() << "\t" << speciesCount[animal->getSpecies()] << std::endl;
    }

    for (const auto& pair : speciesCount) {
        std::cout << "Total " << pair.first << ": " << pair.second << std::endl;
    }
}

int main() {
    processAnimals("arrivingAnimals.txt", "newAnimals.txt");
    return 0;
}