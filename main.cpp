#include <iostream>
#include<map>
#include<vector>
#include<ctime>
using namespace std;


/********** RESTAURANT CLASS **********/

class restaurant {

private:

    string restName;
    int priceCat;
    string foodType;
    bool breakfast, lunch, dinner;
    int rating;

public:

    restaurant() {
        this->restName = "";
        this->priceCat = 0;
        this->foodType = "";
        this->breakfast = false;
        this->lunch = false;
        this->dinner = false;
        this->rating = 0;
    }

    restaurant(string restName, int priceCat, string foodType, bool breakfast, bool lunch, bool dinner, int rating) {
        this->restName = restName;
        this->priceCat = priceCat;
        this->foodType = foodType;
        this->breakfast = breakfast;
        this->lunch = lunch;
        this->dinner = dinner;
        this->rating = rating;
    }

    string getRestName();
    int getPriceCat();
    string getFoodType();
    bool getBreakfast();
    bool getLunch();
    bool getDinner();
    int getRating();


};

string restaurant::getRestName() { return restName; }
int restaurant::getPriceCat()    { return priceCat; }
string restaurant::getFoodType() { return foodType; }
bool restaurant::getBreakfast()  { return breakfast; }
bool restaurant::getLunch()      { return lunch; }
bool restaurant::getDinner()     { return dinner; }
int restaurant::getRating()      { return rating; }





/********** EDGELIST CLASS **********/

class edgeList {

private:
    map<string, vector<restaurant*>> graph;
    map<string, vector<restaurant*>> :: iterator it;

public:
    void insertEdge(restaurant* rest);
    void searchAllRestaurants(string decisions);
    void searchRandRestaurants(string decisions);

};

void edgeList::insertEdge(restaurant* rest) {

    // The key is the restaurant type! (the edge is the restaurant type key word)
    // restaurants with the same type are connected through a vector of restaurants

    restaurant* restTemp = rest;

    // If restaurant type doesn't already exist
    // Will create a new key with that restaurent type
    // and the value will begin a vector of restaurant* STARTING with the restaurant in question (rest)
    if (!graph.count(restTemp->getFoodType())) {
        vector<restaurant*> rests;
        rests.push_back(restTemp);
        graph.insert({ restTemp->getFoodType(), rests });
    }

        // If the restaurant type DOES already exist, it pushes back the restaurant* onto the prexisting vector of restaurant*
    else {
        graph.find(restTemp->getFoodType())->second.push_back(restTemp);
    }

}
void edgeList::searchAllRestaurants(string decisions) {

    vector<restaurant*> res = graph.find(decisions)->second;

    for(int i = 0; i < res.size(); i++) {
        cout << "Restaurant Name: " << res.at(i)->getRestName() << endl;
        cout << "Food Type: " << res.at(i)->getFoodType()  << endl;
        switch (res.at(i)->getPriceCat()) {
            case 1:
                cout << "Price: $" << endl;
                break;
            case 2:
                cout << "Price: $$" << endl;
                break;
            case 3:
                cout << "Price: $$$" << endl;
                break;
        }
        cout << "Rating: " << res.at(i)->getRating() << "/5 "<< endl;
        cout << "Serves: ";
        if(res.at(i)->getBreakfast() == 1){
            cout << "Breakfast ";
        }
        if(res.at(i)->getLunch() == 1) {
            cout << "Lunch ";
        }
        if(res.at(i)->getDinner() == 1){
            cout << "Dinner ";
        }
        cout << endl;
    }


}
void edgeList::searchRandRestaurants(string decisions) {
    vector<restaurant*> res = graph.find(decisions)->second;
    int randomVal = rand() % res.size();
    cout << "Restaurant Name: " << res.at(randomVal)->getRestName() << endl;
    cout << "Food Type: " << res.at(randomVal)->getFoodType()  << endl;
    switch (res.at(randomVal)->getPriceCat()) {
        case 1:
            cout << "Price: $" << endl;
            break;
        case 2:
            cout << "Price: $$" << endl;
            break;
        case 3:
            cout << "Price: $$$" << endl;
            break;
    }
    cout << "Rating: " << res.at(randomVal)->getRating() << "/5 "<< endl;
    cout << "Serves: ";
    if(res.at(randomVal)->getBreakfast() == 1){
        cout << "Breakfast ";
    }
    if(res.at(randomVal)->getLunch() == 1) {
        cout << "Lunch ";
    }
    if(res.at(randomVal)->getDinner() == 1){
        cout << "Dinner ";
    }

    cout << endl;


}




/********** HELPER FUNCTIONS FOR MAIN **********/

string generateRandomString(int length) {
    char alphaNum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    string temp;
    temp.reserve(length);

    for (int i = 0; i < length; i++) {
        temp += alphaNum[rand() % (sizeof(alphaNum) - 1)];
    }

    return temp;
}

string generateRandomType() {
    int num = rand() % (19) + 1;
    string foodType = "";

    switch (num) {
        case 1:
            foodType = "American";
            break;
        case 2:
            foodType = "Mexican";
            break;
        case 3:
            foodType = "Italian";
            break;
        case 4:
            foodType = "Greek";
            break;
        case 5:
            foodType = "Sandwiches";
            break;
        case 6:
            foodType = "French";
            break;
        case 7:
            foodType = "Baked Goods";
            break;
        case 8:
            foodType = "Beverages";
            break;
        case 9:
            foodType = "Frozen Desserts";
            break;
        case 10:
            foodType = "Chinese";
            break;
        case 11:
            foodType = "Japanese";
            break;
        case 12:
            foodType = "Salad";
            break;
        case 13:
            foodType = "Chicken";
            break;
        case 14:
            foodType = "Indian";
            break;
        case 15:
            foodType = "Pizza";
            break;
        case 16:
            foodType = "Seafood";
            break;
        case 17:
            foodType = "Vegan";
            break;
        case 18:
            foodType = "Steak";
            break;
        case 19:
            foodType = "Theme Dining";
            break;
        case 20:
            foodType = "Thai";
            break;
    }

    return foodType;
}





/********** MAIN **********/

int main()
{

    cout << endl;
    
    cout << "Hello! Welcome to 'Restaurant Finder'!" << endl;
    int decision1 = 0, decision2 = 0, decision3 = 0;

    cout << endl;

    cout << "Would you like to use..." << endl;
    cout << "(Type '1') Edge List" << endl;
    cout << "(Type '2') Adjacency List" << endl;
    cout << "(Type '3') Exit" << endl;
    cin >> decision1;

    cout << endl;

    edgeList graph;
    if(decision1 == 1) {
            // Create new adjacencyList

            //Randomly insert 100 "restaurants" into adjacency list
            for (int i = 0; i < 100; i++) {

                string restName = generateRandomString(12);
                int priceCat = rand() % 3 + 1;
                string foodType = generateRandomType();
                bool breakfast = rand() % 2;
                bool lunch = rand() % 2;
                bool dinner = rand() % 2;
                int rating = rand() % 5 + 1;
                restaurant *rest = new restaurant(restName, priceCat, foodType, breakfast, lunch, dinner, rating);
                graph.insertEdge(rest);
            }
            cout << "Loading Edge List..." << endl;
        }
    else if(decision1 == 2) {
        cout << "Loading Adajacency List..." << endl;
    }
    else if(decision1 == 3) {
        return 0;
    }
    while(decision2 != 4) {
        cout << "What would you like to do today?" << endl;
        cout << "(Type '1') Find a random restaurant" << endl;
        cout << "(Type '2') Print all restaurants in a specific food category" << endl;
        cout << "(Type '4') Exit" << endl;
        cin >> decision2;

        cout << endl;
    if(decision2 < 4) {
        cout << "What type of food are you in the mood for?" << endl;
        cout << "(Type '1') American" << endl;
        cout << "(Type '2') Mexican" << endl;
        cout << "(Type '3') Italian" << endl;
        cout << "(Type '4') Greek" << endl;
        cout << "(Type '5') Sandwiches" << endl;
        cout << "(Type '6') French" << endl;
        cout << "(Type '7') Baked Goods" << endl;
        cout << "(Type '8') Beverages" << endl;
        cout << "(Type '9') Frozen Desserts" << endl;
        cout << "(Type '10') Chinese" << endl;
        cout << "(Type '11') Japanese" << endl;
        cout << "(Type '12') Salad" << endl;
        cout << "(Type '13') Chicken" << endl;
        cout << "(Type '14') Indian" << endl;
        cout << "(Type '15') Pizza" << endl;
        cout << "(Type '16') Seafood" << endl;
        cout << "(Type '17') Vegan" << endl;
        cout << "(Type '18') Steak" << endl;
        cout << "(Type '19') Theme Dining" << endl;
        cout << "(Type '20') Thai" << endl;

        cin >> decision3;
    }



        /********** ALGORITHM 1 **********/
        if (decision1 == 1) {
            string foodType;
            switch (decision3) {
                case 1:
                    foodType = "American";
                    break;
                case 2:
                    foodType = "Mexican";
                    break;
                case 3:
                    foodType = "Italian";
                    break;
                case 4:
                    foodType = "Greek";
                    break;
                case 5:
                    foodType = "Sandwiches";
                    break;
                case 6:
                    foodType = "French";
                    break;
                case 7:
                    foodType = "Baked Goods";
                    break;
                case 8:
                    foodType = "Beverages";
                    break;
                case 9:
                    foodType = "Frozen Desserts";
                    break;
                case 10:
                    foodType = "Chinese";
                    break;
                case 11:
                    foodType = "Japanese";
                    break;
                case 12:
                    foodType = "Salad";
                    break;
                case 13:
                    foodType = "Chicken";
                    break;
                case 14:
                    foodType = "Indian";
                    break;
                case 15:
                    foodType = "Pizza";
                    break;
                case 16:
                    foodType = "Seafood";
                    break;
                case 17:
                    foodType = "Vegan";
                    break;
                case 18:
                    foodType = "Steak";
                    break;
                case 19:
                    foodType = "Theme Dining";
                    break;
                case 20:
                    foodType = "Thai";
                    break;
            }
            // Find random restaurant given an edge
            if (decision2 == 1) {

                // INSERT CODE HERE USING ALGORITHM BASED CODE TO FIND RANDOM RESTAURANT
                graph.searchRandRestaurants(foodType);

            }
            // Prints all restaurants with same edge
            if (decision2 == 2) {
                // INSERT CODE HERE USING ALGORITHM BASED CODE TO FIND ALL RESTAURANT WITHIN A FOOD CATEGORY AND PRINT ALL INFORMATION ON THEM
                graph.searchAllRestaurants(foodType);
            }
        }



        /********** ALGORITHM 2 **********/
        if (decision1 == 2) {

            // Find random restaurant given an edge
            if (decision2 == 1) {

                // INSERT CODE HERE USING ALGORITHM BASED CODE TO FIND RANDOM RESTAURANT

            }
            // Prints all resaturants with same edge
            if (decision2 == 2) {

                // INSERT CODE HERE USING ALGORITHM BASED CODE TO FIND ALL RESTAURANT WITHIN A FOOD CATEGORY AND PRINT ALL INFORMATION ON THEM

            }
        }
    }

}


