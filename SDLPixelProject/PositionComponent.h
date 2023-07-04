#pragma once
#include "Components.h"

class PositionComponent : public Component
{
public:
	int x() { return xPos; };
	int y() { return yPos; };

	void Init() override
	{
		xPos = 0;
		yPos = 0;
	}

	void Update() override
	{
		xPos++;
		yPos++;
	}

	void setPos(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

private:
	int xPos;
	int yPos;
};