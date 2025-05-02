#include "Student.h"
#include "Node.h"
#include "List.h"
#include <malloc.h>
#include "cJSON.c"

void* print_List(void* args);
void* add_List(void* args);
void* swap_List(void* args);
void* sort_List(void* args);
void* new_mark(void* args);
void* save_json(void* args);
void* import_json_data(void* args);
void* save_bin(void* args);
void* import_bin_data(void* args);


List* createList(){
    List* list = (List*) malloc(sizeof(List));
    list->root = NULL;
    list->end = NULL;
    list->print = print_List;
    list->add = add_List;
    list->swap = swap_List;
    list->sort = sort_List;
    list->newMark = new_mark;
    list->save_json = save_json;
    list->import_json_data = import_json_data;
    list->save_bin = save_bin;
    list->import_bin_data = import_bin_data;
    return list;
}

void* print_List(void* args){
    List* list = (List*) args;
    for(Node* cur = list->root; cur != NULL; cur = cur->next) cur->print(cur);
}

void* add_List(void* args){
    void** raw_args = (void**) args;
    List* list = (List*) raw_args [0];
    Student* student = (Student*) raw_args [1];
    Node* node = createNode(student);
    if(list->root == NULL){
        list->root = node;
        list->end = node;
    }else{
        list->end->next = node;
        list->end = node;
    }
}

void* swap_List(void* args){
    void** raw_args = (void**) args;
    Node* first = (Node*) raw_args [0];
    Node* second = (Node*) raw_args [1];
    Student* tmp = first->value;
    first->value = second->value;
    second->value = tmp;
}

void* sort_List(void* args){
    List* list = (List*) args;
    for (Node* outer = list->root; outer != NULL; outer = outer->next){
        Node* cur = outer;
        for(Node* inner = outer; inner != NULL; inner = inner->next){
            if (cur->value->lesser(cur->value, inner->value)){
                cur = inner;
            }
        }
        void* swap_args[2] = {cur, outer};
        list->swap(swap_args);
    }
}

void* new_mark(void* args){
    List* list = (List*) args;
    for (Node* cur = list->root; cur != NULL; cur = cur->next){
        cur->value->phisikMark = cur->value->phisikMark + 2 <= 5 ?
         cur->value->phisikMark + 2 : cur->value->phisikMark + 1 <= 5 ?
          cur->value->phisikMark + 1 : cur->value->phisikMark;
    }
}

void* save_json(void* args){
    List* list = (List*) args;
    FILE *fjson = fopen("data.json", "w");
    cJSON *jsonObject = cJSON_CreateArray();
    for (Node* cur = list->root; cur != NULL; cur = cur->next){
        cJSON *json = cJSON_CreateObject();
        cJSON_AddStringToObject(json, "name", cur->value->firstName);
        cJSON_AddStringToObject(json, "fam", cur->value->lastName);
        cJSON_AddBoolToObject(json, "gender", cur->value->gender);
        cJSON_AddNumberToObject(json, "age", cur->value->age);
        cJSON_AddStringToObject(json, "group", cur->value->group);
        cJSON_AddNumberToObject(json, "math", cur->value->mathMark);
        cJSON_AddNumberToObject(json, "phisik", cur->value->phisikMark);
        cJSON_AddNumberToObject(json, "chem", cur->value->chemMark);
        cJSON_AddItemToArray(jsonObject, json);
    }
    char *json_str = cJSON_Print(jsonObject);
    fputs(json_str, fjson);
    fclose(fjson);
    cJSON_free(json_str); 
    cJSON_Delete(jsonObject); 
}

void* import_json_data(void* args){
    List* list = (List*) args;
    FILE *fjson = fopen("data.json", "r");
    if (fjson == NULL){
        printf("ERROR IMPORT! DATA DOESN'T EXIST\n");
        fclose(fjson);
        return (void*) 1;
    } 
    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), fjson);
    cJSON *root = cJSON_Parse(buffer);
    if (root == NULL){
        printf("ERROR!!! BUFFER EMPTY!!!");
        fclose(fjson);
        return (void*) 1;
    }
    cJSON* item = NULL;
    cJSON_ArrayForEach(item, root){
        cJSON *name = cJSON_GetObjectItem(item, "name");
        cJSON *fam = cJSON_GetObjectItem(item, "fam");
        cJSON *gender = cJSON_GetObjectItem(item, "gender");
        cJSON *age = cJSON_GetObjectItem(item, "age");
        cJSON *group = cJSON_GetObjectItem(item, "group");
        cJSON *math = cJSON_GetObjectItem(item, "math");
        cJSON *phisik = cJSON_GetObjectItem(item, "phisik");
        cJSON *chem = cJSON_GetObjectItem(item, "chem");
        void* add_args[2] = {list, createStudent(name->valuestring, fam->valuestring,
             (bool) gender->valueint, age->valueint, group->valuestring, 
             math->valueint, phisik->valueint, chem->valueint)};
        list->add(add_args);
    }
    fclose(fjson);
}

void* save_bin(void* args){
    List* list = (List*) args;
    FILE* file = fopen("data.bin", "wb");
    for(Node* cur = list->root; cur != NULL; cur = cur->next){
        fwrite(cur->value, sizeof(Student), 1, file);
    }
    fclose(file);
}

void* import_bin_data(void* args){
    List* list = (List*) args;
    FILE* file = fopen ("data.bin", "rb");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);
    int num_data = size / sizeof(Student);
    Student* students = (Student*) malloc(size);
    int read = fread(students, sizeof(Student), num_data, file);
    for(int i = 0; i < read; i++){
        void* arg[2] = {list, createStudent(students[i].firstName, students[i].lastName, students[i].gender,
            students[i].age, students[i].group, students[i].mathMark, students[i].phisikMark, students[i].chemMark)};
        list->add(arg);
    }
    fclose(file);
}