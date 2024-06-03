// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "memory"
#include "../GameplayElemental/Elemental.h"

/**
 * 
 */
template<typename GameplayType>
 class ELEMENTALCROWN_API CustomNode {
 protected:
	 GameplayType* value = nullptr;
 public:
	 CustomNode<GameplayType>* next = nullptr;
	 CustomNode() : value(nullptr), next(nullptr) {}
	 CustomNode(GameplayType* val) : value(val), next(nullptr) {}
	 CustomNode(CustomNode<GameplayType>* node) : value(nullptr), next(node) {}
	 CustomNode(GameplayType* val, CustomNode<GameplayType>* node) : value(val), next(node) {}
	 virtual ~CustomNode() {
		 if (value) {
			 delete value;
			 value = nullptr;
		 }
	 }
	 GameplayType* GetValue() { return value; }
 };

 template<typename GameplayType>
class ELEMENTALCROWN_API CustomLinkedList
{
protected:
	CustomNode<GameplayType>* pHead = nullptr;
	CustomNode<GameplayType>* pTail = nullptr;
	int size = 0;
public:
	CustomLinkedList() : pHead(nullptr), pTail(nullptr) {}
	CustomLinkedList(CustomNode<GameplayType>* head, CustomNode<GameplayType>* tail) : pHead(head), pTail(tail) {}
	virtual ~CustomLinkedList() {
		ClearNodes();
	}

	CustomNode<GameplayType>* GetHead() { return pHead; }
	CustomNode<GameplayType>* GetTail() { return pTail; }
	int GetSize() { return size; }
	void AddTail(CustomNode<GameplayType>* node) {
		if (pHead) {
			pTail->next = node;
			pTail = pTail->next;
		}
		else {
			pHead = node;
			pTail = node;
		}
		++size;
	}
	void ClearNodes() {
		CustomNode<GameplayType>* current = pHead;
		while (current) {
			pHead = current->next;
			delete current;
			current = pHead;
		}
	}
	void RemoveTail() {
		if (pHead) {
			CustomNode<GameplayType>* prev = nullptr;
			CustomNode<GameplayType>* > ptr = pHead;
			while (0 == 0) {
				if (ptr == pTail) {
					pTail = prev;
					delete ptr;
					--size;
					return;
				}
				prev = ptr;
				ptr = ptr->next;
			}
		}
	}
};
