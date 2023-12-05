#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <cfenv>


using namespace std;

struct Record {
	string name;
	int age;
	double salary;
};

void PrintSumDivision(int sum)
{
	int denominator;

	cout << "\n������� ����� ��� ������� ����� �� ����" << endl;

	cin >> denominator;

	__try {
		int result = sum / denominator;  // ������� ������� �� ����
		cout << "���������: " << result << endl;
	}
	__except (GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		cerr << "\n������: ������� �� ����" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

#pragma region ��������, ������ ������ � ����

	ofstream fout;
	fout.open("NewFile.txt");

	//ofstream fout("NewFile.txt");

	fout << "Starting file work";

	fout.close();

#pragma endregion

#pragma region ������ ������ �� �����

	char buff[50];

	ifstream fin("NewFile.txt");

	if (!fin.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n";
	else {
		cout << "���� �������� �����: ";
		fin.getline(buff, 50);
		fin.close();
		cout << buff << endl;
	}

#pragma endregion

	//#pragma region ������ ������ int � ���� c ��������� �����
	//
	// fout.open("NewFile1.txt", ios_base::out | ios_base::trunc);
	// //fout.open("NewFile1.txt", ios_base::out | ios_base::app);
	//
	// int input;
	//
	// cout << "������� ������������������ ����� ����� (���� 0 �������� ����� �������������������)" << endl;
	//
	// do {
	// cout << "> ";
	// cin >> input;
	//
	// // ���������, ������� �� ����
	// if (!cin) {
	// cerr << "������ �����. ����������, ������� ����� �����." << std::endl;
	// cin.clear(); // ���������� ���� ������
	// cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ����� �����
	// continue;
	// }
	//
	// if (input != 0) {
	// fout << input << endl;
	// }
	//
	// } while (input != 0);
	//
	// fout.close();
	//
	//#pragma endregion

#pragma region ������ ������ int � ���� c ��� �������� �����

	fout.open("NewFile1.txt", ios_base::out | ios_base::trunc);

	string input;

	cout << "\n������� ������������������ ����� ����� (���� 0 �������� ����� ������������������)" << endl;

	do {
		cout << "> ";
		cin >> input;

		if (input != "0") {
			fout << input << endl;
		}

	} while (input != "0");

	fout.close();

#pragma endregion

#pragma region ������ ������ int �� �����

	ifstream inputFile("NewFile1.txt");

	vector<int> numbers;

	while (inputFile >> input) {
		try {
			int number = stoi(input);
			numbers.push_back(number);
		}
		catch (const invalid_argument& e) {
			cerr << "��������� ������������ ��������: " << input << endl;
		}
		catch (const out_of_range& e) {
			cerr << "��������� ��������, ��������� �� ������� int: " << input << endl;
		}
	}

	inputFile.close();

	// ��������� ����� ���������
	int sum = 0;
	for (int num : numbers) {
		sum += num;
	}

	// ������� ����� ���������
	cout << "\n����� ���������: " << sum << endl;

	PrintSumDivision(sum);


#pragma endregion

#pragma region ������ ������ � ������� ��������

	ifstream file("NewFile.txt");

	// ���� ������� ������ �����
	string targetWord;
	cout << "\n� ���� �������� ������ \"Starting file work\"" << endl;
	cout << "������� ����� ��� ������: " << endl;
	cin >> targetWord;

	streampos startPos = -1;

	string word;
	while (file >> word) {
		if (word == targetWord) {
			startPos = file.tellg() - static_cast<streampos>(word.length());
			break;
		}
	}

	if (startPos != -1) {
		// ���������� ��������� � ����� �� ������ �����
		file.seekg(startPos);

		// ������ � ������� �����
		string resultWord;
		file >> resultWord;

		cout << "��������� �����: " << resultWord << endl;
	}
	else {
		cout << "����� �� �������." << endl;
	}

	// ��������� ����
	file.close();

#pragma endregion

#pragma region ������ �� ����������

	cout << "\n������ �� ���������\n";

	// ������� ��������� �������
	vector<Record> records = {
		{"����", 25, 50000.0},
		{"�����", 30, 60000.0},
		{"����", 28, 55000.0}
	};

	// ���������� ������ � ����
	ofstream outFile("records.txt");

	if (!outFile.is_open()) {
		cerr << "������ �������� �����!" << endl;
		return 1;
	}

	for (const Record& record : records) {
		outFile << record.name << ' ' << record.age << ' ' << record.salary << '\n';
	}

	outFile.close();

	// ��������� ������ �� �����
	ifstream inFile("records.txt");

	vector<Record> readRecords;

	while (!inFile.eof()) {
		Record record;
		inFile >> record.name >> record.age >> record.salary;
		readRecords.push_back(record);
	}

	inFile.close();

	// ������� ��������� ������
	cout << "\n��������� ������:\n";
	for (const Record& record : readRecords) {
		cout << "���: " << record.name << ", �������: " << record.age << ", ��������: " << record.salary << '\n';
	}

#pragma endregion

#pragma region ������ � ������������� �������

	// ��������� ����� �������� ������� �� ����
	fenv_t currentFlags;
	fegetenv(&currentFlags);

	fenv_t newFlags = currentFlags;
	fesetenv(&newFlags);

	double zero = 0.0;

	// ������� ������� �� ����
	double result = 5.0 / zero;

	// �������� ����� ������� �� ����
	if (std::fetestexcept(FE_DIVBYZERO)) {
		std::cerr << "\n������: ������� �� ����" << std::endl;
	}
	else {
		std::cout << "\n���������: " << result << std::endl;
	}

#pragma endregion
}