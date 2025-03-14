#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Automobile {
protected:
    string date;
    string carNumber;
public:
    Automobile(const string& date, const string& carNumber)
        : date(date), carNumber(carNumber) {
    }
    virtual ~Automobile() {}
    virtual void print() const {
        cout << "Date: " << date << ", Number: " << carNumber;
    }
};

class PassengerCar : public Automobile {
private:
    string color;
    int speed;
public:
    PassengerCar(const string& date, const string& carNumber, const string& color, int speed)
        : Automobile(date, carNumber), color(color), speed(speed) {
    }
    void print() const override {
        cout << "Passenger Car -> ";
        Automobile::print();
        cout << ", Color: " << color << ", Speed: " << speed << " km/h";
    }
};

class Truck : public Automobile {
private:
    int weight;
public:
    Truck(const string& date, const string& carNumber, int weight)
        : Automobile(date, carNumber), weight(weight) {
    }
    void print() const override {
        cout << "Truck -> ";
        Automobile::print();
        cout << ", Weight: " << weight << " kg";
    }
};

vector<Automobile*> parseFile(const string& filename) {
    vector<Automobile*> cars;
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file: " << filename << endl;
        return cars;
    }
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string token;
        vector<string> tokens;
        while (getline(iss, token, ';')) {
            tokens.push_back(token);
        }
        if (tokens.size() == 2) {
            string date = tokens[0];
            string carNumber = tokens[1];
            cars.push_back(new Automobile(date, carNumber));
        }
        else if (tokens.size() == 3) {
            string date = tokens[0];
            string carNumber = tokens[1];
            int weight = stoi(tokens[2]);
            cars.push_back(new Truck(date, carNumber, weight));
        }
        else if (tokens.size() == 4) {
            string date = tokens[0];
            string carNumber = tokens[1];
            string color = tokens[2];
            int speed = stoi(tokens[3]);
            cars.push_back(new PassengerCar(date, carNumber, color, speed));
        }
        else {
            cerr << "Invalid data format: " << line << endl;
        }
    }
    return cars;
}

int main() {
    vector<Automobile*> cars = parseFile("cars.txt");
    for (const auto& car : cars) {
        car->print();
        cout << endl;
    }
    for (auto car : cars) {
        delete car;
    }
}
