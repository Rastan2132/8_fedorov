#include "Header.h"

Uzond Uzond::create(short size_of_people, const std::vector<std::string>& arrOfNameUrzant, const std::vector<std::string>& arrOfNames, const std::vector<std::string>& arrOfSurnames, const std::vector<std::string>& arrOfNameKindergarten, const std::vector<std::string>& arrOfWork) {
    Uzond uand;
    uand.Name_property = arrOfNameUrzant[rand() % arrOfNameUrzant.size()];
    uand.Numer_property = rand_data(_num);

    for (int i = 0; i < size_of_people; i++) {
        bool is_child = rand() % 2;
        std::string sex = rand_data(_sex);
        std::string name = arrOfNames[rand_data(sex)];
        std::string surname = arrOfSurnames[rand_data(sex)];
        std::string pesel = rand_data(_piesel);

        if (is_child) {
            std::string kindergarten = arrOfNameKindergarten[rand() % arrOfNameKindergarten.size()];

            uand.people.push_back(std::make_unique<Children>(name, surname, std::to_string(2023 - (rand() % 18)), pesel, sex, kindergarten));
        }
        else {
            std::string year = rand_data(_year);
            std::string work = arrOfWork[rand() % arrOfWork.size()];

            uand.people.push_back(std::make_unique<People>(name, surname, year, pesel, sex, work, std::to_string(rand() % 20)));
        }
    }

    return uand;
}





void Uzond::addPerson(vector<string> arrOfNames, vector<string> arrOfSurnames, vector<string> arrOfNameKindergarten, vector<string> arrOfWork, bool flag) {
    string sex = rand_data(_sex);
    string name = arrOfNames[rand_data(sex)];
    string surname = arrOfSurnames[rand_data(sex)];
    string year = rand_data(_year);
    string piesel = rand_data(_piesel);
    if (flag) {
        string kindergarten = arrOfNameKindergarten[rand() % arrOfNameKindergarten.size()];
        people.push_back(std::make_unique<Children>(name, surname, to_string(2023 - (rand() % 18)), piesel, sex, kindergarten));
    }
    else {
        string year = rand_data(_year);
        string work = arrOfWork[rand() % arrOfWork.size()];
        people.push_back(std::make_unique<People>(name, surname, year, piesel, sex, work, to_string(rand() % 20)));
    }
}

void Uzond::sort(short flag)
{
    switch (flag)
    {
    case 1:
        std::sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
            return a->FullName->Name_property < b->FullName->Name_property;
            });
        break;
    case 2:
        std::sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
            return a->FullName->Surname_property < b->FullName->Surname_property;
            });
        break;
    case 3:
        std::sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
            return a->sex < b->sex;
            });
        break;
    case 4:
        std::sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
            return a->piesel < b->piesel;
            });
        break;
    case 5:
        std::sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
            return a->Year < b->Year;
            });
        break;
    }
}

void Uzond::removePerson(int index) {
    if (index < 0 || index >= people.size()) {
        return;
    }
    people.erase(people.begin() + (index - 1));
}Uzond Uzond::initForFile(std::istream& in, short size_Of_arr_peopls) {
    Uzond uand;
    string name_u, numer;

    in >> name_u >> numer;
    uand.Name = name_u;
    uand.Numer = numer;
    int flag = 0;
    string name, surname, year, pesel, sex;
    if (size_Of_arr_peopls > 0) {
        for (int j = 0; j < size_Of_arr_peopls; j++) {
            in >> flag;
            if (flag == 0) {
                string k;
                in >> name >> surname >> year >> pesel >> sex >> k;
                uand.people.push_back(std::make_unique<Children>(name, surname, year, pesel, sex, k));
            }
            else {
                string Work_property, Work_experience_property;
                in >> name >> surname >> year >> pesel >> sex >> Work_property >> Work_experience_property;
                uand.people.push_back(std::make_unique<People>(name, surname, year, pesel, sex, Work_property, Work_experience_property));
            }
        }
    }
    return uand;

}

std::istream& operator>>(std::istream& in, std::map<int, Uzond>& program)
{
    program.clear();
    short size, size_of_people;
    in >> size >> size_of_people;
    for (int i = 0; i < size; i++) {
        program.insert({ i, Uzond::initForFile(in, size_of_people) });
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const std::map<int, Uzond>& program)
{
    for (const auto& pair : program) {
        int index = pair.first;
        const Uzond& uzond = pair.second;
        uzond.save_(out);
    }
    return out;
}
bool Uzond::save_(std::ostream& out) const {


        out << Name << " " << Numer << " ";
        for (short j = 0; j < people.size(); j++) {

            people[j]->save(out);

        }
        out << std::endl;
    

    return true;
}
