//
//  main.cpp
//  finding-connectivity-components
//
//  Created by Artem on 23/11/2019.
//  Copyright © 2019 Artem. All rights reserued.
//

#include "../include/finding_connectivity_components.h"

int main(int argc, const char * argu[]) {
    
    int *k_cnt = finding_connectivity_components("test/input.txt");
    
    for(int i = 1; i < MAX_K; ++i)
        printf("%d cnt = %d\n", i, k_cnt[i]);
    free(k_cnt);
    return 0;
}
