#pragma once
class Spieler
{
private:
	int Leben, Gold, wave, Speichern, Schwierigkeit;
	string Benutzername;
	bool active, Pause;
public:
	Spieler()
	{
		Leben = 20;
		Gold = 500;
		wave = 0;
		active = false;
		Pause = false;
		Speichern = 0;
		Schwierigkeit = 2;
	}
	bool isAlive()
	{
		if (Leben > 0)
			return true;
		else
			return false;
	}
	bool isActive()
	{
		return active;
	}
	void changeActive()
	{
		active = !active;
	}
	void LoseHP()
	{
		Leben -= 1;
	}
	void getHP(int hp)
	{
		Leben += hp;
	}
	void addGold(int G)
	{
		Gold += G;
	}
	int getGold()
	{
		return Gold;
	}
	int getHP()
	{
		return Leben;
	}
	void changePause()
	{
		Pause = !Pause;
	}
	bool getPause()
	{
		return Pause;
	}
	void changeSave(int i)
	{
		Speichern = i;
	}
	int getSave()
	{
		return Speichern;
	}
	void setSchwierigkeit(int i)
	{
		Schwierigkeit = i;
	}
	int getSchwierigkeit()
	{
		return Schwierigkeit;
	}
	string getBenutzername()
	{
		return Benutzername;
	}
	void setBenutzername(string BN)
	{
		Benutzername = BN;
	}
};