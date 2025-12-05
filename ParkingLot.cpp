#include <iostream>
#include <map>
using namespace std;


enum VehicleType{
    BIKE,
    TRUCK,
    CAR
};


class Vehicle{

    public:

    string licensePlate;
    VehicleType vehicleType;

    Vehicle(string licensePlate,VehicleType vehicleType){
        this->licensePlate=licensePlate;
        this->vehicleType=vehicleType;
    }
    virtual ~Vehicle()=0;
    VehicleType getVehicleType(){
        return vehicleType;
    } 
};

class Bike: public Vehicle{

    public:

    Bike(string licensePlate,VehicleType vehicleType):Vehicle(licensePlate,vehicleType){
    }
};

class Car: public Vehicle{

    public:

    Car(string licensePlate,VehicleType vehicleType):Vehicle(licensePlate,vehicleType){
    }
};

class Truck: public Vehicle{

    public:

    Truck(string licensePlate,VehicleType vehicleType):Vehicle(licensePlate,vehicleType){
    }
};


// Vehicle Creation login in Factory 

class VehicleFactory{

    public:

    Vehicle* createVehicle(string licensePlate,VehicleType vehicleType){
        switch(vehicleType){
            case VehicleType::BIKE:
               return new Bike(licensePlate,vehicleType);
            case VehicleType::CAR:
               return new Car(licensePlate,vehicleType);
            case VehicleType::TRUCK:
               return new Truck(licensePlate,vehicleType);
        }
    }
};

// New vehicle came and go through the createVehicle 

class ParkingSpot{

    public:
    VehicleType vehicleType;
    bool isOccupied=false;
    int spotNumber;

    ParkingSpot(VehicleType vehicleType,int spotNumber):vehicleType(vehicleType),spotNumber(spotNumber){
    }

    bool isOccupied(){
        return isOccupied;
    }

    void releaseSpot(){
        isOccupied=false;
    }

    void occupySpot(){
        isOccupied=true;
    }
};


class ParkingFloor{
    public:

    int floorNumber;
    map<VehicleType,vector<ParkingSpot*>>spots;


    ParkingFloor(int floorNumber,int bike,int truck,int car):floorNumber(floorNumber){

        for(int i=0;i<bike;i++){
            spots[VehicleType::BIKE].push_back(new ParkingSpot(VehicleType::BIKE,i+1));
        }
        for(int i=0;i<truck;i++){
            spots[VehicleType::TRUCK].push_back(new ParkingSpot(VehicleType::TRUCK,i+1));
        }
        for(int i=0;i<car;i++){
            spots[VehicleType::CAR].push_back(new ParkingSpot(VehicleType::CAR,i+1));
        }
    }
    // initialize all spots in this floor 

    int floorNumber(){
        return floorNumber;
    }

    ParkingSpot* findAvailableSpot(VehicleType vehicleType){

        // goes on the loop and find the spot and return it 
    }
};


class ParkingLot{

    public:

    vector<ParkingFloor*>parkingFloors;

    ParkingSpot* findAvailableSpot(VehicleType vehicleType){
        for(auto it : parkingFloors){
            ParkingSpot* parkingspot=it->findAvailableSpot(vehicleType);
            if(parkingspot){
                return parkingspot;
            }
        }
        return NULL;
    }

    // Park the vehicle got the vehicle and park it bro 

    ParkingSpot* parkVehicle(Vehicle* vehicle){
        ParkingSpot* parkingSpot=findAvailableSpot(vehicle->getVehicleType());
        if(parkingSpot!=NULL){
            parkingSpot->occupySpot();
            cout<<"SucessFully Parked the Vehicle"<<endl;
            return parkingSpot;
        }
        else{
            cout<<"No Available Spot Find"<<endl;
        }
        return NULL;
    }

    // Unpark 

    void vacateParkingSpot(int spotNumber){
        // goes to that 
        ParkingSpot* parkingSpot=findSpotByNumber(spotNumber);
        if(parkingSpot!=NULL){
            parkingSpot->releaseSpot();
        }
    }

    // get from the ticket the spotNumber spotNumber is uninuqe 

    ParkingSpot* findSpotByNumber(int spotNumber){
        return NULL;
    }

};


// Pricing and Ticket Entity 

class PriceStratergy{
    public:
    
};

class Ticket{

    public:

    int ticketId;
    Vehicle* vehicle;
    PriceStratergy* priceStatergy;
    int entryTime;
    int exitTime;

};

int main(){


}


// Requirements Gathering 

// Multiple Vehicle can ( Car , Truck , Bike)
// Multiple ParkingSports accroding to these types 
// Multiple Floors in a Parking Lot 

// Ticket at entry gate and calculate at exit side 
// Different Pricing Startgery ( Time based , Premium Based , Event Based)
// This parking Lot will have different Floors means some Method. 