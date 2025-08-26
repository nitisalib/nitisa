// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace ntl
{
	template<class Type>
	struct TList
	{
		Type Item;
		TList *Prev;
		TList *Next;

		TList(const Type &item) :
			Item{ item },
			Prev{ nullptr },
			Next{ nullptr }
		{

		}

		TList(const Type &item, TList *prev) :
			Item{ item },
			Prev{ prev },
			Next{ nullptr }
		{
			if (Prev)
			{
				if (Prev->Next)
				{
					Prev->Next->Prev = this;
					Next = Prev->Next;
				}
				Prev->Next = this;
			}
		}
	};

	template<class Type>
	using PList = TList<Type> *;

	template<class Type> bool Free(PList<Type> &head)
	{
		if (head)
		{
			TList<Type> *p{ head }, *next{ p->Next };
			while (p)
			{
				delete p;
				p = next;
				if (p)
					next = next->Next;
			}
			head = nullptr;
			return true;
		}
		return false;
	}

	template<class Type> size_t Count(TList<Type> *head)
	{
		size_t result{ 0 };
		while (head)
		{
			result++;
			head = head->Next;
		}
		return result;
	}

	template<class Type> TList<Type> *Next(TList<Type> *list)
	{
		if (list)
			return list->Next;
		return nullptr;
	}

	template<class Type> TList<Type> *Prev(TList<Type> *list)
	{
		if (list)
			return list->Prev;
		return nullptr;
	}

	template<class Type> TList<Type> *Head(TList<Type> *list)
	{
		while (list && list->Prev)
			list = list->Prev;
		return list;
	}

	template<class Type> TList<Type> *Tail(TList<Type> *list)
	{
		while (list && list->Next)
			list = list->Next;
		return list;
	}

	template<class Type> TList<Type> *Append(PList<Type> &head, TList<Type> *after, const Type &item)
	{
		if (after)
			return new TList<Type>{ item, after };
		if (head)
			return nullptr;
		return head = new TList<Type>{ item };
	}

	template<class Type> TList<Type> *Detach(TList<Type> &list) // Return list->Next
	{
		if (list.Prev)
			list.Prev->Next = list.Next;
		if (list.Next)
			list.Next->Prev = list.Prev;
		list.Prev = nullptr;
		TList<Type> *result{ list.Next };
		list.Next = nullptr;
		return result;
	}

	template<class Type> TList<Type> *Detach(PList<Type> &head, TList<Type> &list) // Return list->Next
	{
		if (head && !list.Prev && &list != head)
			return nullptr;
		if (list.Prev)
			list.Prev->Next = list.Next;
		else
			head = list.Next;
		if (list.Next)
			list.Next->Prev = list.Prev;
		TList<Type> *result{ list.Next };
		list.Prev = nullptr;
		list.Next = nullptr;
		return result;
	}

	template<class Type> TList<Type> *Detach(PList<Type> &head, TList<Type> &first, TList<Type> &last) // Return last->Next
	{
		if (head && !first.Prev && &first != head)
			return nullptr;
		if (first.Prev)
			first.Prev->Next = last.Next;
		else
			head = last.Next;
		if (last.Next)
			last.Next->Prev = first.Prev;
		TList<Type> *result{ last.Next };
		first.Prev = nullptr;
		last.Next = nullptr;
		return result;
	}

	template<class Type> TList<Type> *Delete(TList<Type> *list) // Return list->Next
	{
		if (list)
		{
			TList<Type> *result{ Detach<Type>(*list) };
			delete list;
			return result;
		}
		return nullptr;
	}

	template<class Type> TList<Type> *Delete(PList<Type> &head, TList<Type> *list) // Return list->Next
	{
		if (list)
		{
			TList<Type> *result{ Detach<Type>(head, *list) };
			delete list;
			return result;
		}
		return nullptr;
	}

	template<class Type> TList<Type> *Delete(PList<Type> &head, TList<Type> *first, TList<Type> *last) // Return list->Next
	{
		if (first && last)
		{
			TList<Type> *result{ Detach<Type>(head, *first, *last) }, *next;
			while (first)
			{
				next = first->Next;
				delete first;
				if (first == last)
					break;
				first = next;
			}
			return result;
		}
		return nullptr;
	}

	template<class Type> TList<Type> *Insert(PList<Type> &head, TList<Type> *before, const Type &item)
	{
		if (!before)
		{
			if (head)
				return nullptr;
			head = new TList<Type>{ item };
			return head;
		}
		if (!before->Prev)
		{
			if (head && head != before)
				return nullptr;
			head = new TList<Type>{ item };
			head->Next = before;
			before->Prev = head;
			return head;
		}
		return new TList<Type>{ item, before->Prev };
	}

	template<class Type> bool Insert(PList<Type> &head, TList<Type> *before, TList<Type> &first, TList<Type> &last)
	{
		if ((!before && head) || (before && !before->Prev && head && head != before))
			return false;
		TList<Type> *tmp{ &first };
		Detach<Type>(tmp, first, last);
		if (!before || !before->Prev)
			head = &first;
		last.Next = before;
		if (before)
		{
			first.Prev = before->Prev;
			before->Prev = &last;
		}
		return true;
	}

	template<class Type> TList<Type> *Copy(const TList<Type> &first, const TList<Type> *last, TList<Type> **tail)
	{
		TList<Type> *head{ nullptr }, *t{ nullptr };
		const TList<Type> *p{ &first };
		while (p)
		{
			t = Append<Type>(head, t, p->Item);
			if (p == last)
				break;
			p = p->Next;
		}
		if (tail)
			*tail = t;
		return head;
	}
}