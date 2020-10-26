#pragma once
#include "base_trie_impl.hpp"
#include "iterator_base_impl.hpp"
#include "trie_node_impl.hpp"
#include "trie_impl.hpp"
#include "sub_trie_impl.hpp"

//#include <cassert>
//#include <string>
//#include <map>
//#include <memory>
//#include <optional>
//
//// Declaration
//class base_trie
//{	
//public:
//	template<class ValueType, class NodeIt>
//	class iterator_base;
//
//	using value_type = int;
//	using key_type = std::string;
//	
//protected:
//	struct trie_node;
//	using node_map = std::map<key_type::value_type, trie_node>;
//	
//	using node_map_it = node_map::iterator;
//	using node_map_const_it = node_map::const_iterator;
//
//	template<class Iterator>
//	constexpr void iterator_validation();
//
//	virtual trie_node& get_root() = 0;
//	virtual trie_node const& get_root() const = 0;
//	virtual key_type get_sub_key() const = 0;
//
//public:
//	using  iterator = iterator_base<value_type&, node_map_it>;
//	using  const_iterator = iterator_base<value_type const&, node_map_const_it>;
//
//	virtual ~base_trie() = default;
//
//	std::pair<iterator, bool> insert(key_type const& key, value_type const& value);
//
//	template<class InputIterator>
//	void insert(InputIterator first, InputIterator last);
//
//	value_type& operator[](key_type const& key);
//
//	bool empty() const;
//	size_t size() const;
//
//	iterator erase(iterator position);
//	size_t erase(key_type const& key);
//	void erase(iterator first, iterator last);
//
//	void clear();
//
//	iterator begin();
//	const_iterator begin() const;
//	const_iterator cbegin() const;
//
//	iterator end();
//	const_iterator end() const;
//	const_iterator cend() const;
//	
//private:
//	size_t size_{0};
//};
//
//template<class ValueType, class NodeIt>
//class base_trie::iterator_base
//{
//public:
//	// Required iterator aliases ------------------------//
//	using iterator_category = std::forward_iterator_tag;
//	using value_type = std::pair<key_type, ValueType>;
//	using difference_type = std::ptrdiff_t;
//	using pointer = value_type*;
//	using reference = value_type&;
//	//--------------------------------------------------//
//
//	using node_map_it = NodeIt;
//	
//private:
//
//	node_map_it current_node_;
//	std::optional<value_type> value_;
//	std::reference_wrapper<trie_node const> root_node_;
//
//public:
//	template<class Key>
//	iterator_base(
//		node_map_it node_it,
//		Key&& key,
//		trie_node const& root_node
//	);
//	iterator_base(
//		node_map_it node_it,
//		trie_node const& root_node
//	);
//	iterator_base(iterator_base const&) = default;
//	iterator_base(iterator_base&&) = default;
//	
//	value_type operator*();
//	value_type* operator->();
//
//	bool operator==(iterator_base const& rsh) const;
//	bool operator!=(iterator_base const& rsh) const;
//
//	iterator_base& operator=(iterator_base const&) = default;
//	iterator_base& operator=(iterator_base&&) = default;
//
//	~iterator_base() = default;
//	
//	iterator_base& operator++();
//	iterator_base operator++(int);
//
//private:
//	friend trie_node;
//
//	void immersion();
//	void to_parent();
//
//	trie_node& get_parent_node();
//	node_map_it get_parent_it();
//
//	bool is_leaf() const;
//	bool has_value() const;
//	bool is_root() const;
//	bool to_next_node();
//};
//
//
//struct base_trie::trie_node final
//{
//	trie_node() = default;
//	explicit trie_node(trie_node* parent_node_ptr);
//
//	template<class... Args>
//	void set_value(Args&& ...args);
//
//	bool operator==(trie_node const& rsh) const;
//	
//	template<class Key>
//	iterator begin(Key&& sub_key);
//
//	template<class Key>
//	const_iterator begin(Key&& sub_key) const;
//	
//	iterator end();
//	const_iterator end() const;
//
//	template<class Key, class... ValueArgs>
//	std::pair<iterator, bool> try_emplace(Key&& key, ValueArgs&&... value_args);
//
//	iterator find(key_type const& key);
//
//	iterator erase(iterator position);
//	size_t erase(key_type const& key);
//
//	~trie_node() = default;
//
//	void clear_value();
//	bool is_leaf() const;
//	bool has_value() const;
//	value_type& get_value();
//	value_type const& get_value() const;
//
//	node_map children{};
//	node_map_it to_self{};
//	trie_node* parent = nullptr;
//	std::unique_ptr<value_type> value_ptr{};
//};
//
////
////class sub_trie final : public base_trie
////{
////public:
////	explicit sub_trie(trie_node& node, key_type const&);
////	explicit sub_trie(trie_node& node, key_type&&);
////
////	std::pair<iterator, bool> insert(key_type const& key, value_type const& value);
////
////	template<class InputIterator>
////	void insert(InputIterator first, InputIterator last);
////
////	value_type& operator[](key_type const& key);
////
////	sub_trie& operator=(sub_trie const& other);
////
////	bool empty() const;
////	size_t size() const;
////
////	iterator erase(iterator position);
////	size_t erase(key_type const& key);
////	void erase(iterator first, iterator last);
////
////	void clear();
////
////	iterator begin();
////	const_iterator begin() const;
////	const_iterator cbegin() const;
////
////	iterator end();
////	const_iterator end() const;
////	const_iterator cend() const;
////
////	void swap(sub_trie& other) noexcept;
////
////private:
////	std::reference_wrapper<trie_node> root_node_;
////	key_type sub_key_;
////};
////
//
//class trie final : public base_trie
//{	
//public:
//	trie();
//	trie(trie const& other);
//	trie(std::initializer_list < std::pair<key_type, value_type> > init_list);
//	template<class InputIterator>
//	trie(InputIterator first, InputIterator last);
//	
//	~trie() = default;
//	
//	std::pair<iterator, bool> insert(key_type const& key, value_type const& value);
//
//	template<class InputIterator>
//	void insert(InputIterator first, InputIterator last);
//
//	value_type& operator[](key_type const& key);
//
//	trie& operator=(trie const& other);
//
//	bool empty() const;
//	size_t size() const;
//	
//	iterator erase(iterator position);
//	size_t erase(key_type const& key);
//	void erase(iterator first, iterator last);
//
//	void clear();
//	
//	iterator begin();
//	const_iterator begin() const;
//	const_iterator cbegin() const;
//	
//	iterator end();
//	const_iterator end() const;
//	const_iterator cend() const;
//
//	void swap(trie& other) noexcept;
//
//private:
//	node_map root_map_;
//	size_t size_{ 0 };
//
//	trie_node& get_root();
//	trie_node const& get_root() const;
//};
//
//
//
////------------------------------ trie_node ------------------------------------------//
////---- 1) Public methods ------------------------------------------------------------//
//inline bool base_trie::trie_node::has_value() const
//{
//	return value_ptr.operator bool();
//}
//
//inline base_trie::value_type& base_trie::trie_node::get_value()
//{
//	assert(has_value());
//	return *value_ptr;
//}
//
//inline base_trie::value_type const& base_trie::trie_node::get_value() const
//{
//	assert(has_value());
//	return *value_ptr;
//}
//
//template<class Key>
//base_trie::iterator base_trie::trie_node::begin(Key&& sub_key)
//{
//	auto current_node_it = children.begin();
//
//	if (current_node_it == children.end())
//	{
//		return end();
//	}
//
//	std::string key(std::forward<Key>(sub_key));
//	key.push_back(current_node_it->first);
//	
//	while (!current_node_it->second.has_value())
//	{
//		current_node_it = current_node_it->second.children.begin();
//		key.push_back(current_node_it->first);
//	}
//
//	return { current_node_it, std::move(key), *this };
//}
//
//template<class Key>
//inline base_trie::const_iterator base_trie::trie_node::begin(Key&& key) const
//{
//	auto begin = begin(std::forward<Key>(key));
//
//	
//}
//
//inline base_trie::iterator base_trie::trie_node::end()
//{
//	return { to_self, *this };
//}
//
//inline base_trie::const_iterator base_trie::trie_node::end() const
//{
//	return { to_self, *this };
//}
//
//template <class ... Args>
//void base_trie::trie_node::set_value(Args&&... args)
//{
//	if (!has_value())
//	{
//		value_ptr.reset(new value_type{ std::forward<Args>(args)... });
//	}
//}
//
//template <class Key, class ... ValueArgs>
//std::pair<base_trie::iterator, bool> base_trie::trie_node::try_emplace(Key&& key, ValueArgs&&... value_args)
//{
//	auto* current = this;
//	node_map_it inserted_it{};
//	bool is_inserted = false;
//	
//	for (auto const& key_symbol : key)
//	{
//		std::tie(inserted_it, is_inserted) = current->children.try_emplace(key_symbol, current);
//		current = &inserted_it->second;
//
//		if (is_inserted)
//		{
//			current->to_self = inserted_it;
//		}
//	}
//	if (!current->has_value())
//	{
//		assert(is_inserted);
//		current->set_value(std::forward<ValueArgs>(value_args)...);
//	}
//
//	return {
//		iterator(inserted_it, std::forward<Key>(key), *this),
//		is_inserted
//	};
//}
//
//inline base_trie::iterator base_trie::trie_node::find(key_type const& key)
//{
//	std::reference_wrapper<trie_node> current = *this;
//	node_map_it found;
//	
//	for (auto const& key_symbol : key)
//	{
//		found = current.get().children.find(key_symbol);
//
//		if (found == current.get().children.end())
//		{
//			return end();
//		}
//		current = found->second;
//	}
//	return { found, key, *this };
//}
//
//inline base_trie::iterator base_trie::trie_node::erase(iterator position)
//{
//	auto current = (position++).current_node_;
//	auto* parent = current->second.parent;
//	
//	if (!current->second.is_leaf())
//	{
//		current->second.clear_value();
//		return position;
//	}
//	
//	while (current->second.is_leaf() && parent != nullptr)
//	{
//		parent->children.erase(current);
//		current = parent->to_self;
//		parent = current->second.parent;
//	}
//	return position;
//}
//
//inline size_t base_trie::trie_node::erase(key_type const& key)
//{
//	auto found = find(key);
//
//	if (found != end())
//	{
//		erase(found);
//		return 1;
//	}
//	return 0;
//}
//
//inline void base_trie::trie_node::clear_value()
//{
//	value_ptr.reset();
//}
//
//inline bool base_trie::trie_node::is_leaf() const
//{
//	return children.empty();
//}
//
//inline base_trie::trie_node::trie_node(trie_node* parent_node_ptr)
//	: parent(parent_node_ptr)
//{
//}
//
//inline bool base_trie::trie_node::operator==(trie_node const& rsh) const
//{
//	return &children == &rsh.children;
//}
////-----------------------------------------------------------------------------------//
//
//
//
//
////------------------------------ base_trie::iterator_base --------------------------------//
////---- 1) Public methods -----------------------------------------------------------------//
//template<class ValueType, class NodeIt>
//template<class Key>
//base_trie::iterator_base<ValueType, NodeIt>::
//iterator_base(
//	node_map_it node_it,
//	Key&& key,
//	trie_node const& root_node
//) :
//	current_node_(std::move(node_it)),
//	root_node_(root_node)
//{
//	value_.emplace(std::forward<Key>(key), current_node_->second.get_value());
//}
//
//template<class ValueType, class NodeIt>
//base_trie::iterator_base<ValueType, NodeIt>::iterator_base(
//	node_map_it node_it,
//	trie_node const& root_node
//) :
//	current_node_(std::move(node_it)),
//	root_node_(root_node)
//{}
//
//template<class ValueType, class NodeIt>
//typename base_trie::iterator_base<ValueType, NodeIt>::
//value_type base_trie::iterator_base<ValueType, NodeIt>::operator*()
//{
//	assert(!is_root());
//	return value_.value();
//}
//
//template<class ValueType, class NodeIt>
//typename base_trie::iterator_base<ValueType, NodeIt>::
//value_type* base_trie::iterator_base<ValueType, NodeIt>::operator->()
//{
//	assert(!is_root());
//	return &value_.value();
//}
//
//template<class ValueType, class NodeIt>
//bool base_trie::iterator_base<ValueType, NodeIt>::operator==(iterator_base<ValueType, NodeIt> const& rsh) const
//{
//	return rsh.value_ == value_;
//}
//
//template<class ValueType, class NodeIt>
//bool base_trie::iterator_base<ValueType, NodeIt>::operator!=(iterator_base<ValueType, NodeIt> const& rsh) const
//{
//	return !operator==(rsh);
//}
//
//template<class ValueType, class NodeIt>
//base_trie::iterator_base<ValueType, NodeIt> base_trie::iterator_base<ValueType, NodeIt>::operator++(int)
//{
//	auto temp = *this;
//	++*this;
//	return temp;
//}
//
//template<class ValueType, class NodeIt>
//base_trie::iterator_base<ValueType, NodeIt>& base_trie::iterator_base<ValueType, NodeIt>::operator++()
//{
//	if (is_leaf())
//	{
//		while (to_next_node())
//		{
//			to_parent();
//
//			if (is_root())
//			{
//				value_.reset();
//				return *this;
//			}
//		}
//	}
//	while (!has_value())
//	{
//		immersion();
//	}
//	// Purpose of next strange code is to reset reference, to value_type object in value_
//	auto temp(std::move(value_.value().first));
//	value_.reset();
//	value_.emplace(std::move(temp), current_node_->second.get_value());
//
//	return *this;
//}
////---- 2) Private methods ------------------------------------------------------------//
//template<class ValueType, class NodeIt>
//void base_trie::iterator_base<ValueType, NodeIt>::immersion()
//{
//	current_node_ = current_node_->second.children.begin();
//	value_.value().first.push_back(current_node_->first);
//}
//
//template<class ValueType, class NodeIt>
//void base_trie::iterator_base<ValueType, NodeIt>::to_parent()
//{
//	value_.value().first.pop_back();	
//	current_node_ = get_parent_it();
//}
//
//template<class ValueType, class NodeIt>
//base_trie::trie_node& base_trie::iterator_base<ValueType, NodeIt>::get_parent_node()
//{
//	assert(current_node_->second.parent != nullptr);
//	return *current_node_->second.parent;
//}
//
//template<class ValueType, class NodeIt>
//typename base_trie::iterator_base<ValueType, NodeIt>::
//node_map_it base_trie::iterator_base<ValueType, NodeIt>::get_parent_it()
//{
//	assert(current_node_->second.parent != nullptr);
//	return current_node_->second.parent->to_self;
//}
//
//template<class ValueType, class NodeIt>
//bool base_trie::iterator_base<ValueType, NodeIt>::is_leaf() const
//{
//	return current_node_->second.is_leaf();
//}
//
//template<class ValueType, class NodeIt>
//bool base_trie::iterator_base<ValueType, NodeIt>::has_value() const
//{
//	return current_node_->second.has_value();
//}
//
//template<class ValueType, class NodeIt> bool base_trie::iterator_base<ValueType, NodeIt>::is_root() const
//{
//	return root_node_.get() == current_node_->second;
//}
//
//// This method trying to increment current_node_ iterator_base
//// if next iterator_base is end iterator_base, decrement current_node_ back
//// and return true, else return false
//template<class ValueType, class NodeIt>
//bool base_trie::iterator_base<ValueType, NodeIt>::to_next_node()
//{
//	auto& parent = get_parent_node();
//
//	++current_node_;
//
//	if (current_node_ == parent.children.end())
//	{
//		--current_node_;
//		return true;
//	}
//	value_.value().first.back() = current_node_->first;
//	
//	return false;
//}
////------------------------------------------------------------------------------------//
//
//template<class It, class Compared>
//constexpr bool _compare_it_value_v = 
//			std::is_same_v< typename std::iterator_traits<It>::value_type, Compared>;
//
////------------------------------ base_trie -------------------------------------------//
////---- 1) Private methods ------------------------------------------------------------//
//template <class Iterator>
//constexpr void base_trie::iterator_validation()
//{
//	static_assert(
//		std::is_base_of_v<std::input_iterator_tag,
//		typename std::iterator_traits<Iterator>::iterator_category>,
//		"Iterator does not derived of std::input_iterator_tag"
//	);
//	static_assert(
//		_compare_it_value_v<Iterator, std::pair<key_type, value_type>>
//		|| _compare_it_value_v<Iterator, std::pair<key_type, value_type&>>
//		|| _compare_it_value_v<Iterator, std::pair<key_type, value_type const>>
//		|| _compare_it_value_v<Iterator, std::pair<key_type, value_type const&>>,
//		"Iterator::value_type doesn't match trie::iterator::value_type"
//	);
//}
////------------------------------------------------------------------------------------//
//
//
////------------------------------ sub_trie --------------------------------------------//
////---- 1) Public methods -------------------------------------------------------------//
//
////------------------------------------------------------------------------------------//
//
//
//
//
////------------------------------ trie ------------------------------------------------//
////---- 1) Private methods ------------------------------------------------------------//
//inline base_trie::trie_node& trie::get_root()
//{
//	return root_map_.begin()->second;
//}
//
//inline base_trie::trie_node const& trie::get_root() const
//{
//	return root_map_.cbegin()->second;
//}
//
//
////---- 2) Public methods ------------------------------------------------------------//
//inline trie::trie()
//{
//	auto [root_node_it, is_inserted] =
//							root_map_.try_emplace('\0', nullptr);
//	
//	root_node_it->second.to_self = root_node_it;
//}
//
//inline trie::trie(trie const& other)
//{
//	trie().swap(*this);
//	insert(other.begin(), other.end());
//}
//
//inline trie::trie(std::initializer_list<std::pair<key_type, value_type>> init_list)
//{
//	trie(init_list.begin(), init_list.end()).swap(*this);
//}
//
//template <class InputIterator>
//trie::trie(InputIterator first, InputIterator last)
//{
//	trie().swap(*this);
//	insert(first, last);
//}
////--------s
//inline void base_trie::swap(base_trie& other) noexcept
//{
//	std::swap(root_map_, other.root_map_);
//	std::swap(size_, other.size_);
//}
//
//inline base_trie& base_trie::operator=(base_trie const& other)
//{
//	if (this == &other)
//	{
//		return *this;
//	}
//	base_trie(other).swap(*this);
//
//	return  *this;
//}
//
////------------------------------ base_trie ------------------------------------------------//
////---- 1) Public methods ------------------------------------------------------------//
//inline std::pair<base_trie::iterator, bool>
//base_trie::insert(key_type const& key, value_type const& value)
//{
//	++size_;
//	return get_root().try_emplace(key, value);
//}
//
//template <class InputIterator>
//void base_trie::insert(InputIterator first, InputIterator last)
//{
//	iterator_validation<InputIterator>();
//	
//	while (first != last)
//	{
//		insert(first->first, first->second);
//		++first;
//	}
//}
//
//inline base_trie::value_type& base_trie::operator[](key_type const& key)
//{
//	++size_;
//	return get_root().try_emplace(key).first->second;
//}
//
//inline bool base_trie::empty() const
//{
//	return get_root().children.empty();
//}
//
//inline size_t base_trie::size() const
//{
//	return size_;
//}
//
//inline base_trie::iterator base_trie::erase(iterator position)
//{
//	--size_;
//	return get_root().erase(position);
//}
//
//inline size_t base_trie::erase(key_type const& key)
//{
//	--size_;
//	return get_root().erase(key);
//}
//
//inline void base_trie::erase(iterator first, iterator last)
//{
//	while (first != last)
//	{
//		erase(first++);
//	}
//}
//
//inline void base_trie::clear()
//{
//	erase(begin(), end());
//}
//
//inline base_trie::iterator base_trie::begin()
//{
//	return get_root().begin("");
//}
//
//inline base_trie::const_iterator base_trie::begin() const
//{
//	return get_root().begin("");
//}
//
//inline base_trie::const_iterator base_trie::cbegin() const
//{
//	return begin();
//}
//
//inline base_trie::iterator base_trie::end()
//{
//	return get_root().end();
//}
//
//inline base_trie::const_iterator base_trie::end() const
//{
//	return get_root().end();
//}
//
//inline base_trie::const_iterator base_trie::cend() const
//{
//	return  end();
//}
////-----------------------------------------------------------------------------------//