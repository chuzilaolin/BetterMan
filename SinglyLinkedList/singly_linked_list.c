#include "singly_linked_list.h"

int main() {
    // 新建链表
    SinglyLinkedList *list = create__list();
    // 头插入
    printf("头插：%d\n", add_before_head(list, 0));
    printf("头插：%d\n", add_before_head(list, 1));
    printf("头插：%d\n", add_before_head(list, 2));
    // 尾插入
    // printf("头插：%d\n", add_behind_tail(list, 3));
    // printf("头插：%d\n", add_behind_tail(list, 4));
    // printf("头插：%d\n", add_behind_tail(list, 5));
    // // 指定索引插入
    // printf("索引插：%d\n", add_by_index(list, 11, 6));
    // printf("索引插：%d\n", add_by_index(list, 3, 6));
    // printf("索引插：%d\n", add_by_index(list, 5, 9));

    print_list(list);




    // 销毁
    destroy_list(list);
    return 0;
}

// 创建一个单向链表
SinglyLinkedList* create__list() {
    SinglyLinkedList *list = calloc(1, sizeof(SinglyLinkedList));
    if (list == NULL) { 
        puts("error：create__list()分配内存失败");
    }
    return list;
}
// 销毁一个单向链表
void destroy_list(SinglyLinkedList *list) {
    if (list != NULL) {
        Node *current = list->head;
        while (current) {
            Node *temp = current->next;
            free(current);
            current = temp;
        }
        free(list);
    }
}

// -------------- 增加数据操作 ---------------
// 从头部插入结点
bool add_before_head(SinglyLinkedList *list, Element val) {
    if (list == NULL) {
        puts("error：add_before_head()的参数list为空值");
        return false;
    }
    Node *temp = calloc(1, sizeof(Node));
    if (temp == NULL) {
        puts("error：add_before_head()分配内存失败");
        free(list);
        return false;
    }
    // 初始化临时结点
    temp->data = val;
    temp->next = list->head;
    // 更新链表信息
    list->head = temp;
    if (list->tail == NULL) { // 链表插入前为空，更新尾节点位置
        list->tail = temp;
    }
    list->size++;
    return true;
}
// 从尾部插入结点
bool add_behind_tail(SinglyLinkedList *list, Element val) {
    
    return true;
}
// 从指定索引位置插入结点
bool add_by_index(SinglyLinkedList *list, int idx, Element val) {

    return true;
}

// -------------- 查询数据操作 ---------------
// 根据下标查询数据（类似数组，第一个结点下标为0）
Node* get_by_idx(const SinglyLinkedList *list, int idx) {
    
    return NULL;
}
// 根据数据值查找数据
Node* get_by_data(const SinglyLinkedList *list, int idx) {

    return NULL;
}

// -------------- 删除数据操作 ---------------
// 从头部删除一个结点
bool delete_from_head(SinglyLinkedList *list) {

    return true;
}
// 从尾部删除一个结点
bool delete_from_tail(SinglyLinkedList *list) {

    return true;
}
// 删除某个值的结点（只删除匹配到的第一个）
bool delete_by_data(SinglyLinkedList *list, Element val) {

    return true;
}

// -------------- 其他操作 ---------------
// 打印链表
void print_list(const SinglyLinkedList *list) {
    if (list != NULL) {
        Node *current = list->head;
        while(current) {
            printf("%d->", current->data);
            current = current->next;
        }
        printf("\b\b  \n");
    }
}