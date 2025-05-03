#include "Student.c"
#include "Node.c"
#include "List.c"
#include "MacrosUse.c"

int main(){
    List* list_1 = createList();
    void* add_args1[2] = {list_1, createStudent("ivan", "ivanov", true, 22, "isp-206", 5, 1, 5)};
    list_1->add(add_args1);
    void* add_args2[2] = {list_1, createStudent("natasha", "ivanova", false, 22, "isp-206", 4, 4, 3)};
    list_1->add(add_args2);
    void* add_args3[2] = {list_1, createStudent("nikita", "dobrunych", true, 202, "isp-206", 5, 3, 4)};
    list_1->add(add_args3);
    list_1->print(list_1);

    printf("\n");

    list_1->save_json(list_1);
    list_1->save_bin(list_1);
    list_1->newMark(list_1);
    list_1->print(list_1);

    printf("\n");

    List* list_2 = createList();
    list_2->import_json_data(list_2);
    List* list_3 = createList();
    list_3->import_bin_data(list_3);

    printf("\n");

    list_2->print(list_2);
    printf("\n");
    list_3->print(list_3);

    printf("\n");
    printf("%d", sum(10, 2) * 2);

    printf("\n");
    Student* stud;
    printStudent(createNode(stud));
    
    return 0;
}