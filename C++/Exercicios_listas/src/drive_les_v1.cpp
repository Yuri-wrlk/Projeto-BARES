// Para compilar: g++ -Wall -pedantic drive_les_v1.cpp les_v1.cpp -o drive_les_v1

#include "les_v1.h"
#include <iostream>
using std::cout;


int main ( void ) {
    SNPtr pHead = NULL;// nullptr;
    int val;
    SNPtr toBeFound = nullptr;

    pushFront( pHead, 1 );
    pushFront( pHead, 1792 );
    pushFront( pHead, 959723 );
    pushFront( pHead, 871274 );
    pushFront( pHead, 12 );


    std::cout << "A lista atual é:" << std::endl;
    print(pHead);

    std::cout << "\nDeletando a lista..." << std::endl;

    clear(pHead);

    std::cout << "\nO tamanho da lista é " << length(pHead) << std::endl;

    std::cout << "\nA lista atual é:" << std::endl;
    print(pHead);

    pushBack( pHead, 1982 );
    pushBack( pHead, 12 );
    pushBack( pHead, 13 );
    pushBack( pHead, 198 );
    pushBack( pHead, 109 );

    std::cout << "A lista atual é:" << std::endl;
    print(pHead);

    std::cout << "Removendo o primeiro elemento da lista..." << std::endl;

    popFront (pHead, val);
    std::cout << "O primeiro elemento foi removido e era " << val << std::endl;

    std::cout << "A lista atual é:" << std::endl;
    print(pHead);

    std::cout << "Removendo o último elemento da lista..." << std::endl;
    popBack (pHead, val);
    std::cout << "O último elemento foi removido e era " << val << std::endl;

    std::cout << "A lista atual é:" << std::endl;
    print(pHead);

    toBeFound = find(pHead, 198);

    std::cout << "\nInserindo elemento na lista..." << std::endl;
    insert(pHead, toBeFound, 45);

    std::cout << "\nA lista atual é:" << std::endl;
    print(pHead);

    std::cout << "\nRemovendo elemento na lista..." << std::endl;
    toBeFound = find(pHead, 13);
    remove(pHead, toBeFound, val);
    std::cout << "O elemento removido foi: " << val << std::endl;

    std::cout << "\nA lista atual é:" << std::endl;
    print(pHead);

    cout << "\n\n>>> Normal exiting...\n";
    return EXIT_SUCCESS;
}
