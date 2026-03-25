#include <iostream>
#include <string>


using namespace std;


struct Page{
string URL;
string title;
int accessTime[3];
Page* nxt;
Page* prev;

};

void Visit(Page** current, string url, string title, int h, int m, int s);
void Move(Page** current);
void Del(Page** current, Page** head);
void History(Page** head, Page** current);
void MemoMan(Page** head, Page** current);

int main()
{
    Page* current = nullptr;
    Page* head = nullptr;





    return 0;
}


void Visit(Page** current, string url, string Title, int h, int m, int s){

    if (*current == nullptr) {
        *current = new Page;
        (*current)->URL = url;
        (*current)->title = Title;
        (*current)->accessTime[0] = h;
        (*current)->accessTime[1] = m;
        (*current)->accessTime[2] = s;
        (*current)->nxt = nullptr;
        (*current)->prev = nullptr;
    }
    else {
        Page* newPage = new Page;
        newPage->URL = url;
        newPage->title = Title;
        newPage->accessTime[0] = h;
        newPage->accessTime[1] = m;
        newPage->accessTime[2] = s;

        newPage->prev = *current;
        newPage->nxt = nullptr;

        (*current)->nxt = newPage;

        *current = newPage;
    }

}

void Move(Page** current,string direct) {

    if (direct == "prev") {
        if ((*current)->prev != nullptr) {
            *current = (*current)->prev;
            cout << "you go previous you are now at: " << (*current)->title << "\n";
        }
        else {
            cout << "you are at first.\n";
        }
    }
    else if (direct == "next") {
        if ((*current)->nxt != nullptr) {
            *current = (*current)->nxt;
            cout << "you go next you are now at: " << (*current)->title << "\n";
        }
        else {
            cout << "it is end.\n";
        }
    }
    else {
        cout << "please only enter 'next' or 'prev' commands.";
    }

}


void Del(Page** current, Page** head) {

    if (*current == nullptr) {
        return;
    }

    Page* toDelete = *current;


    if (toDelete->prev != nullptr) {
        toDelete->prev->nxt = toDelete->nxt;
    }
    else {
        if (head != nullptr) {
            *head = toDelete->nxt;
        }
    }

    if (toDelete->nxt != nullptr) {
        toDelete->nxt->prev = toDelete->prev;
    }

    if (toDelete->prev != nullptr) {
        *current = toDelete->prev;
    }
    else {

        *current = toDelete->nxt;
    }

    delete toDelete;
}

void History(Page** head, Page** current) {
    if (head == nullptr) {
        cout << "history is empty";
        return;
    }

    Page* flag = head;

    while (flag != nullptr) {

        if (flag == current) {
            cout << "current: ";
        }

        cout << flag->title <<"  "<< flag->URL<<"  time:";

        for (int i = 0; i < 3; i++) {
            cout << temp->accessTime[i] << ":";
        }
            cout << endl;
            flag = flag->nxt;
    }
}

void MemoMan(Page** head, Page** current) {

    Page* flag = *head;
    while (flag != nullptr) {

        Page* nextNode = flag->nxt;


        delete flag;


        flag = nextNode;
    }
    *head = nullptr;
    *current = nullptr;

}
