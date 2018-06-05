


Name: Lachezar Lyubenov

-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)

YES




Describe what augmentations to the bst data structures you made to complete the
project -- i.e., what types / data members did you change and why?


I added bookkeeping in order to fulfill the runtime requirements.
I added the following two integers that keep track of the size of the Binary tree:

int sizeofLeftTree;
int sizeofRightTree;




-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?

I added if statements which check if node was successfully deleted/inserted and decrements/increments the size values I added above:

Functions that I added bookkeeping to:
static bst_node * _insert();
static bst_node * _remove();

Also, I needed to use the size values in the _from_vec function to correctly calculate the size of the subtree that is being created based on the numbers stored in the vector.
static bst_node * _from_vec();







-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime
remained the same?

Insert Function:
I added addition operation in an if statement that that correctly adds +1 to the size of the corresponding left/right integer.

Delete Function:
I added subtraction operation in an if statement that that correctly subtracts -1 to the size of the corresponding left/right integer.


_from_vec Function:
I added if statements that check if root is empty, if its not empty, depending on which side of the root we are, we set the size of the tree to the sum of left+right+1 (1 being the root itself)




-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met.
4:  finished and I think it works most of the time and I'm sure my design leads to
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  ____5_______


-----------------------------------------------
get_ith level of completion:  _____5______

    How did you ensure O(h) runtime?

    ANSWER: I believe that by using my size bookkeeping values along with recursively written function, the runtime would be ensured.

-----------------------------------------------
num_geq level of completion:  ____5_______

    How did you ensure O(h) runtime?

    ANSWER: I believe that by using my size bookkeeping values along with recursively written function, the runtime would be ensured.

-----------------------------------------------
num_leq level of completion:  _____5_______

    How did you ensure O(h) runtime?

    ANSWER: I believe that by using my size bookkeeping values along with recursively written function, the runtime would be ensured.

-----------------------------------------------
num_range level of completion:  ______5______

    How did you ensure O(h) runtime?

    ANSWER: I believe that by using my size bookkeeping values along with recursively written function, the runtime would be ensured.

-----------------------------------------------
Implementation of size-balanced criteria according to
the given guidelines (including bst_sb_work):

    Level of completion: _____5______


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?

I tested my size-balancing of the binary tree by using text files with over 1000 numbers.
Also, tested my solution by inserting and deleting different nodes and checking the visual representation of the tree after each inserted/deleted number.
Another test was incrementing 1-9 and deleting odd/even or 9-1 and deleting elements/inserting new elements and keeping track of the functions based on  the bookkeeping data and the other functions.
