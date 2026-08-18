#include <iostream>

int main(){
    std::cout << "[Press Q to quit]" << std::endl;
    char tst = getchar();
    while(tst != 'q'){
        tst = getchar();
    }
    std::cout << "Quiting..." << std::endl;
    return 0;
}