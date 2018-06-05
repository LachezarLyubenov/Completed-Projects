/* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {

    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       /* make this a debugMode statement */
       printf ("Val: %d, ", inputToken.getValue() );

       // add code to perform this operation here
       numberArray.push(inputToken.getValue());
       //numberArray.display();
       printf ("top is: ");
       std::cout << numberArray.top() << std::endl;

       /*
       printf ("\n\nval2222: %d, ", numberArray.top());
       bool ha;
       ha = numberArray.isEmpty();
       if(ha){
         printf ("test is true");
       }
       else{
         printf ("false");
       }*/
     }
    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
       /* make this a debugMode statement */
       printf ("OP: %c, ", inputToken.getOperator() );

       // add code to perform this operation here
       operatorArray.push(inputToken.getOperator());
       //printf ("\n\nvall333: %d, ", operatorArray.top());
       operatorArray.display();
      }

    /* get next token from input */
    inputToken = tr->getNextToken ();

   }
