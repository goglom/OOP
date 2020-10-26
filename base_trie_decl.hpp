#pragma once
#include <map>
#include <string>

class base_trie
{
public:
	template<class ValueType, class NodeIt>
	class iterator_base;

	using value_type = int;
	using key_type = std::string;

protected:
	struct trie_node;
	using node_map = std::map<key_type::value_type, trie_node>;

	using node_map_it = node_map::iterator;
	using node_map_const_it = node_map::const_iterator;

	template<class Iterator>
	constexpr void iterator_validation();

	virtual trie_node& get_root() = 0;
	virtual trie_node const& get_root() const = 0;
	virtual key_type get_sub_key() const = 0;

public:
	using  iterator = iterator_base<value_type&, node_map_it>;
	using  const_iterator = iterator_base<value_type const&, node_map_const_it>;

	base_trie() = default;
	base_trie(base_trie const&) = default;
	base_trie(base_trie&&) = default;

	base_trie& operator=(base_trie const&) = default;
	base_trie& operator=(base_trie&&) = default;
	
	virtual ~base_trie() = default;

	template<class Key, class... ValueArgs>
	std::pair<iterator, bool> try_emplace(Key&& key, ValueArgs&& ...value_args);

	
	std::pair<iterator, bool> insert(key_type const& key, value_type const& value);	

	template<class InputIterator>
	void insert(InputIterator first, InputIterator last);

	iterator find(key_type const& key);
	const_iterator find(key_type const& key) const;
	
	value_type& operator[](key_type const& key);

	bool empty() const;

	// TODO: Fix problem with size of sub_trie, caused not decremented counter in base trie
	size_t size() const;

	iterator erase(iterator position);
	size_t erase(key_type const& key);
	void erase(iterator first, iterator last);

	void clear();

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

protected:
	virtual void decrement_nodes_count() = 0;
	virtual void increment_nodes_count() = 0;
	
	void swap(base_trie& other) noexcept;
	size_t value_nodes_count_ = 0;
};
