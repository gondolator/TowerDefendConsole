#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Enemys
{
private:
	int HP, Gold, x, y, Richtung, Speed, sek, slow, delay;
	int type; //0 = normal -- 1 = Slow resistant -- 2 = 
	bool moved[3], Camouflage, Regeneration;
	static int maxi;
public:
	Enemys(int H, int G, int S, int C, int T, int R)
	{
		HP = H, Gold = G, Speed = S;
		x = 77, y = 17, Richtung = 0, sek = clock(), moved[0] = moved[1] = moved[2] = { false }, slow = 0, Camouflage = C, type = T, Regeneration = R;
	}
	Enemys(int H, int G, int X, int Y, int R, int S, int Slow, int T, int M, int C, int RE)
	{
		HP = H, Gold = G, x = X, y = Y, Richtung = R, Speed = S, slow = Slow, type = T, moved[0] = moved[1] = moved[2] = M, Camouflage = C, sek = clock(), Regeneration = RE;
	}
	int getRichtung()
	{
		return Richtung;
	}
	bool setRichtung(vector<string> &lines)
	{
		if ((x == 49 && y == 17) || (x == 20 && y == 22) || (x == 6 && y == 14))
		{
			Richtung = 1;
		}
		else if ((x == 49 && y == 2) || (x == 36 && y == 22) || (x == 20 && y == 14))
		{
			Richtung = 0;
		}
		else if ((x == 26 && y == 2) || (x == 36 && y == 8))
		{
			Richtung = 3;
		}
		else if (x == 26 && y == 8)
		{
			Richtung = 2;
		}
		if (x == 6 && y == 5)
			return true;
		return false;
		/*
			bool weg0, weg2, weg3, weg1;
			vector<string>::iterator p;
			string line[4] = { { to_string(x - 1) + "," + to_string(y) }, { to_string(x + 1) + "," + to_string(y) }, { to_string(x) + "," + to_string(y - 1) }, { to_string(x) + "," + to_string(y + 1) } };
			weg0 = weg1 = weg2 = weg3 = false;
			p = find(lines.begin(), lines.end(), line[0]);
			if (p != lines.end() || Richtung == 2)
			{
				weg0 = true;
			}
			p = find(lines.begin(), lines.end(), line[1]);
			if (p != lines.end() || Richtung == 0)
			{
				weg2 = true;
			}
			p = find(lines.begin(), lines.end(), line[2]);
			if (p != lines.end() || Richtung == 3)
			{
				weg1 = true;
			}
			p = find(lines.begin(), lines.end(), line[3]);
			if (p != lines.end() || Richtung == 1)
			{
				weg3 = true;
			}
			if (weg0 == false && weg1 == false && weg2 == false)
			{
				return true;
			}
			if (weg0 == false)
				Richtung = 0;
			else if (weg1 == false)
				Richtung = 1;
			else if (weg2 == false)
				Richtung = 2;
			else if (weg3 == false)
				Richtung = 3;
			return false;*/
	}

	bool move(Enemys Gegner, bool erster)
	{
		if (Gegner.canMove() == false && erster == false)
			return false;
		else
		{
			if (moved[0] == false)
				moved[0] = true;
			else if (moved[1] == false)
				moved[1] = true;
			else if (moved[2] == false)
				moved[2] = true;
		}
		switch (Richtung)
		{
		case 0: x -= 1;
			break;
		case 1:  y -= 1;
			break;
		case 2:  x += 1;
			break;
		case 3:  y += 1;
			break;
		}
		if (slow > 0)
		{
			slow--;
		}
		sek = clock();// -(clock() - sek - (1000 / Speed));
		return true;
	}

	static void setMax(int m)
	{
		maxi = m;
	}

	static int getMax()
	{
		return maxi;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	bool getDmg(int dmg)
	{
		HP -= dmg;
		if (HP > 0)
			return false;
		else
			return true;
	}

	int getGold()
	{
		return Gold;
	}

	int getsek()
	{
		return sek;
	}
	int getSpeed()
	{
		return Speed;
	}
	int getHP()
	{
		return HP;
	}
	bool canMove()
	{
		if (moved[0] == true && moved[1] == true && moved[2] == true)
			return true;
		else
		{
			return false;
		}
	}
	bool isSlowed()
	{
		if (slow > 0)
			return true;
		else
			return false;
	}
	void Slow()
	{
		if (type != 1)
		{
			slow = 4;
		}
	}
	bool getCamoo()
	{
		return Camouflage;
	}
	int getType()
	{
		return type;
	}
	bool getRegen()
	{
		return Regeneration;
	}
	void setHP(int hp)
	{
		HP = hp;
	}
};

int Enemys::maxi = 0;