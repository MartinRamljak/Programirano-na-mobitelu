#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <conio.h>
#include <cstdio>

using namespace std;

const string p1_inputs = "qweasd";
const string p2_inputs = "uiojkl";
const int terrain_initial[7][13] = {{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, {5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5}, {5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5}, {5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5}, {5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5}, {5, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 5}, {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}};

int Terrain[7][13];

class Player
{
  public:
	wchar_t c;
	int hp = 1;
	wchar_t sp = L'-';
	int y;
	int x;
	int info_y;
	char action;
	bool turn_taken = false;

	void move(Player* opp);
	void set_action(char act);
	void lose_hp();
	void update_sp();
};

void Player::update_sp()
{
	stringstream ss;
	ss.str("\033[14;" + to_string(info_y) + "H");
	cout << ss.str();
	wcout << sp;
}

void Player::move(Player* opp)
{
	switch (action)
	{
	case 'w':
	case 'i':
	{
		if (Terrain[x - 1][y] <= 3)
			x--;
		break;
	}
	case 'a':
	case 'j':
	{
		if (Terrain[x][y - 1] <= 3)
			y--;
		break;
	}
	case 's':
	case 'k':
	{
		if (Terrain[x + 1][y] <= 3)
			x++;
		break;
	}
	case 'd':
	case 'l':
	{
		if (Terrain[x][y + 1] <= 3)
			y++;
		break;
	}
	case 'q':
	case 'u':
	{
		Terrain[x][y] = 4;
		break;
	}
	case 'e':
	case 'o':
	{
		if (sp != L'-')
		{
			switch (sp)
			{
			case L'†':
			{
				Terrain[x][12 - y] = 5;
				if (opp->x == x && opp->y == 12 - y)
					opp->lose_hp();
				break;
			}
			case L'§':
			{
				if (opp->y == 12 - y)
					opp->lose_hp();
				break;
			}
			case L'∞':
			{
				if (opp->x == x)
					opp->lose_hp();
				break;
			}
			default:
				break;
			}
			sp = L'-';
			update_sp();
		}
		break;
	}
	default:
		break;
	}

	if (Terrain[x][y] < 0)
	{
		Terrain[x][y] = 0;
		switch (rand() % 3)
		{
		case 0:
		{
			sp = L'†';
			break;
		}
		case 1:
		{
			sp = L'§';
			break;
		}
		case 2:
		{
			sp = L'∞';
			break;
		}
		default:
			break;
		}

		update_sp();
	}
}

void Player::set_action(char act)
{
	if ((act == 'e' || act == 'o') && sp == L'-')
		return;
	action = act;
	turn_taken = true;
}

void Player::lose_hp()
{
	--hp;
	stringstream ss;
	ss.str("\033[13;" + to_string(info_y) + "H");
	cout << ss.str();
	wcout << hp;
}

void EraseCursor(int pos)
{
	stringstream ss;
	ss.str("\033[" + to_string(pos) + ";1H");
	cout << ss.str();
	cout << "\033[1K\r";
}

void MoveCursor(int &pos, char move, int max)
{
	switch (move)
	{
	case 'w':
	{
		EraseCursor(pos);
		if (pos == 2)
		{
			stringstream ss;
			ss.str("\033[" + to_string(max) + ";1H");
			cout << ss.str();
			cout << ">";
			pos = max;
		}
		else
		{
			stringstream ss;
			ss.str("\033[" + to_string(pos - 1) + ";1H");
			cout << ss.str();
			cout << ">";
			pos--;
		}
		break;
	}
	case 's':
	{
		EraseCursor(pos);
		if (pos == max)
		{
			cout << "\033[2;1H";
			cout << ">";
			pos = 2;
		}
		else
		{
			stringstream ss;
			ss.str("\033[" + to_string(pos + 1) + ";1H");
			cout << ss.str();
			cout << ">";
			pos++;
		}
		break;
	}
	default:
		break;
	}
}

void PrintMap()
{
	clrscr();
	cout << endl
		 << "   0   0   0   0   0   |   0   0   0   0   0" << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << "                       |                    " << endl
			 << "   0   0   0   0   0   |   0   0   0   0   0" << endl;
	}
	cout << endl
		 << "   P1                         P2" << endl
		 << "   HP: 5                      HP: 5" << endl
		 << "   SP: -                      SP: -";
}

void PrintMainMenu()
{
	clrscr();
	cout << endl
		 << ">Play" << endl
		 << " How To Play" << endl
		 << " Exit"
		 << endl
		 << endl
		 << endl
		 << endl
		 << endl
		 << "Navigate with 'w', 's' and 'space'";
	cout << "\033[2;1H";
}

void PrintInstructions()
{
	clrscr();
	wcout << endl
		  << L"P1:" << endl
		  << L"	w - up" << endl
		  << L"	a - left" << endl
		  << L"	s - down" << endl
		  << L"	d - right" << endl
		  << L"	e - special" << endl
		  << L"	q - bomb" << endl
		  << endl
		  << L"P2:" << endl
		  << L"	i - up" << endl
		  << L"	j - left" << endl
		  << L"	k - down" << endl
		  << L"	l - right" << endl
		  << L"	o - special" << endl
		  << L"	u - bomb" << endl
		  << endl
		  << L"Specials:" << endl
		  << L"     † - deal damage on mirrored position and destroy the tile" << endl
		  << L"     ∞ - deal damage in the whole row" << endl
		  << L"     § - deal damage in the whole mirrored column" << endl
		  << endl
		  << L"Bombs - once placed, they start a countdown and after 3 turns explode dealing famage in a + formation around its location and on the mirrored position" << endl
		  << endl
		  << endl
		  << endl
		  << endl
		  << L"Press 'space' to return";
	while (true)
	{
		if (getch() == ' ')
			break;
	}
}

int MainMenu()
{
	int pos = 2;
	char move = '.';
	PrintMainMenu();
	while (true)
	{
		move = getch();
		MoveCursor(pos, move, 4);
		if (move == ' ')
		{
			switch (pos)
			{
			case 2:
			{
				return 1;
				break;
			}
			case 3:
			{
				return 2;
				break;
			}
			case 4:
			{
				clrscr();
				exit(0);
				break;
			}
			default:
				break;
			}
			move = '.';
		}
	}

	return -1;
}

int SelectCharacter(Player &p1, Player &p2)
{
	wchar_t characters[] = L"$€£¥";
	int pos = 2;
	char move = '.';

	clrscr();
	wcout << "Player 1:" << endl
		  << ">" << characters[0] << endl
		  << " " << characters[1] << endl
		  << " " << characters[2] << endl
		  << " " << characters[3] << endl;

	while (true)
	{
		move = getch();
		MoveCursor(pos, move, 5);
		if (move == ' ')
		{
			p1.c = characters[pos - 2];
			for (int i = pos - 2; i < 3; i++)
				characters[i] = characters[i + 1];
			move = '.';
			pos = 2;
			break;
		}
		move = '.';
	}

	clrscr();
	wcout << "Player 2:" << endl
		  << ">" << characters[0] << endl
		  << " " << characters[1] << endl
		  << " " << characters[2] << endl;

	while (true)
	{
		move = getch();
		MoveCursor(pos, move, 4);
		if (move == ' ')
		{
			p2.c = characters[pos - 2];
			move = '.';
			break;
		}
		move = '.';
	}

	return 0;
}

void PrintPlayer(Player p)
{
	stringstream ss;
	ss.str("\033[" + to_string(2 * p.x) + ";" + to_string(4 * p.y) + "H");
	cout << ss.str();
	wcout << p.c;
}

void PrintTerrain(int y, int x)
{
	stringstream ss;
	ss.str("\033[" + to_string(2 * x) + ";" + to_string(4 * y) + "H");
	cout << ss.str();
	if (Terrain[x][y] == -1)
		cout << '?';
	else if (Terrain[x][y] == 5)
		wcout << L'×';
	else
		cout << Terrain[x][y];
}

void UpdateBombs(Player *p1, Player *p2)
{
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 7; j++)
		{
			if (Terrain[j][i] == 1)
			{
				if ((((p1->y >= i - 1 && p1->y <= i + 1) || (p1->y >= 11 - i && p1->y <= 13 - i)) && p1->x == j) || ((p1->x >= j - 1 && p1->x <= j + 1) && (p1->y == i || p1->y == 12 - i)))
					p1->lose_hp();
				if ((((p2->y >= i - 1 && p2->y <= i + 1) || (p2->y >= 11 - i && p2->y <= 13 - i)) && p2->x == j) || ((p2->x >= j - 1 && p2->x <= j + 1) && (p2->y == i || p2->y == 12 - i)))
					p2->lose_hp();
				Terrain[j][i] = 5;
				if ((i != p1->y || j != p1->x) && (i != p2->y || j != p2->x))
					PrintTerrain(i, j);
				else
					Terrain[j][i] = 6;
			}
			else if (Terrain[j][i] > 1 && Terrain[j][i] < 5)
			{
				Terrain[j][i] = Terrain[j][i] - 1;
				if ((i != p1->y || j != p1->x) && (i != p2->y || j != p2->x))
					PrintTerrain(i, j);
			}
			else if (Terrain[j][i] == 6)
			{
				Terrain[j][i] = 5;
				PrintTerrain(i, j);
			}
		}
}

void SpawnPowerups(int y, int x)
{
	Terrain[x][y] = -1;
	Terrain[x][12 - y] = -1;
	PrintTerrain(y, x);
	PrintTerrain(12 - y, x);
}

void EndScreen(int result)
{
	clrscr();
	cout << endl
		 << endl
		 << endl;

	switch (result)
	{
	case 1:
	{
		wcout << L"\uA9C1\u22B0The winner is Player 1!\u22B1\uA9C2";
		break;
	}
	case 2:
	{
		wcout << L"\uA9C1\u22B0The winner is Player 2!\u22B1\uA9C2";
		break;
	}
	default:
	{
		wcout << L"\u22C9It's a draw.\u22CA";
		break;
	}
	}

	cout << endl
		 << endl
		 << endl
		 << "Press 'space' to return to the menu";

	char temp = '.';
	while (true)
	{
		temp = getch();
		if (temp == ' ')
			break;
	}
}

int Game()
{
	Player p1, p2;
	p1.y = 3;
	p1.x = 3;
	p1.info_y = 8;
	p2.y = 9;
	p2.x = 3;
	p2.info_y = 35;

	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 13; j++)
		{
			Terrain[i][j] = terrain_initial[i][j];
		}

	SelectCharacter(p1, p2);

	PrintMap();

	PrintPlayer(p1);
	PrintPlayer(p2);

	char action = '.';
	while (true)
	{
		action = getch();

		if (action == ' ')
			break;
		else if (p1_inputs.find(action) != string::npos && !p1.turn_taken)
		{
			p1.set_action(action);
		}
		else if (p2_inputs.find(action) != string::npos && !p2.turn_taken)
		{
			p2.set_action(action);
		}

		if (p1.turn_taken && p2.turn_taken)
		{
			if (p2.action == 'i' || p2.action == 'j' || p2.action == 'k' || p2.action == 'l')
			{
				PrintTerrain(p2.y, p2.x);
				p2.move(&p1);
				PrintPlayer(p2);

				PrintTerrain(p1.y, p1.x);
				p1.move(&p2);
				PrintPlayer(p1);
			}
			else
			{
				PrintTerrain(p1.y, p1.x);
				p1.move(&p2);
				PrintPlayer(p1);

				PrintTerrain(p2.y, p2.x);
				p2.move(&p1);
				PrintPlayer(p2);
			}

			UpdateBombs(&p1, &p2);

			if (p1.hp < 1 && p2.hp < 1)
			{
				EndScreen(0);
			}
			else if (p2.hp < 1)
			{
				EndScreen(1);
			}
			else if (p1.hp < 1)
			{
				EndScreen(2);
			}

			if (rand() % 10 == 0)
			{
				int randy = rand() % 5 + 1;
				int randx = rand() % 5 + 1;
				if ((randy != p1.y || randx != p1.x) && (12 - randy != p2.y || randx != p2.x) && (!Terrain[randx][randy] || !Terrain[randx][12 - randy]))
					SpawnPowerups(randy, randx);
			}
			p1.turn_taken = false;
			p2.turn_taken = false;
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	cout << "\033[?25l";
	int state = 0;
	while (true)
	{
		switch (state)
		{
		case 0:
		{
			state = MainMenu();
			break;
		}
		case 1:
		{
			PrintMap();
			state = Game();
			break;
		}
		case 2:
		{
			PrintInstructions();
			state = 0;
			break;
		}
		}
	}
	return 0;
}