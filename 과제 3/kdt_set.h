#pragma once

#include <iostream>
#include <functional>
#include <assert.h>

namespace kdt
{
	template<class _Ty>
	class set;
	template<class _Ty>
	struct FBSTNode;

	template<typename _Ty>
	class _Set_Iterator
	{
	public:
		template<class _Ty>
		friend class set;
		_Set_Iterator() = default;
		_Set_Iterator(set<_Ty>* InSet, FBSTNode<_Ty>* InNode)
			: Set(InSet),
			Node(InNode) {}
		_Set_Iterator(const _Set_Iterator&) = default;

		_Set_Iterator& operator=(const _Set_Iterator&) = default;
		_Set_Iterator& operator++()
		{
			Node = Set->BST_Successor(Node);
			return *this;
		}
		_Set_Iterator& operator--()
		{
			Node = Set->BST_Predecessor(Node);
			return *this;
		}
		_NODISCARD _Ty& operator*() const noexcept
		{
			_ASSERT(Node);
			return Node->Key;
		}
		_NODISCARD _Ty& operator->() const noexcept
		{
			_ASSERT(Node);
			return Node->Key;
		}
		bool operator==(const _Set_Iterator& InOther) const
		{
			return (Node->Key == InOther.Node->Key);
		}
		bool operator!=(const _Set_Iterator& InOther) const
		{
			return !(*this == InOther);
		}

	private:
		set<_Ty>* Set = nullptr;
		FBSTNode<_Ty>* Node = nullptr;
	};


	template<typename _Ty>
	struct FBSTNode
	{
		_Ty Key{};

		FBSTNode* Parent = nullptr;
		FBSTNode* Left = nullptr; // Left Child
		FBSTNode* Right = nullptr; // Right Child

		FBSTNode() = default;
		FBSTNode(const _Ty& InKey, FBSTNode* InParent, FBSTNode* InLeft, FBSTNode* InRight)
			: Key(InKey),
			Parent(InParent),
			Left(InLeft),
			Right(InRight)
		{}
	};
	
	template<typename _Ty>
	class set
	{
	public:
		using iterator = _Set_Iterator<_Ty>;
		using Node = FBSTNode<_Ty>;

		set() = default;
		set(const set& InOther);
		set(set&& InOther) noexcept;
		~set();

		iterator insert(const _Ty& InKey);
		_NODISCARD iterator find(const _Ty& InKey);
		iterator erase(const iterator& It);

		_NODISCARD iterator begin();
		_NODISCARD iterator end();

		void print_inorder();
	protected:
		void BST_Insert(Node* z);
		Node* Iterative_Tree_Search(Node* x, const _Ty& key);

		// key 값 순서
		void Inorder_Tree_Walk(Node* x, std::function<void(Node*)> Function);
		// 부모 -> 자식 순서
		void Preorder_Tree_Walk(Node* x, std::function<void(Node*)> Function);
		// 자식 -> 부모 순서
		void Postorder_Tree_Walk(Node* x, std::function<void(Node*)> Function);

		// 후임자 찾기
		Node* BST_Successor(Node* x);
		Node* BST_Minimum(Node* x);
		// 전임자 찾기
		Node* BST_Predecessor(Node* x);
		Node* BST_Maximum(Node* x);

		Node* BST_Delete(Node* InNode);
	private:
		FBSTNode<_Ty>* RootNode = nullptr;

	};

}

#include "kdt_set.hpp"