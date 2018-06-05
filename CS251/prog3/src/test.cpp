#include <iostream>
#include "bst.h"

using namespace std;

template <typename T>
class Test {
public:
static bool AreEqual(T v1, T v2){
        return (v1==v2) ? true : false;
}
static bool isNull(T v1){
        return (v1 == nullptr) ? true : false;
}
static bool cmpVectors(vector<T> v1 /*expected*/, vector<T> v2 /*actual*/){
        if(v1.size() != v2.size()) return false;

        for (size_t i = 0; i < v1.size(); i++) {
                if(v1.at(i) != v2.at(i)) return false;
        }
        return true;
}
};
int main(){
        int x;
        int nleaves;
        int h;

        bst<int> *t = new bst<int>();
        /*
           vector<int> v = {1,2,3,4,5,6,7,8,9,10};
           t = t->from_sorted_vec(v, 10);
           std::vector<int> *v2 = t->to_vector();
           if (!Test<int>().cmpVectors(v, *v2))
           {
                printf("failed\n");
           }
           else{
                printf("not failed\n");
           }
           bst<int> *t1 = new bst<int>();
           if(!Test<vector<int>* >().isNull(t1->to_vector())) printf("failed null\n" );

         */
        while( (std::cin >> x))
                t->insert(x);

        if(t->size() <= 20) {
                t->inorder();
                t->preorder();
                t->postorder();
        }

        h = t->height();
        std::cout << "\n#### Reported height of tree:   " << h << "\n";

        int leafesNumber = 0;
        nleaves = t->num_leaves();
        std::cout << "\n#### Reported number of leaves:   " << nleaves  << "\n";

        std::cout << "\n####################\n\n";

        //t->to_vector();
        //int xx = 17;
/*
        t = t->from_sorted_vec(*(t->to_vectorSUB()),t->size());
        t->inorder();
        t->preorder();
        t->postorder();
 */


        int test = t->get_ith_SLOW(1,test);
        int test1 = t->get_ith(1,test);

        if (test) printf("\n\nIth number - SLOW is true and it is: %d", test);
        else printf("\nfalse: %d", test);
        if (test1) printf("\nIth number - FAST is true and it is: %d\n", test1);
        else printf("\nfalse: %d", test1);

        //std::cout << "\nIth number: " << t->get_ith_SLOW(10,test) << std::endl;

        int left = t->sizeL();
        int right = t->sizeR();
        std::cout << "\nLeft size is:" << left << "\t Right size is: " << right;


        left = t->sizeL();
        right = t->sizeR();
        std::cout << "\nLeft size is:" << left << "\t Right size is: " << right << std::endl;

        int greaterSlow = t->num_geq_SLOW(22);
        std::cout << "\nSlow greatest number: " << greaterSlow;
        int greaterFast = t->num_geq(22);
        std::cout << "\nFast greatest number: " << greaterFast << "\n" << endl;

        int leqSlow = t->num_leq_SLOW(13);
        std::cout << "\nSlow less than x number: " << leqSlow;
        int leqFast = t->num_leq(13);
        std::cout << "\nFast less than x number: " << leqFast << "\n" << endl;

        int numRangeSlow = t->num_range_SLOW(0, 10);
        std::cout << "\nSLOW - Range values are: " << numRangeSlow;
        int numRangeFast = t->num_range(0, 10);
        std::cout << "\nFAST - Range values are: " << numRangeFast << "\n" << endl;

        t->inorder();
        t->preorder();
        t->postorder();

        t->print2D();
        //int yy= 55;
        //t->insert(yy);
        //xx = 19;
        //yy= 55;
        //t->insert(yy);
        //yy= 212;
        //t->insert(yy);
        //yy= 156;
        //t->insert(yy);
        //yy= 78;
        //t->insert(yy);
        int xx = 9;
        t->remove(xx);
        xx = 7;
        t->remove(xx);
        xx = 5;
        t->remove(xx);
        xx = 3;
        t->remove(xx);
        xx = 1;
        t->remove(xx);

        test = t->get_ith_SLOW(1,test);
        test1 = t->get_ith(1,test);
        if (test) printf("\n\nIth number - SLOW is true and it is: %d", test);
        else printf("\nfalse: %d", test);
        if (test1) printf("\nIth number - FAST is true and it is: %d\n", test1);
        else printf("\nfalse: %d", test1);

        greaterSlow = t->num_geq_SLOW(7);
        std::cout << "\nSlow greatest number: " << greaterSlow;
        greaterFast = t->num_geq(7);
        std::cout << "\nFast greatest number: " << greaterFast << "\n" << endl;

        leqSlow = t->num_leq_SLOW(6);
        std::cout << "\nSlow less than x number: " << leqSlow;
        leqFast = t->num_leq(6);
        std::cout << "\nFast less than x number: " << leqFast << "\n" << endl;

        numRangeSlow = t->num_range_SLOW(0, 10);
        std::cout << "\nSLOW - Range values are: " << numRangeSlow;
        numRangeFast = t->num_range(0, 10);
        std::cout << "\nFAST - Range values are: " << numRangeFast << "\n" << endl;

        t->inorder();
        t->preorder();
        t->postorder();

        t->print2D();

        delete t;

        return 0;
}
