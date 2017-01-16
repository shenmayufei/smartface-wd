#pragma once
#include "ListDialog.h"
#include "DatabaseManager.h"
#include "List.h"
#include "ListCheck.h"
#include <vector>

class ListDialog;
class ListPresenter
{
public:
	ListPresenter(ListDialog *dialog);
	~ListPresenter();

	virtual void onInit(std::string date);
private:
	ListDialog *mDialog;
	DatabaseManager mDBManager;
};

