#include "Header.h"

#define _CRT_SECURE_NO_WARNINGS
COORD getCursorPosition(void)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hOut, &info);
	return info.dwCursorPosition;
}

void Clear(int x, int y, long cnt)
{
	showcursor(false);
	setCursorPosition(x, y);
	for (int i = 0; i < cnt; i++)
		std::cout << " ";
	setCursorPosition(x, y);
	showcursor(true);
}

bool stredit(char* str, int buffer_size, int x, int y, int cursor, bool clear_after)
{
	/*‘ункци€ возвращает true в случае успеха редактиовани€, иначе - false.*/
	/*
	str - строка дл€ редактировани€.
	buffer_size - размер буфера строки.
	x, y = координаты редактора в консоли.
	cursor - начальное смещение курсора.
	clear_after - очищать ли строку после редактировани€?
	*/
	if (buffer_size <= 0) return false;
	if (cursor >= buffer_size) return false;



	COORD size = getConsoleSize();
	if (x < 0 || x >= size.X || y < 0 || y >= size.Y)
	{
		COORD pos = getCursorPosition();
		x = pos.X;
		y = pos.Y;
	}
	int term = 0;
	while (str[term] != '\0') //ѕоиск терминатора
	{
		if (++term >= buffer_size) //≈сли в строке нет терминатора, ставим его по умолчанию
		{
			term = 0;
			str[term] = '\0';
		}
	}
	if (cursor > term) cursor = term;
	//—охран€ем строку до редактировани€.
	char* backup = new char[buffer_size];
	strcpy(backup, str);
	unsigned press;
	bool edit;
	bool sucess; //¬озвращаемое значение. True - строка изменена. False - строка не изменена. 
	do
	{
		showcursor(false);
		setCursorPosition(x + term, y); cout << ' ';
		showcursor(true);
		setCursorPosition(x, y); cout << str;
		setCursorPosition(x + cursor, y);
		edit = true;
		press = _getch();
		switch (press)
		{
		case Esc:
			strcpy(str, backup);
			sucess = false;    //—трока  не отредактированна.
			edit = false;
			break;
		case Enter:
			sucess = true;  //—трока отредактированна.
			edit = false;
			break;
		case Backspace:
			DeleteCh(str, cursor, term);
			break;
		case 0:
		case 224:
			//ƒл€ специальных клавиш передаетс€ два кода - 224 (или 0) и код клавиши, но буква 'a' тоже имеет код 224
			if (_kbhit()) //≈сли дальше следует код, то это специальна€ клавиша. »наче это буква 'а' русска€
			{
				press = _getch();
				switch (press)
				{
				case Left:
					if (cursor > 0) cursor--;
					break;
				case Right:
					if (cursor < term) cursor++;
					break;
				case End:
					cursor = term;
					break;
				case Del:
					backup[0] = '\0';
					strcpy(str, backup);
					Clear(x, y, buffer_size);
					term = 0;
				case Home:
					cursor = 0;
					break;
				}
				break;
			}
		default:
			InsertCh(str, buffer_size, cursor, term, char(press));
			break;
		}
	} while (edit);



	if (clear_after) Clear(x, y, buffer_size);
	press = cursor = term = edit = 0;



	if (backup != nullptr)
	{
		delete[] backup;
		backup = nullptr;
	}

	return sucess;
}

void showcursor(bool flag)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hOut, &info);
	// info.dwSize = 20;
	info.bVisible = flag;
	SetConsoleCursorInfo(hOut, &info);
}
void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}
COORD getConsoleSize()
{
	COORD size;
	_CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &info);
	size.X = info.srWindow.Right - info.srWindow.Left + 1;
	size.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
	return size;
}
void DeleteCh(char* str, int& cursor, int& term)
{
	if (cursor < 1) return;



	for (int i = cursor-- - 1; i < term; i++)
		str[i] = str[i + 1];



	str[term--] = ' ';
}

void InsertCh(char* str, int buffer_size, int& cursor, int& term, char symb)
{
	if (cursor == buffer_size - 1) return;
	if (term != buffer_size - 1) term++;
	for (int i = term - 1; i > cursor; i--)
		str[i] = str[i - 1];



	str[cursor++] = symb;
	str[term] = '\0';
}

COLOR GetColor()
{
	COLOR Color;
	WORD word = GetColorWord();
	Color.back = (int)(word >> 4);
	Color.text = (int)word - (Color.back << 4);
	return Color;
}
WORD GetColorWord()
{
	WORD text_atribute;
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &info);
	text_atribute = info.wAttributes;
	return text_atribute;
}

void SetColor(COLOR Color)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, (WORD)(Color.back << 4 | Color.text));
}
