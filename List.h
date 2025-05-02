#ifndef UNIC_LIST
#define UNIC_LIST

typedef struct List{
    Node* root;
    Node* end;

    void* (*print)(void* args);
    void* (*add)(void* args);
    void* (*swap)(void* args);
    void* (*sort)(void* args);
    void* (*newMark)(void* args);
    void* (*save_json)(void* args);
    void* (*import_json_data)(void* args);
    void* (*save_bin)(void* args);
    void* (*import_bin_data)(void* args);
}List;

List* createList();

#endif