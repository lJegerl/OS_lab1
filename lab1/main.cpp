#include <windows.h>
#include <iostream>
#include <fstream>
#include "employee.h"
#include <conio.h>
#include <string>

void startProcess(char* buffer) {
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	if (!CreateProcess(NULL, buffer, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		std::cout << "\nERROR: Unable to open file\n";
		system("pause");
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void printFromBinFile(int recordsCount, char binaryFileName[256]) {
	std::cout << "Information in binary file:" << std::endl;

	std::ifstream fin(binaryFileName, std::ios::binary);
	fin.read((char *)&recordsCount, sizeof(int));
	employee *records = new employee[recordsCount];


	for (int i = 0; i < recordsCount; i++) {
		fin.read((char *)&records[i], sizeof(employee));
	}

	std::cout << records[0].id << std::endl 
	     << records[0].name << std::endl
		 << records[0].hours;
	for (int i = 1; i < recordsCount; i++) {
		std::cout << std::endl
			 << records[i].id << std::endl
			 << records[i].name << std::endl
			 << records[i].hours;
	}

	delete[] records;
	fin.close();
}

void printFromOutFile(char outputFileName[256], int recordsCount) {
	std::ifstream finInfo(outputFileName);

	std::cout << std::endl
		 << "Information in output file:" << std::endl;
	char text[1000];
	for (int i = 0; i < recordsCount * 4; i++) {
		finInfo.getline(text, 1000);
		for (int i = 0; text[i] != '\0'; i++) {
			printf("%c", text[i]);
		}
		std::cout << std::endl;
		if ((i + 1 )% 4 == 0) {
			std::cout << std::endl;
		}
	}
	finInfo.close();
}

int main()
{
	char binaryFileName[256];

	std::cout << "Binary file: ";
	std::cin.getline(binaryFileName, 256);	
	int recordsCount = 0;
	std::cout << "Number of records: ";
	
	if(!(std::cin >> recordsCount)) {
		std::cout << "ERROR! It isn't digit!" << std::endl;
		system("pause");
	}
	else {
		std::cin.ignore();
		
		char buffer[1000];
		sprintf(buffer, "%s %s %d", "creator.exe", binaryFileName, recordsCount);
		startProcess(buffer);
		
		printFromBinFile(recordsCount, binaryFileName);
		
		char outputFileName[256];
		std::cout << "\n\nOutput file name: ";
		std::cin.getline(outputFileName, 256);
		double salaryPerHour = 0.0;
		std::cout << "Salary per hour: ";
		
		if(!(std::cin >> salaryPerHour)) {
			std::cout << "ERROR! It isn't digit!" << std::endl;
			system("pause");
			}
			else {
				buffer[0] = '\0';
				sprintf(buffer, "%s %s %s %lf", "reporter.exe", binaryFileName, outputFileName, salaryPerHour);
				startProcess(buffer);
				
				printFromOutFile(outputFileName, recordsCount);
				}
	    }
	
	return 0;
}