#include <iostream>
using namespace std;

void instruction() {
	cout << "Для добавления элемента в очередь, введите 1\n";
	cout << "Для извлечения элемента из очереди, введите 2\n";
	cout << "Для подсчета количества элементов в очереди, введите 3\n";
	cout << "Для очистки всей очереди, введите 4\n";
	cout << "Для подсчета количества конкретного элемента в очереди, введите 5\n";
	cout << "Для удаления отрицательных элементов из очереди, введите 6\n";
	cout << "Для вставки перед каждым отрицательным элементом числа 1, введите 7\n";
	cout << "Для завершения работы программы, введите 8\n\n";
}

struct Node {
	int param = 0;
	Node* next = nullptr;
};

struct Queue {

	int counting = 0;
	Node* last = nullptr;
	Node* first = nullptr;

	int count() {
		return counting;
	}
	void queue(int value) {
		Node* node = new Node();
		node->param = value;
		if (count() == 0) { // При добавлении первого элемента
			last = node;
			first = last;
		}
		else { // При добавлении остальных элементов
			last->next = node;
			last = node;
		}
		counting++;
	}
	int unqueue() {
		if (count() == 0) {
			return 0;
		}
		if (first == last) { last = nullptr; } 
		Node* del = first;
		int ans = del->param;
		first = first->next;
		delete del;
		counting--;
		return ans;
	}
	void clear() {
		int kol = count();
		for (int i = 0; i < kol; i++) {
			Node* del = first;
			first = first->next;
			delete del;
			counting--;
		}
		last = nullptr;
	}
	int count(int value) {
		int ans = 0, iter = count();
		Node* node = first;
		for (int i = 0; i < iter; i++) {
			if (node->param == value) { ans++; }
			node = node->next;
		}
		return ans;
	}
	void removeNegative() {
		if (count() == 0) {
			return;
		}
		Node* node = first;
		Node* del;
		while (true) {
			del = node;
			last = node;
			if (node->next == nullptr) { break; }
			if (node->next->param < 0) {
				del = del->next;
				node->next = node->next->next;
				delete del;
				counting--;
			}
			else {
				node = node->next;
			}
		}
		if (first->param < 0) {
			node = first;
			if (first == last) { last = nullptr; }
			first = first->next;
			delete node;
			counting--;
		}
	}
	void insertBeforeNegative() {
		if (count() == 0) {
			return;
		}
		Node* node = first;
		if (node->param < 0) {
			Node* insert = new Node();
			insert->param = 1;
			insert->next = node;
			first = insert;
			counting++;
		}
		while (node != last) {
			if (node->next->param < 0) {
				Node* insert = new Node();
				insert->param = 1;
				insert->next = node->next;
				node->next = insert;
				node = node->next;
				counting++;
			}
			node = node->next;
		}
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	Queue queue;
	instruction();
	while (true) {
		cout << "\nВыберите функцию: ";
		int parametr;
		cin >> parametr;
		switch (parametr) {
			case 1:
				cout << "Введите число: ";
				int num;
				cin >> num;
				queue.queue(num);
				break;
			case 2:
				cout << "Удаленный элемент: " << queue.unqueue() << endl;
				break;
			case 3:
				cout << "Количество элементов: " << queue.count() << endl;
				break;
			case 4:
				queue.clear();
				cout << "Очередь очищена\n";
				break;
			case 5:
				cout << "Введите число: ";
				int number;
				cin >> number;
				cout << "Количество: " << queue.count(number) << endl;
				break;
			case 6:
				queue.removeNegative();
				break;
			case 7:
				queue.insertBeforeNegative();
				break;
			case 8:
				return 0;
			default:
				cout << "Неизвестная команда!\n";
		}
	}
}
