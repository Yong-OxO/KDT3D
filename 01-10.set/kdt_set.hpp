#include "kdt_set.h"

namespace kdt
{

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

	}

	template<typename _Ty>
	inline kdt::set<_Ty>::~set()
	{
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::insert(const _Ty& InKey)
	{
		Node* NewNode = new Node(InKey, nullptr, nullptr, nullptr);
		BST_Insert(NewNode);
		return iterator();
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::find(const _Ty& InKey)
	{
		return iterator();
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::erase(const iterator& It)
	{
		return iterator();
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::begin()
	{
		return iterator();
	}

	template<typename _Ty>
	inline set<_Ty>::iterator set<_Ty>::end()
	{
		return iterator();
	}

	template<typename _Ty>
	inline void set<_Ty>::print_inorder()
	{
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
	}

	template<typename _Ty>
	inline void set<_Ty>::Postorder_Tree_Walk(Node* x, std::function<void(Node*)> Function)
	{
		if (x == nullptr) { return; }

		Postorder_Tree_Walk(x->Left, Function);
		Postorder_Tree_Walk(x->Right, Function);
		Function(x);
	}
}