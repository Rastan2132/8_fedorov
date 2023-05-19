#include "Header.h"

int main()
{
	bool work = 1;
	short urz_num, p_num;;

	std::map<int, Uzond> program;

	vector<string> NAMES = { "Alexander","Maxim","Dmitry","Sergei","Ivan","Anna","Maria","Olga","Elena","Natalia" };
	vector<string> SURNAMES = { "Ivanov","Petrov","Sidorov","Smirnov","Kuznetsov","Ivanova","Petrova","Sidorova","Smirnova","Kuznetsova" };
	vector<string>NAMES_of_Uzond = { "Urzad_Pracy","Urzad_Spraw","Urzad_Skarbowy","Urzad_s._cywilnego" };
	vector<string> arrOfNameKindergarten = { "Krasnoludek", "Sloneczko", "Bajka", "Promyczek" };
	vector<string> arrOfWork = { "nauczyciel", "lekarz", "informatyk", "sprzedawca", "prawnik" };

	//if (chek_file("Uzonds.txt") == 0)
	//{
		short size = rand() % 10 + 1;
		short size_of_peopl = rand() % 10 + 1;
		for (short i = 0; i < size; i++) {
			Uzond uzond = Uzond::create(size_of_peopl, NAMES_of_Uzond, NAMES, SURNAMES, arrOfNameKindergarten, arrOfWork);
			program.insert(std::make_pair(i, uzond));
		}



/* }
	else
	{
		std::ifstream file("Uzonds.txt");
		program >> file;
		file.close();
	}
	*/

	if (program.size() < 0)
	{
		error();
	}
	
	ShowCursor(0);
	do
	{
		show(program);
		switch (_getch())
		{
		case (113):
			work = false;
			break;
		case (97):
			add(program, NAMES, SURNAMES, NAMES_of_Uzond, arrOfNameKindergarten, arrOfWork);
			break;
		case (100):
			dell(program);
			break;
		case (101):
			do {
				cout << "wprowadz numer urzendu i numer osoby" << endl;
				cin >> urz_num >> p_num;
				if (urz_num > 0 && p_num > 0 && urz_num <= program.size() && p_num <= program[0].get_people_size())
					break;
				error();
			} while (true);
			edit(program, urz_num - 1, p_num - 1);
			break;
		case (115): {
			short flag = 0;
			cout << endl << "Wybiesz:\n1 - posortowac za Name\n2 - posortowac za Surname\n3 - posortowac za sex\n4 - posortowac za piesel\n5 - posortowac za Year\n";
			cout << endl;
			switch (_getch())
			{
			case (49):
				flag = 1;
				break;
			case (50):
				flag = 2;
				break;
			case (51):
				flag = 3;
				break;
			case (52):
				flag = 4;
				break;
			case (53):
				flag = 5;
				break;

			default:
			{
				cout << "error" << endl;
				break;
			}

			}
			//	for (short l = 0; l < program.size(); l++)
				//		program[l].sort(flag);
		}
				  break;
		case (121):
			//find(program);
			break;
		}
	} while (work);
	//	std::ofstream  file("Uzonds.txt");
//	file << program.size() << " " << program[0].get_people_size() << " ";
//	file << program;

//	file.close();

}
