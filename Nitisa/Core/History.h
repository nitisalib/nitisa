// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include <vector>

namespace nitisa
{
	template<class Type>
	class CHistory
	{
	private:
		struct ITEM
		{
			Type Data;
			size_t Size;
		};
		std::vector<ITEM> m_aItems;
		size_t m_iLimitCount;
		size_t m_iLimitSize;
		size_t m_iPosition;
		size_t m_iSize;

		void ApplyLimits();
	public:
		size_t getCount() const; // Stored item count
		Type getItem(const size_t index); // Get item by index
		size_t getLimitCount() const; // Get stored item count limit
		size_t getLimitSize() const; // Get memory usage limit
		size_t getPosition() const; // Return index of active item
		size_t getSize() const; // Return stored items total size

		bool setLimitCount(const size_t value); // Set stored item count limit(0 - unlimited)
		bool setLimitSize(const size_t value); // Set memory usage limit(0 - unlimited)
		bool setPosition(const size_t value); // Set active item index

		CHistory();

		bool Store(const Type item, const size_t size); // Add new item
		void Clear(); // Clear all items
	};

#pragma region Implementation
	template<class Type> CHistory<Type>::CHistory() :
		m_iLimitCount{ 0 },
		m_iLimitSize{ 0 },
		m_iSize{ 0 }
	{

	}

	template<class Type> size_t CHistory<Type>::getCount() const
	{
		return m_aItems.size();
	}

	template<class Type> Type CHistory<Type>::getItem(const size_t index)
	{
		return m_aItems[index].Data;
	}

	template<class Type> size_t CHistory<Type>::getLimitCount() const
	{
		return m_iLimitCount;
	}

	template<class Type> size_t CHistory<Type>::getLimitSize() const
	{
		return m_iLimitSize;
	}

	template<class Type> size_t CHistory<Type>::getSize() const
	{
		return m_iSize;
	}

	template<class Type> size_t CHistory<Type>::getPosition() const
	{
		return m_iPosition;
	}

	template<class Type> bool CHistory<Type>::setLimitCount(const size_t value)
	{
		if (value != m_iLimitCount)
		{
			m_iLimitCount = value;
			ApplyLimits();
			return true;
		}
		return false;
	}

	template<class Type> bool CHistory<Type>::setLimitSize(const size_t value)
	{
		if (value != m_iLimitSize)
		{
			m_iLimitSize = value;
			ApplyLimits();
			return true;
		}
		return false;
	}

	template<class Type> bool CHistory<Type>::setPosition(const size_t value)
	{
		size_t v{ value };
		if (m_aItems.size() == 0)
			v = 0;
		else if (v >= m_aItems.size())
			v = m_aItems.size() - 1;
		if (v != m_iPosition)
		{
			m_iPosition = v;
			return true;
		}
		return false;
	}

	template<class Type> bool CHistory<Type>::Store(const Type item, const size_t size)
	{
		if (size > 0)
		{
			if (m_aItems.size() > 0 && m_iPosition < m_aItems.size() - 1)
			{
				m_iSize -= m_aItems.size() - m_iPosition - 1;
				auto pos{ m_aItems.begin() };
				m_aItems.erase(pos + m_iPosition + 1, m_aItems.end());
			}
			m_aItems.push_back(ITEM{ item, size });
			m_iPosition = m_aItems.size() - 1;
			m_iSize += size;
			ApplyLimits();
			return true;
		}
		return false;
	}

	template<class Type> void CHistory<Type>::ApplyLimits()
	{
		if (m_aItems.size() == 0)
			return;
		if (m_iLimitCount > 0 && m_aItems.size() > m_iLimitCount)
		{
			while (m_aItems.size() > m_iLimitCount && m_iPosition < m_aItems.size() - 1)
			{
				auto pos{ m_aItems.end() };
				pos--;
				m_iSize -= pos->Size;
				m_aItems.erase(pos);
			}
			while (m_aItems.size() > m_iLimitCount && m_iPosition > 0)
			{
				m_iSize -= m_aItems[0].Size;
				m_aItems.erase(m_aItems.begin());
				m_iPosition--;
			}
		}
		if (m_iLimitSize > 0)
		{
			while (m_iSize > m_iLimitSize && m_iPosition < m_aItems.size() - 1)
			{
				auto pos{ m_aItems.end() };
				pos--;
				m_iSize -= pos->Size;
				m_aItems.erase(pos);
			}
			while (m_iSize > m_iLimitSize && m_iPosition > 0)
			{
				m_iSize -= m_aItems[0].Size;
				m_aItems.erase(m_aItems.begin());
				m_iPosition--;
			}
		}
	}

	template<class Type> void CHistory<Type>::Clear()
	{
		m_aItems.clear();
		m_iPosition = 0;
		m_iSize = 0;
	}
	#pragma endregion
}