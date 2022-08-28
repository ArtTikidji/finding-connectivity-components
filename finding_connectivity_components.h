//
//  finding_connectivity_components.h
//  finding_connectivity_components
//
//  Created by Artem on 26/08/2022.
//  Copyright © 2022 Artem. All rights reserved.
//

#ifndef finding_connectivity_components_h
#define finding_connectivity_components_h

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
    int my_root;
    int cnt;
} Tree_point;


Pair_int_int* read_grath_from_txt(char* file_path_name, int* points_cnt, int* arc_cnt);


//since the aglorithm is intended to build a spanning tree,
// we need to connect their roots,
// and the next function is designed to find them
int find_root(Tree_point *u_mass, Tree_point u);

// something like constructor in class
void init_point(Tree_point *u, int i);

// this function is adding edge to spanning tree/forest and merging
// subgraphs (if they are in one connectiviti componenet,
// this is the main part of Prim algorithm with some modifications
void union_sets(Tree_point *u_mass, Pair_int_int v);

Tree_point* points_classifier(int points_cnt, int arc_cnt, Pair_int_int *v);
int* components_calculator(int points_cnt, Tree_point* points_info);

int* execute(char* file_name_path);

#endif /* finding_connectivity_components_h */
