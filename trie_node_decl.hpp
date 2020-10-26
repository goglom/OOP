#pragma once
#include "base_trie_decl.hpp"
#include "iterator_base_decl.hpp"

#include <memory>

struct base_trie::trie_node final
{
	trie_node() = default;
	explicit trie_node(trie_node* parent_node_ptr);

	template<class... Args>
	void set_value(Args&& ...args);

	bool operator==(trie_node const& rsh) const;

	template<class Key>
	iterator begin(Key&& sub_key);

	template<class Key>
	const_iterator begin(Key&& sub_key) const;

	iterator end();
	const_iterator end() const;
	
	template<class Key, class... ValueArgs>
	std::pair<iterator, bool> try_emplace(Key&& key, ValueArgs&&... value_args);

	iterator find(key_type const& prefix, key_type const& key);
	const_iterator find(key_type const& prefix, key_type const& key) const;

	trie_node* try_find_node(key_type const& key);
	trie_node const* try_find_node(key_type const& key) const;

	iterator erase(iterator position);
	size_t erase(key_type const& key);

	~trie_node() = default;
	
	void clear_value();
	bool is_leaf() const;
	bool has_value() const;
	value_type& get_value();
	value_type const& get_value() const;

	node_map children{};
	node_map_it to_self{};
	trie_node* parent = nullptr;
	std::unique_ptr<value_type> value_ptr{};
};