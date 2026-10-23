
//practice of pointer implementation 1.3.2 Task

#include <iostream>
#include <array>
#include <vector>


void pointer_tonothing(){

    double* ptr_to_nothing = nullptr; //pointer to nothing
    //pointers typically point to ints

}

void pointer_deferance(){
    double pi = 3.14;
    double* pi_ptr = &pi; //& is address-of operator. putting * in front of var gives 
                         //where it lives in memory not the value
    double** pi_ptr2 = &pi_ptr;
    double*** pi_ptr3 = &pi_ptr2;

    double** deref_pi_ptr3 = *pi_ptr3;
    double* deref_pi_ptr2 = *pi_ptr2;
    double deref_pi_ptr = *pi_ptr;

    std::cout << std::boolalpha; //makes cout print booleans
    std ::cout <<"Do the new values match the old values?\n" << (deref_pi_ptr3 == pi_ptr2) << '\n';
    std::cout << (deref_pi_ptr2 == pi_ptr) << '\n' << (deref_pi_ptr == pi) << "." <<std::endl; //endl ends line

}


int main(){
    int var = 4872;
    std::cout << "Value of var: " << var << std::endl; //outputs actual number
    std::cout << "Address of var: " << &var << std::endl; //outputs 0x7ccff0c (or the address)
    return 0;
}
