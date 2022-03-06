#include "logDebug.h"
#include "doComputation.h"
#include "max.h"

//int unresolvedFunc(char c);
//int doComputation(int a, double b){
//  return 22895;
//}


int main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  //int bad = unresolvedFunc('c');
  max(a, b);
  logDebug('!');
  return 0;
}
