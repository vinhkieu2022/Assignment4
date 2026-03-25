#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void display(struct node* head) {
    struct node* temp = head;
    if (head == NULL) {
        printf("Danh sach trong\n");
    } else {
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// Sửa 'void' thành 'struct node*'
struct node* addback(struct node* head, int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->next = NULL;
    
    if (head == NULL) {
        return newnode;
    } else {
        struct node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
        return head;
    }
}

struct node* find(struct node* head, int data) {
    struct node* temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp; // Tìm thấy! Trả về con trỏ trỏ tới node này
        }
        temp = temp->next; // Bước tiếp
    }
    return NULL; // Đi hết danh sách mà không thấy
}

struct node* delnode(struct node* head, struct node* pelement) {
    // Nếu danh sách trống hoặc node cần xóa không tồn tại
    if (head == NULL || pelement == NULL) return head;

    // Trường hợp 1: Node cần xóa chính là đầu danh sách
    if (head == pelement) {
        struct node* newHead = head->next; // Lưu lại phần còn lại của danh sách
        free(pelement);                    // Giải phóng node đầu
        return newHead;                    // Trả về head mới
    }

    // Trường hợp 2: Node cần xóa nằm ở giữa hoặc cuối
    struct node* temp = head;
    
    // Vòng lặp này để tìm node ĐỨNG NGAY TRƯỚC pelement
    while (temp != NULL && temp->next != pelement) {
        temp = temp->next;
    }

    // Nếu tìm thấy node đứng trước (lúc này temp đang trỏ tới node đứng trước)
    if (temp != NULL) {
        temp->next = pelement->next; // "Bắc cầu" bỏ qua pelement
        free(pelement);              // Tiêu hủy pelement
    }

    return head;
}

void freelist(struct node* head) {
    struct node* current = head;
    struct node* nextNode; // Biến tạm để "nhớ" đường

    while (current != NULL) {
        nextNode = current->next; // 1. Nhìn sang nhà tiếp theo và nhớ đường
        free(current);            // 2. Đập nhà (node) hiện tại
        current = nextNode;       // 3. Bước sang nhà tiếp theo đã nhớ
    }
}

int main() {
    struct node* head = NULL; // Khởi tạo danh sách trống

    printf("1. Them cac phan tu vao cuoi danh sach:\n");
    head = addback(head, 10);
    head = addback(head, 20);
    head = addback(head, 30);
    head = addback(head, 40);
    display(head); // Kết quả mong đợi: 10 -> 20 -> 30 -> 40 -> NULL

    printf("\n2. Tim phan tu co gia tri 30:\n");
    struct node* target = find(head, 30);
    if (target != NULL) {
        printf("Da tim thay: %d\n", target->data);
    }

    printf("\n3. Xoa phan tu 30 (o giua):\n");
    head = delnode(head, target);
    display(head); // Kết quả mong đợi: 10 -> 20 -> 40 -> NULL

    printf("\n4. Xoa phan tu 10 (head):\n");
    struct node* targetHead = find(head, 10);
    head = delnode(head, targetHead);
    display(head); // Kết quả mong đợi: 20 -> 40 -> NULL

    printf("\n5. Giai phong toan bo danh sach:\n");
    freelist(head);
    head = NULL; // Thói quen tốt: Gán head về NULL sau khi xóa sạch
    display(head); // Kết quả mong đợi: Danh sach rong.

    return 0;
}