#pragma once
#include "trie_node_decl.hpp"

#include <cassert>

//---- 1) Public methods ------------------------------------------------------------//
inline bool base_trie::trie_node::has_value() const
{
	return value_ptr.operator bool();
}

inline base_trie::value_type& base_trie::trie_node::get_value()
{
	assert(has_value());
	return *value_ptr;
}

inline base_trie::value_type const& base_trie::trie_node::get_value() const
{
	assert(has_value());
	return *value_ptr;
}

template<class Key>
base_trie::iterator base_trie::trie_node::begin(Key&& sub_key)
{
	auto current_node_it = children.begin();

	if (current_node_it == children.end())
	{
		return end();
	}
	std::string key(std::forward<Key>(sub_key));
	key.push_back(current_node_it->first);

	while (!current_node_it->second.has_value())
	{
		current_node_it = current_node_it->second.children.begin();
		key.push_back(current_node_it->first);
	}

	return { current_node_it, std::move(key), *this };
}

template<class Key>
base_trie::const_iterator base_trie::trie_node::begin(Key&& sub_key) const
{
	auto begin= to_self->second.begin(std::forward<Key>(sub_key));
	
	return { begin.current_node_, std::move(begin.get_key()), *this };
	//auto current_node_it = children.begin();
	//
	//if (current_node_it == children.end())
	//{
	//	return end();
	//}
	//std::string key(std::forward<Key>(sub_key));
	//key.push_back(current_node_it->first);
	//
	//while (!current_node_it->second.has_value())
	//{
	//	current_node_it = current_node_it->second.children.begin();
	//	key.push_back(current_node_it->first);
	//}
	//
	//return { current_node_it, std::move(key), *this };
}

inline base_trie::iterator base_trie::trie_node::end()
{
	return { to_self, *this };
}

inline base_trie::const_iterator base_trie::trie_node::end() const
{
	return { to_self, *this };
}

template <class ... Args>
void base_trie::trie_node::set_value(Args&&... args)
{
	if (!has_value())
	{
		value_ptr.reset(new value_type{ std::forward<Args>(args)... });
	}
}

template <class Key, class ... ValueArgs>
std::pair<base_trie::iterator, bool> base_trie::trie_node::try_emplace(Key&& key, ValueArgs&&... value_args)
{
	auto* current = this;
	node_map_it inserted_it{};
	bool is_inserted = false;

	for (auto const& key_symbol : key)
	{
		std::tie(inserted_it, is_inserted) =
			current->children.try_emplace(key_symbol, current);

		current = &inserted_it->second;

		if (is_inserted)
		{
			current->to_self = inserted_it;
		}
	}
	if (!current->has_value())
	{
		assert(is_inserted);
		current->set_value(std::forward<ValueArgs>(value_args)...);
	}
	
	return {
		iterator(inserted_it, std::forward<Key>(key), *this),
		is_inserted
	};
}

inline base_trie::iterator base_trie::trie_node::find(key_type const& prefix, key_type const& key)
{
	auto const* found = try_find_node(key);
	
	return found != nullptr && found->has_value()
		? iterator(found->to_self,  prefix + key, *this)
		: end();
}

inline base_trie::const_iterator base_trie::trie_node::find(base_trie::key_type const& prefix, key_type const& key) const
{
	auto const* found = try_find_node(key);

	return found != nullptr && found->has_value()
		? const_iterator(found->to_self, prefix + key, *this)
		: end();
}

inline base_trie::trie_node* base_trie::trie_node::try_find_node(key_type const& key)
{
	auto* current = this;

	for (auto const& key_symbol : key)
	{
		auto found = current->children.find(key_symbol);

		if (found == current->children.end())
		{
			return nullptr;
		}
		current = &found->second;
	}

	return current;
}

inline base_trie::trie_node const* base_trie::trie_node::try_find_node(key_type const& key) const
{
	auto& self = to_self->second;
	return self.try_find_node(key);
}

inline base_trie::iterator base_trie::trie_node::erase(iterator position)
{
	auto current = (position++).current_node_;
	auto* parent = current->second.parent;

	if (!current->second.is_leaf())
	{
		current->second.clear_value();
		return position;
	}
	while (current->second.is_leaf() && parent != nullptr)
	{
		parent->children.erase(current);
		current = parent->to_self;
		parent = current->second.parent;
	}
	
	return position;
}

inline size_t base_trie::trie_node::erase(key_type const& key)
{
	auto found = find( "", key);

	if (found != end())
	{
		erase(found);
		return 1;
	}
	return 0;
}

inline void base_trie::trie_node::clear_value()
{
	value_ptr.reset();
}

inline bool base_trie::trie_node::is_leaf() const
{
	return children.empty();
}

inline base_trie::trie_node::trie_node(trie_node* parent_node_ptr)
	: parent(parent_node_ptr)
{}

inline bool base_trie::trie_node::operator==(trie_node const& rsh) const
{
	return &children == &rsh.children;
}