#include <iostream>
#include <stdexcept>

namespace hanoi {
  enum Position: int { P0, P1, P2, P3 };
  int moves = 1;

  void MoveBaseCases(Position p_start, Position p_end) {
    // if (moves < 101) {
    // Base Cases
    if(p_start == P0 && p_end == P1 ){
      std::cout << "Move " << moves << ": Move disk from S to D" << std::endl;
      moves++;
    }
    else if( p_start == P1 && p_end == P2 ){
      std::cout << "Move " << moves << ": Move disk from D to A1" << std::endl;
      moves++;
    }
    else if( p_start == P2 && p_end == P3 ){
      std::cout << "Move " << moves << ": Move disk from A1 to A2" << std::endl;
      std::cout << "Move " << moves + 1 << ": Move disk from A2 to A3" << std::endl;
      std::cout << "Move " << moves + 2 << ": Move disk from A3 to A4" << std::endl;
      moves += 3;
    }
    else if( p_start == P3 && p_end == P2 ){
      std::cout << "Move " << moves << ": Move disk from A4 to A1" << std::endl;
      moves++;
    }
    else if( p_start == P2 && p_end == P1 ){
      std::cout << "Move " << moves << ": Move disk from A1 to D" << std::endl;
      moves++;
    }
      // }
  }

  void Move(int n, Position p_start, Position p_end);

  void MoveGeneralCase(int n, Position p_start, Position p_end) { 
    // General Cases
    if (p_start == P0 && p_end == P1) {
      Move(n - 1, P0, P2);
      Move(1, P0, P1);
      Move(n - 1, P2, P1);
    } 
    else if (p_start == P0 && p_end == P2) {
      Move(n, P0, P1);
      Move(n, P1, P2);
    } 
    else if (p_start == P1 && p_end == P2) {
      Move(n - 1, P1, P3);
      Move(1, P1, P2);
      Move(n - 1, P3, P2);
    } 
    else if (p_start == P2 && p_end == P1) {
      Move(n - 1, P2, P3);
      Move(1, P2, P1);
      Move(n - 1, P3, P1);
    } 
    else if (p_start == P1 && p_end == P3) {
      Move(n - 1, P1, P3);
      Move(1, P1, P2);
      Move(n - 1, P3, P1);
      Move(1, P2, P3);
      Move(n - 1, P1, P3);
    } 
    else if (p_start == P3 && p_end == P2) {
      Move(n - 1, P3, P1);
      Move(1, P3, P2);
      Move(n - 1, P1, P2);
    } 
    else if (p_start == P3 && p_end == P1) {
      Move(n - 1, P3, P1);
      Move(1, P3, P2);
      Move(n - 1, P1, P3);
      Move(1, P2, P1);
      Move(n - 1, P3, P1);
    } 
    else if (p_start == P2 && p_end == P3) {
      Move(n - 1, P2, P1);
      Move(1, P2, P3);
      Move(n - 1, P1, P3);
    }
  }

  void Move(int n, Position p_start, Position p_end){
    if( n == 0 ) {
      // Do nothing
    }
    else if( n == 1 && std::abs(p_start - p_end ) <= 1 ) {
      MoveBaseCases(p_start, p_end);
    }
    else {
      MoveGeneralCase(n, p_start, p_end);
    }
  }
}

int main(int argc, char** argv) {
  for(int n = 1; n <= 5; ++n) {
       std::cout << "Running n = " << n << " case ----------------" << std::endl;
      Move(n, hanoi::P0, hanoi::P1);
      hanoi::moves = 1;
      std::cout << "Finished n = " << n << " case -----------------\n\n" << std::endl;
  }
  
  return 0;
}