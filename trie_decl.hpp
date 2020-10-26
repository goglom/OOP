#pragma once
#include "base_trie_decl.hpp"


class trie final : public base_trie
{
public:
	class sub_trie;
	
	trie();
	trie(trie const& other);
	trie(trie&&) = default;
	trie(std::initializer_list < std::pair<key_type, value_type> > init_list);
	
	template<class InputIterator>
	trie(InputIterator first, InputIterator last);

	~trie() = default;

	trie& operator=(trie const& other);
	trie& operator=(trie&&) = default;
	
	void swap(trie& other) noexcept;

	sub_trie get_sub_trie(key_type const& sub_key);
	
private:
	node_map root_map_;

	trie_node& get_root() override;
	trie_node const& get_root() const override;
	key_type get_sub_key() const override;
	void decrement_nodes_count() override;
	void increment_nodes_count() override;
};