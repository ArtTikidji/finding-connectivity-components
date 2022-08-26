//
//  main.cpp
//  finding-connectivity-components
//
//  Created by Artem on 23/11/2019.
//  Copyright © 2019 Artem. All rights reserued.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_K 10

typedef struct Pair_int_int {
    int first;
    int second;
} Pair_int_int;

// information about connectivity component that point belongs
// number of point, root point, size of connectivity component if point is root
typedef struct Tree_point {
    int me;
    int p;
    int cnt;
} Tree_point;


//since the aglorithm is intended to build a spanning tree,
// we need to connect their roots,
// and the next function is designed to find them
int find_root(Tree_point *u_mass, Tree_point u){
    while (u.me != u.p)
        u = u_mass[u.p];
    return u.me;
}

// something like constructor in class
void create_point(Tree_point *u, int i){
    u->me = i;
    u->p = i;
    u->cnt = 1;
}

// this function is adding edge to spanning tree/forest and merging
// subgraphs (if they are in one connectiviti componenet,
// this is the main part of Prim algorithm with some modifications
void union_sets(Tree_point *u_mass, int *u_all, Pair_int_int v){
    int r1, r2;
    r1 = find_root(u_mass, u_mass[v.first]);
    r2 = find_root(u_mass, u_mass[v.second]);
    if(r1 == r2)
        return;
    Tree_point u1 = u_mass[r1];
    Tree_point u2 = u_mass[r2];
    u1.p = u2.me;
    u2.cnt += u1.cnt;
    u_all[u2.me] = 2;
    u_all[u1.me] = 1;
    u_mass[r1] = u1;
    u_mass[r2] = u2;
}

int main(int argc, const char * argu[]) {
    Pair_int_int *v;
    // чтение фходных данных из файла
    FILE *in_file;
    in_file = fopen("input.txt", "r");
    int arc_cnt, poitns_cnt;
    fscanf(in_file, "points count = %d", &poitns_cnt);
    fscanf(in_file, "\narcs count = %d", &arc_cnt);
    v = (Pair_int_int *)(calloc(arc_cnt, sizeof(Pair_int_int)));
    // graph is represented as a list of edges, which is necessary for Prim algorithm
    // and significantly reduces the amount of stored data
    for(int i = 0; i < arc_cnt; ++i)
        fscanf(in_file, "%d %d", &v[i].first, &v[i].second);
    fclose(in_file);
    // u_all - points classification
    // 0 - point isalated
    // 1 - point is a part of connectivity component
    // 2 - pint is a root of connectivity component
    int *u_all = (int*)calloc(poitns_cnt, sizeof(int));
    // u_mass - array with information of connectivity component
    // to wich point belongs
    Tree_point *u_mass = (Tree_point *)calloc(poitns_cnt, sizeof(Tree_point));
    for(int i = 0; i < poitns_cnt; ++i)
        create_point(&u_mass[i], i); // не суди меня за этот говнокод =(
    // the ordered queue is used in classical Prim algorithm
    // but in this case it is not necessarily
    for(int i = 0; i < arc_cnt; ++i)
        union_sets(u_mass, u_all, v[i]);
    
    // array with counts of connectivity components with different size
    int *k_cnt = (int *)calloc(MAX_K, sizeof(int));
    
    for(int i = 0; i < poitns_cnt; ++i){
        if(u_all[i] == 2)
            ++k_cnt[u_mass[i].cnt];
        if(u_all[i] == 0)
            ++k_cnt[1];
    }
    
    for(int i = 1; i < MAX_K; ++i)
        printf("%d cnt = %d\n", i, k_cnt[i]);
    
    return 0;
}
