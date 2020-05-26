#ifndef RBTREE_H
#define RBTREE_H

#include <type_traits>

namespace A5
{
	class RBTree
	{
	public:
		enum class NodeColor : std::size_t
		{
			BLACK = 0,
			RED = 2
		};
		class Node
		{
		public:
			std::size_t m_PrevSize;
		private:
			Node* m_Parent;
		public:
			Node* m_Right;
			Node* m_Left;
			std::size_t m_Value;

			inline Node* GetParentRaw()
			{
				return m_Parent;
			}

			inline Node* GetParent()
			{
				return reinterpret_cast<Node*>((std::size_t)m_Parent >> 2 << 2);
			}

			inline void SetParent(Node* p)
			{
				m_Parent = reinterpret_cast<Node*>((std::size_t)p | 1);
			}

			inline NodeColor GetColor()
			{
				if (m_Parent == nullptr)
					return NodeColor::BLACK;
				return (std::size_t)m_Parent & 2 ? NodeColor::RED : NodeColor::BLACK;
			}

			inline void SetColor(NodeColor color)
			{
				m_Parent = reinterpret_cast<Node*>((std::size_t)m_Parent | static_cast<std::underlying_type<NodeColor>::type>(color));
			}
		};
	private:
		Node* m_Nil;
		Node* m_Root;
	public:
		RBTree();
		void Init(Node* nil);
		Node* Search(const int v);
		Node* SearchBest(const int v);
		void Insert(Node* z);
		void Remove(Node* z);
		Node* Successor(Node* x);
	private:
		void InsertFixup(Node* z);
		void RemoveFixup(Node* z);
		void Transplant(Node* u, Node* v);
		void LeftRotate(Node* x);
		void RightRotate(Node* x);
	};
};

#endif // !RBTREE_H