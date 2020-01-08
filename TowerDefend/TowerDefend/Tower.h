#pragma once
#include <string>
#include <sstream>
using namespace std;

class tower
{
private:
	unsigned int damage[4], attackspeed[4], level, x, y, sleep, type, count, kills;
	float range[4];
	bool active, Camouflage, ranges, bonus, boost;
	static int anzahl;
	static int damages;
public:
	tower(int art, int X, int Y)
	{
		Camouflage = ranges = bonus = boost = false;
		switch (art)
		{
		case 1: damage[0] = 100, attackspeed[0] = 3, range[0] = 10, damage[1] = 150, attackspeed[1] = 4, range[1] = 12, damage[2] = 250, attackspeed[2] = 5, range[2] = 15, damage[3] = 400, attackspeed[3] = 6, range[3] = 18;
			break;
		case 2: damage[0] = 200, attackspeed[0] = 1, range[0] = 100, damage[1] = 300, attackspeed[1] = 2, range[1] = 100, damage[2] = 700, attackspeed[2] = 2, range[2] = 100, damage[3] = 1100, attackspeed[3] = 3, range[3] = 100;
			break;
		case 3: damage[0] = 2, attackspeed[0] = 20, range[0] = 6, damage[1] = 3, attackspeed[1] = 25, range[1] = 6, damage[2] = 3, attackspeed[2] = 35, range[2] = 7, damage[3] = 4, attackspeed[3] = 40, range[3] = 8, Camouflage = true;
			break;
		case 4: damage[0] = 0, attackspeed[0] = 0, range[0] = 5, damage[1] = 0, attackspeed[1] = 0, range[1] = 7, damage[2] = 0, attackspeed[2] = 0, range[2] = 8, damage[3] = 0, attackspeed[3] = 0, range[3] = 9, Camouflage = true;
			break;
		case 5: damage[0] = 10, attackspeed[0] = 50, range[0] = 15, damage[1] = 15, attackspeed[1] = 100, range[1] = 16, damage[2] = 25, attackspeed[2] = 100, range[2] = 18, damage[3] = 40, attackspeed[3] = 100, range[3] = 22;
			break;
		case 6: damage[0] = 17, attackspeed[0] = 3, range[0] = 5, damage[1] = 17, attackspeed[1] = 7, range[1] = 5, damage[2] = 25, attackspeed[2] = 9, range[2] = 5, damage[3] = 175, attackspeed[3] = 3, range[3] = 5, count = 1, anzahl++;
			break;
		case 7: damage[0] = 0, attackspeed[0] = 0, range[0] = 6, damage[1] = 0, attackspeed[1] = 0, range[1] = 6, damage[2] = 0, attackspeed[2] = 0, range[2] = 6, damage[3] = 0, attackspeed[3] = 0, range[3] = 6;
			break;
		case 8: damage[0] = 20, attackspeed[0] = 10, range[0] = 0, damage[1] = 60, attackspeed[1] = 10, range[1] = 0, damage[2] = 180, attackspeed[2] = 10, range[2] = 0, damage[3] = 540, attackspeed[3] = 10, range[3] = 0, Camouflage = true;
			break;
		}
		x = X, y = Y, sleep = level = 0, active = true, type = art, kills = 0;
	}
	tower(int X, int Y, int art, int lvl, int C, int camoo, int rs, int B)
	{
		Camouflage = bonus = boost = false;
		switch (art)
		{
		case 1: damage[0] = 100, attackspeed[0] = 3, range[0] = 10, damage[1] = 150, attackspeed[1] = 4, range[1] = 12, damage[2] = 250, attackspeed[2] = 5, range[2] = 15, damage[3] = 400, attackspeed[3] = 6, range[3] = 18;
			break;
		case 2: damage[0] = 200, attackspeed[0] = 1, range[0] = 100, damage[1] = 300, attackspeed[1] = 2, range[1] = 100, damage[2] = 700, attackspeed[2] = 2, range[2] = 100, damage[3] = 1100, attackspeed[3] = 3, range[3] = 100;
			break;
		case 3: damage[0] = 2, attackspeed[0] = 20, range[0] = 6, damage[1] = 3, attackspeed[1] = 25, range[1] = 6, damage[2] = 3, attackspeed[2] = 35, range[2] = 7, damage[3] = 4, attackspeed[3] = 40, range[3] = 8, Camouflage = true;
			break;
		case 4: damage[0] = 0, attackspeed[0] = 0, range[0] = 5, damage[1] = 0, attackspeed[1] = 0, range[1] = 7, damage[2] = 0, attackspeed[2] = 0, range[2] = 8, damage[3] = 0, attackspeed[3] = 0, range[3] = 9, Camouflage = true;
			break;
		case 5: damage[0] = 10, attackspeed[0] = 50, range[0] = 15, damage[1] = 15, attackspeed[1] = 100, range[1] = 16, damage[2] = 25, attackspeed[2] = 100, range[2] = 18, damage[3] = 40, attackspeed[3] = 100, range[3] = 22;
			break;
		case 6: damage[0] = 17, attackspeed[0] = 3, range[0] = 5, damage[1] = 17, attackspeed[1] = 7, range[1] = 5, damage[2] = 25, attackspeed[2] = 9, range[2] = 5, damage[3] = 175, attackspeed[3] = 3, range[3] = 5, count = C, anzahl++;
			break;
		case 7: damage[0] = 0, attackspeed[0] = 0, range[0] = 6, damage[1] = 0, attackspeed[1] = 0, range[1] = 6, damage[2] = 0, attackspeed[2] = 0, range[2] = 6, damage[3] = 0, attackspeed[3] = 0, range[3] = 6;
			break;
		case 8:  damage[0] = 8, attackspeed[0] = 10, range[0] = 0, damage[1] = 16, attackspeed[1] = 10, range[1] = 0, damage[2] = 30, attackspeed[2] = 10, range[2] = 0, damage[3] = 50, attackspeed[3] = 10, range[3] = 0, Camouflage = true;
			break;
		}
		x = X, y = Y, sleep = level = lvl, active = true, type = art, Camouflage = camoo, ranges = rs, boost = B, kills = 0;
	}
	int getX()
	{
		return x;
	}
	static int getAnzahl()
	{
		return anzahl;
	}
	static void backAnzahl()
	{
		anzahl--;
	}
	static int getdamages()
	{
		return damages;
	}
	static void adddamages(int D)
	{
		damages += D;
	}
	int getY()
	{
		return y;
	}
	float getRange()
	{
		return range[level];
	}
	void shot()
	{
		sleep = clock();
		active = false;
	}
	bool checkShot(int sek, float Speed)
	{
		if (sek - sleep > (1000 / attackspeed[level]) / Speed / (4 * boost + 1))
			active = true;
		return active;
	}
	bool isActive()
	{
		return active;
	}
	int getDmg()
	{
		return damage[level];
	}
	int getSpeed()
	{
		return attackspeed[level];
	}
	int getCount()
	{
		return count;
	}
	void resetCount()
	{
		count = 1;
	}
	void improveCount()
	{
		count++;
	}
	int getSleep()
	{
		return sleep;
	}
	void Upgrade()
	{
		level++;
		if (level == 2 && type == 2)
			Camouflage = true;
	}
	void Downgrade()
	{
		level--;
	}
	int getLvl()
	{
		return level;
	}
	char drawtype()
	{
		if (type == 1)
			return 'T';
		else if (type == 2)
			return 'B';
		else if (type == 3)
			return 'U';
		else if (type == 4)
			return 'H';
		else if (type == 5)
			return 'I';
		else if (type == 6)
			return 'X';
		else if (type == 7)
			return 'Y';
		else if (type == 8)
			return 'P';
	}
	int gettype()
	{
		return type;
	}
	void notBuild()
	{
		active = false;
	}
	void getInfo(string &info)
	{
		if (level < 3)
		{
			info = (to_string(damage[level + 1]) + " / " + to_string(attackspeed[level + 1]) + " / " + to_string((int)range[level + 1]));
		}
		else
			info = "MAX LEVEL";
	}
	bool getCamoo()
	{
		return Camouflage;
	}
	bool getRanges()
	{
		return ranges;
	}
	void inArea(int lvl)
	{
		if (lvl >= 0)
		{
			Camouflage = true;
		}
		if (lvl >= 1 && ranges == false)
		{
			range[0] *= 1.1; range[1] *= 1.1; range[2] *= 1.1; range[3] *= 1.1;
			ranges = true;
		}
		if (lvl >= 2)
		{
			bonus = true;
		}
		if (lvl >= 3)
		{

		}
	}
	void NotinArea()
	{
		if ((type != 2 || level < 2) && type != 3 && type != 4)
		{
			Camouflage = false;
		}
		if (ranges == true)
		{
			ranges = false;
			range[0] /= 1.1; range[1] /= 1.1; range[2] /= 1.1; range[3] /= 1.1;
		}
		bonus = false;
	}
	bool getBonus()
	{
		return bonus;
	}
	void changeBoost()
	{
		boost = !boost;
	}
	bool getBoost()
	{
		return boost;
	}
	int getkills()
	{
		return kills;
	}
	void improvekills()
	{
		kills += 1;
	}
};

int tower::anzahl = 0;
int tower::damages = 0;