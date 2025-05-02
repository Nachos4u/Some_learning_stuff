#include "Student.h"
#include "Node.h"
#include <malloc.h>

void* printNode(void* args);

Node* createNode(Student* student){
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = student;
    node->next = NULL;
    node->print = printNode;
    return node;
};

void* printNode(void* args){
    Node* node = (Node*) args;
    node->value->print(node->value);
}