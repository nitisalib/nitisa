// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Strings.h"
#include <utility>
#include <vector>

namespace nitisa
{
	// IMPORTANT: If you use Variant type item multiple time(in loop, for example) don't forget to clear it before each use to prevent appearing of waste data from previous state.
	class Variant
	{
	public:
		enum class VariantType // Variant data types
		{
			Pointer, // void*
			Bool, // bool
			Integer, // int
			UnsignedInteger, // unsigned int
			Float, // float
			String, // String
			Map, // A list of key -> value associations. Where key is a String and value is Variant
			Array // An array of variants
		};
	private:
		using Map = std::vector<std::pair<String, Variant>>;
		union
		{
			void *vPointer;
			bool vBool;
			int vInteger;
			unsigned int vUnsignedInteger;
			float vFloat;
		};
		String vString;
		Map vArray;
		VariantType m_eType;

		String Stringify(const int level);
	public:
		explicit Variant(); // Create empty(type is vtPointer and value is nullptr)
		explicit Variant(void *value); // Create with specified pointer value
		explicit Variant(const bool value); // Create with specified bool value
		explicit Variant(const int value); // Create with specified int value
		explicit Variant(const unsigned int value); // Create with specified unsigned int value
		explicit Variant(const float value); // Create with specified float value
		explicit Variant(const String &value); // Create with specified String value
		Variant(const Variant &other) = default;
		Variant(Variant &&other) = default;

		VariantType getType() const; // Return type
		bool isSet(const String &key) const; // Check whether element with specified name exists
		bool inArray(const Variant &value) const; // Check whether specified value is in array of elements
		
		bool operator==(const Variant &other) const; // Check whether variants are equal
		bool operator!=(const Variant &other) const; // Check whether variants are not equal

		void operator=(void *value); // Set pointer value
		void operator=(const bool value); // Set bool value
		void operator=(const int value); // Set int value
		void operator=(const unsigned int value); // Set unsigned int value
		void operator=(const float value); // Set float value
		void operator=(const String &value); // Set String value
		Variant &operator=(const Variant &other) = default;
		Variant &operator=(Variant &&other) = default;

		explicit operator void*() const; // Return as pointer
		explicit operator bool() const; // Return as bool
		explicit operator int() const; // Return as int
		explicit operator unsigned int() const; // Return as unsigned int
		explicit operator float() const; // Return as float
		explicit operator String() const; // Return as String

		Variant &operator[](const wchar_t *key); // Get element by name. Create new empty one if not found
		Variant operator[](const int key); //  // Get element by index. Create new empty one if not found or Variant isn't an array or a map

		// Standard iterators
		Map::iterator begin();
		Map::iterator end();
		Map::const_iterator begin() const;
		Map::const_iterator end() const;
		Map::const_iterator cbegin() const;
		Map::const_iterator cend() const;

		// Standard reverse iterators
		Map::reverse_iterator rbegin();
		Map::reverse_iterator rend();
		Map::const_reverse_iterator rbegin() const;
		Map::const_reverse_iterator rend() const;
		Map::const_reverse_iterator crbegin() const;
		Map::const_reverse_iterator crend() const;

		Map::size_type size() const; // Return number of elements
		bool empty() const; // Return whether there are no elements
		Map::iterator erase(Map::const_iterator _Where); // Erase element at specified position
		Map::iterator erase(Map::const_iterator _First, Map::const_iterator _Last); // Erase specified range of elements
		void clear(); // Clear all elements
		Map::const_iterator find(const String &_Keyval) const; // Find element by name
		void push_back(const Variant &value); // Add element

		Variant get(const wchar_t *key) const; // Safely get map/array item by name. If doesn't exist, return null variant
		Variant get(const int index) const; // Safely get map/array item by index. If doesn't exist, return null variant

		void Reset(); // Remove all elements, set type to Pointer, and set value to nullptr
		String Stringify(); // Return JSON encoded string representing the Variant
	#ifdef _DEBUG
		void Print(const AnsiString &spaces = "") const;
	#endif
	};
}