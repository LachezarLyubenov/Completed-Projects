//CS 251 Program 2
//Lachezar Lyubenov
//March, 10 2018

#include "GWInterface.h"
#include <vector>
#include <iostream>

using std::vector;

struct Node
{
    int personID;           //person ID
    Node* next;
    Node* prev;

};

struct Node* head;

struct List
{
    int size = 0;
    Node *front = nullptr;
    Node *back = nullptr;

};

class Person
{
    public:

    int personID = 0;
    int xLocation = 0, yLocation = 0;
    bool isAlive = false;
    Node *member = nullptr;

    Person(int i, int j, int k, bool alive, Node* p)
    {
        personID = i;
        xLocation = j;
        yLocation = k;
        isAlive = alive;
        member = p;
    }

    ~Person()
    {
        this->personID = 0;
        this->member = nullptr;
        delete member;
    };

};


class GridWorld : public GWInterface {

public:
    GridWorld(unsigned nrows, unsigned ncols) {

        worldPopulation = 0;
        worldX          = nrows;
        worldY          = ncols;
        idCounter       = 0;

        worldList = new List *[nrows];
        for (int i = 0; i < nrows; i++) {
            worldList[i] = new List[ncols];
        }

    }

    ~GridWorld()
    {
        map.clear ();
        for(int i = 0; i < worldX; i++) {
            delete (worldList[i]);
        }
        delete(worldList);

        clear();

    }

    static void clear()
    {
        Node *p = head;

        while (p!= nullptr)
        {
            head = head->next; // Mustn't "lose" the next node
            delete p; // De-allocate memory
            p = head; // Go to next node
        }
        head = nullptr;
        delete head;
    }

    //creates a person under given row and col, and is assigned an id
    bool birth(int row, int col, int &id) {
        if (row >= 0 && col >= 0 && row < worldX && col < worldY) {
            if (deadList.size == 0) {
                id          = idCounter;
                insert_end (&worldList[row][col], id);
                Person temp = Person (id, row, col, true, worldList[row][col].back);
                map.push_back (temp);
                worldPopulation++;
                idCounter++;

            } else {
                Node *temp = deadList.front;
                id = temp->personID;
                insert_end (&worldList[row][col], id);
                Person deadTemp = Person (id, row, col, true, worldList[row][col].back);
                map[id] = deadTemp;
                popNode (&deadList, temp);
                worldPopulation++;
                delete temp;
            }
            return true;
        } else {
            return false;
        }
    }

    //function to delete a person
    bool death(int id) {
        if (map[id].isAlive == true) {
            int row = map[id].xLocation;
            int col = map[id].yLocation;
            popNode (&worldList[map[id].xLocation][map[id].yLocation], map[id].member);
            insert_end (&deadList, id);

            Node *temp = deadList.back;
            id = temp->personID;
            Person deadTemp = Person (id, row, col, false, worldList[row][col].front);
            map[id] = deadTemp;
            worldPopulation--;
            return true;
        } else {
            return false;
        }

    }


    //locate a person based on unique ID
    bool whereis(int id, int &row, int &col) const
    {
        bool personFound = false;
        if (map[id].isAlive == true)
        {
            row         = map[id].xLocation;
            col         = map[id].yLocation;
            personFound = true;
        }
        if (personFound == true)
        {
            return true;
        }
        return false;
    }

    //Move function - moving people between districts
    bool move(int id, int targetRow, int targetCol) {

        if ((map[id].isAlive == true) && (targetRow > 0 && targetCol > 0 && targetRow <= worldX && targetCol <= worldY))
        {
            int oldRow = map[id].xLocation;
            int oldCol = map[id].yLocation;
            popNode (&worldList[oldRow][oldCol], map[id].member);
            insert_end(&worldList[targetRow][targetCol], id);
            map[id].xLocation = targetRow;
            map[id].yLocation = targetCol;
            return true;
        }
        else {
            return false;
        }
    }

    //store all alive people in a vector
    std::vector<int> *members(int row, int col) const
    {

        std::vector<int> *alivelist = new std::vector<int>;
        Node *front = worldList[row][col].front;
        //std::cout << "test: " << front << std::endl;
        if (row >= 0 && col >= 0 && row < worldX && col < worldY) {
            for (int i = 0; i < worldList[row][col].size; i++) {
                alivelist->push_back (front->personID);
                front = front->next;
            }
        }
        return alivelist;
    }


    //returns the alive people population
    int population() const {

        return worldPopulation;
    }

    //returns the people for given row and column
    int population(int row, int col) const {

        return worldList[row][col].size;

    }

    //return number of rows
    int num_rows() const {

        return worldX;
    }

    //returns number of columns
    int num_cols() const {

        return worldY;
    }


private:

    int worldX, worldY;
    int worldPopulation;
    List **worldList;
    List   deadList;
    vector<Person> map;
    int            idCounter;

    bool popNode(List *myList, Node *node) {
        Node *front = myList->front;
        Node *back  = myList->back;


        if (front == nullptr) {
            return false;
        } else if (node == front && node == back) {
            myList->front = nullptr;
            myList->back  = nullptr;
            myList->size--;
        } else if (node == front) {
            Node *temp = front;

            myList->front       = myList->front->next;
            temp->next          = nullptr;
            temp->prev          = nullptr;
            myList->front->prev = nullptr;
            myList->size--;
        } else if (node == back) {
            Node *temp = back;
            myList->back     = myList->back->prev;
            temp->prev->next = nullptr;
            temp->prev       = nullptr;
            temp->next       = nullptr;
            myList->size--;
        } else {
            Node *before = node->prev;
            Node *after  = node->next;
            before->next = after;
            after->prev  = before;
            node->next   = nullptr;
            node->prev   = nullptr;
            myList->size--;
        }
        return true;
    }

    void insert_end(List *myList, int x) {
        Node *temp = new Node;
        temp->personID = x;

        Node *front = myList->front;
        Node *back  = myList->back;

        if (front == nullptr) {
            temp->prev    = nullptr;
            temp->next    = nullptr;
            myList->front = temp;
            myList->back  = temp;
        } else {
            temp->next         = nullptr;
            myList->back->next = temp;
            temp->prev         = myList->back;
            myList->back       = temp;
        }
        temp = nullptr;
        delete temp;
        myList->size++;
    }
};
