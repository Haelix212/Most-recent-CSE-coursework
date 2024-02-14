/*
 * Copyright ©2024 Alex Hansen.  All rights reserved. No use, copying, 
 * distribution, or modification is permitted without prior written consent.
 * Copyrights for third-party components of this work must be honored.
 * 
 * ahansen4@uw.edu
 */

#include <iostream>  // for cout, cin
#include <cstdlib>   // for EXIT_FAILURE, EXIT_SUCCESS

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]) {
    int input, i;

    cout << "Which positive integer would you like me to factorize? ";
    if (!(cin >> input)) {
        cout << "Input could not be understood, shutting down." << endl;
        return EXIT_FAILURE;
    }

    for (i = 1; i <= input; i++) {
        if (input % i == 0) {
            cout << i << " ";
        }
    }
    cout << endl;

    return EXIT_SUCCESS;
}
