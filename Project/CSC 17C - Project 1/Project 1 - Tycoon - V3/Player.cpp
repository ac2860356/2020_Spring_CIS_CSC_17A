/* 
 * File:   Player.cpp
 * Author: Arthur Choy
 * Created on April 23, 2021, 12:07 AM
 */

#include <list>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Player.h"
using namespace std;

Player::Player() {
    hand = new std::list<std::pair<std::string, int>>;
    title = 3;
    emptyHand = true;
}

Player::Player(std::string n) {
    hand = new std::list<std::pair<std::string, int>>;
    title = 3;
    emptyHand = true;
    name = n;
}

Player::Player(const Player& orig) {
    hand = new std::list<std::pair<std::string, int>>;
    for(std::list<std::pair<std::string, int>>::iterator i = orig.hand->begin(); i != orig.hand->end(); i++) {
        hand->push_front(*i);
    }
    title = orig.getTitle();
    name = orig.getName();
    emptyHand = orig.empt();
}

Player::~Player() {
    delete hand;
}

void Player::dspHand() {
    for(std::list<std::pair<std::string, int>>::iterator i = hand->begin(); i != hand->end(); i++) {
        cout << setw(2) << right << (*i).first << " ";
    }
    cout << endl;
}

void Player::addHand(std::pair<std::string, int> c) {
    emptyHand = false;
    hand->push_front(c);
}

std::list<std::pair<std::string, int>> Player::playCards(string r, int a) {
    played.clear();
    int t = 0;
    bool move = true;

    for(std::list<std::pair<std::string, int>>::iterator i = hand->begin(); i != hand->end(); i++) {
        //For-loop accounting for consecutive elements
        for(int j = 0; j < 4; j++) {
            if((*i).first == r && t != a) {
                t++;
                played.push_front((*i));
                i = hand->erase(i);
            }
            if(i == hand->end()) break;
        }
    }
    cout << endl;
    if(played.empty()) throw BadPlay();
    if(hand->empty()) emptyHand = true;
    return played;
}

void Player::reject() {
    for(std::list<std::pair<std::string, int>>::iterator i = played.begin(); i != played.end(); i++) {
        hand->push_front((*i));
    }
    if(!hand->empty()) emptyHand = false;
    played.clear();
}