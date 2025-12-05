#include <iostream>
#include <map>
using namespace std;


// A system with multiple warehouses and product categories.

// • Stock level tracking and management.

// • Intelligent replenishment strategy implementation.

// • Ability to handle edge cases like damaged inventory or returns.

// Core Entities : Product,Warehouse, InventoryManager, 


// Managing COncurrent add , remove 
// Statergy for Replenishment 
// Singelton for one InventoryInstance
// factory for product creation


enum ProductCategory {
    ELECTRONICS, CLOTHING, GROCERY, FURNITURE, OTHER
};

enum InventoryOperation { 
     ADD, REMOVE, TRANSFER, ADJUST 
};


class Product {
    public:
    string sku;
    string name;
    double price;
    int quantity=0;
    int threshold;
    ProductCategory category;

    // getter and setter or use builder to create this Product 

    string getName(){
        return name;
    }

    void addStock(int quan){
        quantity+=quan;
    }

    string getSku(){
        return sku;
    }

    void decreaseStock(int quan){
        quantity=max(quantity,quantity-quan);
    }

    int getQuantity(){
        return quantity;
    }

};

// There are various product ElectronicsProduct , ClothingProduct , GroceryProduct , 


class ElectronicsProduct: public Product{
    public:

    string brand;
    int warrantyPeriod;

    ElectronicsProduct(string sku,string name,double price,int quantity,int threshold):Product(sku,name,price,quantity,threshold,ProductCategory::ELECTRONICS){
    }
};

class ClothingProduct:public Product{
    public:
    string size;
    string color;
    ClothingProduct(string sku,string name,double price,int quantity,int threshold):Product(sku,name,price,quantity,threshold,ProductCategory::ELECTRONICS){
    }

};


class ProductFactory{

    public:
    
    Product* createProduct(ProductCategory category,string sku,string name,double price,int quantity,int threshold){
        switch(category){
            case ProductCategory::ELECTRONICS:
                return new ElectronicsProduct(sku,name,price,quantity,threshold);
            case ProductCategory::CLOTHING:
                return new ClothingProduct(sku,name,price,quantity,threshold); 
        }
    }

};


class ReplenishmentStrategy{

    public:

    virtual void replenish(Product* product)=0;

};


class JustInTimeStrategy :public  ReplenishmentStrategy {
    
    public:
    void replenish(Product* product) {
        // Implement Just-In-Time replenishment logic
        cout<<("Applying Just-In-Time replenishment for " + product->getName());
        // Calculate optimal order quantity based on demand rate
    }
};

class BulkOrderStrategy :public  ReplenishmentStrategy {
    
    public:
    void replenish(Product* product) {
        // Implement JBulkOrderStrategy replenishment logic
        cout<<("Applying BulkOrderStrategy replenishment for " + product->getName());
        // Calculate optimal order quantity based on demand rate
    }
};




class WareHouse{
    private :

    int id;
    string name;
    string address;
    map<string,Product*>products;   // for each warehouse sku -> product  5 -> TV 

    void addProduct(Product* product,int quantity){

        string sku=product->getSku();
        Product* existingProduct=products[sku];
        if(!existingProduct){
            // new product 
            product->addStock(quantity);
            products[sku]=product;
        }
        else{
            existingProduct->addStock(quantity);
        }

        cout<<"Sucessfully added the product"<<endl;
    }

    void removeProduct(string sku,int quantity){
        // check the sku is avalaibale for decrease or either complete remove from the Map if quantity is 0 

    }

    int getAvaiableQuantityBySku(string sku){
        if(products.find(sku)!=products.end()){
            return products[sku]->quantity;
        }
        return 0;
    }
    public:

    Product* getProductBySku(string sku){
        return NULL;
    }

};



class InventoryManager {
  
  private:
  
  static InventoryManager instance;

  
  vector<WareHouse *> warehouses;
  ProductFactory* productFactory;
  ReplenishmentStrategy* replenishmentStrategy;

  // Private constructor to prevent instantiation from outside
  InventoryManager() {
    // Initialize collections and dependencie
    productFactory = new ProductFactory();
  }

  public:

   InventoryManager* getInstance() {
    if (!instance) {
      instance = new InventoryManager();
    }
    return instance;
  }

  // Strategy pattern method
  void setReplenishmentStrategy(ReplenishmentStrategy* strategy) {
    this->replenishmentStrategy = strategy;
  }


  void addWarehouse(WareHouse* warehouse) {
    warehouses.push_back(warehouse);
  }

  void removeWarehouse(WareHouse* warehouse) {
   // warehouses.remove(warehouse); remove
  }

  Product* getProductBySku(string sku) {
    for (WareHouse* warehouse : warehouses) {
      Product* product = warehouse->getProductBySku(sku);
      if (product != NULL) {
        return product;
      }
    }
    return NULL;
  }

  void checkAndReplenish(string sku) {
    Product product = getProductBySku(sku);
    if (product != null) {

      if (product.getQuantity() < product.getThreshold()) {
       // notifyObservers(product);
       
        if (replenishmentStrategy != null) {
          replenishmentStrategy->replenish(product);
        }
      }
    }
  }


   void performInventoryCheck() {
    for (WareHouse* warehouse : warehouses) {
      for (Product product : warehouse->getAllProducts()) {
        if (product.getQuantity() < product.getThreshold()) {
         // notifyObservers(product);
          if (replenishmentStrategy != NULL) {
            replenishmentStrategy->replenish(product);
          }
        }
      }
    }
  }
}

int main(){

    // perform replenihs test and check it 

}