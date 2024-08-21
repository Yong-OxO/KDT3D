#include "kdt_set.h"

namespace kdt
{
	// 부모 -> 자식 순으로 복사해서 형태 유지
	template<typename _Ty>
	inline kdt::set<_Ty>::set(const set& InOther)
	{
		Preorder_Tree_Walk(InOther.RootNode,
			[this](Node* x)
			{
				insert(x->Key);
			});
	}

	template<typename _Ty> 
	inline kdt::set<_Ty>::set(set&& InOther) noexcept
	{
		RootNode = InOther.RootNode;
		InOther.RootNode = nullptr;
	}

	template<typename _Ty>
	inline kdt::set<_Ty>::~set()
	{
		Postorder_Tree_Walk(RootNode,
			[](Node* x)
			{
				delete x;
			});
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::insert(const _Ty& InKey)
	{
		Node* NewNode = new Node(InKey, nullptr, nullptr, nullptr);
		BST_Insert(NewNode);
		return iterator(this, NewNode);
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::find(const _Ty& InKey)
	{
		Iterative_Tree_Search(RootNode, InKey);
		return iterator(this, Iterative_Tree_Search(RootNode, InKey));
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::erase(const iterator& It)
	{
		Node* SuccessorNode = BST_Delete(It.Node);
		return iterator(this, SuccessorNode);
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::begin()
	{
		return iterator(this, BST_Minimum(RootNode));
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::end()
	{
		return iterator(this, BST_Maximum(RootNode));
	}

	template<typename _Ty>
	inline void set<_Ty>::print_inorder()
	{
		std::cout << std::endl << "Inorder_Tree_Walk Print start\n";
		Inorder_Tree_Walk(RootNode, 
			[](Node* x)
			{
				std::cout << "Key : " << x->Key << std::endl;
			});
		std::cout << "Inorder_Tree_Walk Print end\n";
	}

	template<typename _Ty>
	inline void kdt::set<_Ty>::BST_Insert(Node* z)
	{
		if (RootNode == nullptr)
		{
			RootNode = z;
			return;
		}
		Node* x = RootNode;
		// 이중if문 대신 x값 저장용
		// Node* y = nullptr;

		while (x != nullptr)
		{	
			if (x->Key > z->Key)
			{
				if (x->Left == nullptr)
				{
					z->Parent = x;
					x->Left = z;
					return;
				}
				x = x->Left;
			}
			else if (x->Key < z->Key)
			{
				if (x->Right == nullptr)
				{
					z->Parent = x;
					x->Right = z;
					return;
				}
				x = x->Right;
			}
			else
			{
				assert(false);
			}
		}
	}

	template<typename _Ty>
	inline set<_Ty>::Node* set<_Ty>::Iterative_Tree_Search(Node* x, const _Ty& key)
	{
		while (x->Key != key && x != nullptr)
		{
			if (x->Key > key)
			{
				x = x->Left;
			}
			else if (x->Key < key)
			{
				x = x->Right;
			}
		}
		return x;
	}

	template<typename _Ty>
	inline void set<_Ty>::Inorder_Tree_Walk(Node* x, std::function<void(Node*)> Function)
	{
		if (x == nullptr) { return; }

		Inorder_Tree_Walk(x->Left, Function);
		Function(x);
		Inorder_Tree_Walk(x->Right, Function);
	}

	template<typename _Ty>
	inline void set<_Ty>::Preorder_Tree_Walk(Node* x, std::function<void(Node*)> Function)
	{
		Function(x);
		Preorder_Tree_Walk(x->Left, Function);
		Preorder_Tree_Walk(x->Right, Function);
	}

	template<typename _Ty>
	inline void set<_Ty>::Postorder_Tree_Walk(Node* x, std::function<void(Node*)> Function)
	{
		if (x == nullptr) { return; }

		Postorder_Tree_Walk(x->Left, Function);
		Postorder_Tree_Walk(x->Right, Function);
		Function(x);
	}

	// 후임자
	template<typename _Ty>
	inline set<_Ty>::Node* set<_Ty>::BST_Successor(Node* x)
	{
		if (x->Right != nullptr)
		{
			return BST_Minimum(x->Right);
		}

		Node* y = x;
		while (x->Parent == nullptr && y->Right == x)
		{
			x = y;
			y = y->Parent;
		}

		return y;
	}

	template<typename _Ty>
	inline set<_Ty>::Node* set<_Ty>::BST_Minimum(Node* x)
	{
		while (x->Left != nullptr)
		{
			x = x->Left;
		}
		return x;
	}

	// 전임자
	template<typename _Ty>
	inline set<_Ty>::Node* set<_Ty>::BST_Predecessor(Node* x)
	{
		if (x->Left != nullptr)
		{
			return(BST_Maximum(x->Left));
		}

		Node* y = x->Parent;
		while (x->Parent != nullptr && y->Left == x)
		{
			x = y;
			y = y->Parent;
		}
		
		return y;
	}

	template<typename _Ty>
	inline set<_Ty>::Node* set<_Ty>::BST_Maximum(Node* x)
	{
		while (x->Right != nullptr)
		{
			x = x->Right;
		}
		return x;
	}
	template<typename _Ty>
	inline set<_Ty>::Node* set<_Ty>::BST_Delete(Node* InNode)
	{
		Node* OutNode = BST_Successor(InNode);
		Node* ParentNode = InNode->Parent;
		Node* LeftNode = InNode->Left;
		Node* RightNode = InNode->Right;

		if (LeftNode)
		{
			if (LeftNode->Parent == nullptr)
			{
				RootNode = LeftNode;
			}

			Node* LeftRightNode = LeftNode->Right;
			LeftNode->Parent = ParentNode;
			LeftNode->Right = RightNode;		
			if (ParentNode)	{ ParentNode->Left = LeftNode; }
			RightNode->Parent = LeftNode;

			Node* x = BST_Minimum(LeftNode->Right);
			if (LeftRightNode && x)
			{
				x->Left = LeftRightNode;
				LeftRightNode->Parent = x;
			}
		}
		else if (RightNode)
		{
			if (ParentNode) { ParentNode->Right = RightNode; }
			RightNode->Parent = ParentNode;

			if (RightNode->Parent == nullptr)
			{
				RootNode = RightNode;
			}
		}
		else
		{
			if (InNode == ParentNode->Right)
			{
				ParentNode->Right = nullptr;
				InNode->Parent = nullptr;
			}
			else
			{
				if (InNode == ParentNode->Left)
				{
					ParentNode->Left = nullptr;
					InNode->Parent = nullptr;
				}
			}
		}
		delete InNode;
		return OutNode;
	}
}