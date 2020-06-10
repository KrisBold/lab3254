#pragma once

#include <QObject>

class Subscriber : public QObject
{
	Q_OBJECT

public:
	explicit Subscriber(const QString& name);
	~Subscriber() = default;

	QString getName() const;

	QString& getMagazine();
	
	enum Condition
	{
		Init = 0,
		MagazineDelete = 1,
		MagazineDelWinApi = 2
	};

	bool& subscribe();
	Condition& getCondition();

private:
	QString name;
	QString magazine;
	bool isSubscribe;
	Condition condition;
};