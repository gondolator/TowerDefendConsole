#include <iostream>
#include <vector>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <wincon.h>
#include <stdio.h>
#include "Bananas.h"
#include "Enemys.h"
#include "Spieler.h"
#include "Tower.h"

using namespace std;

void clearBuffer()
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IOFBF, BUFSIZ);
}
//funktion um x und y pos auf der console auswählen
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
//funktion um einen Turm Upzugraden
void setconsolecolor(int textColor, int bgColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}
//führt den Verkauf eines Turms durch
void Sell(tower &Turm, Spieler &Player)
{
	float value = 0.75; //kostenfaktor für die verschiedenen schwierigkeitsstufen
	if (Player.getSchwierigkeit() == 1)
		value = 0.8 * 0.85;
	else if (Player.getSchwierigkeit() == 3)
		value = 1.2 *0.65;
	int cost;
	switch (Turm.gettype()) //kosten für das nächste level wird eingelesen
	{
	case 1:switch (Turm.getLvl()) { case 0: cost = 75 * value; break; case 1: cost = 175 * value; break; case 2: cost = 425 * value; break; case 3: cost = 925 * value; break; }
		   break;
	case 2:switch (Turm.getLvl()) { case 0: cost = 100 * value; break; case 1: cost = 250 * value; break; case 2: cost = 600 * value; break; case 3: cost = 1350 * value; break; }
		   break;
	case 3:switch (Turm.getLvl()) { case 0: cost = 100 * value; break; case 1: cost = 250 * value; break; case 2: cost = 600 * value; break; case 3: cost = 1350 * value; break; }
		   break;
	case 4:switch (Turm.getLvl()) { case 0: cost = 100 * value; break; case 1: cost = 200 * value; break; case 2: cost = 500 * value; break; case 3: cost = 950 * value; break; }
		   break;
	case 5:switch (Turm.getLvl()) { case 0: cost = 175 * value; break; case 1: cost = 475 * value; break; case 2: cost = 925 * value; break; case 3: cost = 1825 * value; break; }
		   break;
	case 6:switch (Turm.getLvl()) { case 0: cost = 800 * value; break; case 1: cost = 2100 * value; break; case 2: cost = 3800 * value; break; case 3: cost = 8300 * value; break; }
		   break;
	case 7:switch (Turm.getLvl()) { case 0: cost = 1000 * value; break; case 1: cost = 2500 * value; break; case 2: cost = 5000 * value; break; case 3: cost = 9500 * value; break; }
		   break;
	case 8:switch (Turm.getLvl()) { case 0: cost = 175 * value; break; case 1: cost = 475 * value; break; case 2: cost = 925 * value; break; case 3: cost = 1825 * value; break; }
		   break;
	}
	Player.addGold(cost);
	gotoxy(Turm.getX(), Turm.getY()); cout << " ";
}
//login
void login(string BN, string PW, Spieler &Player)
{
login:
	system("cls");
	int y = 11;
	bool leave = false;
	fstream f, ff;
	string line, übergang = "";
	vector<string>lines, lines2;
	f.open("Accounts.txt");
	while (getline(f, line))
	{
		lines.push_back(line); //lese die zeilen aus Accounts.txt in lines ein
	}
	f.close();
	ff.open("Highscore.txt");
	while (getline(ff, line))
	{
		lines2.push_back(line); //lese die zeilen aus Highscore.txt in lines2 ein
	}
	ff.close();
	if (lines2.size() == 0) //Wenn die Highscore.txt datei leer ist
	{
		ofstream fff;
		fff.open("Highscore.txt");
		fff << "Leicht:\n\nMittel:\n\nSchwer:\n\n"; //Initialisiere sie
		goto login;									//und starte diese funktion von neuen
	}
	vector<string>::iterator l;
	lines2.erase(0 + lines2.begin()); //lösche die erste Zeile Leicht: aus lines2
	l = find(lines2.begin(), lines2.end(), "Mittel:"); //Suche in lines2 die Zeile Mittel:
	for (int i = l - lines2.begin(); i > 0; i--)
	{
		lines2.erase(i + lines2.begin()); //lösche alles bis einschlieslich Mittel: außer die erste Zeile
	}
	l = find(lines2.begin(), lines2.end(), "Schwer:"); //Suche in lines2 die Zeile Schwer:
	for (int i = l - lines2.begin(); i > 1; i--)
	{
		lines2.erase(i + lines2.begin()); //Lösche alles bis einschlieslich Schwer: außer die ersten zwei Zeilen
	}
	for (int i = lines2.size() - 1; i > 2; i--)
	{
		lines2.erase(i + lines2.begin()); //Lösche alles bis auf die ersten drei Zeilen
	}
	if (BN.length() > 0 && PW.length() > 0) //Wenn ein Benutzername und ein Passwort in diese funktion übergeben wurden
	{
		for (unsigned int i = 0; i < lines.size(); i++) //von 0 bis die Anzahl der registrierten Accounts
		{
			if (lines[i] == BN + ' ' + PW) //wenn der Benutzername und das Passwort mit einer Zeile übereinstimmen
			{
				for (int i = 0; i < 3; i++) //für die 3 gespeicherten lines2 Zeilen
				{
					line = lines2[i].substr(0, lines2[i].find("(")); //speichere den namen der lines2 zeile in line
					if (line == BN) //wenn der Benutzer == der name in line
					{
						if (i > 0) //wenn es der zweite oder dritte durchlauf ist
							übergang += ' '; //füge dem String übergang ein leerzeichen hinzu
						for (int n = 0; n <= i + 1; n++)
							übergang += '*'; //füge so viele Sterne hinzu in welchen durchlauf du dich befindest
					}
				}
				BN += übergang; //addiere die sterne und leerzeichen zum benutzernamen
				Player.setBenutzername(BN); //setze den Benutzernamen
			}
		}
	}
	else //wenn kein Benutzername und/oder Passwort übergeben wurde
	{
		gotoxy(25, 11); cout << "Benutzername:";
		gotoxy(25, 13); cout << "Passwort:";
	LOGIN:
		while (leave == false) //Schleife in der Benutzername und Passwort eingegeben werden
		{
			if (_kbhit())
			{
				char c = _getch();
				switch (c)
				{
				case -32:
					break;
				case 8: if (y == 11 && BN.size() > 0) BN = BN.substr(0, BN.size() - 1); else if (y == 13 && PW.size() > 0) PW = PW.substr(0, PW.size() - 1); gotoxy(45, 11); cout << BN << ' '; gotoxy(45, 13); for (int i = 0; i < PW.length(); i++) cout << '*'; cout << ' ';
					break; //lösche das letzte zeichen in der gerade befindlichen zeile
				case 9: if (y == 11) y = 13; else y = 11; //wenn tab gedrückt wird wechsele die eingabezeile
					break;
				case 13: leave = true; //verlasse die Schleife bei enter
					break;
				case 27: return; //breche den login mit ESC ab
					break;
				default: if (y == 11) BN += c; else PW += c; gotoxy(45, 11); cout << BN; gotoxy(45, 13); for (int i = 0; i < PW.length(); i++) cout << '*'; //Schreibe in die befindliche Zeile, bei Passwort zeile * statt eingegebenes Zeichen
					break;
				}
			}
		}
		leave = false;
		string PW2;
		for (int i = 0; i < PW.size(); i++)
		{
			PW2 += to_string(PW[i]); //PW2 == PW
		}
		for (int i = 0; i < lines.size(); i++) //für jeden Registrierten Benutzer
		{
			if (lines[i] == BN + ' ' + PW2) //wenn der Benutzername und das Passwort mit einer Zeile übereinstimmen -- gleiche wie oben auch
			{
				for (int z = 0; z < 3; z++)
				{
					line = lines2[z].substr(0, lines2[z].find("("));
					if (line == BN)
					{
						if (z > 0)
							übergang += ' ';
						for (int n = 0; n <= z; n++)
							übergang += '*';
					}
				}
				BN += übergang;
				Player.setBenutzername(BN);
				return;
			}
		}
		setconsolecolor(4, 0);
		gotoxy(20, 4); cout << "Benutzername oder Passwort ist falsch!";
		setconsolecolor(15, 0);
		for (int i = 0; i <= (BN.length() >= PW.length() ? BN.length() : PW.length()); i++)
		{
			gotoxy(45 + i, 11); cout << " ";
			gotoxy(45 + i, 13); cout << " ";
			y = 11;
		}
		BN = PW = "";
		goto LOGIN;
	}
}
//register
void Register(Spieler &Player)
{
anmelden:
	system("cls");
	bool leave = false;
	int y = 11;
	fstream f;
	ofstream ff;
	string line, BN, PW;
	vector<string>lines, lines2, lines3;
	f.open("Accounts.txt");
	while (getline(f, line))
	{
		lines2.push_back(line.substr(0, line.find(" ")));
		lines3.push_back(line.substr(line.find(" ") + 1, line.length()));
		lines.push_back(line);
	}
	f.close();
	gotoxy(25, 11); cout << "Benutzername:";
	gotoxy(25, 13); cout << "Passwort:";
	while (leave == false)
	{
		if (_kbhit())
		{
			char c = _getch();
			switch (c)
			{
			case -32:
				break;
			case 8: if (y == 11 && BN.size() > 0) BN = BN.substr(0, BN.size() - 1); else if (y == 13 && PW.size() > 0) PW = PW.substr(0, PW.size() - 1); gotoxy(45, 11); cout << BN << ' '; gotoxy(45, 13); for (int i = 0; i < PW.length(); i++) cout << '*'; cout << ' ';
				break;
			case 9: if (y == 11) y = 13; else y = 11;
				break;
			case 13: leave = true;
				break;
			case 27: return;
				break;
			default: if (y == 11) BN += c; else PW += c; gotoxy(45, 11); cout << BN; gotoxy(45, 13); for (int i = 0; i < PW.length(); i++) cout << '*';
				break;
			}
		}
	}
	if (BN.length() < 4 || PW.length() < 4 || BN.length() > 15 || PW.length() > 15)
		goto anmelden;
	for (int i = 0; i < BN.length(); i++)
	{
		if ((BN[i] >= 65 && BN[i] <= 90) || (BN[i] >= 97 && BN[i] <= 122) || (BN[i] >= 48 && BN[i] <= 57))
			continue;
		else
			goto anmelden;
	}
	for (int i = 0; i < PW.length(); i++)
	{
		if ((PW[i] >= 65 && PW[i] <= 90) || (PW[i] >= 97 && PW[i] <= 122) || (PW[i] >= 48 && PW[i] <= 57))
			continue;
		else
			goto anmelden;
	}
	vector<string>::iterator l;
	l = find(lines2.begin(), lines2.end(), BN);
	if (l != lines2.end())
		goto anmelden;
	string PW2;
	for (int i = 0; i < PW.length(); i++)
	{
		PW2 += to_string(PW[i]);
	}
	lines.push_back(BN + ' ' + PW2);
	ff.open("Accounts.txt");
	for (int i = 0; i < lines.size(); i++)
	{
		ff << lines[i] << endl;
	}
	login(BN, PW2, Player);
}
//führt den Upgrade eines Turms durch
void Upgrade(tower &Turm, int &cost, int upgrade[], Spieler &Player, int i, string &info, int Option)
{
	float value = 1; //kostenfaktor für die verschiedenen schwierigkeitsstufen
	if (Player.getSchwierigkeit() == 1)
		value = 0.8;
	else if (Player.getSchwierigkeit() == 3)
		value = 1.2;
	switch (Turm.gettype()) //kosten für das nächste level wird eingelesen
	{
	case 1:switch (Turm.getLvl()) { case 0: cost = 100 * value; break; case 1: cost = 250 * value; break; case 2: cost = 500 * value; break; }
		   break;
	case 2:switch (Turm.getLvl()) { case 0: cost = 150 * value; break; case 1: cost = 350 * value; break; case 2: cost = 750 * value; break; }
		   break;
	case 3:switch (Turm.getLvl()) { case 0: cost = 150 * value; break; case 1: cost = 350 * value; break; case 2: cost = 750 * value; break; }
		   break;
	case 4:switch (Turm.getLvl()) { case 0: cost = 100 * value; break; case 1: cost = 300 * value; break; case 2: cost = 450 * value; break; }
		   break;
	case 5:switch (Turm.getLvl()) { case 0: cost = 300 * value; break; case 1: cost = 450 * value; break; case 2: cost = 900 * value; break; }
		   break;
	case 6:switch (Turm.getLvl()) { case 0: cost = 1300 * value; break; case 1: cost = 1700 * value; break; case 2: cost = 4500 * value; break; }
		   break;
	case 7:switch (Turm.getLvl()) { case 0: cost = 1500 * value; break; case 1: cost = 2500 * value; break; case 2: cost = 4500 * value; break; }
		   break;
	case 8:switch (Turm.getLvl()) { case 0: cost = 450 * value; break; case 1: cost = 1050 * value; break; case 2: cost = 2250 * value; break; }
		   break;
	}
	Turm.getInfo(info);
	gotoxy(63, 14); cout << "                ";
	gotoxy(63, 14); cout << info;
	if (Option == 0) //wenn instant Upgrade deaktiviert ist
	{
		if (upgrade[0] == false) //wenn das erste mal auf den tower gedrückt wird
		{
			upgrade[0] = true;
			return;
		}
		else if (upgrade[0] == true && upgrade[1] != i)
		{
			upgrade[0] = false;
			upgrade[1] = -1;
			return;
		}
		else //wenn das zweite mal auf den tower gedrückt wird
		{
			if (Player.getGold() >= cost && Turm.getLvl() < 3) //wenn genug gold vorhanden und der turm nicht max level erreicht hat
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Turm.getLvl() == 0 ? 9 : Turm.getLvl() == 1 ? 4 : 2); gotoxy(Turm.getX(), Turm.getY()); cout << Turm.drawtype(); //färbe den turm auf eine andere farbe//2 grün -- 4 rot -- 6 gelb -- 9 blau -- 10 hellgrün
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //setze die schreib farbe wieder zurück auf weiß
				Player.addGold(-cost); //ziehe das gold ab
				Turm.Upgrade();//werte den turm auf
			}
		}
	}
	else //wenn instant Upgrade aktiviert ist
	{
		if (Player.getGold() >= cost && Turm.getLvl() < 3) //wenn genug gold vorhanden und der turm nicht max level erreicht hat
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Turm.getLvl() == 0 ? 9 : Turm.getLvl() == 1 ? 4 : 2); gotoxy(Turm.getX(), Turm.getY()); cout << Turm.drawtype(); //färbe den turm auf eine andere farbe//2 grün -- 4 rot -- 6 gelb -- 9 blau -- 10 hellgrün
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //setze die schreib farbe wieder zurück auf weiß
			Player.addGold(-cost); //ziehe das gold ab
			Turm.Upgrade();//werte den turm auf
		}
	}
}
//check ob das feld auf das man geklickt hat zum bauen freigegeben ist
bool isValid(vector<tower> &Türme, vector<string>Wand, int x, int y, int &cost, char c, int upgrade[], Spieler &Player, int focus[], string &info, int speicher[], int wave, int Option)
{
	bool change = upgrade[0];
	for (int i = 0; i < Türme.size(); i++) //für alle türme
	{
		if (Türme[i].getX() == x && Türme[i].getY() == y) //checke ob maus auf einen turm liegt
		{
			if (c == NULL) //wenn der Turm aufwert modus ausgewählt ist
			{
				focus[0] = i; //focusiere den Turm(zeige seine range an)
				speicher[0] = i; //Speicher um den letzten zug rückgängig machen zu können
				if (Türme[i].gettype() != 6 || Player.isActive() == false) //wenn keine wave aktiv ist sind alle Türme Upgradebar in einer wave können keine farmen Upgegraded werden
					Upgrade(Türme[i], cost, upgrade, Player, i, info, Option); //wenn maus auf turm, führe upgrade durch und gebe not valid zurück
				if (change == upgrade[0] && change == true) //wenn upgrade durchgeführt wurde 
				{
					upgrade[0] = false; //setze upgrade variable auf false
					if (Player.isActive() == false) //nur wenn keine runde aktiv ist werden alle nötigen daten zum rückgängigmachen gespeichert
					{
						speicher[0] = i; speicher[1] = cost; speicher[2] = wave;
					}
					cost = 0; //setze kosten auf null
					focus[1] = -1; //setze den focus zurück
					info = ""; //setze die info zurück
				}
				else if (change != upgrade[0] && change == false) //wenn der turm zum ersten mal angeklickt wurde 
				{
					upgrade[1] = i; //setze die zweite upgrade variable auf true um beim zweiten klick upzugraden
				}
			}
			else if (c == '$')
			{
				focus[0] = -1;
				speicher[0] = -2; speicher[1] = 0; speicher[2] = 0;
				Sell(Türme[i], Player);
				Türme.erase(i + Türme.begin());
			}
			else if (c == '#' && Türme[i].getBoost() == false && Player.getGold() >= 300 && Türme[i].gettype() != 4 && Türme[i].gettype() != 3 && Türme[i].gettype() != 6 && Türme[i].gettype() != 7)
			{
				Player.addGold(-300);
				Türme[i].changeBoost();
			}
			return false; //gib feld nicht valide zurück
		}
	}
	if (change == upgrade[0] && change == true)//wenn upgrade variable true aber turm nicht angeklickt
	{
		focus[0] = -1; //setze den focus zurück
		upgrade[0] = false; //setze upgrade variable auf false
		upgrade[1] = -1; //setze die Upgrade variable zurück
		info = ""; //setze die info zurück
		if (c == NULL)
			cost = 0; //setze kosten auf null
	}
	string line2 = to_string(x) + "," + to_string(y); //initaliesiere einen String mit in form x,y um mit Wand vector zu vergleichen
	for (int i = 0; i < Wand.size(); i++) //für jede Wand
	{
		if (line2 == Wand[i]) //checke ob maus auf Wand liegt
			return false; //gebe not valid zurück
	}
	vector<string>::iterator p;
	vector<string>::iterator pp;
	string line[4] = { { to_string(x - 1) + "," + to_string(y) },{ to_string(x + 1) + "," + to_string(y) },{ to_string(x) + "," + to_string(y - 1) },{ to_string(x) + "," + to_string(y + 1) } }; //array mit größe 4, jeweil die umliegenden felder
	p = find(Wand.begin(), Wand.end(), line[0]); //gehe den Wand vector durch ob *links* eine Wand
	pp = find(Wand.begin(), Wand.end(), line[1]);//"" *rechts ""
	if (p != Wand.end() && pp != Wand.end()) //wenn links und rechts eine Wand ist
	{
		return false; //gib not valid zurück weil es dann ein weg feld ist
	}
	p = find(Wand.begin(), Wand.end(), line[2]);//gehe den Wand vecor durch ob *oben* eine Wand
	pp = find(Wand.begin(), Wand.end(), line[3]);//"" *unten* ""
	if (p != Wand.end() && pp != Wand.end())//wenn oben und unten ein Wand ist
	{
		return false; //gib not valid zurück weil es dann ein weg feld ist
	}
	if (x >= 63 && x <= 75 && y >= 1 && y <= 12) //wenn maus irgendwo zwischen der Turm auswahl ist
		return false; //gib not valid zurück
	if ((x >= 5 && x <= 7 && y == 5) || (x == 6 && y == 14) || (x >= 19 && x <= 20 && y >= 14 && y <= 15) || (x == 20 && y == 22) || (x == 36 && (y == 22 || y == 8)) || (x == 26 && (y == 8 || y == 2)) || (x == 49 && (y == 2 || y == 17)) || (x == 0 && y == 0))
		return false; // gib not valid zurück bei den restlichen feldern --base --weg felder die nicht durch algorithmus erkannt wurden --some more
	focus[0] = -1;
	return true; //wenn keine der vorherigen checks not valid zurück gegeben hat gebe jetzt valid zurück
}
//checke ob das feld auf das man geklickt hat einen Gegner beinhaltet
int onEnemy(vector<Enemys>Gegner, int x, int y)
{
	for (int i = 0; i < Gegner.size(); i++) //für jeden gegner
	{
		if (x == Gegner[i].getX() && y == Gegner[i].getY()) //checke ob das feld auf einen gegner liegt
			return i; //gib den indes des gegners zurück
	}
	return -1; //wenn kein gegner auf den feld gib -1(false) zurück
}
//initialisiert den string vector Wand mit den daten aus der textdatei Wand.txt
void CreateWall(vector<string> &Wand)
{
	fstream f; //variable um dokument zu öffnen
	f.open("Wand.txt"); //öffne das textdokument Wand.txt
	string line; //variable zum zwischenspeichern
	while (getline(f, line)) //solange das dokument nicht am ende ist, lese eine zeile in die variable line
	{
		line = line.substr(0, line.size() - 2); //lösche die letzten zwei zeichen, welche angeben welche wand art es ist, da diese nicht wichtig hierfür sind
		Wand.push_back(line);  //schreibe die zeile in den Wand vector
	}
	f.close();
}
//wird am anfang jeder runde ausgeführt um die neuen gegner aus der textdatei Gegner.txt zu initialisieren
void CreateEnemys(vector<Enemys> &Gegner, int wave)
{
	LONG64 Punkte = pow((70 * wave), 1.35) * 80; //punkte welche die gegner pro runde zur verfügung haben
	LONG64 aktPunkte = Punkte; //zweite Punkte variable
	int HP, Speed, Gold, count, misstakes = 0, sek = clock();
	srand(sek); //random einlesen
	while (aktPunkte > 1000) //solange noch genug punkte vorhandne sind
	{
		int mode = rand() % 4 + 1; //Random einer von 4 gegner arten
		if (wave % 15 == 0) //außer bei jeder 15 wave
			mode = 5; //dort ist es gegner art 5
		switch (mode) //initialisiere die HP und Speed für die verschiedenen arten
		{
		case 1: HP = rand() % (int)(500 + (3.5 * pow(wave, 2.5) - 2.5 * wave)) + (500 * pow(wave, 0.8)); Speed = rand() % (int)(0.075 *pow(wave, 1.425) - 0.2 * wave + 3) + 4; count = rand() % (wave / 5 + 2) + 1;
			break;
		case 2: HP = rand() % (int)(75 + (1.5 * pow(wave, 2.0) - 5.5 * wave)) + (75 * pow(wave, 0.8)); Speed = rand() % (int)(0.075 *pow(wave, 1.525) - 0.15 * wave + 4) + 25; count = rand() % (wave / 2 + 5) + 5;
			break;
		case 3: HP = rand() % (int)(250 + (2.3 * pow(wave, 2.265) - 3 * wave)) + (150 * pow(wave, 0.8)); Speed = rand() % (int)(0.075 *pow(wave, 1.475) - 0.18 * wave + 3) + 7; count = rand() % (wave / 3 + 5) + 4;
			break;
		case 4: HP = rand() % (int)(1000 + (5 * pow(wave, 3.0) - 1.5 * wave)) + (1000 * pow(wave, 0.83)); Speed = rand() % (int)(0.065 *pow(wave, 1.4) - 0.2 * wave + 3) + 15; count = 1;
			break;
		case 5: Speed = wave / 15 + 3; HP = aktPunkte / (((500 - pow(wave, 1.25)) > 0.32 ? (500 - pow(wave, 1.25)) : 0.32) / 500) / Speed; count = 1;
			break;
		}
		Gold = ((HP / 75) + 1) * ((Speed / 5) + 1) / ((0.131 * pow((wave + 4), 1.57)) - (0.48 * (wave + 4)) + 3); //initialiesiere das Gold pro Gegner
		for (int i = 0; i < count; i++) //von 0 bis zum count wie oft der selbe gegner hintereinander spawnen soll
		{
			bool Camoo = false; // setze cammo auf false
			bool Regen = false;
			int art = 0, random;
			if (wave >= 10 && mode != 5 && rand() % (7 - (int)(wave / 20) > 1 ? 7 - (int)(wave / 20) : 2) == 0) //ab wave 10 und nicht für gegner art 5, wirf einen random ob Gegner Camoo sein soll
				Camoo = true;
			if (wave >= 15 && mode != 5 && rand() % (12 - (int)(wave / 15) > 1 ? 12 - (int)(wave / 15) : 2) == 0) //ab wave 15 und nicht für gegner art 5, wirf einen random ob Gegner Regen sein soll
				Regen = true;
			if (wave >= 15 && mode != 5)
			{
				random = rand() % (30 - (int)(wave / 20) > 6 ? 30 - (int)(wave / 20) : 6); //ab wave 15 und nicht für gegner art 5, wirf einen random ob Gegner speziell ist
				switch (random)
				{
				case 0: art = 1;
					break;
				case 1: art = 2;
					break;
				case 2: art = 3;
					break;
				case 3: art = 4;
					break;
				default: art = 0;
					break;
				}
			}
			if ((HP * Speed) *(((500 - pow(wave, 1.25)) > 0.32 ? (500 - pow(wave, 1.25)) : 0.32) / 500) <= aktPunkte) //wenn die Punkte des gegners kleiner der noch vorhandenen 
			{
				misstakes = 0; //setze abbruch condition zurück
				aktPunkte -= (HP * Speed) *(((500 - pow(wave, 1.25)) > 0.32 ? (500 - pow(wave, 1.25)) : 0.32) / 500); //ziehe die punkte ab
				Gegner.push_back({ HP, Gold, Speed, Camoo, art, Regen }); //erzeuge Gegner
			}
			else if ((HP * Speed) *(((500 - pow(wave, 1.25)) > 0.32 ? (500 - pow(wave, 1.25)) : 0.32) / 500) > aktPunkte && i == 0) //wenn nicht genug punkte vorhanden sind
				misstakes += 1; //erhöhe abbruch condition
		}
		if (misstakes >= 100) //wenn die abbruch variable 100 erreicht hab
		{
			break; //stoppe mit dem erzeugen von gegnern
		}
	}
	if (Gegner.size() > 2000)
	{
		float multi = pow((float)Gegner.size() / 2000.00, 0.7);
		for (int i = Gegner.size() - 1; i >= 2000; i--)
		{
			Gegner.pop_back();
		}
		for (int i = 0; i < Gegner.size(); i++)
		{
			Gegner[i].setHP(Gegner[i].getHP() * multi);
		}
	}
	Enemys::setMax(Gegner.size()); //setze in die statische max variable der Gegner die anzahl der Gegner
}
//erstellt die Speicher dateien, falls noch keine vorhanden
void CreateTXT()
{
	fstream f;
	ofstream ff;
	string line;
	vector<string>lines;
	f.open("Options.txt");
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	f.close();
	if (lines.size() <= 1)
	{
		ff.open("Options.txt");
		for (int i = 0; i < 7; i++)
			ff << "1" << endl;
		ff.close();
	}
	lines.clear();
	f.open("Highscore.txt");
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	f.close();
	if (lines.size() <= 1)
	{
		ff.open("Highscore.txt");
		ff << "Leicht: " << endl << endl << "Mittel:" << endl << endl << "Schwer:" << endl << endl;
		ff.close();
	}
	lines.clear();
	f.open("Accounts.txt");
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	f.close();
	if (lines.size() <= 1)
	{
		ff.open("Accounts.txt");
		ff << endl;
		ff.close();
	}
	lines.clear();
	f.open("Save.txt");
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	f.close();
	if (lines.size() <= 1)
	{
		ff.open("Save.txt");
		ff << "1: " << endl << endl << "2: " << endl << endl << "3: " << endl;
		ff.close();
	}
	lines.clear();
}
//löscht und zeichnet die map neu --im falle von visual bugs manuell aufrufbar
void redraw(int wave, int cost, Spieler Player, vector<tower> &Türme, int focus, int art, float speed, bool durchlauf, string info, int Page, vector<Banana>Bananas, vector<Enemys>Gegner, bool complete)
{
	for (int i = 0; i < Türme.size(); i++)
	{
		if (Türme[i].gettype() != 7)
		{
			Türme[i].NotinArea();
		}
	}
	for (int i = 0; i < Türme.size(); i++)
	{
		if (Türme[i].gettype() == 7)
		{
			for (int n = 0; n < Türme.size(); n++)
			{
				if (sqrt(pow(Türme[i].getX() - Türme[n].getX(), 2) + pow(Türme[i].getY() - Türme[n].getY(), 2)) <= Türme[i].getRange() && Türme[n].gettype() != 7)
				{
					Türme[n].inArea(Türme[i].getLvl());
				}
			}
		}
	}
	vector<string>::iterator l;
	vector<string>::iterator ll;
	setconsolecolor(15, 0);
	fstream f;
	f.open("Wand.txt"); //öffne Wand.txt
	vector<string>lines;
	string line;
	while (getline(f, line)) //lese zeile für zeile ein
	{
		lines.push_back(line); //und übergebe sie dem vector lines
	}
	f.close();
	if (complete == true)
	{
		system("cls");
		for (int i = 0; i < lines.size(); i++) //für jedes element lines
		{
			line = lines[i].substr(0, lines[i].find(",")); //line ist jetzt die erste zahl der zeile lines
			int x, y, z;
			x = stoi(line); //übergebe diese zahl x
			line = lines[i].substr(lines[i].find(",") + 1, lines[i].find(" ") - 2); //line ist die zweite zahl, welche hinter dem komma steht
			y = stoi(line); //übergebe diese zahl y
			line = lines[i].substr(lines[i].find(" ") + 1, 1); //line ist die letzte zahl  welche die wand art angibt
			z = stoi(line); //übergebe diese zahl z
			gotoxy(x, y); if (z == 1) cout << "|"; else cout << "_"; //gebe an stelle x, y die wandart z aus
		}
	}
	setconsolecolor(15, 12);
	if (focus >= 0 && Türme[focus].gettype() != 2) //wenn ein turm außer dem sniper turm einen focus hat
	{
		for (int i = 0; i < 80; i++) //für jedes x feld
		{
			for (int j = 0; j < 25; j++) //für jedes y feld
			{
				if (sqrt(pow(Türme[focus].getX() - i, 2) + pow(Türme[focus].getY() - j, 2)) <= Türme[focus].getRange() && (i <= 62 || j >= 13)) //wenn das feld in reichweite des turms ist
				{
					l = find(lines.begin(), lines.end(), to_string(i) + ',' + to_string(j) + " 1"); //wenn in dem vector lines, welcher die wand speichert eine zeile mit i,j 1
					ll = find(lines.begin(), lines.end(), to_string(i) + ',' + to_string(j) + " 2"); //oder i,j 2 vorhanden ist, ist l bzw ll nicht lines.end()
					if (l != lines.end()) //wenn eine wand typ 1 gefunden wurde 
					{
						gotoxy(i, j);  cout << "|"; //gib | mit roten hintergrund aus
					}
					else if (ll != lines.end()) //wenn eine wand typ 2 gefunden wurde 
					{
						gotoxy(i, j); cout << "_"; //gib _ mit roten hintergrund aus
					}
					else //ansonsten
						gotoxy(i, j);  cout << " "; //mal den hintergrund rot an
				}
			}
		}
	}
	if (focus == -2) //wenn der focus auf -2 also auf alle türme gerichtet ist
	{
		for (int q = 1; q <= 4; q++) //für 4 verschiedene turm arten
		{
			for (int z = 0; z < Türme.size(); z++) //für jeden turm
			{
				if (Türme[z].gettype() != 2 && Türme[z].gettype() == (q == 1 ? 5 : (q == 2 ? 1 : (q == 3 ? 3 : 4)))) //der reihenfolge nach mit der größten range
				{
					switch (Türme[z].gettype()) //färbe den hintergrund je nachdem welche turmart 
					{
					case 1: setconsolecolor(15, 2);
						break;
					case 2: setconsolecolor(15, 6);
						break;
					case 3: setconsolecolor(15, 9);
						break;
					case 4: setconsolecolor(15, 12);
						break;
					case 5: setconsolecolor(15, 20);
						break;
					}
					for (int i = 0; i < 80; i++) //für jedes x feld
					{
						for (int j = 0; j < 25; j++) //für jedes y feld
						{
							if (sqrt(pow(Türme[z].getX() - i, 2) + pow(Türme[z].getY() - j, 2)) <= Türme[z].getRange() && (i <= 62 || j >= 13)) //wenn das feld in reichweite der turmes
							{
								l = find(lines.begin(), lines.end(), to_string(i) + ',' + to_string(j) + " 1");
								ll = find(lines.begin(), lines.end(), to_string(i) + ',' + to_string(j) + " 2");
								if (l != lines.end())
								{
									gotoxy(i, j);  cout << "|";
								}
								else if (ll != lines.end())
								{
									gotoxy(i, j); cout << "_";
								}
								else
									gotoxy(i, j);  cout << " ";
							}
						}
					}
				}
			}
		}
	}
	setconsolecolor(15, 0);
	for (int i = 0; i < Türme.size(); i++) //für jeden turm
	{
		switch (Türme[i].getLvl()) //fürbe die schriftfarbe je nach turm level
		{
		case 0: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			break;
		case 1: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			break;
		case 2: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			break;
		case 3: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			break;
		}
		gotoxy(Türme[i].getX(), Türme[i].getY()); cout << Türme[i].drawtype(); //gib den turm aus
	}
	setconsolecolor(15, 0);
	for (int i = 0; i < Bananas.size(); i++) //für jede Banane
	{
		gotoxy(Bananas[i].getX(), Bananas[i].getY()); cout << "z"; //gib die Banane aus
	}
	for (int i = 0; i < Gegner.size(); i++) //für jeden Gegner
	{
		if (Gegner[i].canMove() == true) //gib den Gegner aus sofern er schon laufen kann
		{
			setconsolecolor(15 - 9 * Gegner[i].getCamoo(), 0); gotoxy(Gegner[i].getX(), Gegner[i].getY()); cout << "o"; setconsolecolor(15, 0);
		}
		else
			break;
	}
	if (Page == 0) //gib die Turmauswahl aus wenn man auf Seite 1 ist
	{
		gotoxy(63, 6); cout << "[T]  [B]  [U]";
		gotoxy(63, 10); cout << "[ ]  [H]  [I]";
	}
	else //gib die Turmauswahl für Seite 2 aus
	{
		gotoxy(63, 6); cout << "[X]  [Y]  [P]";
		gotoxy(63, 10); cout << "[ ]  [$]  [#]";
	}
	if (speed == 2) //wenn speed modus an ist fürbe den Button grün
		setconsolecolor(2, 0);
	else //ansonsten färbe ihn rot -- das gleiche für die unteren buttons
		setconsolecolor(4, 0);
	gotoxy(60, 22); cout << "[>>]";
	if (speed == 0.5)
		setconsolecolor(2, 0);
	else
		setconsolecolor(4, 0);
	gotoxy(60, 24); cout << "[<<]";
	if (Player.isActive() == true)
		setconsolecolor(2, 0);
	else
		setconsolecolor(4, 0);
	gotoxy(68, 22); cout << "[Start]";
	if (durchlauf == true)
		setconsolecolor(2, 0);
	else
		setconsolecolor(4, 0);
	gotoxy(68, 24); cout << "[Durchlauf]";
	if (Player.getPause() == true)
		setconsolecolor(2, 0);
	else
		setconsolecolor(4, 0);
	gotoxy(64, 23); cout << "[||]";
	setconsolecolor(15, 0);
	switch (art) //markiere den Turm  der in der Bauauswahl ausgewählt ist
	{
	case 0: gotoxy(64, 11); cout << "^"; gotoxy(64, 12); cout << "|";
		break;
	case 1:
	case 6: gotoxy(64, 7); cout << "^"; gotoxy(64, 8); cout << "|";
		break;
	case 2:
	case 7: gotoxy(69, 7); cout << "^"; gotoxy(69, 8); cout << "|";
		break;
	case 3: gotoxy(74, 7); cout << "^"; gotoxy(74, 8); cout << "|";
		break;
	case 4:
	case -1: gotoxy(69, 11); cout << "^"; gotoxy(69, 12); cout << "|";
		break;
	case 5:  gotoxy(74, 11); cout << "^"; gotoxy(74, 12); cout << "|";
		break;
	}
	gotoxy(5, 4); cout << Player.getHP(); //gebe die restlichen display daten aus
	gotoxy(5, 5); cout << "[X]";
	gotoxy(63, 1); cout << "Wave: " << wave;
	gotoxy(63, 3); cout << "Gold: " << Player.getGold() << " (" << cost << ")";
	gotoxy(63, 14); cout << info;
}
//Speichert den aktuellen Spielstand --noch nicht implementiert
int Save(Spieler &Player, vector<float>&Übergabe, int Bananas, int Enemys, int Towers, bool ranked)
{
	for (int i = Player.getBenutzername().length(); i > 0; i--)
	{
		if (Player.getBenutzername()[i] == '*' || Player.getBenutzername()[i] == ' ')
		{
			Player.setBenutzername(Player.getBenutzername().substr(0, Player.getBenutzername().size() - 1));
		}
	}
start:
	if (Player.getSave() == 0)
		return 0;
	else if (Player.getSave() == 3)
		return 1;
	else if (Player.getSave() == 2 || ranked == false)
	{
		system("cls");
		fstream f;
		ofstream ff;
		vector<string>::iterator l, ll, lll;
		int Speicher;
		f.open("Save.txt");
		string line;
		vector<string>lines;
		while (getline(f, line))
		{
			lines.push_back(line);
		}
		f.close();
		if (lines.size() <= 5)
		{
			ff.open("Save.txt");
			ff << "1:\n\n" << "2:\n\n" << "3:\n\n";
			ff.close();
			goto start;
		}
		else
		{
			l = find(lines.begin(), lines.end(), "1:");
			ll = find(lines.begin(), lines.end(), "2:");
			lll = find(lines.begin(), lines.end(), "3:");
			if (lines[l - lines.begin() + 1].length() > 0)
			{
				setconsolecolor(stoi(lines[l - lines.begin() + 18]) == 1 ? 2 : stoi(lines[l - lines.begin() + 18]) == 2 ? 6 : 4, 0);
				gotoxy(30, 5); cout << "[" << stoi(lines[l - lines.begin() + 1]) << "]";
			}
			else
			{
				setconsolecolor(15, 0);
				gotoxy(30, 5); cout << "[" << lines[l - lines.begin() + 1] << "]";
			}
			if (lines[ll - lines.begin() + 1].length() > 0)
			{
				setconsolecolor(stoi(lines[ll - lines.begin() + 18]) == 1 ? 2 : stoi(lines[ll - lines.begin() + 18]) == 2 ? 6 : 4, 0);
				gotoxy(44, 5); cout << "[" << stoi(lines[ll - lines.begin() + 1]) << "]";
			}
			else
			{
				setconsolecolor(15, 0);
				gotoxy(44, 5); cout << "[" << lines[ll - lines.begin() + 1] << "]";
			}
			if (lines[lll - lines.begin() + 1].length() > 0)
			{
				setconsolecolor(stoi(lines[lll - lines.begin() + 18]) == 1 ? 2 : stoi(lines[lll - lines.begin() + 18]) == 2 ? 6 : 4, 0);
				gotoxy(58, 5); cout << "[" << stoi(lines[lll - lines.begin() + 1]) << "]";
			}
			else
			{
				setconsolecolor(15, 0);
				gotoxy(58, 5); cout << "[" << lines[lll - lines.begin() + 1] << "]";
			}
			setconsolecolor(15, 0);
		}
		while (true)
		{
			POINT p; //variable für mausklick
			HWND hWndConsole;
			hWndConsole = GetConsoleWindow();
			GetCursorPos(&p); //mausposition in relation zum Bildschirm beziehen
			ScreenToClient(hWndConsole, &p); //mausposition auf console beziehen
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (((int)(p.x / 9.65 + 0.5) >= 31 && (int)(p.x / 9.65 + 0.5) <= 31 + lines[l - lines.begin() + 1].length()) && (int)(p.y / 13 + 0.5) == 5)
				{
					Speicher = 1;
					break;
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 45 && (int)(p.x / 9.65 + 0.5) <= 45 + lines[ll - lines.begin() + 1].length()) && (int)(p.y / 13 + 0.5) == 5)
				{
					Speicher = 2;
					break;
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 59 && (int)(p.x / 9.65 + 0.5) <= 59 + lines[lll - lines.begin() + 1].length()) && (int)(p.y / 13 + 0.5) == 5)
				{
					Speicher = 3;
					break;
				}
			}
		}
		if (Speicher == 1 && lines[l - lines.begin() + 1].length() > 0 || Speicher == 2 && lines[ll - lines.begin() + 1].length() > 0 || Speicher == 3 && lines[lll - lines.begin() + 1].length() > 0)
		{
			gotoxy(1, 9); cout << "Sind Sie sich sicher, dass Sie dieses Speicherstand \201berschreiben wollen?";
			gotoxy(30, 11); cout << "[JA]"; gotoxy(40, 11); cout << "[NEIN]";
			while (true)
			{
				POINT p; //variable für mausklick
				HWND hWndConsole;
				hWndConsole = GetConsoleWindow();
				GetCursorPos(&p); //mausposition in relation zum Bildschirm beziehen
				ScreenToClient(hWndConsole, &p); //mausposition auf console beziehen
				if (GetAsyncKeyState(VK_LBUTTON))
				{
					if (((int)(p.x / 9.65 + 0.5) >= 31 && (int)(p.x / 9.65 + 0.5) <= 32) && (int)(p.y / 13 + 0.5) == 11)
					{
						break;
					}
					else if (((int)(p.x / 9.65 + 0.5) >= 41 && (int)(p.x / 9.65 + 0.5) <= 44) && (int)(p.y / 13 + 0.5) == 11)
					{
						return 0;
					}
				}
			}
		}
		vector<string>::iterator auswahl, auswahl2;
		switch (Speicher)
		{
		case 1: auswahl = l, auswahl2 = ll;
			break;
		case 2: auswahl = ll, auswahl2 = lll;
			break;
		case 3: auswahl = lll, auswahl2 = lines.end();
			break;
		}
		for (int i = auswahl2 - lines.begin() - 1; i > auswahl - lines.begin(); i--)
		{
			lines.erase(lines.begin() + i);
		}
		vector<string>NewLines;
		for (int i = 0; i <= auswahl - lines.begin(); i++)
		{
			NewLines.push_back(lines[i]);
		}
		for (int i = 0; i < 14; i++)
		{
			NewLines.push_back(to_string(Übergabe[i]));
		}
		NewLines.push_back("Player:");
		for (int i = 14; i < 18; i++)
		{
			NewLines.push_back(to_string(Übergabe[i]));
		}
		NewLines.push_back(Player.getBenutzername());
		NewLines.push_back("Bananas:");
		for (int i = 18; i < 18 + 3 * Bananas; i++)
		{
			NewLines.push_back(to_string(Übergabe[i]));
		}
		NewLines.push_back("Gegner:");
		for (int i = 18 + 3 * Bananas; i < 18 + 3 * Bananas + 11 * Enemys; i++)
		{
			NewLines.push_back(to_string(Übergabe[i]));
		}
		NewLines.push_back("Türme:");
		for (int i = 18 + 3 * Bananas + 11 * Enemys; i < 18 + 3 * Bananas + 11 * Enemys + 8 * Towers; i++)
		{
			NewLines.push_back(to_string(Übergabe[i]));
		}
		l = find(lines.begin(), lines.end(), "1:");
		ll = find(lines.begin(), lines.end(), "2:");
		lll = find(lines.begin(), lines.end(), "3:");
		switch (Speicher)
		{
		case 1: auswahl = l, auswahl2 = ll;
			break;
		case 2: auswahl = ll, auswahl2 = lll;
			break;
		case 3: auswahl = lll, auswahl2 = lines.end();
			break;
		}
		for (int i = auswahl2 - lines.begin(); i < lines.size(); i++)
		{
			NewLines.push_back(lines[i]);
		}
		ff.open("Save.txt");
		for (int i = 0; i < NewLines.size(); i++)
		{
			ff << NewLines[i] << endl;
		}
		ff.close();
	}
	if (Player.getSave() == 2)
		exit(42);
	else
		return 0;
}
//Lädt den letzten Spielstand --noch nicht implementiert
int Load(vector<float>&Übergabe, vector<Banana>&Bananas, vector<Enemys>&Gegner, vector<tower>&Türme, Spieler &Player)
{
	for (int i = Player.getBenutzername().length(); i > 0; i--)
	{
		if (Player.getBenutzername()[i] == '*' || Player.getBenutzername()[i] == ' ')
		{
			Player.setBenutzername(Player.getBenutzername().substr(0, Player.getBenutzername().size() - 1));
		}
	}
	bool ranked;
	vector<string>Newlines;
	Übergabe.clear();
	system("cls");
	fstream f;
	ofstream ff;
	vector<string>::iterator l, ll, lll;
	int Speicher;
	f.open("Save.txt");
	string line;
	vector<string>lines;
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	f.close();
	if (lines.size() < 6)
	{
		gotoxy(5, 7); cout << "Es sind keine gespeicherten daten vorhanden";
		Sleep(2500);
		return 0;
	}
	l = find(lines.begin(), lines.end(), "1:");
	ll = find(lines.begin(), lines.end(), "2:");
	lll = find(lines.begin(), lines.end(), "3:");
	if (lines[l - lines.begin() + 1].length() > 0)
		setconsolecolor(stoi(lines[l - lines.begin() + 18]) == 1 ? 2 : stoi(lines[l - lines.begin() + 18]) == 2 ? 6 : 4, 0);
	else
		setconsolecolor(15, 0);
	if (lines[l - lines.begin() + 1].length() > 0)
	{
		gotoxy(30, 5); cout << "[" << stoi(lines[l - lines.begin() + 1]) << "]";
	}
	else
	{
		gotoxy(30, 5); cout << "[" << lines[l - lines.begin() + 1] << "]";
	}
	if (lines[ll - lines.begin() + 1].length() > 0)
	{
		setconsolecolor(stoi(lines[ll - lines.begin() + 18]) == 1 ? 2 : stoi(lines[ll - lines.begin() + 18]) == 2 ? 6 : 4, 0);
	}
	else
		setconsolecolor(15, 0);
	if (lines[ll - lines.begin() + 1].length() > 0)
	{
		gotoxy(44, 5); cout << "[" << stoi(lines[ll - lines.begin() + 1]) << "]";
	}
	else
	{
		gotoxy(44, 5); cout << "[" << lines[ll - lines.begin() + 1] << "]";
	}
	if (lines[lll - lines.begin() + 1].length() > 0)
		setconsolecolor(stoi(lines[lll - lines.begin() + 18]) == 1 ? 2 : stoi(lines[lll - lines.begin() + 18]) == 2 ? 6 : 4, 0);
	else
		setconsolecolor(15, 0);
	if (lines[lll - lines.begin() + 1].length() > 0)
	{
		gotoxy(58, 5); cout << "[" << stoi(lines[lll - lines.begin() + 1]) << "]";
	}
	else
	{
		gotoxy(58, 5); cout << "[" << lines[lll - lines.begin() + 1] << "]";
	}
	setconsolecolor(15, 0);
	while (true)
	{
		POINT p; //variable für mausklick
		HWND hWndConsole;
		hWndConsole = GetConsoleWindow();
		GetCursorPos(&p); //mausposition in relation zum Bildschirm beziehen
		ScreenToClient(hWndConsole, &p); //mausposition auf console beziehen
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (((int)(p.x / 9.65 + 0.5) >= 31 && (int)(p.x / 9.65 + 0.5) <= 31 + lines[l - lines.begin() + 1].length()) && (int)(p.y / 13 + 0.5) == 5 && lines[l - lines.begin() + 1].length() > 0)
			{
				Speicher = 1;
				break;
			}
			else if (((int)(p.x / 9.65 + 0.5) >= 45 && (int)(p.x / 9.65 + 0.5) <= 45 + lines[ll - lines.begin() + 1].length()) && (int)(p.y / 13 + 0.5) == 5 && lines[ll - lines.begin() + 1].length() > 0)
			{
				Speicher = 2;
				break;
			}
			else if (((int)(p.x / 9.65 + 0.5) >= 59 && (int)(p.x / 9.65 + 0.5) <= 59 + lines[lll - lines.begin() + 1].length()) && (int)(p.y / 13 + 0.5) == 5 && lines[lll - lines.begin() + 1].length() > 0)
			{
				Speicher = 3;
				break;
			}
		}
		if (_kbhit()) //auswahl
		{
			char c = _getch();
			switch (c)
			{
			case 27: return 0;
				break;
			}
		}
	}
	vector<string>::iterator auswahl, auswahl2;
	switch (Speicher)
	{
	case 1: auswahl = l, auswahl2 = ll;
		break;
	case 2: auswahl = ll, auswahl2 = lll;
		break;
	case 3: auswahl = lll, auswahl2 = lines.end();
		break;
	}
	for (int i = lines.size() - 1; i > auswahl2 - lines.begin(); i--)
	{
		lines.erase(i + lines.begin());
	}
	for (int i = auswahl - lines.begin(); i >= 0; i--)
	{
		lines.erase(i + lines.begin());
	}
	ranked = stoi(lines[1]);
	if (Player.getBenutzername() != lines[19])
		return 0;
	for (int i = 0; i < 14; i++)
	{
		Übergabe.push_back(stoi(lines[0]));
		lines.erase(0 + lines.begin());
	}
	lines.erase(0 + lines.begin());
	Player.addGold(-Player.getGold() + stoi(lines[0]));
	lines.erase(0 + lines.begin());
	for (int i = 0; i < Player.getHP() - stoi(lines[0]); i++)
	{
		Player.LoseHP();
	}
	lines.erase(0 + lines.begin());
	Player.setSchwierigkeit(stoi(lines[0]));
	lines.erase(0 + lines.begin());
	if (Player.isActive() != stoi(lines[0]))
	{
		Player.changeActive();
	}
	lines.erase(0 + lines.begin());
	Player.setBenutzername(lines[0]);
	lines.erase(0 + lines.begin());
	l = find(lines.begin(), lines.end(), "Bananas:");
	ll = find(lines.begin(), lines.end(), "Gegner:");
	for (int i = 0; i < ((ll - lines.begin() - 1) - (l - lines.begin() + 1)) / 3; i++)
	{
		Bananas.push_back({ stoi(lines[l - lines.begin() + 1 + 3 * i]) , stoi(lines[l - lines.begin() + 2 + 3 * i]) , stoi(lines[l - lines.begin() + 3 + 3 * i]) });
	}
	l = find(lines.begin(), lines.end(), "Gegner:");
	ll = find(lines.begin(), lines.end(), "Türme:");
	for (int i = 0; i < ((ll - lines.begin() - 1) - (l - lines.begin() + 1)) / 11; i++)
	{
		Gegner.push_back({ stoi(lines[l - lines.begin() + 1 + 11 * i]) , stoi(lines[l - lines.begin() + 2 + 11 * i]) , stoi(lines[l - lines.begin() + 3 + 11 * i]), stoi(lines[l - lines.begin() + 4 + 11 * i]), stoi(lines[l - lines.begin() + 5 + 11 * i]), stoi(lines[l - lines.begin() + 6 + 11 * i]), stoi(lines[l - lines.begin() + 7 + 11 * i]), stoi(lines[l - lines.begin() + 8 + 11 * i]), stoi(lines[l - lines.begin() + 9 + 11 * i]), stoi(lines[l - lines.begin() + 10 + 11 * i]), stoi(lines[l - lines.begin() + 11 + 11 * i]) });
	}
	l = find(lines.begin(), lines.end(), "Türme:");
	for (int i = 0; i < ((lines.size() - 1) - (l - lines.begin() + 1)) / 8; i++)
	{
		Türme.push_back({ stoi(lines[l - lines.begin() + 1 + 8 * i]) , stoi(lines[l - lines.begin() + 2 + 8 * i]) , stoi(lines[l - lines.begin() + 3 + 8 * i]), stoi(lines[l - lines.begin() + 4 + 8 * i]) , stoi(lines[l - lines.begin() + 5 + 8 * i]) , stoi(lines[l - lines.begin() + 6 + 8 * i]), stoi(lines[l - lines.begin() + 7 + 8 * i]), stoi(lines[l - lines.begin() + 8 + 8 * i]) });
	}
	if (ranked == true)
	{
		lines.clear();
		f.open("Save.txt");
		while (getline(f, line))
		{
			lines.push_back(line);
		}
		f.close();
		l = find(lines.begin(), lines.end(), "1:");
		ll = find(lines.begin(), lines.end(), "2:");
		lll = find(lines.begin(), lines.end(), "3:");
		switch (Speicher)
		{
		case 1: auswahl = l, auswahl2 = ll;
			break;
		case 2: auswahl = ll, auswahl2 = lll;
			break;
		case 3: auswahl = lll, auswahl2 = lines.end();
			break;
		}
		for (int i = 0; i <= auswahl - lines.begin(); i++)
		{
			Newlines.push_back(lines[i]);
		}
		Newlines.push_back("");
		for (int i = auswahl2 - lines.begin(); i < lines.size(); i++)
		{
			Newlines.push_back(lines[i]);
		}
		ff.open("Save.txt");
		for (int i = 0; i < Newlines.size(); i++)
		{
			ff << Newlines[i] << endl;
		}
		ff.close();
	}
}
//gibt die Highscore liste aus
void Score()
{
	system("cls");
	fstream f;
	string line, line2;
	vector<string>lines, lines2;
	vector<string>::iterator l, ll, lll;
	f.open("Highscore.txt");
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	f.close();
	f.open("Accounts.txt");
	while (getline(f, line))
	{
		lines2.push_back(line);
	}
	f.close();
	ll = find(lines.begin(), lines.end(), "Mittel:");
	lll = find(lines.begin(), lines.end(), "Schwer:");
	gotoxy(0, 3); cout << "Leicht:";
	for (int i = 1, n = 1; i < ll - lines.begin(); i++, n++)
	{
		line = lines[i].substr(0, lines[i].find("("));
		setconsolecolor(4, 0);
		for (int n = 0; n < lines2.size(); n++)
		{
			line2 = lines2[n].substr(0, lines2[n].find(" "));
			if (line == line2)
			{
				setconsolecolor(15, 0);
				break;
			}
		}
		gotoxy(0, n + 3); cout << n << ": " << lines[i];
	}
	setconsolecolor(15, 0);
	gotoxy(25, 3); cout << "Mittel:";
	for (int i = ll - lines.begin() + 1, n = 1; i < lll - lines.begin(); i++, n++)
	{
		line = lines[i].substr(0, lines[i].find("("));
		setconsolecolor(4, 0);
		for (int n = 0; n < lines2.size(); n++)
		{
			line2 = lines2[n].substr(0, lines2[n].find(" "));
			if (line == line2)
			{
				setconsolecolor(15, 0);
				break;
			}
		}
		gotoxy(25, n + 3); cout << n << ": " << lines[i];
	}
	setconsolecolor(15, 0);
	gotoxy(50, 3); cout << "Schwer:";
	for (int i = lll - lines.begin() + 1, n = 1; i < lines.size(); i++, n++)
	{
		line = lines[i].substr(0, lines[i].find("("));
		setconsolecolor(4, 0);
		for (int n = 0; n < lines2.size(); n++)
		{
			line2 = lines2[n].substr(0, lines2[n].find(" "));
			if (line == line2)
			{
				setconsolecolor(15, 0);
				break;
			}
		}
		gotoxy(50, n + 3); cout << n << ": " << lines[i];
	}
	setconsolecolor(15, 0);
	while (true)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c == 27)
				break;
		}
	}
}
//eintrag in die Highscore liste
void highscore(int wave, int Schwierigkeit, string Benutzername)
{
	for (int i = Benutzername.length(); i > 0; i--)
	{
		if (Benutzername[i] == '*' || Benutzername[i] == ' ')
		{
			Benutzername = Benutzername.substr(0, Benutzername.size() - 1);
		}
	}
	fstream f;
	ofstream ff;
	string line;
	vector<string>lines, lines2, lines3;
	vector<string>::iterator l, ll;
	f.open("Highscore.txt");
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	f.close();
	if (lines.size() < 5)
	{
		ff.open("Highscore.txt");
		ff << "Leicht:\n\nMittel:\n\nSchwer:\n\n";
		ff.close();
		lines.clear();
		f.open("Highscore.txt");
		while (getline(f, line))
		{
			lines.push_back(line);
		}
		f.close();
	}
	if (Schwierigkeit == 1)
	{
		l = find(lines.begin(), lines.end(), "Leicht:");
		ll = find(lines.begin(), lines.end(), "Mittel:");
	}
	else if (Schwierigkeit == 2)
	{
		l = find(lines.begin(), lines.end(), "Mittel:");
		ll = find(lines.begin(), lines.end(), "Schwer:");
	}
	else if (Schwierigkeit == 3)
	{
		l = find(lines.begin(), lines.end(), "Schwer:");
		ll = lines.end();
	}
	for (int i = lines.size() - 1; i > ll - lines.begin(); i--)
	{
		lines2.push_back(lines[i]);
		lines.pop_back();
	}
	if (Schwierigkeit != 3)
	{
		lines2.push_back(lines[ll - lines.begin()]);
		lines.pop_back();
	}
	for (int i = l - lines.begin(); i >= 0; i--)
	{
		lines3.push_back(lines[i]);
		lines.erase(i + lines.begin());
	}
	bool einfügen = false;
	for (int i = 0; i < lines.size(); i++)
	{
		if (lines[i].length() == 0)
		{
			lines.erase(i + lines.begin());
			continue;
		}
		line = lines[i].substr(lines[i].find("(") + 1, lines[i].find(")") - 1);
		if (stoi(line) < wave)
		{
			lines.insert(i + lines.begin(), Benutzername + "(" + to_string(wave) + ")");
			einfügen = true;
			break;
		}
		if (i == 19)
		{
			einfügen = true;
			break;
		}
	}
	if (einfügen == false)
	{
		lines.insert(0 + lines.end(), Benutzername + "(" + to_string(wave) + ")");
	}
	for (int i = 0; i < lines3.size(); i++)
	{
		lines.insert(0 + lines.begin(), lines3[i]);
	}
	for (int i = lines2.size() - 1; i >= 0; i--)
	{
		lines.insert(lines.end(), lines2[i]);
	}
	ff.open("Highscore.txt");
	for (int i = 0; i < lines.size(); i++)
	{
		ff << lines[i] << endl;
	}
}
//öffnet die Optionen --noch nicht inplementiert
void Options(int mode, Spieler &Player, bool ranked)
{
Optionen:
	fstream f;
	ofstream ff;
	string line;
	vector<string>lines;
	if (mode == 1)
	{
		system("cls");
		if (Player.getBenutzername().length() == 0)
		{
			gotoxy(0, 0); cout << "login"; gotoxy(10, 0); cout << "register";
		}
		else
		{
			gotoxy(0, 0); cout << Player.getBenutzername();
		}
		gotoxy(30, 5); cout << "Speichern";
		gotoxy(30, 7); cout << "Speichern und Beenden";
		gotoxy(30, 9); cout << "Neues Spiel Starten";
		gotoxy(30, 11); cout << "Einstellungen";
		gotoxy(30, 13); cout << "Zur\201ck zum Spiel";
		while (true)
		{
			POINT p; //variable für mausklick
			HWND hWndConsole;
			hWndConsole = GetConsoleWindow();
			GetCursorPos(&p); //mausposition in relation zum Bildschirm beziehen
			ScreenToClient(hWndConsole, &p); //mausposition auf console beziehen
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				if (((int)(p.x / 9.65 + 0.5) >= 30 && (int)(p.x / 9.65 + 0.5) <= 38) && (int)(p.y / 13 + 0.5) == 5)
				{
					Player.changeSave(1);
					return;
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 30 && (int)(p.x / 9.65 + 0.5) <= 50) && (int)(p.y / 13 + 0.5) == 7)
				{
					Player.changeSave(2);
					return;
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 30 && (int)(p.x / 9.65 + 0.5) <= 48) && (int)(p.y / 13 + 0.5) == 9)
				{
					Player.changeSave(3);
					return;
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 0 && (int)(p.x / 9.65 + 0.5) <= 4) && (int)(p.y / 13 + 0.5) == 0 && Player.getBenutzername().length() == 0)
				{
					login("", "", Player);
					goto Optionen;
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 10 && (int)(p.x / 9.65 + 0.5) <= 17) && (int)(p.y / 13 + 0.5) == 0 && Player.getBenutzername().length() == 0)
				{
					Register(Player);
					goto Optionen;
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 30 && (int)(p.x / 9.65 + 0.5) <= 42) && (int)(p.y / 13 + 0.5) == 11)
				{
					break;
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 30 && (int)(p.x / 9.65 + 0.5) <= 46) && (int)(p.y / 13 + 0.5) == 13)
				{
					return;
				}
			}
		}
	}
	f.open("Options.txt");
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	f.close();
	if (lines.size() < 2)
	{
		ff.open("Options.txt");
		ff << "0\n0\n0\n2\n0\n0\n";
		ff.close();
		lines.clear();
		f.open("Options.txt");
		while (getline(f, line))
		{
			lines.push_back(line);
		}
		f.close();
	}
	system("cls");
	setconsolecolor(4, 7 * mode);
	if ((stoi(lines[3]) == 1 && mode == 0) || (mode == 1 && Player.getSchwierigkeit() == 1))
		setconsolecolor(2, 7 * mode);
	gotoxy(25, 5); cout << "[Leicht]";
	setconsolecolor(4, 7 * mode);
	if ((stoi(lines[3]) == 2 && mode == 0) || (mode == 1 && Player.getSchwierigkeit() == 2))
		setconsolecolor(2, 7 * mode);
	gotoxy(38, 5); cout << "[Mittel]";
	setconsolecolor(4, 7 * mode);
	if ((stoi(lines[3]) == 3 && mode == 0) || (mode == 1 && Player.getSchwierigkeit() == 3))
		setconsolecolor(2, 7 * mode);
	gotoxy(51, 5); cout << "[Schwer]";
	setconsolecolor(15, 0);
	for (int i = 0; i < 4; i++)
	{
		if ((i == 3 ? stoi(lines[4]) : stoi(lines[i])) == 0)
		{
			setconsolecolor(4, 0);
			gotoxy(35, 2 * i + 8); cout << "[YES]";
			setconsolecolor(2, 0);
			gotoxy(41, 2 * i + 8); cout << "[NO]";
		}
		else
		{
			setconsolecolor(2, 0);
			gotoxy(35, 2 * i + 8); cout << "[YES]";
			setconsolecolor(4, 0);
			gotoxy(41, 2 * i + 8); cout << "[NO]";
		}
	}
	if (stoi(lines[5]) == 0 && mode == 0)
	{
		setconsolecolor(4, 0);
		gotoxy(35, 16); cout << "[YES]";
		setconsolecolor(2, 0);
		gotoxy(41, 16); cout << "[NO]";
	}
	else if (mode == 0 || (mode == 1 && ranked == 1))
	{
		setconsolecolor(2, 0);
		gotoxy(35, 16); cout << "[YES]";
		setconsolecolor(4, 0);
		gotoxy(41, 16); cout << "[NO]";
	}
	else if (mode == 1 && ranked == 0)
	{
		setconsolecolor(4, 7);
		gotoxy(35, 16); cout << "[YES]";
		setconsolecolor(2, 0);
		gotoxy(41, 16); cout << "[NO]";
	}
	setconsolecolor(15, 0);
	gotoxy(5, 5); cout << "Schwierigkeit:";
	gotoxy(5, 8); cout << "Instant Bauen:";
	gotoxy(5, 10); cout << "Instant Upgrade:";
	gotoxy(5, 12); cout << "Maus fangen:";
	gotoxy(5, 14); cout << "Autocollect Bananas:";
	gotoxy(5, 15); cout << "(-20 % value)";
	gotoxy(5, 16); cout << "Ranked:";
	gotoxy(30, 20); cout << "Zur\201ck zum spiel";
	bool runter = false;
	while (true)
	{
		POINT p; //variable für mausklick
		HWND hWndConsole;
		hWndConsole = GetConsoleWindow();
		GetCursorPos(&p); //mausposition in relation zum Bildschirm beziehen
		ScreenToClient(hWndConsole, &p); //mausposition auf console beziehen
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (runter == true)
			{
				if (((int)(p.x / 9.65 + 0.5) >= 26 && (int)(p.x / 9.65 + 0.5) <= 31) && (int)(p.y / 13 + 0.5) == 5 && mode == 0)
				{
					setconsolecolor(2, 0); gotoxy(25, 5); cout << "[Leicht]";
					setconsolecolor(4, 0); gotoxy(38, 5); cout << "[Mittel]"; gotoxy(51, 5); cout << "[Schwer]";
					lines[3] = "1";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 39 && (int)(p.x / 9.65 + 0.5) <= 44) && (int)(p.y / 13 + 0.5) == 5 && mode == 0)
				{
					setconsolecolor(2, 0); gotoxy(38, 5); cout << "[Mittel]";
					setconsolecolor(4, 0); gotoxy(25, 5); cout << "[Leicht]"; gotoxy(51, 5); cout << "[Schwer]";
					lines[3] = "2";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 52 && (int)(p.x / 9.65 + 0.5) <= 57) && (int)(p.y / 13 + 0.5) == 5 && mode == 0)
				{
					setconsolecolor(2, 0); gotoxy(51, 5); cout << "[Schwer]";
					setconsolecolor(4, 0); gotoxy(38, 5); cout << "[Mittel]"; gotoxy(25, 5); cout << "[Leicht]";
					lines[3] = "3";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 36 && (int)(p.x / 9.65 + 0.5) <= 38) && (int)(p.y / 13 + 0.5) == 8) //Instant Bauen true
				{
					lines[0] = "1";
					setconsolecolor(2, 0); gotoxy(35, 8); cout << "[YES]"; setconsolecolor(4, 0); gotoxy(41, 8); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 42 && (int)(p.x / 9.65 + 0.5) <= 43) && (int)(p.y / 13 + 0.5) == 8) //instant Bauen false
				{
					lines[0] = "0";
					setconsolecolor(4, 0); gotoxy(35, 8); cout << "[YES]"; setconsolecolor(2, 0); gotoxy(41, 8); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 36 && (int)(p.x / 9.65 + 0.5) <= 38) && (int)(p.y / 13 + 0.5) == 10) //Instant Upgrade true
				{
					lines[1] = "1";
					setconsolecolor(2, 0); gotoxy(35, 10); cout << "[YES]"; setconsolecolor(4, 0); gotoxy(41, 10); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 42 && (int)(p.x / 9.65 + 0.5) <= 43) && (int)(p.y / 13 + 0.5) == 10) //Instant Upgrade false
				{
					lines[1] = "0";
					setconsolecolor(4, 0); gotoxy(35, 10); cout << "[YES]"; setconsolecolor(2, 0); gotoxy(41, 10); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 36 && (int)(p.x / 9.65 + 0.5) <= 38) && (int)(p.y / 13 + 0.5) == 12) //Maus fangen true
				{
					lines[2] = "1";
					setconsolecolor(2, 0); gotoxy(35, 12); cout << "[YES]"; setconsolecolor(4, 0); gotoxy(41, 12); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 42 && (int)(p.x / 9.65 + 0.5) <= 43) && (int)(p.y / 13 + 0.5) == 12) //Maus fangen false
				{
					lines[2] = "0";
					setconsolecolor(4, 0); gotoxy(35, 12); cout << "[YES]"; setconsolecolor(2, 0); gotoxy(41, 12); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 36 && (int)(p.x / 9.65 + 0.5) <= 38) && (int)(p.y / 13 + 0.5) == 14) //Autocollect Bananas true
				{
					lines[4] = "1";
					setconsolecolor(2, 0); gotoxy(35, 14); cout << "[YES]"; setconsolecolor(4, 0); gotoxy(41, 14); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 42 && (int)(p.x / 9.65 + 0.5) <= 43) && (int)(p.y / 13 + 0.5) == 14) //Autocollect Bananas false
				{
					lines[4] = "0";
					setconsolecolor(4, 0); gotoxy(35, 14); cout << "[YES]"; setconsolecolor(2, 0); gotoxy(41, 14); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 36 && (int)(p.x / 9.65 + 0.5) <= 38) && (int)(p.y / 13 + 0.5) == 16 && mode == 0) //Ranked true
				{
					lines[5] = "1";
					setconsolecolor(2, 0); gotoxy(35, 16); cout << "[YES]"; setconsolecolor(4, 0); gotoxy(41, 16); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 42 && (int)(p.x / 9.65 + 0.5) <= 43) && (int)(p.y / 13 + 0.5) == 16) //Ranked false
				{
					lines[5] = "0";
					setconsolecolor(4, 7 * mode); gotoxy(35, 16); cout << "[YES]"; setconsolecolor(2, 0); gotoxy(41, 16); cout << "[NO]";
				}
				else if (((int)(p.x / 9.65 + 0.5) >= 30 && (int)(p.x / 9.65 + 0.5) <= 45) && (int)(p.y / 13 + 0.5) == 20) //zurück zum spiel
				{
					if (mode == 0)
						Player.setSchwierigkeit(stoi(lines[3]));
					setconsolecolor(15, 0);
					ff.open("Options.txt");
					for (int i = 0; i < lines.size(); i++)
					{
						ff << lines[i] << endl;
					}
					ff.close();
					return;
				}
			}
			runter = false;
		}
		else
			runter = true;
	}
}
//Lässt alle Türme schießen sofern eine Runde aktiv ist, ein Gegner in ihrer Reichweite ist und die ladezeit um ist
void Schuss(vector<tower>&Türme, vector<Enemys>&Gegner, Spieler &Player, float Speed, int &sek, int bauen, int cost, vector<string>Wand, vector<Banana>&Bananas, bool showdamage)
{
	for (int i = 0; i < Türme.size(); i++) //für jeden turm
	{
		if (Türme[i].gettype() != 4 && Türme[i].gettype() != 6 && Türme[i].gettype() != 7) //Turm 4 ist immer aktiv darum kein check notwendig
		{
			if (Türme[i].checkShot(sek, Speed) == false) //checke ob er schießen kann so wie gegner check ob wieder laufen darf
				continue;
			if (Gegner.size() == 0)
				break;
			if (bauen != -1 && i == bauen)
			{
				Türme[i].notBuild();
			}
		}
		if (Türme[i].gettype() == 8) //Turm Typ 8 läd Schockwelle auf
		{
			tower::adddamages(Türme[i].getDmg());
			Türme[i].shot();
			continue;
		}
		for (int j = Gegner.size() - 1; j >= 0; j--) // für jeden gegner mit dem vordersten beginnend
		{
			if (Gegner[j].canMove() == false)
				break;
			if ((sqrt(pow(Türme[i].getX() - Gegner[j].getX(), 2) + pow(Türme[i].getY() - Gegner[j].getY(), 2)) <= Türme[i].getRange() && Gegner[j].canMove() == true) && (Türme[i].getCamoo() == true || Gegner[j].getCamoo() == false) || Türme[i].gettype() == 6) //wenn der gegner in reichweite ist, der turm schießen darf und der gegner bereits losgelaufen ist und der Turm Camoo sehen kann wenn der gegner Camoo ist
			{
				if (Türme[i].gettype() == 4) //nur turm 4 kann slowen
				{
					Gegner[j].Slow(); //slow den gegner für 4 schritte
				}
				if (Türme[i].gettype() == 6)
				{
					if ((j <= Enemys::getMax() - ((Enemys::getMax()) / Türme[i].getSpeed() * Türme[i].getCount()) || j == 0) && Türme[i].getCount() <= Türme[i].getSpeed() && i != bauen)
					{
						string test;
						int cost = 0, test2 = 1, test3[2] = { 0,0 };
						if (Gegner[0].canMove() == true)
						{
							test2 = Türme[i].getSpeed() - Türme[i].getCount() + 1;
						}
						for (int o = 0; o < test2; o++)
						{
							srand(clock());
							int x = rand() % (2 * (int)Türme[i].getRange()) + (Türme[i].getX() - (int)Türme[i].getRange());
							int y = rand() % (2 * (int)Türme[i].getRange()) + (Türme[i].getY() - (int)Türme[i].getRange());
							if (isValid(Türme, Wand, x, y, cost, 10, test3, Player, test3, test, NULL, NULL, 0) == true && sqrt(pow(Türme[i].getX() - x, 2) + pow(Türme[i].getY() - y, 2)) <= Türme[i].getRange() && x > 0 && x < 80 && y > 0 && y < 25)
							{
								Türme[i].improveCount();
								gotoxy(x, y);  cout << "z";
								Bananas.push_back({ x, y, Türme[i].getDmg() });
							}
							else
							{
								o--;
								continue;
							}
						}
					}
				}
				if (Türme[i].gettype() != 4 && Türme[i].gettype() != 6 && Türme[i].gettype() != 7) //Turmart 4 = slow tower, macht kein schaden und ist immer aktiv
				{
					if (Gegner[j].getDmg(Türme[i].getDmg()) == true) //wenn der Gegner nach dem schuss tot ist
					{
						if (Türme[i].getBonus() == false)
							Player.addGold(Gegner[j].getGold()); // füge gold hinzu
						else
							Player.addGold(Gegner[j].getGold() * 1.1);
						Türme[i].improvekills();
						gotoxy(63, 3); cout << "           "; //lösche und aktualiesiere die gold anzeige
						gotoxy(63, 3); cout << "Gold: " << Player.getGold() << " (" << cost << ")";
						gotoxy(Gegner[j].getX(), Gegner[j].getY()); cout << " "; // lösche das Gegner zeichen
						Gegner.erase(Gegner.begin() + j); //lösche Gegner aus vector
					}
					if (Türme[i].gettype() != 4 && Türme[i].gettype() != 3)
					{
						Türme[i].shot(); //turm hat geschossen setze inaktiv
						break; //breche Gegner loop ab
					}
				}
			}
		}
		if (Türme[i].gettype() == 3 && Türme[i].isActive() == true)
			Türme[i].shot();
	}
	if (showdamage == true)
	{
		gotoxy(0, 0); cout << tower::getdamages();
	}
}
//Alle Gegner die ihre Wartezeit überschritten haben laufen
void laufen(vector<Enemys>&Gegner, vector<string>Wand, Spieler &Player, int &sek, float Speed)
{
	for (int i = Gegner.size() - 1; i >= 0; i--) //für jeden gegner
	{
		sek = clock(); //lese zeit ein -- jetzt wichtig!!!
		if (sek - Gegner[i].getsek() < (1000 * (Gegner[i].isSlowed() == true ? 3 - Gegner[i].getCamoo() : 1) / Gegner[i].getSpeed()) / Speed) //wenn zeit - zeitpunkt an dem der gegner zuletzt gelaufen ist kleiner als seine geschwindigkeit
			continue; //mache gleich mit nächsten gegner weiter
		gotoxy(Gegner[i].getX(), Gegner[i].getY()); cout << " "; //ansonsten lösche seine jetzige position
		if (Gegner[i].setRichtung(Wand) == true) //setzte die Richtung in welche der Gegner laufen wird und checke ob der gegner die base erreicht hat
		{
			Player.LoseHP(); //Spieler verliert ein leben
			gotoxy(5, 4); cout << "  "; //aktualisiere lebensanzeige
			gotoxy(5, 4); cout << Player.getHP();
			Gegner.erase(Gegner.begin() + i); //lösche gegner
			continue; //mache sofort mit nächsten gegner weiter
		}
		if (i == Gegner.size() - 1) //wenn gegner vorderster gegner
		{
			Gegner[i].move(Gegner[i], true); //führe move durch 
		}
		else //wenn nicht der vorderste gegner
			if (Gegner[i].move(Gegner[i + 1], false) == false) //füre move durch falls der vordere bereits 2 felder entfernt ansonsten breche die loop ab
				break;
		gotoxy(Gegner[i].getX(), Gegner[i].getY()); setconsolecolor(15 - 9 * Gegner[i].getCamoo(), 0); cout << "o"; setconsolecolor(15, 0); //zeichne die neue position vom Gegner
		if (i != Gegner.size() - 1) //falls der Gegner nicht der vorderste ist
		{
			if (Gegner[i].getX() == Gegner[i + 1].getX() && Gegner[i].getY() == Gegner[i + 1].getY() && Gegner[i].getSpeed() > Gegner[i + 1].getSpeed()) //wenn der Gegner auf dem Feld seines vordermanns landet und er auch schneller ist
			{
				swap(Gegner[i], Gegner[i + 1]); // tausche die position mit ihm
			}
		}
	}
}
//checke ob der mauszeiger auf einer banane liegt
bool onBanana(vector<Banana>&Bananas, Spieler &Player, int x, int y, float Speed, int option)
{
	for (int i = 0; i < Bananas.size(); i++)
	{
		if (Bananas[i].getTime() + 10000 / Speed < clock())
		{
			if (option == 0)
			{
				gotoxy(Bananas[i].getX(), Bananas[i].getY()); cout << " ";
				Bananas.erase(Bananas.begin() + i);
				return false;
			}
			else
			{
				Player.addGold(0.8 * Bananas[i].getMoney());
				gotoxy(Bananas[i].getX(), Bananas[i].getY()); cout << " ";
				Bananas.erase(Bananas.begin() + i);
				return true;
			}
		}
		else if (Bananas[i].getX() == x && Bananas[i].getY() == y && option == 0)
		{
			Player.addGold(Bananas[i].getMoney());
			gotoxy(Bananas[i].getX(), Bananas[i].getY()); cout << " ";
			Bananas.erase(Bananas.begin() + i);
			return true;
		}
	}
	return false;
}
//setzt den zähler der Bananenfarmen zurück, damit diese in der nächsten runde wieder droppen
void resetFarm(vector<tower>&Türme)
{
	for (int i = 0; i < Türme.size(); i++)
	{
		if (Türme[i].gettype() == 6)
		{
			Türme[i].resetCount();
		}
	}
}
//neuzeichnen der Turmauswahl wenn etwas geändert wird
void Mausdruckzeichnen(int zahl, string info)
{
	if (zahl <= 3)
	{
		gotoxy(64, 11); cout << "           ";
		gotoxy(64, 12); cout << "           ";
	}
	else
	{
		gotoxy(64, 7); cout << "           ";
		gotoxy(64, 8); cout << "           ";
	}
	if (zahl == 1 || zahl == 4)
	{
		gotoxy(64, 6 + (int)(1.25*zahl)); cout << "^           ";
		gotoxy(64, 7 + (int)(1.25*zahl)); cout << "|           ";
	}
	else if (zahl == 2 || zahl == 5)
	{
		gotoxy(64, 5 + (int)(1.25*zahl)); cout << "     ^      ";
		gotoxy(64, 6 + (int)(1.25*zahl)); cout << "     |      ";
	}
	else if (zahl == 3 || zahl == 6)
	{
		gotoxy(64, 4 + (int)(1.25*zahl)); cout << "          ^";
		gotoxy(64, 5 + (int)(1.25*zahl)); cout << "          |";
	}
	gotoxy(63, 14); cout << "                ";
	gotoxy(63, 14); cout << info;
}
//Alles was mit einem Mausdruck zu tun hat
void mausdruck(int &bauen, int &art, int focus[], Spieler &Player, int autospeicher[], int &wave, int &cost, vector<tower>&Türme, int &PX, int &PY, int &Page, char &zeichen, string &info, float &Speed, bool &durchlauf, vector<Banana>&Bananas, vector<Enemys>&Gegner, vector<string>Wand, int Upgrade[], POINT &p, vector<string>Options)
{
	static bool runter;
	float value = 1;
	if (Player.getSchwierigkeit() == 1)
		value = 0.8;
	else if (Player.getSchwierigkeit() == 3)
		value = 1.2;
	if (runter == true) // wenn die maustaste vorher nicht gedrückt wurde -- vermeiden von ungewollten ausführungen dadurch, dass man nach jedem klick auch wieder runter von der maus muss
	{
		if (bauen >= 0 && GetAsyncKeyState(VK_LBUTTON) && (int)(p.x / 9.65 + 0.5) == PX && (int)(p.y / 13 + 0.5) == PY && Player.getGold() >= cost && PX > 0 && PX < 79 && PY > 0 && PY < 24) //wenn zweiter klick auf gleiche x und y position vom ersten und genügend gold vorhanden
		{
			if (art == 6 && tower::getAnzahl() > 3)
			{
				bauen = focus[0] = -1; //setze bauen zurück
				gotoxy(PX, PY); cout << " "; //lösche das zeichen wieder
				Türme.pop_back();
			}
			else
			{
				bauen = -1;  Player.addGold(-cost); //ziehe gold ab und setze bauen zurück
				PX = PY = -1;
				if (Player.isActive() == false)
				{
					autospeicher[0] = -1;
					autospeicher[1] = cost;
					autospeicher[2] = wave;
				}
			}
		}
		else if (bauen >= 0 && GetAsyncKeyState(VK_LBUTTON) && ((int)(p.x / 9.65 + 0.5) != PX || (int)(p.y / 13 + 0.5) != PY || Player.getGold() < cost)) //wenn zweiter klick nicht an selber stelle oder nicht genug gold vorhanden
		{
			bauen = focus[0] = -1; //setze bauen zurück
			gotoxy(PX, PY); cout << " "; //lösche das zeichen wieder
			tower::backAnzahl();
			Türme.pop_back();
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && (int)(p.x / 9.65 + 0.5) == 64 && (int)(p.y / 13 + 0.5) == 6) //wenn [T] ausgewählt
		{
			if (Page == 0)
			{
				zeichen = 'T'; //setze zeichen, art und markiere [T]
				art = 1, cost = 75 * value;
				info = "100 / 3 / 10";
			}
			else
			{
				zeichen = 'X'; //setze zeichen, art und markiere [X]
				art = 6, cost = 800 * value;
				info = "17 / 3 / 5";
			}
			Mausdruckzeichnen(1, info);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && (int)(p.x / 9.65 + 0.5) == 69 && (int)(p.y / 13 + 0.5) == 6) //wenn [B] ausgewählt
		{
			if (Page == 0)
			{
				zeichen = 'B'; //setze zeichen, art und markiere [B]
				art = 2, cost = 100 * value;
				info = "200 / 1 / 100";
			}
			else
			{
				zeichen = 'Y'; //setze zeichen, art und markiere [Y]
				art = 7, cost = 1000 * value;
				info = "0 / 0 / 6";
			}
			Mausdruckzeichnen(2, info);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && (int)(p.x / 9.65 + 0.5) == 74 && (int)(p.y / 13 + 0.5) == 6) //wenn [U] ausgewählt
		{
			if (Page == 0)
			{
				zeichen = 'U'; //setze zeichen, art und markiere [U]
				art = 3, cost = 100 * value;
				info = "2 / 25 / 6";
			}
			else
			{
				zeichen = 'P'; //setze zeichen, art und markiere [P]
				art = 8, cost = 300 * value;
				info = "8 / 10 / 0";
			}
			Mausdruckzeichnen(3, info);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && (int)(p.x / 9.65 + 0.5) == 64 && (int)(p.y / 13 + 0.5) == 10) //wenn [ ] ausgewählt
		{
			zeichen = NULL; //auswahl um türme Upzugraden
			art = 0, cost = 0, focus[0] = -1;
			info = "";
			Mausdruckzeichnen(4, info);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && (int)(p.x / 9.65 + 0.5) == 69 && (int)(p.y / 13 + 0.5) == 10) //wenn [H] ausgewählt
		{
			if (Page == 0)
			{
				zeichen = 'H'; //setze zeichen, art und markiere [H]
				art = 4, cost = 100 * value;
				info = "-- / " + to_string(INFINITY) + " / 10";
			}
			else
			{
				zeichen = '$'; //setze zeichen, art und markiere [$]
				art = -1, cost = NULL, focus[0] = -1;
				info = "";
			}
			Mausdruckzeichnen(5, info);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && (int)(p.x / 9.65 + 0.5) == 74 && (int)(p.y / 13 + 0.5) == 10) //wenn [I] ausgewählt
		{
			if (Page == 0)
			{
				zeichen = 'I'; //setze zeichen, art und markiere [I]
				art = 5, cost = 175 * value;
				info = "10 / 50 / 15";
			}
			else
			{
				zeichen = '#';
				art = -2; cost = NULL; focus[0] = -1;
				info = "";
			}
			Mausdruckzeichnen(6, info);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && ((int)(p.x / 9.65 + 0.5) == 61 || (int)(p.x / 9.65 + 0.5) == 62) && (int)(p.y / 13 + 0.5) == 22) //wenn [>>] angeklickt
		{
			if (Speed != 2)
			{
				Speed = 2;
				setconsolecolor(4, 0);
				gotoxy(60, 24); cout << "[<<]";
				setconsolecolor(2, 0);
			}
			else
			{
				Speed = 1;
				setconsolecolor(4, 0);
			}
			gotoxy(60, 22); cout << "[>>]";
			setconsolecolor(15, 0);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && ((int)(p.x / 9.65 + 0.5) == 61 || (int)(p.x / 9.65 + 0.5) == 62) && (int)(p.y / 13 + 0.5) == 24) //wenn [<<] angeklickt
		{
			if (Speed != 0.5)
			{
				Speed = 0.5;
				setconsolecolor(4, 0);
				gotoxy(60, 22); cout << "[>>]";
				setconsolecolor(2, 0);
			}
			else
			{
				Speed = 1;
				setconsolecolor(4, 0);
			}
			gotoxy(60, 24); cout << "[<<]";
			setconsolecolor(15, 0);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && ((int)(p.x / 9.65 + 0.5) == 65 || (int)(p.x / 9.65 + 0.5) == 66) && (int)(p.y / 13 + 0.5) == 23) //wenn [||] angeklickt
		{
			Player.changePause();
			if (Player.getPause() == true)
				setconsolecolor(2, 0);
			else
				setconsolecolor(4, 0);
			gotoxy(64, 23); cout << "[||]";
			setconsolecolor(15, 0);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && ((int)(p.x / 9.65 + 0.5) >= 69 && (int)(p.x / 9.65 + 0.5) <= 73) && (int)(p.y / 13 + 0.5) == 22) //wenn [Start] angeklickt
		{
			if (Player.isActive() == false)
			{
				Player.changeActive();
				wave += 1;
				gotoxy(69, 1); cout << wave;
				CreateEnemys(Gegner, wave);
				redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, false);
			}
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && ((int)(p.x / 9.65 + 0.5) >= 69 && (int)(p.x / 9.65 + 0.5) <= 77) && (int)(p.y / 13 + 0.5) == 24) //wenn [Durchlauf] angeklickt
		{
			if (durchlauf == false)
			{
				durchlauf = true;
				if (Player.isActive() == false)
				{
					Player.changeActive();
					wave += 1;
					gotoxy(69, 1); cout << wave;
					CreateEnemys(Gegner, wave);
				}
				setconsolecolor(2, 0);
				gotoxy(68, 24); cout << "[Durchlauf]";
				gotoxy(68, 22); cout << "[Start]";
			}
			else
			{
				durchlauf = false;
				setconsolecolor(4, 0);
				gotoxy(68, 24); cout << "[Durchlauf]";
			}
			setconsolecolor(15, 0);
		}
		else if (GetAsyncKeyState(VK_LBUTTON) && isValid(Türme, Wand, (int)(p.x / 9.65 + 0.5), (int)(p.y / 13 + 0.5), cost, zeichen, Upgrade, Player, focus, info, autospeicher, wave, stoi(Options[1])) == true && art > 0) //wenn erster klick auf valides feld
		{
			gotoxy((int)(p.x / 9.65 + 0.5), (int)(p.y / 13 + 0.5)); cout << zeichen; //markiere feld mit turm zeichen
			PX = (int)(p.x / 9.65 + 0.5), PY = (int)(p.y / 13 + 0.5); //speichere x und y koordinate
			Türme.push_back({ art, PX, PY }); // baue den turm
			if (stoi(Options[0]) == 1 && Player.getGold() >= cost)
			{
				if (art == 6 && tower::getAnzahl() > 3)
				{
					bauen = focus[0] = -1; //setze bauen zurück
					gotoxy(PX, PY); cout << " "; //lösche das zeichen wieder
					Türme.pop_back();
				}
				else
				{
					bauen = -1; focus[0] = Türme.size() - 1;  Player.addGold(-cost); //ziehe gold ab und setze bauen zurück
					PX = PY = -1;
					if (Player.isActive() == false)
					{
						autospeicher[0] = -1;
						autospeicher[1] = cost;
						autospeicher[2] = wave;
					}
				}
			}
			else
				bauen = focus[0] = Türme.size() - 1; //setze bauen variable um nächsten klick zu checken
		}
		if (GetAsyncKeyState(VK_LBUTTON)) //wenn linke maustaste gedrückt
		{
			if (onEnemy(Gegner, (int)(p.x / 9.65 + 0.5), (int)(p.y / 13 + 0.5)) != -1)
			{
				gotoxy(0, 0); cout << "         ";
				gotoxy(0, 0); cout << "[" << Gegner[onEnemy(Gegner, (int)(p.x / 9.65 + 0.5), (int)(p.y / 13 + 0.5))].getHP() << "]";
			}
			runter = false; //speichere mausklick
			gotoxy(69, 3); cout << "            "; //lösche und aktualiesiere kosten
			gotoxy(69, 3); cout << Player.getGold() << " (" << cost << ")";
			if (focus[0] != focus[1])
			{
				redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, true);
				focus[1] = focus[0];
			}
		}
		if (runter == true && GetAsyncKeyState(VK_MBUTTON)) // wenn mittlere maustaste gedrückt
		{
			for (int i = 0; i < Türme.size(); i++) //überprüfe jeden turm
			{
				if ((int)(p.x / 9.65 + 0.5) == Türme[i].getX() && (int)(p.y / 13 + 0.5) == Türme[i].getY() && Türme[i].gettype() == 8) //wenn maus auf einen Turm und dieser Turm vom Typ 8 ist
				{
					gotoxy(0, 0); cout << "         ";
					for (int j = Gegner.size() - 1; j >= 0; j--) // für jeden gegner mit dem vordersten beginnend
					{
						if (Gegner[j].getHP() <= tower::getdamages())
						{
							tower::adddamages(-Gegner[j].getHP());
							Player.addGold(Gegner[j].getGold()); // füge gold hinzu
							gotoxy(63, 3); cout << "           "; //lösche und aktualiesiere die gold anzeige
							gotoxy(63, 3); cout << "Gold: " << Player.getGold() << " (" << cost << ")";
							gotoxy(Gegner[j].getX(), Gegner[j].getY()); cout << " "; // lösche das Gegner zeichen
							Gegner.erase(Gegner.begin() + j); //lösche Gegner aus vector
						}
						else
						{
							Gegner[j].getDmg(tower::getdamages());
							tower::adddamages(-tower::getdamages());
						}
					}
				}
			}
			runter = false;
			if (Page == 0)
				Page = 1;
			else
				Page = 0;
			redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, false);
		}
	}
	if (!GetAsyncKeyState(VK_LBUTTON) && !GetAsyncKeyState(VK_MBUTTON)) //wenn keine maustaste gedrückt
	{
		runter = true; //speichere das kein mausklick gemacht wurde
	}
	if (stoi(Options[2]) == 1)
	{
		bool change = false;
		HWND hWndConsole;
		hWndConsole = GetConsoleWindow();
		if (p.x < 0)
		{
			p.x = 0;
			change = true;
		}
		if (p.y < 0)
		{
			p.y = 0;
			change = true;
		}
		if (p.x > 640)
		{
			p.x = 640;
			change = true;
		}
		if (p.y > 305)
		{
			p.y = 305;
			change = true;
		}
		if (change == true)
		{
			ClientToScreen(hWndConsole, &p);
			SetCursorPos(p.x, p.y);
		}
	}
}
//Hauptprogramm
int main(int argc, char* argv[])
{
neustart:
	CreateTXT();
	setconsolecolor(15, 0);
	INPUT_RECORD inRec;
	HANDLE hcon = GetStdHandle(STD_INPUT_HANDLE); //variablen um den mausklick zu erkennen
	int x = 52, y = 5, wave = 0, Page = 0, bauen = -1, focus[2] = { -1, -1 };  //initialiesiert die x und y werte für die auswahl 
	int autospeicher[3] = { -2, 0, 0 };
	int Upgrade[2] = { 0,-1 }; //doppelklick notwendig um turm zu bauen/Upgraden ->bauen/Upgrade // check ob maustaste gedrückt oder gedrückt gehalten wird
	int PX, PY, art = 0, cost = 0; //variable um x und y koordinate beim drücken zu speichern, art des turms und kosten um den turm zu bauen
	bool durchlauf = false, ranked = false, showdamage = false;
	string info = "100 / 3 / 10";;
	float Speed = 1;
	Spieler Player;
	vector<tower> Türme;
	vector<Enemys>Gegner;
	vector<string>Wand;
	vector<Banana>Bananas;
	vector<float>ÜG;
start:
	system("cls");
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	if (Player.getBenutzername().length() > 0)
	{
		gotoxy(0, 0); cout << Player.getBenutzername();
	}
	else
	{
		gotoxy(0, 0); cout << "login";
		gotoxy(10, 0); cout << "register";
	}
	gotoxy(40, 5); cout << "Neues Spiel";
	gotoxy(40, 7); cout << "Spiel Laden";
	gotoxy(40, 9); cout << "Highscore";
	gotoxy(40, 11); cout << "Options";
	gotoxy(x, y); cout << "<-";
	bool leave = false;
	while (leave == false) //solange nicht enter gedrückt wurde
	{
		POINT p; //variable für mausklick
		HWND hWndConsole;
		hWndConsole = GetConsoleWindow();
		GetCursorPos(&p); //mausposition in relation zum Bildschirm beziehen
		ScreenToClient(hWndConsole, &p); //mausposition auf console beziehen
		if (_kbhit()) //auswahl
		{
			char c = _getch();
			switch (c)
			{
			case 'w':
			case 'W': if (y > 5) { gotoxy(x, y); cout << "  "; y -= 2; gotoxy(x, y); cout << "<-"; }
					  break;
			case 's':
			case 'S': if (y < 11) { gotoxy(x, y); cout << "  "; y += 2; gotoxy(x, y); cout << "<-"; }
					  break;
			case 13: leave = true;
				break;
			case 'r':
			case 'R': Register(Player); goto start;
				break;
			case 'l':
			case 'L': login("", "", Player); goto start;
			}
		}
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if ((int)(p.x / 9.65 + 0.5) >= 0 && (int)(p.x / 9.65 + 0.5) <= 4 && (int)(p.y / 13 + 0.5) == 0 && Player.getBenutzername().length() == 0)
			{
				login("", "", Player); goto start;
			}
			else if ((int)(p.x / 9.65 + 0.5) >= 10 && (int)(p.x / 9.65 + 0.5) <= 17 && (int)(p.y / 13 + 0.5) == 0 && Player.getBenutzername().length() == 0)
			{
				Register(Player); goto start;
			}
			else if ((int)(p.x / 9.65 + 0.5) >= 40 && (int)(p.x / 9.65 + 0.5) <= 50 && (int)(p.y / 13 + 0.5) == 7)
			{
				y = 7; break;
			}
			else if ((int)(p.x / 9.65 + 0.5) >= 40 && (int)(p.x / 9.65 + 0.5) <= 50 && (int)(p.y / 13 + 0.5) == 5)
			{
				y = 5; break;
			}
			else if ((int)(p.x / 9.65 + 0.5) >= 40 && (int)(p.x / 9.65 + 0.5) <= 48 && (int)(p.y / 13 + 0.5) == 9)
			{
				y = 9; break;
			}
			else if ((int)(p.x / 9.65 + 0.5) >= 40 && (int)(p.x / 9.65 + 0.5) <= 46 && (int)(p.y / 13 + 0.5) == 11)
			{
				y = 11; break;
			}
		}
	}
	if (y == 7) //wenn kein neues Spiel gestartet wird Load/Score oder Options ausführen
	{
		if (Load(ÜG, Bananas, Gegner, Türme, Player) == 0)
			goto start;
		wave = ÜG[0]; ranked = ÜG[1], Page = ÜG[2], focus[0] = ÜG[3], focus[1] = ÜG[4]; autospeicher[0] = ÜG[5]; autospeicher[1] = ÜG[6]; autospeicher[2] = ÜG[7]; Speed = ÜG[8]; bauen = ÜG[9]; Upgrade[0] = ÜG[10]; Upgrade[1] = ÜG[11]; art = ÜG[12]; cost = ÜG[13];
	}
	else if (y == 9)
		Score();
	else if (y == 11)
		Options(0, Player, ranked);
	if (y >= 9 && y <= 11)
		goto start;
	fstream f;
	string line;
	vector<string>lines;
	f.open("Options.txt");
	while (getline(f, line))
	{
		lines.push_back(line);
	}
	if (y == 5)
	{
		Player.setSchwierigkeit(stoi(lines[3]));
		ranked = stoi(lines[5]);
	}
	f.close();
	CreateWall(Wand); //die Wände werden eingelesen
	system("cls");
	if (y == 5)
	{
		if (Player.getSchwierigkeit() == 1)
		{
			Player.getHP(10);
		}
		else if (Player.getSchwierigkeit() == 3)
		{
			Player.getHP(-10);
		}
	}
	redraw(wave, 0, Player, Türme, focus[0], 0, Speed, durchlauf, info, Page, Bananas, Gegner, true);
	char zeichen = NULL; //Zeichen für die Türme wenn welche gebaut werden
	while (Player.isAlive()) //solange der Spieler noch lebt
	{
		int sek1 = clock(); //zeit einlesen, nicht wichtig, nur für check wie lange ein durchlauf dauert
		POINT p; //variable für mausklick
		HWND hWndConsole;
		hWndConsole = GetConsoleWindow();
		GetCursorPos(&p); //mausposition in relation zum Bildschirm beziehen
		ScreenToClient(hWndConsole, &p); //mausposition auf console beziehen
		if (onBanana(Bananas, Player, (int)(p.x / 9.65 + 0.5), (int)(p.y / 13 + 0.5), Speed, stoi(lines[4])) == true)
		{
			//redraw(wave, cost, Player, Türme, -1, art, Speed, durchlauf, info, Page, Bananas, Gegner);
		}
		mausdruck(bauen, art, focus, Player, autospeicher, wave, cost, Türme, PX, PY, Page, zeichen, info, Speed, durchlauf, Bananas, Gegner, Wand, Upgrade, p, lines);
		int sek = clock(); //speichere zeit --eigentlich unnötige zeile
		if (_kbhit()) //wenn die tastatur gedrückt wird
		{
			char c = _getch(); //speichere eingabe
			switch (c) //auswahl je nach eingabe
			{
			case 13: if (Player.isActive() == false) { Player.changeActive(); wave += 1; gotoxy(69, 1); cout << wave; CreateEnemys(Gegner, wave); } //wenn enter gedrückt und keine runde aktiv, erstelle gegner, erhöhe wave, aktiviere runde, 
					 break;
			case 'M':
			case 'K': if (Page == 0) Page = 1; else Page = 0; redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, false); //redraw im falle von visual bugs
				break;
			case 's':
			case 'S': redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, false); //redraw im falle von visual bugs
				break;
			case '^':
			case '°': redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, true); //redraw im falle von visual bugs
				break;
				break;
			case 'x': if (focus[0] != -2 && Player.isActive() == false) focus[0] = -2; else focus[0] = -1; redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, false);
				break;
			case 'b': if (autospeicher[0] == -1 && autospeicher[2] == wave) { Player.addGold(autospeicher[1]); gotoxy(Türme[Türme.size() - 1].getX(), Türme[Türme.size() - 1].getY()); cout << " "; Türme.pop_back(); autospeicher[0] = -2; autospeicher[1] = 0; autospeicher[2] = 0; redraw(wave, cost, Player, Türme, -1, art, Speed, durchlauf, info, Page, Bananas, Gegner, false); }
					  else if (autospeicher[0] >= 0 && autospeicher[2] == wave) { Player.addGold(autospeicher[1]); gotoxy(Türme[autospeicher[0]].getX(), Türme[autospeicher[0]].getY()); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Türme[autospeicher[0]].getLvl() == 1 ? 15 : Türme[autospeicher[0]].getLvl() == 2 ? 9 : 4); cout << Türme[autospeicher[0]].drawtype(); Türme[autospeicher[0]].Downgrade(); autospeicher[0] = -2; autospeicher[1] = 0; autospeicher[2] = 0; redraw(wave, cost, Player, Türme, -1, art, Speed, durchlauf, info, Page, Bananas, Gegner, false); }
					  break;
			case 27: Options(1, Player, ranked); redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, false);
				ÜG.clear(); ÜG.push_back(wave); ÜG.push_back(ranked); ÜG.push_back(Page); ÜG.push_back(focus[0]); ÜG.push_back(focus[1]); ÜG.push_back(autospeicher[0]); ÜG.push_back(autospeicher[1]); ÜG.push_back(autospeicher[2]); ÜG.push_back(Speed); ÜG.push_back(bauen); ÜG.push_back(Upgrade[0]); ÜG.push_back(Upgrade[1]);
				ÜG.push_back(art); ÜG.push_back(cost); ÜG.push_back(Player.getGold()); ÜG.push_back(Player.getHP());  ÜG.push_back(Player.getSchwierigkeit());  ÜG.push_back(Player.isActive()); for (int i = 0; i < Bananas.size(); i++) { ÜG.push_back(Bananas[i].getX()); ÜG.push_back(Bananas[i].getY()); ÜG.push_back(Bananas[i].getMoney()); }
				for (int i = 0; i < Gegner.size(); i++) { ÜG.push_back(Gegner[i].getHP());  ÜG.push_back(Gegner[i].getGold());   ÜG.push_back(Gegner[i].getX());   ÜG.push_back(Gegner[i].getY());   ÜG.push_back(Gegner[i].getRichtung());   ÜG.push_back(Gegner[i].getSpeed()); ÜG.push_back(Gegner[i].isSlowed()); ÜG.push_back(Gegner[i].getType()); ÜG.push_back(Gegner[i].canMove()); ÜG.push_back(Gegner[i].getCamoo()); ÜG.push_back(Gegner[i].getRegen()); }
				for (int i = 0; i < Türme.size(); i++) { ÜG.push_back(Türme[i].getX()); ÜG.push_back(Türme[i].getY()); ÜG.push_back(Türme[i].gettype()); ÜG.push_back(Türme[i].getLvl()); ÜG.push_back(Türme[i].getCount()); ÜG.push_back(Türme[i].getCamoo()); ÜG.push_back(Türme[i].getRanges()); ÜG.push_back(Türme[i].getBoost()); }
				if (Save(Player, ÜG, Bananas.size(), Gegner.size(), Türme.size(), ranked) == 1) {
					wave = 0; Player.addGold(-Player.getGold() + 500); Player.getHP(-Player.getHP() + 40 - 10 * Player.getSchwierigkeit()); for (int i = Türme.size() - 1; i >= 0; i--) Türme.pop_back(); for (int i = Bananas.size() - 1; i >= 0; i--) Bananas.pop_back(); for (int i = Gegner.size() - 1; i >= 0; i--) Gegner.pop_back();
					if (Player.isActive() == true) Player.changeActive(); durchlauf = false; focus[0] = -1; focus[1] = -1; autospeicher[0] = -2; autospeicher[1] = 0; autospeicher[2] = 0; Speed = 1; redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, true);
					if (Player.getPause() == true) Player.changePause();
				}
				lines.clear();
				f.open("Options.txt");
				while (getline(f, line))
				{
					lines.push_back(line);
				}
				f.close();
				Player.changeSave(0);
				redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, true);
				break;
			case 'p': Player.changePause(); if (Player.getPause() == true) setconsolecolor(2, 0); else setconsolecolor(4, 0); gotoxy(64, 23); cout << "[||]";
				break;
			case 'd': if (showdamage == false) showdamage = true; else showdamage = false;
			}
		}

		if (Player.isActive() == true && Gegner.size() > 0 && Player.getPause() == false) //wenn runde aktiv und noch gegner vorhanden
		{
			laufen(Gegner, Wand, Player, sek, Speed);
			Schuss(Türme, Gegner, Player, Speed, sek, bauen, cost, Wand, Bananas, showdamage);
		}
		else if (Player.isActive() == true && Gegner.size() == 0) //wenn die Runde aktiv ist aber kein Gegner mehr lebt
		{
			for (int i = 0; i < Türme.size(); i++)
			{
				if (Türme[i].getBoost() == true)
				{
					Türme[i].changeBoost();
				}
			}
			resetFarm(Türme);
			if (durchlauf == false)
			{
				Player.changeActive(); //beende die runde
				redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, false);
			}
			else
			{
				wave += 1;
				gotoxy(69, 1); cout << wave;
				CreateEnemys(Gegner, wave);
				redraw(wave, cost, Player, Türme, focus[0], art, Speed, durchlauf, info, Page, Bananas, Gegner, false);
			}
			tower::adddamages(-0.1 * tower::getdamages());
		}
		int sek2 = clock(); //zweite zeit variable für check wie lange ein durchgang dauer
		gotoxy(2, 2); cout << "    ";
		gotoxy(2, 2); cout << sek2 - sek1;
		//if (sek1 + 20 > sek2)
		//	Sleep(20 - (sek2 - sek1));
	}
	if (ranked == true)
	{
		if (Player.getBenutzername().length() > 0)
		{
			highscore(wave, Player.getSchwierigkeit(), Player.getBenutzername());
		}
		else
		{
			system("cls");
			gotoxy(0, 10); cout << "Sie sind nicht angemeldet, sollten Sie dies nicht tun wird ihr Score nicht gespeichert!";
			gotoxy(30, 12); cout << "[login]"; gotoxy(40, 12); cout << "[register]";
			while (true)
			{
				POINT p; //variable für mausklick
				HWND hWndConsole;
				hWndConsole = GetConsoleWindow();
				GetCursorPos(&p); //mausposition in relation zum Bildschirm beziehen
				ScreenToClient(hWndConsole, &p); //mausposition auf console beziehen
				if (GetAsyncKeyState(VK_LBUTTON))
				{
					if (((int)(p.x / 9.65 + 0.5) >= 31 && (int)(p.x / 9.65 + 0.5) <= 35 && (int)(p.y / 13 + 0.5) == 12))
					{
						login("", "", Player); break;
					}
					else if (((int)(p.x / 9.65 + 0.5) >= 41 && (int)(p.x / 9.65 + 0.5) <= 48 && (int)(p.y / 13 + 0.5) == 12))
					{
						Register(Player); break;
					}
				}
			}
			highscore(wave, Player.getSchwierigkeit(), Player.getBenutzername());
		}
	}
	goto neustart;
}