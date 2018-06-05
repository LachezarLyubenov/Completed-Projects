//Lachezar Lyubenov - llyube2
//.h file for Binary Tree implementation including a balanced implementation

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

template <typename T>
class bst {

private:
struct bst_node {
        T val;
        bst_node *left;
        bst_node *right;
        int sizeofLeftTree;
        int sizeofRightTree;

        bst_node ( const T & _val = T {
                }, bst_node * l = nullptr, bst_node *r = nullptr)
                : val { _val },  left { l }, right {r}
        { }
};



public:
// constructor:  initializes an empty tree
bst(){
        root = nullptr;
}

private:
// helper function which recursively deallocates nodes
//   in a tree.
static void delete_nodes(bst_node *r){
        if(r==nullptr) return;
        delete_nodes(r->left);
        delete_nodes(r->right);
        delete r;
}

public:
// destructor
~bst() {
        delete_nodes(root);
}

private:

/**
 * function:  insert()
 * desc:      recursive helper function inserting x into
 *            binary search tree rooted  at r.
 *
 * returns:   pointer to root of tree after insertion.
 *
 * notes:     if x is already in tree, no modifications are made.
 */
static bst_node * _insert(bst_node *r, T & x, bool &success){
        if(r == nullptr) {
                success = true;
                bst_node* newNode = new bst_node(x, nullptr, nullptr);
                newNode->sizeofLeftTree = 0;
                newNode->sizeofRightTree = 0;
                return newNode;
        }

        if(r->val == x) {
                success = false;
                return r;
        }
        if(x < r->val) {
                r->left = _insert(r->left, x, success);
                if(success == true)
                {
                        r->sizeofLeftTree++;
                }
                return r;
        }
        else {
                r->right = _insert(r->right, x, success);
                if(success == true)
                {
                        r->sizeofRightTree++;
                }
                return r;
        }
}


public:
/**
 * function:  insert
 * desc:      inserts x into BST given by t.  Note that
 *            a BST stores a SET -- no duplicates.  Thus,
 *            if x is already in t when call made, no
 *            modifications to tree result.
 *
 * note:      helper function does most of the work.
 *
 */
bool insert(T & x){
        bool success;
        if( !contains(x))
        {
                root = _insert(root, x, success);
                if(success)
                {
                        checkForBalance(root, x);
                }
        }
        return success;
}

/**
 * function:  contains()
 * desc:      returns true or false depending on whether x is an
 *            element of BST (calling object)
 *
 */
bool contains(const T & x){
        bst_node *p = root;

        while(p != nullptr) {

                if(p->val == x)
                        return true;
                if(x < p->val) {
                        p = p->left;
                }
                else
                        p = p->right;
        }
        return false;
}

private:
// returns pointer to node containing
//   smallest value in tree rooted at r
static bst_node * _min_node(bst_node *r ){
        if(r==nullptr)
                return nullptr;         // should never happen!
        while(r->left != nullptr)
                r = r->left;
        return r;
}

// returns pointer to node containing
//   smallest value in tree rooted at r
static bst_node * _max_node(bst_node *r ){
        if(r==nullptr)
                return nullptr;         // should never happen!
        while(r->right != nullptr)
                r = r->right;
        return r;
}

// recursive helper function for node removal
//   returns root of resulting tree after removal.
static bst_node * _remove(bst_node *r, T & x, bool &success){
        bst_node *tmp;
        bool sanity;

        if(r==nullptr) {
                success = false;
                return nullptr;
        }
        if(r->val == x) {
                success = true;

                if(r->left == nullptr) {
                        tmp = r->right;
                        delete r;
                        return tmp;
                }
                if(r->right == nullptr) {
                        tmp = r->left;
                        delete r;
                        return tmp;
                }
                // if we get here, r has two children
                r->val = _min_node(r->right)->val;
                r->right = _remove(r->right, r->val, sanity);
                if(!sanity)
                        std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
                return r;
        }
        if(x < r->val)
        {
                r->left = _remove(r->left, x, success);
                if (success) r->sizeofLeftTree--;
        }
        else {
                r->right = _remove(r->right, x, success);
                if (success) r->sizeofRightTree--;
        }
        return r;

}

public:

bool remove(T & x){
        bool success;
        root = _remove(root, x, success);
        if(success)
        {
                checkForBalance(root, x);
        }
        return success;
}


private:
// recursive helper function to compute size of
//   tree rooted at r
static int _size(bst_node *r){
        if(r==nullptr) return 0;
        return _size(r->left) + _size(r->right) + 1;
}

public:
int size() {
        if( root == nullptr)
        {
                return 0;
        }
        else{
                return (root->sizeofLeftTree + root->sizeofRightTree + 1);
        }
}

int sizeR() {
        return root->sizeofRightTree;
}
int sizeL() {
        return root->sizeofLeftTree;
}


private:

static int _height(bst_node *r){
        int l_h, r_h;

        if(r==nullptr) return -1;
        l_h = _height(r->left);
        r_h = _height(r->right);
        return 1 + (l_h > r_h ? l_h : r_h);
}

public:

int height() {
        return _height(root);
}

bool min(T & answer) {
        if(root == nullptr) {
                return false;
        }
        answer = _min_node(root)->val;
        return true;
}

T max() {
        return _max_node(root)->val;
}

/******************************************
 *
 * "stubs" for assigned TODO functions below
 *
 *****************************************/

// TODO
std::vector<T> * to_vector()
{
        bst_node *current,*pre;
        std::vector<T>* treeVector = new std::vector<T>();
        if(root == nullptr)
        {
                return 0;
        }
        current = root;
        while(current != nullptr)
        {
                if(current->left == nullptr)
                {
                        printf("%d ", current->val);
                        treeVector->push_back(current->val);
                        current = current->right;
                }
                else{
                        pre = current->left;
                        while(pre->right != nullptr && pre->right != current)
                        {
                                pre = pre->right;
                        }
                        if(pre->right == nullptr)
                        {
                                pre->right = current;
                                current = current->left;
                        }
                        else{
                                pre->right = nullptr;
                                printf("%d ",current->val);
                                treeVector->push_back(current->val);
                                current = current->right;
                        }
                }
        }

        return treeVector;
}



/* TODO
 * Function:  get_ith
 * Description:  determines the ith smallest element in t and
 *    "passes it back" to the caller via the reference parameter x.
 *    i ranges from 1..n where n is the number of elements in the
 *    tree.
 *
 *    If i is outside this range, false is returned.
 *    Otherwise, true is returned (indicating "success").
 *
 * Runtime:  O(h) where h is the tree height
 */
bool get_ith(int i, T &x) {
        if(i < 1 || i > size()) {
                return false;
        }

        _get_ith_FAST(root, i);
        return true;
}


bool get_ith_SLOW(int i, T &x) {
        int n = size();
        int sofar=0;

        if(i < 1 || i > n)
                return false;

        _get_ith_SLOW(root, i, x, sofar);
        return true;
}


/* TODO
 * Function:  num_geq
 * Description:  returns the number of elements in tree which are
 *       greater than or equal to x.
 *
 * Runtime:  O(h) where h is the tree height
 */
int num_geq(const T & x)
{
        return _num_geq_FAST(root, x);
}

/*
 * function:     num_geq_SLOW
 * description:  same functionality as num_geq but sloooow (linear time)
 *
 */
int num_geq_SLOW(const T & x)
{
        return _num_geq_SLOW(root, x);
}


/* TODO
 * Function:  num_leq
 * Description:  returns the number of elements in tree which are less
 *      than or equal to x.
 *
 * Runtime:  O(h) where h is the tree height
 *
 **/
int num_leq(const T &x)
{
        int result = 0;
        result = _num_leq_FAST(root, x, &result);
        return result;

}

/*
 * function:     num_leq_SLOW
 * description:  same functionality as num_leq but sloooow (linear time)
 *
 */
int num_leq_SLOW(const T & x) {
        return _num_leq_SLOW(root, x);
}

/* TODO
 * Function:  num_range
 * Description:  returns the number of elements in tree which are
 *       between min and max (inclusive).
 *
 * Runtime:  O(h) where h is the tree height
 *
 **/
int num_range(const T & min, const T & max) {

        return _num_range_FAST(root, min, max);

}

/*
 * function:     num_range_SLOW
 * description:  same functionality as num_range but sloooow (linear time)
 *
 */
int num_range_SLOW(const T & min, const T & max) {
        return _num_range_SLOW(root, min, max);
}

private:

//helper functions for geg, ith, leq, range.
static int _num_geq_FAST(bst_node * t, const T & x)
{
        if( t == nullptr) return 0;
        else if( t->val < x )
        {
                return _num_geq_FAST( t->right, x);
        }
        else if ( t->val > x)
        {
                return 1 + t->sizeofRightTree + _num_geq_FAST( t->left, x);
        }
        else return 1 + t->sizeofRightTree;
}
static int _get_ith_FAST(bst_node *t, int n)
{
        //check if the root is null
        if(t == nullptr)
        {
                return false;
        }
        if(t->sizeofLeftTree + 1 == n)
        {
                return t->val;
        }
        if(t->sizeofLeftTree < n)
        {
                return _get_ith_FAST(t->right, n - t->sizeofLeftTree - 1);
        }
        return _get_ith_FAST(t->left, n);
}
static int _num_leq_FAST(bst_node *t, int searchValue, int *result)
{
        if(t == nullptr)
        {
                return *result;
        }
        if(t->val == searchValue)
        {
                (*result)++;
                return _num_leq_FAST(t->left, searchValue, result);
        }
        if(t->val < searchValue)
        {
                (*result) += t->sizeofLeftTree + 1;
                return _num_leq_FAST(t->right, searchValue, result);
        }
        return _num_leq_FAST(t->left, searchValue, result);
}

static int _num_range_FAST(bst_node *t, const T &min, const T &max)
{
        if (!t) return 0;

        if (t->val == max && t->val == min)
        {
                return 1;
        }

        if (t->val <= max && t->val >= min)
        {
                return 1 + _num_range_FAST(t->left, min, max) + _num_range_FAST(t->right, min, max);
        }
        else if (t->val < min)
        {
                return _num_range_FAST(t->right, min, max);
        }
        else return _num_range_FAST(t->left, min, max);
}

static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
        if(t==nullptr)
                return;
        _get_ith_SLOW(t->left, i, x, sofar);

        if(sofar==i)
                return;
        sofar++;
        if(sofar==i) {
                x = t->val;
                return;
        }
        _get_ith_SLOW(t->right, i, x, sofar);
}

static int _num_geq_SLOW(bst_node * t, const T & x) {
        int total;

        if(t==nullptr) return 0;
        total =_num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

        if(t->val >= x)
                total++;
        return total;
}

static int _num_leq_SLOW(bst_node *t, const T &x) {
        int total;

        if(t==nullptr) return 0;
        total =_num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

        if(t->val <= x)
                total++;
        return total;
}

static int _num_range_SLOW(bst_node *t, const T &min, const T &max) {
        int total;

        if(t==nullptr) return 0;
        total =_num_range_SLOW(t->left, min, max) +
                _num_range_SLOW(t->right, min, max);

        if(t->val >= min && t->val <= max)
                total++;
        return total;
}

private:
static void indent(int m){
        int i;
        for(i=0; i<m; i++)
                std::cout << "-";
}

static void _inorder(bst_node *r){
        if(r==nullptr) return;
        _inorder(r->left);
        std::cout << "[ " << r->val << " ]\n";
        _inorder(r->right);
}

static void _preorder(bst_node *r, int margin){
        if(r==nullptr) {
                indent(margin);
                std::cout << " nullptr \n";
        }
        else {
                indent(margin);
                std::cout << "[ " << r->val << " ]\n";
                _preorder(r->left, margin+3);
                _preorder(r->right, margin+3);
        }
}

/*
 * TODO:
 * Complete the (recursive) helper function for the post-order traversal.
 * Remember: the indentation needs to be proportional to the height of the node!
 */
static void _postorder(bst_node *r, int margin){

        if(r==nullptr) {
                indent(margin);
                printf("nullptr \n");
        }
        else {
                _postorder(r->left, margin+3);
                _postorder(r->right, margin+3);
                indent(margin);
                std::cout << "[ " << r->val << " ]\n";
        }
}

public:
void inorder() {
        std::cout << "\n======== BEGIN INORDER ============\n";
        _inorder(root);
        std::cout << "\n========  END INORDER  ============\n";
}


void preorder() {

        std::cout << "\n======== BEGIN PREORDER ============\n";
        _preorder(root, 0);
        std::cout << "\n========  END PREORDER  ============\n";

}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void postorder() {

        std::cout << "\n======== BEGIN POSTORDER ============\n";
        _postorder(root, 0);
        std::cout << "\n========  END POSTORDER  ============\n";

}

private:
/*
 * Recursive  helper function _from_vec, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static bst_node * _from_vec(const std::vector<T> &a, int low, int hi){
        int m;
        bst_node *root;

        if(hi < low) return nullptr;
        m = (low+hi)/2;
        root = new bst_node(a[m]);
        root->left  = _from_vec(a, low, m-1);
        if(root->left != nullptr)
        {
                root->sizeofLeftTree = root->left->sizeofLeftTree + root->left->sizeofRightTree + 1;
        }
        root->right = _from_vec(a, m+1, hi);
        if(root->right != nullptr)
        {
                root->sizeofRightTree = root->right->sizeofLeftTree + root->right->sizeofRightTree + 1;
        }
        return root;

}

public:

void printHelper(bst_node *r, int space)
{
        if (r == NULL)
                return;
        space += 10;

        printHelper(r->right, space);

        printf("\n");
        for (int i = 10; i < space; i++)
                printf(" ");
        printf("%d\n", r->val);

        printHelper(r->left, space);
}

void print2D()
{
        return printHelper(this->root, 0);
}

static bst * from_sorted_vec(const std::vector<T> &a, int n){

        bst * t = new bst();
        t->root = _from_vec(a, 0, n-1);
        return t;
}

static bst_node * from_sorted_vec2(const std::vector<T> &a, bst_node* h, int n){

        h = _from_vec(a, 0, n-1);
        return h;
}

static std::vector<T> * to_vectorSUB(bst_node *t)
{
        bst_node *current,*pre;
        std::vector<T>* balancedSubTree = new std::vector<T>();
        if(t == nullptr)
        {
                return 0;
        }
        current = t;
        while(current != nullptr)
        {
                if(current->left == nullptr)
                {
                        printf("%d ", current->val);
                        balancedSubTree->push_back(current->val);
                        current = current->right;
                }
                else{
                        pre = current->left;
                        while(pre->right != nullptr && pre->right != current)
                        {
                                pre = pre->right;
                        }

                        if(pre->right == nullptr)
                        {
                                pre->right = current;
                                current = current->left;
                        }

                        else{
                                pre->right = nullptr;
                                printf("%d ",current->val);
                                balancedSubTree->push_back(current->val);
                                current = current->right;
                        }
                }
        }
        return balancedSubTree;
}


// TODO:  num_leaves
//   Hint:  feel free to write a helper function!!
int num_leaves() {
        int result = 0;
        return _num_leavesHelp(root, &result);
}

int _num_leavesHelp(bst_node *t, int *result)
{
        if (!t) return 0;

        if (!t->left && !t->right) (*result) += t->val;

        _num_leavesHelp(t->left, result);
        _num_leavesHelp(t->right, result);
}

// TODO:  num_at_level
// description:  returns the number of nodes at specified level
//   in tree.
// note:  the root is at level 0.
// Hint:  recursive helper function?
int num_at_level(int level) {

        std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
        return 0;
}

static bst_node * fixMyTree(bst_node *t, int x)
{
        std::vector<int>* subTreeVector = to_vectorSUB(t);
        bst_node* balancedTree = from_sorted_vec2(*subTreeVector, balancedTree,subTreeVector->size());

        std::vector<int>().swap(*subTreeVector);
        delete( t);
        return balancedTree;

}
void checkForBalance( bst_node *t, int x){
        root = isTreeBalanced( t, x);
}

static bst_node * isTreeBalanced(bst_node *r, int x)
{
        if (r == nullptr) return r;

        if (r->sizeofRightTree > (2 * (r->sizeofLeftTree + 1)) || r->sizeofLeftTree > (2 *(r->sizeofRightTree +1)))
        {
                return fixMyTree(r, x);
        }
        else{
                if (r->val < x)
                {
                        r->left = isTreeBalanced(r->left, x);
                }
                else{
                        r->right = isTreeBalanced(r->right, x);
                }
                return r;
        }
}

private:
bst_node *root;

};         // end class bst

#endif
