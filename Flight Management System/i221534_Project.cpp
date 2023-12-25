#include <iostream>
#include "side functions.h"
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

void registerAsPassenger();
void createPassword(string pwd, bool& hasUpperCase, bool& hasLowerCase, bool& hasNumeric, bool& hasSpecialChar);
int GetHoursUntil_Flight();
void SetHoursUntil_Flight(int f);
int GetTotalCities();
void SetTotalCities(int f);
void takeValidInput(int& input);
void DisplayFlightSchedule();
void DisplayFlightSchedule(int i);
void searchSchedule();
bool planesMade = false;

void takeValidInput(int& input) {
	cin >> input;
	while (cin.fail()) {
		cin.clear(); // Clear the error flags.
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input.
		cout << "Invalid Choice. Please enter a Number:";
		cin >> input;
	}
}


class Airplane {
	unsigned int ID;
	static int totalPlanes;
	unsigned int seatingCapacityEconomy;
	unsigned int seatingCapacityBusiness;
	string currentAirportCity;
	string currentAirportLocation;
public:
	Airplane() {
		seatingCapacityEconomy = 50;
		seatingCapacityBusiness = 10;

	}
	int getID() {
		return ID;
	}
	int getSeatingCapacityEconomy() {
		return seatingCapacityEconomy;
	}
	int getSeatingCapacityBusiness() {
		return seatingCapacityBusiness;
	}
	string getAirportCity() {
		return currentAirportCity;
	}
	string getAirportLocation() {
		return currentAirportLocation;
	}
	static int getTotalPlanes() {
		return totalPlanes;
	}
	void setSeatingCapacityEconomy(int n) {
		seatingCapacityEconomy = n;
	}
	void setSeatingCapacityBusiness(int n) {
		seatingCapacityBusiness = n;
	}
	void setAirportCity(string s) {
		currentAirportCity = s;
	}
	void setAirportLocation(string s) {
		currentAirportLocation = s[0];
	}
	void setID(int id) {
		ID = id;
	}
	static void increaseTotalPlanes() {
		totalPlanes++;
	}
	void operator=(Airplane& A2) {
		seatingCapacityBusiness = A2.seatingCapacityBusiness;
		seatingCapacityEconomy = A2.seatingCapacityEconomy;
	}
};

int Airplane::totalPlanes = 0;

class Airport {
	char location;
	string city;
	Airplane* airplanes;
	int maxPlanes = 5;
	int PlanesAtAirport;
public:
	Airport() {
		maxPlanes = 5;
		airplanes = new Airplane[maxPlanes];
		if (Airplane::getTotalPlanes() < 50) {
			PlanesAtAirport = 5;
			ifstream fin("Airplanes.txt");
			fin.seekg(ios::beg);
			int linesSkipped = 0;
			for (int i = 0; i < linesSkipped + maxPlanes; i++) {
				string str;
				if (i < Airplane::getTotalPlanes() || planesMade) {
					getline(fin, str);
					linesSkipped++;
				}
				else {
					if (!planesMade) {
						fin >> str;
						airplanes[i - linesSkipped].setID(stoi(str));
						fin >> str;
						airplanes[i - linesSkipped].setAirportCity(str);
						fin >> str;
						airplanes[i - linesSkipped].setAirportLocation(str);
						fin >> str;
						airplanes[i - linesSkipped].setSeatingCapacityEconomy(stoi(str));
						fin >> str;
						airplanes[i - linesSkipped].setSeatingCapacityBusiness(stoi(str));
						Airplane::increaseTotalPlanes();
					}
				}
			}
			fin.close();
		}
	}
	string getCity() {
		return city;
	}
	char getLocation() {
		return location;
	}
	Airplane* getAirplanesList() {
		return airplanes;
	}
	const int getMaxPlanes() {
		return maxPlanes;
	}
	int getPlanesAtAirport() {
		return PlanesAtAirport;
	}
	void setCity(string s) {
		city = s;
	}
	void setLocation(char L) {
		location = L;
	}
	void addPlane(Airplane& A) {

	}

	void operator=(Airport& A2) {
		location = A2.getLocation();
		city = A2.getCity();
		PlanesAtAirport = A2.getPlanesAtAirport();
		for (int i = 0; i < A2.getPlanesAtAirport(); i++) {
			airplanes[i] = A2.getAirplanesList()[i];
		}
	}
};

class Distance {
	string destination;
	int duration;
public:
	Distance() {}
	string getDestination() {
		return destination;
	}
	int getDuration() {
		return duration;
	}
	void setDestination(string s) {
		destination = s;
	}
	void setDuration(int h) {
		duration = h;
	}
};

class City {
	string name;
	string countryName;
	Airport* airports;
	Distance* durationHours;
	string filename;
public:
	City() {
		airports = new Airport[2];
		airports[0].setLocation('N');
		airports[0].setCity(name);
		airports[1].setLocation('S');
		airports[1].setCity(name);
		durationHours = new Distance[10];

	}
	string getName() {
		return name;
	}
	string getCountryName() {
		return countryName;
	}
	Distance* getDurationHoursList() {
		return durationHours;
	}
	//void setDurationHoursList(Distance &d) {
	//	durationHours = d;
	//}
	void setName(string n) {
		name = n;
	}
	void setCountryName(string s) {
		countryName = s;
	}
	Airport* getAirportsList() {
		return airports;
	}
	void operator=(const City& C) {
		name = C.name;
	}
};

class Country {
	string name;
	City* cities;
	int citiesInCountry;
	static int totalCities;
public:
	Country(string name = "Pakistan") : name(name) {
		citiesInCountry = 5;
		totalCities += citiesInCountry;
		cities = new City[citiesInCountry];
		if (name == "Pakistan") {
			ifstream fin("Airplanes.txt");
			int i;
			for (i = 0; !fin.eof(); i++) {
				string str1, str2, str3;
				fin >> str1;
				fin >> str2;
				getline(fin, str3);
				bool alreadyAdded = false;
				for (int j = 0; j < i; j++) {
					if (str2 == cities[j].getName()) {
						alreadyAdded = true;
						break;
					}
				}
				if (alreadyAdded) {
					i--;
					continue;
				}
				cities[i].setName(str2);
				cities[i].getAirportsList()[0].setCity(str2);
				cities[i].getAirportsList()[1].setCity(str2);
				string filename = cities[i].getAirportsList()[1].getCity() + ".txt";
				ifstream fin2(filename);
				for (int j = 0; !fin2.eof(); j++) {
					string str;
					fin2 >> str;
					cities[i].getDurationHoursList()[j].setDestination(str);
					fin2 >> str;
					cities[i].getDurationHoursList()[j].setDuration(stoi(str));
					if (j == 9) {
						break;
					}
				}
				cities[i].setCountryName(name);
				if (i == 4) {
					break;
				}
			}
			fin.close();
		}
		else {
			ifstream fin("international cities.txt");
			int i;
			for (i = 0; !fin.eof(); i++) {
				string str1;
				fin >> str1;
				cities[i].setName(str1);
				cities[i].getAirportsList()[0].setCity(str1);
				cities[i].getAirportsList()[1].setCity(str1);
				string filename = cities[i].getAirportsList()[1].getCity() + ".txt";
				ifstream fin2(filename);
				for (int j = 0; !fin.eof(); j++) {
					string str;
					fin2 >> str;
					cities[i].getDurationHoursList()[j].setDestination(str);
					fin2 >> str;
					cities[i].getDurationHoursList()[j].setDuration(stoi(str));
					if (j == 9) {
						break;
					}
				}
				cities[i].setCountryName(name);
				if (i == 4) {
					break;
				}
			}

			fin.close();
		}
	}
	string getName() {
		return name;
	}
	static int getTotalCities() {
		return totalCities;
	}
	City* getCitiesList() {
		return cities;
	}
	static void setTotalCities(int t) {
		totalCities = t;
	}
	int getCitiesInCountry() {
		return citiesInCountry;
	}
	void setCitiesIncountry(int x) {
		citiesInCountry = x;
	}
};

int Country::totalCities = 0;

Country P;
Country I("International");


int GetTotalCities() {
	return Country::getTotalCities();
}
void SetTotalCities(int c) {
	Country::setTotalCities(c);
}
class Clock {
	int hour;
	int day;
	int month;
	int year;
public:
	Clock() {
		hour = 0;
		day = 0;
		month = 0;
		year = 2023;
		getCurrentTime();
	}
	void getCurrentTime() {
		int Time = time(NULL);
		year = (Time / 31536000) + 1970;
		Time %= 31536000;
		month = Time / 2628003;
		Time %= 2628003;
		day = Time / 86400;
		Time %= 86400;
		hour = Time / 3600;
	}
	Clock& increaseTime(int hours) {
		hour += hours;
		if (hours >= 0) {
			while (hour >= 24) {
				day++;
				hour -= 24;
			}
			while (day >= 30) {
				month++;
				day -= 30;
			}
			while (month >= 12) {
				year++;
				month -= 12;
			}
		}
		else {
			while (hour < 0) {
				day--;
				hour += 24;
			}
			while (day <= 0) {
				month--;
				day += 30;
			}
			while (month <= 0) {
				year--;
				month += 12;
			}
		}
		return *this;
	}
	int getHour() {
		return hour;
	}
	int getDay() {
		return day;
	}
	int getMonth() {
		return month;
	}
	int getYear() {
		return year;
	}
	void setHour(int h) {
		hour = h;
	}
	void setDay(int d) {
		day = d;
	}
	void setMonth(int m) {
		month = m;
	}
	int setYear(int y) {
		return year = y;
	}
};

Clock C;

class FlightTime {
	int hour;
	int day;
	int month;
	int year;
public:
	FlightTime() : year(2023) {
		hour = 0;
		day = 0;
		month = 0;
		year = 2023;
	}
	void operator=(const FlightTime& F) {
		year = F.year;
		month = F.month;
		day = F.day;
		hour = F.hour;
	}
	void setClockTime(int additionalHours) {
		C = C.increaseTime(additionalHours);
		this->month = C.getMonth();
		this->day = C.getDay();
		this->hour = C.getHour();
	}
	void setClockTime(int additionalHours, Clock& C) {
		C = C.increaseTime(additionalHours);
		this->month = C.getMonth();
		this->day = C.getDay();
		this->hour = C.getHour();
	}
	int getHour() {
		return hour;
	}
	int getDay() {
		return day;
	}
	int getMonth() {
		return month;
	}
	int getYear() {
		return year;
	}
	void setHour(int h) {
		hour = h;
	}
	void setDay(int d) {
		day = d;
	}
	void setMonth(int m) {
		month = m;
	}
	int setYear(int y) {
		return year = y;
	}
	friend ostream& operator<<(ostream& cout, FlightTime& f) {
		cout << f.getHour() << ":00 ," << f.getDay() << "/" << f.getMonth() << "/" << f.getYear();
		return cout;
	}
};


class Flight {
	Airplane* airplane;
	Airport* origin;
	Airport* destination;
	bool international;
	int durationHours;
	int* maxSeats;
	int* availableSeats;
	int* seatsPrice;
	int* perSeatPrice;
	FlightTime departureTime;
	FlightTime arrivalTime;
	static int hoursUntil_Flight;
	static int totalFlights;
public:
	Flight(Airplane* airplane = NULL, Airport* origin = NULL, Airport* destination = NULL, bool international = NULL, int durationHours = 0, int* maxSeats = NULL, int* availableSeats = NULL) :
		airplane(airplane), origin(origin), destination(destination), international(international), durationHours(durationHours), maxSeats(maxSeats), availableSeats(availableSeats) {
		this->maxSeats = new int[2];
		this->maxSeats[0] = 50;
		this->maxSeats[1] = 10;

		this->availableSeats = new int[2];
		this->availableSeats[0] = 50;
		this->availableSeats[1] = 10;

		this->seatsPrice = new int[2];
		this->perSeatPrice = new int[2];
		this->perSeatPrice[0] = 10000;
		this->perSeatPrice[1] = 20000;
		totalFlights++;
	}
	Airplane* getAirplane() {
		return airplane;
	}
	Airport* getOrigin() {
		return origin;
	}
	Airport* getDestination() {
		return destination;
	}
	bool isInternational() {
		return international;
	}
	int getDurationHours() {
		return durationHours;
	}
	int* getMaxSeats() {
		return maxSeats;
	}
	int* getAvailableSeats() {
		return availableSeats;
	}
	static int getHoursUntil_Flight() {
		return hoursUntil_Flight;
	}
	FlightTime getDepartureTime() {
		return departureTime;
	}
	FlightTime getArrivalTime() {
		return arrivalTime;
	}
	static int getTotalFlights() {
		return totalFlights;
	}
	int* getSeatsPrice() {
		return seatsPrice;
	}
	int* getPerSeatPrice() {
		return perSeatPrice;
	}
	void setDurationHours(int hours) {
		durationHours = hours;
	}
	void setMaxSeats(int e, int b) {
		maxSeats[0] = e;
		maxSeats[1] = b;
	}
	void SetAvailableSeats(int e, int b) {
		maxSeats[0] = e;
		maxSeats[1] = b;
	}
	static void setHoursUntil_Flight(int f) {
		hoursUntil_Flight = f;
	}
	void setDepartureTime(int hours) {
		departureTime.setClockTime(hours);
	}
	void setArrivalTime(int hours) {
		arrivalTime.setClockTime(hours);
	}
	static void updateSchedule() {
		C.getCurrentTime();
	}
	void setSeatsPrice(int e, int b) {
		seatsPrice[0] = e;
		seatsPrice[1] = b;
	}
	void setPerSeatPrice(int e, int b) {
		perSeatPrice[0] = e;
		perSeatPrice[1] = b;
	}
	void setAirplane(string planeID);
	void setOrigin(string airportName, string location);
	void setDestination(string airportName, string location);
	void setIsInternational(bool i);
};

int Flight::hoursUntil_Flight = 0;
int Flight::totalFlights = 0;

Flight* F = new Flight[50];

int GetHoursUntil_Flight() {
	return Flight::getHoursUntil_Flight();
}

void SetHoursUntil_Flight(int f) {
	Flight::setHoursUntil_Flight(f);
}

//cout << "New Departure Time: " << F[flightNo].getDepartureTime().getHour() << ":00, " << F[flightNo].getDepartureTime().getDay() << "/" << F[flightNo].getDepartureTime().getMonth() << "/" << F[flightNo].getDepartureTime().getYear();


class User {
protected:
	const char userType;
	string CNIC;
	string username;
	string password;
public:
	virtual void Abstract() const = 0;
	User(char type) : userType(type) {
		string usernameFile, passwordFile, cnicFile;
		if (userType == 'A') {
			cnicFile = "admin cnics.txt";
			usernameFile = "admin usernames.txt";
			passwordFile = "admin passwords.txt";
		}
		else if (userType == 'P') {
			cnicFile = "passenger cnics.txt";
			usernameFile = "passenger usernames.txt";
			passwordFile = "passenger passwords.txt";
		}
		login(usernameFile, passwordFile, cnicFile);
	}
	void login(string usernameFile, string passwordFile, string cnicFile) {
		string name, pwd;
		bool usernameFound = false, passwordFound = false;
		cout << "USERNAME: ";
		cin >> name;
		int i = checkIfExists(name, usernameFile, usernameFound);
		while (!usernameFound) {
			cout << "Username does not exist. Try Again: ";
			cin >> name;
			int i = checkIfExists(name, usernameFile, usernameFound);
		}
		if (usernameFound) {
			cout << "PASSWORD: ";
			cin >> pwd;

			verify(pwd, passwordFile, i, passwordFound);
			while (!passwordFound) {
				cout << "Incorrect Password. Try Again: ";
				cin >> pwd;
				int i = checkIfExists(pwd, passwordFile, passwordFound);
			}
			if (passwordFound) {
				username = name;
				password = pwd;
				ifstream fin(cnicFile);
				for (int j = 0; !fin.eof(); j++) {
					string input;
					fin >> input;
					if (j == i) {
						CNIC = input;
						break;
					}
				}
				fin.close();
			}
		}
	}
	void verify(string toBeFound, string filename, int index, bool& isAuthentic) {
		ifstream fin(filename);
		isAuthentic = false;
		for (int i = 0; !fin.eof(); i++) {
			//fin.seekg(-1L, ios::cur);
			string input;
			fin >> input;
			if (i == index) {
				if (input == toBeFound) {
					isAuthentic = true;
					break;
				}
			}
		}
		fin.close();
	}
};

class Passport {
	char type;   // 'L' for Local, 'F' for foreign, 'N' for neither
	bool visa;
public:
	Passport() {

	}
	char getType() {
		return type;
	}
	bool getVisa() {
		return visa;
	}
	void setType(char t) {
		type = t;
	}
	void setVisa(bool v) {
		visa = v;
	}
};

class BankAccount {
	//string name;
	const int accNo;
	string PIN;
	int balance;
	static int totalAccounts;
public:
	BankAccount() : accNo(++totalAccounts) {
		PIN = "";
	}
	//string getName() {
	//	return name;
	//}
	int getAccNo() {
		return accNo;
	}
	string getPIN() {
		return PIN;
	}
	static int getTotalAccounts() {
		return totalAccounts;
	}
	int getBalance() {
		return balance;
	}
	//void setName(string s) {
	//	name = s;
	//}
	void setBalance(int x) {
		balance = x;
	}
	void setPIN(string s) {
		if (PIN == "") {
			if (s.length() == 4) {
				PIN = s;
			}
			else {
				cout << "Invalid PIN No." << endl;
			}
		}
		else {
			bool change = false;
			cout << "PIN number already alloted. Change PIN no by verification? (1/0): ";
			cin >> change;
			if (change) {
				changePIN();
			}
		}
	}
	void changePIN() {
		string old, s;
		cout << "Current PIN: ";
		cin >> old;
		while (old != PIN) {
			cout << "Invalid input. Please Enter Your current PIN: ";
			cin >> old;
		}
		cout << "New PIN: ";
		cin >> s;
		while (s.length() != 4) {
			cout << "Invalid input. Please Enter a 4-digit PIN: ";
			cin >> s;
		}
		PIN = s;
	}
};

int BankAccount::totalAccounts = 0;

class Passenger : public User {
	Passport* passport;
	BankAccount* account;
public:
	void Abstract() const {}
	Passenger() : User('P') {
		account = new BankAccount;
		bool usernameFound = false;
		int i = checkIfExists(username, "passenger usernames.txt", usernameFound);
		passport = new Passport;
		ifstream fin("passports and visas.txt");
		for (int j = 0; !fin.eof(); j++) {
			string input1, input2, input3, input4;
			fin >> input1;
			fin >> input2;
			fin >> input3;
			fin >> input4;
			if (j == i) {
				passport->setType(input1[0]);
				if (input2[0] = 'Y') {
					passport->setVisa(true);
				}
				else {
					passport->setVisa(false);
				}
				account->setPIN(input3);
				account->setBalance(stoi(input4));
				break;
			}
		}
	}
	Passport* getPassport() {
		return passport;
	}
	BankAccount* getBankAccount() {
		return account;
	}
	void setPassPort(Passport& p) {
		*passport = p;
	}
	friend bool verifyFinancialDetails(Passenger& P, int price);
	void bookFlight() {
		bool confirmed = false;
		int fl;
		int areAvailable = 0;
		int price;
		int seatType;
		int seats;
		while (!confirmed) {
			string org, loc1;
			cout << "Departure Airport: " << endl;
			cout << "City: ";
			cin >> org;
			cout << "Location: ";
			cin >> loc1;
			string dest, loc2;
			cout << "Destination Airport: " << endl;
			cout << "City: ";
			cin >> dest;
			cout << "Location: ";
			cin >> loc2;
			cout << endl << endl;
			areAvailable = 0;
			for (int i = 0; i < Flight::getTotalFlights(); i++) {
				if ((F[i].getOrigin()->getCity() == org && F[i].getOrigin()->getLocation() == loc1[0]) && (F[i].getDestination()->getCity() == dest && F[i].getDestination()->getLocation() == loc2[0])) {
					cout << "Flight no " << i + 1 << ": " << endl;
					cout << "Plane ID: " << F[i].getAirplane()->getID() << endl;
					cout << "Origin: " << F[i].getOrigin()->getCity() << "  " << F[i].getOrigin()->getLocation() << endl;
					cout << "Departure Time: " << F[i].getDepartureTime().getHour() << ":00 ," << F[i].getDepartureTime().getDay() << "/" << F[i].getDepartureTime().getMonth() << "/" << F[i].getDepartureTime().getYear() << endl;
					cout << "Destination: " << F[i].getDestination()->getCity() << "  " << F[i].getDestination()->getLocation() << endl;
					cout << "Arrival Time: " << F[i].getArrivalTime().getHour() << ":00 ," << F[i].getArrivalTime().getDay() << "/" << F[i].getArrivalTime().getMonth() << "/" << F[i].getArrivalTime().getYear() << endl;
					cout << "Duration: " << F[i].getDurationHours() << " Hours" << endl;
					cout << "Available Seats: " << endl;
					cout << "Economy: " << F[i].getAvailableSeats()[0] << endl;
					cout << "Business: " << F[i].getAvailableSeats()[1] << endl;
					areAvailable++;			
					system("pause");
					system("cls");
				}
			}
			if (!areAvailable) {
				cout << "OOPs! No Flights Available" << endl;
				continue;
			}
			cout << "Enter the Flight ID of the flight you want to book: ";
			takeValidInput(fl);
			cout << endl << endl;
			cout << "You have choosen Flight no " << fl << endl;
			cout << "Flight Details: " << endl;
			DisplayFlightSchedule(fl);
			cout << endl << endl;
			cout << "Continue to booking? (1/0): ";
			cin >> confirmed;
		}
		bool confirmed2 = false;
		while (!confirmed2) {
			cout << "1) Economy Class" << endl;
			cout << "2) Business Class" << endl;
			cout << "Your choice: ";
			takeValidInput(seatType);
			while (seatType > 2 || seatType < 1) {
				cout << "Invalid Input. Enter again: ";
				takeValidInput(seatType);
			}
			cout << endl << endl;
			cout << "No of Seats: ";
			takeValidInput(seats);
			while (seats <= 0) {
				cout << "Invalid Input. Enter again: ";
				takeValidInput(seats);
			}
			cout << endl << endl;
			cout << "Seats booked: " << seats << endl;
			cout << "Type: ";
			if (seatType == 1) {
				cout << " Economy";
			}
			else {
				cout << " Business";
			}
			cout << endl << endl;
			price = F[fl].getPerSeatPrice()[seatType - 1] * seats * F[fl].getDurationHours();
			cout << "Price: " << price;
			cout << endl << endl;
			cout << "Confirm and Proceeed to payment? (1/0): ";
			cin >> confirmed2;
		}
		bool confirmed3 = false;
		while (!confirmed3) {
			if (verifyFinancialDetails(*this, price)) {
				ofstream fout("bookings.txt", ios::app);
				fout << this->username << '\t';
				fout << fl << '\t';
				fout << seatType << '\t';
				fout << seats << endl;
				fout.close();
				confirmed3 = true;
				cout << "Booking Confirmed." << endl;
				account->setBalance(account->getBalance() - price);
				cout << "Your New Balance: " << account->getBalance() << endl;
			}
			else {
				cout << "Error, Insufficient Balance." << endl;
			}
		}
	}
	void viewMyBookings() {
		fstream f("bookings.txt");
		int noOfBookings = 0;
		for (int i = 0; !f.eof(); i++) {
			string str1, str2, str3, str4;
			f >> str1;
			f >> str2;
			f >> str3;
			f >> str4;
			if (str1 == username) {
				noOfBookings++;
				cout << "User Name: " << str1 << endl;
				cout << "Flight No: " << str2 << endl;
				cout << "Seat Type: " << str3 << endl;
				cout << "Seats booked: " << str4 << endl << endl;
			}
		}
		if (!noOfBookings) {
			bool bookOne = false;
			cout << "No Bookings found. Book a flight now?";
			if (bookOne) {
				bookFlight();
			}
		}
		system("pause");
	}
	void editMyBookings() {
		fstream f("bookings.txt");
		int noOfBookings = 0;
		for (int i = 0; !f.eof(); i++) {
			string str1, str2, str3, str4;
			f >> str1;
			f >> str2;
			f >> str3;
			f >> str4;
			if (str1 == username) {
				noOfBookings++;
				cout << "User Name: " << str1 << endl;
				cout << "Flight No: " << str2 << endl;
				cout << "Seat Type: " << str3 << endl;
				cout << "Seats booked: " << str4 << endl << endl;
				bool editBooking = false;
				cout << "Edit this Booking? (1/0): ";
				cin >> editBooking;
				if (editBooking) {
					int choice;
					cout << "Choose your option:" << endl;
					cout << "1) Book more seats" << endl;
					cout << "2) Cancel Flight" << endl;
					cout << "Your choice: ";
					takeValidInput(choice);
					switch (choice)
					{
					case 1: {
						f.seekp(-1L, ios::cur);
						int newBookings;
						string pin;
						cout << "Additional seats to be booked: ";
						takeValidInput(newBookings);
						int price = F[stoi(str2)].getPerSeatPrice()[stoi(str3) - 1] * newBookings * F[stoi(str2)].getDurationHours();
						if (verifyFinancialDetails(*this, price) ) {
							account->setBalance(account->getBalance() - price);
							f << stoi(str4) + newBookings;
						}
						else {
							cout << "Insufficient Balance." << endl;
						}
						f.close();
						break;
					}
					case 2: {
						fstream f("bookings.txt", ios::in);
						string str[100][4];
						int i;
						for (i = 0; !f.eof(); i++) {
							for (int j = 0; j < 4; j++) {
								if (str[i][0] == username) {
									string s;
									f >> s;
								}
								else {
									f >> str[i][j];
								}
							}
							if (str[i][0] == username) {
								str[i][0] = "";
							}
						}
						f.close();
						f.open("bookings.txt");
						for (int k = 0; k<=i+1; k++) {
							for (int j = 0; j < 4; j++) {
								f << str[k][j] << '\t';
							}
							f << endl;
						}
						f.close();
						break;
					}
					default:
						break;
					}
				}
			}
		}
		if (!noOfBookings) {
			bool bookOne = false;
			cout << "No Bookings found. Book a flight now?";
			if (bookOne) {
				bookFlight();
			}
		}
		system("pause");
	}
};
bool verifyFinancialDetails(Passenger &P, int price) {
	string pin;
	cout << "Enter your 4-digit PIN: ";
	cin >> pin;
	while (pin != P.getBankAccount()->getPIN()) {
		cout << "Invalid PIN. Enter Again: ";
		cin >> pin;
	}
	if (P.getBankAccount()->getBalance() >= price) {
		return true;
	}
	else {
		return false;
	}
 }

class Admin : public User {

public:
	void Abstract() const {}
	Admin() : User('A') {

	}
	void addAnAdmin() {
		string cnicFile = "admin cnics.txt";
		string usernameFile = "admin usernames.txt";
		string passwordFile = "admin passwords.txt";
		string username, CNIC, password;
		bool usernameCreated = false;
		cout << "USER NAME:" << endl;
		while (!usernameCreated) {
			string name;
			cout << "Enter your user name: ";
			getline(cin, name);
			bool alreadyExists;
			checkIfExists(name, usernameFile, alreadyExists);
			if (alreadyExists) {
				cout << endl << "This username is already taken." << endl;
				continue;
			}
			else {
				username = name;
				usernameCreated = true;
			}
		}
		bool CnicValidated = false;
		cout << "CNIC:" << endl;
		while (!CnicValidated) {
			string cnic;
			cout << "Enter your CNIC: ";
			cin >> cnic;
			while (cnic.length() != 13) {
				cout << "Invalid CNIC. Enter Again:";
				cin >> cnic;
			}
			bool cnicExists;
			checkIfExists(cnic, cnicFile, cnicExists);
			if (cnicExists) {
				cout << endl << "This CNIC is already registered." << endl;
				continue;
			}
			else {
				CNIC = cnic;
				CnicValidated = true;
			}
		}
		bool passwordCreated = false;
		cout << "PASSWORD:" << endl;
		cout << "Password must contain atleast:" << endl << "1 lower and 1 upper case letter" << endl << "1 special character (-/_/./#)" << endl << "1 number" << endl;
		while (!passwordCreated) {
			string pwd;
			cout << "Enter your password: ";
			int ch = _getch();
			while (ch != 13) {
				if (ch == '\b') {
					pwd.pop_back();
				}
				else {
					pwd.push_back(ch);
					cout << "*";
				}
				ch = _getch();
			}
			cout << endl << endl;
			bool hasLowerCase = false, hasUpperCase = false, hasSpecialChar = false, hasNumeric = false;
			createPassword(pwd, hasUpperCase, hasLowerCase, hasNumeric, hasSpecialChar);
			if (hasUpperCase && hasLowerCase && hasSpecialChar && hasNumeric) {
				cout << "Passowrd meets the Criteria. " << endl;
				bool samePwds = false;
				while (!samePwds) {
					string confirmPwd;
					cout << "Confirm Password: ";
					int ch = _getch();
					while (ch != 13) {
						if (ch == '\b') {
							confirmPwd.pop_back();
						}
						else {
							confirmPwd.push_back(ch);
							cout << "*";
						}
						ch = _getch();
					}
					cout << endl << endl;
					if (pwd == confirmPwd) {
						password = pwd;
						samePwds = true;
						passwordCreated = true;
					}
					else {
						cout << "Passwords do not match. try again:" << endl;
					}
				}
			}
			else {
				cout << "Incorrect Password. Must contain atleast:" << endl << "1 lower and 1 upper case letter" << endl << "1 special character (-/_/./#)" << endl << "1 number" << endl;
			}
			if (CnicValidated && passwordCreated && CnicValidated) {
				ofstream fout(cnicFile, ios::app);
				fout.seekp(0L, ios::end);
				fout << CNIC << "\n";
				fout.close();

				fout.open(usernameFile, ios::app);
				fout.seekp(0L, ios::end);
				fout << username << "\n";
				fout.close();

				fout.open(passwordFile, ios::app);
				fout.seekp(0L, ios::end);
				fout << password << "\n";
				fout.close();
			}
		}
	}
	void changeFlightSchedule(int flightNo) {
		int choice;
		while (flightNo <= 0 || flightNo > Flight::getTotalFlights()) {
			cout << "Invalid Flight number. Enter again: ";
			takeValidInput(flightNo);
		}
		DisplayFlightSchedule(flightNo);
		cout << endl << endl;
		cout << "Change: " << endl;
		cout << "1) Origin" << endl;
		cout << "2) Destination" << endl;
		cout << "3) Departure Time" << endl;
		cout << "4) Arrival Time" << endl;
		cout << "5) Airplane" << endl;
		cout << "6) Available Seats" << endl;
		cout << endl << "Your Choice:";
		takeValidInput(choice);
		switch (choice) {
		case 1: {
			string newOrigin, newLocation;
			cout << "New Origin: ";
			cin >> newOrigin;
			cout << "Location (N/S): ";
			cin >> newLocation;
			while (newLocation != "N" && newLocation != "S") {
				cout << "Invalid location. Enter Again: ";
				cin >> newLocation;
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					if (newOrigin == P.getCitiesList()[i].getAirportsList()[j].getCity() && newLocation[0] == P.getCitiesList()[i].getAirportsList()[j].getLocation()) {
						F[flightNo].getOrigin()->setCity(P.getCitiesList()[i].getAirportsList()[j].getCity());
					}
					else if (newOrigin == I.getCitiesList()[i].getAirportsList()[j].getCity() && newLocation[0] == I.getCitiesList()[i].getAirportsList()[j].getLocation()) {
						F[flightNo].getOrigin()->setCity(I.getCitiesList()[i].getAirportsList()[j].getCity());
					}
				}
			}
			cout << endl << endl;
			cout << "New Origin: " << F[flightNo].getOrigin()->getCity() << endl;
			cout << "New Location: " << F[flightNo].getOrigin()->getLocation() << endl;
			break;
		}
		case 2: {
			string newDestination, newLocation;
			cout << "New Destination: ";
			cin >> newDestination;
			cout << "Location (N/S): ";
			cin >> newLocation;
			while (newLocation != "N" && newLocation != "S") {
				cout << "Invalid location. Enter Again: ";
				cin >> newLocation;
			}
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					if (newDestination == P.getCitiesList()[i].getAirportsList()[j].getCity() && newLocation[0] == P.getCitiesList()[i].getAirportsList()[j].getLocation()) {
						F[flightNo].getDestination()->setCity(P.getCitiesList()[i].getAirportsList()[j].getCity());
					}
					else if (newDestination == I.getCitiesList()[i].getAirportsList()[j].getCity() && newLocation[0] == I.getCitiesList()[i].getAirportsList()[j].getLocation()) {
						F[flightNo].getDestination()->setCity(I.getCitiesList()[i].getAirportsList()[j].getCity());
					}
				}
			}
			cout << endl << endl;
			cout << "New Origin: " << F[flightNo].getDestination()->getCity() << endl;
			cout << "New Location: " << F[flightNo].getDestination()->getLocation() << endl;
			break;
		}
		case 3: {
			int choice2;
			int hours;
			cout << "1) Postpone" << endl;
			cout << "2) Bring Forward" << endl;
			takeValidInput(choice2);
			cout << "Enter time in hours: ";
			takeValidInput(hours);
			while (hours <= 0) {
				cout << "Invalid time quantity. Enter Again: ";
				cin >> hours;
			}
			switch (choice2)
			{
			case 1: {
				Clock c1;
				c1.setHour(F[flightNo].getDepartureTime().getHour());
				c1.setDay(F[flightNo].getDepartureTime().getDay());
				c1.setMonth(F[flightNo].getDepartureTime().getMonth());
				c1.setYear(F[flightNo].getDepartureTime().getYear());
				c1 = c1.increaseTime(hours);
				F[flightNo].getDepartureTime().setHour(C.getHour());
				F[flightNo].getDepartureTime().setDay(C.getDay());
				F[flightNo].getDepartureTime().setMonth(C.getMonth());
				F[flightNo].getDepartureTime().setYear(C.getYear());
				cout << "Timings have been succesfully changed" << endl << endl;
				break;
			}
			case 2: {
				Clock c1;
				c1.setHour(F[flightNo].getDepartureTime().getHour());
				c1.setDay(F[flightNo].getDepartureTime().getDay());
				c1.setMonth(F[flightNo].getDepartureTime().getMonth());
				c1.setYear(F[flightNo].getDepartureTime().getYear());
				hours *= -1;
				c1 = c1.increaseTime(hours);
				F[flightNo].getDepartureTime().setHour(C.getHour());
				F[flightNo].getDepartureTime().setDay(C.getDay());
				F[flightNo].getDepartureTime().setMonth(C.getMonth());
				F[flightNo].getDepartureTime().setYear(C.getYear());
				cout << "Timings have been succesfully changed" << endl << endl;
				break;
			}
			default:
				break;
			}
			break;
		}
		case 4: {
			int choice2;
			int hours;
			cout << "1) Postpone" << endl;
			cout << "2) Bring Forward" << endl;
			takeValidInput(choice2);
			cout << "Enter time in hours: ";
			takeValidInput(hours);
			while (hours <= 0) {
				cout << "Invalid time quantity. Enter Again: ";
				cin >> hours;
			}
			switch (choice2)
			{
			case 1: {
				Clock c1;
				c1.setHour(F[flightNo].getArrivalTime().getHour());
				c1.setDay(F[flightNo].getArrivalTime().getDay());
				c1.setMonth(F[flightNo].getArrivalTime().getMonth());
				c1.setYear(F[flightNo].getArrivalTime().getYear());
				c1 = c1.increaseTime(hours);
				F[flightNo].getArrivalTime().setHour(C.getHour());
				F[flightNo].getArrivalTime().setDay(C.getDay());
				F[flightNo].getArrivalTime().setMonth(C.getMonth());
				F[flightNo].getArrivalTime().setYear(C.getYear());
				cout << "Timings have been succesfully changed" << endl << endl;
				break;
			}
			case 2: {
				Clock c1;
				c1.setHour(F[flightNo].getArrivalTime().getHour());
				c1.setDay(F[flightNo].getArrivalTime().getDay());
				c1.setMonth(F[flightNo].getArrivalTime().getMonth());
				c1.setYear(F[flightNo].getArrivalTime().getYear());
				hours *= -1;
				c1 = c1.increaseTime(hours);
				F[flightNo].getArrivalTime().setHour(C.getHour());
				F[flightNo].getArrivalTime().setDay(C.getDay());
				F[flightNo].getArrivalTime().setMonth(C.getMonth());
				F[flightNo].getArrivalTime().setYear(C.getYear());
				cout << "Timings have been succesfully changed" << endl << endl;
				break;
			}
			default:
				break;
			}
			break;
		}
		case 5: {
			int ID;
			cout << "Enter Plane ID: ";
			takeValidInput(ID);
			while (ID <= 0 || ID > Airplane::getTotalPlanes()) {
				cout << "Invalid Input. Enter again: ";
				takeValidInput(ID);
			}
			F[flightNo].setAirplane(to_string(ID));
			cout << "New Plane: " << F[flightNo].getAirplane()->getID();
			break;
		}
		case 6: {
			int newSeatsEconomy, newSeatsBusiness;
			cout << "No of seats in Economy Class: ";
			takeValidInput(newSeatsEconomy);
			while (newSeatsEconomy >= F[flightNo].getAirplane()->getSeatingCapacityEconomy()) {
				cout << "Invalid Input. Enter again: ";
				takeValidInput(newSeatsEconomy);
			}
			cout << "No of seats in Economy Class: ";
			takeValidInput(newSeatsBusiness);
			while (newSeatsBusiness >= F[flightNo].getAirplane()->getSeatingCapacityBusiness()) {
				cout << "Invalid Input. Enter again: ";
				takeValidInput(newSeatsBusiness);
			}
			F[flightNo].getAirplane()->setSeatingCapacityEconomy(newSeatsEconomy);
			F[flightNo].getAirplane()->setSeatingCapacityBusiness(newSeatsBusiness);
			cout << "Available Seats in Economy: " << F[flightNo].getAirplane()->getSeatingCapacityEconomy() << endl;
			cout << "Available Seats in Business: " << F[flightNo].getAirplane()->getSeatingCapacityBusiness() << endl;
			break;
		}
		default: {
			cout << "Invalid choice." << endl;
		}
		}
	}
};

class Menu {
	bool isLoggedIn;
	char LoggedInAs;
public:
	Menu() {
		isLoggedIn = false;
		LoggedInAs = '\0';
		MainMenu();
	}
	void MainMenu() {
		int choice;
		cout << "=====================================================" << endl;
		cout << "|-------------------- MAIN MENU --------------------|" << endl;
		cout << "=====================================================" << endl;
		cout << endl << endl;
		cout << "Choose your option:" << endl;
		cout << "1) Register an account" << endl;
		cout << "2) Login to your account" << endl;
		cout << "3) View Flight schedule" << endl;
		cout << "4) Search Flight schedule" << endl;
		cout << endl << "Your Choice:";
		takeValidInput(choice);
		switch (choice) {
		case 1: {
			system("cls");
			RegisterationMenu();
			break;
		}
		case 2: {
			system("cls");
			LoginMenu();
			break;
		}
		case 3: {
			system("cls");
			DisplayFlightSchedule();
			system("cls");
			MainMenu();
			break;
		}
		case 4: {
			system("cls");
			searchSchedule();
			system("cls");
			MainMenu();
			break;
		}
		default: {
			system("cls");
			cout << "Invalid choice." << endl;
		}
		}
	}
	void LoginMenu() {
		int choice;
		cout << "=====================================================" << endl;
		cout << "|-------------------- LOGIN MENU -------------------|" << endl;
		cout << "=====================================================" << endl;
		cout << endl << endl;
		cout << "Choose your option:" << endl;
		cout << "1) Return to Previous Menu" << endl;
		cout << "2) Login as a Passenger" << endl;
		cout << "3) Login as an Admin" << endl;
		cout << "Your choice: ";
		takeValidInput(choice);
		switch (choice) {
		case 1: {
			system("cls");
			MainMenu();
			break;
		}
		case 2: {
			Passenger P;
			isLoggedIn = true;
			LoggedInAs = 'P';
			system("pause");
			system("cls");
			PassengerMenu(P);
			break;
		}
		case 3: {
			Admin A;
			isLoggedIn = true;
			LoggedInAs = 'A';
			system("pause");
			system("cls");
			AdminMenu(A);
			break;
		}
		default: {
			system("cls");
			cout << "Invalid choice." << endl;
		}
		}
	}
	void RegisterationMenu() {
		int choice;
		cout << "=====================================================" << endl;
		cout << "|---------------- REGISTRATION MENU ----------------|" << endl;
		cout << "=====================================================" << endl;
		cout << endl << endl;
		cout << "Choose your option:" << endl;
		cout << "1) Return to Previous Menu" << endl;
		cout << "2) Register as Passenger" << endl;
		cout << "3) Register an Admin" << endl;
		cout << "Your choice: ";
		takeValidInput(choice);
		switch (choice) {
		case 1: {
			system("cls");
			MainMenu();
			break;
		}
		case 2: {
			registerAsPassenger();
			system("pause");
			system("cls");
			LoginMenu();
			break;
		}
		case 3: {
			cout << "You need to be logged in as an Admin to register another Admin." << endl;
			system("pause");
			system("cls");
			LoginMenu();
			break;
		}
		default: {
			cout << "Invalid choice." << endl;
			system("pause");
			system("cls");
		}
		}
	}
	void PassengerMenu(Passenger& P) {
		int choice;
		cout << "=====================================================" << endl;
		cout << "|------------------ PASSENGER MENU -----------------|" << endl;
		cout << "=====================================================" << endl;
		cout << endl << endl;
		cout << "Choose your option:" << endl;
		cout << "1) Log out" << endl;
		cout << "2) Book a Flight" << endl;
		cout << "3) View My Bookings" << endl;
		cout << "4) Edit My Bookings" << endl;
		cout << "Your choice: ";
		takeValidInput(choice);
		switch (choice) {
		case 1: {
			isLoggedIn = false;
			LoggedInAs = ' ';
			system("cls");
			LoginMenu();
			break;
		}
		case 2: {
			P.bookFlight();
			system("pause");
			system("cls");
			PassengerMenu(P);
			break;
		}
		case 3: {
			P.viewMyBookings();
			system("cls");
			PassengerMenu(P);
			break;
		}
		case 4: {
			P.editMyBookings();
			system("cls");
			PassengerMenu(P);
			break;
		}
		default: {
			cout << "Invalid choice." << endl;
			system("pause");
			system("cls");
		}
		}
	}
	void AdminMenu(Admin& A) {
		int choice;
		cout << "=====================================================" << endl;
		cout << "|-------------------- ADMIN MENU -------------------|" << endl;
		cout << "=====================================================" << endl;
		cout << endl << endl;
		cout << "Choose your option:" << endl;
		cout << "1) Log out" << endl;
		cout << "2) Edit Flight schedule" << endl;
		cout << "3) Register an Admin" << endl;
		cout << "Your choice: ";
		takeValidInput(choice);
		switch (choice) {
		case 1: {
			isLoggedIn = false;
			LoggedInAs = ' ';
			system("cls");
			LoginMenu();
			break;
		}
		case 2: {
			int ID;
			cout << "Which Flight do you want to edit?" << endl;
			cout << "Flight ID: ";
			takeValidInput(ID);
			while (ID <= 0 || ID >= Flight::getTotalFlights()) {
				cout << "Invalid Input. Enter Again: ";
				takeValidInput(ID);
			}
			A.changeFlightSchedule(ID);
			system("pause");
			system("cls");
			AdminMenu(A);
			break;
		}
		case 3: {
			A.addAnAdmin();
			system("pause");
			system("cls");
			AdminMenu(A);
			break;
		}
		default: {
			cout << "Invalid choice." << endl;
			system("pause");
			system("cls");
		}
		}
	}
};

void registerAsPassenger() {
	string cnicFile = "passenger cnics.txt";
	string usernameFile = "passenger usernames.txt";
	string passwordFile = "passenger passwords.txt";
	bool usernameCreated = false;
	cout << "USER NAME:" << endl;
	string username, CNIC, password;
	while (!usernameCreated) {
		string name;
		cout << "Enter your user name: ";
		getline(cin, name);
		bool alreadyExists;
		checkIfExists(name, usernameFile, alreadyExists);
		if (alreadyExists) {
			cout << endl << "This username is already taken." << endl;
			continue;
		}
		else {
			username = name;
			usernameCreated = true;
		}
	}
	bool CnicValidated = false;
	cout << "CNIC:" << endl;
	while (!CnicValidated) {
		string cnic;
		cout << "Enter your CNIC: ";
		cin >> cnic;
		while (cnic.length() != 13) {
			cout << "Invalid CNIC. Enter Again:";
			cin >> cnic;
		}
		bool cnicExists;
		checkIfExists(cnic, cnicFile, cnicExists);
		if (cnicExists) {
			cout << endl << "This CNIC is already registered." << endl;
			continue;
		}
		else {
			CNIC = cnic;
			CnicValidated = true;
		}
	}
	bool passwordCreated = false;
	cout << "PASSWORD:" << endl;
	cout << "Password must contain atleast:" << endl << "1 lower and 1 upper case letter" << endl << "1 special character (-/_/./#)" << endl << "1 number" << endl;
	while (!passwordCreated) {
		string pwd;
		cout << "Enter your password: ";
		int ch = _getch();
		while (ch != 13) {
			if (ch == '\b') {
				pwd.pop_back();
			}
			else {
				pwd.push_back(ch);
				cout << "*";
			}
			ch = _getch();
		}
		cout << endl << endl;
		bool hasLowerCase = false, hasUpperCase = false, hasSpecialChar = false, hasNumeric = false;
		createPassword(pwd, hasUpperCase, hasLowerCase, hasNumeric, hasSpecialChar);
		if (hasUpperCase && hasLowerCase && hasSpecialChar && hasNumeric) {
			cout << "Passowrd meets the Criteria. " << endl;
			bool samePwds = false;
			while (!samePwds) {
				string confirmPwd;
				cout << "Confirm Password: ";
				int ch = _getch();
				while (ch != 13) {
					if (ch == '\b') {
						confirmPwd.pop_back();
					}
					else {
						confirmPwd.push_back(ch);
						cout << "*";
					}
					ch = _getch();
				}
				cout << endl << endl;
				if (pwd == confirmPwd) {
					password = pwd;
					samePwds = true;
					passwordCreated = true;
				}
				else {
					cout << "Passwords do not match. try again:" << endl;
				}
			}
		}
		else {
			cout << "Incorrect Password. Must contain atleast:" << endl << "1 lower and 1 upper case letter" << endl << "1 special character (-/_/./#)" << endl << "1 number" << endl;
		}
		if (CnicValidated && passwordCreated && CnicValidated) {
			string str, str2, pin;
			int bal;
			cout << "Passport Type: ";
			cin >> str;
			while (str != "L" && str != "F" && str != "N") {
				cout << "Invalid type. Enter again: ";
				cin >> str;
			}
			if (str[0] == 'L') {
				cout << "Visa: (Y/N): ";
				cin >> str2;
				while (str2 != "Y" && str2 != "N") {
					cout << "Invalid type. Enter again: ";
					cin >> str2;
				}
			}
			else if (str[0] == 'F') {
				str2 = "Y";
			}
			else {
				str2 = "N";
			}

			cout << "PIN: ";
			cin >> pin;
			while (pin.length() != 4 || !(isdigit(pin[0])) || !(isdigit(pin[1])) || !(isdigit(pin[2])) || !(isdigit(pin[3]))) {
				cout << "Invalid Pin. Enter again: ";;
				cin >> pin;
			}
			cout << "Enter Balance: ";
			takeValidInput(bal);
			while (bal < 0) {
				cout << "Invalid balance. Enter again: ";
				takeValidInput(bal);
			}
			ofstream fout(cnicFile, ios::app);
			fout.seekp(0L, ios::end);
			fout << CNIC << "\n";
			fout.close();

			fout.open(usernameFile, ios::app);
			fout.seekp(0L, ios::end);
			fout << username << "\n";
			fout.close();

			fout.open(passwordFile, ios::app);
			fout.seekp(0L, ios::end);
			fout << password << "\n";
			fout.close();

			fout.open("passports and visas.txt", ios::app);
			fout.seekp(0L, ios::end);
			fout << str << '\t';
			fout << str2 << '\t';
			fout << pin << '\t';
			fout << bal << endl;
			fout.close();

			cout << endl << "Your Account has been registered. You can now login with the account you just created." << endl << endl;
		}
	}
}

void Flight::setAirplane(string planeID) {
	int id = stoi(planeID);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 5; k++) {
				if (id == P.getCitiesList()[i].getAirportsList()[j].getAirplanesList()[k].getID()) {
					airplane = &(P.getCitiesList()[i].getAirportsList()[j].getAirplanesList()[k]);
				}
			}
		}
	}
}

void Flight::setOrigin(string airportName, string airportLocation) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			if (airportName == P.getCitiesList()[i].getAirportsList()[j].getCity() && airportLocation[0] == P.getCitiesList()[i].getAirportsList()[j].getLocation()) {
				origin = &(P.getCitiesList()[i].getAirportsList()[j]);
			}
			else if (airportName == I.getCitiesList()[i].getAirportsList()[j].getCity() && airportLocation[0] == I.getCitiesList()[i].getAirportsList()[j].getLocation()) {
				origin = &(I.getCitiesList()[i].getAirportsList()[j]);
			}
		}
	}
}

void Flight::setDestination(string airportName, string airportLocation) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			if (airportName == P.getCitiesList()[i].getAirportsList()[j].getCity() && airportLocation[0] == P.getCitiesList()[i].getAirportsList()[j].getLocation()) {
				destination = &(P.getCitiesList()[i].getAirportsList()[j]);
			}
			else if (airportName == I.getCitiesList()[i].getAirportsList()[j].getCity() && airportLocation[0] == I.getCitiesList()[i].getAirportsList()[j].getLocation()) {
				destination = &(I.getCitiesList()[i].getAirportsList()[j]);
			}
		}
	}
}

void Flight::setIsInternational(bool value) {

}
int Count = 0;
void setFlightSchedule() {
	if (Count == 0) {
		ifstream fin("schedule.txt");
		string str, str1, str2, str3;
		for (int i = 0; !fin.eof(); i++) {
			fin >> str;
			F[i].setAirplane(str);
			fin >> str;
			fin >> str1;
			F[i].setOrigin(str, str1);
			fin >> str2;
			fin >> str3;
			F[i].setDestination(str2, str3);
			bool isInternational = false;
			for (int j = 0; j < I.getCitiesInCountry(); j++) {
				if (str == I.getCitiesList()[j].getName() || str2 == I.getCitiesList()[j].getName()) {
					isInternational = true;
				}
			}
			F[i].setIsInternational(isInternational);
			F[i].setDepartureTime(2);
			string filename = F[i].getOrigin()->getCity() + ".txt";
			ifstream fin2(filename);
			for (int j = 0; !fin2.eof(); j++) {
				string fileStr, fileStr2;
				fin2 >> fileStr;
				fin2 >> fileStr2;
				if (fileStr == F[i].getDestination()->getCity()) {
					F[i].setDurationHours(stoi(fileStr2));
					break;
				}
			}
			fin2.close();
			F[i].setArrivalTime(F[i].getDurationHours());
			F[i].setSeatsPrice(F[i].getDurationHours() * F[i].getPerSeatPrice()[0], F[i].getDurationHours() * F[i].getPerSeatPrice()[1]);
			getline(fin, str);
			if (i >= 49) {
				break;
			}
		}
		fin.close();
		Count++;
	}
}

void DisplayFlightSchedule() {
	for (int i = 0; i < Flight::getTotalFlights(); i++) {
		cout << "Flight no " << i + 1 << ": " << endl;
		cout << "Plane ID: " << F[i].getAirplane()->getID() << endl;
		cout << "Origin: " << F[i].getOrigin()->getCity() << endl;
		cout << "Departure Time: " << F[i].getDepartureTime().getHour() << ":00 ," << F[i].getDepartureTime().getDay() << "/" << F[i].getDepartureTime().getMonth() << "/" << F[i].getDepartureTime().getYear() << endl;
		cout << "Destination: " << F[i].getDestination()->getCity() << endl;
		cout << "Arrival Time: " << F[i].getArrivalTime().getHour() << ":00 ," << F[i].getArrivalTime().getDay() << "/" << F[i].getArrivalTime().getMonth() << "/" << F[i].getArrivalTime().getYear() << endl;
		cout << "Duration: " << F[i].getDurationHours() << " Hours" << endl;
		cout << "Available Seats: " << endl;
		cout << "Economy: " << F[i].getAvailableSeats()[0] << endl;
		cout << "Business: " << F[i].getAvailableSeats()[1] << endl;
		system("pause");
		system("cls");

	}
}

void searchSchedule() {
	string org, loc1;
	cout << "Departure Airport: " << endl;
	cout << "City: ";
	cin >> org;
	cout << "Location: ";
	cin >> loc1;
	string dest, loc2;
	cout << "Destination Airport: " << endl;
	cout << "City: ";
	cin >> dest;
	cout << "Location: ";
	cin >> loc2;
	cout << endl << endl;
	int areAvailable = 0;
	for (int i = 0; i < Flight::getTotalFlights(); i++) {
		if ((F[i].getOrigin()->getCity() == org && F[i].getOrigin()->getLocation() == loc1[0]) && (F[i].getDestination()->getCity() == dest && F[i].getDestination()->getLocation() == loc2[0])) {
			cout << "Flight no " << i + 1 << ": " << endl;
			cout << "Plane ID: " << F[i].getAirplane()->getID() << endl;
			cout << "Origin: " << F[i].getOrigin()->getCity() << "  " << F[i].getOrigin()->getLocation() << endl;
			cout << "Departure Time: " << F[i].getDepartureTime().getHour() << ":00 ," << F[i].getDepartureTime().getDay() << "/" << F[i].getDepartureTime().getMonth() << "/" << F[i].getDepartureTime().getYear() << endl;
			cout << "Destination: " << F[i].getDestination()->getCity() << "  " << F[i].getDestination()->getLocation() << endl;
			cout << "Arrival Time: " << F[i].getArrivalTime().getHour() << ":00 ," << F[i].getArrivalTime().getDay() << "/" << F[i].getArrivalTime().getMonth() << "/" << F[i].getArrivalTime().getYear() << endl;
			cout << "Duration: " << F[i].getDurationHours() << " Hours" << endl;
			cout << "Available Seats: " << endl;
			cout << "Economy: " << F[i].getAvailableSeats()[0] << endl;
			cout << "Business: " << F[i].getAvailableSeats()[1] << endl;
			areAvailable++;
			system("pause");
			system("cls");
		}
	}
	if (!areAvailable) {
		cout << "OOPs! No Flights Available" << endl;
	}
	system("pause");
	system("cls");
}

void DisplayFlightSchedule(int i) {
	i--;
	cout << "Flight no " << i + 1 << ": " << endl;
	cout << "Plane ID: " << F[i].getAirplane()->getID() << endl;
	cout << "Origin: " << F[i].getOrigin()->getCity() << endl;
	cout << "Departure Time: " << F[i].getDepartureTime().getHour() << ":00 ," << F[i].getDepartureTime().getDay() << "/" << F[i].getDepartureTime().getMonth() << "/" << F[i].getDepartureTime().getYear() << endl;
	cout << "Destination: " << F[i].getDestination()->getCity() << endl;
	cout << "Arrival Time: " << F[i].getArrivalTime().getHour() << ":00 ," << F[i].getArrivalTime().getDay() << "/" << F[i].getArrivalTime().getMonth() << "/" << F[i].getArrivalTime().getYear() << endl;
	cout << "Duration: " << F[i].getDurationHours() << " Hours" << endl;
	cout << "Available Seats: " << endl;
	cout << "Economy: " << F[i].getAvailableSeats()[0] << endl;
	cout << "Business: " << F[i].getAvailableSeats()[1] << endl;
}

int main() {
	setFlightSchedule();
	Menu M;
	return 0;
}
