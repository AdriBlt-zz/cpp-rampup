#include "pch.h"
#include "LinkedList.h"
#include <string>
/*
template <class T>
void LinkedList<T>::pushLast(T value) {
	Node<T>* node = new Node<T>(value);

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
	Node<T>* node = new Node<T>(value);

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

	return value;
}

template <class T>
std::string LinkedList<T>::toString() const {
	std::string output = "";
	Node<T>* node = m_head;
	for (int i = 0; i < m_length; i++) {
		if (output.length() > 0) {
			output += ",";
		}

		output += node->m_value;
		node = node->m_next;
	}

	return "[" + output + "]";
}
*/