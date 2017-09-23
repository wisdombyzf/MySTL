#pragma once
/*
date:9-17
author:zf
�����
*/

#include<iostream>
enum NodeColor
{	
	red,black
};

template<class T>
struct RBTNode
{
	NodeColor color;	//�����ɫ
	T key;		//�ؼ���
	T data;
	RBTNode* left;		//��ֽ
	RBTNode* right;	//�Һ�ֽ
	RBTNode* parent;	//���ڵ�
};

template<class T>
class RBTree
{
public:
	//���ͱ�
	typedef RBTNode<T>*	node_pointer;	//���ָ��
public:
	RBTree();
	~RBTree();
	void left_rotate(node_pointer x);	//����
	void right_rotate(node_pointer y);	//����
	void insert(node_pointer my_node);	//����
	void insert_fix_up(node_pointer my_node);	//��������
	void remove(node_pointer my_node);		//ɾ��
	void remove(RBTNode<T>* &root, RBTNode<T> *node);
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);
	void remove_fix_up(node_pointer my_node);	//ɾ������
	node_pointer get_root() { return root; }		//���ظ��ڵ�
	node_pointer find(T value);			//���������Ƿ��valueԪ�أ������򷵻ظ�Ԫ�ص�ָ�룬�������򷵻�nullptr

private:
	node_pointer root;

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==red)
#define rb_is_black(r)  ((r)->color==black)
#define rb_set_black(r)  do { (r)->color = black; } while (0)
#define rb_set_red(r)  do { (r)->color = red; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};

template<class T>
RBTree<T>::RBTree()
{
	root = nullptr;
}

template<class T>
RBTree<T>::~RBTree()
{
}

/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(����)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/
template<class T>
void RBTree<T>::left_rotate(node_pointer x)
{
	node_pointer y;
	y = x->right;
	x->right = y->left;		//x���ҽ����Ϊly
	if (y->left!=nullptr)	//��ly��Ϊ�գ�ly�ĸ��ڵ���Ϊx
	{
		y->left->parent = x;
	}

	node_pointer px = x->parent;
	y->parent = px;		//y�ĸ��ڵ��Ϊx�ĸ��ڵ�
	if (x==root)		//��xΪ���ڵ㣬����ڵ���Ϊy
	{
		root = y;
	}
	else
	{
		if (px->left==x)
		{
			px->left = y;
		}
		else
		{
			px->right = y;
		}
	}
	y->left = x;
	x->parent = y;
}

/*
* �Ժ�����Ľڵ�(y)��������ת
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
template<class T>
void RBTree<T>::right_rotate(node_pointer y)
{
	node_pointer x = y->left;
	y->left = x->right;		//y����ڵ��Ϊrx
	if ((x->right)!= nullptr)	//��rx�ǿ�ʱ�����丸�ڵ���Ϊy
	{
		x->right->parent = y;		
	}
	
	node_pointer py = y->parent;	
	x->parent = py;		//x�ĸ��ڵ��Ϊy�ĸ��ڵ�
	if (y==root)		//��yΪ���ڵ�,����ڵ���Ϊx
	{
		root = x;
	}
	else
	{
		if ((py->left)==y)		//���y�������ڵ���Һ��ӣ���x��py���Һ���
		{
			py->left = x;
		}
		else
		{
			py->right = x;		//���y�������ڵ�����ӣ���x��py������
		}

	}
	y->parent = x;				//y�ĸ��ڵ��Ϊx
	x->right = y;		//x���ҽ��Ϊy
}

/*
����˼����Ƿ������ۡ�������

�� ���˵����������Ľڵ��Ǹ��ڵ㡣
��������ֱ�ӰѴ˽ڵ�ͿΪ��ɫ��
�� ���˵����������Ľڵ�ĸ��ڵ��Ǻ�ɫ��
��������ʲôҲ����Ҫ�����ڵ㱻�������Ȼ�Ǻ������
�� ���˵����������Ľڵ�ĸ��ڵ��Ǻ�ɫ��
����������ô������������������ͻ,ʹ��insert_fix_up()����
*/
template<class T>
void RBTree<T>::insert(node_pointer my_node)
{
	//���ö���������Ĺ��򣬽�������
	my_node->right = nullptr;
	my_node->left = nullptr;
	my_node->parent = nullptr;
	if (root==nullptr)			//��������Ǹ��ڵ�
	{
		root = my_node;
		my_node->color = black;
	}
	else
	{
		node_pointer temp = root;
		T node_key = my_node->key;
		while (true)
		{
			if (node_key<(temp->key))
			{
				if (temp->left == nullptr)
				{
					temp->left = my_node;
					my_node->parent = temp;
					break;
				}
				temp = temp->left;
			}
			else
			{
				if (temp->right == nullptr)
				{
					temp->right = my_node;
					my_node->parent = temp;
					break;
				}
				temp = temp->right;
			}
		}
		my_node->color = red;
		//���������ĺ����
		insert_fix_up(my_node);
	}
}


template<class T>
void RBTree<T>::insert_fix_up(node_pointer my_node)
{
	node_pointer parent_node;
	while ((my_node->parent!=nullptr)&&(my_node->parent->color==red))			//�����ڵ������Ϊ��ɫʱ��������ۣ���������ѭ��
	{
		parent_node = my_node->parent;		//���ڵ�
		node_pointer granpa = parent_node->parent;	//�游���	
		if (parent_node==granpa->left)	//�����ڵ����游�ڵ����ڵ�
		{
			node_pointer uncle = granpa->right;
			//������Ϊ��(����Ϊnull,��ʼδ���ǵ�����bug��)
			if ((uncle==nullptr)||(uncle->color==black))
			{
				//������Ϊ�ڣ��ҵ�ǰ�ڵ�Ϊ�Һ�ֽ
				if (parent_node->right == my_node)
				{
					node_pointer temp;
					left_rotate(parent_node);
					temp = parent_node;
					parent_node = my_node;
					my_node = temp;
				}
				else		//Ϊ��ֽ
				{
					parent_node->color = black;
					granpa->color = red;
					right_rotate(granpa);
				}
			}
			else
			{
				uncle->color = black;
				parent_node->color = black;
				granpa->color = red;
				my_node = granpa;
				continue;
			}
		}
		else
		{
			node_pointer uncle = granpa->left;
			//������Ϊ��
			if ((uncle==nullptr)||(uncle->color==black))
			{
				//������Ϊ��ɫ���ҵ�ǰ���Ϊ��ֽ
				if (my_node == parent_node->left)
				{
					node_pointer temp;
					right_rotate(parent_node);
					temp = parent_node;
					parent_node = my_node;
					my_node = temp;
				}
				else
				{
					parent_node->color = black;
					granpa->color = red;
					left_rotate(granpa);
				}
			}
			else
			{
				parent_node->color = black;
				uncle->color = black;
				granpa->color = red;
				my_node = granpa;
				continue;
			}
		}

		/*
		parent_node = my_node->parent;
		node_pointer uncle_node;
		if (parent_node->parent->left== parent_node)		//���ڵ�Ϊ��ֽʱ
		{
			uncle_node = parent_node->parent->right;
			//������Ϊ��ɫʱ������Ϊ�ڣ��游Ϊ�죬�ݹ��游
			if ((uncle_node!=nullptr)&&(uncle_node->color==red))
			{
				parent_node->color = black;
				uncle_node->color = black;
				parent_node->parent->color = red;
				my_node = parent_node->parent;
				continue;
			}
			else				
			{
				if (parent_node->left==my_node)			//������Ϊ��ɫ�ҵ�ǰ���Ϊ��ֽ,���ڣ��游�죬�游����
				{
					parent_node->color = black;
					parent_node->parent->color = red;
					right_rotate(parent_node->parent);
				}
				else								//������Ϊ��ɫ�ҵ�ǰ���Ϊ�Һ�ֽʱ�����ڵ��Ϊ�µĽ�㣬������
				{
					my_node = parent_node;
					left_rotate(my_node);
				}	
			}
		}
		else								//Ϊ�Һ�ֽʱ
		{
			uncle_node = parent_node->parent->left;
			if ((uncle_node!=nullptr)&&(uncle_node->color == red))
			{
				parent_node->color = black;
				uncle_node->color = black;
				parent_node->parent->color = red;
				my_node = parent_node->parent;
				continue;
			}
			else					
			{
				//����
				if (parent_node->right == my_node)			//������Ϊ��ɫ�ҵ�ǰ���Ϊ��ֽ,���ڣ��游�죬�游����
				{
					parent_node->color = black;
					parent_node->parent->color = red;
					right_rotate(parent_node->parent);
				}
				else								//������Ϊ��ɫ�ҵ�ǰ���Ϊ�Һ�ֽʱ�����ڵ��Ϊ�µĽ�㣬������
				{
					my_node = parent_node;
					left_rotate(my_node);
				}
			}
		}
		*/
	}
	root->color = black;
}

template<class T>
RBTNode<T>* RBTree<T>::find(T value)
{
	
	node_pointer temp = root;
	while (true)
	{
		if (value==temp->key)		//����ʱ
		{
			return temp;
		}
		else if (value>temp->key)		//����ʱ����������
		{
			if (temp->right==nullptr)		//������������ʱ������nullptr
			{
				return nullptr;
			}
			else
			{
				temp = temp->right;
			}

		}
		else
		{
			if (temp->left==nullptr)		//������������ʱ������nullptr
			{
				return nullptr;
			}
			else
			{
				temp = temp->left;
			}
		}
	}
}


/*
* �����ɾ����������
*
* �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
* Ŀ���ǽ������������һ�ź������
*
* ����˵����
*     root ������ĸ�
*     node �������Ľڵ�
*/
template <class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
	RBTNode<T> *other;

	while ((!node || rb_is_black(node)) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (rb_is_red(other))
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->right || rb_is_black(other->right))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (rb_is_red(other))
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->left || rb_is_black(other->left))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		rb_set_black(node);
}

/*
* ɾ�����(node)�������ر�ɾ���Ľ��
*
* ����˵����
*     root ������ĸ����
*     node ɾ���Ľ��
*/
template <class T>
void RBTree<T>::remove(RBTNode<T> *node)
{
	RBTNode<T> *child, *parent;
	RBTColor color;

	// ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
	if ((node->left != NULL) && (node->right != NULL))
	{
		// ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
		// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
		RBTNode<T> *replace = node;

		// ��ȡ��̽ڵ�
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			// "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
			root = replace;

		// child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
		// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
		child = replace->right;
		parent = rb_parent(replace);
		// ����"ȡ���ڵ�"����ɫ
		color = rb_color(replace);

		// "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child��Ϊ��
			if (child)
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}

	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	// ����"ȡ���ڵ�"����ɫ
	color = node->color;

	if (child)
		child->parent = parent;

	// "node�ڵ�"���Ǹ��ڵ�
	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == BLACK)
		removeFixUp(root, child, parent);
	delete node;
}








//****************************************************************
//*******д���˵Ĵ��롣������������+1s,�������еġ�����

template<class T>
void RBTree<T>::remove(node_pointer my_node)
{
	//���ַ�ʽ���ɼ򵥵�����,���Կɶ���Ϊ��
	//���ΪҶ�ӽ�㣬����ֽ��Ҳ���Һ�ֽʱ
	if ((my_node->right == nullptr) && (my_node->left == nullptr))
	{
		node_pointer node_parent = my_node->parent;
		//���ΪҶ�ӽ�㣬��Ϊ��ʱ
		if ((my_node->color == red))
		{
			//Ϊ����ʱ
			if (node_parent->left == my_node)
			{
				node_parent->left = nullptr;
				delete my_node;
				return;
			}
			else	//�ҽ��ʱ
			{
				node_parent->right = nullptr;
				delete my_node;
				return;
			}
		}
		else		//���ΪҶ�ӽ�㣬��Ϊ��ʱ
		{
			//Ϊ���ڵ�ʱ
			if (root == my_node)
			{
				root = nullptr;
				delete my_node;
				return;
			}
			return  remove_fix_up(my_node);
		}

	}

	//�����ֻ����ֽʱ�����϶�Ϊ�ڣ���ֽ�϶�Ϊ�죩
	if ((my_node->right == nullptr) && (my_node->left != nullptr))
	{
		return  remove_fix_up(my_node);
	}

	//�����ֻ���Һ�ֽʱ�����϶�Ϊ�ڣ��Һ�ֽ�϶�Ϊ�죩
	if ((my_node->left == nullptr) && (my_node->right != nullptr))
	{
		return  remove_fix_up(my_node);
	}

	//��������ֽ�������Һ���ʱ
	if ((my_node->left != nullptr) && (my_node->right != nullptr))
	{
		//�ҳ���̽��(��������)
		node_pointer replace = my_node->right;
		while (replace->left != nullptr)
		{
			replace = replace->left;
		}

		//��̽���滻ԭ��㣬�ݹ�ɾ����̽��
		my_node->key = replace->key;
		my_node->data = replace->data;

		//��̽��϶�û����ڵ㣬�ú�̽���ҽ��ȡ����̽��
		//����̽��Ϊ��ʱ����϶�û���ҽ�㣬��ֱ��ɾ����
		if (replace->color == red)
		{
			if (replace->parent->left == replace)
			{
				replace->parent->left = nullptr;
				delete replace;
			}
			else
			{
				replace->parent->right = nullptr;
				delete replace;
			}
		}
		else   //����̽��Ϊ��ʱ
		{

			return remove_fix_up(replace);
		}
	}
	/*  //��֪���Ǳ��ˣ�����
	node_pointer parent = nullptr;		//ȡ�����ĸ��ڵ�
	node_pointer child = nullptr;		//ȡ�������Һ�ֽ����̽�㣬�϶���������ֽ��
	int node_color;
	//�����ҽ�㶼����ʱ
	if ((my_node->left!=nullptr)&&(my_node->right!=nullptr))
	{
	node_pointer replace = my_node;		//��replaceȡ��ɾ�����
	//��ȡ��̽��
	replace = replace->right;
	while (replace->left!=nullptr)
	{
	replace = replace->left;
	}

	if (my_node==root)		//���ɾ�����Ϊ���ڵ�
	{
	root = replace;
	}
	else
	{
	node_pointer parent_temp = my_node->parent;
	//�����ĸ��ڵ�ָ���½ڵ�
	if (parent_temp->left==my_node)
	{
	parent_temp->left = replace;
	}
	else
	{
	parent_temp->right = replace;
	}

	child = replace->right;
	parent = replace->parent;
	node_color = replace->color;

	//����ɾ������Ǻ�̽��ĸ��ڵ�
	if (parent==my_node)
	{
	parent = replace;
	}
	else
	{
	//child��Ϊ��
	if (child!=nullptr)
	{
	child->parent = parent;
	}
	parent->left = child;
	replace->right = my_node->right;
	my_node->right->parent = replace;
	}

	replace->parent = my_node->parent;
	replace->color = my_node->color;
	replace->left = my_node->left;
	my_node->left->parent = replace;
	if (node_color==black)
	{
	remove_fix_up(child, parent);
	}
	delete my_node;
	}
	}
	//���������ʱ
	if (my_node->left != nullptr)
	{
	child = my_node->left;
	}
	//�ҽ�����ʱ
	if (my_node->right != nullptr)
	{
	child = my_node->right;
	}
	parent = my_node->parent;
	node_color = my_node->color;

	if (child != nullptr)
	{
	child->parent = parent;
	}
	if (parent != nullptr)
	{
	if (parent->left == my_node)
	{
	parent->left = child;
	}
	else
	{
	parent->right = child;
	}
	}
	else
	{
	root = child;
	}

	if (node_color == black)
	{
	remove_fix_up(child, parent);
	}
	delete my_node;
	*/

}

template<class T>
void RBTree<T>::remove_fix_up(node_pointer node)
{
	node_pointer parent = nullptr;
	node_pointer brother = nullptr;

	while ((node->color == black) && (root != node))
	{
		parent = node->parent;

		/* ǰ��1��nodeΪparent������ */
		if (node == parent->left) {
			brother = parent->right;

			/* Case 1: �ֵܽ��Ϊ��ɫ:  ��parentΪ֧��, �������� */
			if (brother->color == red)
			{
				parent->color = red;
				brother->color = black;
				left_rotate(parent);

				/* ���ս��node����, �ֵܽ���Ϊparent->rchild */
				brother = parent->right;

				/* ע��: ��ʱ����û�н���������Ҫ�������ĵ������� */
			}

			/* Case 2: �ֵܽ��Ϊ��ɫ(Ĭ��), ���ֵܽ���2���ӽ�㶼Ϊ��ɫ */
			if ((brother->left->color == black) && (brother->right->color == black))
			{
				brother->color = red;
				node = parent;
			}
			else {
				/* Case 3: �ֵܽ��Ϊ��ɫ(Ĭ��),
				�ֵܽڵ�����ӽ��Ϊ��ɫ, ���ӽ��Ϊ��ɫ:  ��brotherΪ֧��, �������� */
				if (brother->right->color == black)
				{
					brother->left->color = black;
					brother->color = red;
					right_rotate(brother);

					/* ���ս��node���� */
					brother = parent->right;
				}

				/* Case 4: �ֵܽ��Ϊ��ɫ(Ĭ��),
				�ֵܽ���Һ��ӽ��Ϊ��ɫ:  ��parentΪ֧��, �������� */


				//rbt_copy_color(brother, parent);
				//����
				brother->color = parent->color;
				brother->right->color = black;
				parent->color = black;

				left_rotate(parent);
				node = root;
			}
		}
		/* ǰ��2��nodeΪparent���Һ��� */
		else {
			brother = parent->left;

			/* Case 5: �ֵܽ��Ϊ��ɫ:  ��parentΪ֧��, �������� */
			if (brother->color == red)
			{
				parent->color = red;
				brother->color = black;
				right_rotate(parent);


				/* ���ս��node���� */
				brother = parent->left;

				/* ע��: ��ʱ����û�н���������Ҫ�������ĵ������� */
			}

			/* Case 6: �ֵܽ��Ϊ��ɫ(Ĭ��), ���ֵܽ���2���ӽ�㶼Ϊ��ɫ */
			if ((brother->left->color == black) && (brother->right->color == black))
			{
				brother->color = red;
				node = parent;
			}
			else {
				/* Case 7: �ֵܽ��Ϊ��ɫ(Ĭ��),
				�ֵܽڵ�����ӽ��Ϊ��ɫ, ���ӽ��Ϊ��ɫ:  ��brotherΪ֧��, �������� */
				if (brother->left->color == black)
				{
					brother->color = red;
					brother->right->color = black;
					left_rotate(brother);

					/* ���ս��node���� */
					brother = parent->left;
				}

				/* Case 8: �ֵܽ��Ϊ��ɫ(Ĭ��), �ֵܽ�����ӽ��Ϊ��ɫ: ��parentΪ֧��, �������� */
				//rbt_copy_color(brother, parent);
				brother->color = parent->color;
				brother->left->color = black;
				parent->color = black;
				right_rotate(parent);
				node = root;
			}
		}
	}
	node->color = black;
}

/* ���󣬴���
template<class T>
void RBTree<T>::remove_fix_up(node_pointer my_node, node_pointer parent)
{
node_pointer other_node;
while ((my_node!=root)&&((my_node==nullptr)||(my_node->color==black)))
{
if (parent->left==my_node)
{
other_node = parent->right;
//�ֵܽ��Ϊ��
if (other_node->color==red)
{
other_node->color = black;
parent->color = red;
left_rotate(parent);
other_node = parent->right;
}
//�ֵܽ��Ϊ�ڣ����ֵܽ�������ֽҲΪ��
else if (((other_node->left==nullptr)||(other_node->left->color==black))&&
((other_node->right == nullptr) || (other_node->right->color == black)))
{
other_node->color = red;
my_node = parent;
parent = my_node->parent;
}
else
{
//�ֵܽ��Ϊ�ڣ��ֵܽ�����ֽΪ�죬�Һ�ֽΪ��
if ((other_node->right==nullptr)||(other_node->right->color==black))
{
other_node->left->color = black;
other_node->color = red;
right_rotate(other_node);
other_node = parent->right;
}
other_node->color = parent->color;
parent->color = black;
other_node->right->color = black;
left_rotate(parent);
my_node = root;
break;
}
}
else			//�Գ���
{
other_node = parent->left;
if (other_node->color == red)
{
other_node->color = black;
parent->color = red;
right_rotate(parent);
other_node = parent->left;
}
//�ֵܽ��Ϊ�ڣ����ֵܽ�������ֽҲΪ��
else if (((other_node->left == nullptr) || (other_node->left->color == black)) &&
((other_node->right == nullptr) || (other_node->right->color == black)))
{
other_node->color = red;
my_node = parent;
parent = my_node->parent;
}
else
{
//�ֵܽ��Ϊ�ڣ��ֵܽ�����ֽΪ�죬�Һ�ֽΪ��
if ((other_node->right == nullptr) || (other_node->right->color == black))
{
other_node->left->color = black;
other_node->color = red;
left_rotate(other_node);
other_node = parent->left;
}
other_node->color = parent->color;
parent->color = black;
other_node->right->color = black;
right_rotate(parent);
my_node = root;
break;
}
}
}
if (my_node!=nullptr)
{
my_node->color = black;
}
}
*/
/////************************************************************