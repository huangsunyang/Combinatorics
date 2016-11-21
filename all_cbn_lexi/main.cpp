//
//  main.cpp
//  combination
//
//  Created by huangsunyang on 11/21/2016.
//  Copyright © 2016年 huangsunyang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void print_all_combination(vector<int> vec, int r) {
    sort(vec.begin(), vec.end());
    if (r > vec.size()) {   //r must <= n
        return;
    } else if (r == vec.size()) {
        for_each(vec.begin(), vec.end(), [](int i){printf("%d ", i);});
        putchar('\n');
        return;
    }
    vector<int> choose(vec.begin(), vec.begin() + r); //put the first r elements in "choose"
    vector<int> left(vec.begin() + r, vec.end());       //others in "left"
    bool flag = false;                   //determine when to end the loop
    while (!flag) {
        //print one combination
        for_each(choose.begin(), choose.end(), [](int i){printf("%d ", i);});
        putchar('\n');
        sort(left.begin(), left.end());    //sort "left"
        int max = left.back();             // pick the max of left
        flag = true;
        //search from the back of "choose"
        for (int i = int(choose.size()) - 1; i >= 0; i--) {
            //if there is one element in ‘left’ is bigger than one element in choose
            if (choose[i] < max) {
                flag = false;
                //swap the element in 'choose' with the min in 'left' that is bigger than it
                auto pos = find_if(left.begin(), left.end(),
                                   [&choose, i](int n){return n > choose[i];});
                std::swap(*pos, choose[i]);
                //for the elements behind it, just find the origin elments behind it
                for (int k = i + 1; k < choose.size(); k++) {
                    auto pos2 = find(vec.begin(), vec.end(), choose[k - 1]);
                    if (choose[k] != *(pos2 + 1) ) {
                        std::swap(choose[k],
                                  *find(left.begin(), left.end(), *(pos2 + 1)));
                    }
                }
                break;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    vector<int> vec = {1,4,9,15, 24, 41, 52};
    print_all_combination(vec, 4);
    return 0;
}
