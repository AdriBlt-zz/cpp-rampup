#pragma once
#include <string>

template <class T>
class LinkedList {
private:
	class Node {
	public:
		T m_value;
		Node* m_previous;
		Node* m_next;
		Node(T& value) : m_value(value) {}
	};

	Node* m_head;
	Node* m_tail;
	int m_length;

public:
	LinkedList() : 
		m_length(0),
		m_head(nullptr),
		m_tail(nullptr) {}

	int size() {
		return m_length;
	}

	void pushLast(T value);
	void pushFirst(T value);
	T peekFirst() const;
	T peekLast() const;
	T popFirst();
	T popLast();

	friend std::ostream& operator<< (std::ostream& out, const LinkedList<T>& list) {
		if (list.m_length == 0) {
			out << "[]";
		}
		else {
			out << "[ ";
			Node* node = list.m_head;
			for (int i = 0; i < list.m_length; i++) {
				if (i > 0) {
					out << ", ";
				}

				out << node->m_value;
				node = node->m_next;
			}

			out << " ]";
		}

		return out;
	}
};

template <class T>
void LinkedList<T>::pushLast(T value) {
	Node* node = new Node(value);

	if (m_length == 0) {
		m_head = node;
		m_tail = node;
	}
	else {
		m_tail->m_next = node;
		node->m_previous = m_tail;
		m_tail = node;
	}

	m_length++;
}

template <class T>
void LinkedList<T>::pushFirst(T value) {
	Node* node = new Node(value);

	if (m_length == 0) {
		m_head = node;
		m_tail = node;
	}
	else {
		m_head->m_previous = node;
		node->m_next = m_head;
		m_head = node;
	}

	m_length++;
}

template <class T>
T LinkedList<T>::peekFirst() const {
	if (m_length == 0) {
		throw;
	}

	return m_head->m_value;
}

template <class T>
T LinkedList<T>::peekLast() const {
	if (m_length == 0) {
		throw;
	}

	return m_tail->m_value;
}

template <class T>
T LinkedList<T>::popFirst() {
	if (m_length == 0) {
		throw;
	}

	T value = m_head->m_value;
	m_length--;
	if (m_length > 0) {
		m_head = m_head->m_next;
	}
	else {
		m_head = nullptr;
		m_tail = nullptr;
	}

	return value;
}

template <class T>
T LinkedList<T>::popLast() {
	if (m_length == 0) {
		throw;
	}

	T value = m_tail->m_value;
	m_length--;
	if (m_length > 0) {
		m_tail = m_tail->m_previous;
	}
	else {
		m_head = nullptr;
		m_tail = nullptr;
	}

	return value;
}
