#pragma once
// declaring it with template so ican use it with any data type
template <typename T>
class node {
public:
	node(T data);
	T info;
	node *next;
};

template <typename T>
node<T>::node(T data) {
	this->info = data;
	this->next = nullptr;
}

template <typename T>
class linked_LS{
public:
	linked_LS(){
		head = nullptr;
	}
	void insert_S(T);
	void insert_Start(T);
	void print();
	friend std::ostream& operator<<(std::ostream& out, linked_LS<T>& ls){
		node<T> *temp = ls.head;

		// Check for empty list
		if (ls.head == nullptr) {
			out << "List empty" << std::endl;
			return out;
			}

		// Traverse the list
		while (temp != nullptr) {
		out << temp->info << " ";
		temp = temp->next;
		}
		return out;
}

private:
	node<T> *head;
};

template <typename T>
void linked_LS<T>::insert_S(T data){
	node<T> *new_node = new node<T>(data);
	if (head == nullptr) {
		head = new_node;
		return;
	}

	node<T> *P = head;
	node<T> *temp;
	while (data > P->info && P->next != nullptr) {
		temp = P;
		P = P->next;	
	}
	if (P->next == nullptr) {
		P->next = new_node;
	}
	else {
		temp->next = new_node;
		new_node->next = P;
	}
}


template <typename T>
void linked_LS<T>::insert_Start(T data){
	node<T> *new_node = new node<T>(data);
	if (head == nullptr) {
		head = new_node;
		return;
	}
	new_node->next = this->head;
	this->head = new_node;
}

template <typename T>
void linked_LS<T>::print() { 
	node<T> *temp = head;
    
	// Check for empty list
	if (head == nullptr) {
	std::cout << "List empty" << std::endl;
	return;
	}

	// Traverse the list
	while (temp != nullptr) {
	std::cout << temp->info << " ";
	temp = temp->next;
	}
}
