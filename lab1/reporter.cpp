#include <fstream>
#include "employee.h"

int main(int argc, char *argv[])
{
	std::ifstream fin(argv[1], std::ios::binary);
	std::ofstream fout(argv[2]);
	double salaryPerHour = atof(argv[3]);

	int recordsCount;
	fin.read((char *)&recordsCount, sizeof(int));
	employee *records = new employee[recordsCount];

	for (int i = 0; i < recordsCount; i++) {
		fin.read((char *)&records[i], sizeof(employee));
	}

	for (int i = 0; i < recordsCount; i++) {
		fout << "ID: " << records[i].id << std::endl;
		fout << "Name: " << records[i].name << std::endl;
		fout << "Hours: " << records[i].hours << std::endl;
		fout << "Salary: " << records[i].hours * salaryPerHour << std::endl;
	}
	fin.close();
	fout.close();

	delete[] records;
	return 0;
}