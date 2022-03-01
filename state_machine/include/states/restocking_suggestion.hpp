#pragma once
#include <shop_state.hpp>
#include <shop.hpp>

class RestockingSuggestion : public ShopState
{
public:
	void enter(Shop* shop);
	void exit(Shop* shop);
	static ShopState& getInstance();

private:
	RestockingSuggestion();
	RestockingSuggestion(const RestockingSuggestion& other);
	RestockingSuggestion& operator=(const RestockingSuggestion& other);
};