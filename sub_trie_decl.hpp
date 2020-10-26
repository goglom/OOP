#pragma once
#include "trie_decl.hpp"

//TODO: The class sub_trie have problems with size of elements.
// Need some mechanism to evaluate size of sub trie
// I think, bypass by iterators is not effective,
// cause of class iterator_base contains string, e.g.
// heavy object. May be exist more effective way to calculate size of sub trie... 

class trie::sub_trie final : public base_trie
{
public:
	explicit sub_trie(trie& base_trie, trie_node& node, key_type const& prefix);
	sub_trie(sub_trie const&) = default;
	sub_trie(sub_trie&&) = default;

	sub_trie& operator=(sub_trie const&) = default;
	sub_trie& operator=(sub_trie&&) = default;

	~sub_trie() = default;
private:
	std::reference_wrapper<trie> base_trie_;
	std::reference_wrapper<trie_node> root_node_;
	key_type prefix_;

	key_type get_sub_key() const override;
	trie_node const& get_root() const override;
	trie_node& get_root() override;
	void decrement_nodes_count() override;
	void increment_nodes_count() override;
};