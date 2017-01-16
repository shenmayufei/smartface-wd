#include "stdafx.h"
#include "ListPresenter.h"


ListPresenter::ListPresenter(ListDialog *dialog) :mDialog(dialog)
{
}


ListPresenter::~ListPresenter()
{
}

void ListPresenter::onInit(std::string date)
{
	std::vector<List> list = mDBManager.queryList(date);
	std::vector<ListCheck> listCheck;
	for (List l : list)
	{
		ListCheck check;
		check.id = l.id;
		check.date = l.date;
		check.time = l.time;
		check.image = l.image;
		switch (l.type)
		{
		case START:
			check.type = L"출근";
			break;
		case END:
			check.type = L"퇴근";
			break;
		case LEAVE:
			check.type = L"조퇴";
			break;
		}


		std::vector<User> users = mDBManager.query(l.user_id);
		
		if (users.size() > 0)
		{
			User user = users[0];
			check.name = user.name;
			check.number = user.number;
		}

		listCheck.push_back(check);

	}
	mDialog->onShowList(listCheck);
}
