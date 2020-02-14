#include "main.h"

int main()
{
	outputMenu;
	scanf_s("%d", &opt);
	while (strchr("012345678", opt) != 0) {
		switch (opt) {
		case '1': addCard; break;
		case '2': printCard; break;
		case '3': useComputer; break;
		case '4': exitComputer; break;
		case '5': topUp; break;
		case '6': withdraw; break;
		case '7': searchAll;
		case '8': exitCard; break;
		case '0': printf("Bye!"); return 0;
		};
		outputMenu;
		scanf_s("%d", &opt);
	}
}