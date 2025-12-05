

// #include <bits/stdc++.h>
#include <iostream>
using namespace std;


// ek vending machine 
// States , Vending Machine , Self, Products , 

// States - IdleState , HasMoneyState , ProductSelectState , Dispense STate , OutofStockState 
// Action - putMoney , productSelect , dispense , refill   


class VendingMachine{
    private:

    VendingState* currState;
    int itemCount;
    int itemPrice;
    int insertedCoins;

    VendingState* noCoinState;
    VendingState* hasCoinState;
    VendingState* dispenseState;
    VendingState* soldOutState;

    public:

    VendingMachine(int itemCount,int itemPrice);
    void insertCoin(int coin);
    void selectItem();
    void dispense();
    void returnCoin();
    void refill(int quantity);

    void printStatus();
};

class VendingState{
    public:

    virtual VendingState* addMoney(VendingMachine* vendingMachine,int amount)=0;
    virtual VendingState* selectItem(VendingMachine* vendingMachine)=0;
    virtual VendingState* dispense(VendingMachine* vendingMachine)=0;
    virtual VendingState* returnCoin(VendingMachine* vendingMachin)=0;
    virtual VendingState* refill(VendingMachine* vendingMachine,int amount)=0;

};

class noCoinState: public VendingState{

};

class hasCoinState: public VendingState{

};
class dispenseState: public VendingState{

};
class soldOutState: public VendingState{

};

VendingMachine::VendingMachine(int itemCount,int itemPrice){
    this->itemCount=itemCount;
    this->itemPrice=itemPrice;

    noCoinState=new noCoinState();
    hasCoinState=new hasCoinState();
    dispenseState=new dispenseState();
    soldOutState=new soldOutState();

    if(itemCount>0){
        currState=noCoinState;
    }
    else{
        currState=hasCoinState;
    }
}

void VendingMachine::insertCoin(int coin){
    currState=currState->addMoney(this,coin);
}

void VendingMachine::selectItem(){
    currState=currState->selectItem(this);
}

void VendingMachine::dispense(){
    currState=currState->dispense(this);
}

void VendingMachine::returnCoin(){
    currState=currState->returnCoin(this);
}

void VendingMachine::refill(int coin){
    currState=currState->refill(this,coin);
}


int main(){


}