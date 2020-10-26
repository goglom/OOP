#pragma once
#include "sub_trie_decl.hpp"

inline trie::sub_trie::sub_trie(trie& base_trie, trie_node& node, key_type const& prefix)
	:
	base_trie_(base_trie),
	root_node_(node),
	prefix_(prefix)
{
	for (auto && value : *this)
	{
		++value_nodes_count_;
	}
}

inline base_trie::key_type trie::sub_trie::get_sub_key() const
{
	return prefix_;
}

inline base_trie::trie_node const& trie::sub_trie::get_root() const
{
	return root_node_;
}

inline base_trie::trie_node& trie::sub_trie::get_root()
{
	return root_node_;
}

inline void trie::sub_trie::decrement_nodes_count()
{
	--value_nodes_count_;
	base_trie_.get().decrement_nodes_count();
}

inline void trie::sub_trie::increment_nodes_count()
{
	++value_nodes_count_;
	base_trie_.get().increment_nodes_count();
}
