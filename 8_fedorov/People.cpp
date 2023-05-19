#include "Header.h"


void Uzond::People::print() const
{
	Users::print();
	COLOR p;
	p.back = 0;
	p.text = 9;
	SetColor(p);
	cout << MANIP << work << " "
		<< MANIP << work_experience;
	p.back = 0;
	p.text = 15;
	SetColor(p);

}

void Uzond::People::save(std::ostream& out) const
{
	out << 1 << " ";
	Users::save(out);
	out << work << " " << work_experience << " ";
}

void Uzond::People::find(char* keyword) const {


	if (strstr_lower(stringToArrChar(FullName->Name_property).data(), keyword)
		|| strstr_lower(stringToArrChar(FullName->Surname_property).data(), keyword)
		|| strstr_lower(stringToArrChar(piesel).data(), keyword)
		|| strstr_lower(stringToArrChar(Year).data(), keyword)
		|| strstr_lower(stringToArrChar(sex).data(), keyword)
		|| strstr_lower(stringToArrChar(work).data(), keyword)
		|| strstr_lower(stringToArrChar(work_experience).data(), keyword))

	{
		print_find(stringToArrChar(FullName->Name_property).data(), MAXLINE, keyword, MAXLINE, Red);
		print_find(stringToArrChar(FullName->Surname_property).data(), MAXLINE, keyword, MAXLINE, Red);
		print_find(stringToArrChar(Year).data(), MAXLINE, keyword, MAXLINE, Red);
		print_find(stringToArrChar(piesel).data(), MAXLINE, keyword, MAXLINE, Red);
		print_find(stringToArrChar(sex).data(), MAXLINE, keyword, MAXLINE, Red);
		COLOR p;
		p.back = 0;
		p.text = 9;
		SetColor(p);
		print_find(stringToArrChar(work).data(), MAXLINE, keyword, MAXLINE, Red);
		print_find(stringToArrChar(work_experience).data(), MAXLINE, keyword, MAXLINE, Red);
		p.back = 0;
		p.text = 15;
		SetColor(p);

		cout << endl;
	}

}

void Uzond::People::edit() {

	string line;
	string name_ = "", surname_ = " ", year_ = " ", piesel_ = " ", sex_ = " ", w = " ", w_e = " ";
	bool valid_input = 0;
	while (!valid_input) {

		string line;

		getline(cin, line);
		name_ = line.substr(0, line.find_first_of(";"));
		line = line.substr(line.find_first_of(";") + 1);
		surname_ = line.substr(0, line.find_first_of(";"));
		line = line.substr(line.find_first_of(";") + 1);
		year_ = line.substr(0, line.find_first_of(";"));
		line = line.substr(line.find_first_of(";") + 1);
		piesel_ = line.substr(0, line.find_first_of(";"));
		line = line.substr(line.find_first_of(";") + 1);
		sex_ = line.substr(0, line.find_first_of(";"));
		line = line.substr(line.find_first_of(";") + 1);
		w = line.substr(0, line.find_first_of(";"));
		line = line.substr(line.find_first_of(";") + 1);
		w_e = line.substr(0, line.find_first_of(";"));

		bool name_is_alpha = true, surname_is_alpha = true, sex_is_alpha = true, Year_is_digit = true, Piesel_is_digit = piesel_.size() == 12;
		if (line.size() > 1) {
			for (char c : name_)
				if (!isalpha_r(c)) {
					name_is_alpha = false;
					break;
				}
			for (char c : surname_)
				if (!isalpha_r(c)) {
					surname_is_alpha = false;
					break;
				}
			for (char c : sex_)
				if (!isalpha_r(c)) {
					sex_is_alpha = false;
					break;
				}
			for (char c : year_) {
				if (!isdigit_r(c)) {
					Year_is_digit = false;
					break;
				}
			}
			for (char c : piesel_)
				if (!isdigit_r(c)) {
					Piesel_is_digit = false;
					break;
				}

			if (!name_is_alpha || !surname_is_alpha || !sex_is_alpha || !Year_is_digit || !Piesel_is_digit)
			{
				error();
			}
			else {


				FullName->Name_property = name_;
				FullName->Surname_property = surname_;
				Year = year_;
				piesel = piesel_;
				sex = sex_;
				work = w;
				work_experience = w_e;

				valid_input = true;
			}
		}
	}

}