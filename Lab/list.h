#pragma once

class List;

class Item
{
public:
	friend class List;
	virtual ~Item();

	const Item* Next() const;
	const Item* Prev() const;
private:
	Item* next = nullptr;
	Item* prev = nullptr;
};

class List
{
public:
	List() = default;
	~List();

public:
	const Item* Head() const;
	const Item* Tail() const;

	void Add(Item* item);
	void Delete(int number);
	Item* GetItem(int number);
	Item* Remove(int number);
	void Insert(Item* item, int number);
	int Count();
	void Clear();
	int GetIndex(Item* item);

protected:
	Item* head = nullptr;
	Item* tail = nullptr;
};

