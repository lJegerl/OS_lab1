#include <iostream>
#include <fstream>
#include "employee.h"

int main(int argc, char* argv[])
{
	std::ofstream fout(argv[1], std::ios::binary);

	int recordsCount = atoi(argv[2]);
	employee* records = new employee[recordsCount];

	std::cout << "\nType information about " << recordsCount << " employees:\n" << std::endl;
	for (int i = 0; i < recordsCount; i++) {
		std::cout << "Employee " << (i + 1) << ": " << std::endl;
		std::cout << "ID: ";
		std::cin >> records[i].id;
		std::cout << std::endl << "Name: ";
		std::cin >> records[i].name;
		std::cout << std::endl << "Hours: ";
		std::cin >> records[i].hours;
		std::cout << std::endl;
	}

	fout.write((char*)&recordsCount, sizeof(int));
	for (int i = 0; i < recordsCount; i++) {
		fout.write((char*)&records[i], sizeof(employee));
	}

	fout.close();
	delete[] records;
	return 0;
}