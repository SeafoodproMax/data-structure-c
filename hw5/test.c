//
// Created by 林勁博 on 2025/11/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test.h"
#include "test_interface.h"

void run_all_tests() {
    t_printHeap();
    // t_consolidate();
}

void t_printHeap() {
    FibNode node1, node2, node3;
    node1.value = 1;
    node1.degree = 0;
    node1.childCut = false;
    node1.parent = NULL;
    node1.leftSibling = &node3;
    node1.rightSibling = &node2;
    node1.children = NULL;

    node2.value = 2;
    node2.degree = 0;
    node2.childCut = false;
    node2.parent = NULL;
    node2.leftSibling = &node1;
    node2.rightSibling = &node3;
    node2.children = NULL;

    node3.value = 3;
    node3.degree = 0;
    node3.childCut = false;
    node3.parent = NULL;
    node3.leftSibling = &node2;
    node3.rightSibling = &node1;
    node3.children = NULL;


}
void t_consolidate() {

}
