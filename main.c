#include <stdio.h>
#include "skiplist.h"

int main(){
    Skiplist* skiplist = create_skiplist();

    for(int i = 1; i <= 10; i++){
        insert(i, skiplist);
    }

    print_skiplist(skiplist);

    if(search(5, skiplist)){
        printf("achei\n");
    }
    remover(5, skiplist);
    print_skiplist(skiplist);
    return 0;
}

