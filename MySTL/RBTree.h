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
struct Node
{
	NodeColor color;	//�����ɫ
	T key;		//�ؼ���
	T data;
	Node* left;		//��ֽ
	Node* right;	//�Һ�ֽ
	Node* parent;	//���ڵ�
};

template<class T>
class RBTree
{
public:
	//���ͱ�
	typedef Node<T>*	node_pointer;	//���ָ��
public:
	RBTree();
	~RBTree();
	void left_rotate(node_pointer x);	//����
	void right_rotate(node_pointer y);	//����
	void insert(node_pointer my_node);	//����
	void insert_fix_up(node_pointer my_node);	//��������
	void remove(node_pointer my_node);		//ɾ��
	void remove_fix_up(node_pointer child,node_pointer parent);	//ɾ������
	node_pointer get_root() { return root; }		//���ظ��ڵ�
	node_pointer find(T value);			//���������Ƿ��valueԪ�أ������򷵻ظ�Ԫ�ص�ָ�룬�������򷵻�nullptr





private:
	node_pointer root;

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
void RBTree<T>::remove(node_pointer my_node)
{
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
	else
	{
		//���������ʱ
		if (my_node->left!=nullptr)
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
		if (child!=nullptr)
		{
			child->parent = parent;
		}
		if (parent!=nullptr)
		{
			if (parent->left==my_node)
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

		if (node_color==black)
		{
			remove_fix_up(child,parent);
		}
		delete my_node;
	}

}

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

template<class T>
Node<T>* RBTree<T>::find(T value)
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



