#pragma once
#include "iterator_base_decl.hpp"
#include "trie_node_decl.hpp"

#include <cassert>

//---- 1) Public methods -----------------------------------------------------------------//
template<class ValueType, class NodeIt>
template<class Key>
base_trie::iterator_base<ValueType, NodeIt>::
iterator_base(
	node_iterator node_it,
	Key&& key,
	trie_node const& root_node
) :
	current_node_(std::move(node_it)),
	root_node_(root_node)
{
	value_.emplace(std::forward<Key>(key), current_node_->second.get_value());
}

template<class ValueType, class NodeIt>
base_trie::iterator_base<ValueType, NodeIt>::iterator_base(
	node_iterator node_it,
	trie_node const& root_node
) :
	current_node_(std::move(node_it)),
	root_node_(root_node)
{}

template<class ValueType, class NodeIt>
typename base_trie::iterator_base<ValueType, NodeIt>::
value_type base_trie::iterator_base<ValueType, NodeIt>::operator*()
{
	assert(!is_root());
	return value_.value();
}

template<class ValueType, class NodeIt>
typename base_trie::iterator_base<ValueType, NodeIt>::
value_type* base_trie::iterator_base<ValueType, NodeIt>::operator->()
{
	assert(!is_root());
	return &value_.value();
}

template<class ValueType, class NodeIt>
bool base_trie::iterator_base<ValueType, NodeIt>
::operator==(iterator_base<ValueType, NodeIt> const& rsh) const
{
	return rsh.value_ == value_;
}

template<class ValueType, class NodeIt>
bool base_trie::iterator_base<ValueType, NodeIt>
::operator!=(iterator_base<ValueType, NodeIt> const& rsh) const
{
	return !operator==(rsh);
}

template<class ValueType, class NodeIt>
base_trie::iterator_base<ValueType, NodeIt>
base_trie::iterator_base<ValueType, NodeIt>::operator++(int)
{
	auto temp = *this;
	++(*this);
	return temp;
}

template<class ValueType, class NodeIt>
base_trie::iterator_base<ValueType, NodeIt>& 
base_trie::iterator_base<ValueType, NodeIt>::operator++()
{
	if (is_leaf())
	{
		while (to_next_node())
		{
			to_parent();

			if (is_root())
			{
				value_.reset();
				return *this;
			}
		}
	}
	while (!has_value())
	{
		immersion();
	}
	replace_value(current_node_->second.get_value());
	
	return *this;
}
//---- 2) Private methods ------------------------------------------------------------//
template<class ValueType, class NodeIt>
void base_trie::iterator_base<ValueType, NodeIt>::immersion()
{
	current_node_ = current_node_->second.children.begin();
	get_key().push_back(current_node_->first);
}

template<class ValueType, class NodeIt>
void base_trie::iterator_base<ValueType, NodeIt>::to_parent()
{
	get_key().pop_back();
	current_node_ = get_parent_it();
}

template<class ValueType, class NodeIt>
base_trie::trie_node& base_trie::iterator_base<ValueType, NodeIt>::get_parent_node()
{
	assert(current_node_->second.parent != nullptr);
	return *current_node_->second.parent;
}

template<class ValueType, class NodeIt>
typename base_trie::iterator_base<ValueType, NodeIt>::
node_iterator base_trie::iterator_base<ValueType, NodeIt>::get_parent_it()
{
	assert(current_node_->second.parent != nullptr);
	return current_node_->second.parent->to_self;
}

template <class ValueType, class NodeIt>
void base_trie::iterator_base<ValueType, NodeIt>::replace_value(base_trie::value_type& value)
{
	assert(value_.has_value());
	auto temp = std::move(get_key());

	value_.reset();
	value_.emplace(std::move(temp), value);
}

template <class ValueType, class NodeIt>
void base_trie::iterator_base<ValueType, NodeIt>::replace_value(base_trie::value_type const& value)
{
	assert(value_.has_value());
	auto temp = std::move(get_key());

	value_.reset();
	value_.emplace(std::move(temp), value);
}

template <class ValueType, class NodeIt>
base_trie::key_type& base_trie::iterator_base<ValueType, NodeIt>::get_key()
{
	assert(value_.has_value());
	return value_.value().first;
}

template<class ValueType, class NodeIt>
bool base_trie::iterator_base<ValueType, NodeIt>::is_leaf() const
{
	return current_node_->second.is_leaf();
}

template<class ValueType, class NodeIt>
bool base_trie::iterator_base<ValueType, NodeIt>::has_value() const
{
	return current_node_->second.has_value();
}

template<class ValueType, class NodeIt> bool base_trie::iterator_base<ValueType, NodeIt>::is_root() const
{
	return root_node_.get() == current_node_->second;
}

// This method trying to increment current_node_ iterator_base
// if next iterator_base is end iterator_base, decrement current_node_ back
// and return true, else return false
template<class ValueType, class NodeIt>
bool base_trie::iterator_base<ValueType, NodeIt>::to_next_node()
{
	auto& parent = get_parent_node();

	++current_node_;

	if (current_node_ == parent.children.end())
	{
		--current_node_;
		return true;
	}
	get_key().back() = current_node_->first;

	return false;
}