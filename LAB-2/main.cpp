#include <iostream>
#include <string>

using namespace std;

struct Node
{
	string title;
	Node* Next;
};


void Displaylist(Node* n);
void addfirst(Node** head, string newtitle);
void search(Node* Head, string title);

int main() {

	Node* head = nullptr;
	int choice = 0;
	string nsong;

	do
	{

		cout << "Musics" << endl << "1. Add" << endl << "2. Search" << endl << "3. List" << endl << "4.Exit" << endl << "enter a number:";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Please, enter the song title:";
			cin >> nsong;
			addfirst(&head, nsong);

			break;
		case 2:
			cout << "Please, enter the song title:";
			cin >> nsong;
			search(head, nsong);
			break;
		case 3:
			Displaylist(head);
			break;
		default:
			cout << "Please choose a menu number." << endl;


		}


	} while (choice != 4);

	return 0;

}

void Displaylist(Node* node) {

	if (node == NULL) {
		cout << " list is empty" << endl;
		return;
	}
	int i = 1;

	while (node != NULL) {

		cout << i << "." << node->title << endl;
		i++;
		node = node->Next;
	}
}

void addfirst(Node** Head, string newtitle) {
	Node* node = new Node;
	node->title = newtitle;
	node->Next = *Head;
	*Head = node;
}


void search(Node* Head, string title) {

	Node* temp = Head;
	int found = 0;


	while (temp != nullptr) {
		if (temp->title == title) {
			cout << "File found" << endl;
			found = 1;
			break;
		}
		temp = temp->Next;
	}
	if (found != 1) {
		cout << "File not found" << endl;
	}
}