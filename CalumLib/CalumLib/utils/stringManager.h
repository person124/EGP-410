#ifndef STRING_MANAGER_H
#define STRING_MANAGER_H

#include "utils/trackable.h"

#include <string>
#include <map>

template <class T>
class StringManager : public Trackable
{
	public:
		StringManager()
		{
			mItems = std::map<std::string, T*>();
		}

		virtual ~StringManager()
		{
			removeAll();
		}

		void add(const std::string& key, T* item)
		{
			mItems.insert(std::pair<std::string, T*>(key, item));
		}

		void removeItem(const std::string& key)
		{
			std::map<std::string, T*>::iterator iter;
			iter = mItems.find(key);

			if (iter != mItems.end())
			{
				delete mItems.at(key);
				mItems.erase(key);
			}
		}

		void removeAll()
		{
			std::map<std::string, T*>::iterator iter;

			for (iter = mItems.begin(); iter != mItems.end(); iter++)
				delete iter->second;

			mItems.clear();
		}

		T* get(const std::string& key)
		{
			return mItems.at(key);
		}

		int count()
		{
			return mItems.size();
		}
	protected:
		std::map<std::string, T*> mItems;
};

#endif