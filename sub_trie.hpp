#pragma once
#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>

class trie_iterator;

class base_trie
{
public:
	using iterator = trie_iterator;
	using value_type = int;
	using key_type = std::string;

protected:
	using node_key = key_type::value_type;
};

class sub_trie final : public base_trie
{
	friend iterator;	
	using node_map = std::map<char, sub_trie>;
	using node_map_it = node_map::iterator;
	
	node_map_it parent_;
	node_map children_;
	node_key node_key_;
	std::unique_ptr<value_type> value_;
	
	bool is_leaf() const;
	bool has_value() const;

	value_type& get_value();
	value_type const& get_value() const;
	void set_value(value_type const& value);

	bool compare(sub_trie const& rsh) const;	
public:
	sub_trie(node_key const& key, node_map_it parent);
	sub_trie(sub_trie const& other);
	sub_trie(sub_trie&&) = default;

	std::pair<iterator, bool> insert(
		key_type const& key, 
		value_type const& value
	);
	
};

class trie final : public base_trie
{
	std::map<node_key, sub_trie> root_map_;

public:
	trie();
	std::pair<iterator, bool> insert(
		key_type const& key,
		value_type const& value
	);
};

class trie_iterator
{
public:
	using value_type = std::pair<sub_trie::key_type, int&/*TODO: Change HERE!*/>;
	using distance = ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
	using trie_iterator_category = std::forward_iterator_tag;
	using node_map = std::map<char, sub_trie>;
	using node_map_it = node_map::iterator;
	using key_type = std::string;

	trie_iterator(
		node_map_it node_trie_iterator,
		key_type const& key,
		sub_trie const& root_node
	);
	trie_iterator(trie_iterator const&) = default;
	trie_iterator(trie_iterator&&) = default;

	trie_iterator& operator=(trie_iterator const&) = default;
	trie_iterator& operator=(trie_iterator&&) = default;

	trie_iterator& operator++();
	trie_iterator operator++(int);

	bool operator==(trie_iterator const& rsh) const;
	bool operator!=(trie_iterator const& rsh) const { return !operator==(rsh); }

	value_type operator*() const;
	pointer operator->();

	~trie_iterator() = default;
private:

	node_map_it current_node_it_;
	value_type value_;
	sub_trie const& root_node_;

	void immersion();
	void to_parent();

	sub_trie& get_parent_trie();

	bool is_leaf() const;
	bool has_value() const;
	bool is_end(node_map& parent_node) const;
	bool is_root() const;
	bool to_next_node();
};

//*********************************** trie *************************************************//
//---------------- 1) Private methods ------------------------------------------------------//
//---------------- 2) Public methods -------------------------------------------------------//
inline trie::trie()
	: root_map_({{'\0', sub_trie('\0', {})}})
{}

inline std::pair<base_trie::iterator, bool> trie::insert(key_type const& key, value_type const& value)
{
	return root_map_.begin()->second.insert(key, value);
}
//------------------------------------------------------------------------------------------//



//*********************************** sub_trie *********************************************//
//---------------- 1) Private methods ------------------------------------------------------//
inline bool sub_trie::is_leaf() const
{
	return children_.empty();
}

inline bool sub_trie::has_value() const
{
	return value_.operator bool();
}

inline base_trie::value_type& sub_trie::get_value()
{
	if (!has_value())
	{
		throw std::logic_error(
			"Try to get value_ptr from non-value_ptr sub_trie"
		);
	}
	return *value_;
}

inline base_trie::value_type const& sub_trie::get_value() const
{
	if (!has_value())
	{
		throw std::logic_error(
			"Try to get value_ptr from non-value_ptr sub_trie"
		);
	}
	return *value_;
}

inline void sub_trie::set_value(value_type const& value)
{
	if (!has_value())
	{
		value_.reset(new value_type{ value });
	}
	else
	{
		if constexpr (std::is_copy_assignable_v<value_type>)
		{
			*value_ = value;
		}
		else if (std::is_class_v<value_type>)
		{
			std::destroy_at(value_.get());
			new(value_.get()) value_type{ value };
		}
	}
}

inline bool sub_trie::compare(sub_trie const& rsh) const
{
	return children_.begin() == rsh.children_.begin();
}

//---------------- 2) Public methods -------------------------------------------------------//
inline sub_trie::sub_trie(node_key const& key, node_map_it parent)
	: parent_(std::move(parent)), node_key_(key)
{}

inline sub_trie::sub_trie(sub_trie const& other)
	:
	parent_(other.parent_),
	node_key_(other.node_key_)
{
	if (value_)
	{
		value_.reset(new value_type{ *other.value_ });
	}
}

inline std::pair<sub_trie::iterator, bool>
sub_trie::insert(key_type const& key, value_type const& value)
{

	
	//

	for (auto const& key_symbol : key)
	{
		current_it = current_it->second.children_.try_emplace(key_symbol, key_symbol, current_it).first;
	}
	bool const is_inserted = !current_it->second.has_value();

	if (is_inserted)
	{
		current_it->second.set_value(value);
	}
	return { iterator(current_it, key, *this), is_inserted };
}
//------------------------------------------------------------------------------------------//

//*********************************** trie_iterator ****************************************//
//---------------- 1) Private methods ------------------------------------------------------//
inline void trie_iterator::immersion()
{
	current_node_it_ = current_node_it_->second.children_.begin();
	value_.first.push_back(current_node_it_->first);
}

inline void trie_iterator::to_parent()
{
	value_.first.pop_back();
	current_node_it_ = current_node_it_->second.parent_;
}

inline bool trie_iterator::is_leaf() const
{
	return current_node_it_->second.is_leaf();
}

inline bool trie_iterator::has_value() const
{
	return current_node_it_->second.has_value();
}

inline sub_trie& sub_trie::iterator::get_parent_trie()
{
	return current_node_it_->second.parent_->second;
}

inline bool sub_trie::iterator::is_end(node_map& parent_node) const
{
	return current_node_it_ == parent_node.end();
}

inline bool sub_trie::iterator::is_root() const
{
	return root_node_.compare(current_node_it_->second);
}

inline bool sub_trie::iterator::to_next_node()
{
	auto& parent = get_parent_trie();

	++current_node_it_;

	if (current_node_it_ == parent.children_.end())
	{
		--current_node_it_;
		return true;
	}
	return false;
}

//----------------2) Public methods---------------------------------------------------------//
inline trie_iterator::trie_iterator(
	sub_trie::node_map_it node_trie_iterator,
	sub_trie::key_type const& key,
	sub_trie const& root_node
) :
	current_node_it_(std::move(node_trie_iterator)),
	value_(key, current_node_it_->second.get_value()),
	root_node_(root_node)
{}


inline trie_iterator& trie_iterator::operator++()
{
	if (is_leaf())
	{
		auto is_end = to_next_node();

		while (is_end)
		{
			to_parent();

			if (is_root())
			{
				current_node_it_ = current_node_it_->second.parent_;
				return *this;
			}
			is_end = to_next_node();
		}
	}
	do
	{
		immersion();
	} while (!has_value());

	value_.second = current_node_it_->second.get_value();

	return *this;
}

inline sub_trie::iterator sub_trie::iterator::operator++(int)
{
	auto tmp = *this;
	++(*this);

	return tmp;
}

inline bool trie_iterator::operator==(trie_iterator const& rsh) const
{
	return current_node_it_ == rsh.current_node_it_;
}

inline trie_iterator::value_type trie_iterator::operator*() const
{
	return value_;
}

inline trie_iterator::value_type* trie_iterator::operator->()
{
	return &value_;
}
//------------------------------------------------------------------------------------------//