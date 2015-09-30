#ifndef  ARBOL23
#define	ARBOL23

#include <utility>
#include <iostream>
#include <exception>

using namespace std;

template<typename T> class Arbol23;

class duplicatekey : public exception
{
public:

	virtual const char* what() const throw()
	{
		return "Attempting to insert duplicate key ";
	}
};

template<typename K> class Arbol23
{
public:
	class Node23
	{
		friend class Arbol23<K>;
		friend class Node34;
		Node23(bool three_node = false);

		Node23& operator=(Node23& rhs);
		Node23(K key);

		Node23(K small, K large);
		Node23(K small, Node23 *pParent, Node23 *pleftChild, Node23 *prightChild);
		Node23(const Node23& n);

		Node23& makeTwoNode(K value, Node23 *pParent, Node23 *left, Node23 *right);

		bool isLeafNode();
		bool isThreeNode();

		void setThreeNode(bool flag);

		K getSmallValue() { return keys[0]; }
		K getLargeValue() { return keys[1]; }
		Node23 *children[3];

		Node23 *parent;

		K keys[2];

		bool isThreeNodeFlag;
	};
	typedef Node23 Node;

protected:
	class Node34
	{

		friend class Arbol23<K>;
		K keys[3];

		Arbol23<K>::Node23 *leftChild;
		Arbol23<K>::Node23 *leftMiddleChild;
		Arbol23<K>::Node23 *rightMiddleChild;
		Arbol23<K>::Node23 *rightChild;
	public:
		Node34(Node23 *threeNode, K new_value, Arbol23<K>::Node23 *leftChildOfNewValue = nullptr, Arbol23<K>::Node23 *rightChildOfNewValue = nullptr);
		K  getSmallValue() { return keys[0]; }
		K  getMiddleValue() { return keys[1]; }
		K  getLargeValue() { return keys[2]; }

		Arbol23<K>::Node23 *getLeftChild() { return leftChild; }
		Arbol23<K>::Node23 *getLeftMiddleChild() { return leftMiddleChild; }
		Arbol23<K>::Node23 *getRightMiddleChild() { return rightMiddleChild; }
		Arbol23<K>::Node23 *getRightChild() { return rightChild; }
	};
	Node23 *root;

	bool DoSearch(K key, Node23 *root, Node23 *&location);

	Node23 *Split(Node23 *p, K key, Node23 *pLeftChildOfNewKey = nullptr, Node23 *pRightChildOfNewKey = nullptr);

	template<typename Functor>
	void DoTraverse(Functor f, Node23 *root);
	void DestroyTree(Node23 *root);

	Node23 *FindNextLargest(K key, Node23 *location);
	void fix(Node23 *location, Node23 *pAdoptee = nullptr);
	bool Redistribute(Node23 *node, int& situation_designator);
	void ReassignChildren(Node23 *node, Node23* pChildOfNode, int situation);

public:
	Arbol23() { root = nullptr; }
	~Arbol23();
	template<typename Functor> void Traverse(Functor f);
	bool Search(K key, Node23 *&location);
	bool remove(K key, Node23 *location = nullptr);

	Arbol23<K>::Node23 *insert(K key, Node23 *location = nullptr) throw(duplicatekey);
};

template<typename K> inline
bool Arbol23<K>::Node23::isLeafNode()
{
	return !children[0] ? true : false;
}

template<typename K> inline
bool Arbol23<K>::Node23::isThreeNode()
{
	return this->isThreeNodeFlag;
}

template<typename K> inline
void Arbol23<K>::Node23::setThreeNode(bool flag)
{
	this->isThreeNodeFlag = flag;
}

template<typename K> inline
Arbol23<K>::Node23::Node23(K key) : isThreeNodeFlag(false)
{
	keys[0] = key;
	children[0] = 0;
	children[2] = 0;
}

template<typename K> inline
Arbol23<K>::Node23::Node23(bool three_node) : isThreeNodeFlag(three_node), parent(0)
{
	children[0] = 0;
	children[1] = 0;
}

template<typename K> inline
Arbol23<K>::Node23::Node23(K small, K large) : isThreeNodeFlag(false), parent(0)
{
	keys[0] = small;
	keys[1] = large;
	children[0] = 0;
	children[2] = 0;
}

template<typename K> inline Arbol23<K>::Node23::Node23(K small, Arbol23<K>::Node23 *pParent, Arbol23<K>::Node23 *pleftChild, Arbol23<K>::Node23 *prightChild) : isThreeNodeFlag(false), parent(pParent)
{
	keys[0] = small;
	children[0] = pleftChild;
	children[2] = prightChild;
}

template<typename K> inline Arbol23<K>::Node23::Node23(const Arbol23<K>::Node23& n) : isThreeNodeFlag(n.isThreeNodeFlag), parent(n.parent)
{
	children[0] = n.children[0];
	children[2] = n.children[2];
}


template<typename K> typename
Arbol23<K>::Node23& Arbol23<K>::Node23::makeTwoNode(K value, Arbol23<K>::Node23 *pParent, Arbol23<K>::Node23 *left, Arbol23<K>::Node23 *right)
{
	keys[0] = value;
	children[0] = left;
	children[2] = right;
	isThreeNodeFlag = false;
	parent = pParent;
	return *this;
}

template<typename K>  inline Arbol23<K>::~Arbol23()
{
	DestroyTree(root);
}

template<typename K> void Arbol23<K>::DestroyTree(Node23 *p)
{
	if (p == nullptr) {
		return;
	}

	if (p->isThreeNode())
	{
		DestroyTree(p->children[0]);
		DestroyTree(p->children[1]);
		DestroyTree(p->children[2]);
		delete p;

	}
	else
	{

		DestroyTree(p->children[0]);
		DestroyTree(p->children[2]);

		delete p;
	}
}

template<typename K> template<typename Functor>  inline
void Arbol23<K>::Traverse(Functor f)
{
	return DoTraverse(f, root);
}

template<typename K> template<typename Functor>
void Arbol23<K>::DoTraverse(Functor f, Node23 *p)
{
	if (p == nullptr)
	{
		return;
	}

	if (p->isThreeNode())
	{
		DoTraverse(f, p->children[0]);
		f(p->keys[0]);
		DoTraverse(f, p->children[1]);
		f(p->keys[1]);
		DoTraverse(f, p->children[2]);
	}
	else
	{
		DoTraverse(f, p->children[0]);
		f(p->keys[0]);
		DoTraverse(f, p->children[2]);
	}
}

template<typename K> bool
Arbol23<K>::Search(K key, Node23 *&location)
{
	if (root == nullptr)
	{
		location = nullptr;
		return false;
	}
	else
	{
		return DoSearch(key, root, location);
	}
}

template<typename K>
bool Arbol23<K>::DoSearch(K key, Node23 *current, Node23 *&location)
{
	bool bRc;
	if (current->keys[0] == key || (current->isThreeNode() && current->keys[1] == key))
	{
		location = current;
		return true;
	}
	else if ((current->isLeafNode()))
	{
		location = current;
		return false;
	}
	else if (current->isThreeNode())
	{
		if (key < current->keys[0])
		{
			bRc = DoSearch(key, current->children[0], location);
		}
		else if (key < current->keys[1])
		{
			bRc = DoSearch(key, current->children[1], location);
		}
		else
		{
			bRc = DoSearch(key, current->children[2], location);
		}
	}
	else
	{
		if (key < current->keys[0])
		{
			bRc = DoSearch(key, current->children[0], location);
		}
		else
		{
			bRc = DoSearch(key, current->children[2], location);
		}
	}
	return bRc;
}

template<typename K> typename
Arbol23<K>::Node23 *Arbol23<K>::insert(K key, Arbol23<K>::Node23 *location)  throw(duplicatekey)
{
	if (root == nullptr)
	{
		root = new Node23(key);
		return root;
	}

	if (location == nullptr || !location->isLeafNode())
	{
		Node23 *leaf;
		bool bRc = DoSearch(key, root, leaf);
		return insert(key, leaf);
	}

	Node23 *result = nullptr;

	if (!location->isThreeNode())
	{
		result = location;
		if (key > location->keys[0])
		{
			location->keys[1] = key;
			location->setThreeNode(true);

		}
		else if (key < location->keys[0])
		{
			location->keys[1] = location->keys[0];
			location->keys[0] = key;
			location->setThreeNode(true);
		}
		else
		{
			throw duplicatekey();
		}

	}
	else
	{
		result = Split(location, key);
	}

	return result;
}

template<typename K> typename Arbol23<K>::Node23* Arbol23<K>::Split(Node23 *location, K new_key, Node23 *pLeftChildOfNewKey, Node23 *pRightChildOfNewKey)
{
	Node23* parent = nullptr;

	bool isLeaf = location->isLeafNode();
	bool bRootIsNew = false;

	if (location == root)
	{
		parent = new Node23;
		bRootIsNew = true;
	}
	else
		parent = location->parent;

	Node34 node34(location, new_key, pLeftChildOfNewKey, pRightChildOfNewKey);
	Node23 *pSmallest = new Node23(node34.getSmallValue(), parent, node34.getLeftChild(), node34.getLeftMiddleChild());
	location->makeTwoNode(node34.getLargeValue(), parent, node34.getRightMiddleChild(), node34.getRightChild());
	Node23 *pLargest = location;
	if (!isLeaf)
	{
		node34.getLeftChild()->parent = pSmallest;
		node34.getLeftMiddleChild()->parent = pSmallest;
		node34.getRightMiddleChild()->parent = pLargest;
		node34.getRightChild()->parent = pLargest;
	}

	K middle = node34.getMiddleValue();

	if (bRootIsNew)
	{
		parent->keys[0] = middle;
		parent->children[0] = pSmallest;
		parent->children[2] = pLargest;
		root = parent;
	}
	else if (parent->isThreeNode())
	{
		Split(parent, middle, pSmallest, pLargest);

	}
	else
	{
		parent->setThreeNode(true);
		if (middle < parent->keys[0])
		{
			parent->keys[1] = parent->keys[0];
			parent->keys[0] = middle;
			parent->children[0] = pSmallest;
			parent->children[1] = pLargest;
		}
		else
		{
			parent->keys[1] = middle;
			parent->children[1] = pSmallest;
		}
	}

	return parent;
}

template<typename K> bool
Arbol23<K>::remove(K key, Node23 *location)
{
	if (location == nullptr)
	{
		bool bFound = DoSearch(key, root, location);

		if (bFound == false)
		{
			return false;
		}

		bool bRc = remove(key, location);
		return bRc;

	}
	else if (key != location->keys[0] && key != location->keys[1])
	{
		return false;
	}
	Node23 *leafNode = nullptr;
	bool isInternalNode = !location->isLeafNode();

	if (isInternalNode)
	{
		leafNode = FindNextLargest(key, location);
		swap(location->keys[0], leafNode->keys[0]);
	}
	else
		leafNode = location;

	if (leafNode->isThreeNode())
	{
		if (key == leafNode->keys[0])
			leafNode->keys[0] = leafNode->keys[1];

		leafNode->setThreeNode(false);
	}
	else
		fix(leafNode);

	return true;
}
template<typename K> typename Arbol23<K>::Node23 *Arbol23<K>::FindNextLargest(K key, Arbol23<K>::Node23 *location)
{
	Node23 *next = nullptr;

	if (location->isThreeNode() && location->keys[0] == key)
		next = location->children[1];
	else
		next = location->children[2];
	while (!next->isLeafNode())
		next = next->children[0];

	return next;
}

template<typename K> bool Arbol23<K>::Redistribute(Node23 *node, int& situation)
{
	bool bRc = true;
	Node23 *parent = node->parent;

	if (parent->isThreeNode()) {
		if (node == parent->children[0]) {
			if (parent->children[1]->isThreeNode()) {
				node->keys[0] = parent->keys[0];
				parent->keys[0] = parent->children[1]->keys[0];
				parent->children[1]->keys[0] = parent->children[1]->keys[1];
				parent->children[1]->setThreeNode(false);

				situation = 1;

			}
			else if (parent->children[2]->isThreeNode()) {
				node->keys[0] = parent->keys[0];
				parent->keys[0] = parent->children[1]->keys[0];

				parent->children[1]->keys[0] = parent->keys[1];
				parent->keys[1] = parent->children[2]->keys[0];
				parent->children[2]->keys[0] = parent->children[2]->keys[1];
				parent->children[2]->setThreeNode(false);
				situation = 2;

			}
			else {
				bRc = false;
			}

		}
		else if (node == parent->children[1]) {
			if (parent->children[0]->isThreeNode()) {
				node->keys[0] = parent->keys[0];
				parent->keys[0] = parent->children[0]->keys[1];
				parent->children[0]->setThreeNode(false);

				situation = 3;

			}
			else if (parent->children[2]->isThreeNode()) {
				node->keys[0] = parent->keys[1];
				parent->keys[1] = parent->children[2]->keys[0];
				parent->children[2]->setThreeNode(false);

				situation = 4;
			}
			else {
				bRc = false;
			}

		}
		else
			if (parent->children[1]->isThreeNode()) {
				node->keys[0] = parent->keys[1];
				parent->keys[1] = parent->children[1]->keys[1];
				parent->children[1]->setThreeNode(false);

				situation = 5;

			}
			else if (parent->children[0]->isThreeNode()) {
				node->keys[0] = parent->keys[1];
				parent->keys[1] = parent->children[1]->keys[0];
				parent->children[1]->keys[0] = parent->keys[0];
				parent->keys[0] = parent->children[0]->keys[1];
				parent->children[0]->setThreeNode(false);
				situation = 6;

			}
			else {
				bRc = false;
			}
	}
}
 else {

	 if (parent->children[0] == node) {

		 if (parent->children[2]->isThreeNode()) {

			 node->keys[0] = parent->keys[0];
			 parent->keys[0] = parent->children[2]->keys[0];
			 parent->children[2]->keys[0] = parent->children[2]->keys[1];
			 parent->children[2]->setThreeNode(false);
			 situation = 7;

		 }
		 else {

			 bRc = false;
		 }

	 }
	 else {
		 if (parent->children[0]->isThreeNode()) {

			 node->keys[0] = parent->keys[0];
			 parent->keys[0] = parent->children[0]->keys[1];
			 parent->children[2]->setThreeNode(false);
			 situation = 8;

		 }
		 else {
			 bRc = false;
		 }
	 }
 }
 return bRc;
}

template<typename K> void Arbol23<K>::fix(Node23 *node, Node23 *pChildOfNode)
{
	if (node == root) {
		delete root;
		root = pChildOfNode;

	}
	else {

		Node23 *parent = node->parent;

		int situation;

		if (Redistribute(node, situation)) {

			if (!node->isLeafNode()) {

				ReassignChildren(node, pChildOfNode, situation);
			}

		}
		else {

			Node23 *pSibling;

			Node23 *middleChild;
			Node23 *Node23::*Ptr2newParentOfChild;
			int index;
			bool parentIsEmpty = false;

			if (parent->isThreeNode()) {

				if (parent->children[2] == node) {

					pSibling = parent->children[1];
					pSibling->keys[1] = parent->keys[1];

					middleChild = pSibling->children[2];
					index = 2;

				}
				else if (parent->children[1] == node) {

					pSibling = parent->children[2];

					pSibling->keys[1] = pSibling->keys[0];
					pSibling->keys[0] = parent->keys[1];

					middleChild = pSibling->children[0];
					index = 0;

				}
				else {

					pSibling = parent->children[1];

					pSibling->keys[1] = pSibling->keys[0];
					pSibling->keys[0] = parent->keys[1];

					middleChild = pSibling->children[0];
					index = 0;
				}

				parent->setThreeNode(false);

			}
			else {
				if (parent->children[2] == node) {

					pSibling = parent->children[0];

					pSibling->keys[1] = parent->keys[0];

					middleChild = pSibling->children[2];
					index = 2;

				}
				else {

					pSibling = parent->children[2];

					pSibling->keys[1] = pSibling->keys[0];
					pSibling->keys[0] = parent->keys[0];

					middleChild = pSibling->children[0];
					index = 0;
				}

				parentIsEmpty = true;
			}

			pSibling->setThreeNode(true);

			if (!node->isLeafNode()) {

				pSibling->children[1] = middleChild;

				pSibling->children[index] = pChildOfNode;
			}

			delete node;

			if (parentIsEmpty) {

				fix(parent, pSibling);
			}
		}
	}
}

template<typename K> void Arbol23<K>::ReassignChildren(Node23 *node, Node23* pChildOfNode, int situation)
{
	Node23 *parent = node->parent;

	switch (situation) {

	case 1:
		node->children[0] = pChildOfNode;
		node->children[2] = parent->children[1]->children[0];
		parent->children[1]->children[0] = parent->children[1]->children[1];

		break;
	case 2:
		node->children[0] = pChildOfNode;

		node->children[2] = parent->children[1]->children[0];

		parent->children[1]->children[0] = parent->children[1]->children[2];
		parent->children[1]->children[2] = parent->children[2]->children[0];
		parent->children[2]->children[0] = parent->children[2]->children[1];
		break;

	case 3:
		node->children[0] = pChildOfNode;
		node->children[2] = parent->children[2]->children[0];
		parent->children[2]->children[0] = parent->children[2]->children[1];
		break;

	case 4:
		node->children[0] = pChildOfNode;
		node->children[2] = parent->children[2]->children[0];
		parent->children[2]->children[0] = parent->children[2]->children[1];
		break;

	case 5:
		node->children[2] = pChildOfNode;
		node->children[0] = parent->children[1]->children[2];
		parent->children[1]->children[2] = parent->children[1]->children[1];


	case 6:
		node->children[2] = (node->children[0] = pChildOfNode) ? node->children[0] : node->children[2];

		node->children[0] = parent->children[1]->children[2];

		parent->children[1]->children[2] = parent->children[1]->children[0];
		parent->children[1]->children[0] = parent->children[0]->children[2];
		parent->children[0]->children[2] = parent->children[0]->children[1];
		break;

	case 7:
		node->children[0] = pChildOfNode;
		node->children[2] = parent->children[2]->children[0];
		parent->children[2]->children[0] = parent->children[2]->children[1];
		break;


	case 8:
		node->children[2] = pChildOfNode;
		node->children[0] = parent->children[0]->children[2];
		parent->children[0]->children[2] = parent->children[2]->children[1];
		break;
	}
}

template<typename K> Arbol23<K>::Node34::Node34(Node23 *threeNode, K new_key, Node23 *leftChildOfNewValue, Node23 *rightChildOfNewValue)
{
	if (new_key < threeNode->keys[0]) {

		keys[0] = new_key;
		keys[1] = threeNode->keys[0];
		keys[2] = threeNode->keys[1];

		leftChild = leftChildOfNewValue;
		leftMiddleChild = rightChildOfNewValue;
		rightMiddleChild = threeNode->children[1];
		rightChild = threeNode->children[2];

	}
	else if (new_key > threeNode->keys[1]) {

		keys[0] = threeNode->keys[0];
		keys[1] = threeNode->keys[1];
		keys[2] = new_key;

		leftChild = threeNode->children[0];
		leftMiddleChild = threeNode->children[1];
		rightMiddleChild = leftChildOfNewValue;
		rightChild = rightChildOfNewValue;

	}
	else {

		keys[0] = threeNode->keys[0];
		keys[1] = new_key;
		keys[2] = threeNode->keys[1];

		leftChild = threeNode->children[0];
		leftMiddleChild = leftChildOfNewValue;
		rightMiddleChild = rightChildOfNewValue;
		rightChild = threeNode->children[2];
	}
}
#endif	