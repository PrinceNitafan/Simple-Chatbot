#include "Simplebot.h"

using namespace std;

// converse function allows the user to ineract with the smart bot
void converse(Chatbot* a, Chatbot* b, int max_turns = 50) {
  for(int turn = 1; turn <= max_turns; turn++) {
    string a_msg = a->get_msg();
    cout << "(" << turn << ") " << a->get_name() << ": " << a_msg << "\n";
    
    turn++;
    if (turn > max_turns) return;

    b->give_msg(a_msg);
    string b_msg = b->get_msg();

    cout << "(" << turn << ") " << b->get_name() << ": " << b_msg << "\n";
    a->give_msg(b_msg);
  } // for
}

int main() {
    User_bot user("User");
    Simple_bot simple_bot("Alan");

    cout << "Simple_bot start\n" << endl;
    converse(&simple_bot, &user, 31);
    cout << "\n" << endl;
    cout << "Simple_bot done\n" << endl;

}
