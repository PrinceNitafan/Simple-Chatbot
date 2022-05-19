#include "error.h"    
#include "Chatbot.h"       
#include <iostream>        
#include <fstream>       
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime>     
#include <cassert>


/////////////////////////////////////////////////////////////////////////////////////////
// Most of my code tries to catch phrases or certain words to which the bot will react to, 
// hence the there is a large usage of .find() == string::npos. 
// Also, a method I thought up to use was creating two vectors that would intersect in a way 
// in which if that certain phrase/word triggers the .find() within the first vector, the 
// second vector would have a reply in the same spot as the trigger phrase/word in the first
// vector.
// And, if a question triggered a phrase/word in the first vector, I made it so that the next
// time the same question or something similar is inputted by the user, the bot would reply 
// that it already answered that question by replacing the second vector's index.
/////////////////////////////////////////////////////////////////////////////////////////

class User_bot: public Chatbot {
    string reply;
public:

    User_bot(const string& name) : Chatbot(name) {}
    
    void give_msg(const string&) {
    }

    string get_msg() {
        cout << "User: ";
        getline(cin, reply);
        return reply;
    }
};

class Simple_bot : public Chatbot {
    int counter = 0; // regulates when to ask marvel topic 
    int mode = 0; // helps regulate what topic to continue
    int key = 0; // helps stop code from looking for agree/disagree answers

    string in_msg = "";
    string reply = "Hi there, how are you?";

    // replies if bot doesn't understand the user input
    vector<string> dont_know = {"I'm not sure what to say", "Don't know what to say", 
    "I don't know", "I can't say", "I don't know what to say", "I'm not sure", 
    "Can't say much about it"}; 
    
    // vectors that hold replies for msgs that include words from what_phrase
    vector<string> what_phrase = {"up", "weather", "date", "time", "name", "food", "you"};
    vector<string> what_reply = {"Nothing much", 
    "I don't know about the weather today. Maybe it's sunny", "I'm not sure about the date",
    "I'm not sure of the time currently. Don't have a watch",
    "My name is " + get_name(), "My favourite food is the spaghetti", "It's been fine"};

    // vectors that hold replies for msgs that include words from i_phrase
    vector<string> i_phrase = {"know", "say", "colour", "think", "like"};
    vector<string> i_reply = {"Okay", "Alright then.", "That's nice", 
    "I'm not sure what to think about that", "I like you too"};

    // vectors that hold replies for msgs that include words from do_phrase
    vector<string> do_phrase = {"time", "date", "name", "games", "weather", "colour"};
    vector<string> do_reply = {"I'm not sure what the time is", 
    "Don't know the date right now", "My name is " + get_name(), "I like to play games",
    "I don't know the weather currently", "My favourite colour is green"};

    // vector holds replies for greetings
    vector<string> greet = {"how are you", "how about you", "anything good" , "meet you",
    "good morning", "good afternoon", "good evening", "hello", "good", "ok", "fine", "decent", 
    "alright", "not bad", "how's it been", "hows it been"};
    vector<string> greet_rep = {"I'm good, thank you for asking", "It's been fine", 
    "Nothing much really", "Nice to meet you too", "Good morning", "Good afternoon", 
    "Good evening", "Well hello again", "That's good", "That's ok", "That's fine", 
    "Alright", "That's not bad", "Ok, that's good", "It's been ok", "It's been ok"};

    // vectors that hold replies for msgs that include words from like_fav
    vector<string> like_fav = {"colour", "food", "hero", "heroes", "movie", "tv", "show", "who", 
    "character", "movies", "you", "yours"};
    vector<string> like_fav_rep = {"My favourite colour is green",
    "My favourite food is spaghetti", 
    "My favourtite hero is Dr.Strange", 
    "My favourite group is the Avengers", 
    "One of my favourite movies is the Dr.Strange movie", 
    "I don't really have a favourite tv show", 
    "No show comes up to mind", 
    "The Hulk is one of my favourite heroes.", "I like Iron Man, he has amazing tech", 
    "I like the Avengers movie.", "What about me?", "What about mine?"};

    vector<string> game_fav = {"character", "hero", "game", "console", "pc", "nintendo", "PS5",
    "Playstation", "xbox", "you", "yours"};
    vector<string> game_rep = {"The Doom Slayer is my favourite", 
    "I like Noble 6, he was a great hero", "My favourite game is Black Ops 2", 
    "I play on Xbox, it provides great services", 
    "I play on PC and the platforms gives me great freedom", 
    "Nintendo games are quite fun IMO", "Unfortunately, I don't have a PS5", 
    "Unforutnately, I don't have a playstation, though I do want one.", 
    "I have an Xbox, and it is pretty good", "What about me?", "What about mine?"};

    // vector that holds potential answers to check from the user
    vector<string> agree_ans = {"yes", "sure", "fine", "why not", "okay", "yeah"};
    vector<string> disagree_ans = {"no", "nah", "not really", "no thanks", "nada", "nope"};

    // vector with sentences for replying to questions already asked
    vector<string> again = {"You already asked that", "You asked that before", 
    "I already answered that", "I've answered that already"};

    // vector with sentences for the bot to say they have already said that.
    vector<string> said = {"I think I already said that", "I've already said that", 
    "I think already told you"};

    // vector with replies if the user don't like or like something
    vector<string> dont = {"Oh, that's fine", "Alright then", "Okay", "that's fine"};
    vector<string> lik = {"That's nice", "Great!", "Awsome", "nice"};

    // Topics that the bot will try go through in order
    vector<string> topic = {". Anyways, do you like the Marvel universe?", 
    ". Say, do you want to talk about something else, like games?"};

    // replies if they say something like nice
    vector<string> ni = {"nice", "good", "awesome", "amazing"};

public:

    Simple_bot(const string& name) : 
    Chatbot(name) {}

    // gives a random reply
    void rand_rep() {
        int siz = dont_know.size();
        int random = rand()%siz;
        reply = dont_know[random];
    }

    // gets a reply for msgs with "what"
    void what_func(const string& new_msg) {
        for (int i = 0; i < what_phrase.size(); i++) {
            if (new_msg.find(what_phrase[i]) != string::npos) {
                reply = what_reply[i];

                // changes the previous answers of the questions asked
                int siz = again.size();
                int random = rand()%siz;
                what_reply[i] = again[random];
                break;
            } else {
                rand_rep();
            }
        }
    }

    // gets a reply for msgs with "i" or "i'm"
    void i_func(const string& new_msg) {
        for (int i = 0; i < i_phrase.size(); i++) {
            if (new_msg.find(i_phrase[i]) != string::npos) {
                reply = i_reply[i];

                // changes the previous answers of the questions asked
                int siz = again.size();
                int random = rand()%siz;
                i_reply[i] = again[random];
                break;
            } else {
                rand_rep();
            }
        }
    }

    // gets a reply for msgs with "do"
    void do_func(const string& new_msg) {
        for (int i = 0; i < do_phrase.size(); i++) {
            if (new_msg.find(do_phrase[i]) != string::npos) {
                reply = do_reply[i];

                // changes the previous answers of the questions asked
                int siz = again.size();
                int random = rand()%siz;
                do_reply[i] = again[random];
                break;
            } else {
                rand_rep();
            }
        }
    }

    // checks for a greeting
    bool greeting(const string& new_msg) { 
        for (int i = 0; i < greet.size(); i++) {
            if (new_msg.find(greet[i]) != string::npos) {
                reply = greet_rep[i];

                int siz = again.size();
                int random = rand()%siz;
                greet_rep[i] = again[random];
                
                return true;
            } else {
                rand_rep();
            }
        }
        return false;
    }

    // checks for agreeing or disagreeing answers from user
    void agree_dis() {
        // checks for answer to change topic to marvel universe  
        if (mode == 1 && key == 0) {
            for (int i = 0; i < agree_ans.size(); i++) {
                if(in_msg.find(agree_ans[i]) != string::npos) {
                    key = 1; // if yes, the key == 1 to allow responses for marvel topic
                    reply = "Okay, which hero do you like?";
                    break;
                } else if (in_msg.find(disagree_ans[i]) != string::npos){
                    mode = 2; // if answer is no, then the mode == 2
                    key = 1; // and key == 1 so the bot asks the next topic quesiton
                    reply = "That's fine. Do you wanna talk about games?";
                    break;
                } else if (mode == 1 && key == 0) {
                    rand_rep();
                }
            }
        // checks for answer to change topic to game  
        } else if (mode == 2 && key == 1) {
            for (int i = 0; i < agree_ans.size(); i++) {
                if(in_msg.find(agree_ans[i]) != string::npos) {
                    key = 2; // if yes, the key == 2 to allow responses for game topic
                    reply = "Okay, what is your favourite game?";
                    break;
                } else if (in_msg.find(disagree_ans[i]) != string::npos){
                    mode = 0; // if the ansnwer is no, then it returns mode to 0
                    key = 0; // and the key to 0
                    reply = "Alright";
                    break;
                } else if (mode == 2 && key == 1) {
                    rand_rep();
                }   
            } 
        } else {
            rand_rep();
        }
    } 

    // changes the reply based on the topic of marvel
    void marvel_topic(const string& new_msg) {
        // checks if the user says they don't like something
        if (new_msg.find("don't") != string::npos|| new_msg.find("dont") != string::npos ||
        new_msg.find("not sure") != string::npos) {

            // gives a rand reply that if they say dont like to something.
            int siz = dont.size();
            int random = rand()%siz;
            reply = dont[random] + ". ";
            counter++;

            // The bot tells what it likes despite the user's dislike
            for (int i = 0; i < like_fav.size(); i++) {
                if (new_msg.find(like_fav[i]) != string::npos) {
                    reply += like_fav_rep[i];

                    // if the bot replies with this, then if asked about
                    // this topic, it will tell the user it already said it.
                    int si = said.size();
                    int ran = rand()%si;
                    like_fav_rep[i] = said[ran];
                    break;
                }
            }
        // checks if the user says they like something
        } else if ((new_msg.find("i ") != string::npos || 
        new_msg.find("my") != string::npos) && (new_msg.find("like") != string::npos || 
        new_msg.find("favourite") != string::npos || new_msg.find("love") || 
        new_msg.find("adore") != string::npos)) {

            int siz = lik.size();
            int random = rand()%siz;
            reply = lik[random] + ". ";
            counter++;

            // checks if the user asks a question after their answer
            if (new_msg.find("?") != string::npos || new_msg.find("who") != string::npos || 
            new_msg.find("what") != string::npos|| new_msg.find("which") != string::npos ||
            new_msg.find("about") != string::npos) {
                for (int i = 0; i < like_fav.size(); i++) {
                    if (new_msg.find(like_fav[i]) != string::npos) {
                        reply += like_fav_rep[i];

                        int sizes = again.size();
                        int rando = rand()%sizes;
                        like_fav_rep[i] = again[rando];
                        break;
                    }
                }
            }
        // This checks if the user asked a question
        } else if ((new_msg.find("do") != string::npos || new_msg.find("what") || 
        new_msg.find("which") != string::npos) && (new_msg.find("you") != string::npos || 
        new_msg.find("?") != string::npos || new_msg.find("about") != string::npos || 
        new_msg.find("your") != string::npos|| new_msg.find("yours") != string::npos)) {
            for (int i = 0; i < like_fav.size(); i++) {
                if (new_msg.find(like_fav[i]) != string::npos) {
                    reply = like_fav_rep[i];

                    int sizes = again.size();
                    int rando = rand()%sizes;
                    like_fav_rep[i] = again[rando];
                    counter++;
                    break;
                }
            } 
        } else {
            for (int i = 0; i < ni.size(); i++) {
                if (new_msg.find(ni[i]) != string::npos) {
                    reply = "Thank you";
                    counter++;
                    break;
                } else {
                    rand_rep();
                    counter++;
                }
            }
        }
    };

    // changes the reply based on the topic of games
    void game_topic(const string& new_msg) {
        // checks if the user says they don't like something
        if (new_msg.find("don't") != string::npos|| new_msg.find("dont") != string::npos ||
        new_msg.find("not sure") != string::npos) {

            // gives a rand reply that if they say dont like to something.
            int siz = dont.size();
            int random = rand()%siz;
            reply = dont[random] + ". ";
            counter++;

            // The bot tells what it likes despite the user's dislike
            for (int i = 0; i < game_fav.size(); i++) {
                if (new_msg.find(game_fav[i]) != string::npos) {
                    reply += game_rep[i];

                    // if the bot replies with this, then if asked about
                    // this topic, it will tell the user it already said it.
                    int si = said.size();
                    int ran = rand()%si;
                    like_fav_rep[i] = said[ran]; 
                    break;
                }
            }

        // checks if the user says they like something
        } else if ((new_msg.find("i ") != string::npos || 
        new_msg.find("my") != string::npos) && (new_msg.find("like") != string::npos || 
        new_msg.find("favourite") != string::npos || new_msg.find("love") || 
        new_msg.find("adore") != string::npos)) {

            int siz = lik.size();
            int random = rand()%siz;
            reply = lik[random] + ". ";
            counter++;

            // checks if the user asks a question after their answer
            if (new_msg.find("?") != string::npos || new_msg.find("who") != string::npos || 
            new_msg.find("what") != string::npos|| new_msg.find("which") != string::npos ||
            new_msg.find("about") != string::npos) {
                for (int i = 0; i < game_fav.size(); i++) {
                    if (new_msg.find(game_fav[i]) != string::npos) {
                        reply += game_rep[i];

                        int sizes = again.size();
                        int rando = rand()%sizes;
                        game_rep[i] = again[rando];
                        break;
                    }
                }
            }
        // This checks if the user asked a question
        } else if ((new_msg.find("do") != string::npos || new_msg.find("what") || 
        new_msg.find("which") != string::npos) && (new_msg.find("you") != string::npos || 
        new_msg.find("?") != string::npos || new_msg.find("about") != string::npos || 
        new_msg.find("your") != string::npos || new_msg.find("yours") != string::npos)) {
            for (int i = 0; i < game_fav.size(); i++) {
                if (new_msg.find(game_fav[i]) != string::npos) {
                    reply = game_rep[i];

                    int sizes = again.size();
                    int rando = rand()%sizes;
                    game_rep[i] = again[rando];
                    counter++;
                    break;
                }
            }
        } else {
            for (int i = 0; i < ni.size(); i++) {
                if (new_msg.find(ni[i]) != string::npos) {
                    reply = "Thank you";
                    counter++;
                    break;
                } else {
                    rand_rep();
                    counter++;
                }
            }
        }
    };

    void give_msg(const string& msg) {
       
        in_msg = msg;

//https://thispointer.com/converting-a-string-to-upper-lower-case-in-c-using-stl-boost-library/
        // used link above to learn lowercasing strings.
        for_each(in_msg.begin(), in_msg.end(), [](char& c) {
            c = tolower(c);
        });

        // this checks for the answer to the topic question
        if ((mode == 1 && key == 0) || (mode == 2 && key == 1)) {
            agree_dis();

        // check mode for marvel topic
        } else if (mode == 1 && key == 1) {
            marvel_topic(in_msg);

            // check mode for game topic
        } else if (mode == 2 && key == 2) {
            game_topic(in_msg);

        } else if (mode == 0) {
            // checks for phrases with "what"
            if (in_msg.find("what") != string::npos) {
                what_func(in_msg);
                counter++;

            // checks for phrases with "i"
            } else if (in_msg.find("i'm") != string::npos || 
            in_msg.find("i ") != string::npos) {
                i_func(in_msg);
                counter++;

            // checks phrases with "do"
            } else if (in_msg.find("do") != string::npos) {
                do_func(in_msg);
                counter++;

            // checks for a greeting
            } else if (greeting(in_msg)) {
                counter++;

            } else { // if none of the previous passed, a random reply is generated.
                rand_rep();
                counter++;
            }

        }

    }

    string get_msg() {
        // this checks for mode and counter to see if bot should ask about Marvel topics.
        if (counter >= 4 && mode == 0) {
            reply += topic[0];
            topic[0] = "";
            mode = 1;
        }

        // this checks for mode and counter to see if bot should ask about game topics.
        if (counter >= 9 && mode == 1) {
            reply += topic[1];
            topic[1] = "";
            mode = 2;
            key = 1;
        }
        
        return reply;
    }
};