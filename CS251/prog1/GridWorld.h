
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

    Person(int i, int j , int k, bool alive, Node* p)
    {
        personID = i;
        xLocation = j;
        yLocation = k;
        isAlive = alive;
        member = p;
    }

};

class GridWorld : public GWInterface {

public:
    GridWorld(unsigned nrows, unsigned ncols) {

        worldPopulation = 0;
        worldX          = nrows;
        worldY          = ncols;
        idCounter       = 0;

        worldList = new List *[nrows];
        for (int i = 0; i <= nrows; i++) {
            worldList[i] = new List[ncols];
        }

        //sims = (Person*)malloc(sizeof(struct Person));




    }

    ~GridWorld() {
        // your destructor code here.
    }

    //birth 1 5 command fails? why?
    bool birth(int row, int col, int &id) {
        //int counter= 0;
        //std::cout << "size is:" << deadList.size <<std::endl;
        if (row >= 0 && col >= 0 && row < worldX && col < worldY) {                                 // DOES IT MAKE SENSE???
            if (deadList.size == 0) {
                id          = idCounter;
                //std::cout << "id is:" << id <<std::endl;
                insert_end (&worldList[row][col], id);
                Person temp = Person (id, row, col, true, worldList[row][col].back);   //is it id or worldPopulation?
                map.push_back (temp);
                worldPopulation++;
                idCounter++;
                //std::cout << "id is:" << id <<std::endl;

            } else {
                Node *temp = deadList.front;
                id = temp->personID;
                insert_end (&worldList[row][col], id);
                Person deadTemp = Person (id, row, col, true, worldList[row][col].back);
                map[id] = deadTemp;
                popNode (&deadList, temp);
                std::cout << "i was here" << std::endl;
                delete temp;
            }
            return true;
        } else {
            return false;
        }
    }


    //death 0 on full list doesnt work
    bool death(int id) {
        if (map[id].isAlive == true) {
            int row = map[id].xLocation;
            int col = map[id].yLocation;

            popNode (&worldList[map[id].xLocation][map[id].yLocation], map[id].member);
            insert_end (&deadList, id);

            Node *temp = deadList.front;
            id = temp->personID;
            Person deadTemp = Person (id, row, col, true, worldList[row][col].back);
            map[id] = deadTemp;
            map[id].isAlive = false;
            worldPopulation--;
            return true;
        } else {
            return false;
        }

    }

    //correctly gets the val for row and col but does not send correct one to main, why?
    bool whereis(int id, int &row, int &col) const {
        bool personFound = false;
        if (map[id].isAlive == true) {
            row = map[id].xLocation;
            col = map[id].yLocation;
            //std::cout << "row is: " << row << "\t column is: " << col << std::endl;
            personFound = true;
        }
        if (personFound == true) {
            return true;
        }
        return false;
    }

    bool move(int id, int targetRow, int targetCol) {

        if ((map[id].isAlive == true) && (targetRow > 0 && targetCol > 0 && targetRow <= worldX && targetCol <= worldY))
        {
            int oldRow = map[id].xLocation;
            int oldCol = map[id].yLocation;
            popNode (&worldList[oldRow][oldCol], map[id].member);
            insert_end(&worldList[targetRow][targetCol], id);
            map[id].xLocation = targetRow;
            map[id].yLocation = targetCol;
            //worldList[oldRow][oldCol].size--;
            return true;
        }
        else {
            return false;
        }
    }

    std::vector<int> *members(int row, int col) const
    {

        std::vector<int> *alivelist = new std::vector<int>;
        Node *front = worldList[row][col].front;
        std::cout << "test: " << front << std::endl;
        if (row >= 0 && col >= 0 && row < worldX && col < worldY) {                                 // DOES IT MAKE SENSE???
            for (int i = 0; i < worldList[row][col].size; i++) {
                alivelist->push_back (front->personID);
                front = front->next;
            }
        }
        return alivelist;
    }

    int population() const {
        return worldPopulation;
    }

    int population(int row, int col) const {
        return worldList[row][col].size;
    }

    int num_rows() const {

        return worldX;
    }

    int num_cols() const {

        return worldY;
    }


private:

    int worldX, worldY;
    int worldPopulation;
    List **worldList;
    List           deadList;
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

        Node *front = myList->front;
        Node *back  = myList->back;

        if (front == nullptr) {
            temp->prev    = nullptr;
            temp->next    = nullptr;
            myList->front = temp;
            myList->back  = temp;
            //std::cout << "Linked list Created!" << std::endl;
        } else {
            temp->next         = nullptr;
            myList->back->next = temp;
            temp->prev         = myList->back;
            myList->back       = temp;
            //std::cout << "Data Inserted at the end of the Linked list!" << std::endl;
        }
        myList->size++;
    }

    void insert_end2(List *myList, int x)
    {
        Node *temp = new Node;


        temp->personID = x;
        temp->next = nullptr;


        if (head == nullptr)
        {
            head = temp;
            std::cout << "Linked list Created!" << std::endl;
        }
        else
        {
            Node *temp2 = head;

            while (temp2->next != nullptr)
            {
                temp2 = temp2->next;
            }
            temp2 = temp->next;
        }
        myList->size++;
    }

};
