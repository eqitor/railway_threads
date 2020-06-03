#include <stdlib.h>
#include "RandomIntGenerator.h"

int RandomIntGenerator::generate(int low, int up){

    return rand() % (up-low) + low;

}