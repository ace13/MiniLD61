#pragma once

#include <string>
#include <iosfwd>

#define __PROFILE_COMBINE2(VAR1,VAR2) VAR1 ## VAR2
#define __PROFILE_COMBINE1(VAR1,VAR2) __PROFILE_COMBINE2(VAR1,VAR2)
#define PROFILE(NAME) ::Profiler::Block __PROFILE_COMBINE1(__prof_, __LINE__)(NAME);
#define PROFILE_CALL(NAME, CALL) ::Profiler::startBlock(NAME); CALL; ::Profiler::endBlock();

class Profiler
{
public:
	typedef float TimeSpan;
	typedef float TimePoint;
	class Iterator;
	class Node;

	static void startBlock(const std::string& name);
	static void endBlock();
	static void resetBlocks();
	static void releaseMemory();

	static Node* getRoot();

	static Iterator begin();
	static Iterator end();

	struct Block
	{
		Block(const std::string& name);
		~Block();
	};

	class Node
	{
	public:
		Node(const std::string& name, Node* parent = nullptr);
		~Node();

		Iterator begin() const;
		Iterator end() const;

		void startCall();
		bool endCall();

		void reset();
		void cleanup();

		Node* getChild(const std::string& name);

		friend std::ostream& operator<<(std::ostream& os, const Node& node)
		{
			node.toStream(os);
			return os;
		}
		void toStream(std::ostream&, unsigned int level = 0) const;

		std::string getName() const;

		TimeSpan getAvgTime() const;
		TimeSpan getMinTime() const;
		TimeSpan getMaxTime() const;
		TimeSpan getTotalTime() const;

		unsigned int getCallCount() const;

	private:
		std::string mName;
		TimePoint mStartTime;
		TimeSpan mMaxTime, mMinTime, mTotalTime;
		unsigned int mCallCount, mRecursion;

		Node *mParent, *mChild, *mSibling;

		friend class Profiler;
		friend class Iterator;
	};

	class Iterator
	{
	public:
		typedef std::ptrdiff_t difference_type;
        typedef Node value_type;
        typedef const Node& reference;
        typedef const Node* pointer;
        typedef std::forward_iterator_tag iterator_category;

		Iterator(const Iterator&);
		Iterator(Iterator&&);
		~Iterator();

		Iterator& operator=(const Iterator&);
		Iterator& operator++();
		Iterator& operator+=(int);

		reference operator*() const;
		pointer operator->() const;

		pointer getParent() const;

		friend bool operator==(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs.mCurChild == rhs.mCurChild &&
				lhs.mCurParent == rhs.mCurParent;
		}
		friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
		{
			return lhs.mCurChild != rhs.mCurChild ||
				lhs.mCurParent != rhs.mCurParent;
		}
		friend void swap(Profiler::Iterator& l, Profiler::Iterator& r)
		{
			using std::swap;

			swap(l.mCurChild, r.mCurChild);
			swap(l.mCurParent, r.mCurParent);
		}

	private:
		Iterator(const Node* node, bool atEnd = false);

		const Node *mCurChild, *mCurParent;

		friend class Profiler;
		friend class Node;
	};
};


