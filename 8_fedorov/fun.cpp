#include "Header.h"

bool chek_file(string file) {
	ifstream in;
	in.open(file, ios::in);

	auto rez = 1;
	if (in.is_open())
	{
		if (in.peek() == char_traits<char>::eof())
			rez = 0;
		in.close();
	};
	return rez;
}
void error()
{
	Beep(800, 150);
	cout << "ERROR!" << endl << endl;
	system("pause");
}

bool isdigit_r(unsigned char a) { return (a >= '0' && a <= '9'); }

bool isalpha_r(unsigned char a)
{
	bool rez = ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '-');

	return rez;
}

int rand_data(string sex)								/// от 0 до 9 муж. от 10 до 19 жен
{
	if (sex == "man")
		return rand() % 5;
	else
		return rand() % 5 + 5;

}
std::string rand_data(int max) {
	std::string rez;
	if (max == 2) {
		if ((rand() % 2) == 1) {
			rez = "man";
		}
		else {
			rez = "women";
		}
		return rez;
	}
	else if (max == 4) {
		int year = rand() % (2023 - 1900 + 1) + 1900;
		return std::to_string(year);
	}
	else if (max == 12) {
		unsigned int number = 0;
		for (int i = 0; i < 12; i++) {
			number = number * 10 + rand() % 10;
		}
		return std::to_string(number);
	}
	else if (max == 3) {
		long long number = 0;
		for (int i = 0; i < 3; i++) {
			number = number * 10 + rand() % 10;
		}
		return std::to_string(number);
	}
	return "error";
}
std::string adapted_rand_data(int max, short i) {
	return rand_data(max);
}
void add(std::map<int, Uzond>& program, const std::vector<std::string>& arr_name, const std::vector<std::string>& arr_surname, const std::vector<std::string>& arr_of_name_urzant, const std::vector<std::string>& arrOfNameKindergarten, const std::vector<std::string>& arrOfWork)
{
	std::cout << "Сhcesz dodac urzond lub osobe(u lub o)" << std::endl;

	switch (_getch())
	{
	case (117):
	{
		int index = program.size();
		program.insert(std::make_pair(index, Uzond::create(program[0].get_people_size(), arr_of_name_urzant, arr_name, arr_surname, arrOfNameKindergarten, arrOfWork)));
		break;
	}
	case (111):
	{
		std::cout << "Ty chces dodac People lub Children? (1 or 2)" << std::endl;
		bool flag;
		switch (_getch())
		{
		case ('1'):
			flag = false;
			break;
		case ('2'):
			flag = true;
			break;
		default:
			flag = false;
			break;
		}

		for (auto& pair : program)
			pair.second.addPerson(arr_name, arr_surname, arrOfNameKindergarten, arrOfWork, flag);
		break;
	}
	default:
		break;
	}
}
void edit(std::map<int, Uzond>& program, int index_1, int index_2)
{
	system("cls");
	ShowCursor(1);
	if (index_1 < 0 || index_2 < 0 || program.find(index_1) == program.end() || program[index_1].get_user(index_2) == nullptr)
	{
		error();
	}

	std::cout << "Wstepne dane:" << std::endl;
	program[index_1].get_user(index_2)->print();
	std::cout << "Podaj Name Surname Year Pesel i sex: ";
	program[index_1].get_user(index_2)->edit();
	ShowCursor(0);
}


void dell(std::map<int, Uzond>& program)
{
	std::cout << "Usunac uzytkownika lub uzytkownika? (u lub o)" << std::endl;

	switch (_getch()) {
	case (117):
	{
		if (program.empty()) {
			error();
		}
		std::cout << "Wybierz numer Uzond, ktory chcesz usunac (1 - " << program.size() << "):" << std::endl;
		int num = 0;
		std::cin >> num;
		if (num < 1 || num > program.size()) {
			error();
		}
		program.erase(num - 1);

		break;
	}

	case (111):
	{

		std::cout << "Wybierz numer uzytkownika, ktorego chcesz usunac(1 - " << program.begin()->second.get_people_size() << "):" << std::endl;
		int num = 0;
		std::cin >> num;
		if (num < 1 || num > program.begin()->second.get_people_size()) {
			error();
		}

		for (auto& pair : program) {
			pair.second.removePerson(num);
		}

		break;
	}
	}
}

void print_find(char* str, short str_size, char* keyword, short key_size, int text, int back)
{
	if (str == nullptr || keyword == nullptr) return;

	size_t str_len = strlen(str);
	size_t key_len = strlen(keyword);

	if (str_len > str_size || str_len < 0 || key_len > key_size || key_len < 0) return;

	COORD start, cursor;

	start = getCursorPosition();
	cout << left << setw(str_size) << str;
	cursor = getCursorPosition();
	showcursor(false);

	COLOR DefColor = GetColor();
	COLOR FindColor;

	FindColor.text = (text == -1) ? DefColor.text : text;
	FindColor.back = (back == -1) ? DefColor.back : back;

	char* ptr = strstr_lower(str, keyword);
	short index = 0;

	while (ptr != nullptr)
	{
		index = (int)(ptr - str);                    //Считаем позицию слова в строке и 
		setCursorPosition(start.X + index, start.Y); //переходим к позиции слова.

		// Выводим слово с форматом цвета.
		SetColor(FindColor);
		for (int j = 0; j < key_len; j++) cout << str[index + j];
		SetColor(DefColor);

		//Ищем далее.
		ptr = strstr_lower(ptr + key_len, keyword);
	}

	setCursorPosition(cursor.X, cursor.Y);
	showcursor(true);
}
/*
Uzond& Uzond::operator=(const Uzond& other) {
	if (this != &other) {
		// копируем обычные поля
		Name = other.Name;
		Numer = other.Numer;
		size_Of_arr_peopls = other.size_Of_arr_peopls;
		size = other.size;


		delete[] people;
		people = new Users * [size_Of_arr_peopls];
		for (int i = 0; i < size_Of_arr_peopls; i++) {
			if (dynamic_cast<People*>(other.people[i])) {
				people[i] = new People(*dynamic_cast<People*>(other.people[i]));
			}
			else if (dynamic_cast<Children*>(other.people[i])) {
				people[i] = new Children(*dynamic_cast<Children*>(other.people[i]));
			}
			else {
				people[i] = new Users(*other.people[i]);
			}
		}
	}
	return *this;
}*/
char* strstr_lower(char* str_a, char* str_b)
{


	if (str_a == nullptr || str_b == nullptr)
		return nullptr;


	for (int i = 0;; i++)
	{
		if (str_a[i] == '\0') return nullptr;

		for (int j = 0, k = i;; j++, k++)
		{
			if (str_b[j] == '\0') return (str_a + i);
			if (tolower(str_a[k]) != tolower(str_b[j])) break;
		}
	}
}
vector<char> stringToArrChar(const string& str) {
	vector<char> char_array(str.begin(), str.end());
	char_array.push_back('\0');
	return char_array;
}
void show(const std::map<int, Uzond>& program) {
	system("cls");
	std::cout << "----------------------------------------------------------------------------------------------------\n";
	std::cout << MENU << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------\n";
	std::cout << "                    ---=== UZOND BOOK ===--- your Uzond: " << program.size() << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------\n";
	std::cout << stru << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------\n";

	for (const auto& pair : program) {
		int index = pair.first;
		const Uzond& uzond = pair.second;
		std::cout << std::right << std::setw(3) << std::setfill('0') << index + 1 << std::setfill(' ') << " ";
		uzond();

	}

	std::cout << std::endl << std::endl;
}
void find(std::map<int, Uzond>& program)
{
	if (program.empty())
	{
		error();
		return;
	}
	char keyword[MAXLINE];
	keyword[0] = '\0';

	COORD enter, hat;

	system("cls");
	cout << " Esc - Wejscie" << endl << endl;
	cout << "Szukaj: ";
	enter = getCursorPosition();
	cout << endl;
	cout << stru << endl;
	hat = getCursorPosition();

	COORD temp_pos;
	short len = 0;
	int i;
	// Вводим ключевое слово для поиска.
	do
	{
		if (!stredit(keyword, MAXLINE, enter.X, enter.Y, len, false))
			return;
		len = static_cast<short>(strlen(keyword));

		
		for (i = 0; i < len; i++)
		{
			if (!(isdigit_r(keyword[i]) || isalpha_r(keyword[i])))
				break;
		}

	} while (i != len || len == 0);

	// Выводим результаты.

	system("cls");
	cout << " Esc - Wejscie" << endl << endl;
	cout << "Szukaj: ";
	enter = getCursorPosition();

	cout << endl << stru << endl;
	hat = getCursorPosition();
	// Выводим новые результаты поиска

	for (const auto& pair : program)
	{
		const Uzond& uand = pair.second;
		cout << "Rezultat o "  << " linii" << endl;
		for (short i = 0; i < uand.get_people_size(); i++)
		{
			uand.get_user(i)->find(keyword);
		}
		cout << endl;
	}
	system("pause");
}
