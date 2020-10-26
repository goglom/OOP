#pragma once
#include "trie_decl.hpp"

#include <optional>

template<class ValueType, class NodeIt>
class base_trie::iterator_base
{
public:
	// Required iterator aliases ------------------------//
	using iterator_category = std::forward_iterator_tag;
	using value_type = std::pair<key_type, ValueType>;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
	//--------------------------------------------------//

	using node_iterator = NodeIt;

private:
	node_iterator current_node_;
	std::optional<value_type> value_;
	std::reference_wrapper<trie_node const> root_node_;

public:
	template<class Key>
	iterator_base(
		node_iterator node_it,
		Key&& key,
		trie_node const& root_node
	);
	iterator_base(
		node_iterator node_it,
		trie_node const& root_node
	);
	iterator_base(iterator_base const&) = default;
	iterator_base(iterator_base&&) = default;

	value_type operator*();
	pointer operator->();

	bool operator==(iterator_base const& rsh) const;
	bool operator!=(iterator_base const& rsh) const;

	iterator_base& operator=(iterator_base const&) = default;
	iterator_base& operator=(iterator_base&&) = default;

	~iterator_base() = default;

	iterator_base& operator++();
	iterator_base operator++(int);

private:
	friend trie_node;
	friend trie;

	void immersion();
	void to_parent();

	trie_node& get_parent_node();
	node_iterator get_parent_it();

	void replace_value(base_trie::value_type& value);
	void replace_value(base_trie::value_type const& value);
	
	key_type& get_key();
	
	bool is_leaf() const;
	bool has_value() const;
	bool is_root() const;
	bool to_next_node();
};