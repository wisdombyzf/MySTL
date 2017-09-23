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
struct RBTNode
{
	NodeColor color;	//结点颜色
	T key;		//关键字
	T data;
	RBTNode* left;		//左孩纸
	RBTNode* right;	//右孩纸
	RBTNode* parent;	//父节点
};

template<class T>
class RBTree
{
public:
	//类型表
	typedef RBTNode<T>*	node_pointer;	//结点指针
public:
	RBTree();
	~RBTree();
	void left_rotate(node_pointer x);	//左旋
	void right_rotate(node_pointer y);	//右旋
	void insert(node_pointer my_node);	//插入
	void insert_fix_up(node_pointer my_node);	//插入修正
	void remove(node_pointer my_node);		//删除
	void remove(RBTNode<T>* &root, RBTNode<T> *node);
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);
	void remove_fix_up(node_pointer my_node);	//删除修正
	node_pointer get_root() { return root; }		//返回根节点
	node_pointer find(T value);			//查找树中是否存value元素，存在则返回改元素的指针，不存在则返回nullptr

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

template<class T>
RBTNode<T>* RBTree<T>::find(T value)
{
	
	node_pointer temp = root;
	while (true)
	{
		if (value==temp->key)		//等于时
		{
			return temp;
		}
		else if (value>temp->key)		//大于时，向右子树
		{
			if (temp->right==nullptr)		//右子树不存在时，返回nullptr
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
			if (temp->left==nullptr)		//左子树不存在时，返回nullptr
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
* 红黑树删除修正函数
*
* 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 待修正的节点
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
				// Case 1: x的兄弟w是红色的  
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->right || rb_is_black(other->right))
				{
					// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
				// Case 1: x的兄弟w是红色的  
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->left || rb_is_black(other->left))
				{
					// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
* 删除结点(node)，并返回被删除的结点
*
* 参数说明：
*     root 红黑树的根结点
*     node 删除的结点
*/
template <class T>
void RBTree<T>::remove(RBTNode<T> *node)
{
	RBTNode<T> *child, *parent;
	RBTColor color;

	// 被删除节点的"左右孩子都不为空"的情况。
	if ((node->left != NULL) && (node->right != NULL))
	{
		// 被删节点的后继节点。(称为"取代节点")
		// 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
		RBTNode<T> *replace = node;

		// 获取后继节点
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node节点"不是根节点(只有根节点不存在父节点)
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			// "node节点"是根节点，更新根节点。
			root = replace;

		// child是"取代节点"的右孩子，也是需要"调整的节点"。
		// "取代节点"肯定不存在左孩子！因为它是一个后继节点。
		child = replace->right;
		parent = rb_parent(replace);
		// 保存"取代节点"的颜色
		color = rb_color(replace);

		// "被删除节点"是"它的后继节点的父节点"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child不为空
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
	// 保存"取代节点"的颜色
	color = node->color;

	if (child)
		child->parent = parent;

	// "node节点"不是根节点
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
//*******写崩了的代码。。。。。待续+1s,先用现有的。。。

template<class T>
void RBTree<T>::remove(node_pointer my_node)
{
	//换种方式，由简单到复杂,并以可读性为主
	//结点为叶子结点，无左孩纸，也无右孩纸时
	if ((my_node->right == nullptr) && (my_node->left == nullptr))
	{
		node_pointer node_parent = my_node->parent;
		//结点为叶子结点，且为红时
		if ((my_node->color == red))
		{
			//为左结点时
			if (node_parent->left == my_node)
			{
				node_parent->left = nullptr;
				delete my_node;
				return;
			}
			else	//右结点时
			{
				node_parent->right = nullptr;
				delete my_node;
				return;
			}
		}
		else		//结点为叶子结点，且为黑时
		{
			//为根节点时
			if (root == my_node)
			{
				root = nullptr;
				delete my_node;
				return;
			}
			return  remove_fix_up(my_node);
		}

	}

	//结点有只有左孩纸时（结点肯定为黑，左孩纸肯定为红）
	if ((my_node->right == nullptr) && (my_node->left != nullptr))
	{
		return  remove_fix_up(my_node);
	}

	//结点有只有右孩纸时（结点肯定为黑，右孩纸肯定为红）
	if ((my_node->left == nullptr) && (my_node->right != nullptr))
	{
		return  remove_fix_up(my_node);
	}

	//结点既有左孩纸，又有右孩子时
	if ((my_node->left != nullptr) && (my_node->right != nullptr))
	{
		//找出后继结点(右子树的)
		node_pointer replace = my_node->right;
		while (replace->left != nullptr)
		{
			replace = replace->left;
		}

		//后继结点替换原结点，递归删除后继结点
		my_node->key = replace->key;
		my_node->data = replace->data;

		//后继结点肯定没有左节点，用后继结点右结点取代后继结点
		//当后继结点为红时（其肯定没有右结点，可直接删除）
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
		else   //当后继结点为黑时
		{

			return remove_fix_up(replace);
		}
	}
	/*  //不知道那崩了，放弃
	node_pointer parent = nullptr;		//取代结点的父节点
	node_pointer child = nullptr;		//取代结点的右孩纸（后继结点，肯定不存在左孩纸）
	int node_color;
	//当左右结点都存在时
	if ((my_node->left!=nullptr)&&(my_node->right!=nullptr))
	{
	node_pointer replace = my_node;		//用replace取代删除结点
	//获取后继结点
	replace = replace->right;
	while (replace->left!=nullptr)
	{
	replace = replace->left;
	}

	if (my_node==root)		//如果删除结点为根节点
	{
	root = replace;
	}
	else
	{
	node_pointer parent_temp = my_node->parent;
	//将结点的父节点指向新节点
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

	//若被删除结点是后继结点的父节点
	if (parent==my_node)
	{
	parent = replace;
	}
	else
	{
	//child不为空
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
	//当左结点存在时
	if (my_node->left != nullptr)
	{
	child = my_node->left;
	}
	//右结点存在时
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

		/* 前提1：node为parent的左孩子 */
		if (node == parent->left) {
			brother = parent->right;

			/* Case 1: 兄弟结点为红色:  以parent为支点, 左旋处理 */
			if (brother->color == red)
			{
				parent->color = red;
				brother->color = black;
				left_rotate(parent);

				/* 参照结点node不变, 兄弟结点改为parent->rchild */
				brother = parent->right;

				/* 注意: 此时处理还没有结束，还需要做后续的调整处理 */
			}

			/* Case 2: 兄弟结点为黑色(默认), 且兄弟结点的2个子结点都为黑色 */
			if ((brother->left->color == black) && (brother->right->color == black))
			{
				brother->color = red;
				node = parent;
			}
			else {
				/* Case 3: 兄弟结点为黑色(默认),
				兄弟节点的左子结点为红色, 右子结点为黑色:  以brother为支点, 右旋处理 */
				if (brother->right->color == black)
				{
					brother->left->color = black;
					brother->color = red;
					right_rotate(brother);

					/* 参照结点node不变 */
					brother = parent->right;
				}

				/* Case 4: 兄弟结点为黑色(默认),
				兄弟结点右孩子结点为红色:  以parent为支点, 左旋处理 */


				//rbt_copy_color(brother, parent);
				//待定
				brother->color = parent->color;
				brother->right->color = black;
				parent->color = black;

				left_rotate(parent);
				node = root;
			}
		}
		/* 前提2：node为parent的右孩子 */
		else {
			brother = parent->left;

			/* Case 5: 兄弟结点为红色:  以parent为支点, 右旋处理 */
			if (brother->color == red)
			{
				parent->color = red;
				brother->color = black;
				right_rotate(parent);


				/* 参照结点node不变 */
				brother = parent->left;

				/* 注意: 此时处理还没有结束，还需要做后续的调整处理 */
			}

			/* Case 6: 兄弟结点为黑色(默认), 且兄弟结点的2个子结点都为黑色 */
			if ((brother->left->color == black) && (brother->right->color == black))
			{
				brother->color = red;
				node = parent;
			}
			else {
				/* Case 7: 兄弟结点为黑色(默认),
				兄弟节点的右子结点为红色, 左子结点为黑色:  以brother为支点, 左旋处理 */
				if (brother->left->color == black)
				{
					brother->color = red;
					brother->right->color = black;
					left_rotate(brother);

					/* 参照结点node不变 */
					brother = parent->left;
				}

				/* Case 8: 兄弟结点为黑色(默认), 兄弟结点左孩子结点为红色: 以parent为支点, 右旋处理 */
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

/* 有误，待定
template<class T>
void RBTree<T>::remove_fix_up(node_pointer my_node, node_pointer parent)
{
node_pointer other_node;
while ((my_node!=root)&&((my_node==nullptr)||(my_node->color==black)))
{
if (parent->left==my_node)
{
other_node = parent->right;
//兄弟结点为红
if (other_node->color==red)
{
other_node->color = black;
parent->color = red;
left_rotate(parent);
other_node = parent->right;
}
//兄弟结点为黑，且兄弟结点的俩孩纸也为黑
else if (((other_node->left==nullptr)||(other_node->left->color==black))&&
((other_node->right == nullptr) || (other_node->right->color == black)))
{
other_node->color = red;
my_node = parent;
parent = my_node->parent;
}
else
{
//兄弟结点为黑，兄弟结点的左孩纸为红，右孩纸为黑
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
else			//对称树
{
other_node = parent->left;
if (other_node->color == red)
{
other_node->color = black;
parent->color = red;
right_rotate(parent);
other_node = parent->left;
}
//兄弟结点为黑，且兄弟结点的俩孩纸也为黑
else if (((other_node->left == nullptr) || (other_node->left->color == black)) &&
((other_node->right == nullptr) || (other_node->right->color == black)))
{
other_node->color = red;
my_node = parent;
parent = my_node->parent;
}
else
{
//兄弟结点为黑，兄弟结点的左孩纸为红，右孩纸为黑
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