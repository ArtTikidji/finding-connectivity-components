//
//  main.cpp
//  fathers_task
//
//  Created by Artem on 23/11/2019.
//  Copyright © 2019 Artem. All rights reserued.
//

#include <iostream>
#define MAX_K 10
using namespace std;

struct Tree_point {
    int me;
    int p;
    int cnt;
};

// так как аглоритм предназначен для построения остовного дерева,
// поэтому для дальнейшей работы по соеденению деревьев нам понадобится
// соединять их корни, а следубющая функция предназначена для поиска оных
int find_root(Tree_point *u_mass, Tree_point u){
    while (u.me != u.p)
        u = u_mass[u.p];
    return u.me;
}

// это что-то около конструктора в классах
void create_point(Tree_point *u, int i){
    u->me = i;
    u->p = i;
    u->cnt = 1;
}

// данная функция отвечает за добавление ребра к остовному дереву,
// следовательно и за объединение подграфов (если они в одной компоненте
// связности), это основная часть алгоритма Прима, с некоторыми модификациями
void union_sets(Tree_point *u_mass, int *u_all, pair<int, int> v){
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
    pair<int, int> *v;
    // чтение фходных данных из файла
    FILE *in_file;
    in_file = fopen("input.txt", "r");
    int arc_cnt, poitns_cnt;
    fscanf(in_file, "points count = %d", &poitns_cnt);
    fscanf(in_file, "\narcs count = %d", &arc_cnt);
    v = (pair<int, int> *)(calloc(arc_cnt, sizeof(pair<int, int>)));
    // граф представлен в виде списка ребер, что необходимо для алгоритма Прима
    // и занчительно сокращает объем хранимых данных
    for(int i = 0; i < arc_cnt; ++i)
        fscanf(in_file, "%d %d", &v[i].first, &v[i].second);
    fclose(in_file);
    // u_all - это классификация вершин, 0 - вершина изолирована
    // 1 - вершина является частью компоненты связности,
    // 2 - вершина является "корнем" компоненты связности и в информации о ней
    // хранится колличество вершин в компоненте связности
    int *u_all = (int*)calloc(poitns_cnt, sizeof(int));
    // u_mass - этот массив содержит структуры с ключивыми сведениями о вершинах
    // № вершины, "предок" и кол-во вершин копоненте связности (если вершина является)
    // корнем оной
    Tree_point *u_mass = (Tree_point *)calloc(poitns_cnt, sizeof(Tree_point));
    for(int i = 0; i < poitns_cnt; ++i)
        create_point(&u_mass[i], i); // не суди меня за этот говнокод =(
    // в классическом алгоритме Прима используется очередь с приоритетом
    // но нам это не нужно (хотя бы по тому, что граф не взвешан)
    for(int i = 0; i < arc_cnt; ++i)
        union_sets(u_mass, u_all, v[i]);
    
    int *k_cnt = (int *)calloc(MAX_K, sizeof(int)); // это массив с кол-вом компонент
    // связности (нидекс - размер, значение - кол-во)
    
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
