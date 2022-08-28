//
//  executor.c
//  connectivi_graph
//
//  Created by Artem on 26/08/2022.
//  Copyright © 2022 Artem. All rights reserved.
//

#include "finding_connectivity_components.h"


Pair_int_int* read_grath_from_txt(const char* file_path_name, int* points_cnt, int* arc_cnt){
    Pair_int_int *v;
    
    FILE *in_file = fopen(file_path_name, "r");
    fscanf(in_file, "points count = %d", points_cnt);
    fscanf(in_file, "\narcs count = %d", arc_cnt);
    v = (Pair_int_int *)(calloc(*arc_cnt, sizeof(Pair_int_int)));
    // graph is represented as a list of edges, which is necessary for Prim algorithm
    // and significantly reduces the amount of stored data
    for(int i = 0; i < *arc_cnt; ++i)
        fscanf(in_file, "%d %d", &v[i].first, &v[i].second);
    fclose(in_file);
    return v;
}


int find_root(Tree_point *u_mass, Tree_point *u){
    while (u->me != u->my_root)
        u = u_mass + u->my_root;
    return u->me;
}

void init_point(Tree_point *u, int i){
    u->me = i;
    u->my_root = i;
    u->cnt = 1;
}

void union_sets(Tree_point *u_mass, Pair_int_int v){
    int r1, r2;
    r1 = find_root(u_mass, u_mass + v.first);
    r2 = find_root(u_mass, u_mass + v.second);
    if(r1 == r2)
        return;
    Tree_point* u1 = u_mass + r1;
    Tree_point* u2 = u_mass + r2;
    u1->my_root = u2->me;
    u2->cnt += u1->cnt;
}

Tree_point* points_classifier(int points_cnt, int arc_cnt, Pair_int_int *v){
    Tree_point *u_mass = (Tree_point *)calloc(points_cnt, sizeof(Tree_point));
    for(int i = 0; i < points_cnt; ++i) {
        init_point(&u_mass[i], i);
    }
    // the ordered queue is used in classical Prim algorithm
    // but in this case it is not necessarily
    for(int i = 0; i < arc_cnt; ++i)
        union_sets(u_mass, v[i]);
    return u_mass;
}

int* components_calculator(int points_cnt, Tree_point* points_info){
    int *k_cnt = (int *)calloc(MAX_K, sizeof(int));
    
    for(int i = 0; i < points_cnt; ++i){
        if((points_info[i].my_root == points_info[i].me) && (points_info[i].cnt > 1)){
            ++k_cnt[points_info[i].cnt];
        }
        if((points_info[i].my_root == points_info[i].me) && (points_info[i].cnt == 1)){
            ++k_cnt[1];
        }
    }
    return k_cnt;
}

int* execute(char* file_name_path){
    int arc_cnt, poitns_cnt;
    Pair_int_int *v = read_grath_from_txt(file_name_path, &poitns_cnt, &arc_cnt);
    // u_mass - points description
    Tree_point *u_mass = points_classifier(poitns_cnt, arc_cnt, v);
    
    // array with counts of connectivity components with different size
    int *k_cnt = components_calculator(poitns_cnt, u_mass);
    return k_cnt;
}
