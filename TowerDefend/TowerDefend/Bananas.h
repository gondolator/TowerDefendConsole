#pragma once
class Banana
{
private:
	int x, y, money, time;
public:
	Banana(int X, int Y, int Gold)
	{
		x = X, y = Y, money = Gold;
		time = clock();
	}
	int getMoney()
	{
		return money;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	int getTime()
	{
		return time;
	}
};