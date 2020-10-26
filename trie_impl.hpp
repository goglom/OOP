#pragma once
#include "trie_decl.hpp"
#include "sub_trie_decl.hpp"

//---- 1) Public methods ------------------------------------------------------------//
inline trie::trie()
{
	auto [root_node_it, is_inserted] =
		root_map_.try_emplace('\0', nullptr);

	root_node_it->second.to_self = root_node_it;
}

inline trie::trie(trie const& other)
	: base_trie(other)
{
	trie().swap(*this);
	insert(other.begin(), other.end());
}

inline trie::trie(std::initializer_list<std::pair<key_type, value_type>> init_list)
{
	trie(init_list.begin(), init_list.end()).swap(*this);
}

template <class InputIterator>
trie::trie(InputIterator first, InputIterator last)
{
	trie().swap(*this);
	insert(first, last);
}

inline void trie::swap(trie& other) noexcept
{
	base_trie::swap(other);
	std::swap(root_map_, other.root_map_);
}

inline trie::sub_trie trie::get_sub_trie(key_type const& sub_key)
{
	auto* found = get_root().try_find_node(sub_key);
	
	if (found != nullptr)
	{
		return sub_trie(*this, *found, sub_key);
	}
	return sub_trie(*this,get_root(), "");
}

inline trie& trie::operator=(trie const& other)
{
	if (this == &other)
	{
		return *this;
	}
	trie(other).swap(*this);

	return  *this;
}

//---- 2) Private methods -----------------------------------------------------------//
inline base_trie::trie_node& trie::get_root()
{
	return root_map_.begin()->second;
}

inline base_trie::trie_node const& trie::get_root() const
{
	return root_map_.begin()->second;
}

inline base_trie::key_type trie::get_sub_key() const
{
	return { "" };
}

inline void trie::decrement_nodes_count()
{
	--value_nodes_count_;
}

inline void trie::increment_nodes_count()
{
	++value_nodes_count_;
}
