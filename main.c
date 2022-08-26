//
//  main.cpp
//  finding-connectivity-components
//
//  Created by Artem on 23/11/2019.
//  Copyright © 2019 Artem. All rights reserued.
//

#include "finding_connectivity_components.h"

int main(int argc, const char * argu[]) {
    
    int arc_cnt, poitns_cnt;
    Pair_int_int *v = read_grath_from_txt("input.txt", &poitns_cnt, &arc_cnt);
    // u_all - points classification
    Tree_point *u_mass = points_classifier(poitns_cnt, arc_cnt, v);
    
    // array with counts of connectivity components with different size
    int *k_cnt = components_calculator(poitns_cnt, u_mass);
    
    for(int i = 1; i < MAX_K; ++i)
        printf("%d cnt = %d\n", i, k_cnt[i]);
    
    return 0;
}
