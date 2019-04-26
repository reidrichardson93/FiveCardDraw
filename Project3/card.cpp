
#include "pch.h"
#include "card.h"

void card::printCard(ostream &os)
{
	static const char suitChar[] = { 'C','D','H','S' };
	static const char rankChar[] = { ' ','A','2','3','4','5','6','7','8','9','T','J','Q','K' };

	if (faceUp)
	{
		os << "| " << rankChar[rank] << " " << suitChar[suit] << " |\n";
	}
	else
	{
		os << "| # # |";
	}
}

void card::flipOver()
{
	faceUp = !faceUp;
}

