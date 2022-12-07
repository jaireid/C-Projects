/*
** Created on 9/25/22.
*/
#include <iostream>
#include <stdexcept>

namespace hanoi {
    enum Position: int { P0, P1, P2, P3 };

    void MoveBaseCases(Position p_start, Position p_end) {
        if(p_start == P0 and p_end == P1 ){
            std::cout << "Move disk from S to D" << std::endl;
        }else if( p_start == P1 and p_end == P2 ){
            std::cout << "Move disk from D to A1" << std::endl;
        }else if( p_start == P2 and p_end == P3 ){
            std::cout << "Move disk from A1 to A2" << std::endl;
            std::cout << "Move disk from A2 to A3" << std::endl;
            std::cout << "Move disk from A3 to A4" << std::endl;
        }else if( p_start == P3 and p_end == P2 ){
            std::cout << "Move disk from A4 to A1" << std::endl;
        }else if( p_start == P2 and p_end == P1 ){
            std::cout << "Move disk from A1 to D" << std::endl;
        }else{
            //std::cout << "P_start = " << p_start << " and " << "P_end = " << p_end << std::endl;
            //throw std::runtime_error("Got an unexpected result");
        }
    }

    void Move(int n, Position p_start, Position p_end);

    void MoveGeneralCase(int n, Position p_start, Position p_end) {// handle the general cases
        if (p_start == P0 and p_end == P1) {
            Move(n - 1, P0, P2);
            Move(1, P0, P1);
            Move(n - 1, P2, P1);
        } else if (p_start == P0 and p_end == P2) {
            Move(n, P0, P1);
            Move(n, P1, P2);
        } else if (p_start == P1 and p_end == P2) {
            Move(n - 1, P1, P3);
            Move(1, P1, P2);
            Move(n - 1, P3, P2);
        } else if (p_start == P2 and p_end == P1) {
            Move(n - 1, P2, P3);
            Move(1, P2, P1);
            Move(n - 1, P3, P1);
        } else if (p_start == P1 and p_end == P3) {
            Move(n - 1, P1, P3);
            Move(1, P1, P2);
            Move(n - 1, P3, P1);
            Move(1, P2, P3);
            Move(n - 1, P1, P3);
        } else if (p_start == P3 and p_end == P2) {
            Move(n - 1, P3, P1);
            Move(1, P3, P2);
            Move(n - 1, P1, P2);
        } else if (p_start == P3 and p_end == P1) {
            Move(n - 1, P3, P1);
            Move(1, P3, P2);
            Move(n - 1, P1, P3);
            Move(1, P2, P1);
            Move(n - 1, P3, P1);
        } else if (p_start == P2 and p_end == P3) {
            Move(n - 1, P2, P1);
            Move(1, P2, P3);
            Move(n - 1, P1, P3);
        }
    }

    void Move(int n, Position p_start, Position p_end){
        if( n < 0 ){
            std::cout << "Negative input, so invalid input." << std::endl;
        }else if( n == 0 ){
            // do nothing
        }else if( n == 1 and std::abs(p_start - p_end ) <= 1 ) {
            MoveBaseCases(p_start, p_end);
        }else{
            MoveGeneralCase(n, p_start, p_end);
        }
    }
}


int main(int argc, char** argv) {

    try {

        for(int n = 1; n <= 5; ++n){
            std::cout << "Running n = " << n << " case ----------------" << std::endl;
            Move(n, hanoi::P0, hanoi::P1);
            std::cout << "Finished n = " << n << " case -----------------\n\n" << std::endl;
        }

    }catch(std::exception& e){
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
