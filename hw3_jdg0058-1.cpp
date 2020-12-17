//Jacob Galanopoulos
//JDG0058
//hw3_jdg0058.cpp
//The program calculates who shall win the duel
//I received help from Alexis Merrick and Eric LaPorte in understanding the requirements of the project.

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

const int AARON_SHOT(33);
const int BOB_SHOT(50);
const int CHARLIE_SHOT(100);
const double TEST_DUELS(10000);

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
void run_strategies(bool strat1, bool A_alive, bool B_alive, bool C_alive);

int main() {
	srand(time(0));
	bool A_alive = true, B_alive = true, C_alive = true;

	cout << "*** Welcome to the Duel Simulator ***" << endl;
	cout << "Unit Testing 1: Function -at_least_two_alive()" << endl;
	cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive" << endl;
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed ..." << endl;
	cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive" << endl;
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed ..." << endl;
	cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive" << endl;
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed ..." << endl;
	cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead" << endl;
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed ..." << endl;
	cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive" << endl;
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed ..." << endl;
	cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead" << endl;
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed ..." << endl;
	cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead" << endl;
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed ..." << endl;
	cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead" << endl;
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed ..." << endl;
	cout << "Press Enter to continue...";
	cin.get();

	cout << "Ready to test strategy 1 (run " << TEST_DUELS << " times):" << endl;
	cout << "Press Enter to continue...";
	cin.get();
	run_strategies(true, A_alive, B_alive, C_alive);
	
	cout << "Ready to test strategy 2 (run " << TEST_DUELS << " times):" << endl;
	cout << "Press Enter to continue...";
	cin.get();
	run_strategies(false, A_alive, B_alive, C_alive);
	cout << "Strategy 2 is better than strategy 1." << endl;
}

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
	return ((A_alive && B_alive) || (B_alive && C_alive) || (A_alive && C_alive));
}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
	int shoot_target_result;
	shoot_target_result = rand() % 100;
	if (C_alive) {
		if (shoot_target_result < AARON_SHOT) {
			C_alive = false;
		}
	}
	else if (B_alive) {
		if (shoot_target_result < AARON_SHOT) {
			B_alive = false;
		}
	}
}

void Bob_shoots(bool& A_alive, bool& C_alive) {
	int shoot_target_result;
	shoot_target_result = rand() % 100;
	if (C_alive) {
		if (shoot_target_result < BOB_SHOT) {
			C_alive = false;
		}
	}
	else if (A_alive) {
		if (shoot_target_result < BOB_SHOT) {
			A_alive = false;
		}
	}
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {
	int shoot_target_result;
	shoot_target_result = rand() % 100;
	if (B_alive) {
		if (shoot_target_result <= CHARLIE_SHOT) {
			B_alive = false;
		}
	}
	else if (A_alive) {
		if (shoot_target_result <= CHARLIE_SHOT) {
			A_alive = false;
		}
	}
}

void Aaron_shoots2(bool& B_alive, bool& C_alive) {
	if (!(B_alive && C_alive)) {
		int shoot_target_result;
		shoot_target_result = rand() % 100;
		if (C_alive) {
			if (shoot_target_result < AARON_SHOT) {
				C_alive = false;
			}
		}
		else if (B_alive) {
			if (shoot_target_result < AARON_SHOT) {
				B_alive = false;
			}
		}
	}
}

void run_strategies(bool strat1, bool A_alive, bool B_alive, bool C_alive) {
	int xcount = 0;
	double awins = 0, bwins = 0, cwins = 0;
	while (xcount < TEST_DUELS) {
		A_alive = true, B_alive = true, C_alive = true;
		while (at_least_two_alive(A_alive, B_alive, C_alive)) {
			if (A_alive) {
				if (strat1) {
					Aaron_shoots1(B_alive, C_alive);
				}
				else {
					Aaron_shoots2(B_alive, C_alive);
				}
			}
			if (B_alive) {
				Bob_shoots(A_alive, C_alive);
			}
			if (C_alive) {
				Charlie_shoots(A_alive, B_alive);
			}
		}
		if (A_alive) {
			awins++;
		}
		else if (B_alive) {
			bwins++;
		}
		else if (C_alive) {
			cwins++;
		}
		xcount++;
	}
	cout << "Aaron won " << awins << "/" << TEST_DUELS << " duels or " << awins / TEST_DUELS << "%" << endl;
	cout << "Bob won " << bwins << "/" << TEST_DUELS << " duels or " << bwins / TEST_DUELS << "%" << endl;
	cout << "Charlie won " << cwins << "/" << TEST_DUELS << " duels or " << cwins / TEST_DUELS << "%\n" << endl;
}