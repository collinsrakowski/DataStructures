#include <iostream>
#include "SortedLinkedList.h"
#include "ListNode.h"
#include "ItemType.h"
#include <string.h>
#include <stdio.h>

using namespace std;
// did not delete your code but for some reason it wasnt adding anything to a list at all.
SortedLinkedList::SortedLinkedList() { // DONE
    head = NULL;
}

SortedLinkedList::~SortedLinkedList() { // I think this works
    ListNode *curr;
    while (head != NULL) {
        curr = head;
        head = head -> next;
        delete curr;
    }
}

int SortedLinkedList::length() const { // DONE
    int len = 0;
    ListNode *leng = head;
    while (leng != NULL) {
        leng = leng -> next;
        len++;
    }
    return len;
}

void SortedLinkedList::deleteItem(ItemType item) {
    if (head == NULL) {
        cout << "You cannot delete from an empty list.\n";
        return;
    }

    bool keepSearching = true;
    ListNode *curr = head;
    ListNode *beh = head;
    while (keepSearching) {
        if (curr -> item.compareTo(item) == Comparison::EQUAL) {
            if (curr == head) {
                head = head -> next;
            } else {
                beh -> next = curr -> next;
            }
            delete curr;
            keepSearching = false;
        } else {
            if (curr -> next == NULL) {
                keepSearching = false;
                cout << "Item not found." << endl;
            } else {
                if (curr != head) {
                    beh = beh -> next;
                }
                curr = curr -> next;
            }
        }
    }
}

int SortedLinkedList::searchItem(ItemType item) {
    ListNode *curr = head;
    bool keepSearch = true;
    int index = -1;
    int len = length() - 2;
    while (keepSearch) {
        if (index > len) {
            index = -1;
            keepSearch = false;
        } else {
            index++;
            if (item.compareTo(curr -> item) == Comparison::EQUAL) {
                keepSearch = false;
            } else {
                curr = curr -> next;
            }
        }
    }
    return index;
}

void SortedLinkedList::insertItem(ItemType item) {
    ListNode* newNode = new ListNode(); // creates node
    newNode -> item = item; // sets item in node equal to param item
    newNode -> next = NULL;

    if (head == NULL) { // IF EMPTY
        head = newNode; // pointing head toward out new node
        currentPos = head;
        return;
    }
    bool keepSearching = true;
    ListNode *curr = head;
    ListNode *beh = head;
    while (keepSearching) {
        if (newNode -> item.compareTo(curr -> item) == Comparison::EQUAL) {
            cout << "Sorry. You cannot insert the duplicate item.\n";
            keepSearching = false;
        } else if (newNode -> item.compareTo(curr -> item) == Comparison::LESS) {
            if (curr == head) {
                newNode -> next = head;
                head = newNode;
                currentPos = head;
                keepSearching = false;
            } else {
                beh -> next = newNode;
                newNode -> next = curr;
                keepSearching = false;
            }
        } else {
            if (curr -> next == NULL) {
                curr -> next = newNode;
                keepSearching = false;
            } else {
                if (curr != head) {
                    beh = beh -> next;
                }
                curr = curr -> next;
            }
        }
    } // while
} // insert item

ItemType SortedLinkedList::GetNextItem() { // works
    if (length() == 0) {
        cout << "List is empty!" << endl;
        return head -> item;
    }
    if (currentPos == NULL) {
        cout << "End of the list has been reached!" << endl;
        currentPos = head;
    }
    ItemType local;
    local = currentPos -> item;
    currentPos = currentPos -> next;

    return local;
}

void SortedLinkedList::ResetList() {
    currentPos = head;
}

void SortedLinkedList::mergeList(SortedLinkedList &s2) { // doesnt crash now that we pass by ref!
    ListNode *l1 = head;
    
    while (l1 != NULL) { // supposed to check for matching first // does check for matching tho!
        ListNode *l2 = s2.head;
        while (l2 != NULL) {
            if (l1 -> item.compareTo(s2.GetNextItem()) == Comparison::EQUAL) {
                cout << "Sorry. You cannot insert the duplicate item.\n";
                return;
            }
            l2 = l2 -> next;
        }
        s2.ResetList();
        l1 = l1 -> next;
    }

    ListNode *curr = s2.head;
    while(curr != NULL) { // this needed to be curr not s2.head but now works
        insertItem(curr -> item);
        curr = curr -> next;
    } // while
} // merge List

void SortedLinkedList::deleteAltNodes() {
    if (head == NULL) {
        cout << "You cannot delete from an empty list.\n";
        return;
    }
    cout << "List before alternate delete: ";
    printLink();

    ListNode *del = head -> next;
    while (del != NULL) {
        ItemType t = del -> item;
        if (del -> next != NULL) {
            del = del -> next;
        }
        del = del -> next;
        deleteItem(t);
    }

    cout << "List after alternate delete: ";
    printLink();
}

void SortedLinkedList::intersection() {

}

void SortedLinkedList::printLink() { // DONE
    ListNode *temp = head;
    while (temp) {
        cout << temp -> item.getValue() << " ";
        temp = temp -> next;
    } // while
    cout << "" << endl;
}
