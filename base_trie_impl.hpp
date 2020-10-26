#pragma once
#include <utility>

#include "base_trie_decl.hpp"
#include "iterator_base_decl.hpp"
#include "trie_node_decl.hpp"

template <class Iterator>
constexpr void base_trie::iterator_validation()
{
	static_assert(
		std::is_base_of_v<std::input_iterator_tag,
		typename std::iterator_traits<Iterator>::iterator_category>,
		"Iterator does not derived of std::input_iterator_tag"
	);
}

template <class Key, class ... ValueArgs>
std::pair<base_trie::iterator, bool> base_trie::try_emplace(Key&& key, ValueArgs&& ...value_args)
{
	auto inserted = get_root().try_emplace(
		std::forward<Key>(key),
		std::forward<ValueArgs>(value_args)...
	);
	if (inserted.second)
	{
		increment_nodes_count();
	}
	return inserted;
}

inline std::pair<base_trie::iterator, bool>
base_trie::insert(key_type const& key, value_type const& value)
{
	return try_emplace(key, value);
}

inline base_trie::iterator base_trie::find(key_type const& key)
{
	return get_root().find(get_sub_key(), key);
}

inline base_trie::const_iterator base_trie::find(key_type const& key) const
{
	return get_root().find(get_sub_key(), key);
}

template <class InputIterator>
void base_trie::insert(InputIterator first, InputIterator last)
{
	iterator_validation<InputIterator>();

	while (first != last)
	{
		insert(first->first, first->second);
		++first;
	}
}

inline base_trie::value_type& base_trie::operator[](key_type const& key)
{
	return try_emplace(key).first->second;
}

inline bool base_trie::empty() const
{
	return get_root().children.empty();
}

inline size_t base_trie::size() const
{
	return value_nodes_count_;
}

inline base_trie::iterator base_trie::erase(iterator position)
{
	decrement_nodes_count();
	return get_root().erase(std::move(position));
}

inline size_t base_trie::erase(key_type const& key)
{
	decrement_nodes_count();
	return get_root().erase(key);
}

inline void base_trie::erase(iterator first, iterator last)
{
	while (first != last)
	{
		erase(first++);
	}
}

inline void base_trie::clear()
{

	erase(begin(), end());
}

inline base_trie::iterator base_trie::begin()
{
	return get_root().begin(get_sub_key());
}

inline base_trie::const_iterator base_trie::begin() const
{
	return get_root().begin(get_sub_key());
}

inline base_trie::const_iterator base_trie::cbegin() const
{
	return begin();
}

inline base_trie::iterator base_trie::end()
{
	return get_root().end();
}

inline base_trie::const_iterator base_trie::end() const
{
	return get_root().end();
}

inline base_trie::const_iterator base_trie::cend() const
{
	return  end();
}

inline void base_trie::swap(base_trie& other) noexcept
{
	std::swap(value_nodes_count_, other.value_nodes_count_);
}