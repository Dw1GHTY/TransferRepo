#include "BSTree.h"

void BSTree::insert(int el)
{
	if (isEmpty()) {
		root = new BSNode(el);
		numOfElements++;
		return;
	}

	BSNode* ptr = root, *prev = nullptr;
	while (ptr != nullptr)
	{
		prev = ptr;
		if (el < ptr->key)
			ptr = ptr->left;
		else if (el >= ptr->key)
			ptr = ptr->right;
	}

	if (prev->key <= el)
		prev->right = new BSNode(el);
	else prev->left = new BSNode(el);
	numOfElements++;
}

BSNode* BSTree::search(BSNode* p, int el)
{
	BSNode* ptr = p;
	while (ptr != nullptr && ptr->key != el)
	{
		if (el > ptr->key)
			ptr = ptr->right;
		if (el < ptr->key)
			ptr = ptr->left;
	}
	return ptr;
}

void BSTree::preorder(BSNode* p)
{
	if (p != nullptr)
	{
		p->print();
		preorder(p->left);
		preorder(p->right);
	}
}

void BSTree::inorder(BSNode* p)
{
	if (p != nullptr)
	{
		inorder(p->left);
		p->print();
		inorder(p->right);
	}
}

void BSTree::postorder(BSNode* p)
{
	if (p != nullptr)
	{
		postorder(p->left);
		postorder(p->right);
		p->print();
	}
}

void BSTree::iterativePreorder()
{
	Stack stack(numOfElements);
	if (isEmpty())
		return;
	BSNode* p = root;

	stack.push(p);
	while (!stack.isEmpty())
	{

		p = stack.pop();

		p->print();
		if (p->right != nullptr)
			stack.push(p->right);
		if (p->left != nullptr)
			stack.push(p->left);
	}
}

void BSTree::iterativeInorder()
{
	Stack stack(numOfElements);
	if (isEmpty())
		return;

	BSNode* p = root;
	while (p!=nullptr)
	{
		while (p != nullptr)
		{
			if (p->right)
				stack.push(p->right);
			stack.push(p);
			p = p->left;
		}
		p = stack.pop();
		while (!stack.isEmpty() && p->right == nullptr)
		{
			p->print();
			p = stack.pop();
		}
		p->print();
		if (!stack.isEmpty())
			p = stack.pop();
		else
			p = nullptr;
	}
}

void BSTree::iterativePostorder()
{
	BSNode* p = root, * last= nullptr;
	Stack stack(numOfElements);
	while (p != nullptr)
	{
		while (p->left != nullptr && p->left != last)
		{
			stack.push(p);
			p = p->left;
		}
		//p = stack.pop();
		while ((!stack.isEmpty() && p->right == nullptr) || p->right == last) {
			p->print();
			last = p;
			p = stack.pop();
			if (p == nullptr)
				return;
		}
		stack.push(p);

		if (p->right != nullptr && p->right != last) {

			stack.push(p->right);
		}
		p = stack.pop();
	}
}

void BSTree::breadthFirst()
{
	if (isEmpty())
		return;

	BSNode* p = root;
	Queue queue(numOfElements);

	queue.enqueue(p);
	while (!queue.isEmpty())
	{
		p = queue.dequeue();
		if (p->left)
			queue.enqueue(p->left);
		if (p->right)
			queue.enqueue(p->right);
		p->print();
	}
}

void BSTree::copyInArray(int* niz, BSNode* p, int* i)
{
	if (p != nullptr) {
		copyInArray(niz, p->left, i);
		copyInArray(niz, p->right, i);
		niz[(*i)++] = p->key;
	}
}
void BSTree::balance()
{
	int* data = new int[numOfElements];
	int i = 0;
	copyInArray(data, root, &i);
	deleteTree(root);
	for (int j = 0; j< i; j++)
	{
		int min = i;
		for (int k = j + 1; k < i; k++)
		{
			if (data[k] < data[min])
				min = k;
		}
		int tmp = data[j];
		data[j] = data[min];
		data[min] = tmp;
	}

	balancer(data, 0, i-1);

}
void BSTree::balancer(int* data, int first, int last)
{
	if (first <= last)
	{
		int mid = (first + last) / 2;
		insert(data[mid]);
		balancer(data, first, mid - 1);
		balancer(data, mid + 1, last);
	}
}

void BSTree::deleteByMerging(int el)
{
	BSNode* p = root, * prev = nullptr, *tmp, *tmp2, *node;
	while (p != nullptr && p->key != el)
	{
		prev = p;
		if (el > p->key)
			p = p->right;
		else if (el < p->key)
			p = p->left;
	}
	if (!p)
		return;
	if (p->right == nullptr)
	{
		node = p->left;
	}
	else if (p->left == nullptr)
	{
		node = p->right;
	}
	else {
		tmp = p->right;
		tmp2 = p->left;
		while (tmp2->right != nullptr)
			tmp2 = tmp2->right;
		tmp2->right = tmp;
		node = p->left;

	}
	if (root == p)
		root = node;
	else if (prev->right == p)
		prev->right = node;
	else if (prev->left == p)
		prev->left = node;
	delete p;
	numOfElements--;
}

void BSTree::deleteByCopying(int el)
{
	BSNode* p = root, * prev = nullptr, * tmp, * tmpprev;
	while (p != nullptr && p->key != el)
	{
		prev = p;
		if (el > p->key)
			p = p->right;
		else if (el < p->key)
			p = p->left;
	}
	if (!p)
		return;

	if (!p->right && !p->left)
	{
		delete p;
		return;
	}
	else if (p->right == nullptr)
	{
		tmp = p->left;
	}
	else if (p->left == nullptr)
	{
		tmp = p->right;
	}
	else
	{
		tmpprev = p;
		tmp = p->left;
		while (tmp->right != nullptr)
		{
			tmpprev = tmp;
			tmp = tmp->right;
		}
		int rez = tmp->key;
		if (tmp->left) {
			if (tmpprev->right == tmp)
				tmpprev->right = tmp->left;
			else tmpprev->left = tmp->left;
			delete tmp;
		}
		p->key = rez;
		numOfElements--;
		return;
	}
	if (p == root)
		root = tmp;
	else if (prev->right == p)
		prev->right = tmp;
	else prev->left = tmp;
	numOfElements--;
}


int BSTree::countNodesInRange(BSNode* root, int min, int max)
{
	if (root == nullptr)
		return 0;

	int currentVal = root->key;	//znamo koja je trenutna vrednost cvora
	if (currentVal <= max && currentVal >= min)
		return 1 + countNodesInRange(root->left, min, max) + countNodesInRange(root->right, min, max);
	else if (currentVal < min)
		return countNodesInRange(root->right, min, max);
	else if (currentVal > max)
		return countNodesInRange(root->left, min, max);
}

int BSTree::countNodes(BSNode* p)
{
	if (p != nullptr)
		return 1 + countNodes(p->left) + countNodes(p->right);
	if (p == nullptr)
		return 0;
}

bool BSTree::isPerfect()
{
	if (root == nullptr)
		return true;
	return isPerfect(root);
}
bool BSTree::isPerfect(BSNode* p)
{
	if (p == nullptr) return true;

	int nodesLeft = countNodes(p->left);
	int nodesRight = countNodes(p->right);
	
	if (abs(nodesLeft - nodesRight) <= 1)
		return true && isPerfect(p->left) && isPerfect(p->right);
	else return false;
}

BSNode* BSTree::findNodeWithLargestRightSubtree()
{
	BSNode* retVal = nullptr;
	int max = 0;

	findNodeWithLargestRightSubtree(root, &retVal, &max);
	return retVal;
}

BSNode* BSTree::findNodeWithLargestRightSubtree(BSNode* ptr, BSNode** largest, int* max)
{
	if (ptr != nullptr)
	{
		if (countNodes(ptr->right) > *max)
		{
			*max = countNodes(ptr->right);
			*largest = ptr;
		}
	}
	return nullptr;
}

BSNode* BSTree::getNNode()
{
	BSNode* retVal = nullptr;
	bool flag = false;
	getNNode(root, &retVal, &flag);
	return retVal;
}

void BSTree::getNNode(BSNode* ptr, BSNode** retVal, bool* flag)
{
	if (ptr == nullptr || *flag)
		return;
	int levoCvorovi = countNodes(ptr->left);
	int desnoCvorovi = countNodes(ptr->right);

	if (desnoCvorovi - levoCvorovi == 2) {
		*retVal = ptr;
		*flag = true;
	}
	else
	{
		getNNode(ptr->left,retVal,flag);
		getNNode(ptr->right,retVal,flag);
	}
}

int BSTree::CountSL()
{
	return CountSL(root);

}
int BSTree::CountSL(BSNode* ptr)
{
	if (ptr == nullptr)
		return 0;

	int levo = Count(ptr->left);
	int desno = Count(ptr->right);

	if (levo > desno) {
		ptr->print();
		return 1 + CountSL(ptr->left) + CountSL(ptr->right);

	}
	else
		return CountSL(ptr->left) + CountSL(ptr->right);

}

int BSTree::Count(BSNode* ptr)
{
	if (ptr == nullptr)
		return 0;
	return ptr->key + Count(ptr->right) + Count(ptr->left);
}