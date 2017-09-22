#pragma once
/*
date:9-17
author:zf
红黑树
*/

#include<iostream>
enum NodeColor
{	
	red,black
};

template<class T>
struct Node
{
	NodeColor color;	//结点颜色
	T key;		//关键字
	T data;
	Node* left;		//左孩纸
	Node* right;	//右孩纸
	Node* parent;	//父节点
};

template<class T>
class RBTree
{
public:
	//类型表
	typedef Node<T>*	node_pointer;	//结点指针
public:
	RBTree();
	~RBTree();
	void left_rotate(node_pointer x);	//左旋
	void right_rotate(node_pointer y);	//右旋
	void insert(node_pointer my_node);	//插入
	void insert_fix_up(node_pointer my_node);	//插入修正
	node_pointer get_root() { return root; }		//返回根节点




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
* 对红黑树的节点(x)进行左旋转
*
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(左旋)-->           / \                #
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
	x->right = y->left;		//x的右结点置为ly
	if (y->left!=nullptr)	//若ly不为空，ly的父节点置为x
	{
		y->left->parent = x;
	}

	node_pointer px = x->parent;
	y->parent = px;		//y的父节点变为x的父节点
	if (x==root)		//若x为根节点，则根节点置为y
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
* 对红黑树的节点(y)进行右旋转
* 右旋示意图(对节点y进行右旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
template<class T>
void RBTree<T>::right_rotate(node_pointer y)
{
	node_pointer x = y->left;
	y->left = x->right;		//y的左节点变为rx
	if ((x->right)!= nullptr)	//当rx非空时，将其父节点置为y
	{
		x->right->parent = y;		
	}
	
	node_pointer py = y->parent;	
	x->parent = py;		//x的父节点变为y的父节点
	if (y==root)		//若y为根节点,则根节点置为x
	{
		root = x;
	}
	else
	{
		if ((py->left)==y)		//如果y是它父节点的右孩子，则将x设py的右孩子
		{
			py->left = x;
		}
		else
		{
			py->right = x;		//如果y是它父节点的左孩子，则将x设py的左孩子
		}

	}
	y->parent = x;				//y的父节点变为x
	x->right = y;		//x的右结点为y
}


/*
核心思想就是分类讨论。。。。

① 情况说明：被插入的节点是根节点。
处理方法：直接把此节点涂为黑色。
② 情况说明：被插入的节点的父节点是黑色。
处理方法：什么也不需要做。节点被插入后，仍然是红黑树。
③ 情况说明：被插入的节点的父节点是红色。
处理方法：那么，该情况与红黑树的相冲突,使用insert_fix_up()修正
*/
template<class T>
void RBTree<T>::insert(node_pointer my_node)
{
	//利用二叉查找树的规则，将结点插入
	my_node->right = nullptr;
	my_node->left = nullptr;
	my_node->parent = nullptr;
	if (root==nullptr)			//被插入的是根节点
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
		//修正插入后的红黑树
		insert_fix_up(my_node);
	}
}


template<class T>
void RBTree<T>::insert_fix_up(node_pointer my_node)
{
	node_pointer parent_node;
	while ((my_node->parent!=nullptr)&&(my_node->parent->color==red))			//当父节点存在且为红色时进入情况③，否则跳过循环
	{
		parent_node = my_node->parent;		//父节点
		node_pointer granpa = parent_node->parent;	//祖父结点	
		if (parent_node==granpa->left)	//若父节点是祖父节点的左节点
		{
			node_pointer uncle = granpa->right;
			//叔叔结点为黑(包括为null,开始未考虑到，出bug了)
			if ((uncle==nullptr)||(uncle->color==black))
			{
				//叔叔结点为黑，且当前节点为右孩纸
				if (parent_node->right == my_node)
				{
					node_pointer temp;
					left_rotate(parent_node);
					temp = parent_node;
					parent_node = my_node;
					my_node = temp;
				}
				else		//为左孩纸
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
			//叔叔结点为黑
			if ((uncle==nullptr)||(uncle->color==black))
			{
				//叔叔结点为黑色，且当前结点为左孩纸
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
		if (parent_node->parent->left== parent_node)		//父节点为左孩纸时
		{
			uncle_node = parent_node->parent->right;
			//叔叔结点为红色时，父叔为黑，祖父为红，递归祖父
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
				if (parent_node->left==my_node)			//叔叔结点为黑色且当前结点为左孩纸,父黑，祖父红，祖父右旋
				{
					parent_node->color = black;
					parent_node->parent->color = red;
					right_rotate(parent_node->parent);
				}
				else								//叔叔结点为黑色且当前结点为右孩纸时，父节点成为新的结点，并左旋
				{
					my_node = parent_node;
					left_rotate(my_node);
				}	
			}
		}
		else								//为右孩纸时
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
				//待定
				if (parent_node->right == my_node)			//叔叔结点为黑色且当前结点为左孩纸,父黑，祖父红，祖父右旋
				{
					parent_node->color = black;
					parent_node->parent->color = red;
					right_rotate(parent_node->parent);
				}
				else								//叔叔结点为黑色且当前结点为右孩纸时，父节点成为新的结点，并左旋
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
