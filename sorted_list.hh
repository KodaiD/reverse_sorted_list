#include <cstdint>

struct Node {
    std::uint32_t ts;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(std::uint32_t ts, Node* next, Node* prev)
        : ts(ts), next(next), prev(prev) {}
    Node(std::uint32_t ts) : ts(ts) {}
};

class ReverseSortedList {
   private:
    Node* head = nullptr;
    Node* tail = nullptr;
    std::uint32_t size = 0;

   public:
    ReverseSortedList() {}

    void insert(Node* new_node) {
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            Node* cur = head;
            while (cur != nullptr && cur->ts > new_node->ts) {
                cur = cur->next;
            }
            if (cur == nullptr) {
                // insert at tail
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            } else {
                if (cur->prev == nullptr) {
                    // insert at head
                    head = new_node;
                    cur->prev = new_node;
                    new_node->next = cur;
                } else {
                    // insert before cur
                    cur->prev->next = new_node;
                    new_node->prev = cur->prev;
                    cur->prev = new_node;
                    new_node->next = cur;
                }
            }
        }
        size++;
    }

    Node* remove(std::uint32_t ts) {
        Node* cur = head;
        while (cur != nullptr && cur->ts != ts) {
            cur = cur->next;
        }
        if (cur == nullptr) {
            // not found
            return nullptr;
        } else {
            if (cur->prev == nullptr) {
                // remove head
                if (size == 1) {
                    head = nullptr;
                    tail = nullptr;
                } else {
                    head = cur->next;
                    head->prev = nullptr;
                }
            } else {
                if (cur->next != nullptr) {
                    // remove cur
                    cur->prev->next = cur->next;
                    cur->next->prev = cur->prev;
                } else {
                    // remove tail
                    tail = cur->prev;
                    tail->next = nullptr;
                }
            }
            size--;
            return cur;
        }
    }

    std::uint32_t get_size() const { return size; }

    Node* get_head() const { return head; }

    Node* get_tail() const { return tail; }

    bool is_empty() const { return size == 0; }
};