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

	cout << "\nВведите чисдо для деления суммы на него" << endl;

	cin >> denominator;

	__try {
		int result = sum / denominator;  // Попытка деления на ноль
		cout << "Результат: " << result << endl;
	}
	__except (GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
		cerr << "\nОшибка: деление на ноль" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

#pragma region Создание, запись текста в файл

	ofstream fout;
	fout.open("NewFile.txt");

	//ofstream fout("NewFile.txt");

	fout << "Starting file work";

	fout.close();

#pragma endregion

#pragma region Чтение текста их файла

	char buff[50];

	ifstream fin("NewFile.txt");

	if (!fin.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n";
	else {
		cout << "Файл содержит фразу: ";
		fin.getline(buff, 50);
		fin.close();
		cout << buff << endl;
	}

#pragma endregion

	//#pragma region Запись данных int в файл c проверкой ввода
	//
	// fout.open("NewFile1.txt", ios_base::out | ios_base::trunc);
	// //fout.open("NewFile1.txt", ios_base::out | ios_base::app);
	//
	// int input;
	//
	// cout << "Введите последовательность целых чисел (ввод 0 означает конец последоваттельности)" << endl;
	//
	// do {
	// cout << "> ";
	// cin >> input;
	//
	// // Проверяем, успешен ли ввод
	// if (!cin) {
	// cerr << "Ошибка ввода. Пожалуйста, введите целое число." << std::endl;
	// cin.clear(); // Сбрасываем флаг ошибки
	// cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
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

#pragma region Запись данных int в файл c без проверки ввода

	fout.open("NewFile1.txt", ios_base::out | ios_base::trunc);

	string input;

	cout << "\nВведите последовательность целых чисел (ввод 0 означает конец последовательности)" << endl;

	do {
		cout << "> ";
		cin >> input;

		if (input != "0") {
			fout << input << endl;
		}

	} while (input != "0");

	fout.close();

#pragma endregion

#pragma region Чтение данных int из файла

	ifstream inputFile("NewFile1.txt");

	vector<int> numbers;

	while (inputFile >> input) {
		try {
			int number = stoi(input);
			numbers.push_back(number);
		}
		catch (const invalid_argument& e) {
			cerr << "Пропущено некорректное значение: " << input << endl;
		}
		catch (const out_of_range& e) {
			cerr << "Пропущено значение, выходящее за пределы int: " << input << endl;
		}
	}

	inputFile.close();

	// Вычисляем сумму элементов
	int sum = 0;
	for (int num : numbers) {
		sum += num;
	}

	// Выводим сумму элементов
	cout << "\nСумма элементов: " << sum << endl;

	PrintSumDivision(sum);


#pragma endregion

#pragma region Прямой досткп к нужному значению

	ifstream file("NewFile.txt");

	// Ищем позицию начала слова
	string targetWord;
	cout << "\nВ файл записана строка \"Starting file work\"" << endl;
	cout << "Введите слово для поиска: " << endl;
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
		// Перемещаем указатель в файле на начало слова
		file.seekg(startPos);

		// Читаем и выводим слово
		string resultWord;
		file >> resultWord;

		cout << "Найденное слово: " << resultWord << endl;
	}
	else {
		cout << "Слово не найдено." << endl;
	}

	// Закрываем файл
	file.close();

#pragma endregion

#pragma region Работа со структурой

	cout << "\nРабота со стуктурой\n";

	// Создаем несколько записей
	vector<Record> records = {
		{"Иван", 25, 50000.0},
		{"Мария", 30, 60000.0},
		{"Петр", 28, 55000.0}
	};

	// Записываем данные в файл
	ofstream outFile("records.txt");

	if (!outFile.is_open()) {
		cerr << "Ошибка открытия файла!" << endl;
		return 1;
	}

	for (const Record& record : records) {
		outFile << record.name << ' ' << record.age << ' ' << record.salary << '\n';
	}

	outFile.close();

	// Считываем данные из файла
	ifstream inFile("records.txt");

	vector<Record> readRecords;

	while (!inFile.eof()) {
		Record record;
		inFile >> record.name >> record.age >> record.salary;
		readRecords.push_back(record);
	}

	inFile.close();

	// Выводим считанные данные
	cout << "\nСчитанные записи:\n";
	for (const Record& record : readRecords) {
		cout << "Имя: " << record.name << ", Возраст: " << record.age << ", Зарплата: " << record.salary << '\n';
	}

#pragma endregion

#pragma region Работа с вещественными числами

	// Установка флага проверки деления на ноль
	fenv_t currentFlags;
	fegetenv(&currentFlags);

	fenv_t newFlags = currentFlags;
	fesetenv(&newFlags);

	double zero = 0.0;

	// Попытка деления на ноль
	double result = 5.0 / zero;

	// Проверка флага деления на ноль
	if (std::fetestexcept(FE_DIVBYZERO)) {
		std::cerr << "\nОшибка: деление на ноль" << std::endl;
	}
	else {
		std::cout << "\nРезультат: " << result << std::endl;
	}

#pragma endregion
}