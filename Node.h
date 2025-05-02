#pragma once

typedef struct Node{
    Student* value;
    struct Node* next;

    void* (*print)(void* args);
}Node;

Node* createNode(struct Student* student);