#ifndef  ARBOL23
#define	ARBOL23

#include <utility>
#include <iostream>
#include <exception>

using namespace std;

template<typename T> class Arbol23;    

class duplicatekey :  public exception 
{
public:
    
  virtual const char* what() const throw()
  {
    return "Attempting to insert duplicate key ";
  }
};

template<typename K> class Arbol23 
{
protected:           
   class Node34;
public:
   class Node23 
   { 
    friend class Arbol23<K>;             
    friend class Node34;
    Node23(bool three_node=false);
           
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
    	 Node34(Node23 *threeNode, K new_value, Arbol23<K>::Node23 *leftChildOfNewValue=nullptr, Arbol23<K>::Node23 *rightChildOfNewValue=nullptr);
         K  getSmallValue()  { return keys[0]; }
         K  getMiddleValue() { return keys[1]; }
         K  getLargeValue()  { return keys[2]; }

    	 Arbol23<K>::Node23 *getLeftChild() { return leftChild; }
	 Arbol23<K>::Node23 *getLeftMiddleChild()  { return leftMiddleChild; }	
	 Arbol23<K>::Node23 *getRightMiddleChild() { return rightMiddleChild; }	
	 Arbol23<K>::Node23 *getRightChild()   { return rightChild; } 
    };

   protected:

    Node23 *root; 
    
    bool DoSearch(K key, Node23 *root, Node23 *&location);
    
    Node23 *Split(Node23 *p, K key, Node23 *pLeftChildOfNewKey = nullptr, Node23 *pRightChildOfNewKey = nullptr);

    template<typename Functor> 
    void DoTraverse(Functor f, Node23 *root);
    void DestroyTree(Node23 *root);
    
    Node23 *FindNextLargest(K key, Node23 *location);
    void fix(Node23 *location, Node23 *pAdoptee=nullptr);
    bool Redistribute(Node23 *node, int& situation_designator);
    void ReassignChildren(Node23 *node, Node23* pChildOfNode, int situation);

  public:    
     Arbol23() { root = nullptr; } 
    ~Arbol23();
     template<typename Functor> void Traverse(Functor f);
     bool Search(K key, Node23 *&location);
     bool remove(K key, Node23 *location=nullptr);
           
     Arbol23<K>::Node23 *insert(K key, Node23 *location=nullptr) throw(duplicatekey);
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
    children[2] = prightChild; // TODO: Change this to be: children[1] = rightChild;
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
  parent =  pParent;
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
  { // descend three node
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
    } else if ((current->isLeafNode())) 
        {     
        location = current;
	return false; 
        } else if (current->isThreeNode())
          {   
            if (key < current->keys[0]) 
            {    
                bRc = DoSearch(key, current->children[0], location);    
            }  else if (key < current->keys[1]) 
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
    // root case
    if (root == nullptr) 
    {
         root = new Node23(key);
	 return root;
    } 

    // Test that location is 0, which suggests the root, or if it truly is a leaf.
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
            
        } else if (key < location->keys[0]) 
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
    
    Node34 node34(location, new_key, pLeftChildOfNewKey, pRightChildOfNewKey); // defaults handles leaf node case. 
    Node23 *pSmallest = new Node23(node34.getSmallValue(), parent, node34.getLeftChild(), node34.getLeftMiddleChild());
    location->makeTwoNode(node34.getLargeValue(), parent, node34.getRightMiddleChild(), node34.getRightChild());
    Node23 *pLargest = location; 
    if (!isLeaf) 
    { 
        node34.getLeftChild()->parent  = pSmallest; 
        node34.getLeftMiddleChild()->parent  = pSmallest;
        node34.getRightMiddleChild()->parent  = pLargest; 
        node34.getRightChild()->parent  = pLargest;
    }

    K middle = node34.getMiddleValue(); 

    if (bRootIsNew) 
    { 
        parent->keys[0] = middle;
        parent->children[0] = pSmallest; 
        parent->children[2] = pLargest; 
        root = parent;
    } else if (parent->isThreeNode()) 
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
        }  else 
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
        
  } else if (key != location->keys[0] && key != location->keys[1]) 
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

    /* parent is three node. Look for a three node sibling. */
    if (node == parent->children[0]) { // left

         if (parent->children[1]->isThreeNode()) { // case 1
            /* 
              (20,      40)          (30,     40)
             /      |     \    =>    /     |    \
          Hole   (30,35)   50       20    35     50
            |    /  | \    /\       |    / | \   /\
            C   29 32  37 60 70     C  29 32 37 45 70
             */
              node->keys[0] = parent->keys[0]; 
              parent->keys[0] = parent->children[1]->keys[0]; 
              parent->children[1]->keys[0] = parent->children[1]->keys[1]; 
              parent->children[1]->setThreeNode(false);

              situation = 1;

         } else if (parent->children[2]->isThreeNode()) {
           /*
               (10,  20)                  (15,  30)    
              /    |    \          =>    /    |    \
            Hole   15    (30, 40)      10    20     40 */

              node->keys[0] = parent->keys[0]; 
              parent->keys[0] = parent->children[1]->keys[0]; 
              
              parent->children[1]->keys[0] = parent->keys[1]; 
              parent->keys[1] = parent->children[2]->keys[0];
              parent->children[2]->keys[0] = parent->children[2]->keys[1]; 
              parent->children[2]->setThreeNode(false);
              situation = 2;

         } else {
	     bRc = false; 
	 }

    } else if (node == parent->children[1]) { // middle

         if (parent->children[0]->isThreeNode()) {
           /* 
               (10, 20)                   (5, 20)
              /    |  \             =>   /   |  \
           (1, 5) Hole (30, 40)        1    10  (30, 40) */

            node->keys[0] = parent->keys[0];
            parent->keys[0] = parent->children[0]->keys[1];
            parent->children[0]->setThreeNode(false);
		
            situation = 3;

         } else if (parent->children[2]->isThreeNode()) {
           /*
              (10, 20)                 (10,  30)
             /    |  \           =>    /    |   \
           1     Hole  (30, 40)       1    20   40
           */
            node->keys[0] = parent->keys[1];
            parent->keys[1] = parent->children[2]->keys[0];
            parent->children[2]->setThreeNode(false);
            
            situation = 4;
         } else {
	   bRc = false;
         } 

    } else /*(node == parent->children[2])*/ {  //children[2] is the only case left 

         if (parent->children[1]->isThreeNode()) {
           /* We redistribute value of siblings, but we do not reassign here their children 
              (10,       25)              (10,       19)
             /       |     \       =>    /      |       \
            5    (15, 19)   Hole        5       15       25     
           / \    /  |  \    /         / \     / | \     /      
          1   7  12 17  22  60        1   7  12  17 18  60       */
              
              node->keys[0] = parent->keys[1]; 
              parent->keys[1] = parent->children[1]->keys[1]; 
              parent->children[1]->setThreeNode(false);

              situation = 5;

         } else if (parent->children[0]->isThreeNode()) {

           /*  Redistribute() redistributes node values but not their child. 
           (20,       40)               (18,   30)   
           /       |     \      =>     /     |   \   
       (10, 18)   30     Hole        10     20    40 
        /  | \    /  \    /         / | \   / \   /  
       5  12  19 25  32  55        5  7 19 25 32 55      */
 
             node->keys[0] =  parent->keys[1];
              parent->keys[1] = parent->children[1]->keys[0];
              parent->children[1]->keys[0] =  parent->keys[0];
              parent->keys[0] = parent->children[0]->keys[1];
              parent->children[0]->setThreeNode(false);
              situation = 6;

         } else {
	      bRc = false;
         } 
    } // end else 
    
  } else { // parent is a two node

    if (parent->children[0] == node) {
   
        if (parent->children[2]->isThreeNode()) {    

	      node->keys[0] = parent->keys[0];
              parent->keys[0] = parent->children[2]->keys[0];
              parent->children[2]->keys[0] = parent->children[2]->keys[1]; // Is this necessary if parent is a two node?
              parent->children[2]->setThreeNode(false);  
              situation = 7;
              
        }  else {

	   bRc = false;	
        }
        
     } else {  // node is children[2]
        
     
        if (parent->children[0]->isThreeNode()) {    

	      node->keys[0] = parent->keys[0];
              parent->keys[0] = parent->children[0]->keys[1];
              parent->children[2]->setThreeNode(false);  
              situation = 8;

        } else {
	      bRc = false;	
        } 
    } 
  }
  return bRc;
}

template<typename K> void Arbol23<K>::fix(Node23 *node, Node23 *pChildOfNode)
{
 if (node  == root) {
      /* delete root */ 
      delete root;
      root = pChildOfNode; 

 } else {

     Node23 *parent = node->parent;

     int situation;
  
     // try to redistribute.. 
     if (Redistribute(node, situation)) { 

        // We could redistribute. If node is a internal node, we need to reassign the children appropriately among the siblings. 	   
	if (!node->isLeafNode()) {  

              ReassignChildren(node, pChildOfNode, situation);
	 }

     } else { // ...we could not redistribute because all siblings are two nodes, so we merge the parent with a sibling. 

	 Node23 *pSibling;

         Node23 *middleChild;
         Node23 *Node23::*Ptr2newParentOfChild; // Pointer to member variable (of type Node23 *)
         int index;
         //Node23 *Ptr2newParentOfChild; // Pointer to member variable (of type Node23 *)
         bool parentIsEmpty = false; // If parent is a two node, it will be flagged empty after merge.

	 /* Merge nodes by bringing down parent's value to sibling of node.  */ 
                  
          if (parent->isThreeNode()) {

              if (parent->children[2] == node) {

                  pSibling = parent->children[1]; 
                  pSibling->keys[1] = parent->keys[1];

                  middleChild = pSibling->children[2];
		  //--Ptr2newParentOfChild = &(Node23::children[2]);
		  index = 2;
                  
              } else if (parent->children[1] == node) {

                  pSibling = parent->children[2]; 

                  pSibling->keys[1] = pSibling->keys[0];
                  pSibling->keys[0] = parent->keys[1];

                  middleChild = pSibling->children[0];
		  //--Ptr2newParentOfChild = &Node23::children[0];
		  index = 0;

              } else { // node is children[0]

                  pSibling = parent->children[1]; 

                  pSibling->keys[1] = pSibling->keys[0];
                  pSibling->keys[0] = parent->keys[1];

                  middleChild = pSibling->children[0];   
		  //--Ptr2newParentOfChild = &(Node23::children[0]);
		  index = 0;
              } 

              // parent is now a two node
              parent->setThreeNode(false);

          }  else { /* parent is a two node and its other child is a two node  */ 
              
                if (parent->children[2] == node) {

		       pSibling = parent->children[0];

                       pSibling->keys[1] = parent->keys[0];

                       middleChild = pSibling->children[2];
                       //--Ptr2newParentOfChild =  &Node23::children[2];
                       index = 2;
           
                 } else {

			pSibling = parent->children[2];

	                pSibling->keys[1] = pSibling->keys[0];
        	        pSibling->keys[0] = parent->keys[0];

                        middleChild = pSibling->children[0];
			//--Ptr2newParentOfChild = &(Node23::children[0]);
			index = 0;
                 }      

                 parentIsEmpty = true;
          } 

          pSibling->setThreeNode(true);  

	  if (!node->isLeafNode()) {
	           
              pSibling->children[1] =  middleChild;
              
              // Move node's child pChildOfNode to sibling 
	      //--pSibling->*Ptr2newParentOfChild  =  pChildOfNode;
	      pSibling->children[index] =  pChildOfNode;
	  }

	  // Remove node...
	  delete node;

	  if (parentIsEmpty) { 

	      fix(parent, pSibling); 
	  }
     }
   } // end main if/else
}

template<typename K> void Arbol23<K>::ReassignChildren(Node23 *node, Node23* pChildOfNode, int situation)
{
    Node23 *parent = node->parent;
    
       switch (situation) {

            case 1:
            /*  Redistribute did (a). We must do (b)
              (20,      40)    (a)   (30,     40)     (b)   (30,     40)        
             /      |     \     =>   /     |    \     =>    /     |    \     
          Hole   (30,35)   50       20    35     50        20    35    50      
            |    /  | \    /\       |    / | \   /\        /\    / \   /\      
            C   29 32  37 60 70     C  29 32 37 45 70     C 29 32  37 45 70 */
                 node->children[0] = pChildOfNode;
                 node->children[2] = parent->children[1]->children[0]; 
                 parent->children[1]->children[0] = parent->children[1]->children[1]; 

                 break;
            case 2:

           /*      (10,       20)     Redist.    (15,   30)                                                                                     
                   /       |     \       =>     /     |    \                   (15,   30)   
                 Hole     15    (30,40)        10    20     40      Reassign    /    |  \   
                   |      / \    / | \          |    / \   / | \       =>     10   20     40                                                  
                   5    12 17  32 35 70         5   12 17 32 35 70   Children / \   / \   / \                                                  
                                                                             5  12 17 32 35 70      */                                                      
                   node->children[0] = pChildOfNode;

                   node->children[2] = parent->children[1]->children[0];

                   parent->children[1]->children[0] = parent->children[1]->children[2];
                   parent->children[1]->children[2] = parent->children[2]->children[0];
                   parent->children[2]->children[0] = parent->children[2]->children[1]; 
                   break;
                   
            case 3: 
             

           /* 
               (10,  20)          Redist.     (10,  30)       Reassign  (10,    30)          
              /     |  \             =>      /     |   \      Children  /     |   \         
             7    Hole (30, 40)             7     20    40       =>    7     20    40  
            / \     |   /  |  \            / \     |   / | \          / \    /\    / \
           1   5   17  32 35  70          1   5   17  32 35  70      1   5 17  32 35  70 */

            case 4: // case 4 is identical to case 3.
              /*     (10,  20)          Redist.    (10,  30)       Reassign      (10,     30)  
                   /    |    \             =>      /    |    \     Children      /      |   \      
               (5,8)   Hole  (30, 40)         (5,8)    20    40      =>        (5,8)    20    40   
              /  | \    |   /   |  \          /  | \    |   / | \              / | \    /\    / \  
             1   7  9  17  32  35  70        1   7  9  17  32 35  70          1  7  9 17  32 35  70 */

                    node->children[0] = pChildOfNode;
                    node->children[2] = parent->children[2]->children[0];
                    parent->children[2]->children[0] = parent->children[2]->children[1];
                    break;

            case 5:
       /* We redistribute value of siblings, but we do not reassign here their children 
          (10,       25)              (10,      19)    Reassign      (10,       19)
         /       |     \       =>    /      |      \   Children     /      |       \                              
        5    (15, 19)   Hole        5       15      25    =>       5       15       25     
       / \    /  |  \    |         / \     / | \     |            / \     /  \     /  \    
      1   7  12 17  22  60        1   7  12  17 18  60           1   7  12    17  22   60   */
            
                   // If the sole child of node is the children[0], move it to the children[2].
                   node->children[2] = pChildOfNode;
                   node->children[0] = parent->children[1]->children[2];
                   parent->children[1]->children[2] = parent->children[1]->children[1];
                   

              case 6:

       /*  Redistribute() redistributed node values (a) but did not reassign their childa(b)
                  (20,       40)               (18,   30)           (18,    30)    
                  /       |     \    Redist   /     |   \   Shift   /     |    \                
              (10, 18)   30     Hole   =>   10     20    40   =>   10     20     40                         
               /  | \    /  \    /    (a)  / | \   / \   /   (b)  /  \   / \    / \
              5  12  19 25  32  55        5 12 19 25 32 55       5   12 19 25  32 55  
              */

                   // If the sole child of node is the children[0], move it to the children[2].
                   node->children[2] = (node->children[0] = pChildOfNode) ? node->children[0] : node->children[2];

                   node->children[0] = parent->children[1]->children[2];

                   parent->children[1]->children[2] = parent->children[1]->children[0];
                   parent->children[1]->children[0] = parent->children[0]->children[2];
                   parent->children[0]->children[2] = parent->children[0]->children[1]; 
                   break;

            case 7:
             /* parent is a two node and right Child is three node
                    20                            30                    30
                   /  \         Redistribute     /  \      Reassign    /   \               
                Hole  (30, 40)     =>           20    40     =>       20     40    
                  |    /  |  \                  |    / | \           / \    / \
                  5  25  35  50                 5  25  35  50       5  25 35  50 */


                  node->children[0] = pChildOfNode;
                  node->children[2] = parent->children[2]->children[0]; 
                  parent->children[2]->children[0] = parent->children[2]->children[1];
                  break;


            case 8: /* parent is a two node and right Child is three node
                       50        After              40                        40        
                      /   \      Redistribute      /   \      Reassign       /  \     
                  (30, 40) Hole     =>           30     50       =>         30   50   
                  /  |  \   |                   / | \    |    Children     / \   / \  
                25  35  45  60                 25 35 45  60               25 35 45 60   */ 

                  node->children[2] = pChildOfNode;
                  node->children[0] = parent->children[0]->children[2]; 
                  parent->children[0]->children[2] = parent->children[2]->children[1];
                  break;
       }
}

template<typename K> Arbol23<K>::Node34::Node34(Node23 *threeNode, K new_key, Node23 *leftChildOfNewValue, Node23 *rightChildOfNewValue)
{
    /*
     * Sort to find keys[0], keys[1] and keys[2]. Assign child pointers appropriately.
     */
    if (new_key < threeNode->keys[0]) { // new_key is smallest value
     	
 	keys[0] = new_key;
 	keys[1] = threeNode->keys[0];
 	keys[2] = threeNode->keys[1];

        leftChild = leftChildOfNewValue;
        leftMiddleChild = rightChildOfNewValue;
        rightMiddleChild = threeNode->children[1];
     	rightChild = threeNode->children[2];
             		
     } else if (new_key > threeNode->keys[1]) { // new_key is largest value
     
 	keys[0] = threeNode->keys[0];
 	keys[1] = threeNode->keys[1];
 	keys[2] = new_key;
     
        leftChild = threeNode->children[0];
        leftMiddleChild = threeNode->children[1];
        rightMiddleChild = leftChildOfNewValue;
     	rightChild = rightChildOfNewValue;

     } else { // new_key is the middle value
     
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