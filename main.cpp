#include <iostream>
#include<map>
#include<vector>
#include<set>
#include<queue>
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





/********** adjList CLASS **********/

class adjList {

private:
    map<string, pair<restaurant*, vector<pair<int, restaurant*>>>> graph;
    map<string, pair<restaurant*, vector<pair<int, restaurant*>>>> :: iterator it;

public:
    void insertEdge(restaurant* to, restaurant* from, int w);
    void searchAllRestaurants(string decisions, int price);
    void searchRandRestaurants(string decisions, int price);
    map<string, pair<int, restaurant*>> dijkstra(string decisions, int price);
    int v = 0;

};

void adjList::insertEdge(restaurant* to, restaurant* from, int w) {

    // The key is the restaurant name!

    if (!graph.count(from->getRestName())) {
        vector<pair<int, restaurant*>> rests;
        rests.emplace_back(w, to);
        graph.insert({from->getRestName(), make_pair(from, rests) });
    }
        // If the restaurant type DOES already exist, it pushes back the restaurant* onto the prexisting vector of restaurant*
    else {
        graph[from->getRestName()].second.emplace_back(w, to);
    }

}

map<string, pair<int, restaurant*>> adjList::dijkstra(string foodType, int price) {

    map<string, pair<int, restaurant*>> r;
    map<string, int> d;
    map<string, string> p;
    priority_queue<pair<int,string>> pq;
    set<string> visited;
    int distance = 0;

//Initialize
    pq.push(make_pair(0, graph.begin()->first));

//Initialize  first vertex
    d.insert(pair<string, int>(graph.begin()->first, 0));
    p.insert(pair<string, string> (graph.begin()->first, ""));
    for(int i = 0; i < graph.begin()->second.second.size(); i++){
        d.insert(pair<string, int>(graph.begin()->second.second[i].second->getRestName(), INT_MAX));
        p.insert(pair<string, string> (graph.begin()->second.second[i].second->getRestName(), ""));
    }

    if(graph.begin()->second.first->getFoodType() == foodType ) r.insert({graph.begin()->first , {0, graph.begin()->second.first} });

//Initialize distance and previous vector
    for(auto it = ++graph.begin(); it != graph.end(); ++it){

        d.insert(pair<string, int>(it->first, INT_MAX));
        p.insert({it->first, ""});
//Adjacent nodes
        for(int i = 0; i < it->second.second.size(); i++){
            d.insert(pair<string, int>(it->second.second[i].second->getRestName(), INT_MAX));
            p.insert(pair<string, string> (it->second.second[i].second->getRestName(), ""));
        }
    }

    while(!pq.empty()){
        string current = pq.top().second;
        pq.pop();
        visited.insert(current);
        distance = d[current];
        vector<pair<int, restaurant*>> currentVector = graph[current].second;

        for(int i = 0; i< currentVector.size(); i++){
            if(visited.find(currentVector[i].second->getRestName()) == visited.end()){
//Inserts values in priority queue as negative so its smallest first
                pq.push(make_pair((-1)*currentVector[i].first, currentVector[i].second->getRestName()));
            }

            if (d[currentVector[i].second->getRestName()] > distance + currentVector[i].first) {

                d[currentVector[i].second->getRestName()] = distance + currentVector[i].first;
                string food = currentVector[i].second->getFoodType();
                p[currentVector[i].second->getRestName()] = current;

//Adds to special map if it satisfies wanted foodtype
                if(currentVector[i].second->getPriceCat() == price && currentVector[i].second->getFoodType() == foodType && r.count(currentVector[i].second->getRestName()) == 0) {
                    if(currentVector[i].second->getRating() == 4 || currentVector[i].second->getRating() == 5) {
                        if(currentVector[i].second->getDinner() == 1 || currentVector[i].second->getLunch() == 1 || currentVector[i].second->getBreakfast() == 1) {
                            r.insert({currentVector[i].second->getRestName(),{distance + currentVector[i].first, currentVector[i].second}});
                        }
                    }
                } else if(currentVector[i].second->getFoodType() == foodType && currentVector[i].second->getPriceCat() == price){
                    if(currentVector[i].second->getRating() == 4 || currentVector[i].second->getRating() == 5) {
                        if(currentVector[i].second->getDinner() == 1 || currentVector[i].second->getLunch() == 1 || currentVector[i].second->getBreakfast() == 1) {
                            r[currentVector[i].second->getRestName()] = make_pair(distance + currentVector[i].first, currentVector[i].second);
                        }
                    }
                }

            }
        }
    }
    return r;
}
void adjList::searchAllRestaurants(string foodType, int price) {
    //gets the returning map of values containing choices
    map<string, pair<int, restaurant*>> d = dijkstra(foodType, price);
    vector<restaurant*> res;
    vector<int> dist;
    //transfer the map into vectors for easy looping.
    for (auto it = d.begin(); it != d.end(); ++it) {
        res.push_back(it->second.second);
        dist.push_back(it->second.first);
    }
    //display results
    cout << "Restaurants within your given choices (4 stars or higher):" << endl;
    cout << "-----------------------------------------------------------" << endl;
    char nextVal = 'Y';
    int j = 0;
    while(j < res.size() && nextVal != 'N') {
        for (int i = j; i < j + 10; i++) {
            if (i < res.size()) {
                cout << "Restaurant Name: " << res[i]->getRestName() << endl;
                cout << "Food Type: " << res[i]->getFoodType()  << endl;
                switch ( res[i]->getPriceCat()) {
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
                cout << "Rating: " << res[i]->getRating() << "/5 "<< endl;
                cout << "Serves: ";
                if(res[i]->getBreakfast() == 1){
                    cout << "Breakfast ";
                }
                if(res[i]->getLunch() == 1) {
                    cout << "Lunch ";
                }
                if(res[i]->getDinner() == 1) {
                    cout << "Dinner ";
                }
                cout << endl;
                cout << "Distance: " << dist[i] << " yds" << endl;
                cout << endl;
            } else {
                return;
            }
        }
        //keep track of going to next ten values
        cout << "Would you like to see the next ten restaurants? (Y/N)" << endl;
        cin >> nextVal;
        j += 10;
    }

}
void adjList::searchRandRestaurants(string foodtype, int price) {
    //gets map containing values of choices
    map<string, pair<int, restaurant*>> res = dijkstra(foodtype, price);
    //gets random index
    int randomVal = rand() % res.size();
    auto it = res.begin();
    int i = 0;
    for (; it != res.end(); ++it){
        if (i == randomVal) break;
        i++;
    }
    //Display Results
    cout << "Random restaurant within your given choices (4 stars or higher):" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "Restaurant Name: " << it->first << endl;
    cout << "Food Type: " << it->second.second->getFoodType()  << endl;
    switch ( it->second.second->getPriceCat()) {
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
    cout << "Rating: " << it->second.second->getRating() << "/5 "<< endl;
    cout << "Serves: ";
    if(it->second.second->getBreakfast() == 1){
        cout << "Breakfast ";
    }
    if(it->second.second->getLunch() == 1) {
        cout << "Lunch ";
    }
    if(it->second.second->getDinner() == 1) {
        cout << "Dinner ";
    }
    cout << endl;
    cout << "Distance: " << it->second.first << " yds" << endl;
    cout << endl;

}
/********** EDGELIST CLASS **********/
class Edge {

private:
//set the variables stored for each edge
    restaurant* start;
    restaurant* end;
    int weight;

public:

    Edge() {
        this->start = nullptr;
        this->end = nullptr;
        this->weight = 0;
    }

    Edge(restaurant* start, restaurant* end, int weight) {
        this->start = start;
        this->end = end;
        this->weight = weight;

    }
    restaurant* getStart();
    restaurant* getEnd();
    int getWeight();

};
restaurant* Edge::getStart() {return start; }
restaurant* Edge::getEnd() {return end; }
int Edge::getWeight() {return weight; }

class edgeList {

private:
    //created a graph based off a vector of edges
    vector<Edge*> graph;

public:
    void insertEdge(restaurant* start, restaurant* end, int weight);
    void searchAllRestaurants(string decisions, int price);
    void searchRandRestaurants(string decisions, int price);
    map<string,pair<int, restaurant*>>dijkstra(string foodtype, int price);
    int v = 0;
};

void edgeList ::insertEdge(restaurant* start, restaurant* end, int weight) {
    //insert start and end vertex with weight value
    Edge* edge = new Edge(start, end, weight);
    graph.push_back(edge);


}

map<string, pair<int, restaurant*>> edgeList::dijkstra(string foodType, int price) {
    map<string, pair<int, restaurant*>> r;
    map<string, int> d;
    map<string, string> p;
    priority_queue<pair<int,string>> pq;
    set<string> visited;
    int distance = 0;

//Initialize
    pq.push(make_pair(0, graph[0]->getStart()->getRestName()));

//Initialize  first vertex
    d.insert(pair<string, int>(graph[0]->getStart()->getRestName(), 0));
    p.insert(pair<string, string> (graph[0]->getStart()->getRestName(), ""));

    if(graph[0]->getStart()->getFoodType() == foodType ) r.insert({graph[0]->getStart()->getRestName() , {0, graph[0]->getStart()} });


   for (int j = 0; j < graph.size(); j++){

        string current = graph[j]->getEnd()->getRestName();
        visited.insert(current);
        if (d.count(current) == 0) d.insert(pair<string, int>(current, INT_MAX));
        distance = d[graph[j]->getStart()->getRestName()];

            if (d[current] > distance + graph[j]->getWeight()) {

                d[current] = distance + graph[j]->getWeight();
                string food = graph[j]->getEnd()->getFoodType();
                p[current] = graph[j]->getStart()->getRestName();

                //Adds to special map if it satisfies wanted foodtype
                if(graph[j]->getEnd()->getPriceCat() == price && graph[j]->getEnd()->getFoodType() == foodType && r.count(graph[j]->getEnd()->getRestName()) == 0) {
                    if(graph[j]->getEnd()->getRating() == 4 || graph[j]->getEnd()->getRating() == 5) {
                        if(graph[j]->getEnd()->getDinner() == 1 || graph[j]->getEnd()->getLunch() == 1 || graph[j]->getEnd()->getBreakfast() == 1) {
                            r.insert({graph[j]->getEnd()->getRestName(),{distance + graph[j]->getWeight(), graph[j]->getEnd()}});
                        }
                    }
                } else if(graph[j]->getEnd()->getFoodType() == foodType && graph[j]->getEnd()->getPriceCat() == price){
                    if(graph[j]->getEnd()->getRating() == 4 || graph[j]->getEnd()->getRating() == 5) {
                        if(graph[j]->getEnd()->getDinner() == 1 || graph[j]->getEnd()->getLunch() == 1 || graph[j]->getEnd()->getBreakfast() == 1) {
                            r[graph[j]->getEnd()->getRestName()] = make_pair(distance + graph[j]->getWeight(), graph[j]->getEnd());
                        }
                    }
                }

            }

    }
    return r;
}
void edgeList::searchAllRestaurants(string foodType, int price){
    //gets the returning map of values containing choices
    map<string, pair<int, restaurant*>> d = dijkstra(foodType, price);
    vector<restaurant*> res;
    vector<int> dist;
    //transfer the map into vectors for easy looping.
    for (auto it = d.begin(); it != d.end(); ++it) {
        res.push_back(it->second.second);
        dist.push_back(it->second.first);
    }
    cout << "Restaurants within your given choices (4 stars or higher):" << endl;
    cout << "-----------------------------------------------------------" << endl;
    char nextVal = 'Y';
    int j = 0;
    while(j < res.size() && nextVal != 'N') {
        for (int i = j; i < j + 10; i++) {
            if (i < res.size()) {
                cout << "Restaurant Name: " << res[i]->getRestName() << endl;
                cout << "Food Type: " << res[i]->getFoodType() << endl;
                switch (res[i]->getPriceCat()) {
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
                cout << "Rating: " << res[i]->getRating() << "/5 " << endl;
                cout << "Serves: ";
                if (res[i]->getBreakfast() == 1) {
                    cout << "Breakfast ";
                }
                if (res[i]->getLunch() == 1) {
                    cout << "Lunch ";
                }
                if (res[i]->getDinner() == 1) {
                    cout << "Dinner ";
                }
                cout << endl;
                cout << "Distance: " << dist[i] << " yds" << endl;
                cout << endl;
            } else {
                return;
            }
        }
        //keep track of next ten values
        cout << "Would you like to see the next ten restaurants? (Y/N)" << endl;
        cin >> nextVal;
        j += 10;
    }
}
void edgeList::searchRandRestaurants(string foodtype, int price) {
    //gets map containing values of choices
    map<string, pair<int, restaurant*>> res = dijkstra(foodtype, price);
    //gets random index
    int randomVal = rand() % res.size();
    auto it = res.begin();
    int i = 0;
    for (; it != res.end(); ++it){
        if (i == randomVal) break;
        i++;
    }
    //Display results
    cout << "Random restaurant within your given choices (4 stars or higher):" << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << "Restaurant Name: " << it->first << endl;
    cout << "Food Type: " << it->second.second->getFoodType()  << endl;
    switch ( it->second.second->getPriceCat()) {
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
    cout << "Rating: " << it->second.second->getRating() << "/5 "<< endl;
    cout << "Serves: ";
    if(it->second.second->getBreakfast() == 1){
        cout << "Breakfast ";
    }
    if(it->second.second->getLunch() == 1) {
        cout << "Lunch ";
    }
    if(it->second.second->getDinner() == 1) {
        cout << "Dinner ";
    }
    cout << endl;
    cout << "Distance: " << it->second.first << " yds" << endl;
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
    int num = rand() % (20) + 1;
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


void loadData(adjList &graph, edgeList &graph2){
    //Create new Lists
    cout << "Loading Graphs..." << endl;
    //Place every restaurant into queue so you systematically go through each node to add more onto
    queue<restaurant*> prev;
    //vector stores previous restaurants so we can randomly link back to previous ones
    vector<restaurant*> storedRes;
    //Randomly insert 100000 "restaurants" into edge list
    //head restaurant
    string restName = generateRandomString(12);
    int priceCat = rand() % 3 + 1;
    string foodType = generateRandomType();
    bool breakfast = rand() % 2;
    bool lunch = rand() % 2;
    bool dinner = rand() % 2;
    int rating = rand() % 5 + 1;
    restaurant *rest = new restaurant(restName, priceCat, foodType, breakfast, lunch, dinner, rating);
    graph.v++;
    graph2.v++;

    prev.push(rest);
    storedRes.push_back(rest);

    while (graph2.v <= 100000) {
        rest = prev.front();
        prev.pop();
        int connected = rand()%4 + 1;

        for(int j = 0; j < connected; j++){
            int ranRes = 0;
            if(graph2.v > 10){
                ranRes = rand()%2;
            }
            restaurant *rest2 = nullptr;
            if (ranRes == 0) {
                restName = generateRandomString(12);
                priceCat = rand() % 3 + 1;
                foodType = generateRandomType();
                breakfast = rand() % 2;
                lunch = rand() % 2;
                dinner = rand() % 2;
                rating = rand() % 5 + 1;
                rest2 = new restaurant(restName, priceCat, foodType, breakfast, lunch, dinner, rating);
                prev.push(rest2);
                storedRes.push_back(rest2);
                graph.v++;
                graph2.v++;
            } else{
                rest2 = storedRes[rand()%(storedRes.size() -1)];
            }
            int weight = rand()%100 + 1;
            //insert into adajacency
            graph.insertEdge(rest2, rest, weight);
            //insert into edge
            graph2.insertEdge(rest, rest2, weight);

        }
    }
    cout << "-Download Complete-" << endl;

}


/********** MAIN **********/

int main()
{
    adjList graph;
    edgeList graph2;

    loadData(graph, graph2);
    cout << endl;

    cout << "Hello! Welcome to 'Restaurant Finder'!" << endl;
    int decision1 = 0, decision2 = 0, decision3 = 0;

    cout << endl;

    while(true && decision2 != 4) {
        cout << "Would you like to use..." << endl;
        cout << "(Type '1') Adjacency List" << endl;
        cout << "(Type '2') Edge List" << endl;
        cout << "(Type '3') Exit" << endl;
        cin >> decision1;

        cout << endl;

        if (decision1 == 3) {
            cout << endl;
            cout << "Closing Program..." << endl;
            return 0;
        }
        while (decision2 != 4) {
            cout << "What would you like to do today?" << endl;
            cout << "(Type '1') Find a random restaurant" << endl;
            cout << "(Type '2') Print all restaurants in a specific food category" << endl;
            cout << "(Type '3') New list" << endl;
            cout << "(Type '4') Exit" << endl;
            cin >> decision2;

            if (decision2 == 3) break;
            cout << endl;
            if (decision2 < 4) {
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
            cout << endl;
            int decision4;
            if (decision2 < 4) {
                //Has user decide the price
                cout << "What price are you wanting to pay?" << endl;
                cout << "(Type '1') $" << endl;
                cout << "(Type '2') $$" << endl;
                cout << "(Type '3') $$$" << endl;
                cin >> decision4;
            }
            /********** ALGORITHM 1 **********/
            if (decision1 == 1) {

                // Find random restaurant given an edge
                if (decision2 == 1) {

                    // INSERT CODE HERE USING ALGORITHM BASED CODE TO FIND RANDOM RESTAURANT
                    graph.searchRandRestaurants(foodType, decision4);

                }
                // Prints all restaurants with same edge
                if (decision2 == 2) {
                    // INSERT CODE HERE USING ALGORITHM BASED CODE TO FIND ALL RESTAURANT WITHIN A FOOD CATEGORY AND PRINT ALL INFORMATION ON THEM
                    graph.searchAllRestaurants(foodType, decision4);
                }
            }



            /********** ALGORITHM 2 **********/
            if (decision1 == 2) {

                // Find random restaurant given an edge
                if (decision2 == 1) {

                    // INSERT CODE HERE USING ALGORITHM BASED CODE TO FIND RANDOM RESTAURANT
                    graph2.searchRandRestaurants(foodType, decision4);
                }
                // Prints all restaurants with same edge
                if (decision2 == 2) {

                    // INSERT CODE HERE USING ALGORITHM BASED CODE TO FIND ALL RESTAURANT WITHIN A FOOD CATEGORY AND PRINT ALL INFORMATION ON THEM
                    graph2.searchAllRestaurants(foodType,decision4);
                }
            }
        }
    }
    cout << "Closing Program..." << endl;

}
