#pragma once
#include <shop_state.hpp>
#include <shop.hpp>

class AdminOptionSelection : public ShopState
{
public:
	void enter(Shop* shop);
	void exit(Shop* shop);
	static ShopState& getInstance();

private:
	AdminOptionSelection();
	AdminOptionSelection(const AdminOptionSelection& other);
	AdminOptionSelection& operator=(const AdminOptionSelection& other);
};