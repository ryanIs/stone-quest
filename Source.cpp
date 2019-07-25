#include "stdlib.h"
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;

// Variable definition
char userName[64];
int health, healthM, XP, strength, luck;
int eHealth, eHealthM, eStrength, eLuck, eLevel = 0, eTurn = 0;
int chests;
bool playerDead = false;

// Function declaration
int random(int);
int round(double);
int getDamage(int);

void mainAction(int input);
void initiateStats();
void promptAction();
void battle(int &l);

bool doesCrit(int, int);

// Function definition
int main(int argc, const char* argv[]) {
	srand((time(NULL)));
	system("title Stone Quest");
	cout << "Welcome to Stone Quest!" << endl;
	//cout << "Please enter your username: ";
	//cin >> userName;
	initiateStats();
	mainAction(0);
	while(!playerDead) {
		promptAction();
	}
	cout << endl;
	system("title Stone Quest: Game Over");
	cout << "Your stone quest has come to an end!" << endl;
	cout << "This simulation is over. Press any key to exit the program." << endl;
	system("pause >nul");
	return 0;
}

void promptAction() {
	int _input;
	system("cls");
	system("title Stone Quest - Location: Town");
	cout << "What would you like to do?" << endl;
	cout << "0) View stats" << endl;
	cout << "1) Train Health" << endl;
	cout << "2) Train Strength" << endl;
	cout << "3) Train Luck" << endl;
	cout << "4) Use Chest" << endl;
	cout << "5) Battle!" << endl;
	cout << "6) Quit game." << endl;
	cin >> _input;
	mainAction(_input);
	return;
}

void initiateStats() {
	XP = random(11);
	health = healthM = 10 + random(10);
	strength = 3 + random(13);
	luck = 1 + random(10);
	return;
}

void mainAction(int input) {
	if(input == 0) { // Display stats.
		system("cls");
		system("title Stone Quest - Stat Display");
		cout << "-- Your stats --" << endl;
		cout << "XP remaining: " << XP << endl;
		cout << "Health points: " << healthM << endl;
		cout << "Strength points: " << strength << endl;
		cout << "Luck points: " << luck << endl;
		system("pause");
	} else if(input == 1) { // Train HP
		system("cls");
		system("title Stone Quest - Training health");
		if(XP > 0) {
			XP -= 1;
			health = ++healthM;
			cout << "You have successfully trained health! Health is now: " << healthM << endl;
		} else {
			cout << "You do not have enough XP." << endl;
		}
		system("pause");
	} else if(input == 2) { // Train strength
		system("cls");
		system("title Stone Quest - Training strength");
		if(XP > 0) {
			XP -= 1;
			strength++;
			cout << "You have successfully trained strength! Strength is now: " << strength << endl;
		} else {
			cout << "You do not have enough XP." << endl;
		}
		system("pause");
	} else if(input == 3) { // Train strength
		system("cls");
		system("title Stone Quest - Training luck");
		if(XP > 0) {
			XP -= 1;
			luck++;
			cout << "You have successfully trained luck! Luck is now: " << luck << endl;
		} else {
			cout << "You do not have enough XP." << endl;
		}
		system("pause");
	} else if(input == 4) { // Use chest
		system("cls");
		system("title Stone Quest - Chest");
		if(chests > 0) {
			// do chests
		} else {
			cout << "You don't have any chests." << endl;
		}
		system("pause");
	} else if(input == 5) { // Engage Battle
		battle(eLevel);
	} else if(input == 6 || input == 3435973836) { // End game.
		playerDead = true;
	} else {
		cout << endl << "Unregonized command: " << input << endl; //cout << (unsigned int)-858993460 << endl; // -858993460 is 3435973836 and occurs when i input a char
		system("pause");
	}
	return;
}

void battle(int &lv) {
	++lv;
	short victor = 0; // 0 undecided, 1 player, 2 enemy
	int damage = 0, XPLoot = 1, XPGain = 0, turns = 0, crits = 0, dmgDealt = 0, _guess = 0;
	bool _c = false;

	eHealthM = 4 + lv;
	eHealthM += random(lv);
	eHealthM += lv;
	eHealth = eHealthM;
	eStrength = 7 + (lv * 2);
	eLuck = 5 + (lv);

	system("cls");
	system("title Stone Quest - Battle: prepare");
	cout << "Welcome to the battlefield!" << endl << "Your enemy is level " << lv << endl;
	cout << "Press any key to battle!" << endl;
	system("pause >nul");

	eTurn = random(1); // 0 player turn, 1 enemy turn

	while(victor == 0) {
		system("cls");
		system("title Stone Quest - Battle: Status");
		cout << "CURENTLY IN BATTLE." << endl << endl;
		cout << "Your HP: " << health << " / " << healthM << endl << endl;
		cout << "Enemy HP: " << eHealth << " / " << eHealthM << endl << endl;
		system("pause");
		if(eHealth < 1) {
			victor = 1;
			goto endBattleWhile;
		} else if(health < 1) {
			victor = 2;
			goto endBattleWhile;
		}
		turns++;
		if(eTurn == 0) { // Player turn
			system("cls");
			system("title Stone Quest - Battle: Player Attack!");
			cout << "CURENTLY IN BATTLE." << endl << endl;
			damage = getDamage(strength);
			cout << "Guess a number between 0 and " << (120 - luck) << ": ";
			cin >> _guess;
			if(doesCrit(luck, _guess)) {
				cout << "PLAYER ATTACKS ENEMY! CRITICAL STRIKE!" << endl << endl;
				damage *= 2;
				crits++;
			} else {
				cout << "PLAYER ATTACKS ENEMY!" << endl << endl;
			}
			eHealth -= damage;
			dmgDealt += damage;
			cout << "Damage Dealt: " << damage << endl << endl;
			eTurn = 1;
			system("pause");
		} else {
			system("cls");
			system("title Stone Quest - Battle: Enemy Attack!");
			cout << "CURENTLY IN BATTLE." << endl << endl;
			damage = getDamage(eStrength);
			if(doesCrit(eLuck, 1)) {
				cout << "ENEMY ATTACKS PLAYER! CRITICAL STRIKE!" << endl << endl;
				damage *= 2;
			} else {
				cout << "ENEMY ATTACKS PLAYER!" << endl << endl;
			}
			health -= damage;
			cout << "Damage Dealt: " << damage << endl << endl;
			eTurn = 0;
			system("pause");
		}
		endBattleWhile:;
	}
	if(victor == 1) { // PLAYER VICTORY
		XPLoot += random(5);
		XPGain = 1 + floor(lv/5);
		XPGain += random(floor(lv/5));
		XPLoot += XPGain;
		XP += XPLoot;

		system("cls");
		system("title Stone Quest - Battle: Victory!");
		cout << "BATTLE WON! CONGRATULATIONS, YOU GAINED: " << XPLoot << " XP!" << endl << endl;
		if(random(110 - luck) == 0) { 
			chests += 1;
			cout << "You found a chest!" << endl << endl;
		}
		cout << "-- Battle results -- " << endl;
		cout << "Health remaining: " << health << " / " << healthM << endl;
		cout << "Damage dealt: " << dmgDealt << endl;
		cout << "Total critical strikes: " << crits << endl;
		cout << "Total turns: " << turns << endl;
		cout << "XP Gained: " << XPLoot << endl;
		system("pause");
	} else if(victor == 2) { // ENEMY VICTORY
		system("cls");
		system("title Stone Quest - Battle: Defeat!");
		cout <<  "BATTLE LOST! SORRY, YOU HAVE DIED." << endl << endl;
		cout << "Game over." << endl;
		playerDead = true;
		system("pause");
	}
	return;
}
bool doesCrit(int luc, int guess) {
	bool crts = false;
	if(random(120 - luck) < 3) {
		crts = true;
	}
	return crts;
}
int getDamage(int str) {
	int dmg = 1;
	dmg += floor(str/10);
	dmg += random(round(floor(str/5) * 1.0));
	return dmg;
}
int random(int _i) {
	return round( (static_cast<double>(rand()) / RAND_MAX) * _i );
}

int round(double _i) {
	return static_cast<int>(_i + 0.5);
}