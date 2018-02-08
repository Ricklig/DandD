#include "Map.h"
#include "Character.h"
#include "NPC.h"
#include "Dice.h"
#include <iostream>
#include "Combat.h"
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

bool Combat::fighting(Character& player, NPC& enemy) {

	int playerHealth = player.getHitPoints();
	int enemyHealth = enemy.getHitPoints();

	while (playerHealth != 0 && enemyHealth != 0) {

		cout << "\n----------------------\n";
		cout << "Player's health: " << playerHealth << endl;
		cout << "Enemy's health: " << enemyHealth << endl;

		char in;

		cout << "(A)ttack or (R)un" << endl;
		cout << "Player choice: ";
		cin >> in;
		cout << endl;


		auto status = ((Character*)&player)->calcStats();

		if (in == 'A' || in == 'a') {


			enemy.hit(player.getFirstAttack() + status[0]);//Strength + attBonus
			enemyHealth = enemy.getCurrentHitPoints();
			if (enemy.getCurrentHitPoints() < 0)
				cout << "enemy's Health " << 0 << endl << endl;
			else
				cout << "enemy's Health " << enemyHealth << endl << endl;

			if (enemy.getCurrentHitPoints() <= 0) {
				enemy.die();
				return true;
			}

			if (player.getSecondAttack() > 0) {
				enemy.hit(player.getSecondAttack() + status[0]);
				enemyHealth = enemy.getCurrentHitPoints();
				if (enemy.getCurrentHitPoints() < 0)
					cout << "enemy's Health " << 0 << endl << endl;
				else
					cout << "enemy's Health " << enemyHealth << endl << endl;

				if (enemy.getCurrentHitPoints() <= 0) {
					enemy.die();
					return true;
				}
			}
			if (player.getThirdAttack() > 0) {
				enemy.hit(player.getThirdAttack() + status[0]);
				enemyHealth = enemy.getCurrentHitPoints();
				if (enemy.getCurrentHitPoints() < 0)
					cout << "enemy's Health " << 0 << endl << endl;
				else
					cout << "enemy's Health " << enemyHealth << endl << endl;

				if (enemy.getCurrentHitPoints() <= 0) {
					enemy.die();
					return true;
				}
			}
			if (player.getFourthAttack() > 0) {
				enemy.hit(player.getFourthAttack() + status[0]);
				enemyHealth = enemy.getCurrentHitPoints();
				if (enemy.getCurrentHitPoints() < 0)
					cout << "enemy's Health " << 0 << endl << endl;
				else
					cout << "enemy's Health " << enemyHealth << endl << endl;

				if (enemy.getCurrentHitPoints() <= 0) {
					enemy.die();
					return true;
				}
			}

			//!enemyhit
			int enemyDmg = enemy.getAttackBonus();

			player.message = "Attack Attempted by player... Attack result: - " + to_string(enemyDmg) + " from enemy's health\n";
			player.notify(); //! notify observer that an attack has been made and write message into GameLog

			player.hit(enemyDmg);
			playerHealth = player.getCurrentHitPoints();
			cout << "Player's Health " << playerHealth << endl << endl;

			if (player.getCurrentHitPoints() <= 0) {
				cout << "You have died. Enter any key to end game" << endl;
				cin >> in;
				player.message = "Game has ended";
				player.notify();
				exit(0);
			}
		}
		if (in == 'R' || in == 'r') {
			return false;
		}
	}

}
